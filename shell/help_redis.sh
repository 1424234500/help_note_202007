#!/bin/bash
############################

function help(){
    echo ' show ms-broadcast* del, del keys '
    echo ' show ms-broadcast* list, list keys '
    echo ' show ms-broadcast-group, show the key and value '
    echo ' show ms-broadcast*     , show the keys and values '
    eval $exe
}
function show(){
    local i=$1
    local key=$2
    local type=$3
    if [ -z $type ]
    then
        showValue $key $i
    elif [[ $type == "del" ]]
    then
        delKey $key
    fi
}
function showValue(){
    local i=$2
    local key=$1
    local cmdShowType=$exe' type '$key
    local type=`eval $cmdShowType`
    local cmdShow=''
    local cmdSize=''
    if [[ $type == "string" ]]
    then
        cmdShow=$exe' get '$key
    elif [[ $type == "set" ]]
    then
        cmdShow=$exe' smembers '$key 
    elif [[ $type == "zset" ]]
    then
        cmdShow=$exe' zrange '$key' 0 '$end' withscores'
        cmdSize=$exe' zcard '$key
    elif [[ $type == "hash" ]]
    then
        cmdShow=$exe' hgetall '$key 
    elif [[ $type == "list" ]]
    then
        cmdShow=$exe' lrange '$key' 0 '$end
        cmdSize=$exe' llen '$key
    else 
        echo 'What type ? '$type
    fi
    echo -e "## $i\t ## $key"
    eval $cmdShow 
    if (( ${#cmdSize} > 0 ));then
        eval $cmdSize    
        cmdSize=""
    fi
}
function delKey(){
    local key=$1
#    local cmdShowType=$exe' type '$key
#    local type=`eval $cmdShowType`
    local cmdShow=$exe' del '$key
    
    echo -e "## $i\t ## $key del `eval $cmdShow`"
    
}

exe='/home/walker/software/redis-5.0.3/src/redis-cli ' #-a ruaho123
key=''
type=''
end=24
if [ ! -z $1 ]
then
    key=$1
    if [ ! -z $2 ]
    then
        type=$2
    fi
    
    cmd=$exe" keys "$key" | awk -F'\"'  '"'{print $1}'"' | sort"  
    echo $cmd 
    #eval $cmd 
    listKey=(`eval $cmd`)
    for ((i=0; i<${#listKey[@]}; i++))
    do 
        item=${listKey[$i]}
        show $i $item $type
    done
else 
    help
fi




    
    
