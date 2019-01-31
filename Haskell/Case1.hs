module Case1 where

myLast :: [a] -> a
myLast = head . reverse

data List a = Empty
            | Cons a (List a)
            deriving Show

myMap :: (a -> b) -> List a -> List b
myMap _ Empty = Empty
myMap func (Cons a rest) = Cons (func a) (myMap func rest)

testList1 :: List Int
testList1 = Cons 1 (Cons 2 (Cons 3 Empty))