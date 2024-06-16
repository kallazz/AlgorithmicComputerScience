set terminal pngcairo

# MST Generation Time
set title "MST Generation Time Comparison"
set xlabel "Graph Size(n)"
set ylabel "Duration in nanoseconds"
set output './durations.png'

set datafile separator " "
plot "durations.txt" using 1:2 with lines title "Kruskal's Algorithm", \
     "durations.txt" using 1:3 with lines title "Prim's Algorithm"

# MST Signal Propagation Rounds
set title "MST Signal Propagation Rounds"
set xlabel "Graph Size(n)"
set ylabel "Rounds"
set output './rounds.png'

set datafile separator " "
plot "rounds.txt" using 1:2 with lines title "Average", \
     "rounds.txt" using 1:3 with lines title "Min", \
     "rounds.txt" using 1:4 with lines title "Max"