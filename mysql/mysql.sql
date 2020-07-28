------------
简易安装临时使用
sudo apt-get install mysql-server

---------------------------------------------
mysqld --verbose --help			#帮助文档
mysqld --print-default			#默认参数
	mysqld would have been started with the following arguments:
	--user=mysql --pid-file=/var/rumysqld/mysqld.pid --socket=/var/rumysqld/mysqld.sock --port=3306 --basedir=/usr --datadir=/var/lib/mysql --tmpdir=/tmp --lc-messages-dir=/usr/share/mysql --skip-external-locking --key_buffer_size=16M --max_allowed_packet=16M --thread_stack=192K --thread_cache_size=8 --myisam-recover-options=BACKUP --query_cache_limit=1M --query_cache_size=16M --log_error=/var/log/mysql/error.log --expire_logs_days=10 --max_binlog_size=100M

mysqld_safe --print-default 

-------------------------------------------

--mysql安装 注意位数 避免 -bash: ./mysqld: cannot execute binary file: Exec format error
wget https://cdn.mysql.com//Downloads/MySQL-5.7/mysql-5.7.29-linux-glibc2.12-i686.tar.gz
wget https://cdn.mysql.com//Downloads/MySQL-5.7/mysql-5.7.29-linux-glibc2.12-x86_64.tar.gz

#mkdir mysql-5.7
tar -xzvf mysql-5.7.29-linux-glibc2.12-x86_64.tar.gz
mv mysql-5.7.29-linux-glibc2.12-x86_64 mysql-5.7
cd mysql-5.7

sudo groupadd mysql
sudo useradd -r -s /sbin/nologin -g mysql mysql -d /home/walker/mysql     #新建msyql用户禁止登录shell 主home目录

basedir=/home/walker/software/mysql-5.7
datadir=${basedir}/data
tmpdir=${basedir}
mkdir -p ${datadir}
mkdir -p ${basedir}/logredo
mkdir -p ${basedir}/logundo


--生成my.cnf作为配置文件
#cp my-default.cnf /etc/my.cnf	 
cp ~/help_note/mysql/mysql.cnf ./my.cnf
#mysql的安装目录share下就有各种不同需求的my.cnf配置，直接copy过来改名my.cnf就可以使用了
my-huge.cnf
This is for a large system with memory of 1G-2G where the system runs mainly.
my-innodb-heavy-4G.cnf
#DESCR: 4GB RAM, InnoDB only, ACID, few connections, heavy queries.
my-large.cnf
This is for a large system with memory = 512M where the system runs mainly.
my-medium.cnf
# This is for a system with little memory (32M - 64M) where MySQL plays
# an important part, or systems up to 128M where MySQL is used together with
# other programs (such as a web server)
my-small.cnf
# This is for a system with little memory (<= 64M) where MySQL is only used
# from time to time and it's important that the mysqld daemon
# doesn't use much resources.


#问题 大小写 中文支持 !!!!!!!!! 但在一些不区分大小写目录的系统报错 需修改
lower_case_table_names = 0
#问题 内存过载？
SHOW VARIABLES LIKE '%table_open_cache%'
#问题 权限全局警告不可用 临时修改644?依然不行 mysqld: [Warning] World-writable config file '/home/walker/software/mysql-5.7/my.cnf' is ignored.
chmod 444 ./my.cnf

#顺序不能变
./bin/mysqld --defaults-file=./my.cnf --initialize  --user=walker

tail ${basedir}/error.log
出现:
2020-02-09T08:54:12.610175Z 1 [Note] A temporary password is generated for root@localhost: V2hDolDsce*+
记录生成的临时密码，上文结尾处

#初始化rsa？密钥
./bin/mysql_ssl_rsa_setup  --datadir=/home/walker/software/mysql-5.7/data 

--修改启动工具
vim /home/walker/software/mysql-5.7/support-files/mysql.server
	basedir=/home/walker/software/mysql-5.7
	datadir=/home/walker/software/mysql-5.7/data


--关闭
./bin/mysqladmin -u root -proot shutdown

--启动mysql 具体是否使用mysql用户？  			
#启动1， 读取[safe_mysqld]中的配置 守护进程模式
./bin/mysqld_safe --defaults-file=./my.cnf  --user=walker &
#启动2， 读取配置文件中的[mysqld]的部分
./bin/mysqld --defaults-file=./my.cnf --user=walker  &	
#启动3， 须先把启动工具复制到启动菜单中 cp support-files/mysql.server /etc/init.d/mysql
service mysql start		


--启动日志
tail ./error.log
	2020-02-09T09:00:56.260506Z 0 [Note] mysqld: ready for connections.
	Version: '5.7.29-log'  socket: '/home/walker/mysql-5.7/mysql.sock'  port: 3306  MySQL Community Server (GPL)
	
--配置mysql开机自动启动
#cp ${basedir}/support-files/mysql.server /etc/init.d/mysql  #为了加入service开机自启  
	chmod 755 /etc/init.d/mysql
	chkconfig --add mysql
	chkconfig --level 345 mysql on 

--修复
mysqlcheck --auto-repair -A -o -uroot -pyigeorg
--登录
mysql  --defaults-file=/home/walker/mysql-5.7/my.cnf  -u root -proot	#指定配置sock文件 
mysql -u root -proot
mysql <-h 127.0.0.1> -u root -ppasswd <-P 3306>
mysqladmin -u用户名 -p旧密码 password 新密码

--修改默认密码	授权root只限localhost登录
set password=password('root');
grant all privileges on *.* to 'root'@'localhost' identified by 'root';	
flush privileges;

--如提示不能成功连接，可能需要添加需要监听的端口 火墙
/sbin/iptables -I  INPUT -p tcp --dport 3306 -j ACCEPT

--shell调用sql文件
mytest.sql 
	use walker;
	select * from mytable;
mysql -u root -proot < mytest.sql 
mysql -u root -proot -e "show databases;"


--变量设置 查看 mysql当前服务进程有效
show variables like 'max_connections'
set global max_connections=1000;
--查看中文支持
show variables like 'character%'; 
--数据库 创建 权限 登录
select USER(), version(),current_date();
SHOW DATABASES;
--删除数据库
drop database walker;
--创建数据库 赋予 远程登录权限 % 不限ip  
CREATE DATABASE IF NOT EXISTS walker default charset utf8 COLLATE utf8_general_ci;
GRANT ALL PRIVILEGES ON *.* TO 'walker'@'%' IDENTIFIED BY 'qwer' WITH GRANT OPTION;
CREATE DATABASE IF NOT EXISTS walker0 default charset utf8 COLLATE utf8_general_ci;
GRANT ALL PRIVILEGES ON *.* TO 'walker0'@'%' IDENTIFIED BY 'qwer' WITH GRANT OPTION;
CREATE DATABASE IF NOT EXISTS walker1 default charset utf8 COLLATE utf8_general_ci;
GRANT ALL PRIVILEGES ON *.* TO 'walker1'@'%' IDENTIFIED BY 'qwer' WITH GRANT OPTION;
 
--赋权方式 改表 或 授权
use mysql;
select host,user from user;	--查看用户 授权情况
GRANT ALL PRIVILEGES ON *.* TO 'root'@'localhost' IDENTIFIED BY 'root' WITH GRANT OPTION;
update user set host = '%' where user like 'walker%';
flush privileges;

 
--安全模式
safemode
--Error Code: 1175. You are using safe update mode and you tried to update a table without a WHERE that uses a KEY column To disable safe mode, toggle the option in Preferences -> SQL Queries and reconnect.
--这是因为MySql运行在safe-updates模式下，该模式会导致非主键条件下无法执行update或者delete命令
--查看是否开启了安全模式
show variables like ‘SQL_SAFE_UPDATES‘;
--关闭
SET SQL_SAFE_UPDATES = 0;


--导出 导入
mysqldump -uroot -proot student > student.sql;
1、在B机器上装mysql。
将A机器上的mysql/data下的你的数据库目录整个拷贝下来。
将B机器上的mysql服务停止。
找到B机器上的mysql/data目录，将你拷贝的目录粘贴进去，然后启动mysql服务就可以了。

--Master/Slave  主备？ 数据库之间的同步 <异步处理>
grant file on *.* to 'root'@' 1222.122.1.1' identified by 'password';
grant replication master on *.* ....


--mysql定位
/usr/local/Cellar/mysql/5.7.17	--mac
whereis mysql	--定位
locate mysql 
--授权登陆


--主键自动索引pk > 数字索引index > 字符串索引index > 组合字段索引merge_index
explain select * from student where id = 12;	--explain sql-select
system > const > eq_ref > ref > fulltext > ref_or_null > index_merge > unique_subquery > index_subquery > range > index > all

	
--显示引擎 
--innorDB		行锁+表锁	事物  
--<MY>ISAM		表锁		
--MERGE         合并逻辑表INSERT_METHOD=LAST/FIRST/0不允许插入 分表
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
3. 没有事务

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



--表锁：开销小 加锁快 不会出现死锁
--行锁：开销大 加锁慢 会出现死锁 锁定力度小 发生锁冲突概率小


1、查看最大连bai接数的代码：
show variables like '%max_connections%';
2、修du改最大连接数的代码zhi：
set GLOBAL max_connections = 128;



desc 表名;       -- 表信息 
show columns from 表名;       -- 表字段 
describe 表名;       -- 表信息 
show create table 表名;        -- 表创建语句 
show table status from 数据库名;        -- 数据库状态 
show tables或show tables from database_name;       -- 显示当前数据库中所有表的名称 
show databases;       -- 显示mysql中所有数据库的名称 
show processlist;       -- 显示系统中正在运行的所有进程，也就是当前正在执行的查询。大多数用户可以查看他们自己的进程，但是如果他们拥有process权限，就可以查看所有人的进程，包括密码。 
show table status;       -- 显示当前使用或者指定的database中的每个表的信息。信息包括表类型和表的最新更新时间 
show columns from table_name from database_name;        -- 显示表中列名称 
show columns from database_name.table_name;        -- 显示表中列名称 
show grants for user_name@localhost;        -- 显示一个用户的权限，显示结果类似于grant 命令 
show index from table_name;        -- 显示表的索引 show status;解释：显示一些系统特定资源的信息，例如，正在运行的线程数量 
show variables;        -- 显示系统变量的名称和值 
show privileges --;解释：显示服务器所支持的不同权限 
show create database database_name ;       -- 显示create database 语句是否能够创建指定的数据库 
show create table table_name;       -- 显示create database 语句是否能够创建指定的数据库 
show engies;        -- 显示安装以后可用的存储引擎和默认引擎。 
show innodb status ;        -- 显示innoDB存储引擎的状态 
show logs;        -- 显示BDB存储引擎的日志 
show warnings;       --显示最后一个执行的语句所产生的错误、警告和通知 
show errors;       -- 只显示最后一个执行语句所产生的错误

set names utf8;
set character set utf8;
set collation_connection='utf8-general_ci';

--优化
slow query 慢查询统计
索引
缓存
 
    
    
    
--切换数据库
USE walker;


--数据结构
主键 索引 最大长度1000, 不能达到500？
建立索引时，数据库计算key的长度是累加所有Index用到的字段的char长度后再按下面比例乘起来不能超过限定的key长度1000： 
latin1 = 1 byte = 1 character uft8 = 3 byte = 1 character gbk = 2 byte = 1 character 
上步骤语句中索引总长度（100+255+255） * 2 = 1220 > 1000

--建表 查表 描述
CREATE TABLE  IF NOT EXISTS  test (id VARCHAR(20) primary key, name CHAR(10));
drop table test;
SHOW TABLES;
DESCRIBE test; 
desc test;
show table status like 'test';
show create table student;  --查看表create创建语句

--生成sql批量分表
tt=''; for i in `seq 0 99`; do tt="${tt},msg_entity_${i}"; done ; tt=${tt:1}; str="CREATE TABLE  IF NOT EXISTS  W_MSG (ID VARCHAR(40) primary key, TEXT TEXT) ENGINE=MERGE UNION=( '${tt}' ) INSERT_METHOD=LAST DEFAULT CHARSET=utf8 "; echo ${str}
    

--插入更新
insert into test values('001', 'walker');
update test set name='walker1';
--分页查询
select * from test;
select * from test limit 0,1;
--查看列名
select COLUMN_NAME from information_schema.COLUMNS where table_name = 'test';   
NOT NULL auto_increment,

--常用函数 
ifnull  nvl

--整数转换
select concat(8,'0')  from dual;

select * from (
select cast(NET_COST as signed) NET_COST from W_LOG_SOCKET_MODEL
) where NET_COST > 100;
select NET_COST from W_LOG_SOCKET_MODEL where NET_COST > 100;

--查询
--行号rownum
select rownum from (select  (@i:=@i+1) rownum from  information_schema.COLUMNS t ,(select   @i:=0) it ) t  where rownum < 10 ;       

--序列 位数补齐
select lpad(level, 2, '0') lev from (select  (@i:=@i+1) level from  information_schema.COLUMNS t ,(select   @i:=0) it ) t  where level<=24     ;
--2015-01-01~2018-06-01的连续日期，一种方式，借助笛卡儿积，进行生成，SQL代码如下： -- 生成的日期多少取决于主表

select date_add('2021-01-01',interval @i:=@i+1 day) as date 
from ( 
    select 1 from (select  (@i:=@i+1) level from  information_schema.COLUMNS t ,(select   @i:=0) it ) t  where level<=10   

) as tmp,
(select @i:= -1) t

 
 
--代码java执行替换
select lpad(level, 2, '0') lev from (select  (@i/*'*/:=/*'*/@i+1) level from  information_schema.COLUMNS t ,(select   @i/*'*/:=/*'*/0) it ) t  where level<=24     ;
用符号:/*'*/:=/*'*/转换:=



select date_format(FROM_UNIXTIME(1595901121739 / 1000),'%Y-%m-%d %H:%i:%S');    //时间戳格式化字符串

select FROM_UNIXTIME(1595901121.739);   //2020-07-28 09:52:01.739   UNIX时间戳转换为日期
Select UNIX_TIMESTAMP('2018-09-05 17：01：34');    //1536138000   日期转换为UNIX时间戳
select date_format(now(),'%Y-%m-%d %H:%i:%S')   //2020-07-28 10:35:39   oracle中的to_char();
SELECT DATE_FORMAT(20130111191640,'%Y-%m-%d %H:%i:%s')    //2013-01-11 19:16:40 
select str_to_date(1595901121739, '%Y-%m-%d') -------------->oracle中的to_date();

　　%Y：代表4位的年份
　　%y：代表2为的年份
　　%m：代表月, 格式为(01……12)
　　%c：代表月, 格式为(1……12)
　　%d：代表月份中的天数,格式为(00……31)
　　%e：代表月份中的天数, 格式为(0……31)
　　%H：代表小时,格式为(00……23)
　　%k：代表 小时,格式为(0……23)
　　%h： 代表小时,格式为(01……12)
　　%I： 代表小时,格式为(01……12)
　　%l ：代表小时,格式为(1……12)
　　%i： 代表分钟, 格式为(00……59)
　　%r：代表 时间,格式为12 小时(hh:mm:ss [AP]M)
　　%T：代表 时间,格式为24 小时(hh:mm:ss)
　　%S：代表 秒,格式为(00……59)
　　%s：代表 秒,格式为(00……59)




--行数大表容量
 select table_schema,table_name,table_type,data_length+index_length size, table_rows from information_schema.tables 
 where 1=1
 and table_schema not in ('performance_schema', 'mysql')
 order by table_rows desc 
 limit 40









