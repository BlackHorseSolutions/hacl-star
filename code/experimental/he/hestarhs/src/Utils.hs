-- | General-purpose utility functions.

module Utils where

import Universum

import qualified Data.Time.Clock.POSIX as P


findM :: Monad m => (a -> m Bool) -> [a] -> m (Maybe a)
findM _ []     = return Nothing
findM p (x:xs) = ifM (p x) (return $ Just x) (findM p xs)

measureTimeSingle :: Text -> IO a -> IO a
measureTimeSingle label action = do
    time0 <- P.getPOSIXTime
    r <- action
    time1 <- P.getPOSIXTime
    putTextLn $ label <> " took : " <> show (round ((time1-time0) * 1000) :: Integer) <> "ms"
    pure r

simdadd :: Num a => [a] -> [a] -> [a]
simdadd x y = map (uncurry (+)) (zip x y)

simdmul :: Num a => [a] -> [a] -> [a]
simdmul x y = map (uncurry (*)) (zip x y)

dotprod :: [Integer] -> [Integer] -> Integer
dotprod x y = sum $ simdmul x y