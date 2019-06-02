#!/usr/bin/python
#-*- coding:utf-8 -*-  
 
import json
import time
import BeautifulSoup
import tool
from http import Http
from tool import ThreadRun
import re

# 163网易云歌曲抓取 搜索 转链 信息采集
class Auto163:
    def __init__(self, name="0000000"):
        self.http = Http()
        self.name = name

    def out(self, obj):
        print(self.__module__ + "." + self.name + "." + obj)
    def login(self):
        pass 
    def help(self):
        self.out(dir(self))
# [methodName arg1 arg2]
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
    def getMusic(self, musicName="", fromName=""):
        tool.line()
        res = []
        self.out("歌曲名字[" + musicName + "] from:" + fromName)
        responce = self.http.do("http://music.163.com/api/search/get/web?csrf_token=", {
           "hlpretag":"",
           "hlposttag":"",
           "s":musicName,
           "type":1,
           "offset":0,
           "total":"true",
           "limit":5,
        })
        obj = tool.toJson(responce.read())
        songs = obj.get("result", {}).get("songs", [])
        self.out("抓取到音乐：")
        for item in songs:
            id = item.get("id", "")
            name = item.get("name", "")
            url = "http://link.hhtjim.com/163/" + str(id) + ".mp3"
            duration = item.get("duration", 0)
            music = {"url":url, "name":name, "fromName":fromName, "duration":duration}
            self.out("url:" + url + " name:" + name)
            res.append(music)

        return res
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
                        self.getMusic(cmd)
                        time.sleep(1)
            except Exception as e:
                self.out(repr(e))
        return
    def test(self):
        self.login()
        ThreadRun( "InputHello." + str(self.name),  self.inputHello ).start()

        tool.wait()
        return
if __name__ == '__main__':
    obj = Auto163("Test")
    obj.test()