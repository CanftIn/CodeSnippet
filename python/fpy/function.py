import inspect
import collections.abc as cabc

from composable import Composable
from transparent import Transparent

from typing import TypeVar, Callable

import sys
import traceback

class SignatureMismatchError(Exception):
  def __init__(self, e):
    self.e = e


class NotEnoughArgsError(Exception):
  def __init__(self, expect, got):
    self.expect = expect
    self.got = got


class func(Composable, Transparent):
  fn: Callable = None

  def __init__(self, f, *args, **kwargs):
    if isinstance(f, func):
      self.fn = f.fn
      self.args = (*f.args, *args)
      self.kwargs = {**f.kwargs, **kwargs}
      self.sig = f.sig
    elif isinstance(f, cabc.Callable):
      self.fn = f
      self.args = args
      self.kwargs = kwargs
      self.sig = inspect.signature(f)
    else:
        raise TypeError(f"{f} is not callable")

  def __underlying__(self):
    return self.fn

  def __repr__(self):
    return repr(self.fn)

  def __call__(self, *args, **kwargs):
    _args = (*self.args, *args)
    _kwargs = {**self.kwargs, **kwargs}
    try:
      self.sig.bind(*_args, **_kwargs)
      return self.fn(*_args, **_kwargs)
    except TypeError as e:
      try:
        self.sig.bind_partial(*_args, **_kwargs)
        return func(self, *args, **kwargs)
      except TypeError as e:
        raise SignatureMismatchError(e)
    except NotEnoughArgsError:
      return func(self, *args, **kwargs)

  def __compose__(self, other):
    if isinstance(other, func):
      return self.__class__(lambda *args, **kwargs: other(self(*args, **kwargs)))
    if isinstance(other, cabc.Callable):
      fn = func(other)
      return self.__class__(lambda *args, **kwargs: fn(self(*args, **kwargs)))
    raise TypeError(f"Cannot compose function with {type(other)}")

T = TypeVar("T")
F = TypeVar("F")
A = TypeVar("A")
B = TypeVar("B")


def id_(x: T) -> T:
    return x

@func
def const(x: T, _: any) -> T:
  return x

@func
def flip(f: Callable[[B, A], T], a: A, b: B) -> T:
  return f(b, a)

def fix(f: Callable) -> Callable:
  fn = func(f)
  return lambda *args: fn(fix(fn))(*args)

@func
def on(b: Callable[[B, B], T], u: Callable[[A], B], x: A, y: A) -> T:
  return b(u(x), u(y))