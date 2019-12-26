#!/bin/bash
#
# Simple script to run all the tests that we find

TOPDIR=`dirname $0`
cd $TOPDIR

# Only run for the given build directories
BUILDER="gcc_make"
for D in build/*_${BUILDER}
do
	echo "# $D"
	echo
	for F in $D/src/*.bin
	do
		date
		echo "[$F]"
		$F &> /dev/null
		echo
	done
	echo
done
