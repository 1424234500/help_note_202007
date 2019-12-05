# !/bin/bash  
########################################### 
# ./do function <help>
# About:
# 
# 
###########################################
source constant.sh
source tools.sh
#########################################


function template_functionName(){
    echo $#
    
}   

function template_main(){
    echo $@
} 



function do_init(){  
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
        show
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


 


# 单独执行文件时操作如下 引入时提示
_temp='do_template.sh'
if [[ $0 =~ $_temp ]]
then
    do_main $@
else
    echo 'source '$_temp
fi 
