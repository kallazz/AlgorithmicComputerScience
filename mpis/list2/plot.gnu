# Scatter Plot Script

# Set output file format and name
set terminal pngcairo

# Set axis labels
set xlabel 'Number of bins(n)'
set ylabel 'Number of balls'

set grid
set key at graph 0.30, 0.95

max_x = system("awk '{if($1>x) x=$1} END {print x}' values.txt")
padding = 0.05 * max_x
set xrange [0:(max_x + padding)]

# B_n
set title 'B_n plot'
set output './plots/B_plot.png'

plot 'values.txt' using 1:2 title 'values' with points pointtype 7 pointsize 0.5 lc rgb "blue", \
    'means.txt' using 1:2 title 'means' with points pointtype 7 pointsize 1 lc rgb "red"

# U_n
set title 'U_n plot'
set output './plots/U_plot.png'

plot 'values.txt' using 1:3 title 'values' with points pointtype 7 pointsize 0.5 lc rgb "blue", \
    'means.txt' using 1:3 title 'means' with points pointtype 7 pointsize 1 lc rgb "red"

# C_n
set title 'C_n plot'
set output './plots/C_plot.png'

plot 'values.txt' using 1:4 title 'values' with points pointtype 7 pointsize 0.5 lc rgb "blue", \
    'means.txt' using 1:4 title 'means' with points pointtype 7 pointsize 1 lc rgb "red"

# D_n
set title 'D_n plot'
set output './plots/D_plot.png'

plot 'values.txt' using 1:5 title 'values' with points pointtype 7 pointsize 0.5 lc rgb "blue", \
    'means.txt' using 1:5 title 'means' with points pointtype 7 pointsize 1 lc rgb "red"

# D_n - C_n
set title 'D_n - C_n plot'
set output './plots/DC_plot.png'

plot 'values.txt' using 1:6 title 'values' with points pointtype 7 pointsize 0.5 lc rgb "blue", \
    'means.txt' using 1:6 title 'means' with points pointtype 7 pointsize 1 lc rgb "red"