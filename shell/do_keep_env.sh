# !/bin/bash  
########################################### 
# ./do function <help>
# About:
# 保持服务器环境
# 添加于crontab守护进程拉起
# crontab -e
# */1 * * * * echo `date "+%Y-%m-%d %H:%M:%S"` >> ~/logs/crontab.log
# */5 * * * * cd ~/shell && ./do_keep_env.sh start >> ~/logs/crontab.log
###########################################
source constant.sh
source tools.sh
#########################################

 
function start(){
    nowDir=`pwd -LP`
    echo $@
    #mysql 
    #walker-service-provider
    #walker-web
    toolsLineLong
    local dirArr=( 
         '/home/walker/software/redis-5.0.3/src'        #redis
         '/home/walker/software/zookeeper-3.4.12/bin'   #zookeeper
         '/home/walker/zookeeper-3.4.14/bin'            #zookeeper server
#        '/home/walker/software/apache-tomcat-8.5.40/bin'    #tomcat admin monitor  

         '/home/walker/walker-service-provider'  
         '/home/walker/walker-web'
     
     )
    local cmdArr=(
        './redis-server'
        './zkServer.sh start'   
        './zkServer.sh start'
        #'startup.sh'
        './server.sh start'
        './server.sh start'
        
    )
    out 'start linux software '${#arr[@]}
    toolsLineLong
    for ((i=0; i<${#dirArr[@]}; i++))
    do
        local path=${dirArr[$i]}     
        local she=${cmdArr[$i]}
        out "Start $i\t cd $path && $she" 
        
        if [ ! -d "$myPath"]; then      # 这里的-d 参数判断$myPath是否存在 是否为目录   不存在 跳过启动
            out "no exists the path $myPath"
            continue
        fi 
        cd ${myPath}
        local tools_out='nohup '$she' >/dev/null & '   #日志输出?
        out $tools_out
        eval $tools_out
        
        
        toolsLineLong
    done    
 
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
        echo `date "+%Y-%m-%d %H:%M:%S"`" keep env "
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
