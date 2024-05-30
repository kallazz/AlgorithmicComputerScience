set terminal pngcairo

# Comparisons
set title "Key Comparisons Ascending"
set xlabel "Input Size(n)"
set ylabel "Number of Comparisons"
set output './keyComparisonsAscending.png'

set datafile separator " "
plot "keyComparisonsAscending.txt" using 1:2 with lines title "BST", \
     "keyComparisonsAscending.txt" using 1:3 with lines linewidth 2 title "Red-Black BST"

# Comparisons
set title "Key Comparisons Random"
set xlabel "Input Size(n)"
set ylabel "Number of Comparisons"
set output './keyComparisons.png'

set datafile separator " "
plot "keyComparisons.txt" using 1:2 with lines title "BST", \
 "keyComparisons.txt" using 1:3 with lines title "Red-Black BST"


# Pointer operations
set title "Pointer Operations Ascending"
set xlabel "Input Size(n)"
set ylabel "Number of Pointer Operations"
set output './pointerOperationsAscending.png'

set datafile separator " "
plot "pointerOperationsAscending.txt" using 1:2 with lines title "BST", \
     "pointerOperationsAscending.txt" using 1:3 with lines linewidth 2 title "Red-Black BST"

set title "Pointer Operations Random"
set xlabel "Input Size(n)"
set ylabel "Number of Pointer Operations"
set output './pointerOperations.png'

set datafile separator " "
plot "pointerOperations.txt" using 1:2 with lines title "BST", \
     "pointerOperations.txt" using 1:3 with lines title "Red-Black BST"


# Heights
set title "Heights Ascending"
set xlabel "Input Size(n)"
set ylabel "Tree Heights"
set output './heightsAscending.png'

set datafile separator " "
plot "heightsAscending.txt" using 1:2 with lines title "BST", \
     "heightsAscending.txt" using 1:3 with lines linewidth 2 title "Red-Black BST"

set title "Heights Random"
set xlabel "Input Size(n)"
set ylabel "Tree Heights"
set output './heights.png'

set datafile separator " "
plot "heights.txt" using 1:2 with lines title "BST", \
     "heights.txt" using 1:3 with lines title "Red-Black BST"