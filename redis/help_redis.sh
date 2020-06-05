#!/bin/bash
############################
#
#
#
######################
function help(){
    out ' ./help_redis.sh del ms-broadcast* [ other args], del keys '
    out ' ./help_redis.sh delttl ms-broadcast* 3600 [ h=3600 d=86400 15d=1296000], del keys expire seconds '
    out ' ./help_redis.sh list ms-broadcast* [ other args], list keys '
    out ' ./help_redis.sh show ms-broadcast*  [ other args], show the keys and values '
    echo $exe
    eval $exe
}


function out(){
    echo -e `date "+%Y-%m-%d %H:%M:%S" `' '$@
}
function outCmd(){
    #echo -e `date "+%Y-%m-%d %H:%M:%S" `' '$@
    return 0
}

# $cc $key 
function list(){
    out "list## ${1}\t ## ${2} "
}
function show(){
    local i=$1
    local key=$2
    local cmdShowType=$exe' type "'$key'"'
    local type=`eval $cmdShowType`
    local cmdShow=''
    local cmdSize=''
    if [[ $type == "string" ]]
    then
        cmdShow="$exe get '$key' "
        cmdSize="$exe strlen '$key' "
    elif [[ $type == "set" ]]
    then
        cmdShow="$exe smembers '$key' "
        cmdSize="$exe scard '$key' "
    elif [[ $type == "zset" ]]
    then
        cmdShow="$exe zrange '$key' -$valueSize -1 withscores "
        cmdSize="$exe zcard '$key' "
    elif [[ $type == "hash" ]]
    then
        cmdShow="$exe hgetall '$key' "
        cmdSize="$exe hlen '$key' "
    elif [[ $type == "list" ]]
    then
        cmdShow="$exe lrange '$key' -$valueSize -1 "
        cmdSize="$exe llen '$key' "
    elif [[ $type == "none" ]]
    then
        out "show## $i\t ##type:${type} no exists '$key' "
    else
        out "show## $i\t ##type:${type} what fuck ? '$key' "
    fi

    if (( ${#cmdSize} > 0 ));then
        out "show## $i\t ##type:${type} '$key' "
        eval $cmdShow 
        eval $cmdSize    
    fi
}
function del(){
    
    local i=$1
    local key=$2
    local cmdShowType=$exe' type "'$key'"'
    local type=`eval $cmdShowType`
    local cmdShow=''
    local cmdSize=''
    if [[ $type == "string" ]]
    then
        cmdShow="$exe get '$key' "
        cmdSize="$exe strlen '$key' "
    elif [[ $type == "set" ]]
    then
        cmdShow="$exe smembers '$key' "
        cmdSize="$exe scard '$key' "
    elif [[ $type == "zset" ]]
    then
        cmdShow="$exe zrange '$key' -$valueSize -1 withscores "
        cmdSize="$exe zcard '$key' "
    elif [[ $type == "hash" ]]
    then
        cmdShow="$exe hgetall '$key' "
        cmdSize="$exe hlen '$key' "
    elif [[ $type == "list" ]]
    then
        cmdShow="$exe lrange '$key' -$valueSize -1 "
        cmdSize="$exe llen '$key' "
    elif [[ $type == "none" ]]
    then
        out "del## $i\t ##type:${type} no exists '$key' "
    else
        out "del## $i\t ##type:${type} what fuck ? '$key' "
    fi
    length=""
    if [ ! -z "${cmdSize}" ] ; then
        length=`eval ${cmdSize} `
    fi
    
    local cmd=$exe' del "'${2}'"'
    outCmd ${cmd}
    out "del## ${1}\t ##type:${type}, length:${length}, res:`eval ${cmd}` ${2} "
    
}
# $cc $key 3600(s)
function expire(){
    local cmd=$exe' expire "'${2}'"'" ${3} "
    outCmd ${cmd}
    out "expire## ${1}\t ## ${2} ${3} res:`eval ${cmd}`"

}
# $cc $key 3600(s)
# 过期时间检测
# 大于3600s则设置为3600s
# 小于3600s的删除
function delttl(){
    local cmd=$exe' ttl "'${2}'"'
    outCmd ${cmd}
    local res=`eval ${cmd}`
    out "delttl## ${1}\t ## ${2} ${3} res:${res}"
    if (( ${res} > ${3} )); then
        expire $@
    elif (( ${res} > 0 )); then
        del $@
    fi
   
    
}

# ${cursor} 
function whileCursor(){
    IFS_old=$IFS #将原IFS值保存，以便用完后恢复 
        
    IFS=$'\n' #更改IFS值为$’\n’ ，注意，以回车做为分隔符，IFS必须为：$’\n’   

    cursor=0
    local flag=0    #do while
    while [[ ${cursor} != 0 || ${flag} == 0 ]]
    do
        flag=1
        cmd="${exe} scan ${cursor} ${match} COUNT ${cursorSize} "
        str=`eval ${cmd}`
        if [[ ${str} == *ERR* ]]; then
            out "error!!! ${str} break"
            break
        fi
        
        arr=( ${str} )

        nextCursor=${arr[0]}
        
        #arr=(${arr[@]:1})

        arrSize=${#arr[@]}
        arrSize=$((arrSize-1))
        out "##${count}\t#dbsize:${dbsize}, next-cursor: ${nextCursor},res-size: ${arrSize} " #cmd: ${cmd}, 
        for ((i=1; i<${#arr[@]}; i++))
        do 
            item=${arr[${i}]}
            cc=$((count+i-1))
            $type $cc $item $params
        done
        
        count=$((count+arrSize))
        cursor=${nextCursor}
        #break
    done
    IFS=$IFS_old #恢复原IFS值 
    return 0
}
function whileKeys(){
    cmd="${exe} keys '${key}' "
    out ${cmd}
    str=`eval ${cmd}`
    if [[ ${str} == *ERR* ]]; then
        out "error!!! ${str} break"
        return 1
    fi
    
    arr=( ${str} )
    out "##${count}\t#dbsize:${dbsize}, next-cursor: ${nextCursor},res-size: ${arrSize} " #cmd: ${cmd}, 
    for ((i=0; i<${#arr[@]}; i++))
    do 
        item=${arr[${i}]} 
        $type ${i} $item $params
    done

    return 0
}

# $cc $key $others
function start(){
    
    redisHome="/home/walker/software/redis-5.0.3"
    configFile="${redisHome}/redis.conf"
    
    out "redisHome:${redisHome}"
    out "redisConfig:${configFile}"
    
    auth=`cat ${configFile} | grep -v '#' | grep requirepass | awk '{print $2}' `
    exe="${redisHome}/src/redis-cli " #-a ruaho123
    if [ ! -z ${auth} ]; then
        exe="${exe} -a ${auth}"
    fi
    exeRole="${exe} info Replication | grep role "
    exeInfo="${exe} info all "
    #eval ${exeInfo}
    role=`eval ${exeRole}`
    
    key="*"          # *stat*
    type='list'         #del list delttl show 
    valueSize=12     #show size
    cursorSize=100   #scan cursor count

    if [ ! -z $1 ]
    then
        type=$1
        if [ ! -z $2 ]
        then
            key=$2
            match=" MATCH ${key} "
        fi
        
        rootParams=($@)   
        params=(${rootParams[@]:2}) 
        
        dbsize=`${exe} dbsize `
        out "{ type:$type, key:$key, cursorSize:$cursorSize, showValueSize:$valueSize, otherArgs:${params[@]}, dbsize:${dbsize}, role:${role} } "
        if [[ ${role} != *master* && ${type} == del* ]]; then
            out "only master can del*"
            exit 0
        fi
        
        timeStart=`date -d now +%s `
        
        count=0 #total scan res size
       # whileCursor
        whileKeys
        
        timeStop=`date -d now +%s `
        timeDeta=$((timeStop-timeStart))
        out "-----over-----"
        out "dbsize:${dbsize}, role:${role}, scanSize:${count}, cost:${timeDeta} s "
    else 
        help
    fi

}


start $@
    
