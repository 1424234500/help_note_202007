#!/bin/bash  
###########################################
# raspberry服务器 启动流程 
# 项目架构参照/python/server_frame.c
# 
###########################################
source tools.sh
source constant.sh
##-----------------------------------------
 
echo $server_python_web_log
echo $server_python_socket_log

function start_raspberry(){
    echo 'Begin to start the raspberry servers!'
# //  tomcat
    
    # tomcat/bin/start.sh
# //  web tornado         短连接     图片/视频流生成-加工
    cd $_server
    echo ' nohup python server_web.py >> '$server_python_web_log' &'
    nohup python 'server_web.py' >> $server_python_web_log &

# //  socket-io           长连接
    cd $_server
    echo ' nohup python server_socket.py >> '$server_python_socket_log' &'
    nohup python 'server_socket.py' >> $server_python_socket_log &

# //  nginx 代理启动
    # /usr/sbin/nginx

    echo 'End---------- '
}



function stop_raspberry(){
    echo 'Begin to start the raspberry servers!' 
    killall -9 python

    echo 'End------------'
}





function start_main(){
    
    start_raspberry $@

}
# 单独执行文件时操作如下 引入时提示
_temp='do_start.sh'
if [[ $0 =~ $_temp ]]
then
    start_main $@
else
    echo 'source '$_temp
fi 



