from load_symbol import load_symbol

#----------------------------------------------------------------------
# 符号矢量：符号列表
#----------------------------------------------------------------------

class Vector(object):
  def __init__(self, vector):
    self.m = tuple(self.__load_vector(vector))
    self.__hash = None

  def __load_vector(self, vector):
    epsilon = True
    output = []
    p = [ load_symbol(n) for n in vector ]
    for symbol in p:
      if not symbol.is_epsilon:
        epsilon = False
        break
    if not epsilon:
      for n in p:
        if not n.is_epsilon:
          output.append(n)
    return output

  def __len__(self):
    return len(self.m)

  def __getitem__(self, index):
    return self.m[index]

  def __contains__(self, key):
    if isinstance(key, int):
      return (key >= 0 and key < len(self.m))
    for n in self.m:
      if n == key:
        return True
    return False

  def __hash__(self):
    if self.__hash is None:
      h = tuple([n.name for n in self.m])
      self.__hash = hash(h)
    return self.__hash

  def __iter__(self):
    return self.m.__iter__()

  def __repr__(self):
    return '%s(%r)'%(type(self).__name__, self.m)

  def __str__(self):
    body = [ str(n) for n in self.m ]
    return ' '.join(body)

  def __eq__(self, p):
    assert isinstance(p, Vector)
    if hash(self) != hash(p):
      return False
    return (self.m == p.m)

  def __ne__(self, p):
    return (not (self == p))

  def __ge__(self, p):
    return (self.m >= p.m)

  def __gt__(self, p):
    return (self.m > p.m)

  def __le__(self, p):
    return (self.m <= p.m)

  def __lt__(self, p):
    return (self.m < p.m)

  def __copy__(self):
    obj = Vector(self.m)
    obj.__hash = self.__hash
    return obj

  def __deepcopy__(self):
    p = [ n.__deepcopy__() for n in self.m ]
    obj = Vector(p)
    obj.__hash = self.__hash
    return obj

  def search(self, symbol, stop = -1):
    if stop < 0:
      return self.m.index(symbol)
    return self.m.index(symbol, stop)

  @property
  def is_empty(self):
    return (len(self.m) == 0)

  # 计算最左边的终结符
  def leftmost_terminal(self):
    for n in self.m:
      if n.term:
        return n
    return None

  # 计算最右边的终结符
  def rightmost_terminal(self):
    index = len(self.m) - 1
    while index >= 0:
      symbol = self.m[index]
      if symbol.term:
        return symbol
      index -= 1
    return None

