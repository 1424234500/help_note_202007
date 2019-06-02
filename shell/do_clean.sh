# !/bin/bash  
########################################### 
# ./do function <help>
# About:
# 清理临时文件工具
# 
###########################################
source constant.sh
source tools.sh



function clean_clean(){
    clean_cleanExe $_opencv
    clean_cleanExe $_server
    clean_cleanExe $_python
    a=1
}
function clean_cleanExe(){
    ##删除python临时文件 *.pyc res_* build目录
    dir=$1
    cd $dir

    echo 'clean: '$dir' rm res*, *.pyc, p*g, build -R, _* -R'
    rm res* >> $log_temp
    # rm *.pyc >> $log_temp
    rm p*g >> $log_temp
    rm build -R >> $log_temp
    rm _* -R >> $log_temp
}

# project_exefun clean_javaProject <base>
function clean_cleanJava(){
    do_project_exefun clean_cleanJavaProject $@ #<base>
} 
function clean_cleanJavaProject(){
    echo '------------------------'
    echo 'clean: '$1
    #echo ' rm build, bin, ccandroid/bin, cchttp/build, ccserver/build, cchttp/WebContent/WEB-INF/classes -R'

    cd $1
    # clean_rm build 
    # clean_rm bin 
    # clean_rm WebContent/WEB-INF/classes 
    clean_rm ccandroid/bin  
    # clean_rm cchttp/build 
    # clean_rm cchttp/WebContent/WEB-INF/classes 
    # clean_rm ccserver/build 
}
function clean_rm(){
    myPath=$1
    if [ -f $myPath ]; then
        echo 'rm '"$myPath"
        rm $myPath
    fi 
    # 这里的-f参数判断$myFile是否存在 是否为文件
    if [ -d $myPath ]; then
        echo 'rm '"$myPath"' -R '
        rm $myPath -R
    fi

}





# 单独执行文件时操作如下 引入时提示
_temp='do_clean.sh'
if [[ $0 =~ $_temp ]]
then
    start_main $@
else
    echo 'source '$_temp
fi 



