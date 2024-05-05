set terminal pngcairo

# Comparisons
set title "Average Comparisons with 50 Repeats"
set xlabel "Array Size(n)"
set ylabel "Number of Comparisons(c)"
set output './comparisons.png'

set datafile separator " "
plot "comparisons.txt" using 1:2 with lines title "Select", \
     "comparisons.txt" using 1:3 with lines title "RandomizedSelect"


# Swaps
set title "Average Swaps with 50 Repeats"
set xlabel "Array Size(n)"
set ylabel "Number of Comparisons(c)"
set output './swaps.png'

set datafile separator " "
plot "swaps.txt" using 1:2 with lines title "Select", \
     "swaps.txt" using 1:3 with lines title "RandomizedSelect"

# Comparisons over n
set title "(Average Comparisons / n) with 50 Repeats"
set xlabel "Array Size(n)"
set ylabel "Number of Comparisons(c)"
set output './comparisonsOverN.png'

set datafile separator " "
plot "comparisonsOverN.txt" using 1:2 with lines title "Select", \
     "comparisonsOverN.txt" using 1:3 with lines title "RandomizedSelect"


# Swaps over n
set title "(Average Swaps / n) with 50 Repeats"
set xlabel "Array Size(n)"
set ylabel "Number of Comparisons(c)"
set output './swapsOverN.png'

set datafile separator " "
plot "swapsOverN.txt" using 1:2 with lines title "Select", \
     "swapsOverN.txt" using 1:3 with lines title "RandomizedSelect"
