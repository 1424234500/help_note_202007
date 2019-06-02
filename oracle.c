// import sql/help.sql

D:\oracle\product\11.2.0\dbhome_1\NETWORK\ADMIN\SAMPLE


64位oracle安装，安装oracle xe，安装plsql，移动oci32 ，配置 oci dll 
E:\Oracle\instantclient_10_2
E:\oracle\instantclient_10_2\oci.dll 
localhost:1521/xe
// 中文编码-环境变量
NLS_LANG
SIMPLIFIED CHINESE_CHINA.ZHS16GBK


// 登录1
sqlplus /nolog
conn  /  as sysdba;
//登录2
sqlplus / as sysdba

// 创建用户：
create user walker identified by qwer; 
// 授予登陆和常用角色权限：//视图权限
grant connect, resource to walker
grant create view to walker 

// 端口冲突问题
begin  
   dbms_xdb.sethttpport('8081');  
   dbms_xdb.setftpport('0');  
end;  
/   



dbca  数据库管理
netca 监听管理

//删除数据库 报错 nt问题
权限管理员cmd执行dbca即可

//中文乱码问题2
$ sqlplus / as sysdba;
select userenv('language') from dual;
如果是：AMERICAN_AMERICA.WE8MSWIN1252  则需要调整编码格式为：AL32UTF8
SQL> shutdown immediate;
SQL> startup mount;
SQL> alter system enable restricted session;
SQL> alter system set job_queue_processes=0;
SQL> alter database open;
SQL> alter database character set internal_use AL32UTF8;
SQL> shutdown immediate;
SQL> startup
SQL>alter system disable restricted session;


//dblink 跨数据库数据操作
-- 查看wangyong用户是否具备创建database link 权限
select * from user_sys_privs where privilege like upper('%DATABASE LINK%') AND USERNAME='WANGYONG';
-- 给wangyong用户授予创建dblink的权限
grant create public database link to wangyong; 
-- 注意一点，如果密码是数字开头，用“”括起来
create public database link TESTLINK2 connect to WANGYONG identified by "123456" USING 'ORCL21'

create database link xxx----即将建立的dblink名
  connect to 数据库用户名 identified by "密码"
  using 'xxx.xxx.xxx.xx-----数据库IP';

select * from tbl_ost_notebook@dblink;

// 数据导入导出
 DOS中可以执行时由于 在oracle 8i 中  安装目录\$ora10g\BIN被设置为全局路径，
// 数据导出：
 1 将数据库TEST完全导出,用户名system 密码manager 导出到D:\daochu.dmp中
   exp system/manager@TEST file=d:\daochu.dmp  
 2 将数据库中system用户与sys用户的表导出
   exp system/manager@TEST file=d:\daochu.dmp owner=(system,sys)
 3 将数据库中的表table1 、table2导出
   exp system/manager@TEST file=d:\daochu.dmp tables=(table1,table2) 
 4 将数据库中的表table1中的字段filed1以"00"打头的数据导出
   exp system/manager@TEST file=d:\daochu.dmp tables=(table1) query=\" where filed1 like  '00%'\"
       上面是常用的导出，对于压缩我不太在意，用winzip把dmp文件可以很好的压缩。
                     不过在上面命令后面 加上 compress=y  就可以了
// 数据的导入
 1 将D:\daochu.dmp 中的数据导入 TEST数据库中。
   imp system/manager@TEST  file=d:\daochu.dmp full=y
   上面可能有点问题，因为有的表已经存在，然后它就报错，对该表就不进行导入。
   在后面加上 ignore=y 就可以了。
 2 将d:\daochu.dmp中的表table1 导入
 imp system/manager@TEST  file=d:\daochu.dmp  tables=(table1) 
  基本上上面的导入导出够用了。不少情况我是将表彻底删除，然后导入。
 注意：
 你要有足够的权限，权限不够它会提示你。
 数据库时可以连上的。可以用tnsping TEST 来获得数据库TEST能否连上。


// 一、ORACLE的启动和关闭 
1、在单机环境下 
要想启动或关闭ORACLE系统必须首先切换到ORACLE用户，如下 
su - oracle 
a、启动ORACLE系统 
oracle>svrmgrl 
SVRMGR>connect internal 
SVRMGR>startup 
SVRMGR>quit 
b、关闭ORACLE系统 
oracle>svrmgrl 
SVRMGR>connect internal 
SVRMGR>shutdown 
SVRMGR>quit 
启动oracle9i数据库命令： 
$ sqlplus /nolog 
SQL*Plus: Release 9.2.0.1.0 - Production on Fri Oct 31 13:53:53 2003 
Copyright (c) 1982, 2002, Oracle Corporation.  All rights reserved. 

SQL> connect / as sysdba  
Connected to an idle instance. 
SQL> startup^C 

SQL> startup 
ORACLE instance started. 
// 2、在双机环境下 
要想启动或关闭ORACLE系统必须首先切换到root用户，如下 
su － root 
a、启动ORACLE系统 
hareg －y oracle 
b、关闭ORACLE系统 
hareg －n oracle 
Oracle数据库有哪几种启动方式 
三、查看数据库的SQL 
1、查看表空间的名称及大小 
    select t.tablespace_name, round(sum(bytes/(1024*1024)),0) ts_size 
    from dba_tablespaces t, dba_data_files d 
    where t.tablespace_name = d.tablespace_name 
    group by t.tablespace_name; 
2、查看表空间物理文件的名称及大小 
    select tablespace_name, file_id, file_name, 
    round(bytes/(1024*1024),0) total_space 
    from dba_data_files 
    order by tablespace_name; 
3、查看回滚段名称及大小 

    select segment_name, tablespace_name, r.status, 
    (initial_extent/1024) InitialExtent,(next_extent/1024) NextExtent, 
    max_extents, v.curext CurExtent 
    From dba_rollback_segs r, v$rollstat v 
    Where r.segment_id = v.usn(+) 
    order by segment_name ; 
4、查看控制文件 
    select name from v$controlfile; 
5、查看日志文件 
    select member from v$logfile; 
6、查看表空间的使用情况 
    select sum(bytes)/(1024*1024) as free_space,tablespace_name 
    from dba_free_space 
    group by tablespace_name; 

    SELECT A.TABLESPACE_NAME,A.BYTES TOTAL,B.BYTES USED, C.BYTES FREE, 
    (B.BYTES*100)/A.BYTES "% USED",(C.BYTES*100)/A.BYTES "% FREE" 
    FROM SYS.SM$TS_AVAIL A,SYS.SM$TS_USED B,SYS.SM$TS_FREE C 
    WHERE A.TABLESPACE_NAME=B.TABLESPACE_NAME AND A.TABLESPACE_NAME=C.TABLESPACE_NAME; 

7、查看数据库库对象 
    select owner, object_type, status, count(*) count# from all_objects group by owner, object_type, status; 
8、查看数据库的版本 
    Select version FROM Product_component_version 
    Where SUBSTR(PRODUCT,1,6)='Oracle'; 
9、查看数据库的创建日期和归档方式 
    Select Created, Log_Mode, Log_Mode From V$Database; 

// 四.ORACLE里常用的数据对象 (SCHEMA) 
1.索引 (INDEX) 
CREATE INDEX 索引名ON 表名 ( 字段1, [字段2, ……] ); 
ALTER INDEX 索引名 REBUILD; 
一个表的索引最好不要超过三个 (特殊的大表除外), 最好用单字段索引, 结合SQL语句的分析执行情况, 
也可以建立多字段的组合索引和基于函数的索引 
ORACLE8.1.7字符串可以索引的最大长度为1578 单字节 
ORACLE8.0.6字符串可以索引的最大长度为758 单字节 
2.视图 (VIEW) 
CREATE VIEW 视图名AS SELECT …. FROM …..; 
ALTER VIEW视图名 COMPILE; 
视图仅是一个SQL查询语句, 它可以把表之间复杂的关系简洁化. 
3.同义词 (SYNONMY) 
CREATE SYNONYM同义词名FOR 表名; 
CREATE SYNONYM同义词名FOR 表名@数据库链接名; 
4.数据库链接 (DATABASE LINK) 
CREATE DATABASE LINK数据库链接名CONNECT TO 用户名 IDENTIFIED BY 密码 USING ‘数据库连接字符串’; 
数据库连接字符串可以用NET8 EASY CONFIG或者直接修改TNSNAMES.ORA里定义. 
数据库参数global_name=true时要求数据库链接名称跟远端数据库名称一样 
数据库全局名称可以用以下命令查出 
SELECT * FROM GLOBAL_NAME; 
查询远端数据库里的表 
SELECT …… FROM 表名@数据库链接名; 
 
