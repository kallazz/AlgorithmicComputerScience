# Scatter Plot Script

# Set output file format and name
set terminal pngcairo

# Set axis labels
set xlabel 'Number of bins(n)'
set ylabel 'Number of balls'

set grid
set key outside right
set key title 'Legend:'

max_x = system("awk '{if($1>x) x=$1} END {print x}' values.txt")
padding = 0.05 * max_x
set xrange [0:(max_x + padding)]

# Bn
set title 'Bn plot'
set output './plots/Bn_plot.png'

plot 'values.txt' using 1:2 title 'values' with points pointtype 7 pointsize 0.5 lc rgb "blue", \
    'means.txt' using 1:2 title 'means' with points pointtype 7 pointsize 1 lc rgb "red"

# Un
set title 'Un plot'
set output './plots/Un_plot.png'
set ylabel 'Number of empty bins'

plot 'values.txt' using 1:3 title 'values' with points pointtype 7 pointsize 0.5 lc rgb "blue", \
    'means.txt' using 1:3 title 'means' with points pointtype 7 pointsize 1 lc rgb "red"

set ylabel 'Number of balls'

# Cn
set title 'Cn plot'
set output './plots/Cn_plot.png'

plot 'values.txt' using 1:4 title 'values' with points pointtype 7 pointsize 0.5 lc rgb "blue", \
    'means.txt' using 1:4 title 'means' with points pointtype 7 pointsize 1 lc rgb "red"

# Dn
set title 'Dn plot'
set output './plots/Dn_plot.png'

plot 'values.txt' using 1:5 title 'values' with points pointtype 7 pointsize 0.5 lc rgb "blue", \
    'means.txt' using 1:5 title 'means' with points pointtype 7 pointsize 1 lc rgb "red"

# Dn - Cn
set title 'Dn - Cn plot'
set output './plots/DnCn_plot.png'

plot 'values.txt' using 1:6 title 'values' with points pointtype 7 pointsize 0.5 lc rgb "blue", \
    'means.txt' using 1:6 title 'means' with points pointtype 7 pointsize 1 lc rgb "red"


# ************************************************ a) ************************************************
# Bn / n
set title 'Bn / n plot'
set output './plots/Bn_over_n_plot.png'

plot 'values.txt' using 1:($2/$1) title 'values' with points pointtype 7 pointsize 0.5 lc rgb "blue", \
    'means.txt' using 1:($2/$1) title 'means' with points pointtype 7 pointsize 1 lc rgb "red"

# Bn / sqrt(n)
set title 'Bn / sqrt(n) plot'
set output './plots/Bn_over_sqrt_n_plot.png'

plot 'values.txt' using 1:($2/sqrt($1)) title 'values' with points pointtype 7 pointsize 0.5 lc rgb "blue", \
    'means.txt' using 1:($2/sqrt($1)) title 'means' with points pointtype 7 pointsize 1 lc rgb "red"

# ************************************************ b) ************************************************
# Un / n
set title 'Un / n plot'
set output './plots/Un_over_n_plot.png'
set ylabel 'Number of empty bins'

plot 'values.txt' using 1:($3/$1) title 'values' with points pointtype 7 pointsize 0.5 lc rgb "blue", \
    'means.txt' using 1:($3/$1) title 'means' with points pointtype 7 pointsize 1 lc rgb "red"

set ylabel 'Number of balls'

# ************************************************ c) ************************************************
# Cn / n
set title 'Cn / n plot'
set output './plots/Cn_over_n_plot.png'

plot 'values.txt' using 1:($4/$1) title 'values' with points pointtype 7 pointsize 0.5 lc rgb "blue", \
     'means.txt' using 1:($4/$1) title 'means' with points pointtype 7 pointsize 1 lc rgb "red"

# Cn / (n * log(n)) 
set title 'Cn / (n * log(n)) plot'
set output './plots/Cn_over_n_log_n_plot.png'

plot 'values.txt' using 1:($4/($1 * log($1))) title 'values' with points pointtype 7 pointsize 0.5 lc rgb "blue", \
     'means.txt' using 1:($4/($1 * log($1))) title 'means' with points pointtype 7 pointsize 1 lc rgb "red"

# Cn / n^2
set title 'Cn / n^2 plot'
set output './plots/Cn_over_n_squared.png'

plot 'values.txt' using 1:($4/($1 * $1)) title 'values' with points pointtype 7 pointsize 0.5 lc rgb "blue", \
    'means.txt' using 1:($4/($1 * $1)) title 'means' with points pointtype 7 pointsize 1 lc rgb "red"

# ************************************************ d) ************************************************
# Dn / n
set title 'Dn / n plot'
set output './plots/Dn_over_n_plot.png'

plot 'values.txt' using 1:($5/$1) title 'values' with points pointtype 7 pointsize 0.5 lc rgb "blue", \
    'means.txt' using 1:($5/$1) title 'means' with points pointtype 7 pointsize 1 lc rgb "red"

# Dn / (n * log(n)) 
set title 'Dn / (n * log(n)) plot'
set output './plots/Dn_over_n_log_n_plot.png'

plot 'values.txt' using 1:($5/($1 * log($1))) title 'values' with points pointtype 7 pointsize 0.5 lc rgb "blue", \
    'means.txt' using 1:($5/($1 * log($1))) title 'means' with points pointtype 7 pointsize 1 lc rgb "red"

# Dn / n^2
set title 'Dn / n^2 plot'
set output './plots/Dn_over_n_squared.png'

plot 'values.txt' using 1:($5/($1 * $1)) title 'values' with points pointtype 7 pointsize 0.5 lc rgb "blue", \
    'means.txt' using 1:($5/($1 * $1)) title 'means' with points pointtype 7 pointsize 1 lc rgb "red"

# ************************************************ e) ************************************************
# (Dn - Cn) / n
set title '(Dn - Cn) / n plot'
set output './plots/DnCn_over_n_plot.png'

plot 'values.txt' using 1:($6/$1) title 'values' with points pointtype 7 pointsize 0.5 lc rgb "blue", \
    'means.txt' using 1:($6/$1) title 'means' with points pointtype 7 pointsize 1 lc rgb "red"

# (Dn - Cn) / (n * log(n)) f
set title '(Dn - Cn) / (n * log(n)) plot'
set output './plots/DnCn_over_n_log_n_plot.png'

plot 'values.txt' using 1:($6/($1 * log($1))) title 'values' with points pointtype 7 pointsize 0.5 lc rgb "blue", \
    'means.txt' using 1:($6/($1 * log($1))) title 'means' with points pointtype 7 pointsize 1 lc rgb "red"

# (Dn - Cn) / (n * log(log(n)))
set title '(Dn - Cn) / (n * log(log(n))) plot'
set output './plots/DnCn_over_n_log_log_n_plot.png'

plot 'values.txt' using 1:($6/($1 * log(log($1)))) title 'values' with points pointtype 7 pointsize 0.5 lc rgb "blue", \
    'means.txt' using 1:($6/($1 * log(log($1)))) title 'means' with points pointtype 7 pointsize 1 lc rgb "red"
