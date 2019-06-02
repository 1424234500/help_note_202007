#!/usr/bin/python
#-*- coding:utf-8 -*-  
import tool
from http import Http
import time
import json
from python_sqlite import Database
from auto163 import Auto163
import traceback

# @singlton
class Robot:
    """机器人智能语义应答""" 

    id = ""
    name = ""

    def __init__(self):
        self.id = "test id"
        self.name = "test name"
        self.http = Http()
        self.auto163 = Auto163("Music")
        self.apiKey = "bfbf6432b655493b9e861b470bca9921"
        self.userId = "WalkerDust"
        
        self.db = Database()
        self.db.execute(
        ''' 
        create table if not exists music(
            url         text primary key,
            name        text,
            duration    text,
            fromName    text,
            count       text
        )
        ''' )
        self.db.execute(
            ''' 
            create table if not exists user(
                name        text primary key,
                id          text,
                icon        text,
                flag        text
            )
            ''' )
        self.db.execute(
            ''' 
            create table if not exists msg(
                id            text primary key, 
                userName      text,
                data          text,
                time          text
            )
            ''' )
        self.initMusic()
        self.palyHistoryMusic = []
        return
    def out(self, obj):
        print(self.__module__ + "." + str(obj))
        return
# 音乐模块
    def initMusic(self):
        li = ""
        count = self.db.getCount("select * from music ")
        if(count <= 0): #毫无数据 则 加入默认数据
            li = []
            with open('music.txt', 'r') as f:  
                data = f.readlines()  
                for item in data:
                    name = item.strip()
                    url = "http://39.107.26.100:8088/file/" + name
                    fromName = ""
                    self.db.execute('insert into music values(?,?,?,?,?)', url, name,"0", fromName,"5")
        return    
    def nextMusic(self, name = ""):
        self.nextNames.append(name)
    # 内部点播 若有名字则按照名字本地搜索和云搜索 否则 按照type切歌
    def turnMusic(self, playType):
        music = {}
        if(playType == -1 and len(self.palyHistoryMusic) > 1): #上一曲
            music = self.palyHistoryMusic.pop() #弹出顶 取末
            music = self.palyHistoryMusic[-1]
        else:
            cc = 0
            while(music.get("url","") == ""):
                size = self.db.getCount("select * from music ")
                if(size <= 0):
                    break
                num = 5
                page = int(1.0 * size / num)
                page = tool.getRandom(0, page)
                (size, listRes) = self.db.executeQueryPage("select * from music", page, num)

                getSize = len(listRes)
                count = tool.getRandom(0, getSize)
                music = listRes[count]
                tool.line()
                self.out("随机找到歌曲页 " + "size:" + str(size) + "  page:" + str(page) + " num:" + str(num) + " listResSize:" + str(getSize) )
                for item in listRes:
                    self.out("url:" + item.get("url") + " name:" + item.get("name") +" fromName:" + item.get("fromName") + " time:" + str(tool.calcTime(item.get("duration", 0))))
                self.out("选中了" + str(count))
                tool.line()
                url = music.get("url", "")
                if(self.http.existAudio(url)):
                    break
                else:
                    self.out("访问音乐文件失败" + url)
                    self.removeMusic(url)
                    music = {}
                if(cc > 20):
                    break
                cc = cc + 1
        return music
    def getMusic(self, musicName="", fromName=""):
        music = {}

        if(musicName != ""):
            # res = self.db.executeQueryOne("select * from music where name=? ", musicName)
            # if(res.get("url", "") != ""):
            #     music = res
            # else:
            res=self.auto163.getMusic(musicName, fromName) # [music,music]
            rres = []
            for item in res:
                if(self.addMusic(item)): #有效歌曲才参与接下来的选择
                    rres.append(item)
            res = rres
            if(len(res) > 0):
                #按照 前面权重依次递减 1 2 3 4 5 -> 16 8 4 2 1
                ii = tool.getRandomWeight(0, len(res))
                self.out("0, " + str(len(res)) + " -> " + str(ii) )
                music = res[ii]
        if(music.get("url", "") != ""):
            self.addHistory(music)

        return music
    def addHistory(self, music):
        self.palyHistoryMusic.append(music)
        if(len(self.palyHistoryMusic) > 20):
            self.palyHistoryMusic.pop(0)
    # 外部点播音乐记录
    def addMusic(self, music):
        url = music.get("url", "")
        name = music.get("name", "")
        fromName = music.get("fromName", "")
        duration = music.get("duration", 0)
        oldMusic = self.db.executeQueryOne("select * from music where url = ? ", url)
        if(oldMusic.get("url", "") == ""):
            # self.out("添加音乐")
            # self.out(music)
            self.db.execute('insert into music values(?,?,?,?,?)', url, name, duration, fromName, "1")
        else: #更新该音乐数据
            # self.out("更新音乐")
            count = int(oldMusic.get("count", 0))
            count = str(count + 1)
            music["count"] = count
            # self.out(music)
            self.db.execute('update music set name=?, fromName=?, count=?,duration=? where url=?', name, fromName, count, duration, url)
        if(not self.http.existAudio(url)):
            self.out("访问音乐文件失败" + url)
            self.removeMusic(url)
            return False

        return True
    def removeMusic(self, url=""):
        index = 0
        self.out("移除音乐" + url)
        self.db.execute('delete from music where url = ? ', url)
        return 
# 人员信息管理 权限 状态
#     name        text primary key,
#     id        text,
#     icon    text,
#     flag    text
    def addUser(self, user={}):
        name = user.get("name", "")
        id = user.get("id", "")
        icon = user.get("icon", "")
        flag = user.get("flag", "0")
        if(self.db.getCount("select * from user where name=?", name) > 0):
            self.db.execute("update user set id=?,icon=?,flag=? where name=?", id, icon, flag, name)
        else:
            self.db.execute("insert into user(name,id,icon,flag) values(?,?,?,?)",name,id,icon,flag)
    def turnUser(self, name, flag):
        if(self.db.getCount("select * from user where name=?", name) > 0):
            self.db.execute("update user set flag=? where name=?", flag, name)
        else:
            self.db.execute("insert into user(name,flag) values(?,?)",name,flag)
    def getUser(self, name=""):
        res = self.db.executeQueryOne("select * from user where name=?", name)
        if(res == None):
            res = {}
        return res


# 消息监控
    def addMsg(self, id, userName, data, msgTime):
        if(self.db.getCount("select * from msg where id=?", id) <= 0):
            self.db.execute('insert into msg values(?,?,?,?)', id, userName, data, msgTime)
        return
# 智能应答 
    def do(self, msg, userId="CC"):
        res = ""
        if(msg == ""):
            return "消息不能为空"
        response = self.http.doPost('http://www.tuling123.com/openapi/api', {
                "key":self.apiKey,
                "info":msg,
                "userid":userId,
                # "userInfo":{
                #     "apiKey":self.apiKey,
                #     "userId":self.userId,
                # },
                # "reqType":0,
                # "perception":{
                #     "inputText":{
                #         "text":msg,
                #     }
                # },
            }
        )
        jsonStr = response.read()

        if(jsonStr != ""):
            res = tool.makeObj(json.loads(jsonStr))
            code = res.get("code", "")
            self.out("Robot. " + str(msg) + " -> " + jsonStr)
        else:
            self.out("Robot. " + str(msg) + " -> error !!!!!!!!! ")
        return res
    def doParse(self, obj):
        res = ""
        text = obj.get("text", "")
        res = res + text
        url = obj.get("url", "")
        list = obj.get("list", "")
        if(url != ""):
            res = res + " \n" + url
        i = 0
        if(list != "" and len(list) > 0):
            for item in list:
                # res = res + " \n"
                # for key,value in item.items():
                #     res = res + " \n" + str(value)
                ttt = item.get("url", "")
                if(ttt != ""):
                    res = res + " \n" + str(ttt)

                ttt = item.get("detailurl", "")
                if(ttt != ""):
                    res = res + " \n" + str(ttt)

                if(len(res) > 200):
                    break
            # {
            #     "name": "鱼香肉丝",
            #     "icon": "",
            #     "info": "瘦肉、黑木耳、胡萝卜、靑椒、豆瓣酱，葱姜蒜、白糖，香醋，料酒",
            #     "detailurl": "http://m.xiachufang.com/recipe/100352761/?ref=tuling"
            # }
        return res

    def test(self):
        while(True):
            cmd=raw_input("")
            if(cmd != ""):
                res = self.do(cmd)
                self.out(res)
                time.sleep(1)

        return





if __name__ == '__main__':
    r = Robot()
    r.test()
