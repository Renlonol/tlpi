#!/bin/bash

BIN="./bin/is_echo_cl"
host=$1
num=$3
for ((i=1; i<=${3}; i ++))
do
    str=$2_$i
	${BIN} $host $str
done