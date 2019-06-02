#!/bin/bash  
###########################################
#do
#管道 生产者 写入管道
########################################### 
source tools.sh 



function pipe_init(){
    out 'pipe maker start'
    out 'pid.'$$
    
    tempfifo='make.'$$'.fifo'
    # exec 1000>&-;表示关闭文件描述符1000的写
    # exec 1000<&-;表示关闭文件描述符1000的读
    trap "exec 1000>&-;exec 1000<&-;exit 0" 2 #捕获中断命令 

    mkfifo -m 0644 $tempfifo # 创建一个管道文件
    # 将文件描述符1000与FIFO进行绑定，<读的绑定，>写的绑定，<>则标识对文件描述符1000的所有操作等同于对管道文件$tempfifo的操作
    exec 1000<>$tempfifo #创建文件标示符“5”，这个数字可以为除“0”、“1”、“2”之外的所有未声明过的字符，以读写模式操作管道文件；系统调用exec是以新的进程去代替原来的进程，但进程的PID保持不变，换句话说就是在调用进程内部执行一个可执行文件
    rm -rf $tempfifo #清除创建的管道文件

    if (( $# < 1))
    then 
        count=5
    else
        count=$1
    fi
    
    for ((i=1; i<=$count; i++))
    do
        echo "" >&1000
    done
}


function signalMake(){
    while [[ "1" == "1" ]]
    do
        cmd=`date "+%Y-%m-%d %H:%M:%S"`
        signal="make-"$cmd
        echo $signal >&1000
        sleep $(($RANDOM%2))
    done
}

function signalUse(){
    for ((i=1; i<=999; i++))
    do
        read -u1000 readStr
        {
            out "get Source: "$readStr
            sleep $(($RANDOM%5))
        } &
    done
}

# dequeDo methodName args1 args2
function dequeDo(){
    method=$1
    if [[ "$method" != "" ]]
    then 
        rootParams=($@)   
        params=(${rootParams[@]:1}) 
#        out "wait signal - $@"
        local readStr
        read -u1000 st
        local readStr=$st
        {
            out "get  signal: "$readStr
            out $@
            $method ${params[@]}
            sleep $(($RANDOM%3))
            echo $readStr >&1000
        } &

    else
        echo 'eg:'
        echo 'dequeDo methodName args1 args2'
    fi
}

# 单独执行文件时操作如下 引入时提示
_temp='pipe_maker.sh'
if [[ $0 =~ $_temp ]]
then
    
    if (( $# < 1 ))
    then
        pipe_init 3
        thread signalMake
        thread signalUse
    else
        pipe_init 5
        for ((i=1; i<=100; i++))
        do
            dequeDo echo $i & 
        done
    fi  
    wait  
else
    echo 'source '$_temp
fi 


