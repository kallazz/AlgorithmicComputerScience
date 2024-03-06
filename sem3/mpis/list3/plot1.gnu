set terminal pngcairo
set output 'scatter_plots.png'

set style data points
set xlabel 'Number of bins and balls(n)'
set ylabel 'Max number of balls in a bin'
set grid

max_x = system("awk '{if($1>x) x=$1} END {print x}' values.txt")
padding = 0.05 * max_x
set xrange [0:(max_x + padding)]

# Ln_1
set yrange [0:15]
set title 'L_n1 plot'
set output './plots/L1_plot.png'

plot 'values.txt' using 1:2 title 'values' with points pointtype 7 pointsize 0.5 lc rgb "blue" , \
    'means.txt' using 1:2 title 'means' with points pointtype 7 pointsize 1 lc rgb "red"

# Ln_2
set yrange [0:10]
set title 'L_n2 plot'
set output './plots/L2_plot.png'

plot 'values.txt' using 1:3 title 'values' with points pointtype 7 pointsize 0.5 lc rgb "blue" , \
    'means.txt' using 1:3 title 'means' with points pointtype 7 pointsize 1 lc rgb "red" 


# Ln_1 / f1(n)
set yrange [1:2]
set title 'l_n1 / f_1 plot'
set output './plots/l1_over_f1_plot.png'

plot 'means.txt' using 1:($2 / (log($1) / log(log($1)))) notitle with points pointtype 7 pointsize 1 lc rgb "red"

# Ln_2 / f2(n)
set yrange [0:2]
set title 'l_n2 / f_2 plot'
set output './plots/l2_over_f2_plot.png'

plot 'means.txt' using 1:($3 / (log(log($1)) / log(2))) notitle with points pointtype 7 pointsize 1 lc rgb "red" 
