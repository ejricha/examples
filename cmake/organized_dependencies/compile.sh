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
APPS="A1.bin A2.bin A3.bin"
DIRS="DepsFull DepsLess"
SEARCH="[[:digit:]]{4}-[[:digit:]]{2}-[[:digit:]]{2}_[[:digit:]]{6}"

# Debugging flags
KEEP_LOGS=0   # Preserve all .log files
FORCE_ERROR=0 # Produce an error sometimes

# The main function
main()
{
	# Create the build directories,
	#  and run the initial CMake
	clean_cmake

	# Loop 1000 times or until we encounter an error
	for N in `seq 1 1000`
	do
		DATE_TIME=`date +"%Y-%m-%d_%H%M%S"`
		echo "[$DATE_TIME] (Run #$N)"

		change_random_libs_and_apps
		build_random_libs_and_apps
		run_and_compare_apps

		# Sleep for at least a second
		sleep 1
		echo
	done

	echo "Successfully completed $N runs"
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

		# Generate the CMake files, and compile all targets
		RUN $CMAKE -G"$S" ..
		RUN $CMAKE --build .

		# Produce graphs in the build dir
		RUN ../$SCRIPTS/bash/graph_dependencies.sh

		cd -
	done
	echo
}

# Change a random selection of header files
change_random_libs_and_apps()
{
	echo "change_random_libs_and_apps()"

	# Choose between 1 and 5 random files
	R=$(($RANDOM % 5 + 1))
	for F in `ls -1 include/ | sort -R | head -$R`
	do
		echo "  $F"
		update_date_time include/$F
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
		# Choose between 1 and 5 random files
		R=$(($RANDOM % 5 + 1))
		for F in `ls -1 include/ | sort -R | head -$R`
		do
			# Get the basename of the target by
			#  stripping off .hpp and making uppercase
			T1=${F%%.hpp}
			T=${T1^^}
			echo "  $T"
			for D in $DIRS
			do
				# If we are intentionally erroring, skip 5% of builds
				if [[ $FORCE_ERROR -eq 1 && $(($RANDOM % 100)) -lt 5 ]]
				then
					continue
				fi

				# Actually build the specified target
				RUN $CMAKE --build $B --target $D$T
			done
		done
	done
}

# Run all the applications, and compare the output files
run_and_compare_apps()
{
	echo "run_and_compare_apps()"

	# Run for all generators
	for B in build_*
	do
		# Ensure that the log directory exists
		L=$LOG/$B/$DATE_TIME
		mkdir -p $L

		# Make sure every app produced identical results
		#  for both types of dependency builds
		for A in $APPS
		do
			for D in $DIRS
			do
				# Capture the output of the application
				APP=${D}${A}
				$B/$APP > $L/$APP.log
			done
			
			# If the files differed at all, show the diff and exit
			check_diff $L $A
		done

		# Remove the logs unless we are keeping them
		if [[ $KEEP_LOGS -eq 0 ]]
		then
			RUN rm -f $L/*.log
			RUN rmdir $L
		fi
	done
	echo "  (no differences)"
}

# If the files had any differences, show them and exit
check_diff() {
	L=$1
	A=$2

	# First, create the diff file
	DIFF=$L/${A}.diff
	diff -u $L/*$A.log > $DIFF

	# On a non-zero return code, show the diff and exit
	RET=$?
	if [[ $RET -ne 0 ]]
	then
		echo "ERROR: $L had differences for $A:"
		cat $DIFF
		exit $RET
	fi

	# Otherwise, clean up the diff file
	RUN rm -f $DIFF
}

# Call the main function
main "$@"
