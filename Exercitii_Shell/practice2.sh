#!/usr/bin/bash

if [ $# -lt 2 ];then
	echo Invalid number of args
	exit 1
fi

P=$1
shift
for D in $@;do
	if [ ! -d $D ];then
		echo Given directory doesnt exist
		exit 1
	fi
	for file in `find $D`;do
		if [ -f $file ];then
		#	if echo $file | grep -q -E ".bak$";then
				#da
		#	else
				if ls -l | grep -E -q "$P";then
					N=$(echo $file.bak)
					chmod $N 755
					cd $dir | touch $N
					cat $file > $N
					chmod $N 200
				fi
			#fi
		fi

	done

done
