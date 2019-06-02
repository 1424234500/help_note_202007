# !/bin/bash  
########################################### 
# ./do function <help>
# About:
# 
# 
###########################################
source constant.sh
source tools.sh



function template_functionName(){
    echo $#
    
} 





function template_main(){
    echo $@
} 

# 单独执行文件时操作如下 引入时提示
_temp='do_template.sh'
if [[ $0 =~ $_temp ]]
then
    template_main $@
else
    echo 'source '$_temp
fi 
