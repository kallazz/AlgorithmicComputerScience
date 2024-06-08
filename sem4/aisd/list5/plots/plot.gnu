set terminal pngcairo

# Comparisons
set title "MST Generation Time Comparison"
set xlabel "Graph Size(n)"
set ylabel "Duration in nanoseconds"
set output './durations.png'

set datafile separator " "
plot "durations.txt" using 1:2 with lines title "Kruskal's Algorithm", \
     "durations.txt" using 1:3 with lines title "Prim's Algorithm"