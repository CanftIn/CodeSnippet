import copy
from load_symbol import load_symbol
from vector import Vector

# ----------------------------------------------------------------------
# 产生式/生成式：由 head -> body 组成，head 是 Symbol，
# body 是一个 Vector，即 Symbol 组成的序列
# ----------------------------------------------------------------------
class Production(object):
  def __init__(self, head, body, index=-1):
    self.head = load_symbol(head)
    self.body = Vector(body)
    self.__hash = None
    self.index = index
    self.is_epsilon = None
    self.has_epsilon = None
    self.precedence = None
    self.action = None

  def __len__(self):
    return len(self.body)

  def __getitem__(self, index):
    return self.body[index]

  def __contains__(self, key):
    return key in self.body

  def __hash__(self):
    if self.__hash is None:
      h1 = hash(self.head)
      h2 = hash(self.body)
      self.__hash = hash((h1, h2))
    return self.__hash

  def __iter__(self):
    return self.body.__iter__()

  def __repr__(self):
    return "%s(%r, %r)" % (type(self).__name__, self.head, self.body)

  def __str__(self):
    body = [str(n) for n in self.body]
    return "%s: %s ;" % (self.head, " ".join(body))

  def __eq__(self, p):
    assert isinstance(p, Production)
    if hash(self) != hash(p):
      return False
    if self.head != p.head:
      return False
    return self.body == p.body

  def __ne__(self, p):
    return not (self == p)

  def __ge__(self, p):
    if self.head > p.head:
      return True
    elif self.head < p.head:
      return False
    return self.body >= p.body

  def __gt__(self, p):
    if self.head > p.head:
      return True
    elif self.head < p.head:
      return False
    return self.body > p.body

  def __lt__(self, p):
    return not (self >= p)

  def __le__(self, p):
    return not (self > p)

  def __copy__(self):
    obj = Production(self.head, self.body)
    obj.index = self.index
    obj.precedence = self.precedence
    obj.is_epsilon = self.is_epsilon
    obj.has_epsilon = self.has_epsilon
    obj.__hash = self.__hash
    obj.action = self.action
    return obj

  def __deepcopy__(self):
    p = self.body.__deepcopy__()
    obj = Production(self.head.__deepcopy__(), p)
    obj.index = self.index
    obj.precedence = self.precedence
    obj.is_epsilon = self.is_epsilon
    obj.has_epsilon = self.has_epsilon
    obj.__hash = self.__hash
    if self.action:
      obj.action = copy.deepcopy(self.action)
    return obj

  def search(self, symbol, stop=-1):
    return self.body.search(symbol, stop)

  @property
  def is_empty(self):
    return len(self.body) == 0

  # 计算最右边的终结符
  def rightmost_terminal(self):
    return self.body.rightmost_terminal()

  # 最左侧的终结符
  def leftmost_terminal(self):
    return self.body.leftmost_terminal()

  # 计算是否直接左递归
  @property
  def is_left_recursion(self):
    if len(self.body) == 0:
      return False
    return self.head == self.body[0]

  # 计算是否直接右递归
  @property
  def is_right_recursion(self):
    if len(self.body) == 0:
      return False
    return self.head == self.body[-1]

  def __action_to_string(self, m):
    if isinstance(m, str):
      return m
    assert isinstance(m, tuple)
    name: str = m[0]
    stack = m[1]
    if name.startswith("{") and name.endswith("}"):
      return "{%s/%d}" % (name[1:-1], stack)
    return "%s/%d" % (name, stack)

  # 返回包含动作的身体部分
  def stringify(self, head=True, body=True, action=False, prec=False):
    text = ""
    if head:
      text += str(self.head) + ": "
    act = getattr(self, "action", {})
    if body:
      for i, n in enumerate(self.body.m):
        if action and act and (i in act):
          for m in act[i]:
            text += "%s " % self.__action_to_string(m)
        text += n.name + " "
      i = len(self.body)
      if action and act and (i in act):
        for m in act[i]:
          text += "%s " % self.__action_to_string(m)
    if prec:
      text += " <%s>" % (self.precedence,)
    return text.strip("\r\n\t ")
