#!/bin/bash

# Fetch external libraries as submodules

TOPDIR=`dirname $0`

# Update all the external dependencies
for F in $TOPDIR/.external/*
do
       git submodule update --init $M
done
