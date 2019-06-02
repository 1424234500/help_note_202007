
#My Shell Tools.



_toolsres='toolsTemp.txt'

function out(){
    echo -e `date "+%Y-%m-%d %H:%M:%S" `' '$@
}

# start a function or a system call &
# thread toolsShow 
function thread(){
    {
        eval $*
    } & 
}
# start a function or a system call nohup &
# call "echo aasdb"
function call(){
    local tools_out='nohup '$*' & '
    out $tools_out
    eval $tools_out
}
# do the cmd and show cmd
# do "echo asdf"
function doShell(){
    out $*
    eval $*
}


#toolsShow $@
function toolsShow(){
    toolsLineLong
    out ">>shell: "${0}
    out ">>params: "$*     
    toolsLineShort  
}

#toolsShowMethod $method ${params[*]}
function toolsShowMethod(){ 
    #toolsLineShort  
    out ">>method: "${1}
    out ">>params: "${2}     
    toolsLineShort  
}
 
#toolsMakefile filename.txt
function toolsMakefile(){
    filename=$1
    if [ "$filename" = "" ]
    then
        out 'toolsMakefile create a file must with a filename '
        exit
    else
        if [ ! -f "$filename" ]    # 这里的-f参数判断$myFile是否存在
        then
            touch "$filename"
        fi
    fi
}


#Get params 
#toolsGet $1 <default value>
function toolsGet(){
    res=$1
    default=$2
    if [ "$res" = "" ]
    then
        res=$2
        if [ "$res" = "" ]
        then
            res=''
        fi
    fi
    echo "$res" > $_toolsres    
    return 0
}
#toolsMakestr '--' '10'
function toolsMakestr(){
    res=''
    str=$1
    count=$2 
    if [ -z "$count" ]
    then
        out 'toolsMakestr eg: toolsMakestr "" "10" '
        res=''
    else
        for ((i=1; i<=$count; i++))
        do
            res=$res''$str
        done
    fi  
    
    echo $res > $_toolsres
    return 0
}
#toolsMakestr 'q' 3 

#Show the split line such as '-----------'
#toolsLine <10>
function toolsLine(){
    local split='-'
    local str=''
    local len=$1
    if [ "$len" = "" ]
    then
        len=16
        #echo "len is not set!"
#    else
#        echo
#        #echo "len is set !"
    fi
    
    for ((tools_i=0; tools_i<$len; tools_i++))
    do
        str=$str""$split
    done

    out $str
}
 
function toolsLineLong(){
    toolsLine 32
}

function toolsLineShort(){
    toolsLine 8
}

function start_main(){
    echo $_temp' start_main of args:'
    echo $@
}

# 单独执行文件时操作如下 引入时提示
_temp='tools.sh'
if [[ $0 =~ $_temp ]]
then
    start_main $@
else
    echo 'source '$_temp
fi 











