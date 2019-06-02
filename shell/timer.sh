#!/bin/bash
###########################################


if [ -z "$1" ];then
    echo "./timer.sh './help.sh adjf' <5 s <999 count> > "
    exit
fi
cmd=$1

deta=5
if [ ! -z $2 ];then
    deta=$2
fi
count=0
if [ ! -z $3 ];then
    count=$3
fi


echo "Interval sleep $deta sec, count $count start "

if [[ "$count" == "0" ]] ;then
    i=0
    while [[ "1" == "1" ]]
    do
        i=$[i + 1]
        echo "-----------all"
        echo `date "+%Y-%m-%d %H:%M:%S" `" now $i/$count sleep $deta run ! " 
        $cmd 
        sleep $deta
    done
else
    for ((i=0; i<$count; i++))
    do
        echo "----------------"
        echo `date "+%Y-%m-%d %H:%M:%S" `" now $i/$count sleep $deta run ! " 
        $cmd 
        sleep $deta
    done  
fi


