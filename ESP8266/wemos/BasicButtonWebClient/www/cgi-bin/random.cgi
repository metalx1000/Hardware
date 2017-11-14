#!/bin/sh
echo "Content-type: text/plain\n"

r=$(shuf -i0-9 -n1)
echo "$r"
echo "$r" > ../photos.dat
