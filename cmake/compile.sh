#!/bin/bash

# Binary to run
EXE="cyclic_dependencies/main/test_cycle"

# Try both static and shared libraries
for SHARED in OFF ON
do
	B="build_ninja_shared_${SHARED}"
	echo "[$B]"
	mkdir -p $B
	cd $B
	cmake -G"Unix Makefiles" -D"BUILD_SHARED_LIBS=${SHARED}" ..
	make
	$EXE

	cd -
	echo
	echo
done
