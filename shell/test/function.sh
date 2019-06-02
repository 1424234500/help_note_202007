function testDualProcessLimit(){ 
    #source /etc/profile; 
    # ----------------------------- 
    tempfifo=$$.fifo        # $$表示当前执行文件的PID
    begin_date=0           # 开始时间
    end_date=100             # 结束时间 
    # ----------------------------- 
    trap "exec 1000>&-;exec 1000<&-;exit 0" 2
    mkfifo $tempfifo #创建一个管道文件
#将文件描述符1000与FIFO进行绑定， <读的绑定，>写的绑定，<>则标识对文件描述符1000的所有操作等同于对管道文件$tempfifo的操作
    exec 1000<>$tempfifo 
    rm -rf $tempfifo

#对文件描述符1000进行写入8个空行， 以行为单位的
    for ((i=1; i<=8; i++))
    do
        echo >&1000
    done

    while [[ $begin_date != $end_date ]]
    do
#的作用就是读取管道中的一行 在这里就是读取一个空行 每次读取管道就会减少一个空行
        read -u1000 
          {
            echo "do at $begin_date " 
            sleep 1 
            echo >&1000 #执行完后台任务之后，往文件描述符1000中写入一个空行。 
        } & #它表示进程放到linux后台中执行
 
        begin_date=$[begin_date+1]
    done

    wait
    echo "done!!!!!!!!!!"
}


 
 
 
function testFile(){
    for file in ` ls $1 `  
    do  
        if [ -d $1"/"$file ]  
        then  
            testFile $1"/"$file  
        else  
            filename=$1"/"$file   
            echo $filename
        fi  
    done  
  
} 


function testDualProcess(){
    #!/bin/bash
    date
    for i in `seq 1 5`
    do
    {
        echo "sleep 1"
        sleep 1
    } &
    done
    echo 'wait'
    wait  ##等待所有子后台进程结束
    echo 'wait end '
    date 
}











function testReadAuto(){
    filename=$1
    str=""
    #str1="1234"
    until [[ $str == "Get random number :1000" || $str == "quit" ]]
    #while  [[ $str != "exit" ]]
    do
        str="Get random number :"$(($RANDOM%1000+1 ))
        echo "$str"  >> $filename
        #read str
        sleep 1 
        #read  str str1
        #echo ">$str"
        #echo ">$str1 "
    done 
}

function testread(){ 
    filename=$1
    str=""
    #str1="1234"
    
    clearfile $filename
    res=$? 
    if [ $res == 0 ]
    then
        echo "error! ${filename} is not exist "
        return 0     
    fi
        
    until [[ $str == "exit" || $str == "quit" ]]
    #while  [[ $str != "exit" ]]
    do
        echo "$str"  >> $filename
        read str
         
        done 
        
    return 1
}

function clearfile(){
    if [ $# \< 1 ]
    then
        echo '> clearfile name = null' 
        return 0
    else
        echo > clearfile name:$1
        echo -n '' > $1
        return 1
    fi
}

 #clearfile filename


