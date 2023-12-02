from function import func, SignatureMismatchError, NotEnoughArgsError

import unittest


def add1(x):
  return x + 1

def mul2(x):
  return x * 2

def pos(x):
  return x > 0

def odd(x):
  return x % 2 != 0

def add(a, b):
  return a + b


class TestCompsable(unittest.TestCase):
  def testFunc(self):
    f1 = func(add1)
    f2 = func(mul2)
    self.assertEqual(4, (f1 ^ f2)(1))
    self.assertEqual(3, (f2 ^ f1)(1))


unittest.main()