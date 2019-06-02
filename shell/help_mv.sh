#!/bin/bash  
########################################### 
#./do dirfile <help>
#文件筛选   移动到 某个目录
#全文件
#递归
###########################################
source constant.sh
source tools.sh 

##-----------------------------------------

function dirfile_main(){ 
    echo
    toolsShow $@
    ##########################do something yourself
    dirfile_init $@
    ##########################
    toolsLineLong 
    echo
}
dirfile_level='0'
dirfile_ifcop='0'
dirfile_reg='.*'
function dirfile_init(){
    echo '<<eg: ./do_dirfile.sh test<dir> reg<’^.*aaa.*‘> 0<show dir level> 0<if show file> '
    
    path=$1    
    
    if [ -n "$3" ] 
    then
        dirfile_level=$3
    fi 
    if [ -n "$4" ] 
    then
        dirfile_ifcop=$4
    fi 
    if [ -n "$2" ] 
    then
        dirfile_reg=$2
    fi 
    
    if [ ! -d "$path" ] 
    then
        echo '参数1为目录'
        return 1
    fi 
    # realPath=`pwd`'/'$path
    realPath=$path
    echo 'rootPath: '$realPath 
    dirfile_showdir $realPath '1'
    echo '总文件数量: '$fileCount
    
}
function dirfile_showdir(){
    realPath=$1
    nowLevel=$2
    
    if [[ $nowLevel > $dirfile_level && $dirfile_level > 0 ]]  
    then
        return 0 
    fi
    
    if [ ! -d "$1" ] 
    then
        return 0 
    fi
    toolsMakestr '-' ${#1} #$nowLevel
    res=`cat $_toolsres`
    # echo $1 #'    level:'$nowLevel'      dir_level:'$dirfile_level
    
    if [[ $dirfile_ifcop > 0 ]]
    then
        arr=(`ls $1`)
        len=${#arr[@]}
        printf 'files:% 3d  '$1"\n" "$len"
    else
        #echo $res'====file>>'
        echo '>>>'$1
        local i=0
        for obj in `ls $1`
        do
            path=$1'/'$obj
            if [ -f "$path" ]
            then 
                if [[ $obj =~ $dirfile_reg ]] 
                then
                    i=$[i+1]
                    printf "% 3d"$res''$obj"\n" "$i"
                    doFile $1 $obj
                fi  
            fi 
        done
    fi
    #echo $res'++++dire>>'
    for obj in `ls $1`
    do 
        path=$1'/'$obj 
        if [ -d "$path" ]
        then 
            #echo $path 
            nowLevel=`expr $nowLevel + 1`
            dirfile_showdir $path  $nowLevel
        fi 
    done 
}
 
fileCount=0
function doFile(){
    local path=$1
    local fileName=$2
    local _rootDir=`pwd`
    local filePath=$path'/'$fileName 
    mv $filePath /mnt/e/movie/WALKER/
    # count=$[count+1]
    fileCount=`expr $fileCount + 1`
}
 

function controlDir(){ 
    if [ ! -d "$1" ] 
    then
        return 0 
    fi
    path=$1
    for obj in `ls $1`
    do
        path=$1'/'$obj
        if [ -f "$path" ]
        then 
            if [[ $obj =~ $dirfile_reg ]] 
            then
                echo $res''$obj
            fi  
        fi 
    done
    for obj in `ls $1`
    do 
        path=$1'/'$obj 
        if [ -d "$path" ]
        then 
            dirfile_showdir $path  $nowLevel
        fi 
    done 
} 


# 单独执行文件时操作如下 引入时提示
_temp='help_mv.sh'
if [[ $0 =~ $_temp ]]
then
    dirfile_main $@
else
    echo 'source '$_temp
fi 


