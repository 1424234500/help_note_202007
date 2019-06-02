# !/bin/bash  
########################################### 
# ./do function <help>
# About:
# 多服务器项目部署管理监控工具
# 
###########################################
source tools.sh


names=('ali'            'localhost'            ) 
ips=('39.107.26.100'    '127.0.0.1'            ) 
uses=('root'             'walker'               )  
pwds=('RUAho1234'        'ruaho1234'            ) 



function server_init(){  
    method=$1
    if [[ "$method" != "" ]]
    then 
        rootParams=($@)   
        params=(${rootParams[@]:1}) 
        toolsShowMethod $method "${params[*]}"
        #echo ${params[@]}
        $method ${params[@]}
    else
        echo 'eg:'
        echo './do test "params of test"'
    fi
}
function log(){
    toolsLine
    local len=${#ips[@]}
    for ((i=0; i<$len; i++))
    do
        local name=${names[$i]}
        local ip=${ips[$i]}
        local user=${uses[$i]}
        local pwd=${pwds[$i]}
        if [ "$name" = "$1" ]
        then
            echo "++"$ip" + "$name" + "$user" + "$pwd 

            local cmd="sshpass -p "$pwd" ssh "$user'@'$ip
            `$cmd`

            # sshpass -p "XXX" ssh user@IP
            ls 

        else
            echo 'no exist '$1
            list
        fi 

    done
    toolsLine
}


# 列出ssh列表
function list(){
    toolsLine
    local len=${#ips[@]}
    echo 'Servers list('$len') : '

    for ((i=0; i<$len; i++))
    do
        local name=${names[$i]}
        local ip=${ips[$i]}
        local user=${uses[$i]}
        local pwd=${pwds[$i]}
        echo "++"$ip" + "$name" + "$user" + "$pwd 
    done
    toolsLine

}


# 单独执行文件时操作如下 引入时提示
_temp='do_server.sh'
if [[ $0 =~ $_temp ]]
then
    server_init $@
else
    echo 'source '$_temp
fi 



