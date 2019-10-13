#!/bin/bash

# Filename: ex21.sh
#
# Problem: Count the number of quotes each person had in the top 100 quote
# list. Then output the list of names in alphabetical order with the number of quotes each.
#ih= 0
cat ex21.input | awk '{
		if (match($0,"-")) {
			name=substr($0,0,match($0,"-")-1);
			Array[name] += 1
		}
	}
	END {
		#n = asorti(Array, copy)
		for (i in Array){
			print i " had " Array[i] " quotes." | "sort"
			#print name " had "  " quotes."
}	}'
