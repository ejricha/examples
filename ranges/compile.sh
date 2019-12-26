#!/bin/bash

# Loop through a variety of toolchain files,
#  using both make and ninja

TOPDIR=`dirname $0`

BUILD="Release"

# Different options for make and ninja
declare -A BUILDER
BUILDER[make]="Unix Makefiles"
BUILDER[ninja]="Ninja"
declare -A OPTIONS
#OPTIONS[make]="-j4 -s -S VERBOSE=1"
OPTIONS[make]="-j4 -s -S"
OPTIONS[ninja]="-j4"

# Build with the following options for ranges
RANGES="NONE V3 NANO CMCSTL2"
declare -A TIMES

# Build with the following compilers
COMPILERS="gcc clang"

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

# For all the builder types
HEADER=""
for B in ${!BUILDER[@]}
do
	S=${BUILDER[$B]}
	O=${OPTIONS[$B]}

	# For the specified compilers
	for C in $COMPILERS
	do
		HEADER+="\t${C}_${B}"
		TOOLCHAIN="../../../cmake/Toolchain_$C.cmake"

		# For all the range types
		for R in $RANGES
		do
			D=$TOPDIR/build/${R}_${C}_${B}
			echo "# $D"

			# Skip CMCSTL2 for clang, it requires -fconcepts
			if [[ $C == "clang" && ( $R == "CMCSTL2" || $R == "NANO" ) ]]
			then
				TIMES[$R]+="\t0"
				echo
				continue
			fi

			# Only run cmake if the directory didn't exist
			if [[ ! -d $D ]]
			then
				mkdir -p $D
				cd $D &>/dev/null
				RUN cmake ../.. -G"$S" -D CMAKE_BUILD_TYPE=$BUILD -D CMAKE_TOOLCHAIN_FILE=$TOOLCHAIN -D RANGES="$R"
			else
				cd $D &>/dev/null
			fi

			# Compile
			TIME_START=`date +%s.%N`
			time RUN $B $O
			TIME_END=`date +%s.%N`
			TIME_DIFF=`echo "$TIME_END - $TIME_START" | bc`
			TIMES[$R]+="\t$TIME_DIFF"
			echo

			cd - &>/dev/null
			echo
		done
	done
	echo
done

# Save the compile times to file
F="$TOPDIR/results/compile_times.dat"
echo -e "Title\t$HEADER" > $F
for T in ${!TIMES[@]}
do
	echo -e "$T\t${TIMES[$T]}" >> $F
done
