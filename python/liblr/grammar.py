from load_symbol import Symbol, load_symbol
from production import Production
from grammar_error import GrammarError
from vector import Vector

# 语法类，一个语法 G 由终结符，非终结符和产生式组成
class Grammar(object):
  def __init__(self):
    self.production = []
    self.symbol = {}  # str -> Symbol map
    self.terminal = {}  # str -> Symbol map
    self.rule = {}  # str -> list
    self.precedence = {}  # str -> prec
    self.assoc = {}  # str -> one of (None, 'left', 'right')
    self._anchor = {}  # str -> (filename, linenum)
    self._dirty = False
    self.scanner = []  # scanner rules
    self.start = None

  def reset(self):
    self.production.clear()
    self.symbol.clear()
    self.terminal.clear()
    self.nonterminal.clear()
    self.rule.clear()
    self._anchor.clear()
    self.scanner.clear()
    self.start = None
    return 0

  def _symbol_name(self, symbol):
    if isinstance(symbol, Symbol):
      return symbol.name
    elif isinstance(symbol, str):
      return symbol
    raise TypeError("bad symbol: %r" % symbol)

  def __len__(self):
    return len(self.production)

  def __getitem__(self, index):
    return self.production[index]

  def __iter__(self):
    return self.production.__iter__()

  def __contains__(self, key):
    if isinstance(key, int):
      return key >= 0 and key < len(self.production)
    elif isinstance(key, Production):
      for p in self.production:
        if p == key:
          return True
    elif isinstance(key, Symbol):
      return key.name in self.symbol
    elif isinstance(key, str):
      return key in self.symbol
    return False

  def __copy__(self):
    obj = Grammar()
    for p in self.production:
      obj.push_production(p.__copy__())
    for t in self.terminal:
      obj.push_token(t)
    for p in self.precedence:
      c = self.precedence[p]
      obj.push_precedence(p, c[0], c[1])
    obj.srcinfo = self.srcinfo.__copy__()
    obj.update()
    if self.start:
      obj.start = obj.symbol[self.start.name]
    return obj

  def __deepcopy__(self, memo):
    obj = Grammar()
    for p in self.production:
      obj.push_production(p.__deepcopy__(memo))
    for t in self.terminal:
      obj.push_token(t)
    for p in self.precedence:
      c = self.precedence[p]
      obj.push_precedence(p, c[0], c[1])
    obj.srcinfo = self.srcinfo.__deepcopy__(memo)
    obj.update()
    if self.start:
      obj.start = obj.symbol[self.start.name]
    return obj

  def insert(self, index, production):
    self.production.insert(index, production)
    self._dirty = True

  def search(self, p, stop=-1):
    if stop < 0:
      return self.production.index(p)
    return self.production.index(p, stop)

  def remove(self, index):
    if isinstance(index, int):
      self.production.pop(index)
    else:
      index = self.search(index)
      self.production.pop(index)
    self._dirty = True

  def pop(self, index=-1):
    self.production.pop(index)
    self._dirty = True

  def append(self, production):
    index = len(self.production)
    self.production.append(production)
    production.index = index
    self._dirty = True

  def replace(self, index, source):
    if isinstance(source, Production):
      self.production[index] = source
    elif isinstance(source, list) or isinstance(source, tuple):
      for n in source:
        assert isinstance(n, Production)
        self.production.insert(index + 1, n)
      self.production.pop(index)
    self._dirty = True

  def update(self):
    self.symbol.clear()
    self.rule.clear()
    for i, p in enumerate(self.production):
      p.index = i
      head = p.head
      if head.name not in self.symbol:
        self.symbol[head.name] = head
      for n in p.body:
        if n.name not in self.symbol:
          self.symbol[n.name] = n
      if head.name not in self.rule:
        self.rule[head.name] = []
      self.rule[head.name].append(p)
    for n in self.terminal:
      s = self.terminal[n]
      if not s.term:
        s.term = True
    for n in self.symbol:
      s = self.symbol[n]
      s.term = n in self.terminal
      if not s.term:
        if s.name not in self.rule:
          self.rule[s.name] = []
    for p in self.production:
      p.head.term = p.head.name in self.terminal
      for n in p.body:
        n.term = n.name in self.terminal
    for p in self.production:
      if p.precedence is None:
        rightmost = p.rightmost_terminal()
        if rightmost and (rightmost in self.precedence):
          p.precedence = rightmost.name
    self._dirty = False
    return 0

  # declare terminal
  def push_token(self, token):
    name = self._symbol_name(token)
    if token not in self.terminal:
      t = load_symbol(token)
      t.term = True
      self.terminal[name] = t
    self._dirty = True
    return 0

  # push precedence
  def push_precedence(self, symbol, prec, assoc):
    name = self._symbol_name(symbol)
    if prec == "precedence":
      prec = "left"
    self.precedence[name] = prec
    self.assoc[name] = assoc

  # push scanner (aka. lexer) rules
  def push_scanner(self, obj):
    self.scanner.append(obj)
    return 0

  # create new symbol according to self.terminal
  def create_symbol(self, name):
    cc = load_symbol(name)
    if name != "":
      if name in self.terminal:
        cc.term = True
    return cc

  # argument
  def argument(self):
    if not self.start:
      raise GrammarError("no start point")
    if "S^" in self.symbol:
      raise GrammarError("already argumented")
    head = "S^"
    p = Production(head, [self.start])
    self.insert(0, p)
    self.start = p.head
    self.update()
    return 0

  def __anchor_key(self, obj):
    if isinstance(obj, str):
      return obj
    elif isinstance(obj, Symbol):
      return str(obj)
    elif isinstance(obj, int):
      return "^INT/" + str(obj)
    elif isinstance(obj, Vector):
      return "^VEC/" + str(obj)
    elif isinstance(obj, Production):
      return "^PROD/" + str(obj)
    return str(obj)

  # anchor: source file info (filename, line_num)
  def anchor_set(self, obj, filename, line_num):
    self._anchor[self.__anchor_key(obj)] = (filename, line_num)
    return 0

  def anchor_get(self, obj):
    key = self.__anchor_key(obj)
    if key not in self._anchor:
      return (None, None)
    return self._anchor[key]

  def anchor_has(self, obj):
    key = self.__anchor_key(obj)
    return key in self._anchor

  def print(self, mode=0, action=False, prec=False):
    if mode == 0:
      for i, n in enumerate(self.production):
        t = "(%d) %s" % (i, n.stringify(True, True, action, prec))
        print(t)
    else:
      keys = list(self.rule.keys())
      for key in keys:
        head = str(key) + ": "
        padding = " " * (len(head) - 2)
        for i, p in enumerate(self.rule[key]):
          if i == 0:
            print(head, end="")
          else:
            print(padding + "| ", end="")
          print(p.stringify(False, True, action, prec), end=" ")
          if len(self.rule[key]) > 1:
            print("")
        if len(self.rule[key]) > 1:
          print(padding + ";")
        else:
          print(";")
    return 0

  def __str__(self):
    text = []
    for i, n in enumerate(self.production):
      t = "(%d) %s" % (i, str(n))
      text.append(t)
    return "\n".join(text)
