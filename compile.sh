#!/bin/bash

# Loop through a variety of toolchain files,
#  using both make and ninja

TOPDIR=`dirname $0`

# Different options for make and ninja
declare -A BUILDER
BUILDER[make]="Unix Makefiles"
BUILDER[ninja]="Ninja"
declare -A OPTIONS
OPTIONS[make]="-j4 -s -S"
OPTIONS[ninja]="-j4"

# Build with the following options for ranges
#RANGES="NONE EXPERIMENTAL NIEBLER CMCSTL2 NANO"
#RANGES="NIEBLER"
RANGES="NONE NIEBLER"

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

	# For all the range types
	for R in $RANGES
	do
		D=$TOPDIR/build_${B}_ranges_${R}
		echo "# $D"

		# Only run cmake if the directory didn't exist
		if [[ ! -d $D ]]
		then	
			mkdir -p $D
			cd $D
			RUN cmake .. -G"$S" -D RANGES="$R"
		else
			cd $D
		fi

		# Compile
		RUN $B $O

		cd -
		echo
	done
	echo
done
