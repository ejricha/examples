#!/bin/bash

# Binary to run
EXE="cyclic_dependencies/ExecutableApp/TestCycle"

# Source the common functions
SCRIPTS="../../.external/scripts"
source $SCRIPTS/bash/common.sh

# Try both static and shared libraries
for SHARED in OFF ON
do
	B="build_ninja_shared_${SHARED}"
	echo "[$B]"
	
	# Create and enter the build directory
	mkdir -p $B
	cd $B

	# Build and run the application
	RUN cmake -G"Unix Makefiles" -D"BUILD_SHARED_LIBS=${SHARED}" ..
	RUN make
	RUN $EXE

	# Produce graphs
	../$SCRIPTS/bash/graph_dependencies.sh

	cd -
	echo
	echo
done
