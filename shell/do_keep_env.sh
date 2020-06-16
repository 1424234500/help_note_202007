# !/bin/bash  
########################################### 
# ./do function <help>
# About:
# 保持服务器环境
# 添加于crontab守护进程拉起
# crontab -e
#*/1 * * * * . /etc/profile; echo `date "+\%Y-\%m-\%d \%H:\%M:\%S"`" crontab trigger 1m " >> ~/logs/crontab.log  #定时测试crontab状况
#*/5 * * * * . /etc/profile; cd ~/shell && bash do_keep_env.sh start >> ~/logs/crontab.log  #定时拉起关键服务
###########################################
source constant.sh
source tools.sh
#########################################


function start(){
	
	rm /tmp/zookeeper -r
	rm /tmp/kafka-logs/ -r
 
 
    nowDir=`pwd -LP`
    #mysql 
    local dirArr=( 
		 '/home/walker/software/redis-5.0.3'				'./src/redis-server redis.conf'			#redis 反复启动问题
    
        

         '/home/walker/software/zookeeper-3.4.14'			'./bin/zkServer.sh start'				#zookeeper local 
		 '/home/walker/software/kafka_2.12-2.5.0'			'./bin/kafka-server-start.sh config/server.properties'	#强依赖zookeeper 

#        '/home/walker/software/apache-tomcat-8.5.40'		'./bin/startup.sh'						#tomcat admin monitor  

         '/home/walker/software/mysql-8.0.16-linux-x86_64-minimal'		'./bin/mysqld_safe --defaults-file=my.cnf  --user=walker'
         '/home/walker/software/mysql-5.7'								'./bin/mysqld_safe --defaults-file=my.cnf  --user=walker'

         '/home/walker/project/walker-service-provider'				'bash server.sh start'  
         '/home/walker/project/walker-web'							'bash server.sh start'
         '/home/walker/project/walker-socket'						'bash server.sh start'  
     
     )
     
    toolsLineLong
    out 'start linux software '${#arr[@]}
    toolsLineLong
    for ((i=0; i<${#dirArr[@]}; i=i+2))
    do
        local myPath=${dirArr[$i]}     
        local she=${dirArr[${i} + 1]}
        if [ ! -d "$myPath" ]; then      # 这里的-d 参数判断$myPath是否存在 是否为目录   不存在 跳过启动
            out "#${i}## Skip no exists the path cd $myPath && $she"
            continue
        else
            cd ${myPath}
            local tools_out='nohup '$she' >/dev/null 2>&1 & '   #日志输出?
            out "=${i}== Start cd $myPath && $tools_out"
            eval $tools_out
			sleep 1
        fi 
    done    
    toolsLineLong
    out 'start linux software over '
    toolsLineLong
    cd $nowDir
} 



function do_init(){  
    method=$1
    if [[ "$method" != "" ]]
    then 
        rootParams=($@)   
        params=(${rootParams[@]:1}) 
        out " keep env "
        toolsShowMethod $method "${params[*]}"
        #echo ${params[@]}
        $method ${params[@]}
    else
        echo 'eg:'
        echo './do test "params of test"'
    fi
}


function do_main(){ 
    echo
    toolsShow $@
    ##########################do something yourself
    do_init $@
    ##########################
    toolsLineLong 
    echo
}

function show(){  
    echo '$0'">>"$0
    echo '$*'">>"$*
    echo '$@'">>"$@    
    echo '$#'">>"$# 
    echo '$$'">>"$$ 
}


 
#start



# 单独执行文件时操作如下 引入时提示
_temp='do_keep_env.sh'
if [[ $0 =~ $_temp ]]
then
    do_main $@
else
    echo 'source '$_temp
fi 
