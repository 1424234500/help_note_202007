#!/usr/bin/env python
#-*- coding:utf-8 -*- 
from include import *

""" 
    数据库service
""" 
#   db = database()
#   count,listRes = db.executeQueryPage("select * from student where id=? and name like ? ", 2, 10, "id01", "%name%")
#   listRes = db.executeQuery("select * from student where id=? and name like ? ", "id01", "%name%")
#   db.execute("delete from student where id=? ", "id01")
#   count = db.getCount("select * from student ")
#   db.close()
#
@singleton
class ServiceDb:
    def __init__(self):
        self.db = Database()
    def insertFile(self, id, time, path):
        self.db.execute('insert into file values(?, ?, ?) ', id, time, path)

    def insertSocket(self, id, time, msg):
        self.db.execute('insert into socket values(?, ?, ?) ', id, time, msg)



# ################常用查询
    def getUser(self, id) :
        return self.db.executeQueryOne("select  'user' type, id, username, sex, profilepath, profilepathwall, sign ,email  from "+C.TB_USER + " where  id=?  ", id)
    
    def getGroup(self, id) :
        return  self.db.executeQueryOne("select 'group' as type, id, username, num, profilepathwall profilepath, profilepathwall, sign ,creatorid,checked  from "+C.TB_GROUP + " where id=?  ", id)
    
    def getGroupByCreatorid(self, id) :
        return  self.db.executeQueryOne("select 'group' as type, id, username, num, profilepathwall profilepath, profilepathwall, sign ,creatorid  from "+C.TB_GROUP + " where creatorid=?  ", id)
    
    def getGroupByGroupidCreatorid(self, groupid,  cid) :
        return  self.db.executeQueryOne("select 'group' as type, id, username, num, profilepathwall profilepath, profilepathwall, sign ,creatorid  from "+C.TB_GROUP + " where id=? and creatorid=?  ", groupid, cid)
    
    def getAddApply(self, id,  toid) :
        return  self.db.executeQueryOne("select yanzhen,time,fromid,toid,nickname from "+C.TB_ADD_APPLY + " where fromid=? and toid=?   ", id,toid)
       
    def getAddApplySessionUser(self, id) :
        return  self.db.executeQuery("select '1' num,us.type,aa.yanzhen,aa.time,u.username name,u.username,u.id,u.sex,u.sign,u.profilepath,u.username||':'||aa.yanzhen||',请求添加好友' msg from "+C.TB_ADD_APPLY + " aa, tb_user u,tb_user_session us where  us.type='adduser' and u.id=aa.fromid and aa.toid=? and us.id=aa.toid and us.toid=aa.fromid  ", id)
    
    def getAddApplySessionGroup(self, id) :
        return  self.db.executeQuery("select '1' num,us.type,aa.toid groupid,aa.yanzhen,aa.time,u.username name,u.username,u.id,u.sex,u.sign,u.profilepath,u.username||':'||aa.yanzhen||',请求加群'||tg.username msg from tb_add_apply aa, tb_user u,tb_user_session us,tb_group tg where us.type='addgroup' and us.id=? and us.toid=aa.fromid and aa.toid=tg.id and tg.creatorid=us.id and tg.id=aa.toid and us.toid=u.id   ", id)
    
    
    
    def getGroups(self, about) :
        return  self.db.executeQuery("select 'group' as type, id, username, num, profilepathwall profilepath, profilepathwall, sign  from "+C.TB_GROUP + " where username like ? or id like ?  ", "%"+about+"%", "%"+about+"%")
    
    def getUsers(self, about) :
        return  self.db.executeQuery("select  'user' type, id, username, sex, profilepath, profilepathwall,sign, email from "+C.TB_USER + " where username like ? or id like ?  ", "%"+about+"%", "%"+about+"%")
    
    
    def getGroupUsersEx(self, selfId,  groupid) :
        return  self.db.executeQuery("select   username name,ifnull( uu.friendid , 'false') ifadd, find.* from "
                + " ( select  'user' type, u.id, u.username groupnickname,u.username, u.sex, u.profilepath, u.profilepathwall,u.sign, u.email from tb_user u,tb_user_group ug   "
                + " where ug.groupid=? and ug.userid=u.id  ) find  "
                + " left join tb_user_user  uu on  uu.friendid=find.id and uu.userid=? ", groupid, selfId)
    
    #查找
    def getUsersAdd(self, selfId,  findId) :
        return  self.db.executeQuery("select  ifnull( uu.friendid , 'false') ifadd, find.* from "
                + " ( select  'user' type, u.id, u.username name,u.username, u.sex, u.profilepath, u.profilepathwall,u.sign, u.email from tb_user u   "
                + " where (u.username like ? or u.id like ? ) ) find  "
                + " left join tb_user_user  uu on  uu.friendid=find.id and uu.userid=? ", "%"+findId+"%", "%"+findId+"%", selfId)
    
    #查找
    def getGroupsAdd(self, selfId,  findId) :
        return  self.db.executeQuery("select  ug.groupid ifadd,find.* from  "
                + " ( select  'group' as type, g.id,  g.username name, g.username, g.num,  g.profilepathwall  profilepath , g.profilepathwall, g.sign,g.creatorid,g.checked,(select count(*) from tb_user_group ug where ug.groupid=g.id ) nownum   from tb_group g  "
                + " where (g.username like ? or g.id like ? ) ) find  "
                + " left join tb_user_group  ug on   ug.groupid=find.id and ug.userid=? ", "%"+findId+"%", "%"+findId+"%", selfId)
    
    
    def ifAddUser(self, userid,  friendid):
        return self.db.executeQueryOne("select userid  from "+C.TB_USER_USER + " where  userid=? and friendid=? ", userid, friendid)
    
    def ifAddGroup(self, userid,  groupid):
        return self.db.executeQueryOne("select userid  from "+C.TB_USER_GROUP + " where  userid=? and groupid=? ", userid, groupid)
    

    #查询id的好友集合，关联tb_user_user,查询信息组装nickname,并判断在线与否
    def getMyFriendsById(self, id) :
        return self.db.executeQuery( "select 'true' ifadd, 'user' type,u.id,ifnull(u.username,u.username) name,u.username,u.email,u.sex,u.profilepath,u.sign,u.profilepathwall,ifnull(u.username,' ') nickname  from tb_user_user uu,tb_user u where uu.userid=? and u.id=uu.friendid", id)
    
    def getMyGroupsById(self, id) :
        return self.db.executeQuery( "select 'true' ifadd, 'group' type,g.id,g.username name,g.username, g.profilepathwall  profilepath,g.sign,g.profilepathwall,g.num,g.creatorid,g.checked,(select count(*) from tb_user_group ug where ug.groupid=g.id ) nownum from tb_user_group ug,tb_group g where ug.userid=? and ug.groupid=g.id " , id)
    
    #查询个人会话列表  级联相关信息,用做前端显示列表,#好友会话列表
    def getUserSessionsById(self, id) :
        return self.db.executeQuery( " select us.type,us.toid id,u.username,u.profilepath,u.username,u.username name from tb_user_session us, tb_user u,tb_user_user uu  where us.id=? and us.toid=u.id and us.id=uu.userid and us.toid = uu.friendid and (us.type='user' )" , id)
    
    #查询个人会话列表  级联相关信息,用做前端显示列表,#好友会话列表
    def getGroupSessionsById(self, id) :
        return self.db.executeQuery( " select us.type,us.toid id,u.username,u.profilepathwall profilepath,u.username nickname,u.username name from tb_user_session us, tb_group u,tb_user_group uu  where us.id=? and us.toid=u.id and us.id=uu.userid and us.toid = uu.groupid and (  us.type='group')" , id)
    
    #查询某人对某人的会话映射,只用作判断是否已有会话列表
    def getUserSession(self, id,  toid) :
        return self.db.executeQueryOne( "select * from tb_user_session where id=? and toid=?" , id, toid)
    
     
    #查询对某人聊天记录
    def getUserMsgs(self, id,  toid,  starttime,  size) :
        count = self.db.getCount(" select * from tb_user_msg um,tb_user u,tb_user_user uu where (( fromid=? and toid=? ) or ( fromid=? and toid=? )) and u.id=um.fromid and uu.userid=um.toid and uu.friendid=um.fromid and um.time < ?  " , id, toid, toid, id, starttime)
        start = count-size
        if(start < 0):
            start = 0
        #并更新这些数据的status为已读
        self.db.execSQL(" update  tb_user_msg set status='1' where fromid=? and toid=? ", toid, id)
        #根据时间顺序，查询starttime最近的size10条数据        
        # return self.db.executeQuery( "  select * from ( select t.*,rownum rowno from   ( "
        #         + " select  ifnull(u.username,u.username) username,u.profilepath,um.fromid,um.toid,um.type,um.time,msg from tb_user_msg um,tb_user u,tb_user_user uu where (( fromid=? and toid=? ) or ( fromid=? and toid=? )) and u.id=um.fromid and uu.userid=um.toid and uu.friendid=um.fromid"
        #         + " and um.time < ?  order by um.time  "
        #         + "  ) t  )  where rowno>? and rowno<=? " , id, toid, toid, id, starttime,count-size, count )
        return self.db.executeQueryOffset(  
                " select  ifnull(u.username,u.username) username,u.profilepath,um.fromid,um.toid,um.type,um.time,msg from tb_user_msg um,tb_user u,tb_user_user uu where (( fromid=? and toid=? ) or ( fromid=? and toid=? )) and u.id=um.fromid and uu.userid=um.toid and uu.friendid=um.fromid"
                + " and um.time < ?  order by um.time  "
               ,start, size, id, toid, toid, id, starttime)

    
    #查询对某人聊天记录
    def getUserMsgBy(self, id,  toid,  type,  time,  msg) :
        return self.db.executeQuery( " select  'user' sessiontype, ifnull(u.username,u.username) username,u.profilepath,um.fromid,um.toid,um.type,um.time,msg from tb_user_msg um,tb_user u,tb_user_user uu where (( fromid=? and toid=? )  ) and u.id=um.fromid and uu.userid=um.toid and uu.friendid=um.fromid and type=? and msg=? and um.time=?  " , id, toid, type,msg,time)
    
    #查询对某人聊天记录
    def getGroupMsgs(self, toid,  starttime,  size) :
        count = self.db.getCount(" select * from tb_group_msg where  groupid=? and time<?  ", toid, starttime )
        start = count-size
        if(start < 0):
            start = 0
        #根据时间顺序，查询starttime最近的size10条数据        
        # return self.db.executeQuery( "  select * from ( select t.*,rownum rowno from   ( "
        #         + " select  ifnull(ug.nickname,u.username) username,u.profilepath,gm.fromid,gm.groupid,gm.type,gm.time,gm.reltime,msg from tb_group_msg gm,tb_user u,tb_user_group ug where (( gm.groupid=? )) and u.id=gm.fromid and gm.fromid=ug.userid(+) and gm.groupid=ug.groupid(+) "
        #         + " and gm.time < ?  order by gm.time  "
        #         + "  ) t  )  where rowno>? and rowno<=? " , groupid, starttime,count-size, count )
        return self.db.executeQueryOffset(  
                " select  ifnull(ug.nickname,u.username) username,u.profilepath,gm.fromid,gm.groupid,gm.type,gm.time,msg from tb_group_msg gm,tb_user u,tb_user_group ug where gm.groupid=? and u.id=gm.fromid and gm.fromid=ug.userid and gm.groupid=ug.groupid "
                + " and gm.time < ?  order by gm.time  "
               ,start, size, toid, starttime)
    
    #查询对某群聊天记录 
    def getGroupMsgBy(self, id,  toid,  type,  time,  msg) :
        return self.db.executeQuery( " select  'group' sessiontype, u.username,u.profilepath,gm.groupid toid,gm.fromid,gm.type,gm.time, gm.msg msg from tb_group_msg gm,tb_group g,tb_user_group ug,tb_user u where u.id=gm.fromid and (( gm.fromid=? and gm.groupid=? )  ) and g.id=gm.groupid and ug.groupid=gm.groupid and ug.userid=gm.fromid and gm.type=? and gm.msg=? and gm.time=?  " , id, toid, type,msg,time)
    
    def getRobotGroupMsgBy(self, id,  toid,  type,  time,  msg) :
        return self.db.executeQuery( " select  'group' sessiontype,   u.username,u.profilepath,gm.groupid toid,gm.fromid,gm.type,gm.time time, gm.msg msg from tb_group_msg gm,tb_group g,tb_user u where u.id=gm.fromid and (( gm.fromid=? and gm.groupid=? )  ) and g.id=gm.groupid and gm.type=? and gm.msg=? and gm.time=?  " , id, toid, type,msg,time)
    
    #查询对某人聊天记录 最新一条
    def getUserMsg(self, id,  toid) :
        return self.db.executeQueryOne( "  select  type msgtype, msg, time "
                + "from   (  select * from  tb_user_msg where ( fromid=? and toid=? ) or ( fromid=? and toid=?  )  order by time desc )   " , id, toid, toid, id)
    
    #获取对某人聊天记录未读条数
    def  getGroupMsgCount(self, toid,  time) :
        return self.db.getCount("select * from tb_group_msg where  groupid=? and time>=?  ", toid, time )
    
    #查询某群聊天记录 最新一条
    def getGroupMsg(self, id ) :
        return self.db.executeQueryOne( "select  type msgtype,  msg, time from   (  select gm.*,ug.nickname nickname,u.username username from  tb_group_msg gm, tb_user u,tb_user_group ug where  gm.groupid=? and u.id=gm.fromid and gm.fromid=ug.userid  order by gm.time desc ) " , id )
    
    #获取用户上次下线时间
    def  getUserLastLoginOutTime(self, id):
        map = self.db.executeQueryOne(" select time from tb_login_info where id=? and status='1' order by time desc ", id) 
        if(map is None):
            return "1970-10-10 12:12:12"
         
        return map.get("TIME").to()
    
    #获取对某人聊天记录未读条数
    def  getUserMsgCount(self, id ,  fromid) : #fromid发给我id的未读的条数
        return self.db.getCount("select * from tb_user_msg where fromid=? and toid=? and status='0' ", fromid, id)
    
    
    def getUserByGroup(self, groupid):
        return self.db.executeQuery( " select  userid from tb_user_group where groupid=? ", groupid)
    











    def init(self):
        db = self.db

# 文件模块
        db.execute( ''' create table if not exists file( id text primary key,time    text not null, path    text  ) '''  )
# socket日志
        db.execute( '''  create table if not exists socket( id      text primary key, time    text not null, msg     text ) ''' )


# 聊天模块
        db.execute( '''CREATE TABLE  IF NOT EXISTS TB_GROUP(self, id TEXT, CREATORID TEXT NOT NULL, USERNAME TEXT NOT NULL, PROFILEPATH TEXT,PROFILEPATHWALL TEXT, SIGN TEXT,  NUM TEXT, CHECKED TEXT, PRIMARY KEY(ID) )''')
        db.execute( '''CREATE TABLE  IF NOT EXISTS TB_USER(self, id TEXT, USERNAME TEXT, EMAIL TEXT UNIQUE, SEX TEXT, PWD TEXT,PROFILEPATH TEXT,PROFILEPATHWALL TEXT, SIGN TEXT , PRIMARY KEY(ID) )''')
        db.execute( '''CREATE TABLE  IF NOT EXISTS TB_LOGIN_INFO( TIME TEXT, ID TEXT, USERNAME TEXT, IP TEXT, STATUS TEXT )''')
        db.execute( '''CREATE TABLE  IF NOT EXISTS TB_USER_USER(USERID TEXT, FRIENDID TEXT, NICKNAME TEXT, TIME TEXT, PRIMARY KEY(USERID, FRIENDID) )''')
        db.execute( '''CREATE TABLE  IF NOT EXISTS TB_USER_GROUP(USERID TEXT, GROUPID TEXT,NICKNAME TEXT, TIME TEXT, PRIMARY KEY(USERID,GROUPID) )''')
        db.execute( '''CREATE TABLE  IF NOT EXISTS TB_USER_GROUP(USERID TEXT, GROUPID TEXT,NICKNAME TEXT, TIME TEXT, PRIMARY KEY(USERID,GROUPID) )''')
        db.execute( '''CREATE TABLE  IF NOT EXISTS TB_ADD_APPLY(TYPE TEXT, STATUS TEXT, FROMID TEXT, TOID TEXT, NICKNAME TEXT, YANZHEN TEXT, TIME TEXT, PRIMARY KEY(FROMID, TOID) )''')
        db.execute( '''CREATE TABLE  IF NOT EXISTS TB_USER_SESSION (ID TEXT, TOID TEXT, TYPE TEXT ,PRIMARY KEY(ID, TOID, TYPE)  )''')  
        db.execute( '''CREATE TABLE  IF NOT EXISTS TB_GROUP_MSG(GROUPID TEXT, FROMID TEXT,TYPE TEXT, TIME TEXT, MSG TEXT)''')
        db.execute( '''CREATE TABLE  IF NOT EXISTS TB_USER_MSG(FROMID TEXT, TOID TEXT,TYPE TEXT, STATUS TEXT, TIME TEXT, MSG TEXT)''')
        db.execute( '''CREATE TABLE  IF NOT EXISTS DOWNLOAD(ID TEXT, NAME TEXT, FILESIZE TEXT, TYPE TEXT, PATH TEXT)''')

        return





  