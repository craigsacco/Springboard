#!/bin/bash

TEMPLATE=Tools/UpdateCopyright/copyright.template
FILES=`find Springboard/Source -type f \( -iname "*.cpp" -o -iname "*.hpp" \) && find Springboard/Include -type f \( -iname "*.cpp" -o -iname "*.hpp" \)`
for f in $FILES; do
	rm -f $f.new
	cat $TEMPLATE > $f.new
    grep -n "Copyright" $f > /dev/null
    if [[ $? -eq 0 ]]; then
		LINECUT=`grep -n "^\s*$" $f | head -1 | sed "s/\://g"`
		tail -n +$LINECUT $f >> $f.new
	else
		cat $f >> $f.new
	fi
	mv -f $f.new $f
done

