#!/usr/bin/bash

#Sa se scrie un script shell care primeste ca argument un simbol + sau -
# urmat de oricate nr naturale
#+ -> suma nr date
#- -> dif dintre primu si restu

C=$1
result=$2
shift
shift
for N in $@; do
	if [ $C = "+" ];then
		result=$((result+$N))
	elif [ $C = "-" ]; then
		result=$((result-$N))
	else
		echo Invalid expresion
		exit 1
	fi
done

echo $result
