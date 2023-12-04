import unittest

from load_symbol import Symbol, load_symbol

class TestSymbol(unittest.TestCase):
  def test_symbol_creation(self):
    sym = Symbol("A")
    self.assertEqual(sym.name, "A")
    self.assertFalse(sym.term)

  def test_symbol_comparison(self):
    sym1 = Symbol("A")
    sym2 = Symbol("A", True)
    sym3 = Symbol("B")
    self.assertEqual(sym1, "A")
    self.assertNotEqual(sym1, sym3)
    self.assertTrue(sym1 < sym3)
    self.assertFalse(sym2 < sym1)

  def test_symbol_hash_and_copy(self):
    sym = Symbol("A")
    sym_copy = sym.__copy__()
    self.assertEqual(hash(sym), hash(sym_copy))
    self.assertEqual(sym, sym_copy)

  def test_special_properties(self):
    literal = Symbol('"A"')
    epsilon = Symbol("")
    self.assertTrue(literal.is_literal)
    self.assertTrue(epsilon.is_epsilon)

  def test_load_symbol_from_string(self):
    sym = load_symbol("A")
    self.assertEqual(sym, Symbol("A"))

  def test_load_symbol_from_tuple(self):
    sym = load_symbol(("A", True))
    self.assertEqual(sym, Symbol("A", True))

  def test_load_symbol_error(self):
    with self.assertRaises(ValueError):
      load_symbol(123)  # Invalid type

# 运行测试
if __name__ == '__main__':
  unittest.main()
