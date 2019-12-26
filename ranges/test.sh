#!/bin/bash
#
# Simple script to run all the tests that we find

TOPDIR=`dirname $0`

BUILDER="gcc_make"
#BUILDER="gcc_ninja"
#BUILDER="clang_make"
#BUILDER="clang_ninja"
for D in $TOPDIR/build/*_${BUILDER}
do
	echo "# $D"
	echo
	for F in $D/src/*.bin
	do
		date
		echo "[$F]"

		# Run the binary
		$F &> /dev/null

		# Move the results file
		mv results*.dat results/

		echo
	done
	echo
done
