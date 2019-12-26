#!/usr/bin/gnuplot
# results.gnu
#
# Print the results of all the *.dat files

# Titles
set xlabel "Number of elements"
set ylabel "Time taken"

# Set slightly different line formats for each file
set style line 1 lc rgb '#ff0000' lt 7 lw 2 ps 1.0
set style line 2 lc rgb '#008800' lt 6 lw 2 ps 1.5
set style line 3 lc rgb '#880088' lt 9 lw 2 ps 1.2
set style line 4 lc rgb '#0000ff' lt 1 lw 2 ps 1.0

# Use log scaling (default to log10)
set logscale xy
set yrange [0.000001:10]

# Rotate X labels and get rid of the small striped at the top (nomirror)
set xtics nomirror rotate by -45

# Show human-readable Y-axis. E.g. "100 k" instead of 100000.
set format y '%.0s %cs'
set format x '%.0s %c'

# Put the legend in the upper-left corner
set key left top

# Output to .png file
set terminal pngcairo nocrop enhanced font "verdana,12"
OPERATIONS = "Even EvenThenSquared DivisibleBy70 FastFilter"
do for [O in OPERATIONS] {
	newtitle = sprintf("Comparison of range libraries (%s)", O)
	set title newtitle
	fpng = sprintf("results_%s.png", O)
	print("File is [%s]", fpng)
	set output fpng

	i = 1
	array f[4]
	do for [R in "NONE V3 CMCSTL2 NANO"] {
		f[i] = sprintf("%s_%s.dat", R, O)
		i = i + 1
	}

	# Actually plot the data
	plot \
		f[1] with linespoints linestyle 1 title "No ranges", \
		f[2] with linespoints linestyle 2 title "Range-v3", \
		f[3] with linespoints linestyle 3 title "CMCSTL2", \
		f[4] with linespoints linestyle 4 title "NanoRange"
}

# Also plot the compile times
unset logscale xy
unset xlabel
unset yrange
fpng = "compile_times.png"
print("File is [%s]", fpng)
set output fpng
set title "Compile-time comparison of range libraries"
set auto x
set style data histogram
set style histogram cluster gap 1
set style fill solid border -1
set offsets 0, 0, 1, 0
set key fixed top center horizontal Right noreverse noenhanced autotitle
set boxwidth 1.0
set xtic scale 0
plot for [i=2:5] "compile_times.dat" using i:xtic(1) ti col
