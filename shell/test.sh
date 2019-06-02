#!/bin/bash  
###########################################
#test
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
function dirfile_showdir(){
   # realPath=$1
    echo 'ls:'$1   
    for obj in `ls $1`
    do 
        path=$1'/'$obj 
        if [ -f "$path" ]
        then  
            echo ' file:'$path   
        fi  
    done 
    for obj in `ls $1`
    do 
        path=$1'/'$obj 
        if [ -d "$path" ]
        then  
            echo '    dir:'$path  
            dirfile_showdir $path  
        fi  
    done 
} 


function init(){
    #realPath='/home/walker/root/help_note/shell/test/'
    #dirfile_showdir $@


    a='a'
    b='2'
    if [[ $a > $b && $a < 5 ]]
    then
        echo '4 > 2' 
    fi
    
    


}



#start
main $@

