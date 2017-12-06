#!/bin/sh

for i in *.txt ; do j=`echo $i|sed s/.txt//g`;`./calculator $i > $j"output.txt"`; done