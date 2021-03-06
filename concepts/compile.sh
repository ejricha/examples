#!/bin/bash

# Loop through a variety of toolchain files,
#  using both make and ninja

TOPDIR=`dirname $0`
TOOLSDIR="../../../.external/scripts/cmake"

BUILD="Release"

# Different options for make and ninja
declare -A BUILDER
#BUILDER[make]="Unix Makefiles"
BUILDER[ninja]="Ninja"
OPTIONS="-j4"

# Only g++ supports -fconcepts that we eed
COMPILERS="gcc"

# Function to run, and exit on failure
RUN() {
	# Run the commands
	"${@}"

	# Check the return code
	RET=$?
	if [[ $RET -ne 0 ]]
	then
		echo "Command [${@}] returned code ($RET)"
		exit $RET
	fi
}

# Update all the external dependencies
$TOPDIR/../fetch_external_libraries.sh

# For all the builder types
HEADER=""
for B in ${!BUILDER[@]}
do
	S=${BUILDER[$B]}

	# For the specified compilers
	for C in $COMPILERS
	do
		HEADER+="\t${C}_${B}"
		TOOLCHAIN="$TOOLSDIR/Toolchain_$C.cmake"

		D=$TOPDIR/build/${C}_${B}
		echo "# $D"

		# Only run cmake if the directory didn't exist
		if [[ ! -d $D ]]
		then
			mkdir -p $D
			cd $D &>/dev/null
			RUN cmake ../.. -G"$S" -D CMAKE_BUILD_TYPE=$BUILD -D CMAKE_TOOLCHAIN_FILE=$TOOLCHAIN
		else
			cd $D &>/dev/null
		fi

		# Only failing the VALID target should exit this script
		CMD="cmake --build . $OPTIONS"
		TIME_START=`date +%s.%N`
		if [[ $P == VALID ]]
		then
			$CMD
		else
			RUN $CMD
		fi
		TIME_END=`date +%s.%N`
		TIME_DIFF=`echo "$TIME_END - $TIME_START" | bc`
		TIMES[$S]+="\t$TIME_DIFF"
		echo

		cd - &>/dev/null
		echo
	done
	echo
done

# Save the compile times to file
mkdir -p $TOPDIR/results
F="$TOPDIR/results/compile_times.dat"
echo -e "Title\t$HEADER" > $F
for B in ${!BUILDER[@]}
do
	S=${BUILDER[$B]}
	echo -e "$C\t${TIMES[$S]}" >> $F
done
