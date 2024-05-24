-- 1.
binomial :: Int -> Int -> Int
binomial n 0 = 1
binomial n k
    | n < 0 || k < 0 || k > n = -1
    | n == k = 1
    | otherwise = binomial (n - 1) k + binomial (n - 1) (k - 1)

-- 2.
pascalsTriangleRow :: Int -> [Int]
pascalsTriangleRow 0 = [1]
pascalsTriangleRow n = [binomial n x | x <- [0..n]]

binomial2 :: Int -> Int -> Int
binomial2 n k = pascalsTriangleRow n !! k

-- 3.
merge :: Ord a => [a] -> [a] -> [a]
merge xs [] = xs
merge [] ys = ys
merge (x:xs) (y:ys)
    | x <= y = x : merge xs (y:ys)
    | otherwise = y : merge ys (x:xs)

mergeSort :: Ord a => [a] -> [a]
mergeSort [] = []
mergeSort [x] = [x]
mergeSort xs = merge (mergeSort firstHalf) (mergeSort secondHalf)
    where halfListLength = length xs `div` 2
          firstHalf = take halfListLength xs
          secondHalf = drop halfListLength xs

-- 4.

-- 5.

primeFactors :: Int -> [Int]
primeFactors n
    | n < 2 = []
    | null firstFactor = [n]
    | otherwise = firstFactor ++ primeFactors (n `div` head firstFactor)
        where firstFactor = take 1 [x | x <- [1..squareOfN], n `mod` x == 0, isPrime x]
              squareOfN = floor (sqrt (fromIntegral n))


isPrime :: Int -> Bool
isPrime n = n >= 2 && null [x | x <- [2..squareOfN], n `mod` x == 0]
    where squareOfN = floor (sqrt (fromIntegral n))

main = do
    putStrLn "Hello, World!"
