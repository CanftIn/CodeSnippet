from __future__ import unicode_literals, print_function
import sys
import os
import time
import json
import copy
import re
import collections
import pprint

from enum import Enum, IntEnum

#----------------------------------------------------------------------
# 符号类：包括终结符和非终结符，term 代表是否为终结符，
# 空的话用空字符串表示
#----------------------------------------------------------------------
class Symbol(object):
  def __init__(self, name, terminal = False):
    self.name = name
    self.term = terminal
  
  # 转为可打印字符串
  def __str__(self):
    if not self.name:
      return "''"
    return self.name

  # 判断是否相等
  def __eq__(self, symbol):
    if isinstance(symbol, str):
      return (self.name == symbol)
    elif symbol is None:
      return (self is None)
    elif not isinstance(symbol, Symbol):
      raise TypeError('Symbol cannot be compared to a %s'%type(symbol))
    return (self.name == symbol.name)

  def __ne__(self, symbol):
    return (not (self == symbol))

  # >=
  def __ge__(self, symbol):
    return (self.name >= symbol.name)

  # > 
  def __gt__(self, symbol):
    return (self.name > symbol.name)

  # <=
  def __le__(self, symbol):
    return (self.name <= symbol.name)

  # < 
  def __lt__(self, symbol):
    return (self.name < symbol.name)

  def __repr__(self):
    if not self.term:
      return '%s(%r)'%(type(self).__name__, self.name)
    return '%s(%r, %r)'%(type(self).__name__, self.name, self.term)

  # 求哈希，有这个函数可以将 Symbol 放到容器里当 key
  def __hash__(self):
    return hash(self.name)

  # 拷贝
  def __copy__(self):
    obj = Symbol(self.name, self.term)
    if hasattr(self, 'value'):
      obj.value = self.value
    if hasattr(self, 'token'):
      obj.token = self.token
    return obj

  # 深度拷贝
  def __deepcopy__(self):
    obj = Symbol(self.name, self.term)
    if hasattr(self, 'value'):
      obj.value = copy.deepcopy(self.value)
    if hasattr(self, 'token'):
      obj.token = copy.deepcopy(self.token)
    return obj

  # 判断是否是字符串字面量
  def _is_literal(self):
    if len(self.name) < 2:
      return False
    mark = self.name[0]
    if mark not in ('"', "'"):
      return False
    if self.name[-1] == mark:
      return True
    return False

  # 判断是否是空/epsilon
  @property
  def is_epsilon(self):
    if self.term:
      return False
    elif self.name == '':
      return True
    if self.name in ('%empty', '%e', '%epsilon', '\u03b5', '<empty>'):
      return True
    return False

  # 判断是否是字符串字面量
  @property
  def is_literal(self):
    return self._is_literal()


#----------------------------------------------------------------------
# 从字符串或者 tuple 创建一个 Symbol
#----------------------------------------------------------------------
def load_symbol(source):
  if isinstance(source, Symbol):
    return source
  elif isinstance(source, str):
    sym = Symbol(source)
    if sym.is_literal:
      sym.term = True
      if len(sym.name) == 2 and sym.name[0] == sym.name[1]:
        sym.term = False
        sym.name = ''
      try: sym.value = eval(sym.name)
      except: pass
    elif source == '$':
      sym.term = True
    elif source == '#':
      sym.term = True
    return sym
  elif isinstance(source, list) or isinstance(source, tuple):
    assert len(source) > 0
    if len(source) == 0:
      raise ValueError('bad symbol: %r'%source)
    elif len(source) == 1:
      return Symbol(source[0])
    elif len(source) == 2:
      return Symbol(source[0], source[1])
    s = Symbol(source[0], source[1])
    s.value = source[2]
    return s
  raise ValueError('bad symbol: %r'%source)