#!/bin/bash
############################

function help(){
    echo ' ./help "2018-01-01 01:01:01" <"2018-01-01 01:01:01"> ' 
}

min=0
max=3

tstart=$1
tstop=$2
if [ ! -z "$tstart" ]
then
    tstartmill=`date -d "$tstart" +%s `"000"
else
    help
    exit
fi
if [ ! -z "$tstop" ]
then
    tstopmill=`date -d "$tstop" +%s `"000"
fi

#echo "--$tstart : $tstartmill  -> $tstop : $tstopmill"

tables=(    "msg_record_"   "msg_entity_"   "msg_state_"    )
keys=(      "s_atime"    "timemillis"    "s_atime"   )
keyTypes=(  "long"  "long"  "str"   )

before="delete from "

for ((i=0; i<${#tables[@]}; i++))
do
    keyType=${keyTypes[$i]}
    key=${keys[$i]}
    table=${tables[$i]}
    if [[ "$keyType" == "long" ]]
    then
        start=$tstartmill
        stop=$tstopmill
    else
        start=$tstart
        stop=$tstop 
    fi
    echo -e "\n\n"
    #echo "do $table $key $keyType "
    after=" where 1=1 and $key >= '$start'"
    if [ ! -z "$stop" ]
    then
        after="$after and $key <= '$stop'"
    fi
    for ((j=$min; j<$max; j++))
    do
        nowTable="$table""$j"
        sql="$before $nowTable $after;"
        echo $sql
    done
    
done








    
    
