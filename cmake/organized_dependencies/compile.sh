#!/bin/bash

# Logs go next to this script
TOPDIR=`dirname $0`

# Source the common functions
SCRIPTS="../../.external/scripts"
source $SCRIPTS/bash/common.sh

# Run for the following generators
declare -A GENERATOR
GENERATOR[make]="Unix Makefiles"
GENERATOR[ninja]="Ninja"

# More variables
#CMAKE="/usr/local/bin/cmake" # CMake 3.17
CMAKE="/usr/bin/cmake" # CMake 3.16
LOG="$TOPDIR/log"
APPS="a1.bin a2.bin a3.bin"
DIRS="deps_full deps_less"

# The main function
main()
{
	# Create the build directories,
	#  and run the initial CMake
	clean_cmake

	# Loop until we encounter an error
	while true
	do
		DATE_TIME=`date +"%Y-%m-%d_%H%M%S"`
		change_random_libs_and_apps $DATE_TIME
		build_random_libs_and_apps
		run_apps $DATE_TIME
		check_for_differences $DATE_TIME

		# Sleep for at least a second
		sleep 1
		echo
	done
}

# Run initial cmake
clean_cmake()
{
	echo "clean_cmake()"

	# For all the generators
	for G in ${!GENERATOR[@]}
	do
		S=${GENERATOR[$G]}
		B="build_${G}"
		echo "[$B via $S]"
	
		# Create and enter the build directory
		mkdir -p $B
		cd $B

		# Generate the CMake files
		RUN $CMAKE -G"$S" ..
	
		# Produce graphs in the build dir
		RUN ../$SCRIPTS/bash/graph_dependencies.sh

		cd -
	done
	echo
}

# Change some random number of libraries/applications
change_random_libs_and_apps()
{
	# The argument is the date/time
	DATE_TIME=$1
	echo "change_random_libs_and_apps($DATE_TIME)"

	# TODO: use sed to change date/time in header files
}

# Build a random selection of libs and apps,
#  but the same for each in $DIRS
build_random_libs_and_apps()
{
	echo "build_random_libs_and_apps()"

	# TODO: don't just build all
	for B in build_*
	do
		echo "RUN $CMAKE --build $B"
		RUN $CMAKE --build $B
	done
}

# Check for differences in the output files
check_for_differences() {
	# The argument is the date/time
	DATE_TIME=$1
	echo "check_for_differences($DATE_TIME)"

	# Run for all generators
	for B in build_*
	do
		# Use the following log file
		L=$LOG/$B/$DATE_TIME
		
		# Make sure every app produced identical results
		#  for both types of depedency builds
		for A in $APPS
		do
			# If we had any diff, exit
			RUN diff -u $L/*_${A}.log > $L/${A}.diff

			# Otherwise, clean up
			RUN rm -f $L/${A}.diff
		done
	done
}

# Run all the applications
run_apps()
{
	# The argument is the date/time
	DATE_TIME=$1
	echo "run_apps($DATE_TIME)"

	# Run for all generators
	for B in build_*
	do
		# Ensure that the log directory exists
		L=$LOG/$B/$DATE_TIME
		mkdir -p $L
		
		# Make sure every app produced identical results
		#  for both types of depedency builds
		for A in $APPS
		do
			for D in $DIRS
			do
				# Capture the output of the application
				APP=${D}_${A}
				$B/$APP > $L/$APP.log
			done
		done
	done
}

# Call the main function
main "$@"
