#!/usr/bin/bash

for name in `awk '{print $1}' who.fake`
do
	echo "$name $(grep -c "$name" ps.fake)"
done
