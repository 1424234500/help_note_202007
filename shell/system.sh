#!/bin/bash  
###########################################
#监控cpu 超过预计则执行特定操作
#./system.sh <80, cpu%> 
###########################################

cpuMax=5
if [ ! -z $1 ];then
    cpuMax=$1
fi

keyword='java'
if [ ! -z $2 ];then
    keyword=$2
fi

# do something
function onCpuMax(){
    nowdir=`pwd`
    
    pid=`ps -elf | grep $keyword  | grep -v grep | awk '{print $4}' `   #获取jmap 关键词pid
    pid_commond=(`jps -q`)     #6213 Bootstrap   获取所有java进程pid 用于jstack
    
    ti=`date "+%Y%m%d-%H%M%S"`    #时间戳
    ip=`ifconfig | grep inet | grep -v 127.0.0.1 | grep -v inet6 | awk '{print $2}'`

    
    echo -e "pid:$pid, ip:$ip, key:$key"
    arr=($pid)
    if (( ${#arr[@]} > 1 ));then
        pid=${arr[0]}
        echo -e "Error!---------- many pid exists, chose the first one"
    fi
    if (( ${#arr[@]} == 0 ));then
        echo -e "Error!---------- no pid exists, exit! "
        exit 1
    fi
    
    key=$ip-$pid.$ti.$1        #命名键
    
    file=~/logs/make         #存储根路径 临时存放路径
    file_gz=$file/cpu   #压缩文件存储路径
    mkdir $file
    mkdir $file_gz
    file_cpu_thread=$file/$key.cpu_thread.log    
    file_jstack=$file/$key.jstack.log  #$file/$ip-$pid.$ti.$1
    file_jmap=$file/$key.jmap_dump.hprof
    file_net=$file/$key.net.log
    file_7z=$file_gz/$key.tar.gz

    echo "net work df top "
    echo ' ' > $file_net
    ifconfig >> $file_net
    df -h >> $file_net
    top -bn 1 -i -c >> $file_net
    netstat -ano >> $file_net
    
    echo "ps thread"
    #采集最消耗cpu的线程tid pid ppid command 可根据tid->16进制查找java线程栈
    #ps H -eo user,pid,ppid,tid,time,%cpu --sort=%cpu  > $file_cpu_thread    
    ps H -eo tid,%cpu,pid,ppid,time,user,cmd --sort=+%cpu  | awk '{printf "0x%x\t %s\n", $1, $0}'  > $file_cpu_thread  #附带自动转换16进制
    
    echo "jstack ${pid_commond[@]} "
#    echo "jstack ${pid_commond[@]} " > $file_jstack
    for ((i=0; i<${#pid_commond[@]}; i++))
    do
        item=${pid_commond[$i]}
        echo -e "\n\n\n\n--$i\t------$item\t--------\n" >> $file_jstack
        jstack -l $item > $file/$ip-$item.$ti.$1.jstack.log      #采集java线程栈 
    done  
    
    echo "jmap"
    jmap -dump:format=b,live,file=$file_jmap $pid       #采集jmap
    
    echo "Begin comp"`date "+%Y-%m-%d %H:%M:%S"`
    cd $file #避免压缩文件夹路径
    tar -czvf $file_7z $key.* 
    #rm $file/$key.*     #移除已经压缩数据
    
    #jhat -J-Xmx1024M $jmap_file #等待访问 http://127.0.0.1:7000
    #jvisualvm $file_jmap &  #图形化分析工具

    cd $nowdir
}



time=`date "+%Y-%m-%d %H:%M:%S"`

idle=`top -bn 1 -i -c | awk 'NR==3{print $8}' OFS=':'`

idle=${idle%.*}
cpuNow=$((100 - idle))
echo "Now $time cpuNow $cpuNow, cpuMax $cpuMax "
if [ $cpuNow -ge $cpuMax ]; then
    echo "Start $time cpuNow $cpuNow, cpuMax $cpuMax "
    onCpuMax $cpuNow
    time=`date "+%Y-%m-%d %H:%M:%S"`
    echo "Stop $time cpuNow $cpuNow, cpuMax $cpuMax "
fi








