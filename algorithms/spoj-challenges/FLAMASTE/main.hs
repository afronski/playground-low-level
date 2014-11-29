import Data.List
import Text.Printf
import Control.Monad

encodeRLE :: String -> [ (Int, Char) ]
encodeRLE = map (\xs -> (length xs, head xs)) . groupBy (==)

convert :: (Int, Char) -> String
convert (amount, char)
  | amount > 2 = printf "%c%d" char amount
  | otherwise  = replicate amount char

stringify :: [ (Int, Char) ] -> String
stringify listOfPairs = concat $ map convert listOfPairs

main = do
  n <- getLine
  inputs <- replicateM (read n) getLine
  results <- return (map (stringify . encodeRLE) inputs)
  mapM_ (putStrLn . id) results