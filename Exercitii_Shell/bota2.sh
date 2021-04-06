#!/usr/bin/bash

#8. Să se scrie un script bash care afişează, pentru fiecare fişier dat ca argument,
# linia care apare de cele mai multe ori. Afişarea se va face în ordinea descrescătoare a numărului de apariţii.
#(comenzi: sort, uniq, head)0

for file in $@;do
	if [ -f $file ];then
		sort $file | uniq -c | head -1
	fi
done
