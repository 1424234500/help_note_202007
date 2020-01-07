//文件配置 /etc/my.cnf
my.ini 或 my.cnf
	default_character=utf8
	[mysqld]
	
    # disable_ssl
    skip_ssl
    #总连接数
    max_connections=512
	long_query_time=2	//慢查询时间定义s 
	//5.5如下配置
	show-query-log=on
	show_uery_log_file="mysql_slow_query.log"

//启动mysql
su mysql
--mkdir data
./bin/mysqld --initialize-insecure  //这是初始化一个用户名为root的用户，没有密码
./bin/mysqld &



//修复
mysqlcheck --auto-repair -A -o -uroot -pyigeorg
//登录
mysql -u root -proot
mysql <-h 127.0.0.1> -u root -ppasswd <-P 3306>
mysqladmin -u用户名 -p旧密码 password 新密码
//shell调用sql
mysql -u root -proot -e "show databases;"
//shell调用sql文件
use abccs;
select * from mytable;
select name,sex from mytable where name=‘abccs‘;
mysql -u root -proot < mytest.sql 

//管理员密码初始化
ALTER USER'root'@'%'IDENTIFIED WITH mysql_native_password BY 'root';
FLUSH PRIVILEGES;


//变量设置 查看 mysql当前服务进程有效
show variables like 'max_connections'
set global max_connections=1000;
--查看中文支持
show variables like 'character%'; 
//数据库 表 show
select USER(), version(),current_date();
SHOW DATABASES; //创建表 赋予 远程登录权限
CREATE DATABASE IF NOT EXISTS walker default charset utf8 COLLATE utf8_general_ci;
CREATE DATABASE IF NOT EXISTS walker0 default charset utf8 COLLATE utf8_general_ci;
CREATE DATABASE IF NOT EXISTS walker1 default charset utf8 COLLATE utf8_general_ci;

//登录密码权限 用户分配权限
select host, user, grant_priv,super_priv from mysql.user;
--初始化管理员root
UPDATE mysql.user SET Grant_priv='Y', Super_priv='Y' WHERE User='root';
FLUSH PRIVILEGES;
GRANT ALL ON *.* TO 'root'@'localhost';

create user 'walker'@'%' identified by 'qwer';
create user 'walker0'@'%' identified by 'qwer';
create user 'walker1'@'%' identified by 'qwer';
GRANT ALL PRIVILEGES ON *.* TO 'walker'@'%' ;
GRANT ALL PRIVILEGES ON *.* TO 'walker0'@'%' ;
GRANT ALL PRIVILEGES ON *.* TO 'walker1'@'%' ;

DROP DATABASE walker;
USE walker;

//建表 查表 描述
CREATE TABLE  IF NOT EXISTS  test (id VARCHAR(20), name CHAR(10));
drop table test;
SHOW TABLES;
DESCRIBE test; 
desc test;
show table status like 'test';
show create table student;  //查看表create创建语句

insert into test values('001', 'walker');
update test set name='walker1';
//分页查询
select * from test;
select * from test limit 0,1;
//查看列名
select COLUMN_NAME from information_schema.COLUMNS where table_name = 'test';   
NOT NULL auto_increment,

//常用函数 
ifnull  nvl

//查询
//行号rownum
select rownum from (select  (@i:=@i+1) rownum from  information_schema.COLUMNS t ,(select   @i:=0) it ) t  where rownum < 10 ;       
select lpad(level, 2, '0') lev from (select  (@i:=@i+1) level from  information_schema.COLUMNS t ,(select   @i:=0) it ) t  where level<=24     ;
//代码java执行替换
select lpad(level, 2, '0') lev from (select  (@i/*'*/:=/*'*/@i+1) level from  information_schema.COLUMNS t ,(select   @i/*'*/:=/*'*/0) it ) t  where level<=24     ;
用符号:/*'*/:=/*'*/转换:=

//安全模式
safemode
--Error Code: 1175. You are using safe update mode and you tried to update a table without a WHERE that uses a KEY column To disable safe mode, toggle the option in Preferences -> SQL Queries and reconnect.
--这是因为MySql运行在safe-updates模式下，该模式会导致非主键条件下无法执行update或者delete命令
--查看是否开启了安全模式
show variables like ‘SQL_SAFE_UPDATES‘;
--关闭
SET SQL_SAFE_UPDATES = 0;



mysqldump -uroot -proot student > student.sql;	//导出 导入

//Master/Slave  主备？ 数据库之间的同步 <异步处理>
grant file on *.* to 'root'@' 1222.122.1.1' identified by 'password';
grant replication master on *.* ....


//mysql定位
/usr/local/Cellar/mysql/5.7.17	//mac
whereis mysql	//定位
locate mysql 
//授权登陆


//主键自动索引pk > 数字索引index > 字符串索引index > 组合字段索引merge_index
explain select * from student where id = 12;	//explain sql-select
system > const > eq_ref > ref > fulltext > ref_or_null > index_merge > unique_subquery > index_subquery > range > index > all

	
//显示引擎 
//innorDB		行锁+表锁	事物  
//<MY>ISAM		表锁		
//MERGE         合并逻辑表INSERT_METHOD=LAST/FIRST/0不允许插入 分表
--引擎 

show engines;

mysql的存储引擎包括：MyISAM、InnoDB、BDB、MEMORY、MERGE、EXAMPLE、NDBCluster、ARCHIVE、CSV、BLACKHOLE、FEDERATED等，其中InnoDB和BDB提供事务安全表，其他存储引擎都是非事务安全表。

MyISAM: 表级锁，用户在操作myisam表时，select，update，delete，insert语句都会给表自动加锁，如果加锁以后的表满足insert并发的情况下，可以在表的尾部插入新的数据。也可以通过lock table命令来锁表，这样操作主要是可以模仿事务，但是消耗非常大，一般只在实验演示中使用。
InnoDB ： 事务和行级锁，是innodb的最大特色。
事务的ACID属性：atomicity,consistent,isolation,durable。
并发事务带来的几个问题：更新丢失，脏读，不可重复读，幻读。
事务隔离级别：未提交读(Read uncommitted)，已提交读(Read committed)，可重复读(Repeatable read)，可序列化(Serializable)

MyISAM引擎是不支持事务的。如果你在使用Spring+Hibernate事务回滚无效。可以联想一下mysql使用的引擎是那种。
InnoDB存储引擎提供了具有提交、回滚和崩溃恢复能力的事务安全。但是对比Myisam的存储引擎，InnoDB写的处理效率差一些并且会占用更多的磁盘空间以保留数据和索引。

Innordb的功能要比myiasm强大很多，但是innordb的性能要比myisam差很多。
如果只是做简单的查询，更新，删除，那么用myiasm是最好的选择。
如果你的数据量是百万级别的，并且没有任何的事务处理，那么用myisam是性能最好的选择。
Innordb的表的大小更加的大，用myisam可以省很多的硬盘空间。 
总结：一般来说，MYisam引擎比较常用。
适合：
1. 做很多count 的计算。
2. 插入不平凡，查询非常频繁。
3.  没有事务

innordb 适合：
1. 可靠性要求比较高，或者要求事务。
2. 表更新和查询都相当的频繁，并且表锁定的机会比较大的情况。

MERGE :   类似于视图      合并逻辑表INSERT_METHOD=LAST/FIRST/0不允许插入 分表
1  每个子表的结构必须一致，主表和子表的结构需要一致，
2  每个子表的索引在merge表中都会存在，所以在merge表中不能根据该索引进行唯一性检索。 约束没有任何作用
3  子表需要是MyISAM引擎
4  REPLACE在merge表中不会工作
5  AUTO_INCREMENT 不会按照你所期望的方式工作。

CREATE TABLE  IF NOT EXISTS  W_MSG (ID VARCHAR(40) primary key, TEXT TEXT) ENGINE=MERGE UNION=(W_MSG_0,W_MSG_1) INSERT_METHOD=LAST DEFAULT CHARSET=utf8;
ALTER TABLE tbl_name  UNION=(...)


--生成sql批量分表
tt=''; for i in `seq 0 99`; do tt="${tt},msg_entity_${i}"; done ; tt=${tt:1}; str='CREATE TABLE  IF NOT EXISTS  W_MSG (ID VARCHAR(40) primary key, TEXT TEXT) ENGINE=MERGE UNION=( '"${tt}"' ) INSERT_METHOD=LAST DEFAULT CHARSET=utf8 '; echo ${str}
    

//表锁：开销小 加锁快 不会出现死锁
//行锁：开销大 加锁慢 会出现死锁 锁定力度小 发生锁冲突概率小



desc 表名;       // 表信息 
show columns from 表名;       // 表字段 
describe 表名;       // 表信息 
show create table 表名;        // 表创建语句 
show table status from 数据库名;        // 数据库状态 
show tables或show tables from database_name;       // 显示当前数据库中所有表的名称 
show databases;       // 显示mysql中所有数据库的名称 
show processlist;       // 显示系统中正在运行的所有进程，也就是当前正在执行的查询。大多数用户可以查看他们自己的进程，但是如果他们拥有process权限，就可以查看所有人的进程，包括密码。 
show table status;       // 显示当前使用或者指定的database中的每个表的信息。信息包括表类型和表的最新更新时间 
show columns from table_name from database_name;        // 显示表中列名称 
show columns from database_name.table_name;        // 显示表中列名称 
show grants for user_name@localhost;        // 显示一个用户的权限，显示结果类似于grant 命令 
show index from table_name;        // 显示表的索引 show status;解释：显示一些系统特定资源的信息，例如，正在运行的线程数量 
show variables;        // 显示系统变量的名称和值 
show privileges //;解释：显示服务器所支持的不同权限 
show create database database_name ;       // 显示create database 语句是否能够创建指定的数据库 
show create table table_name;       // 显示create database 语句是否能够创建指定的数据库 
show engies;        // 显示安装以后可用的存储引擎和默认引擎。 
show innodb status ;        // 显示innoDB存储引擎的状态 
show logs;        // 显示BDB存储引擎的日志 
show warnings;       //显示最后一个执行的语句所产生的错误、警告和通知 
show errors;       // 只显示最后一个执行语句所产生的错误

set names utf8;
set character set utf8;
set collation_connection='utf8-general_ci';

//优化
slow query 慢查询统计
索引
缓存

 
查看mysql每个数据库的大小 行数
select
table_schema as 'db',
sum(table_rows) as 'rows',
sum(truncate(data_length/1024/1024, 2)) as 'dataSize(MB)',
sum(truncate(index_length/1024/1024, 2)) as 'indexSize(MB)'
from information_schema.tables
where table_schema='mysql'
group by table_schema

--ssl 5.7关闭
show varibles like '%ssl%'
    have_openssl=YES
    have_ssl=YES

vim /etc/my.cnf
    # disable_ssl
    skip_ssl
    
    
--查看所有数据库 所有表 
cmd='mysql -u root -proot'
type="show"
temp_sqls="temp/${type}"
[ ! -d ${temp_sqls} ] && mkdir -p ${temp_sqls}
dbs=(`${cmd} -e "show databases;" | grep $1 `)
for ((i=0; i < ${#dbs[@]}; i++))
do
    item=${dbs[$i]}
    sql="${temp_sqls}/${item}
    echo "make ${type} sql of db-file: ${sql}"
    echo "use ${item};" > ${sql}
    tables=(`${cmd} -e "use ${item}; show tables;" | grep -v Table | awk '{print $0}'`)
    echo "${type} size ${#tables[@]}"
    echo "${type} size ${#tables[@]}" >> ${sql}
    ${cmd} -e "use ${item}; show tables;" | grep -v Table | awk '{print $0}' >> ${sql}
done
    
--清理所有数据库 所有表 数据
cmd='mysql -u root -proot'
type="truncate"
temp_sqls="temp/${type}"

[ ! -d ${temp_sqls} ] && mkdir -p ${temp_sqls}
dbs=(`${cmd} -e "show databases;" | grep $1 `)
for ((i=0; i < ${#dbs[@]}; i++))
do
    item=${dbs[$i]}
    sql="${temp_sqls}/${item}
    echo "make ${type} sql of db-file: ${sql}"
    echo "use ${item};" > ${sql}
    ${cmd} -e "use ${item}; show tables;" | grep -v Table | awk '{print "truncate table "$0";"}' >> ${sql}
    echo "${type}"
    cat ${sql}
    ${cmd} < ${sql}
done

--删除所有数据库 所有表
cmd='mysql -u root -proot'
type="drop"
temp_sqls="temp/${type}"
[ ! -d ${temp_sqls} ] && mkdir -p ${temp_sqls}
dbs=(`${cmd} -e "show databases;" | grep $1 `)
for ((i=0; i < ${#dbs[@]}; i++))
do
    item=${dbs[$i]}
    sql="${temp_sqls}/${item}
    echo "make ${type} sql of db-file: ${sql}"
    echo "use ${item};" > ${sql}
    ${cmd} -e "use ${item}; show tables;" | grep -v Table | awk '{print "drop table "$0";"}' >> ${sql}
    echo "${type}"
    cat ${sql}
    ${cmd} < ${sql}
done

 
--新建数据库 所有表
cmd='mysql -u root -proot'
type="create"
temp_sqls="temp/${type}"
[ ! -d ${temp_sqls} ] && mkdir -p ${temp_sqls}
dbs=(`${cmd} -e "show databases;" | grep $1 `)
for ((i=0; i < ${#dbs[@]}; i++))
do
    item=${dbs[$i]}
    sql="${temp_sqls}/${item}
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
    
    
    
    

