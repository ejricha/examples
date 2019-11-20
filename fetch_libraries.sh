#!/bin/bash
# fetch_libraries.sh
#
# Fetch all the available range libraries

TO="external"
RANGES_V3="https://github.com/ericniebler/range-v3.git"
RANGES_NANO="https://github.com/tcbrindle/NanoRange.git"
RANGES_CMCSTL2="https://github.com/CaseyCarter/cmcstl2.git"

RANGES_LIBS="$RANGES_V3 $RANGES_NANO $RANGES_CMCSTL2"

mkdir -p $TO
cd $TO
for R in $RANGES_LIBS
do
	G=${R##*/}
	D=${G/.git/}
	if [[ -d $D ]]
	then
		cd $D
		git up
		cd -
	else
		git clone $R
	fi
done
