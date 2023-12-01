import sys
from tokenize import generate_tokens

from grammar import GrammarParser
from tokenizer import Tokenizer
from generator import generate

def main():
  file = "toy.gram"
  print("Reading", file)
  with open(file) as f:
    tokengen = generate_tokens(f.readline)
    tok = Tokenizer(tokengen)
    p = GrammarParser(tok)
    rules = p.grammar()
  if not rules:
    sys.exit("Fail")
  print("[")
  for rule in rules:
    print(f"  {rule},")
  print("]")
  for rule in rules:
    print(rule.name, end=": ", file=sys.stderr)
    print(*(" ".join(alt) for alt in rule.alts), sep=" | ", file=sys.stderr)
  outfile = "toy.py"
  print("Updating", outfile, file=sys.stderr)
  with open(outfile, "w") as stream:
    generate(rules, stream)

if __name__ == '__main__':
  main()