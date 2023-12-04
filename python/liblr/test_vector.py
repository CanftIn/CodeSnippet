import unittest

from load_symbol import Symbol
from vector import Vector


class TestVector(unittest.TestCase):
  def test_vector_creation(self):
    vec = Vector(["A", "B", "C"])
    self.assertEqual(len(vec), 3)

  def test_vector_access(self):
    vec = Vector(["A", "B", "C"])
    self.assertEqual(vec[0], Symbol("A"))
    self.assertIn("B", vec)

  def test_vector_iteration(self):
    vec = Vector(["A", "B", "C"])
    symbols = [s for s in vec]
    self.assertEqual(symbols, [Symbol("A"), Symbol("B"), Symbol("C")])

  def test_vector_hash(self):
    vec1 = Vector(["A", "B", "C"])
    vec2 = Vector(["A", "B", "C"])
    self.assertEqual(hash(vec1), hash(vec2))

  def setUp(self):
    self.non_terminal_vec = Vector(["A", "B", "C"])  # 均为非终结符
    self.mixed_vec = Vector(["A", Symbol("b", True), "C", Symbol("d", True)])  # 混合终结符和非终结符

  def test_leftmost_terminal(self):
    # 没有终结符的情况
    self.assertIsNone(self.non_terminal_vec.leftmost_terminal())

    # 混合终结符和非终结符的情况
    leftmost = self.mixed_vec.leftmost_terminal()
    self.assertEqual(leftmost, Symbol("b", True))

  def test_rightmost_terminal(self):
    # 没有终结符的情况
    self.assertIsNone(self.non_terminal_vec.rightmost_terminal())

    # 混合终结符和非终结符的情况
    rightmost = self.mixed_vec.rightmost_terminal()
    self.assertEqual(rightmost, Symbol("d", True))

unittest.main()
