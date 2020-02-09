#!/bin/bash
###########################################
#do
#一些常用简单功能脚本
#配置启动脚本命令cmd
#配置日志文件路径logfile
#./do start <help><stop><show><log><restart>

##-----------------------------------------
cmd='mysql -u root -proot '
temp='sql'
about="
Ctrl the mysql dbs tables.    \n
Usage: 
./mysql.sh [ create | truncate | show | drop | help ] [ps grep database]   \n
    \t  create   \t  batch create tables   \n
    \t  drop   \t  batch drop tables   \n
    \t  truncate walker    \t  batch truncate tables    \n
    \t  show walker \t  show all the database's tables    \n
    \t  help    \t  show this   \n
"

##------------------------------------------

function show(){ 
    echo '查看所有数据库 所有表  mysql: '"${cmd} key: ${key}"
    type="show"
    temp_sqls="${temp}/${type}"
    [ ! -d ${temp_sqls} ] && mkdir -p ${temp_sqls}
	if [ -z $1 ];then
		dbs=(`${cmd} -e "show databases;" `)
	else 
	    dbs=(`${cmd} -e "show databases;" | grep ${key} `)
	fi
    for ((i=0; i < ${#dbs[@]}; i++))
    do
        item=${dbs[$i]}
        sql="${temp_sqls}/${item}"
        echo "make ${type} sql of db-file: ${sql}"
        echo "use ${item};" > ${sql}
        tables=(`${cmd} -e "use ${item}; show tables;" | grep -v Table | awk '{print $0}'`)
        echo "${type} size ${#tables[@]}"
        echo "${type} size ${#tables[@]}" >> ${sql}
        ${cmd} -e "use ${item}; show tables;" | grep -v Table | awk '{print $0}'
        ${cmd} -e "use ${item}; show tables;" | grep -v Table | awk '{print $0}' >> ${sql}
    done
}
function truncate(){
    echo '清理所有数据库 所有表 数据 mysql: '"${cmd}"
    type="truncate"
    temp_sqls="${temp}/${type}"
    [ ! -d ${temp_sqls} ] && mkdir -p ${temp_sqls}
    dbs=(`${cmd} -e "show databases;" | grep $1 `)
    for ((i=0; i < ${#dbs[@]}; i++))
    do
        item=${dbs[$i]}
        sql="${temp_sqls}/${item}"
        echo "make ${type} sql of db-file: ${sql}"
        echo "use ${item};" > ${sql}
        ${cmd} -e "use ${item}; show tables;" | grep -v Table | awk '{print "truncate table "$0";"}' >> ${sql}
        echo "${type}"
        cat ${sql}
        ${cmd} < ${sql}
    done
}
function drop(){
    echo '删除所有数据库 所有表 mysql: '"${cmd}"
    type="drop"
    temp_sqls="${temp}/${type}"
    [ ! -d ${temp_sqls} ] && mkdir -p ${temp_sqls}
    dbs=(`${cmd} -e "show databases;" | grep $1 `)
    for ((i=0; i < ${#dbs[@]}; i++))
    do
        item=${dbs[$i]}
        sql="${temp_sqls}/${item}"
        echo "make ${type} sql of db-file: ${sql}"
        echo "use ${item};" > ${sql}
        ${cmd} -e "use ${item}; show tables;" | grep -v Table | awk '{print "drop table "$0";"}' >> ${sql}
        echo "${type}"
        cat ${sql}
        ${cmd} < ${sql}
    done
}
function create(){
    echo '新建数据库 所有表 mysql: '"${cmd}"
    
    type="create"
    temp_sqls="${temp}/${type}"
    [ ! -d ${temp_sqls} ] && mkdir -p ${temp_sqls}
    dbs=(`${cmd} -e "show databases;" | grep $1 `)
    for ((i=0; i < ${#dbs[@]}; i++))
    do
        item=${dbs[$i]}
        sql="${temp_sqls}/${item}"
        echo "make ${type} sql of db-file: ${sql}"
        echo "use ${item};" > ${sql}
        ${cmd} -e "use ${item}; show tables;"  >> ${sql}
        for j in `seq 0 3`
        do
            echo "
                    create table w_test_sh_${j} (
                        id varchar(40),
                        name varchar(200),
                        primray key(id)
                    } ENGINE=MyISAM DEFAULT CHARSET=utf8;
                " >> ${sql}
        done
        
        echo "${type}"
        cat ${sql}
        ${cmd} < ${sql}
    done
}
function help(){
    line
    echo -e $about
    line
	eval ${cmd}
}
function line(){
    echo "---------------------------------"
}

function do_main(){
    echo
    ##########################do something yourself
    do_init $@
    echo
}

function do_init(){
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


#start
do_main $@
