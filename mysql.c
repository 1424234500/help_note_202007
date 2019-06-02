//启动mysql
d:/mysql/bin/mysqld 

//登录
mysql -u root -proot
mysql <-h 127.0.0.1> -u root -ppasswd <-P 3306>
mysqladmin -u用户名 -p旧密码 password 新密码
远程登录权限
GRANT ALL PRIVILEGES ON *.* TO 'walker'@'%' IDENTIFIED BY 'qwer' WITH GRANT OPTION;

//shell调用sql
mysql -uuser -ppasswd -e "show databases;"
//shell调用sql文件
use abccs;
select * from mytable;
select name,sex from mytable where name=‘abccs‘;
mysql < mytest.sql | more

//变量设置 查看 mysql当前服务进程有效
show variables like 'max_connections'
set global max_connections=1000;
//文件配置 
my.ini 或 my.cnf
	default_character=utf8
	[mysqld]
	long_query_time=2	//慢查询时间定义s 
	//5.5如下配置
	show-query-log=on
	show_uery_log_file="mysql_slow_query.log"
	
	
//数据库 表 show
select USER(), version(),current_date();
SHOW DATABASES;
CREATE DATABASE walker;
CREATE DATABASE IF NOT EXISTS walker default charset utf8 COLLATE utf8_general_ci;
drop database walker;
USE walker;

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
//表锁：开销小 加锁快 不会出现死锁
//行锁：开销大 加锁慢 会出现死锁 锁定力度小 发生锁冲突概率小
show engines;

desc 表名;       // 表信息 
show columns from 表名;       // 表字段 
describe 表名;       // 表信息 
show create table 表名;        // 表创建语句 
show create database 数据库名;        // 显示数据库 信息 
show table status from 数据库名;        // 数据库状态 
show tables或show tables from database_name;       // 显示当前数据库中所有表的名称 
show databases;       // 显示mysql中所有数据库的名称 
show processlist;       // 显示系统中正在运行的所有进程，也就是当前正在执行的查询。大多数用户可以查看他们自己的进程，但是如果他们拥有process权限，就可以查看所有人的进程，包括密码。 
show table status;       // 显示当前使用或者指定的database中的每个表的信息。信息包括表类型和表的最新更新时间 
show columns from table_name from database_name;        // 显示表中列名称 
show columns from database_name.table_name;        // 显示表中列名称 
show grants for user_name@localhost;        // 显示一个用户的权限，显示结果类似于grant 命令 
show index from table_name;        // 显示表的索引 show status;解释：显示一些系统特定资源的信息，例如，正在运行的线程数量 
show variables;        // 显示系统变量的名称和值 show privileges;解释：显示服务器所支持的不同权限 
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


1.要查询表所占的容量，就是把表的数据和索引加起来
select sum(DATA_LENGTH)+sum(INDEX_LENGTH) from information_schema.tables 
where table_schema='数据库名';
select concat(round(sum(DATA_LENGTH/1024/1024),2),'M') from tables; -- 查询所有的数据大小

2.查看mysql库容量大小 
select
table_schema as '数据库',
sum(table_rows) as '记录数',
sum(truncate(data_length/1024/1024, 2)) as '数据容量(MB)',
sum(truncate(index_length/1024/1024, 2)) as '索引容量(MB)'
from information_schema.tables
where table_schema='mysql'


