set terminal pngcairo

# Comparisons
set title "Average Comparisons with 50 Repeats"
set xlabel "Array Size(n)"
set ylabel "Number of Comparisons"
set output './comparisons.png'

set datafile separator " "
plot "comparisons.txt" using 1:2 with lines title "Select", \
     "comparisons.txt" using 1:3 with lines title "RandomizedSelect"


# Swaps
set title "Average Swaps with 50 Repeats"
set xlabel "Array Size(n)"
set ylabel "Number of Swaps"
set output './swaps.png'

set datafile separator " "
plot "swaps.txt" using 1:2 with lines title "Select", \
     "swaps.txt" using 1:3 with lines title "RandomizedSelect"

# Comparisons over n
set title "(Average Comparisons / n) with 50 Repeats"
set xlabel "Array Size(n)"
set ylabel "Number of Comparisons"
set output './comparisonsOverN.png'

set datafile separator " "
plot "comparisonsOverN.txt" using 1:2 with lines title "Select", \
     "comparisonsOverN.txt" using 1:3 with lines title "RandomizedSelect"


# Swaps over n
set title "(Average Swaps / n) with 50 Repeats"
set xlabel "Array Size(n)"
set ylabel "Number of Swaps"
set output './swapsOverN.png'

set datafile separator " "
plot "swapsOverN.txt" using 1:2 with lines title "Select", \
     "swapsOverN.txt" using 1:3 with lines title "RandomizedSelect"


# Comparisons for different array sizes
set title "Average Comparisons with 50 Repeats"
set xlabel "Array Size(n)"
set ylabel "Number of Comparisons"
set output './arraySizesComparisons.png'

set datafile separator " "
plot "arraySizesComparisons.txt" using 1:2 with lines title "Select with 3-element arrays", \
     "arraySizesComparisons.txt" using 1:3 with lines title "Select with 5-element arrays", \
     "arraySizesComparisons.txt" using 1:4 with lines title "Select with 7-element arrays", \
     "arraySizesComparisons.txt" using 1:5 with lines title "Select with 9-element arrays"

# Swaps for different array sizes
set title "Average Swaps with 50 Repeats"
set xlabel "Array Size(n)"
set ylabel "Number of Swaps"
set output './arraySizesSwaps.png'

set datafile separator " "
plot "arraySizesSwaps.txt" using 1:2 with lines title "Select with 3-element arrays", \
     "arraySizesSwaps.txt" using 1:3 with lines title "Select with 5-element arrays", \
     "arraySizesSwaps.txt" using 1:4 with lines title "Select with 7-element arrays", \
     "arraySizesSwaps.txt" using 1:5 with lines title "Select with 9-element arrays"

# Durations for different array sizes
set title "Average Durations with 50 Repeats"
set xlabel "Array Size(n)"
set ylabel "Duration in nanoseconds"
set output './arraySizesDurations.png'

set datafile separator " "
plot "arraySizesDurations.txt" using 1:2 with lines title "Select with 3-element arrays", \
     "arraySizesDurations.txt" using 1:3 with lines title "Select with 5-element arrays", \
     "arraySizesDurations.txt" using 1:4 with lines title "Select with 7-element arrays", \
     "arraySizesDurations.txt" using 1:5 with lines title "Select with 9-element arrays"

# Comparisons for binary search
set title "Average Comparisons with 50 Repeats for Binary Search"
set xlabel "Array Size(n)"
set ylabel "Number of Comparisons"
set key bottom right
set output './binarySearchComparisons.png'

set datafile separator " "
plot "binarySearchComparisons.txt" using 1:2 with lines title "Left element", \
     "binarySearchComparisons.txt" using 1:3 with lines title "Middle element", \
     "binarySearchComparisons.txt" using 1:4 with lines title "Right element", \
     "binarySearchComparisons.txt" using 1:5 with lines title "Out of array element", \
     "binarySearchComparisons.txt" using 1:6 with lines title "Random Element", \
     "binarySearchComparisons.txt" using 1:7 with lines title "Master Theorem Approximation"

# Durations for binary search
set title "Average Durations with 50 Repeats for Binary Search"
set xlabel "Array Size(n)"
set ylabel "Duration in nanoseconds"
set key bottom right
set output './binarySearchDurations.png'

set datafile separator " "
plot "binarySearchDurations.txt" using 1:2 with lines title "Left element", \
     "binarySearchDurations.txt" using 1:3 with lines title "Middle element", \
     "binarySearchDurations.txt" using 1:4 with lines title "Right element", \
     "binarySearchDurations.txt" using 1:5 with lines title "Out of array element", \
     "binarySearchDurations.txt" using 1:6 with lines title "Random Element"