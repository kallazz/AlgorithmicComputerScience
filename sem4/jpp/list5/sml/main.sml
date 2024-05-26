(* sml -> use "main.sml"; *)

(* 1. *)
fun binomial(n: int, k: int) : int = (* slower than the second version *)
        if n < 0 orelse k < 0 orelse k > n
        then ~1
        else if k = 0 orelse n = k
            then 1
            else
                binomial(n - 1, k) + binomial (n - 1, k - 1)

(* 2. *)
fun pascalsTriangleRow (n: int) : int list =
        if n = 0
        then [1]
        else
            let
                val previousRow : int list = pascalsTriangleRow(n - 1)
                val rowWithZeroFront : int list = 0 :: previousRow
                val rowWithZeroBack : int list = previousRow @ [0]
            in
                ListPair.map op+ (rowWithZeroFront, rowWithZeroBack)
            end;

fun binomial2(n: int, k: int) : int =
        if n < 0 orelse k < 0 orelse k > n
        then ~1
        else
            List.nth(pascalsTriangleRow(n), k)

(* 3. *)

fun merge(xs, []) = xs
    | merge([], ys) = ys
    | merge(x::xs, y::ys) =
        if x <= y
        then x :: merge(xs, y::ys)
        else
            y :: merge(x::xs, ys)

fun mergeSort([]) = []
    | mergeSort([x]) = [x]
    | mergeSort(xs) =
        let
            val halfListLength = length(xs) div 2
            val firstHalf = List.take(xs, halfListLength)
            val secondHalf = List.drop(xs, halfListLength)
        in
            merge(mergeSort(firstHalf), mergeSort(secondHalf))
        end;

(* 4. *)
fun gcdExtended(0, b) = (b, 0, 1) (* returns (gcd, x, y) *)
    |   gcdExtended(a, b) =
        let
            val (g, x1, y1) = gcdExtended (b mod a, a)
        in
            (g, y1 - (b div a) * x1, x1)
        end;

fun diophantine(a: int, b: int) : (int * int * int) =
        let
            val (g, x, y) = gcdExtended (abs(a), abs(b))
            val x0 = if a >= 0 then x else ~x
            val y0 = if a >= 0 then y else ~y
        in
            (x0, y0, g)
        end;

(* 5. *)
fun smallestFactor(n: int, d: int) : int =
        if d * d > n then n
        else if n mod d = 0 then d
            else smallestFactor(n, d + 1)

fun primeFactors(n : int) : int list =
        if n < 2
        then []
        else
            let
                val factor = smallestFactor(n, 2)
            in
                factor :: primeFactors (n div factor)
            end;

(* 6. *)
fun gcd(a, 0) = a
    | gcd(a, b) = gcd(b, a mod b)

fun totient(n: int) : int = (* slower than the second version *)
        let
            fun countCoPrimes(0, counter) = counter
                | countCoPrimes(i, counter) =
                    if gcd(n, i) = 1 then countCoPrimes(i - 1, counter + 1)
                    else countCoPrimes(i - 1, counter)
        in
            countCoPrimes(n, 0)
        end;

(* 7. *)
fun removeDuplicates([]) = []
    |   removeDuplicates(x::xs) = x :: removeDuplicates(List.filter (fn y => y <> x) xs)

fun product([]) = 1.0
    |   product(x::xs) = x * product(xs)

fun totient2(n: int) : int =
        let
            val factors = List.map Real.fromInt (removeDuplicates (primeFactors n))
        in
            floor ((Real.fromInt n) * (product (map (fn p => (1.0 - (1.0 / p))) factors)))
        end;

(* 8. *)
fun intSqrt(n: int) : int =
        floor (Math.sqrt (Real.fromInt n))

fun isDivisible(n: int, currentDivisor: int) : bool =
        if currentDivisor > (intSqrt n)
        then false
        else if n mod currentDivisor = 0
            then true orelse isDivisible(n, currentDivisor + 1)
            else
                false orelse isDivisible(n, currentDivisor + 1)

fun isPrime(n: int) : bool =
        n >= 2 andalso not(isDivisible(n, 2))

fun primesHelper(n: int, i: int) : int list  =
        if n <= 1
        then []
        else if isPrime i
            then i :: primesHelper(n - 1, i + 1)
            else primesHelper(n - 1, i + 1)

fun primes(n: int) : int list =
        primesHelper(n, 2)
