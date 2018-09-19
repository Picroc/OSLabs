#!usr/local/bin/bash
while true
do
	a=$(grep -Eo '^[0-9]+$' file | tail -1)
	a=$((a+1))
	echo "\n$a" >> file
	sleep 5
done
