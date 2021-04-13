#!/usr/bin/bash

#Scrieti un script shell care primeste ca prim argument numele
#unei extensii de fisier (ex: .txt)
#Scriptul va parcurge recursiv directorul curent si va identifica
#fisierele cu extensia data ca prim argument, care nu contin niciun
#numar par si au numar impar de cuvinte.
#Se vor afisa numele acelor fisiere si drepturile de acces
#(scriere/citire/executie) asupra lor.
#Se va valida numarul argumentelor liniei de comanda. Daca nu exista
# niciun fisier cu extensia data ca prim parametru, se va afisa un
#mesaj de eroare.

ok=0

if [ $# != 1 ];then
	echo Invalid number of args
	exit 1
fi

IFS='\n'
for file in `find -type f -name "*$1"`
do
	#echo $file
	num=$(wc -w | awk '{print $1}')
	if grep -E -q " [0-9]*[02468] " "$file" ;then
		if [ `expr $num % 2` != 0 ];then
		echo $file $(ls -l "$file" | awk '{print $1}')
		ok=1
		fi
	fi
done
