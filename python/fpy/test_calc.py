import string
from typing import List, Callable
from dataclasses import dataclass
from parsec import (
    parser,
    one,
    neg,
    pmaybe,
    many,
    many1,
    ptrans,
    peek,
    skip,
    pseq,
    inv,
    isspace,
    trans
)
from either import Left, Right


def is_digit(c):
  return c in string.digits

def is_operator(c):
  return c in "+-*/"

def digit():
  return one(is_digit)

def operator():
  return one(is_operator)

def space():
  return many(one(isspace))

def number():
  @parser
  def parse_number(s):
    num_result = many1(digit())(s)
    if isinstance(num_result, Right):
      digits, rest = num_result.v
      num = int(''.join(digits))
      return Right((num, rest))
    return Left(s)

  return parse_number

def expression():
  @parser
  def parse_expr(s):
    num_result = number()(s)
    if isinstance(num_result, Right):
      left_num, rest = num_result.v
      if rest and rest[0] in '+-':
        op = rest[0]
        rest_expr = parse_expr(rest[1:])
        if isinstance(rest_expr, Right):
          right_num, final_rest = rest_expr.v
          return Right(
            (
              left_num + right_num if op == "+" else left_num - right_num,
              final_rest,
            )
          )
      return Right((left_num, rest))
    return Left(s)

  return parse_expr

def calc(expr_str):
    expr_parser = expression()
    result = expr_parser(expr_str)
    if isinstance(result, Right):
      value, _ = result.v
      return value
    else:
      return "parse error"

print(calc("10 + 20"))  # 30
print(calc("30 - 10"))  # 20

num = number()("10+20")

if isinstance(num, Right):
    value, rest = num.v
    print(f"数字: {value}, 剩余字符串: {rest}")
else:
    print("解析错误")