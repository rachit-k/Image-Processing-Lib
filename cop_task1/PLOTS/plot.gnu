set style data boxplot
set xlabel "Implementation"
set ylabel "Time"
set xtics('openBLAS' 1, 'pthread' 2, 'MKL' 3 , 'Manual' 4)
set style fill solid 0.5 border -1
set style boxplot outliers pointtype 8
set style data boxplot
set title 'input size x kernel size' font 'Arial,13';
set output 'time.png'
plot for [i=1:4] 'out512-9.dat' using (i):i notitle
