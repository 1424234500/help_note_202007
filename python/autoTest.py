#!/usr/bin/python
#-*- coding:utf-8 -*-  
 
import json
import re
import time
import traceback
import BeautifulSoup
import traceback

import tool
from http import Http
from robot import Robot
from tool import ThreadRun


class AutoSophia:
    def __init__(self, name="0000000", count = 0, makeRooms=[]):
        self.robot = Robot()
        self.http = Http()
        self.name = name
        self.count = count   #编号

        self.listMsgQue = []    #消息发送队列
        self.timeDetaMsgSend = 1.1    #最小发送消息间隔s

        self.makeRooms = makeRooms
        self.roomIndex = {} #房间号 及其<用户>信息
        self.roomMsg = {}   #消息 记录
        self.roomId = ""  #当前房号

############### 心情模块
        self.statusMin = 20
        self.statusMax = 95
        self.statusDefault = 80
        self.status = 90     #说话欲望值 0-100
        self.statusOnDeta = 15      #开心
        self.statusOffDeta = 15     #难过
        self.statusDownDeta = 40    #闭嘴

        self.getMsgDetaTime = 1     #抓取消息间隔
        self.lastMsgTime = int(time.time() * 10000 ) * 1.0 / 10000  #上一次更新房间聊天记录时间
        self.lastEchoTime = tool.getNowTime()   #上次说话时间
        self.maxDetaTime = 1000 * 60 * 3   # 最大沉默时间
        self.lastMusicTime = tool.getNowTime() 
        self.maxMusicTime = 1000 * 60 * 4 #音乐间隔 暂不解析音乐文件时长控制
        self.musicNow = {}
        self.musicPlayType = -1
        self.ifOnMusic = True
        self.tail = " の... "
    def out(self, obj):
        print(time.strftime("%Y%m%d %H:%M:%S", time.localtime()) + "." + self.name + "." + str(obj))
        return
    def login(self):
        # tool.line()
        self.out("访问主页 获取 token session")
        responce = self.http.doGet('http://drrr.com/')
        re = responce.read()
        soup =BeautifulSoup.BeautifulSoup(re)
        # self.out soup.prettify()
        nameList = soup.findAll('input',{'name':{'token'}})
        if(len(nameList) > 0):
            token = nameList[0]['data-value']
            token = tool.encode(token)
            self.out("抓取成功: ")
            self.out("token\t " + token)
            self.out("cookie\t " + tool.toString(self.http.getCookie()))

            # tool.line()
            self.out("模拟登录")
            responce=self.http.doPost('http://drrr.com/', {
                        "name":self.name,
                        "login":"ENTER",
                        "token":token,
                        "direct-join":"",
                        "language":"zh-CN",
                        "icon":"zaika-2x",
                })
        else:
            self.out("error！ 没能抓取到token")
    def createRoom(self, room=""):
        # tool.line()
        self.out("创建房间")
        if(room == ""):
            room = {}
            room["name"] = self.name + "'s room"
        responce=self.http.doPost("http://drrr.com/create_room/?", {
            "name":room.get("name",""),
            "description":room.get("description",""),
            "limit":room.get("limit",10),
            "music":room.get("music",True),
            "submit":room.get("music","创建房间"),
        })

    def help(self):
        self.out(dir(self))
    def showUser(self, user, show=True):
        userInfo ="U " + tool.fill(user.get("device", ""), ' ', 15) +  " " + tool.fill(user.get("icon", ""), ' ', 15) + " "  + user.get("name", "")
        if(show):
            self.out(userInfo)
        return userInfo
    def showRoom(self, roomId, show=True, i=0):
        room = self.roomIndex.get(roomId, "")
        if(room == ""):
            self.getRooms()
        room = self.roomIndex.get(roomId, "")
        info = ""
        if(room != ""):
            info = ("##" + tool.fill(str(i), '#', 40) + "\n--G " + tool.fill(room["id"], ' ', 15) + " " + tool.fill(str(room["total"]) + "/" + str(room["limit"]), ' ', 15) + " " + room["name"]) + "\n" 
            info = info + "music: " + str(room.get("music", False)) + " language:" + room.get("language","") +"\n"  # " 静态房间: " + str(room.get("staticRoom", "")) + ""
            # info = info + " hiddenRoom: " + str(room.get("staticRoom", "")) + " 游戏房间: " + str(room.get("gameRoom", "")) + " 成人房间: " + str(room.get("adultRoom", "")) + "\n"
            info = info + "Host:" + room.get("host", {}).get("name", "") + "\n"
            info = info + "Users: " + "\n"
            for item in room.get("users", []):
                info = info + "--" + self.showUser(item, False) + "\n"
        if(show):
            self.out(info)
        return info
    def showAllRoom(self):
        if(self.roomIndex is None or self.roomIndex == "" or self.roomIndex == {}):
            self.getRooms()
        tool.line()
        self.out("展示所有房间信息")
        i = 0
        for key in self.roomIndex:
            # room = self.roomIndex[key]
            self.showRoom(key, True, i)
            i = i+1
        tool.line()
    # 获取当前房间人员列表
    def getRoomUsers(self, roomId=""):
        room = self.roomIndex.get(roomId, {})
        users = room.get("users", [])
        return users
    # 获取用户所在房间
    def getUserRoom(self, userName="小氷", userId="8f1b61e25098b0427f01d724716b70cb"):
        i=0
        res = []
        for key in self.roomIndex:
            room = self.roomIndex[key]
            users = room.get("users", [])
            for user in users:
                if(user.get("name", "") == userName):
                    # self.showRoom(key, True, i)
                    res.append(room)
                if(user.get("id", "") == userId):
                    self.showRoom(key, True, i)
            i = i+1
        if(len(res) <= 0):
            self.out("用户不在线"+userName)
        if(len(res) >= 2):
            self.out("该用户多次出现？？？？？")
            for item in res:
                self.out(item)
            tool.line()
        return res
    def goRoomName(self, roomName):
        if(self.roomIndex is None or self.roomIndex == "" or self.roomIndex == {}):
            self.getRooms()
        tool.line()
        self.out("查找房间名字加入" + roomName)
        i = 0
        for key in self.roomIndex:
            room = self.roomIndex[key]
            name = room.get("name", "")
            if(re.search(roomName, name) != None):
                self.goRoom(key)
                break;
            i = i+1
        tool.line()

    def goRoom(self, roomId):
        # tool.line()
        self.out("加入房间:" + roomId)
        # self.showRoom(roomId)
        responce=self.http.doGet("http://drrr.com/room/?id=" + roomId)
        self.roomId = roomId
        # self.send("/me 大家好 我是暖手宝" + self.name + " 可以@ [点歌/turn/prev](*^_^*) @不一定会回 不@也不一定不会回(∩_∩) ")
        return
    def outRoom(self):
        self.out("离开房间:" + self.roomId)
        # self.send("/me " + self.name + "好无聊啊 "+self.name +"要出去溜达一会儿" + self.tail)
        # self.send("/me "+self.name+"一定会回来的" + self.tail)
        # self.send("/me 出去一下，马上回来" + self.tail)
        # self.showRoom(self.roomId)
        time.sleep(self.timeDetaMsgSend *  len(self.listMsgQue) + 1)  #等待一会儿消息发送
        responce=self.http.doPost("http://drrr.com/room/?ajax=1", {
                        "leave":"leave", 
                })
        self.roomId = ""
        if(responce == "error"):
            return False
        return True
    def getRooms(self, detail=False):
        # tool.line()
        self.out("获取房间列表")
        responce=self.http.doGet("http://drrr.com/lounge?api=json")
        jsonObj = tool.makeObj(json.loads(responce.read()))
        rooms = jsonObj["rooms"]
        if(len(rooms) > 0):
            self.roomIndex.clear()
        count = 0
        userCount = 0
        for i in range(len(rooms)):
            room = rooms[i]
            self.roomIndex[room["id"]] = room
            count = count + 1
            userCount = userCount + int(room.get("total", 0))
            # self.out("#" + str(i) + "\t" + room["id"] + " " + str(room["total"]) + "/" + str(room["limit"]) + "\t " + room["name"])
        self.out("共计房间" + tool.fill(str(count), ' ', 5) + " 用户" + tool.fill(str(userCount), ' ', 5) )
        # self.out("解析完毕")
        return rooms
    # 定时消息发送队列
    def doHello(self):
        while(True):
            if(self.roomId != ""):
                self.out("开启消息发送队列 deta=" + str(self.timeDetaMsgSend) + "ms")
                # self.listMsgQue = []
            while(self.roomId != ""):
                try:
                    detaTime = tool.getNowTime() - self.lastEchoTime
                    if(detaTime > self.timeDetaMsgSend): # 发送时差大于最小发送间隔
                        if(len(self.listMsgQue) > 0):
                            msg = self.listMsgQue.pop(0)
                            self.doSend(msg)
                    time.sleep(self.timeDetaMsgSend)
                except Exception as e:
                    self.out("消息发送异常 消息队列:")
                    self.out(self.listMsgQue)
                    self.out(traceback.format_exc())
            # self.out("当前房间roomId:" + self.roomId + " 未加入房间 暂时停止sayHello ")
            time.sleep(3)



    # 定时发送消息
    def sayHello(self):
        while(True):
            if(self.roomId != ""):
                self.out("开启定时发言，最大发言间隔" + str(self.maxDetaTime / 1000) + "s")
            dt = 0
            while(self.roomId != ""):
                try:
                    # message = "Now Time is "+ time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
                    detaTime = tool.getNowTime() - self.lastEchoTime # ms
                    if(detaTime > self.maxDetaTime):
                        message = "/me " + time.strftime("%Y%m%d %H:%M:%S")
                        self.send(message)
                        self.out(str(i) + "\t" + message)
                    detaTime = tool.getNowTime() - self.lastMusicTime # ms
                    if(self.ifOnMusic and detaTime > self.maxMusicTime and len(self.getRoomUsers(self.roomId)) > 1 ): #音乐开启 且 太久没放歌曲 且当前房间有至少两个人(包括自己robot)
                        self.playMusic()

                    if(dt % 300 == 0):
                        self.getRooms() #定时获取房间最新信息
                    time.sleep(10)
                    dt = dt + 10
                    dt = dt % 3600
                except Exception as e:
                    self.out(traceback.format_exc())
            # self.out("当前房间roomId:" + self.roomId + " 未加入房间 暂时停止sayHello ")
            time.sleep(3)
    # 定时抓取消息##########################
    def getHello(self):
        tt = self.getMsgDetaTime
        while(True):
            if(self.roomId != ""):
                self.out("开启抓取发言，" + str(tt) + "s/次")
            while(self.roomId != ""):
                try:
                    obj = self.rece()
                    if(obj != ""):
                        self.makeHello(obj)
                except Exception as e:
                    self.out(traceback.format_exc())
                time.sleep(tt)
            # self.out("当前房间roomId:" + self.roomId + " 未加入房间 暂时停止getHello ")
            time.sleep(3)
    # 抓取发言    json Obj
    def rece(self):
        # 获取最新时间的消息1530004210 157 s秒
        res = ""
        url = "http://drrr.com/json.php?update="+str(self.lastMsgTime)
        # self.out(url)
        responce=self.http.doGet(url)
        if(responce != "" and type(responce) != str ):
            jsonStr = responce.read()
            if(jsonStr != ""):
                res = tool.makeObj(json.loads(jsonStr))
            else:
                res = ""
        else:
            self.out("请求异常:" + str(responce) ) 
        return res

    # 发送消息-添加队列
    def send(self, message):
        if(message != None and message != ""):
            self.listMsgQue.append(message)
        return
    # 发送消息
    def doSend(self, message):
        if(message == ""):
            return
        self.out("Send." + message)
        responce=self.http.doPost("http://drrr.com/room/?ajax=1", {
                        "message":message, # [0:self.musicPlayType * 4],
                        "url":"",
                })
        # self.out("发送[" + message + "]" + re[0:66])
        self.lastEchoTime = tool.getNowTime()
        return

# 用户权限
    def getUserAuth(selfself, name=""):
        res = ""
        return res
    # 分享音乐
    def playMusic(self, url="", name="", fromName=""):
        self.musicPlayType = 0 #重置为随机播放

        if(url[0:4] != "http"): #无地址url则是定向点播
            if(name == ""): #无名字 则自动换
                music = self.robot.turnMusic(self.musicPlayType)
            else:
                self.send("/me 正在搜索歌曲[" + name + "]" + self.tail)
                music = self.robot.getMusic(name, fromName)
            url = music.get("url", "")
            name = music.get("name", "")
            fromName = music.get("fromName", "")
        if(fromName != ""):
            msg = ""
            rooms = self.getUserRoom(fromName)
            if(len(rooms) > 0):
                room = rooms[0]
                if(room.get("id","") == self.roomId): #在当前房间
                    pass
                    # msg = "/me 一首[" + name + "]送给" + fromName + "" + self.tail
                else:
                    pass
                    # msg = "/me Share " + room.get("name")[0:4] + "/" + fromName + "'s[" + name + "]" + "" + self.tail
            else:   #不在线
                pass
                # msg = "/me Then play" + fromName + " ordered [" + name + "]" + "" + self.tail
            self.send(msg)
        self.out("分享歌曲url=" + url + " name=" + name + " fromName=" + fromName )
        if(url == ""):
            # self.send("/me 怼不起,没有找到类似的歌曲,瑟瑟发抖"+self.tail)
            return
        responce=self.http.doPost("http://drrr.com/room/?ajax=1", {
                        "music":"music",
                        "name":name,
                        "url":url,
                })
        self.musicNow = {"url":url, "name":name, "fromName":fromName}
        self.lastMusicTime = tool.getNowTime()
        return
    def listMusic(self):
        self.out(self.robot.listMusic)
    # 切歌控制 on/off/turn/prev/next/remove
    def music(self, cmd="on"):
        self.out("music:" + cmd)
        if(cmd == "on"):
            self.ifOnMusic = True
            self.send("/me 已经打开音乐点播" + self.tail)
        elif(cmd == "off"):
            self.ifOnMusic = False
            self.send("/me 已经关闭音乐点播" + self.tail)
        elif(cmd == "turn"):
            self.ifOnMusic = True
            self.musicPlayType = 0
            self.playMusic()
        elif(cmd == "prev"):
            self.ifOnMusic = True
            self.musicPlayType = -1
            self.playMusic()
        elif(cmd == "next"):
            self.ifOnMusic = True
            self.musicPlayType = 1
            self.playMusic()
        elif(cmd == "remove"):
            self.robot.removeMusic(self.musicNow.get("url", ""))
            self.send("/me 降低音乐" + self.musicNow.get("name") + "播放频率 " + self.tail)

        return 
    # 手动控制
    def inputHello(self):
        self.out("开启输入监控！")
        self.help()
        while(True):
            try:
                cmd=raw_input("")
                if(cmd != ""):
                    if(not self.doMethod(cmd.split(" "))):
                        self.out("手动发送:" + cmd)
                        self.send(cmd)
                        time.sleep(1)
            except Exception as e:
                self.out(traceback.format_exc())
        return
    # 抓取到消息的auto回复
    def makeHello(self, obj):
        res = ""
        try:
            # tool.line()
            # self.out("抓取到消息obj")
            # self.out(obj)
            newTime = obj.get("update", self.lastMsgTime)
            newTime = int(newTime)
            # print(newTime)
            self.lastMsgTime = newTime
            talks = obj.get('talks', "")
            users = obj.get('users', "")
            if(users != ""):
                room = self.roomIndex.get(self.roomId, "")
                if(room != ""):
                    self.roomIndex[self.roomId]['users'] = users
                else:
                    self.roomIndex[self.roomId] = obj
            if(talks != ""):
                onceDocount = 0
                for item in talks:
                    # self.out(item)
                    msgTime = item.get("time", tool.getNowTime())
                    msgId = item.get('id', " ")
                    msgType = item.get('type', 'message')
                    msgData = ""
                    msgFromName = item.get('from', {}).get('name', "")
                    if(msgFromName == ""):
                        msgFromName = item.get('user', {}).get('name', "")

                    


                    if(msgType == 'me'):
                        msgData = item.get('content', "")
                    elif(msgType == 'message'):
                        msgData = item.get('message', "")
                    elif(msgType == 'join'):
                        # msgFromName = item.get('user', {}).get('name', "")
                        msgData = '欢迎' + msgFromName + self.tail
                    elif(msgType == 'leave'):
                        msgData = ' ' + msgFromName + ' 默默的离开了 ' + self.tail
                    elif(msgType == 'music'):
                        music = item.get('music', {})
                        name = music.get('name', '')
                        url = music.get('url', '')
                        # msgData = '悄悄的的把[' + name + ']给记在小本子上 '  + self.tail
######################################################## 不处理
                    if( self.roomMsg.get(msgId, "") != ""): #已经处理过 或者是自己发送的 或者取出发送者失败
                        # self.out("旧消息 " + msgId + " type:" + msgType + " data:" + msgData)
                        break

                    if(msgType == "me" or msgType == "message"): #只记录聊天消息
                        self.robot.addMsg(msgId, msgFromName, msgData, msgTime)
                    if( msgFromName == self.name or msgFromName == ""):
                        break
#############################################################

                    if(msgType == 'music'):
                        music = { "name":name, "url":url, "fromName":msgFromName }
                        res = self.robot.addMusic(music) #添加用户分享记录
                        if(res == 1):   #更新则不提示
                            msgData = ""
                        self.musicNow = music
                        self.lastMusicTime = tool.getNowTime()

                    self.roomMsg[msgId] = item #标记未已经处理 历史消息

                    if(self.status>self.statusMax):
                        self.status = self.statusMax
                    elif(self.status < self.statusMin):
                        self.status = self.statusMin

                    detaTime = tool.getNowTime() - self.lastEchoTime # ms 60s
                    olRan = tool.getRandom(0,self.maxDetaTime) / 1000    #0-180 过于久没有发过消息了 权重高则可能自回复
                    weight = (self.maxDetaTime - detaTime) / 1000   #多久没说话了 最大多长时间必须说话
                    ran = int(1.0 * olRan * (1+ 1.0 * (self.status-60) / 100) )

                    self.out("新消息 " + msgId + " 发言权" + tool.fill(str(weight) + "" , ' ', 6) + " 随机数" + tool.fill(str(olRan) + "->" + str(ran),' ', 6) + " from:" + tool.fill(msgFromName,' ',12) + " type:"+tool.fill(msgType,' ',6) + " data:" + msgData)

                    flag = 0 #不回复
                    if(msgType == 'message' or msgType == 'me' ):    #普通聊天消息
                        if( re.search('@' + self.name + " ", msgData) != None):    #有@自己 且权重不太低
                            msgData = re.sub('@' + self.name + " ", "", msgData) #摘除@自己
                            ran = tool.getRandom(0,100)
                            if(ran < self.status):
                                flag = 1
                            else:
                                self.out("@me 随机数=" + str(ran) + " 小于 说话欲望=" + str(self.status) + " ")
                                flag = 2
                                msg = "生气程度:" + str(100-self.status) + "%,不想搭理"+self.tail
                        elif(ran > weight and  re.search('@', msgData) == None): # 没有@ 且 权重高 主动搭话概率
                            flag = 1
                    else: #事件 
                        flag = 2

                    res = ""
                    if(self.filterFlag(msgData, msgFromName)):    #最高级 权限是否黑名单过滤
                        if(flag == 1):
                            if(self.robot.getUser(msgFromName).get("flag", "0") != "0"):
                                self.out("不想搭理" + msgFromName)
                            else:
                                if(self.filterCmd(msgData, msgFromName)):    #若过滤器未处理 则继续交由下面处理
                                    robotRes = self.robot.do(msgData, self.name)
                                    code = str(robotRes.get("code", ""))
                                    if(code[0:1] != '4'):
                                        res = '@' + str(msgFromName) +" " + robotRes.get("text", "")
                                    else:
                                        self.out("robot接口调用失败 code=" + code)
                        elif(flag == 2):
                            res = msg

                        if(res != "" and flag != 0 and onceDocount < 6): # 最多一次抓取发送3个
                            res = '/me ' + res
                            onceDocount = onceDocount + 1
                            self.send(res)
                        
        except Exception as e:
            self.out("Exception:" + str(e))
        # tool.line()
        return res
    # /do help   指令控制行为 
    def filterCmd(self, msgData="", fromName=""):
        res = True
        msgData = msgData.strip()
        flag = False
        size = len(msgData)

        pr = ['放音乐', '播放音乐', '放歌', '开启放歌']
        if(not flag):
            for item in pr:
                if(msgData == item):
                    msgData = ""
                    self.music("on")
                    flag = True
                    break
        pr = ['不要放音乐', '停止放歌','停止音乐', '别放歌', '关闭放歌','关闭音乐', '别放了']
        if(not flag):
            for item in pr:
                if(msgData == item):
                    msgData = ""
                    self.music("off")
                    flag = True
                    break
        pr = ['prev', '上一曲', '上一首', '换回去']
        if(not flag):
            for item in pr:
                if(msgData == item):
                    msgData = ""
                    self.musicPlayType = -1
                    flag = True
                    break
        nnn = ['下一曲','下一首', '切歌', '换','换歌', '不好听', '难听','难听死了', '换换换','换一首', 'next', 'turn']
        if(not flag):
            for item in nnn:
                if(msgData == item):
                    msgData = ""
                    flag = True
                    break
        ppp = ['点歌','music','歌曲','点播','下面播放', '想听', '播放', '放', 'play', 'mp3']
        if(not flag):
            for item in ppp:
                itemLen = len(item)
                index = msgData.find(item)
                if(index == 0): #头命中
                    msgData = msgData[itemLen:9999].strip()
                    flag = True
                    break
                elif(index > 0 and index == size - itemLen):# 尾命中
                    msgData = msgData[0:size-itemLen].strip()
                    flag = True
                    break
        ooo = [
            ('一首','献给大家'),
            ('一首','送给大家'),
            ('点','这首歌'),
        ]
        if(not flag):
            for before,after in ooo:
                index = msgData.find(before)
                if(index == 0):
                    index1 = msgData.find(after)
                    if(index1+len(after) == size):
                        flag = True
                        msgData = msgData[len(before):index1].strip()
                        break
        if(flag):#抽离点歌 名字
            self.out('filterCmd.' + str(flag) + "." + msgData)
            res = False
            self.playMusic(url="", name=msgData, fromName=fromName)
        elif( re.search('/do ', msgData) != None ): 
            res = False
            cmd = msgData[4:9999]
            cmd = cmd.strip()
            cmds = cmd.split(' ')
            if(len(cmds) > 0 and cmds[0] == ""):
                cmds.pop(0)

            if(not self.doMethod(cmds)):
                self.send("/me ########## @" + self.name + " /do music <on/off/turn/prev/next> ########")

        return res

    # [methodName arg1 arg2]
    def filterFlag(self, msgData="", fromName=""):
        res = True
        msgData = msgData.strip()
        flag = False
        size = len(msgData)
        msg = ""
        keys = ["别说话", "你别说话", "闭嘴", "shutup"]
        statusOn = ['笨蛋', '傻逼', 'sb', 'SB', 'Sb','sB', '傻b', '傻']
        statusOff = ['开心一点','开心点','我错了', '求你了', '后悔', '收回','我收回','对不起', '悔恨', '不要生气']


        if(not flag):
            for item in statusOff:
                if(msgData == item):
                    self.robot.turnUser(fromName, "0")
                    self.status = self.status + self.statusOnDeta
                    if(self.status >= self.statusMax + self.statusOnDeta):
                        msg = self.name + "现在没有生气(╯▔皿▔)╯"
                    elif(self.status >= self.statusDefault):
                        msg = self.name + "心情好转了 不生气了﹏"
                    else:
                        msg = self.name + "气消了一点点，生气值-" + str(self.statusOnDeta) + self.tail
                    flag = True
                    break
        if(self.robot.getUser(fromName).get("flag", "0") != "0"):   #限制黑名单只接受道歉
            res = True
            self.out("黑名单只接受道歉 不想搭理" + fromName)
            return res

        if(not flag):
            for item in keys:
                if(msgData == item):
                    self.status = self.status - self.statusDownDeta
                    msg = "好的" + ",生气值陡升" + str(self.statusDownDeta) + ",当前" + str(100-self.status) + "% "
                    flag = True
                    break
        if(not flag):
            for item in statusOn:
                if(msgData == item):
                    self.robot.turnUser(fromName, "1")
                    self.status = self.status - self.statusOffDeta
                    if(self.status <= self.statusMin - self.statusOffDeta):
                        msg = self.name + "已经气死了 没这号robot 😕"
                    elif(self.status <= self.statusMin):
                        msg = self.name + "已经气炸了 不想再说话了 ε=( o｀ω′)ノ "
                    else:
                        msg = self.name + "生气值暴涨" + str(self.statusOffDeta) + "，不想再搭理" + fromName + "了" + self.tail
                    flag = True
                    break

        if(flag):#状态控制
            self.out('filterFlag.' + str(flag) + "." + msgData)
            res = False
            self.send("/me " + msg)
        return res
    def doMethod(self, listArgs):
        size = len(listArgs)
        res = False
        if(size > 0):
            if(hasattr(self, listArgs[0])):
                method = getattr(self, listArgs[0])#获取的是个对象
                if(callable(method)):
                    if(size == 2):
                        method(listArgs[1]) 
                    elif(size == 3):
                        method(listArgs[1], listArgs[2])  
                    elif(size == 4):
                        method(listArgs[1], listArgs[2], listArgs[3]) 
                    elif(size == 5):
                        method(listArgs[1], listArgs[2], listArgs[3], listArgs[4]) 
                    else:
                        method()
                    res = True
                else:
                    self.out(method)
        return res

    def test(self):
        self.login()
        self.getRooms()
        # self.goRoom("YfdWkQ1lEs")
        self.goRoomName("上帝")
        ThreadRun( "DoSend." + str(self.count),  self.doHello ).start()
        ThreadRun( "SayHello." + str(self.count),  self.sayHello ).start()
        ThreadRun( "GetHello." + str(self.count),  self.getHello ).start()
        ThreadRun( "InputHello." + str(self.count),  self.inputHello ).start()


        tool.wait()
        return
    def test2(self):
        self.login()
        self.getRooms()
        self.createRoom()
        # self.goRoom("YfdWkQ1lEs")
        # self.goRoomName("上帝")
        ThreadRun( "DoSend." + str(self.count),  self.doHello ).start()
        ThreadRun( "SayHello." + str(self.count),  self.sayHello ).start()
        ThreadRun( "GetHello." + str(self.count),  self.getHello ).start()
        ThreadRun( "InputHello." + str(self.count),  self.inputHello ).start()

        tool.wait()
def testMake():
    a = AutoSophia("tt")
    a.test2()



if __name__ == '__main__':
    testMake()

# the admin
# akakoori