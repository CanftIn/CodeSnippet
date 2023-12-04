from load_symbol import Symbol
from production import Production


def test_production():
  # 创建一些符号
  S = Symbol("S")
  A = Symbol("A", True)  # 终结符
  B = Symbol("B", True)

  # 创建一些产生式
  prod1 = Production(S, ["A", "B"])  # S -> A B
  prod2 = Production(S, ["S", "A"])  # S -> S A (左递归)
  prod3 = Production(S, [""])  # S -> ε

  # 打印产生式
  print(prod1)  # S: A B ;
  print(prod2)  # S: S A ;
  print(prod3)  # S: '' ;

  # 检查属性
  print("prod1 is left recursion:", prod1.is_left_recursion)  # False
  print("prod2 is left recursion:", prod2.is_left_recursion)  # True
  print("prod3 is empty:", prod3.is_empty)  # True


# 运行测试
test_production()
