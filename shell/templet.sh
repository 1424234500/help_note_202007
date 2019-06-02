#!/bin/bash  
###########################################
#do
#一些常用简单功能脚本
#./do commit <help>
###########################################
source constant.sh
source tools.sh 






##-----------------------------------------

function templet_main(){ 
    echo
    toolsShow $@
    ##########################do something yourself
    init $@
    ##########################
    toolsLineLong 
    echo
}

function templet_init(){  
    templet_show    

    
}

function templet_show(){  
    echo '$0'">>"$0
    echo '$*'">>"$*
    echo '$@'">>"$@    
    echo '$#'">>"$# 
    echo '$$'">>"$$ 
}


 
#start
templet_main $@

