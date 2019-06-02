#!/usr/bin/env python
#-*- coding:utf-8 -*-  

import os


robotId = "1424234500"



#数据库表
    
#登录记录
TB_LOGIN_INFO = "tb_login_info"; #time, id,  username, ip
#用户表
TB_USER = "tb_user"; #id, username, email, sex, pwd, profilepath, sign
#群组表
TB_GROUP = "tb_group";   #id, creatorId, username, profilepath, sign,  num
#用户-群表：userid,groupid,time
TB_USER_GROUP = "tb_user_group";  
#用户好友表：userid,friendid,nickname,time
TB_USER_USER = "tb_user_user";    
#添加好友/群 申请表：type, status<, 在线推送问题,不在线存储等待上线推送
#user0添加好友-未发送
#user1添加好友-已发送
#user2添加好友-已同意 
#user20添加好友-已同意-已回送 
#user3添加好友-已拒绝
#user30添加好友-已拒绝-已回送 
#><group0添加群 类似>   ,fromid,toid,nickname,yanzhen,time
TB_ADD_APPLY= "tb_add_apply";

filePath = '/mnt/e/nginx-rtmp/'
if(not os.path.exists(filePath)):
    filePath = '/home/pi/resource/'
    



