#!/bin/bash
#
# Simple script to run all the tests that we find

BUILDER="gcc_make"
#BUILDER="gcc_ninja"
#BUILDER="clang_make"
#BUILDER="clang_ninja"
for D in build_*_${BUILDER}
do
	echo "# $D"
	echo
	for F in $D/src/*.bin
	do
		date
		echo "[$F]"
		$F
		echo
	done
	echo
done
