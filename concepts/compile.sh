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
OPTIONS[make]="-j4 -s -S VERBOSE=1"
OPTIONS[ninja]="-j4"

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
for B in ${!BUILDER[@]}
do
	S=${BUILDER[$B]}
	O=${OPTIONS[$B]}

	D=$TOPDIR/build_${B}
	echo "# $D"

	# Only run cmake if the directory didn't exist
	if [[ ! -d $D ]]
	then	
		mkdir -p $D
		cd $D
		RUN cmake .. -G"$S" -D CMAKE_BUILD_TYPE=$BUILD -D RANGES="$R"
	else
		cd $D
	fi

	# Compile
	time RUN $B $O
	echo

	cd -
	echo
done
