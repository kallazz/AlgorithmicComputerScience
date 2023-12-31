set terminal pngcairo
set output 'scatter_plots.png'

set style data points
set xlabel 'Array size(n)'
set grid

max_x = system("awk '{if($1>x) x=$1} END {print x}' means2.txt")
padding = 0.05 * max_x
set xrange [0:(max_x + padding)]

# cmp(n)
set title 'cmp(n) and single values plot'
set ylabel 'Comparisons'
set output './plots/cmp_plot.png'

plot 'values2.txt' using 1:2 title 'values' with points pointtype 7 pointsize 0.5 lc rgb "blue" , \
    'means2.txt' using 1:2 title 'means' with points pointtype 7 pointsize 1 lc rgb "red"

# s(n)
set title 's(n) and single values plot'
set ylabel 'Shifts'
set output './plots/s_plot.png'

plot 'values2.txt' using 1:3 title 'values' with points pointtype 7 pointsize 0.5 lc rgb "blue" , \
    'means2.txt' using 1:3 title 'means' with points pointtype 7 pointsize 1 lc rgb "red"

# cmp(n) / n
set yrange [0:3000]
set title 'cmp(n) / n plot'
set ylabel 'Comparisons'
set output './plots/cmp_over_n_plot.png'

plot 'means2.txt' using 1:($2/$1) notitle with points pointtype 7 pointsize 1 lc rgb "red"

# s(n) / n
set title 's(n) / n plot'
set ylabel 'Shifts'
set output './plots/s_over_n_plot.png'

plot 'means2.txt' using 1:($3/$1) notitle with points pointtype 7 pointsize 1 lc rgb "red"

# cmp(n) / (n^2)
set yrange [0.2:0.3]
set title 'cmp(n) / (n^2) plot'
set ylabel 'Comparisons'
set output './plots/cmp_over_n_squared_plot.png'

plot 'means2.txt' using 1:($2/($1 * $1)) notitle with points pointtype 7 pointsize 1 lc rgb "red"

# s(n) / (n^2)
set title 's(n) / (n^2) plot'
set ylabel 'Shifts'
set output './plots/s_over_n_squared_plot.png'

plot 'means2.txt' using 1:($3/($1 * $1)) notitle with points pointtype 7 pointsize 1 lc rgb "red"
