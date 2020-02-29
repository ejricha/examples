#!/bin/bash

# Logs go next to this script
TOPDIR=`dirname $0`

# Source the common functions
SCRIPTS="../../.external/scripts"
source $SCRIPTS/bash/common.sh

# Run for the following generators
declare -A GENERATOR
#GENERATOR[make]="Unix Makefiles"
GENERATOR[ninja]="Ninja"

# More variables
#CMAKE="/usr/local/bin/cmake" # CMake 3.17
CMAKE="/usr/bin/cmake" # CMake 3.16
LOG="$TOPDIR/log"
APPS="a1.bin a2.bin a3.bin"
DIRS="deps_full deps_less"
SEARCH="[[:digit:]]{4}-[[:digit:]]{2}-[[:digit:]]{2}_[[:digit:]]{6}"
KEEP_LOGS=0 # Set to 1 to preserve all .log files

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
		change_random_libs_and_apps
		build_random_libs_and_apps
		run_apps
		check_for_differences

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

# Change a random selection of header files
change_random_libs_and_apps()
{
	echo "change_random_libs_and_apps($DATE_TIME)"

	# Choose between 1 and 5 random files
	R=$(($RANDOM % 5 + 1))
	for F in `ls -1 include/*.hpp | sort -R | head -$R`
	do
		update_date_time $F
	done
}

# Update the date/time in the given file
update_date_time()
{
	# The argument is the file
	FILE=$1

	# Replace the string in the file
	RUN sed -Ei "s/$SEARCH/$DATE_TIME/" $FILE
}

# Build a random selection of libs and apps,
#  but the same for each in $DIRS
build_random_libs_and_apps()
{
	echo "build_random_libs_and_apps()"

	# Build in every directory
	for B in build_*
	do
		# Always build all targets
		RUN $CMAKE --build $B
	done
}

# Check for differences in the output files
check_for_differences() {
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

		# Remove the logs unless we are keeping them
		if [[ $KEEP_LOGS -eq 0 ]]
		then
			RUN rm -f $L/*.log
			RUN rmdir $L
		fi
	done
}

# Run all the applications
run_apps()
{
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
