-- ghci -> :l main.hs

import Data.List

intSquareRoot :: Int -> Int
intSquareRoot n = floor (sqrt (fromIntegral n))

-- 1.
binomial :: Int -> Int -> Int -- faster than the second version
binomial n k
  | n < 0 || k < 0 || k > n = -1
  | k == 0 || n == k = 1
  | otherwise = binomial (n - 1) k + binomial (n - 1) (k - 1)

-- 2.
pascalsTriangleRow :: Int -> [Int]
pascalsTriangleRow 0 = [1]
pascalsTriangleRow n = zipWith (+) (0 : pascalsTriangleRow (n - 1)) (pascalsTriangleRow (n - 1) ++ [0])

binomial2 :: Int -> Int -> Int
binomial2 n k
  | n < 0 || k < 0 || k > n = -1
  | otherwise = pascalsTriangleRow n !! k

-- 3.
merge :: (Ord a) => [a] -> [a] -> [a]
merge xs [] = xs
merge [] ys = ys
merge (x : xs) (y : ys)
  | x <= y = x : merge xs (y : ys)
  | otherwise = y : merge ys (x : xs)

mergeSort :: (Ord a) => [a] -> [a]
mergeSort [] = []
mergeSort [x] = [x]
mergeSort xs = merge (mergeSort firstHalf) (mergeSort secondHalf)
  where
    halfListLength = length xs `div` 2
    firstHalf = take halfListLength xs
    secondHalf = drop halfListLength xs

-- 4.
gcdExtended :: Int -> Int -> (Int, Int, Int) -- returns (gcd, x, y)
gcdExtended 0 b = (b, 0, 1)
gcdExtended a b =
  let (g, x1, y1) = gcdExtended (b `mod` a) a
   in (g, y1 - (b `div` a) * x1, x1)

diophantine :: Int -> Int -> (Int, Int, Int)
diophantine a b =
  let (g, x, y) = gcdExtended (abs a) (abs b)
      x0 = if a >= 0 then x else -x
      y0 = if b >= 0 then y else -y
   in (x0, y0, g)

-- 5.
primeFactors :: Int -> [Int]
primeFactors n
  | n < 2 = []
  | null firstFactor = [n]
  | otherwise = firstFactor ++ primeFactors (n `div` head firstFactor)
  where
    firstFactor = take 1 [x | x <- [2 .. intSquareRoot n], n `mod` x == 0]

-- 6.
totient :: Int -> Int -- slower than the second version
totient n = 1 + length [x | x <- [2 .. n - 1], gcd n x == 1]

-- 7.
totient2 :: Int -> Int
totient2 n = floor (fromIntegral n * product [1 - (1 / fromIntegral p) | p <- nub (primeFactors n)])

-- 8.
isPrime :: Int -> Bool
isPrime n = n >= 2 && null [x | x <- [2 .. intSquareRoot n], n `mod` x == 0]

primes :: Int -> [Int]
primes n = [x | x <- [2 .. n], isPrime x]

-- For testing:
main = do
  putStr "n: "
  n <- readLn
  putStr "k: "
  k <- readLn
  let result = binomial n k
  putStrLn $ "The result is " ++ show result
