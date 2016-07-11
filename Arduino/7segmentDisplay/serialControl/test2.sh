#!/bin/bash

echo "Setting up ttyUSB connection..."
stty raw -echo < /dev/ttyUSB0

echo "Sending Integers..."
while [ 1 ]
do 
  for i in `seq 0 9`
  do 
    for x in `seq 0 9`
    do 
      echo $x > /dev/ttyUSB0
      echo -n "$x "
      sleep .05
    done
    echo " "
  done
done
