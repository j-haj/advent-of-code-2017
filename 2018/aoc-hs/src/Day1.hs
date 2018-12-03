module Day1 where

applyFrequencyChanges :: [Int] -> Int
applyFrequencyChanges xs = foldr (+) xs 0
