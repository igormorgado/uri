#!/bin/bash

for x in $( seq ${1} )
do
    ./switch.sh $x && make all
done
