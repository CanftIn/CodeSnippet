import Text.Parsec
import Text.Parsec.String (Parser)
import qualified Text.Parsec.Expr as Expr
import Text.Parsec.Token
import Text.Parsec.Language (emptyDef)
import Control.Applicative ()
import Data.Functor.Identity

lexer :: TokenParser ()
lexer = makeTokenParser emptyDef

number :: Parser Integer
number = natural lexer

binary :: String -> (a -> a -> a) -> Expr.Assoc -> Expr.Operator String () Identity a
binary name fun assoc = Expr.Infix (do{ reservedOp lexer name; return fun }) assoc

table :: [[Expr.Operator String () Identity Integer]]
table = [ [binary "*" (*) Expr.AssocLeft, binary "/" div Expr.AssocLeft]
        , [binary "+" (+) Expr.AssocLeft, binary "-" (-) Expr.AssocLeft]
        ]

expr :: Parser Integer
expr = Expr.buildExpressionParser table factor

factor :: Parser Integer
factor = parens lexer expr <|> number

parseString :: String -> Either ParseError Integer
parseString input = parse (whiteSpace lexer >> expr) "" input

main :: IO ()
main = do
  let input = "1 + 2 * 3"
  case parseString input of
    Left err -> print err
    Right result -> print result
