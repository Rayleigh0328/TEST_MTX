#!/bin/bash
FILES=*.mtx
for f in $FILES
do
	echo "Processing file $f"
	./jbig_enc $f
	jbig=${f/%mtx/jbg}
	size=$(stat -c%s "$jbig")
	echo "size of $jbig is $size"
	echo ""
done
