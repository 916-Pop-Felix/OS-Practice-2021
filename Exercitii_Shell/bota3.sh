#!/usr/bin/bash


#5. Să se scrie un script bash care afișează primele 5 linii și ultimele 5 linii ale fișierelor de tip text din
# directorul curent. Dacă un fișier are mai puțin de 10 linii, atunci va fi afişat în întregime.
#(comenzi: head, tail, find, file, wc)


for file in `ls`;do
	if [ -f $file ];then
		echo $file contains
		if [ $(wc $file | awk '{print $1}') -lt 10 ];then
			cat $file
		else
			head -5 $file
			tail -5 $file
		fi
	fi
done
