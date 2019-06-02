 啊d
d;
ss sdf from to_date(?, 'yyyy-mm-dd hh24:mi:ss') 
;
select 'true' ifadd, 'group' type,
g.id,g.username,g.profilepath,g.sign,g.profilepathwall,g.num 
from tb_user_group ug,tb_group g 
where ug.userid='100' and ug.groupid=g.id 


--查询用户 并附加 是否已添加 或者自己
select  nvl2( uu.friendid , 'true', (case when find.id='100' then 'self' else 'false' end)) ifadd, find.* from  
( select  'user' type, u.id, u.username, u.sex, u.profilepath, u.profilepathwall,u.sign, u.email from tb_user u  
where (u.username like '%1%' or u.id like '%1%' ) ) find 
left join tb_user_user  uu on  uu.friendid=find.id and uu.userid='100'

--查询群 并附加 是否已添加  
select  nvl2( ug.groupid , 'true', 'false') ifadd,find.* from  
( select  'group' as type, g.id,  g.username, g.num, g.profilepath, g.profilepathwall, g.sign  from tb_group g  
 where (g.username like '1000' or g.id like '1000' ) ) find  
left join tb_user_group  ug on   ug.groupid=find.id and ug.userid='100'
 
  
--会话 消息
 select * from tb_user;
  select * from tb_user_msg;
  update  tb_user_msg set status='1' where fromid='101' and toid='100'
  --insert into tb_user_msg(toid,fromid,type,status,time,msg) select * from tb_user_MSG;
select nvl2(uu.nickname,uu.nickname,u.username) name,um.*,u.profilepath from tb_user_msg um, tb_user u,tb_user_user uu where um.fromid=u.id and uu.userid=um.toid and uu.friendid=um.fromid and ((fromid='100' and toid='101') or (fromid='101' and toid='100'));
--适配器需要username,time,text,profilepath
select * from tb_add_apply;   
select * from tb_group   ; 
select * from tb_user_user  ; 
select * from tb_user_group order by userid FOR UPDATE; 

select * from tb_user_session order by id;  
select t.*,to_char(t.time,'yyyy-mm-dd hh24:mi:ss') time from tb_group_msg t order by t.time desc; 

select gm.*,g.username toname,u.username fromusername from 
tb_group_msg gm,tb_user u,tb_group g 
where gm.groupid=g.id and gm.fromid=u.id

select fromid,toid,type,status,msg,to_char(time,'yyyy-mm-dd hh24:mi:ss') time from tb_user_msg   order by time desc;  
select * from (  select um.*,u.username tousername from (  select um.*,u.username fromusername from tb_user_msg um, tb_user u where um.fromid=u.id(+) ) um,tb_user u where um.toid=u.id(+)   ) where 1=1 

select  t.*,to_char(t.time,'yyyy-mm-dd hh24:mi:ss') time from tb_login_info t   order by t.time desc;  
select * from tb_user_user  ; 
select * from tb_user  for update; 
 
 




--insert into tb_user_user (userid,friendid,nickname)  ( select id,'1424234500' friendid,'CC' cickname from tb_user);
--insert into tb_user_group (groupid,userid,nickname)  ( select id,'1424234500' friendid,'CC' cickname from tb_group);

select * from tb_group_msg ; 
select fromid,toid,type,status,msg,to_char(time,'yyyy-mm-dd hh24:mi:ss') time from tb_user_msg   order by time desc;  
select us.*, (select count(*) from tb_user_group ) nownum from tb_user_session us  order by us.id;  
 
select g.id,(select count(*) from tb_user_group ug where ug.groupid=g.id ) nownum  from tb_group g ;

select count(*) from tb_user_group ug group by ug.groupid;


--分组取第一条#############################
select  *  from (
select row_number() over ( partition by id order by time desc) rn, li.* from tb_login_info li 
)  where   rn=1 ;

select *  from tb_user_user  ; 
 select *  from  tb_login_info order by time desc;
select *  from tb_user_session ;  
select *  from tb_add_apply;   
 select *   from tb_user_msg  ;
 select *   from tb_group_msg ;
  select *  from tb_user_group ;
 select *   from tb_user ;
 select *   from tb_group ;
 
delete from tb_user_user  ; 
 delete from  tb_login_info  ;
delete from tb_user_session ;  
delete from tb_add_apply;   
 delete  from tb_user_msg  ;
 delete  from tb_group_msg ;
  delete from tb_user_group ;
 delete  from tb_user ;
 delete  from tb_group ;
delete from   download;


 delete from tb_user_group where group in (select id from tb_user);
 
update  tb_user set pwd=MD5('cc'||id||MD5('cc'||id||'123'));

select * from download;

select * from ( select * from tb_user where (email='100' or id='100') and pwd='123'  ) where rownum <= 1  args:[ 100, 100, 123
delete from tb_user_msg where time not in (select time from tb_user_msg where rownum > 7)

select '1' num,us.type,aa.yanzhen,aa.time,u.username,u.sex,u.sign,u.profilepath,
u.username||':'||aa.yanzhen||'请求添加好友' msg
 from tb_add_apply aa, tb_user u,tb_user_session us where  us.type='adduser' and u.id=aa.fromid and aa.toid='101' and us.id=aa.toid and us.toid=aa.fromid  

select '1' num,us.type,aa.yanzhen,to_char(aa.time,'yyyy-mm-dd hh24:mi') time,u.username name,u.username,u.id,u.sex,u.sign,u.profilepath,
u.username||':'||aa.yanzhen||',请求添加好友' msg from tb_add_apply aa, tb_user u,tb_user_session us 
where  us.type='adduser' and u.id=aa.fromid and aa.toid='100' 
and us.id=aa.toid and us.toid=aa.fromid 

select * from tb_add_apply;
select * from tb_user_group ;

select * from tb_group ;
 
--查询会话列表 级联相关信息
select * from tb_user_user  ;  

select u.id,u.username,u.pwd,MD5('cc'||u.id||MD5('cc'||u.id||'123')) pp from tb_user u for update ;
update  tb_user set pwd=MD5('cc'||id||MD5('cc'||id||'123'));


select MD5('cc'||'100'||MD5('cc'||'100'||'123')) from dual;

select * from tb_user_session  ;   
select SYSDATE from dual;
select us.*,u.username,u.profilepath,uu.nickname,nvl2(uu.nickname,uu.nickname,u.username) name from tb_user_session us, tb_user u,tb_user_user uu  where us.id='100' and us.toid=u.id and us.id=uu.userid and us.toid = uu.friendid 
--查询最新聊天记录一条 
select * from (
  select  msg,(case when to_char(time,'yyyy-mm-dd')=to_char( SYSDATE,'yyyy-mm-dd')  then to_char(time,'hh24:mi') else  to_char(time,'yyyy-mm-dd') end )time 
   from   (  select * from  tb_user_msg where ( fromid='100' and toid='102' ) or ( fromid='102' and toid='100' )  order by time desc )  
   
 ) where rownum <= 1

select msg,(case when to_char(time,'yyyy-mm-dd')=to_char( SYSDATE,'yyyy-mm-dd') then to_char(time,'hh24:mi') else  to_char(time,'yyyy-mm-dd') end )time from ( select  * from tb_user_msg where ( fromid='100' and toid='102' ) or ( fromid='102' and toid='100' ) order by time desc) where rownum <=1 




select * from ( select t.*,rownum rowno from ( 
select * from tb_user_msg order by time
 ) t where rownum < 10 ) where rowno > 2


