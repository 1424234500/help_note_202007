# !/bin/bash  
########################################### 
# ./do function <help>
# About:
# 
# 
###########################################
source constant.sh
source tools.sh



function do_start_sftware_start(){
    toolsLineLong


    local arr=( 
    '/home/walker/software/eclipse/eclipse'
    '/home/walker/software/tomcat7/bin/startup.sh'
#    'do update'
    'gedit'
    '/home/walker/software/redis-5.0.3/src/redis-server'
    '/home/walker/software/smartgit/bin/smartgit.sh' 
     )
     
    out 'start linux software '${#arr[@]}
    toolsLineLong
    for ((i=0; i<${#arr[@]}; i++))
    do
        local item=${arr[$i]}
        out 'Start '$i"\t"$item 
        
        local nowdir=`pwd`
        
#        local ss=($item)
#        local len=${#ss[*]}
#        if (( $len > 1 ))
#        then
#            out 'stack push dir: '$nowdir 
#            cd ${ss[0]}
#            out 'turn to dir: '`pwd`
#            item=${item:${#ss[0]}}
#        fi
#        
        local key=${item##*/}
        local cmd="ps -elf | grep -v grep | grep '$key'"
        out $cmd
        local res=`eval $cmd`
        out $res        
        if [[ $res == "" ]]
        then
#            call $item
            
            local tools_out='nohup '$item' & '
            out $tools_out
            eval $tools_out
#            out $pid
        else
            pid=`ps -elf | grep "$key"  | grep -v grep | awk '{print $4}' `   #获取jmap 关键词pid
            out '###########have started pid '$pid'##########################'
            echo 

        fi
        
#        if (( $len > 1 ))
#        then
#            cd $nowdir
#            out 'stack pop dir: '`pwd`
#        fi
        
        toolsLineLong
    done    
 
    out 'start linux software over '
    toolsLineLong
} 

function startCochat(){
    nowdir=`pwd`
    echo 'stack pwd:' $nowdir
    cd /home/walker/help/python/
    pwd
    nohup python autoCochatCph.py >> ~/auto.log &
    cd $nowdir
    pwd
}



function do_start_sftware(){
    echo $@
} 

# 单独执行文件时操作如下 引入时提示
_temp='do_start_software.sh'
if [[ $0 =~ $_temp ]]
then
    do_start_sftware_start $@
else
    echo 'source '$_temp
fi 
