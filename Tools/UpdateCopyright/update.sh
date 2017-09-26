#!/bin/bash

TEMPLATE_C=Tools/UpdateCopyright/copyright.template.c
FILES_C=`find Springboard/Source -type f \( -iname "*.cpp" -o -iname "*.hpp" \) && find Springboard/Include -type f \( -iname "*.cpp" -o -iname "*.hpp" \)`
for f in $FILES_C; do
	rm -f $f.new
	cat $TEMPLATE_C > $f.new
    grep -n "Copyright" $f > /dev/null
    if [[ $? -eq 0 ]]; then
		LINECUT=`grep -n "^\s*$" $f | head -1 | sed "s/\://g"`
		tail -n +$LINECUT $f >> $f.new
	else
		cat $f >> $f.new
	fi
	mv -f $f.new $f
done

TEMPLATE_PY=Tools/UpdateCopyright/copyright.template.c
FILES_PY=`find Springboard/Python -type f -iname "*.py"`
for f in $FILES_PY; do
	rm -f $f.new
	cat $TEMPLATE_PY > $f.new
    grep -n "Copyright" $f > /dev/null
    if [[ $? -eq 0 ]]; then
		LINECUT=`grep -n "^\s*$" $f | head -1 | sed "s/\://g"`
		tail -n +$LINECUT $f >> $f.new
	else
		cat $f >> $f.new
	fi
	mv -f $f.new $f
done
