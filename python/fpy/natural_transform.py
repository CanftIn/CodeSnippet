from __future__ import annotations

from abc import ABCMeta, abstractmethod
from dataclasses import dataclass
from typing import TypeVar, Generic, Callable


F = TypeVar("F")
G = TypeVar("G")
A = TypeVar("A")
B = TypeVar("B")


class _NTrans(Generic[F, A, G, B], metaclass=ABCMeta):
  @abstractmethod
  def __trans__(self, v: A) -> G[B]:
    raise NotImplementedError

  def __call__(self, v: A) -> G[B]:
    return self.__trans__(v)


@dataclass
class NTrans(_NTrans):
  f: Callable[[A], G[B]]

  def __trans__(self, v: F[A]) -> G[B]:
    assert hasattr(v, "__ntrans__")
    return v.__ntrans__(self.f)

# from typing import List, Optional
# 
# class ListFunctor:
#   def __init__(self, values):
#     self.values = values
# 
#   def __ntrans__(self, f):
#     if self.values:
#       return f(self.values[0])
#     return None
# 
# class OptionFunctor:
#   def __init__(self, value):
#     self.value = value
# 
# # ListFunctor 和 OptionFunctor 分别代表 F 和 G 函子。
# # 从 A 到 G[B]（OptionFunctor）的转换函数。
# def list_to_option(x: ListFunctor) -> OptionFunctor:
#   return OptionFunctor(x)
# 
# list_functor = ListFunctor([1, 2, 3])
# 
# # 自然转换: 将一个列表的第一个元素转换为一个选项。
# transformation = NTrans(list_to_option)
# 
# # 应用自然转换
# option_functor = transformation(list_functor)
# 
# print(option_functor.value)  # 1