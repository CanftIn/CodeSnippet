import           Prelude hiding (and, not, or, (&&), (/=), (==), (||))

(==) :: Bool -> Bool -> Bool
(==) True True   = True
(==) False False = True
(==) _ _         = False

not :: Bool -> Bool
not True = False
not _    = True


-- Rome
romeNotation :: [String]
romeNotation = ["M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"]

romeAmount :: [Int]
romeAmount = [1000,900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1]

pair :: [(Int, String)]
pair = zip romeAmount romeNotation

subtrahend  :: Int -> (Int, String)
subtrahend n = head (dropWhile (\(a,_) -> a > n) pair)

convert :: Int -> String
convert 0 = ""
convert n = let (rome, m) = subtrahend n
                in m ++ convert (n-rome)


-- BinarySearch
search :: (Ord a) => a -> [a] -> Bool
search a [] = False
search a xs | m < a = search a behind
            | m > a = search a front
            | otherwise = True
            where (front,m:behind) = splitAt (length xs `div` 2) xs

-- Sorts
insert :: Ord a => a -> [a] -> [a]
insert x [] = [x]
insert x (y:ys) | x < y = x:y:ys
                | otherwise = y:insert x ys

insertionSort :: Ord a => [a] -> [a]
insertionSort []     = []
insertionSort (x:xs) = insert x (insertionSort xs)

swaps :: Ord a => [a] -> [a]
swaps [] = []
swaps [x] = [x]
swaps (x1:x2:xs)
  | x1 > x2 = x2 : swaps (x1 : xs)
  | otherwise = x1 : swaps (x2 : xs)


main :: IO ()
main = do
  putStr "Fuck your mom"
  name <- getLine
  putStrLn $ "Hello " ++ name

