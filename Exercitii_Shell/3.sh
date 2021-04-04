#!/usr/bin/bash

D=$1

for F in `find $D -type f -name "*.c"`
do
	sort $F -o $F
done
 
