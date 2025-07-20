#!/bin/bash

OUT="src/Makefile.am"
echo "AM_CPPFLAGS = -I\$(top_srcdir)/include" > $OUT
echo -n "bin_PROGRAMS =" >> $OUT

for file in src/*.c; do
    base=$(basename "$file" .c)
    if [ "$base" != "utils" ]; then
        echo -n " $base" >> $OUT
    fi
done

echo "" >> $OUT

for file in src/*.c; do
    base=$(basename "$file" .c)
    if [ "$base" != "utils" ]; then
        echo "${base}_SOURCES = $base.c utils.c" >> $OUT
    fi
done

