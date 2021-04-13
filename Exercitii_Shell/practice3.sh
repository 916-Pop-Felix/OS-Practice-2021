#!/usr/bin/bash

if [ $# -lt 1 ];then
	echo Invalid number of args
	exit 1
fi

for I in $@;do
	if [ -d $I ];then
		ls -l "$I" | tail -n+2 | awk '{print $1}'
	elif [ -f $I ];then
		if ls -l "$I" | grep -E -q "rw";then # check permissions
			sed -E -n "s/[0-9]{1,} /ERROR/gi" $I
		fi
	else
		finger $I > /dev/null
		if [ $? -eq 0 ]  ;then  # user doesn't exist
			echo $I,"is not a valid name for each field given"
		elif finger $I | grep -E -q "Never logged in" ;then # user exists, but not logged in
			last $I | head -1 | awk '{print $3,$7,$9}'
		else # user exists, is logged in
			N=$(ps -U $I | wc -l)
			N=$((N-1))
			echo $N
		fi
	fi
done
