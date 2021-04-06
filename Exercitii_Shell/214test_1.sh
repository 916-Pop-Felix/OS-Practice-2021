#!/usr/bin/bash

#Sa se scrie un script shell care primeste un cuvant, urmat de oricate nume de fisiere
#Determina cate fisiere date contin acel cuvant

name=$1
count=0
shift

for filename in $@
do
	if [ -f $filename ];then
		if grep -E -q "$name" $filename ;then
			count=$((count+1))
		fi
	fi
done
echo $count
