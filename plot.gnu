#!/usr/bin/gnuplot
# results.gnu
#
# Print the results of all the *.dat files

# Titles
set title "Comparison of range libraries"
set xlabel "Number of elements"
set ylabel "Time taken"

# Set slightly different line formats for each file
set style line 1 linewidth 5
set style line 2 linewidth 4
set style line 3 linewidth 3
set style line 4 linewidth 2

# Use log scaling (default to log10)
set logscale xy

# Output to .png file
set terminal png
set output "results.png"

# Actually plot the data
plot \
        "results_NONE.dat" with linespoints linestyle 1 title "No ranges", \
        "results_V3.dat" with linespoints linestyle 2 title "Range-v3", \
        "results_CMCSTL2.dat" with linespoints linestyle 3 title "CMCSTL2", \
        "results_NANO.dat" with linespoints linestyle 4 title "NanoRange"
