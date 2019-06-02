#!/usr/bin/python
#-*- coding:utf-8 -*-

import re
import sys
import time
import json
import traceback
import uuid
import ast
import tool
import BeautifulSoup
from socketIo import Socket

from http import Http
from robot import Robot
from tool import ThreadRun
from python_sqlite import Database



# cochat 自动化
class AutoCochat:
    def __init__(self, name="Test", id="18408249138", pwd="1234qwer"):
        reload(sys)
        sys.setdefaultencoding('utf8') #针对socket发送中文异常
        self.detaTime = 1.5 * 3600 * 1000 #推送延时 60min
        self.detaTimeMin = 1200 * 1000 #推送延时 20min

        self.id = id
        self.pwd = pwd
        self.name = name
        self.robot = Robot()
        self.http = Http()
        self.db = Database('sqlite_' + self.id + '.db')
        self.socket = Socket()
        self.onConnect = False
        self.ifOk = False
        # sendTime添加时间, type消息类型, msg发送消息体, deta间隔发送时间, preTime预期发送时间节点
        self.db.execute(
            ''' 
            create table if not exists cochat(
                id  text,
                sendTime    text,
                sendTimeT text,
                deta    text,
                preTime text,
                preTimeT text,
                type        text,
                msg    text,
                flag    text
            )
            ''' )
        self.sendList = [] #发送队列 (time, deta, return, type)
    # 日志输出
    def out(self, obj):
        print(time.strftime("%Y%m%d %H:%M:%S", time.localtime()) + "." + self.name + "." + str(obj))
        return
    # 实时控制帮助
    def help(self):
        self.out(dir(self))
        return
    # doMethod([methodName arg1 arg2]) -> methodName(arg1,arg2)
    def doMethod(self, listArgs):
        size = len(listArgs)
        res = None
        if(size > 0):
            if(hasattr(self, listArgs[0])):
                method = getattr(self, listArgs[0])
                if(callable(method)):
                    if(size == 2):
                        res = method(listArgs[1])
                    elif(size == 3):
                        res = method(listArgs[1], listArgs[2])
                    elif(size == 4):
                        res = method(listArgs[1], listArgs[2], listArgs[3])
                    elif(size == 5):
                        res = method(listArgs[1], listArgs[2], listArgs[3], listArgs[4])
                    else:
                        res = method()
                else:
                    self.out(method)
        return res
    # 手动命令监控
    def inputHello(self):
        self.out("开启输入监控！")
        self.help()
        while(True):
            try:
                cmd=raw_input("")
                if(cmd != ""):
                    if(not self.doMethod(cmd.split(" "))):
                        # self.out("exm???")
                        # self.out(cmd)
                        pass
                    time.sleep(1)
            except Exception as e:
                self.out(traceback.format_exc())
        return
    def send(self, ttt, data, deta=-1):
        if(deta == -1):
            deta = tools.getRandom(self.detaTime, self.detaTimeMin)
        sendTime = tool.getNowTime()
        preTime = sendTime + deta
        sendTimeT = tool.parseTime(sendTime/1000, "%D %H:%M:%S")
        preTimeT = tool.parseTime(preTime/1000, "%D %H:%M:%S")

        # self.sendList1.append((sendTime, deta, preTime, type, data))
        # sendTime添加时间, type消息类型, msg发送消息体, deta间隔发送时间, preTime预期发送时间节点
        self.db.execute("insert into cochat values(?,?,?,?,?,?,?,?,?)", str(self.id), str(sendTime),str(sendTimeT), str(deta), str(preTime),str(preTimeT), str(ttt), str(data),'0')

        return
    # 定时任务
    def timeSend(self):
        self.out("开启定时任务 发送队列！")
        self.nowNight = 0
        while(True):
            time.sleep(5) #每分钟扫描 只对非凌晨时间处理 延时一小时发送
            timeNow = tool.getNowTime()
            hour = tool.parseTime(timeNow/1000, "%H:%M")
            if(hour >= "23:30" or hour <= "07:40" or self.ifOk == False):
                if(self.nowNight != 1):
                    self.out("不是白天 或者 没有登录 now:" + str(hour) )
                self.nowNight = 1
                continue
            self.nowNight = 0
            try:
                # self.sendList1.append((sendTime, deta, preTime, type, data))
                self.sendList = self.db.executeQuery("select * from cochat where preTime<=? and flag=0 and id=?", timeNow, str(self.id) )
                i = len(self.sendList) - 1
                while(i >= 0):
                    obj = self.sendList[i]
                    sendTime = int(obj.get("sendTime", 0))
#                    deta = int(obj.get("deta", 0))
                    preTime = int(obj.get("preTime", 0))
                    type = str(obj.get("type", ""))
                    data = ast.literal_eval((str(obj.get("msg", ""))))
                    info = ""
                    hour = tool.parseTime(preTime/1000, "%D %H:%M:%S")
                    info = str(timeNow) + "->" + str(preTime) + " 推送时刻:" + str(hour)
                    if(timeNow >= preTime):
                        info += " 触发"
                        self.sendTrue(type, data)
                        # self.sendList.pop(i)
                    else:
                        info += " "
                    self.out(tool.parseTime(timeNow/1000, "%D %H:%M:%S") + "." + str(type) + "." + str(data) + "." + info)
                    i = i - 1
                self.db.execute("update cochat set flag='1' where preTime<=? and flag=0 and id=? ", timeNow, str(self.id))
            except Exception as e:
                self.out(traceback.format_exc())
        return

    # 定时任务
    def timeHello(self):
        self.out("开启定时任务！")
        self.help()
        while(True):
            time.sleep(3600 * 3)
            try:
                self.out("定时重新连接")
                self.login()
            except Exception as e:
                self.out(repr(e))
        return
    # 测试用
    def test(self):
        self.login()
        ThreadRun( "TimeHello." + str(self.name),  self.timeHello ).start()
        # ThreadRun( "TimeCtrl." + str(self.name),  self.inputHello ).start()
        ThreadRun( "TimeSend." + str(self.name),  self.timeSend ).start()
        self.socket.waitRead(self.onException)    #异常回调
        tool.wait()
        return
    # 监控执行
    def doCmd(self, cmd):
        self.send({"data":cmd})
        return
    def login(self):
        i = 0
        while(self.ifOk == False or i <= 0):
            try:
                self.whileLogin()
                i = i + 1
            except Exception as e:
                self.out(traceback.format_exc())
                self.out("登录异常,5s后重试 try:" + str(i))
            time.sleep(5)
        return

    # 认证登录
    def whileLogin(self):
        self.ifOk = False
        if(self.onConnect):
            self.out("已经在尝试登录")
            return
        self.socket.close()
        self.onConnect = True
        self.out("尝试登录:")
# {CONF_V   ARS: "*", ORG_VARS: true, logintype: "mobile", id: "18408249138", password: "1234qwer"}
# Request URL:http://picc.cochat.cn/SY_ORG_LOGIN.login.do?DESKTOP_OS=Win10&USER_LAST_BROWSER=Win32&USER_LAST_CLIENT=2.5.1&USER_LAST_OS=DESKTOP&USER_LAST_PCNAME=%7B%7D
# request Cookie:JSESSIONID=abcb0skaQYCGs6lvy9orw
        obj = self.http.doJson("http://picc.cochat.cn/SY_ORG_LOGIN.login.do?DESKTOP_OS=Win10&USER_LAST_BROWSER=Win32&USER_LAST_CLIENT=2.5.1&USER_LAST_OS=DESKTOP&USER_LAST_PCNAME=%7B%7D",{
            "CONF_VARS":"*",
            "ORG_VARS":"true",
            "logintype":"mobile",
            "id":self.id,
            "password":self.pwd
        })
        if(obj.get("error","") != ""):
            self.onConnect = False
            return
        self.loginUser = obj
        token = obj.get("USER_TOKEN", "")
        self.out("登录结果 token:" + token)
        urlWithPort = obj.get("CONF_VARS", {}).get("@C_SY_COMM_SOCKET_SERV_V1.0@", "http://cochat.cn:9091")
        uus = urlWithPort.split(':')
        port = int(uus[2])
        url = uus[1][2:999] #cochat.cn 不需要ws http 只需要ip 域名

        self.socketServerUrl = urlWithPort
        self.socketUrl = url
        self.socketPort = port
        self.showUser()

        self.config = {
            "transports":['websocket', 'polling'],  # websocket优先
            "timeout":5 * 1000, # 超时时间
            "forceNew": True,
            "reconnection" : False
        };
        self.out("socket开始")
        self.socket.connect(url,port) # , params=self.config)
        self.out("socket连接完成，开始初始化事件")

        socketMsgTypes = ("connect", "disconnect","error","connect_error","connect_timeout","connecting","reconnecting","message", "event")
        # socketMsgTypes = ("connect", "disconnect","message", "event")
        for item in socketMsgTypes:
            if(hasattr(self, item)):
                method = getattr(self, item)
                if(callable(method)):
                    self.socket.on(item, method)
                else:
                    self.out("变量而非方法" + item + "回调?")
            else:
                self.out("属性" + item + "不存在，是否写错了名字?")
        # self.socket.on("message", self.message)

        self.out("socket初始化事件完成，开始发送认证")
        self.data = {
            "userName":obj.get("USER_CODE", ""),
            "displayName": tool.encode(obj.get("ORG_VARS", {}).get("@USER_NAME@", "") ), #"ccc",#
            "odept":obj.get("ORG_VARS", {}).get("@ODEPT_CODE@", ""),
            "token":obj.get("USER_TOKEN", ""),
            "uuid":"" + str(uuid.uuid1()),
            "version":obj.get("USER_CODE", "") + "_LAST_MSG"
        }
        self.out(self.data)
        self.socket.emit('loginv17', self.data, self.onSocketLogin)
        self.out("已发送认证信息")
        self.ifOk = True
        self.onConnect = False
        return
    def connect(self, *args):
        print("connect")
        print(args)
        # self.login()
        return
    def disconnect(self, *args):
        print("disconnect")
        print(args)
        self.login()
        return
    def error(self, *args):
        print("error")
        print(args)
        self.login()
        return
    def connect_error(self, *args):
        print("connect_error")
        print(args)
        return
    def connect_timeout(self, *args):
        print("connect_timeout")
        print(args)
        return
    def connecting(self, *args):
        print("connecting")
        print(args)
        return
    def reconnect(self, *args):
        print("reconnect")
        print(args)
        return
    def reconnecting(self, *args):
        print("reconnecting")
        print(args)
        return
    def onException(self, *args):
        tool.line()
        self.out("onexception")
        print(args)
    def turnArray(self, args):
        if(len(args) == 1):
            args = args[0]
            reg = re.match(r'^\d+', args)         #25[xxxx] -> [xxxxx]
            if(reg is not None):
                start = reg.group()
                args = args[len(start):999999]
            # reg = re.match(r'^\["\w+",', args)         #["message",  {"to":{"id":" ->  {"to":xxxx
            # if(reg is not None):
            #     start = reg.group()
            #     args = args[len(start):999999]
            #     mtype = start[2:-2]
            res = tool.toJson(args)
        else:
            res = list(args)
            if(len(res) <= 1):
                res = ( 'null', res[0])
            elif(callable(res[1])):
                res = ( 'fun', res[0])

        return res
    def message(self, *args): # 普通消息
        try:
            # print("收到message ")
            # print(args)
            # tool.line()
            # print("转换")
            args = self.turnArray(args)
            # print(args[0])
            # print(args[1])
            if(len(args) <= 1):
                return

            data = args[1] #{}
            mtype = args[0] #message null fun
            if(mtype == 'message'):
                data = tool.toJson(data)
                fro = data.get("from", {})
                to = data.get("to", {})
                contact = data.get("contact", {})
                msg = data.get("body")
                fullId = contact.get("fullId")
                sessionName = contact.get("nickName", "")

                uid = self.data.get("uuid")
                tTag = data.get("timeMillis", tool.getNowTime())
                tool.line()
                self.out("Msg:" + fro.get("nickName","from") + ">>" + msg + ">>" + to.get("nickName","to") + " time:" + data.get("time"))
                # self.out(msg);

                # 自发消息不需要处理
                if(fro.get("nickName","from").find(self.loginUser.get("ORG_VARS", {}).get("@USER_NAME@", "")) >= 0):
                    return

                ttt = self.detaTime
                reg = re.match(r'^\d+$', str(msg))
                if(reg is not None):
                    ttt = int(msg) * 1000

                ttt = int(ttt)
                
                self.send("updateConversationStatus", {
                    'contactFullId': fullId,
                    'clientId': uid,
                    'timeTag': tTag
                }, ttt)
                self.send("updateMsgStatus", {
                    "messages":data.get("id","")
                }, ttt)


                # 自发言 且 只有自己auto回复
                if(self.id != "18408249138"):
                    return
                # 过滤 
                ff = sessionName.find("陈鹏辉")
                hh = fro.get("nickName","from").find("许欢")
                zz = fro.get("nickName","from").find("赵振国")
                cdf = fro.get("nickName","from").find("迪")
                d1 = sessionName.find("迪")
                d2 = sessionName.find("祝")
                d3 = sessionName.find("纯")
                if(ff < 0 or d1 >= 0 or d2 >= 0 or d3 >= 0):
                    self.out("未命中自己title 命中特殊 不回复")
                    return
                point = 76
                if(hh >= 0 or zz >= 0):
                    point = 33
                    self.sendTrue("updateMsgStatus", {
                        "messages":data.get("id","")
                    })
                if(tool.getRandom(0,100) < point):
                    self.out("概率不自动回复" + str(point))
                    return

                # data["body"] = str(data["body"]) + "."
                # self.send("message", data)

                obj = {}
                # if(contact.get("type") == "GROUP"):
                # unicode(self.robot.do(msg, fro.get("nickName")))
                msg = self.robot.do(msg, fro.get("nickName"))
                msg = msg.get("text", '');
                if(msg == ''):
                    return
                obj["body"] = msg #"666" + str(tool.getNowTime())
                obj["bodyType"] = "text"
                obj["clientId"] = str(uuid.uuid1())
                obj["retry"] = 1
                obj["from"] = {}
                obj["from"]["fullId"] = "u__" + self.data.get("userName")
                obj["from"]["id"] = self.data.get("userName")
                obj["from"]["nickName"] = "fromnickname"
                obj["to"] = {}

                if(contact.get("type") == "GROUP"):
                    obj["to"]["fullId"] = contact.get("fullId")
                else:
                    obj["to"]["fullId"] = fro.get("fullId")
                obj["to"]["nickName"] = "tonickname"

                obj["from"]["nickName"] = self.loginUser["ORG_VARS"]["@USER_NAME@"]   # "from-nickName"
                obj["to"]["nickName"] = "to-nickName"

#                self.sendTrue("message", obj)
            elif(str(mtype) == 'fun'):
                pass
            elif(str(mtype) == 'event'):
                pass
            else:
                self.out("其他:" + str(mtype))
                print(data)
                # print(args)
                # tool.line()
        except Exception as e:
            self.out(traceback.format_exc())

        return

    def event(self, *args): # 事件消息 群创建？
        print("event")
        print(args)
        return
    def onSocketLogin(self, *data):
        self.out("socket登录回调:")
        print(data)
        return


    def sendTrue(self, type, data):
        self.socket.send(type, data)
        return


    def showUser(self):
        tool.line()
        obj = self.loginUser
        user = obj.get("ORG_VARS", {})
        self.out(user.get("@USER_NAME@", ""))
        self.out(user.get("@USER_POST@", ""))
        self.out(user.get("@LOGIN_NAME@", ""))
        self.out("USER_CODE:" + obj.get("USER_CODE", ""))
        self.out("USER_TOKEN:" + user.get("UESR_TOKEN", ""))
        self.out("socketServerUrl:" + self.socketServerUrl)
        self.out("to url:" + self.socketUrl)
        self.out("to port:" + str(self.socketPort))

        tool.line()
        return
if __name__ == '__main__':
    obj = AutoCochat("Test")
    # obj = AutoCochat("Test", "18262600672", "654321")
    # obj = AutoCochat("Test")
    obj.test()

    # obj.login()
    #
    # socket = SocketIO(obj.socketUrl,port=obj.socketPort) # , params=self.config)
    # socket.on('message', obj.message)
    # socket.on('event', obj.event)
    #
    # socket.emit('loginv17', obj.data, obj.onSocketLogin)
    #
    # data = {
    #     "v1": "aaaaaaaaaaa",
    #     "v2": "bbbbbbbbb"}
    # socket.emit('message', data)
    # socket.emit('event', data)
    # print("over")
    # # sk.wait_for_callbacks(seconds=1)
    # socket.wait()
    # tool.wait()
