#!/usr/bin/bash

#5. Write a shell script that will verify if a list of N numbers (N given as argument) 
# read from the keyboard are prime or not.

N=$1
shift

for num in $@;do
	if [ $num -le 1 ];then
		echo $num is not prime!
	elif [ $num -ne 2 ] && [ `expr $num % 2` == 0 ];then
		echo $num is not prime!
	else
		ok=0
		for((i=3;i<$num&&ok==0;i+=2));do
			if [ `expr $num % $i` == 0 ];then
				echo $num is not prime!
				ok=1
			fi
		done
		if [ $ok -eq 0 ];then
			echo $num is a prime number!
		fi
	fi
done
