#!/usr/bin/bash

while [ 1 ]; do
	for P in $@; do
		F=`grep -E -c "$P" ps.fake`
		if [ $F -gt 0 ]; then
			kill $P
		fi
	done
done
