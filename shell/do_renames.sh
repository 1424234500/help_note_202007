#!/bin/bash  
########################################### 
#./do renames <help>
#批量文件重命名工具 
#正则规则 筛选 文件 
#按照正则规则 拆分 字符串 动态算法拼接生成 规则文件名
#是否 子目录 递归
###########################################
source constant.sh
source tools.sh 






##-----------------------------------------

function renames_main(){ 
    echo
    toolsShow $@
    ##########################do something yourself
    renames_rename $@
    ##########################
    toolsLineLong 
    echo
}

function renames_rename(){
    path=$1
    echo './do rename test/ "est"   '
    if [ ! -d $path ]
    then 
        echo '参数1必须为目录路径<参数2=test eg: Tetest.txt -> Te.txt > <png后缀修改>'
        exit
    fi
    if [ -z $2 ]
    then
        echo '<参数2=test eg: Tetest.txt -> Te.txt > '
        exit
    fi
    
    _rootDir=`pwd`
    realPath=$_rootDir"/"$path 
    echo "now path: "$realPath
    
    echo 'Files>>'
    for obj in `ls $realPath`
    do
        path=$realPath"/"$obj
        if [ -f "$path" ]
        then
            echo $path" file"
            renames_rename_exe $realPath $obj $2 $3
        fi 
    done
    echo 'Directorys>>'
    for obj in `ls -d $realPath`
    do
        #obj=$realPath"/"$obj 
        if [ -d "$obj" ]
        then
            echo $obj" directory" 
        fi 
    done
}

count=0
function renames_rename_exe(){
    dir=$1
    obj=$2
    path=$dir'/'$obj  
    if [ -n "$4" ]
    then
        rightStr=${obj%.*}    #.bat
        newName=$rightStr'.'$4
        echo $obj'>>'$newName
                
                
        toPath=$dir'/'$newName 
        mv $path $toPath
        count=${count+1}
        return 1
    fi
    
    
    reg=$3      #'Active'                    #bbb
    regular='.*'$reg'.*' 
    echo $path
    if [[ "$obj" =~ $regular ]]  
    then  #Filebbbxxxx.bat
        leftStr=${obj%%${reg}*}    #File
        rightStr=${obj#*${reg}}    #xxxx.bat
        rightStr=${rightStr##*.}    #.bat

        #echo 'leftStr: '${leftStr}
        #echo 'rightStr: '$rightStr 
        newName=$leftStr'-'$count'.'$rightStr
        echo $obj'>>'$newName
                
        toPath=$dir'/'$newName 
        mv $path $toPath
        count=${count+1}
    fi
    
    
}

function renames_show(){
    path='imgs'
    _rootDir=`pwd`
    realPath=$_rootDir"/"$path 
    echo "now path: "$realPath
    for obj in `ls  $realPath`
    do
        obj=$realPath"/"$obj
        if [ -f "$obj" ]
        then
            echo $obj" file"
        elif [ -d "$obj" ]
        then
            echo $obj" directory"
        else
            echo $obj" not file or directory"
        fi 
    done
}

#
 

function start_renames(){
    
    renames_main $@

}
# 单独执行文件时操作如下 引入时提示
_temp='do_renames.sh'
if [[ $0 =~ $_temp ]]
then
    start_renames $@
else
    echo 'source '$_temp
fi 
