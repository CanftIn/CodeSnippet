from abc import ABCMeta, abstractmethod

from applicative import _Applicative
from typing import TypeVar, Generic, Callable


T = TypeVar("T")
R = TypeVar("R")


class _Monad(_Applicative[T], Generic[T]):
  @classmethod
  def ret(cls, val):
    return cls(val)

  def __bind__(self, b):
    raise NotImplementedError

  def __rshift__(self, b):
    return self.__bind__(b)

class SimpleMonad(_Monad):
  def __init__(self, val):
    self.val = val

  def __bind__(self, b):
    return b(self.val)