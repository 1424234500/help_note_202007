#!/bin/bash
###########################################
#git版本差异化 期间类补丁 文件覆盖制作
#
#
##-------------------------------- 
 
#app 下面复制到desktop下面 而git路径在echat_desktop下面所以需要路径转换映射
dirs_from=('/mnt/e/workspace/echat_desktop'     '/mnt/e/workspace/OBCP-Server'         )   #git目录
dirs_diff=('/mnt/e/workspace/echat_desktop/app' '/mnt/e/workspace/OBCP-Server/db/ddl;/mnt/e/workspace/OBCP-Server/db/dml;/mnt/e/workspace/OBCP-Server'    )   #源路径截取 把源文件app下面的东西按照原有路径层次同步到目标路径
dirs_to=('/mnt/e/workspace/obcpweb/pro/desktop' '/mnt/e/workspace/obcpdb/TABLE;/mnt/e/workspace/obcpdb/DATA;/mnt/e/workspace/obcpweb'    )   #覆盖同步路径
dir_open=''

_make_path='/mnt/e/make'    # 补丁包路径
# //git 日志格式化
# git log --pretty=format:"%H %an %cd %cr"
# git log --pretty=format:"%H %an %cd %cr" --after="2018-4-09 17:37:42" --before="2022-11-06 17:45:42"
# aa6492c71ea38371d95f26fc705ebc9be1edfd19 walker Wed Apr 11 10:41:03 2018 +0800 36 minutes ago
# e4514488d2772ea2acb8e62442eaea6e3331dbec walker Tue Apr 10 15:34:20 2018 +0800 20 hours ago
# e68d8075414572e8097e312dd02e2dfefc45a358 walker Mon Apr 9 18:42:27 2018 +0800 2 days ago
# //使用diff导出差异文件列表
# git diff aa6492c71ea38371d95f26fc705ebc9be1edfd19 e4514488d2772ea2acb8e62442eaea6e3331dbec --stat --name-only

# ./help_git.sh time_from <time_to>     <test>
# ./help_git.sh branch_from branch_to <test>
function make(){
    sta=0
    dotype='do'
    time_from='from'
    time_to='to'

    if (( $# >= 1 ))
    then
        str1=$1
        if [[ "$1" =~ [0-9]{4}-[0-9]{1,2}-[0-9]{1,2}.* ]]
        then  # 第一个参数为时间
            sta=1
            time_from=$1
            if (( $# >= 2 ))    #时间 <时间> / <类型>
            then
                if [[ "$2" =~ [0-9]{4}-[0-9]{1,2}-[0-9]{1,2}.* ]]
                then
                    time_to=$2
                    if (( $# >= 3 ))    # 时间 时间 <类型>
                    then
                        if [[ "$3" =~ test|show ]]
                        then
                            dotype=$3
                        else
                            sta=999
                        fi
                    fi
                elif [[ "$2" =~ test|show ]]    #时间 <类型>
                then
                    time_to=`date "+%Y-%m-%d" `
                    dotype=$2
                else
                    sta=999
                fi
            else # 时间
                time_to=`date "+%Y-%m-%d" `
            fi
        elif (( ${#str1}  < 6 ))
        then
            sta=1
            time_from=`date "+%Y-%m-%d" -d yesterday`
            time_to=`date "+%Y-%m-%d" `
            dotype=$1
        else  # 分支 分支
            if (( $# >= 2 ))
            then
                sta=2
                if (( $# >= 3 ))
                then
                    if [[ "$3" =~ test|show ]]
                    then
                        time_from=$1
                        time_to=$2
                        dotype=$3
                    else
                        sta=999
                    fi
                else
                    time_from=$1
                    time_to=$2
                fi
            else
                sta=999
            fi
        fi
    else    # 无参数 默认时间昨天-now
        sta=1
        time_from=`date "+%Y-%m-%d" -d yesterday`
        time_to=`date "+%Y-%m-%d" `
    fi

    echo 'from:'$time_from' to:'$time_to' dotype:'$dotype' sta:'$sta

    if (( $sta == 1 ))
    then
        rm $_make_path -R
        makeTime $time_from $time_to $dotype
    elif (( $sta == 2 ))
    then
        rm $_make_path -R
        makeBranch $time_from $time_to $dotype
    else
        show
    fi

}
function show(){
    echo '
# Eg:    
# ./help_git.sh 2018-06-01 <2018-09-02> <test>
# ./help_git.sh adjdadlakfjdkafj dajflajsdflasdjfasdklf <test>
    '
}
function makeTime(){
    dir_open=`pwd`  #记录使用脚本的路径

    echo '时间 '$1' -> '$2

    # echo ${#dirs_from[@]}
    for ((i=0; i<${#dirs_from[@]}; i++))
    do
        local dir_from=${dirs_from[$i]}
        local dir_diff=${dirs_diff[$i]}
        local dir_to=${dirs_to[$i]}   
        line
        echo '同步开始 "'$dir_diff'" -> "'$dir_to'"'
        line
        logTime "$dir_from" "$dir_diff" "$dir_to" $1 $2 $3 &   #异步同步等待 
        wait

        echo '同步完成 '$dir_diff' -> '$dir_to
        line
        echo
    done
    cd $dir_open    #回到当初位置
}
function makeBranch(){
    dir_open=`pwd`  #记录使用脚本的路径

     
    echo '版本 '$1' -> '$2

    # echo ${#dirs_from[@]}
    for ((i=0; i<${#dirs_from[@]}; i++))
    do
        local dir_from=${dirs_from[$i]}
        local dir_diff=${dirs_diff[$i]}
        local dir_to=${dirs_to[$i]}   
        line
        echo '同步开始 '$dir_diff' -> '$dir_to 
        line
        cd $dir_from
        diff $1 $2 $dir_from $dir_diff $dir_to $3 &   #比对分支差异文件并复制移动

        wait

        echo '同步完成 '$dir_diff' -> '$dir_to
        line
        echo
    done
    cd $dir_open    #回到当初位置
}
function logTime(){
    # echo $@
    local nowdir=$1
    local diffdir=$2
    local todir=$3
    local timefrom=$4
    local timeto=$5
    local dotype=$6
    cd $nowdir  #进入源目录
    local cmd="git log --pretty=format:%H --after=$time_from --before=$time_to"
    echo $cmd
    line
    local branchs=`$cmd`    #期间分支集合
    # echo $branchs
    git log --pretty=fromat:"%h %an %cr %s " --after=$time_from --before=$time_to

    local arr=(` echo $branchs | tr ' ' "\n" `)
    if (( ${#arr[@]} < 2 ))
    then
        echo '期间未提交新的分支'
        line
    else
        local branch_from=${arr[-1]}
        local branch_to=${arr[0]}
        diff $branch_from $branch_to $nowdir $diffdir $todir $dotype   #比对分支差异文件并复制移动
    fi    
} 
function diff(){
    # echo $@
    if [ "$#" = "6" ] 
    then
        local nowdir=$3
        local diffdir="$4" # 'dir/obcp-server/db/dml dir/obcp-server/db/ddl dir/obcp-server'
        local todir="$5"   # 'dir/db/dml             dir/db/ddl             dir/obcpweb'
        local dotype=$6
        line
        local cmd="git diff $1 $2 --stat --name-only"
        echo $cmd
        local files=( `$cmd` )
        line
        echo '共计差异文件 '${#files[@]}' 个. '
        line
        local nowdirLen=${#nowdir}+1  #/斜杠占位

        local todirs=(`echo $todir|tr ";" "\n"`)
        local diffdirs=(`echo $diffdir|tr ";" "\n"`)

        echo '源路径:'$nowdir
        for ((cc=0; cc< ${#todirs[@]}; cc++))   #有3种移动规则
        do
            echo '移动规则 ['$cc'] '${diffdirs[$cc]}' -> '${todirs[$cc]}
        done
        line
        # echo $todir' '$diffdir
        local delFileCount=0    # 差异删除文件数
        local cpFileCount=0     # 差异覆盖/添加文件数
        local delFileCountRel=0 # 实际删除文件数
        for ((i=0; i<${#files[@]}; i++))    #每一个文件需要决定去处
        do
            local itemdiff=${files[$i]}                    #app/modules/chat/services/chatService.js
            local fileFromPath=$nowdir'/'$itemdiff         #/mnt/e/workspace/echat_desktop/app /modules/chat/services/chatService.js 源文件真实路径

            for ((cc=0; cc< ${#todirs[@]}; cc++))   #有3种移动规则
            do
                local todirnow=${todirs[$cc]}
                local diffdirnow=${diffdirs[$cc]}
                # echo 'fileFrom:'$fileFromPath' diff:'$diffdirnow
                if [[ "$fileFromPath" =~ .*"$diffdirnow".* ]]
                then
                    if [[ "$dotype" =~ test|show ]]
                    then
                        todirnow=$_make_path
                        # echo '测试差异，处理文件到目录'$todirnow'，生成补丁文件夹'
                        mkdir $todirnow -p
                    fi   

                    local diffdirLen=${#diffdirnow}+1  #/斜杠占位
                    local newItemDiff=${fileFromPath:$diffdirLen}  #                                   /modules/chat/services/chatService.js 目标相对路径
                    local fileToPath=$todirnow'/'$newItemDiff #/mnt/e/workspace/obcpweb/pro/desktop    /modules/chat/services/chatService.js 目标真实路径
                    
                    # echo $i' '$fileFromPath' -> '$fileToPath
                    mkFileDir $fileToPath   #确保文件所在目录存在 否则cp失败
                    if [ -f $fileFromPath ] # 源文件存在 
                    then
                        printf "% 3d [$cc] cp ${fileFromPath:$nowdirLen} \n" "$i"
                        cpFileCount=$[cpFileCount+1]
                        # echo "cp $fileFromPath $fileToPath "
                        cp $fileFromPath $fileToPath #-v    修改/添加文件 则覆盖文件
                    else
                        echo "$i [$cc] rm ${fileFromPath:$nowdirLen}"
                        delFileCount=$[delFileCount+1]
                        # echo "rm $fileToPath"
                        if [ -f $fileToPath ] # 目标文件存在 
                        then
                            delFileCountRel=$[delFileCountRel+1]
                            rm $fileToPath  # 删除文件 源不存在了 目标存在的情况 就删除目标文件
                        fi
                    fi 
                    break
                fi   
            done
        done


        line
        echo "差异添加/修改: $cpFileCount  差异删除: $delFileCount  实际删除文件数除: $delFileCountRel"
    else
        echo '比对分支并移动需要 版本号from to 和 源路径 目标路径 args:'$@
    fi
}



function mkFileDir(){
    myPath=$1
    local fileDir=${myPath%/*}
    if [ ! -d $fileDir ]; then
        mkdir $fileDir -p
    fi
}

function line(){
    echo "---------------------------------"
}

function help(){
    echo "-------make --------"
}

function git_main(){
    echo
    ##########################do something yourself
    git_init $@
    echo
}

function git_init(){
    method=$1
    if [[ "$method" != "" ]]
    then
        rootParams=($@)
        params=(${rootParams[@]:1})
        $method ${params[@]}
    else
        help 
    fi
} 


# 单独执行文件时操作如下 引入时提示
_temp='help_git.sh'
if [[ $0 =~ $_temp ]]
then
    # git_main $@
    make $@
else
    echo 'source '$_temp
fi 