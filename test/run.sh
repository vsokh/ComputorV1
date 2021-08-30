#!/bin/bash

prog=$1
input=$2
output=$3
[[ -f "$output" ]] && true>"$output"
while IFS= read -r line;
do
	./"$prog" "$line"  >> "$output"
done < "$input"
