#!/bin/bash
#
# Simple script to run all the tests that we find

for D in build/*
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
