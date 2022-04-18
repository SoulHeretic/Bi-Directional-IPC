#!/bin/bash
if [ -z $1 ]
   then
       echo "Usage test_script #messages"
       exit
fi
   
i=0
until [ $i -ge $1 ]
do
    echo "${i}th message"
    let i+=1
done
