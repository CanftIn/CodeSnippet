-- file:: ch03/sumList.hs
module SumList where

sumList (x:xs) = x + sumList xs
sumList []  = 0

data List a = Cons a (List a)
            | Nil
              deriving (Show)

data Tree a = Node a (Tree a) (Tree a)
            | Empty
              deriving (Show)

mySecond :: [a] -> a
mySecond xs = if null (tail xs)
              then error "list too short"
              else head (tail xs)
