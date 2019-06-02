asdf;a;
--常用 dml dcl ddl sql语句


SELECT count(*) from user_tables;
--查看用户列表 
select * from dba_users; --查看数据库里面所有用户，前提是你是有dba权限的帐号，如sys,system
select * from all_users; --查看你能管理的所有用户！
select * from user_users; --查看当前用户信息 ！

---
--oracle sql 操作模板
---
create table test(id varchar(20), time date);
insert into test values('0002', to_date('1000-12-12','yyyy-mm-dd hh24:mi:ss') );
SELECT  to_char(time, 'yyyy-mm-dd hh24:mi:ss' ), id  FROM test;

SELECT  to_char(  to_date('1000-12-12','yyyy-mm-dd hh24:mi:ss'), 'yyyy-mm-dd hh24:mi:ss') FROM dual

 




















 