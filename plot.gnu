#!/usr/bin/gnuplot
# results.gnu
#
# Print the results of all the *.dat files

# Titles
set title "Comparison of range libraries"
set xlabel "Number of elements"
set ylabel "Time taken"

# Set slightly different line formats for each file
set style line 1 lc rgb '#ff0000' lt 7 lw 2 ps 1.0
set style line 2 lc rgb '#008800' lt 6 lw 2 pi -1 ps 1.5
set style line 3 lc rgb '#880088' lt 9 lw 2 pi -1 ps 1.2
set style line 4 lc rgb '#0000ff' lt 1 lw 2 pi -1 ps 1.0

# Use log scaling (default to log10)
set logscale xy

# Rotate X labels and get rid of the small striped at the top (nomirror)
set xtics nomirror rotate by -45

# Show human-readable Y-axis. E.g. "100 k" instead of 100000.
set format y '%.0s %cs'
set format x '%.0s %c'

# Put the legend in the upper-left corner
set key left top

# Output to .png file
set terminal pngcairo nocrop enhanced font "verdana,12"
set output "results.png"

# Actually plot the data
plot \
        "results_NONE.dat" with linespoints linestyle 1 title "No ranges", \
        "results_V3.dat" with linespoints linestyle 2 title "Range-v3", \
        "results_CMCSTL2.dat" with linespoints linestyle 3 title "CMCSTL2", \
        "results_NANO.dat" with linespoints linestyle 4 title "NanoRange"
