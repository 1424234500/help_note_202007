#!/bin/bash  
###########################################
# My init tools 
# 初始化cmd用户目录下的快捷方式到指定位置
# 常用配置
###########################################
source tools.sh
source constant.sh
##-----------------------------------------

function main(){ 
    echo
    toolsLineLong
    echo ">>shell: ${0}"
    #$@与$*相同，使用时加引号，返回每个参数,$?获取函数返回值
    echo ">>params: $*"     
    toolsLineShort  
    ##########################do something yourself
    init $@
    ##########################
    toolsLineLong 
    echo
}

function init(){
   initLn $@
    
}
#initLn /shell 
function initLn(){
    toolsGet $1 '/mnt/e' 
    root=`cat $_toolsTempFileName`
    echo 'ln root '
    ln -s $root '/root'
	ln -s $root '~/root'
	
    echo 'ln shell '
    ln -s $root'/help_note/shell/' '/shell' 
    ln -s $root'/help_note/shell/' '~/shell' 
    
    rm $_toolsTempFileName
}




 
#start
main $@

