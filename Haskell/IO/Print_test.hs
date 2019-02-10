import System.Environment

main :: IO ()
main = do
    args <- getArgs
    let linesToRead = if length args > 0
                      then read (head args)
                      else 0 :: Int
    print linesToRead