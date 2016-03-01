#!/bin/bash
rm quad_log
FILES=*.mtx
for f in $FILES
do
	echo "Processing file $f"
	./quad -f $f >> quad_log
done
