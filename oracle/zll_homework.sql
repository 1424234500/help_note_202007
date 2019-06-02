
  
-----------------------------------------------------
--表单创建及其初始化,关于是否创建外键关联??，减小数据库压力，不建，交由java代码控制管理级联删除等
----------------------------------------------



--md5加密函数
CREATE OR REPLACE FUNCTION MD5(passwd IN VARCHAR2) RETURN VARCHAR2 IS retval varchar2(32);
BEGIN
 retval := Lower(utl_raw.cast_to_raw( DBMS_OBFUSCATION_TOOLKIT.MD5(INPUT_STRING => passwd)) );
 RETURN retval;
END;
 
----------------------------------------------------------------------
--使用md5方法
select MD5('zll11') res from dual;



--提交作业表, 附加评阅结果字段，评阅时间
drop table z_homework_submit; 
create table z_homework_submit(homeworkid varchar(20), classid varchar(20), studentid varchar(20), 
 detail varchar(512), filename varchar(100), filepath  varchar(128), time date, read varchar(512), readtime date, 
 primary key (homeworkid, classid, studentid)
);

--作业表 作业随班 多个课程班的放在一起 老师：发布人，班级可能换老师，老师只能管理自己所辖班级作业
drop table z_homework;

create table z_homework(homeworkid varchar(20), classid varchar(20), teacherid varchar(20) not null, 
 name varchar(100) not null,      detail varchar(512),filename varchar(100), filepath varchar(128), 
  fromtime date not null, totime date not null,
    primary key(homeworkid,classid) 
 );


--班级 学生映射
drop table z_class_student; 
create table z_class_student(classid varchar(20), studentid varchar(20), primary key(classid, studentid ) );
 
--班级表，班级 老师映射
drop table z_class; 
create table z_class(id varchar(20) primary key,  teacherid varchar(20), name varchar(100) not null,time date not null,stoptime date not null );
 
-- id 1 密码 1  = 19f7df5df3097163ffb26e433dbd90a1
--登陆表，每次用户登陆时生成一个key，并插入/更新登陆记录表，增删查改时验证key,防止非法访问， 也可以添加触发器于此表，限制登陆人数之类的
drop table z_login;
create table z_login( id varchar(20) primary key, time date not null,type varchar(20), key varchar(256) );


--老师表 教师id必须以t开头
drop table z_teacher;
create table z_teacher(id varchar(20) primary key, name varchar(100) not null , pwd varchar(64) not null, time date not null);
 --初始化密码
update z_teacher set pwd=MD5('zll'||id||'1');

--学生表 学生id必须数字开头
drop table z_student;
create table z_student(id varchar(20) primary key, name varchar(100) not null , pwd varchar(64) not null, time date not null, sex varchar(10) default '男' );
alter table z_student add (sex varchar(10) default '男' );

insert into z_student (id, name, pwd, time) values( '111', '北原春希', '123', to_date('2017-01-01', 'yyyy-mm-dd') );
insert into z_student (id, name, pwd, time) values( '112', '冬马和沙', '123', to_date('2017-01-01', 'yyyy-mm-dd') );
insert into z_student (id, name, pwd, time) values( '113', '小木曾雪菜', '123', to_date('2017-01-01', 'yyyy-mm-dd') );
insert into z_student (id, name, pwd, time) values( '114', '饭冢武也', '123', to_date('2017-01-01', 'yyyy-mm-dd') );
insert into z_student (id, name, pwd, time) values( '115', '水沢依绪', '123', to_date('2017-01-01', 'yyyy-mm-dd') );
insert into z_student (id, name, pwd, time) values( '116', '杉浦小春', '123', to_date('2017-01-01', 'yyyy-mm-dd') );
insert into z_student (id, name, pwd, time) values( '117', '和泉千晶', '123', to_date('2017-01-01', 'yyyy-mm-dd') );
insert into z_student (id, name, pwd, time) values( '118', '路人A', '123', to_date('2017-01-01', 'yyyy-mm-dd') );
insert into z_student (id, name, pwd, time) values( '119', '路人B', '123', to_date('2017-01-01', 'yyyy-mm-dd') );
insert into z_student (id, name, pwd, time) values( '120', '路人C', '123', to_date('2017-01-01', 'yyyy-mm-dd') );
insert into z_student (id, name, pwd, time) values( '121', '路人D', '123', to_date('2017-01-01', 'yyyy-mm-dd') );
insert into z_student (id, name, pwd, time) values( '122', '路人E', '123', to_date('2017-01-01', 'yyyy-mm-dd') ); 
insert into z_student (id, name, pwd, time) values( '123', '路人F', '123', to_date('2017-01-01', 'yyyy-mm-dd') );
insert into z_student (id, name, pwd, time) values( '124', '路人G', '123', to_date('2017-01-01', 'yyyy-mm-dd') );
insert into z_student (id, name, pwd, time) values( '125', '路人H', '123', to_date('2017-01-01', 'yyyy-mm-dd') );
insert into z_student (id, name, pwd, time) values( '126', '路人I', '123', to_date('2017-01-01', 'yyyy-mm-dd') );
insert into z_student (id, name, pwd, time) values( '127', '路人J', '123', to_date('2017-01-01', 'yyyy-mm-dd') );
insert into z_student (id, name, pwd, time) values( '128', '路人K', '123', to_date('2017-01-01', 'yyyy-mm-dd') );
insert into z_student (id, name, pwd, time) values( '129', '路人L', '123', to_date('2017-01-01', 'yyyy-mm-dd') );
insert into z_student (id, name, pwd, time) values( '130', '路人M', '123', to_date('2017-01-01', 'yyyy-mm-dd') );
insert into z_student (id, name, pwd, time) values( '131', '路人N', '123', to_date('2017-01-01', 'yyyy-mm-dd') );
insert into z_student (id, name, pwd, time) values( '132', '路人O', '123', to_date('2017-01-01', 'yyyy-mm-dd') );
--初始化密码
update z_student set pwd=MD5('zll'||id||'1');

--管理员表 管理员必须以a开头 密码默认 1
drop table z_admin;
create table z_admin(id varchar(20) primary key, name varchar(100) not null , pwd varchar(64) not null, time date not null);
insert into z_admin (id, name, pwd, time) values( 'a01', 'admin', '123', to_date('2017-01-01', 'yyyy-mm-dd') );
--初始化密码
update z_admin set pwd=MD5('zll'||id||'1');

 


--基本查询
select * from z_admin ; 
select * from z_teacher; 
select * from z_student ;
select * from z_login; 
select * from z_class  ; 
select * from z_class_student  ;  
select * from z_homework; 
select * from z_homework_submit;
 


--外码 外键
ALTER TABLE  z_class ADD  FOREIGN KEY(teacherid ) REFERENCES z_teacher(id);
ALTER TABLE  z_class_student ADD  FOREIGN KEY(classid ) REFERENCES z_class(id);
ALTER TABLE  z_class_student ADD  FOREIGN KEY(studentid ) REFERENCES z_student(id);
ALTER TABLE  z_homework ADD  FOREIGN KEY(classid ) REFERENCES z_class(id);
ALTER TABLE  z_homework ADD  FOREIGN KEY(teacherid ) REFERENCES z_teacher(id); 
ALTER TABLE  z_homework_submit ADD  FOREIGN KEY(classid ) REFERENCES z_class(id);
ALTER TABLE  z_homework_submit ADD  FOREIGN KEY(studentid ) REFERENCES z_student(id); 
 
delete from z_class_student;
delete from z_class;
