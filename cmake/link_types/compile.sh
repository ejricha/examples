#!/bin/bash

# Logs go next to this script
TOPDIR=`dirname $0`

# Source the common functions
SCRIPTS="../../.external/scripts"
source $SCRIPTS/bash/common.sh

# Run for the following generators
declare -A GENERATOR
GENERATOR[ninja]="Ninja"

# More variables
CMAKE="cmake"

# The main function
main()
{
	# Create the build directories,
	#  and run the initial CMake
	clean_cmake
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

		# Build only the TestLink target
		RUN $CMAKE --build . --target TestLink

		cd -
		echo
	done
}

# Call the main function
main "$@"
