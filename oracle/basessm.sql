asdfasdf;
adf;
SELECT * FROM sys_config


SELECT * FROM student

SELECT * FROM launch ;

SELECT * FROM launch where rownum <= 1;

SELECT COLUMN_NAME FROM ALL_TAB_COLUMNS WHERE TABLE_NAME = upper('info') ORDER BY COLUMN_ID

SELECT t.*,rownum FROM info t;
SELECT * FROM log_time order by time desc;
SELECT * FROM loginuser for update;

--文件上传 监控
SELECT * FROM fileinfo order by path for update ;
SELECT  (select count(*) from file_down_up where fileid=f.id) count,f.* FROM fileinfo f;

SELECT * FROM file_down_up;

select * from fileinfo where 1=1  and TYPE in ('png', 'jpg')



SELECT * FROM file_down_up;
SELECT fi.name,fi.id,fi.filesize,fdu.type,fdu.costtime,fdu.time FROM file_down_up fdu,fileinfo fi where fi.id=fdu.fileid;
select id,name,(select count(*) from file_down_up where fileid=id and type='down') count from fileinfo ;
 
DELETE FROM log_time;
       
SELECT * FROM log_time order by id desc;
insert into student values(lpad(SEQ_STUDENT.nextval,4, '0'),'aaaaa', to_date('2017-12-13 10:50', 'yyyy-mm-dd hh24:mi:ss') ) 

--统计url操作次数
SELECT url,sum(count) sumcount FROM log_time where 1=1 group by url order by sum(count)
--url分时操作次数
  SELECT url,sum(count) sumcount FROM log_time where 1=1 group by url order by url 
SELECT lev, nvl(count, '0') count FROM 
(
SELECT hour, sum(count) count FROM ( 
SELECT  to_char(lt.time, 'hh24') hour, lt.url, lt.count FROM log_time lt where 1=1 and lt.url='/angular/statis.do' 
)group by hour 
) t1, 
(
select lpad(level, 2, '0') lev from dual connect by level <= 24   
) t2
where t1.hour(+) = t2.lev 
ORDER BY lev 

--统计url操作 耗时
SELECT url,cast(sum(costtime)/sum(count)/1000 as number(8, 3)) time FROM log_time where 1=1 group by url order by sum(costtime)/sum(count)
--统计某url 分时耗时 
 
SELECT lev, nvl(time, '0') time FROM 
(
SELECT hour, cast(sum(costtime)/sum(count)/1000 as number(8, 3)) time FROM ( 
SELECT  to_char(lt.time, 'hh24') hour, lt.count, lt.costtime FROM log_time lt where 1=1 and lt.url='/angular/statis.do' 
)group by hour  
) t1, 
(
select lpad(level, 2, '0') lev from dual connect by level <= 24   
) t2
where t1.hour(+) = t2.lev 
ORDER BY lev 

--统计最近三年 每月注册情况
 
SELECT t2.lev x, nvl(t1.y, '0') y FROM 
(
SELECT t.xs x,count(*) y FROM ( SELECT s.*,to_char(s.time, 'MM') xs FROM student s where to_char(s.time, 'yyyy')='2017'  ) t group by t.xs 
) t1
,(
select lpad(level, 2, '0') lev from dual connect by level <=12   
) t2
where t1.x(+) = t2.lev
order by t2.lev 

SELECT nvl(t1.y, '0') y FROM ( SELECT t.xs x,count(*) y FROM ( SELECT s.*,to_char(s.time, 'MM') xs FROM student s where to_char(s.time, 'yyyy')=to_char(sysdate, 'yyyy')  ) t group by t.xs ) t1,(select lpad(level, 2, '0') lev from dual connect by level <=12   ) t2 where t1.x(+) = t2.lev order by t2.lev 
--统计 总计 每月注册情况

SELECT t2.lev x, nvl(t1.y, '0') y FROM 
(
SELECT t.xs x,count(*) y FROM ( SELECT s.*,to_char(s.time, 'MM') xs FROM student s) t group by t.xs 
) t1
,(
select lpad(level, 2, '0') lev from dual connect by level <=12   
) t2
where t1.x(+) = t2.lev
order by t2.lev
 

SELECT * FROM lunch;
--统计多月每天的消费情况
--3月每天
SELECT t2.lev x, nvl(t1.y, '0') y FROM 
(
SELECT substr(t.xs,4,2) x,sum(t.buynum) y FROM ( 
       SELECT s.*,substr(s.day,6,5) xs FROM lunch s where substr(s.day,6,2)=lpad(3, 2, '0') and substr(s.day,1,7)>='2018-02' and substr(s.day,1,7)<='2018-04' 
) t 
group by t.xs 
) t1
,(
select lpad(level, 2, '0') lev from dual connect by level <=31   
) t2
where t1.x(+) = t2.lev
order by t2.lev
 

asdflkasdfj;--删除
drop sequence seq_fileinfo;
drop sequence seq_info;
drop sequence seq_student;
drop table student;
drop table info;
drop table loginuser;
drop table fileinfo;
drop table log_time;
drop table launch;


asdlfjasldf;


create table sys_config( key varchar(200) primary key, value varchar(2000), info varchar(2000), time varchar(40) ); 
INSERT INTO sys_config values('db_once', '400', 'database once query max', to_char(sysdate, 'yyyy-mm-dd hh24:mi:ss'));

--创建表/序列/触发器
create table student( id varchar(20) primary key, name varchar(40), time date  ); 
--登录用户操作日志info: id, time userid url ip mac 端口
create table info( id varchar(20) primary key, userid varchar(40), time date, url varchar(100), ip varchar(20), mac varchar(20), port varchar(20), about varchar(200)   ); 
create table log_time( id varchar(20) primary key, url varchar(80), count number(32), time date, costtime number(32)   ); 
--登录用户 loginuser: id,pwd,name,roleid
create table loginuser(id varchar(40) primary key, pwd varchar(40), name varchar(40), roleid varchar(20));
--文件管理 fileinfo: id,name,upuserid,filesize,type,path,uptime,changetime,about
create table fileinfo(id varchar(40) primary key, name varchar(200),upuserid varchar(40),type varchar(20), filesize varchar(40), path varchar(200), uptime date,  changetime date, about varchar(512));
--文件上传和下载情况统计 id,fileid,type(up/down),costtime(ms),time
create table file_down_up(id varchar(20) primary key, fileid varchar(40), type varchar(10), costtime varchar(40), time date );




create sequence SEQ_file_down_up
minvalue 1
maxvalue 99999999
start with 1
increment by 1
cache 20;

create sequence SEQ_fileinfo
minvalue 1
maxvalue 99999999
start with 1
increment by 1
cache 20;


create sequence SEQ_log_time
minvalue 1
maxvalue 99999999
start with 1
increment by 1
cache 20;

create sequence SEQ_info
minvalue 1
maxvalue 99999999
start with 1
increment by 1
cache 20;

create  sequence SEQ_student
minvalue 1
maxvalue 99999999
start with 1000
increment by 1
cache 20;
 
select SEQ_student.nextval from dual;


--饭票计算模块
---
day       personNum buyNum lastNum reason price costMoney
2018-03-13    14      13      0      ''       20    260
2018-03-12    14      14      1    'meet'     20    280
---
create table lunch(day varchar2(20) primary key, personNum varchar2(20), buyNum varchar2(20), lastNum varchar2(20), reason varchar2(800), price varchar2(20), costMoney varchar2(20));

---
day          name    orderName    price     
2018-03-14   xh      猪排           28     
---
create table dinner(day varchar2(20), name varchar2(20), orderName varchar2(200), price varchar2(20) );




