#!/usr/bin/env python
#-*- coding:utf-8 -*- 
from include import *

@singleton
class ServiceServer:
    users = {}
    keys = {}
    """ 
        Service 
        Return map by map
        Control the system
    """ 
    def __init__(self):
        self.db = ServiceDb()
        self.dao = Database()
    def do(self, fromMsg):
        data = fromMsg.data
        cmd = data.get("cmd", "")
        #消息处理 默认发给请求者
        msg = Msg()
        msg.toSysKey = fromMsg.fromSysKey
        msg.toKey = fromMsg.fromKey
        msg.data = {}
        msg.msgType = 10                #单点回传

        if(cmd != ""):
            msg.data["cmd"] = cmd
            msgs = self.doCmd(cmd, data, msg)
        else:
            # msg.data["res"] = "1"
            # msg.data["info"] = "info"
            msg.data["method"] = data.get("method", "no method ? ")
            try:
                msgs = self.doMethod(msg, msg.data["method"], data["params"])
            except Exception as e:
                print(e)
                msg.data["info"] = 'exception'
                msgs = [msg]
        return msgs




# 输入控制
    def doInput(self, cmd):
        msgs = []
        msg = Msg()
        msg.data = {"info":cmd}
        msg.info = "输入控制"
        if(cmd == "show"):
            msg.msgType = -1000
            msg.data["info"] = "显示用户列表"
            print("本地存储登录用户列表：" + str(len(self.users)))
            print(self.users)
        elif(cmd == "local"):
            msg.data["info"] = "本地广播"
            msg.msgType = -1
            pass
        else:
            pass
        msgs.append(msg)
        return msg
# 系统方法控制
    def doMethod(self, msg, method, params):
        # params = params.encode('utf-8')
        # method = method.encode('utf-8')

        # tool.doMethod(self, method, params)
        print("class:  " + self.__class__.__name__)    #className
        print("method: ", method)    #list
        print("params: ", params)    #:arg1: 'a1', arg2: 'a2' 
        #检查成员
        ret = hasattr(self, method) #因为有func方法所以返回True 
        if(ret == True) :
            #获取成员
            method = getattr(self, method)#获取的是个对象
            return method(msg, params) 
        else :
            print("Error ! 该方法不存在")
            msg.data["res"] = "false"
            msg.data["info"] = "该方法不存在"
            return [msg]

# left right head back space stop
    def move(self, msg, param):
        print("move", param)
        params = param.split("-")[0]
        if(params == 'left'):
            ModelMove().turnLeft()
        elif(params == 'right'):
            ModelMove().turnRight()
        elif(params == 'head'):
            ModelMove().moveHead()
        elif(params == 'back'):
            ModelMove().moveBack()
        elif(params == 'space'):
            ModelMove().space()
        elif(params == 'stop'):
            ModelMove().stop()
        elif(params == 'faster'):
            ModelMove().moveFaster(1)
        elif(params == 'slower'):
            ModelMove().moveFaster(-1)
        elif(params == 'movefasterto'):
            dc = param.split("-")[1]
            dc = int(dc)
            ModelMove().moveFasterTo(dc)
        elif(params == 'turnrevert'):
            ModelMove().turnRevert()
        elif(params == 'moveleft'):
            ModelMove().moveLeft()
        elif(params == 'moveright'):
            ModelMove().moveRight()

        msg.data["info"] = "move"
        return [msg]

# 0 1 
    def cameraTurn(self, msg, params):
        # obj = json.loads(params)
        ff = int(params)
        if(params == "0"):
            deta = 20
            (ifMove, info, costTime) = ModelTurn().turnDeta(deta)
        elif(params == "1"):
            deta = -20
            (ifMove, info, costTime) = ModelTurn().turnDeta(deta)
        elif(ff == -1):
            deta = 0
            (ifMove, info, costTime) = ModelTurn().turnTo()
        else:
            (ifMove, info, costTime) = ModelTurn().turnTo(ff)

        msg.data["res"] = 1
        msg.data["info"] = info + " " + str(costTime)
        msg.data["cmd"] = 2
        return [msg]
    def takePhoto(self, msg, params):

        photoPath = ""
        with open(path, 'rb') as f:
            byts = base64.b64encode(f.read())
            msg.data['id'] = id
            msg.data['res'] = byts
            msg.data['cmd'] = MSGTYPE.SYS_PHOTO_DETAIL # 图片数据
            self.serverSocket.sendImpl(msg.toString())




# 文件下载
    def file(self, msg, params):
        # print(params)
        id = params.get("id", "")
        filePath = C.filePath
        path = filePath + id
        if(id != ""):
            with open(path, 'rb') as f:
                byts = base64.b64encode(f.read())
                msg.data['id'] = id
                msg.data['res'] = byts
                msg.data['cmd'] = MSGTYPE.SYS_PHOTO_DETAIL # 图片数据
                return [msg]
        return []


    def login(self, msg, params):
        msg.data["info"] = params["id"] + "-" + params["pwd"]
        msg.data["res"] = 1
        msg.data["cmd"] = 2
        return [msg]





# cmd类型控制 
    def doCmd(self, cmd, params, msg):
        dc = self.db
        db = self.db
        dao = self.dao

        msgs = []
        # cmd: int GET_CHAT_SESSIONS = 10 
        # params: :"value":1, "value1":2
        # res msg
        if(cmd == MSGTYPE.REGISTE_BY_USERNAME_EMAIL_SEX_PWD):
            username = params["value0"]
            email = params["value1"]
            sex = params["value2"]
            pwd = params["value3"]
            res = -2
            map = dao.executeQuery("SELECT * FROM TB_USER WHERE EMAIL=? ", email)
            if(map is None or len(map) <= 0):
                id = tool.getUuid()
                # pwd = MD5.make(id,MD5.make(id, pwd))
                dao.execute("INSERT INTO TB_USER(ID, USERNAME, EMAIL, SEX, PWD,PROFILEPATH,PROFILEPATHWALL) VALUES(?, ?, ? ,?, ?,?,?) ", id, username, email, sex, pwd,tool.getRandom(0,20),tool.getRandom(0,20))
                res = 1
                info = id
            if(res == -2):#有重复
                res = "false"
                info = "该邮件已经被注册过了"
            elif(res == -1):#插入失败
                res = "false"
                info = "添加用户数据失败"
            elif(res >= 0):#插入成功,返回生成的用户id
                res = "true"
                #添加机器人cc好友
                dao.execute("INSERT INTO TB_USER_USER(USERID,FRIENDID,NICKNAME,TIME) VALUES(?,?,?,?) ", id, "1424234500","CC", tool.getNowTime())
                dao.execute("INSERT INTO TB_USER_USER(USERID,FRIENDID,NICKNAME,TIME) VALUES(?,?,?,?) ", C.robotId,id, "", tool.getNowTime())
            msg.makeMsg(res, info)
            pass
        elif(cmd == MSGTYPE.LOGIN_BY_ID_PWD):
            id = params["value0"]
            pwd = params["value1"]
            # pwd = MD5.make(id, pwd)  #客户端发送时先 MD5(cc+id+pwd)加密，这里再次加密,MD5(cc+id+MD5(cc+id+pwd))
            listMap = dao.executeQuery("SELECT * FROM TB_USER WHERE (EMAIL=? OR ID=?) AND PWD=?  ", id, id, pwd)
            if(listMap is not None and len(listMap) > 0):    #登陆成功

                map = listMap[0]
                msg.makeMsg("true", map)
                # client.loginOk(map)
                dao.execute("INSERT INTO TB_LOGIN_INFO(TIME, ID,  USERNAME, IP, STATUS) VALUES(?, ?, ?, ?, ?) ", tool.getNowTime(), map["id"], map["username"], "", "0")
                #向该用户的在线好友们发送通知上线下线
                msg2 = Msg()
                msg2.msgType = -1
                msg2.data["cmd"] = MSGTYPE.LINE_STATUS_ID_TYPE
                msg2.makeMsg("true", id)
                msgs.append(msg2)
                # 记录本地 syskey key 对应用户id 双向索引
                oldId = self.keys.get(msg.toKey, "")
                oldKey = self.users.get(oldId, "")
                self.users[oldId] = ""
                self.keys[oldKey] = ""
                self.users[map["id"]] = msg.toKey
                self.keys[msg.toKey] = map["id"]
            else:
                msg.makeMsg("false", "账号或密码错误")
            pass
        if(True or self.keys.get(msg.toKey, "") != "" ) :
            id = self.keys.get(msg.toKey)
            key = msg.toKey
            if(cmd == MSGTYPE.GET_CHAT_SESSIONS):       #会话列表
                msg = self.sendSession(id)
            elif(cmd == MSGTYPE.CONTACT_USER_GROUP_MAP):    #好友列表
                msg = self.sendContact(id)
            elif(cmd == MSGTYPE.FIND_USERS_GROUPS_BY_ID):    #搜索用户列表
                value = params["value0"]
                list1 = db.getUsersAdd(id, value)
                list2 = db.getGroupsAdd(id, value)
                list1 = list1 + list2
                msg.makeMsg("true", list1)
            elif(cmd == MSGTYPE.ADD_USER_GROP_BY_TYPE_ID_YANZHEN_NICKNAME):    #添加好友请求
                type = params["value0"]
                toid = params["value1"]
                nickname = params["value3"]
                yanzhen = params["value2"]
                if(type == "user"):
                    if(dc.ifAddUser(id, toid) is None):
                        map = dc.getAddApply(id, toid)
                        if(map is None):
                            dao.execSQL(" insert into "+C.TB_ADD_APPLY+" (type,status,fromid,toid,yanzhen,nickname,time ) values(?,?,?,?,?,?,?) ",type,"0",id,  toid,yanzhen,nickname, tool.getNowTime() )
                        #更新为未发送状态，若已存在
                        dao.execSQL(" update "+C.TB_ADD_APPLY+" set status=? where fromid=? and toid=? ", "0", id, toid)
                        if(toid != C.robotId):
                            #插入会话列表，系统提示消息@@@@@@@@@@@
                            if(dc.getUserSession(toid, id) is None):#这是不应该有的，未添加好友，可重复添加呢？
                                dao.execSQL("insert into tb_user_session (id,toid,type) values (?,?,?) ", toid, id, "adduser")
                            
                            if(self.keys.get(msg.toKey, "") != ""):     #在线发送会话添加
                                #dc.getClientById(id).send(MSG.GET_ADD_USER_GROP_BY_MAP, dc.getAddApply(id,toid))
                                msgs.append(self.sendSession(toid))
                                dao.execSQL(" update "+C.TB_ADD_APPLY+" set status=? where fromid=? and toid=? ", "1", id, toid)
                            msg.makeMsg("true","已发送请求")
                        else:#机器人直接添加
                            dao.execSQL("insert into tb_user_user(userid,friendid,nickname,time) values(?,?,?,?) ", id, C.robotId,"CC",Tools.getNowTime())
                            dao.execSQL("insert into tb_user_user(userid,friendid,nickname,time) values(?,?,?,?) ", C.robotId,id, "",Tools.getNowTime())
                            dao.execSQL("insert into tb_user_session (id,toid,type) values (?,?,?) ", id, toid, "user")
                            msgs.append(self.sendSession(msg, id))
                            msgs.append(self.sendContact(msg, id))
                    else:
                        msg.makeMsg("false","您已经添加了该用户")   
                else:
                    if(dc.ifAddGroup(id, toid) is None):
                        map = dc.getAddApply(id, toid)
                        if(map is None):
                            dc.execSQL(" insert into "+C.TB_ADD_APPLY+" (type,status,fromid,toid,yanzhen,nickname,time ) values(?,?,?,?,?,?,? ) ", 
                                                                        type,"0",id,  toid,yanzhen,nickname, tool.getNowTime() )
                        dc.execSQL(" update "+C.TB_ADD_APPLY+" set status=? where fromid=? and toid=? ", "0", id, toid)
                        map = dc.getGroup(toid)    #toid:加群id
                        if(map.get("checked", "") == "true"):
                            map = dc.getAddApply(id, toid)
                            dao.execSQL(" insert into " + C.TB_USER_GROUP + "(userid,groupid,time,nickname) values(?,?,?,? )  ", 
                                    id, toid, tool.getNowTime(), "")
                            dao.execSQL(" update "+C.TB_ADD_APPLY+" set status=? where fromid=? and toid=? ", "2", id, toid)
                            #更新该用户的联系人列表
                            msgs.append(self.sendContact(id))
                            #插入并更新该用户的会话列表
                            dao.execSQL("insert into tb_user_session (id,toid,type) values (?,?,?) ", id, toid, type)
                            msgs.append(self.sendSession(id))
                        else:
                            id = map["creatorid"]
                            dc.execSQL("delete from tb_user_session where (id=? and toid=?) or (id=? and toid=?) ", id, toid, toid, id)
                            dc.execSQL("insert into tb_user_session (id,toid,type) values (?,?,?) ", toid, id, "addgroup")
                            msgs.append(self.sendSession(id))
                    else:
                        msg.makeMsg("false","您已经添加了该群")   
            elif(cmd == MSGTYPE.RESULT_USER_GROP_BY_TYPE_ID_RESULT_NICKNAME):
                type = params["value0"]
                toid = params["value1"]
                if(type == "user"):
                #并发送提示添加成功？添加会话消息          #删除会话 
                    dao.execSQL("delete from tb_user_session where (id=? and toid=?) or (id=? and toid=?) ", id,toid,toid, id)
                 #更新添加记录表，并回送
                    if(params.get("value2","") == "1"):
                        #直接成功添加好友 测试 从申请表中提取信息加入好友关系表
                        map = dc.getAddApply(toid, id)
                        dao.execSQL(" insert into " + C.TB_USER_USER + "(userid,friendid,nickname,time) values(?,?,?,? )  ", map["fromid"],map["toid"],map["nickname"],tool.getNowTime() )
                        dao.execSQL(" insert into " + C.TB_USER_USER + "(userid,friendid,nickname,time) values(?,?,?,? )  ", map["toid"],map["fromid"], params.get("value3", ""),tool.getNowTime() )
                        dao.execSQL(" update "+C.TB_ADD_APPLY+" set status=? where fromid=? and toid=? ", "2", toid, id)
                        
                        msg.makeMsg("true","Have add friend:"+dc.getUser(toid).get("username"))
                        #并发送消息更新两边的好友列表
                        msgs.append(self.sendContact(id))
                        msgs.append(self.sendContact(toid))
                        dao.execSQL("insert into tb_user_session (id,toid,type) values (?,?,?) ", id, toid, type)
                        dao.execSQL("insert into tb_user_session (id,toid,type) values (?,?,?) ", toid, id, type)
                        msgs.append(self.sendSession(id))
                        msgs.append(self.sendSession(toid))
                    else:
                        dao.execSQL(" update "+C.TB_ADD_APPLY+" set status=? where fromid=? and toid=? ", "4", toid, id)
                    msg.makeMsg("true")
                else:
                    dao.execSQL("delete from tb_user_session where (id=? and toid=?) or (id=? and toid=?) ", id,toid,toid, id)
                    toid = params["value1"]
                    id = params["4"]
                    map = dao.getAddApply(toid, id)
                    if(params.get("value2","") == "1"):
                        name = dao.getUser(toid).get("username", "nobody")
                        dao.execSQL(" insert into " + C.TB_USER_GROUP + "(userid,groupid,nickname,time) values(?,?,?,? )  ", map["fromid"],map["toid"], name,tool.getNowTime() )
                        dao.execSQL(" update "+C.TB_ADD_APPLY+" set status=? where fromid=? and toid=? ", "已同意",  map["fromid"],map["toid"])
                        msgs.append(self.sendContact(toid))
                        dc.execSQL("insert into tb_user_session (id,toid,type) values (?,?,?) ", toid, id, type)
                        msgs.append(self.sendSession(toid))
                    else:
                        dao.execSQL(" update "+C.TB_ADD_APPLY+" set status=? where fromid=? and toid=? ", "已拒绝",map["fromid"],map["toid"])
                    msg.makeMsg("true") 
            elif(cmd == MSGTYPE.SEND_CHATMSG_BY_GTYPE_TOID_TYPE_TIME_MSG): #发送消息
                gtype = params["value0"]
                toid = params["value1"]
                type = params["value2"]
                time = tool.getNowTime()
                msgg = params["value4"]
                if(gtype == "user"): 
                    status = "0"   #0未推送
                    dao.execSQL("insert into tb_user_msg(fromid,toid,type,status,time,msg) values(?,?,?,?,?,?)", id,toid,type,status, time,msgg)
                    msg2 = msg.makeMsg("true", dc.getUserMsgBy(id,toid,type,time,msgg))
                    msg2.toKey = self.users.get(toid, "")
                    msgs.append(msg2)
                    #若目标没有与其的会话列表,则添加
                    if(dc.getUserSession(toid, id) is None):
                        dao.execSQL("insert into tb_user_session (id,toid,type) values (?,?,?) ", toid, id, gtype)
                else:
                    dao.execSQL("insert into tb_group_msg(fromid,groupid,type,time,msg) values(?,?,?,?,?)",  id,toid,type, time,msgg)
                    listMap = dc.getUserByGroup(toid);
                    for map in listMap:
                        if(dc.getUserSession(map["userid"], toid) is None):
                            dao.execSQL("insert into tb_user_session (id,toid,type) values (?,?,?) ", map["userid"], toid, gtype);
                        if(self.users.get(map["userid"], "") != ""):
                            toid = map["userid"]
                            msg2 = Msg()
                            msg2 = msg.makeMsg("true", dc.getGroupMsgBy(id,toid,type,time,msgg))
                            msg2.toKey = self.users.get(toid, "")
                            msgs.append(msg2)
                    msg.makeMsg("true")
            elif(cmd == MSGTYPE.GET_USER_GROUP_CHAT_BY_TYPE_ID_START_HISTORY or cmd == MSGTYPE.GET_USER_GROUP_CHAT_BY_TYPE_ID_START):  # 聊天记录
                type = params["value0"]
                toid = params["value1"]
                start = params.get("value2", "")
                if(start == ""):
                    start = tool.getNowTime()
                listMap = []
                if(type == "user"): 
                    listMap = dc.getUserMsgs(id, toid, start, 20)
                elif(type == "group"):
                    listMap = dc.getGroupMsgs(toid, start, 20)
                msg.makeMsg("true", listMap)
            elif(cmd == MSGTYPE.CREATE_GROUP_BY_NAME_NUM_CHECK):  # 创建群
                gid = tool.getUuid()
                dao.execSQL("insert into " + C.TB_GROUP + "(id, creatorid,username,profilepath,profilepathwall,num,checked) values(?, ?, ? ,?, ?,?,?) ", 
                            gid, id, params["value0"],tool.getRandom(0,20),tool.getRandom(0,20), params["value1"], params["value2"] )
                msg.makeMsg("true", "创建群成功，ID:" + str(gid))
                # #并加入 该群，群组退群则删群，删群消息，删群成员记录
                dao.execSQL("insert into tb_user_group(userid,groupid,time) values(?,?,?)", id, gid, tool.getNowTime())
                msgs.append(self.sendContact(id))
            elif(cmd == MSGTYPE.FIND_USERS_BY_GROUPID):    #查找某群的用户列表
                gid = params["value0"] #目标群id
                listMap = dc.getGroupUsersEx(id, gid)
                msg.makeMsg("true", listMap)
            


            else:
                print(cmd, params, msg)
                pass
        else:
            pass
        msgs.append(msg)
        return msgs

#发送会话列表
    def sendSession(self, id):
        dc = self.db
        db = self.db
        # if(self.users.get(id, "") == ""):#不在线
        #     return "" 
        msg = Msg()
        msg.msgType = 10
        msg.data["cmd"] = MSGTYPE.GET_CHAT_SESSIONS
        msg.toKey = self.users.get(id, "")
        print("====Session list", id)
        listMap = dc.getUserSessionsById(id)
        #组装每个会话的最新消息
        for lmap in listMap:
            map = db.getUserMsg(id, lmap["id"])
            j = dc.getUserMsgCount(id, lmap["id"] )
            if(map is not None):
                lmap["MSG"] = map["msg"]
                lmap["TIME"] = map["time"]
                lmap["MSGTYPE"] = map["msgtype"]
                lmap["NUM"] = j
            else:
                lmap["MSG"] = ""
                lmap["MSGTYPE"] = ""
                lmap["TIME"] = ""
                lmap["NUM"] = j
            if(self.users.get("id", "") == "" and lmap["id"] != C.robotId ):
                lmap["STATUS"] = "[离线]"
            else:
                lmap["STATUS"] = "[在线]"
                pass


        list2 = dc.getGroupSessionsById(id);
        for lmap in list2:
            map = dc.getGroupMsg(lmap["id"]);
            j = dc.getGroupMsgCount(lmap["id"], dc.getUserLastLoginOutTime(id));
            if(map is not None):
                lmap["MSG"] =  map["msg"]
                lmap["TIME"] = map["time"]
                lmap["MSGTYPE"] =  map["msgtype"]
            else:
                lmap["MSG"] = ""
                lmap["MSGTYPE"] = ""
                lmap["TIME"] = ""
            lmap["NUM"] =  j
            lmap["STATUS"] = ""
        listMap = listMap + list2
        listMap = listMap + dc.getAddApplySessionUser(id)
        listMap = listMap + dc.getAddApplySessionGroup(id)
        

        if(listMap is None or len(listMap) <= 0):
            msg.makeMsg("false", "没有任何会话")
        else:
            msg.makeMsg("true", listMap)
        print("====Res", listMap)
        return msg
#发送好友列表
    def sendContact(self, id):
        dc = self.db
        # if(self.users.get(id, "") == ""):#不在线
        #     return "" 
        msg = Msg()
        msg.msgType = 10
        msg.data["cmd"] = MSGTYPE.CONTACT_USER_GROUP_MAP
        msg.toKey = self.users.get(id, "")
        i=0
        onlineCount = 0
        friendCount = 0
        groupCount = 0

        list1 = dc.getMyFriendsById( id)
        list2 = dc.getMyGroupsById(id)        #组装每个会话的最新消息
        listMap = list1 + list2

        for lmap in listMap:
            type = lmap["type"]
            id = lmap["id"]
            if(type == "user"): #查看好友是否在线并附加字段
                friendCount += 1
                if(self.users.get(id, "") == "" and id != C.robotId):
                    lmap["STATUS"] = "[离线]"
                else:
                    lmap["STATUS"] = "[在线]"
                    onlineCount += 1
            elif(type == "group"):
                groupCount += 1
        map  = {}
        listType = []
        map["USERNAME"] = "我的好友"
        map["NUM"] = friendCount
        map["ONNUM"] = onlineCount
        map["START"] = 0
        listType.append(map)
        map  = {}
        map["USERNAME"] = "群组"
        map["NUM"] = groupCount
        map["ONNUM"] = groupCount 
        map["START"] = friendCount 
        listType.append(map)
            
        if(listMap is None or len(listMap) <= 0):
            msg.makeMsg("false", "没有任何会话")
        else:
            msg.makeMsg("true", listType, listMap)

        
     
        return msg





 
    def toString(self):
        res = "" 

        return res

        