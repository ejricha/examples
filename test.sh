#!/bin/bash
#
# Simple script to run all the tests that we find

#BUILDER="ninja"
BUILDER="make"
for D in build_${BUILDER}*
do
	echo "# $D"
	echo
	for F in $D/ranges/*.bin
	do
		date
		echo "[$F]"
		$F
		echo
	done
	echo
done
