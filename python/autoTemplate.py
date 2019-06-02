#!/usr/bin/python
#-*- coding:utf-8 -*-

import re
import sys
import time
import json
import traceback

import tool
import BeautifulSoup
from http import Http
from tool import ThreadRun
from python_sqlite import Database

# icbc 自动化 定时登录刷新session
class Auto:
    def __init__(self, name="Test"):
        self.name = name

        self.http = Http()
        self.db = Database()
        self.db.execute(
            ''' 
            create table if not exists auto(
                url         text,
                about        text,
                time        text,
                v1       text,
                v2       text,
                v3       text,
                v4       text,
                v5       text
            )
            ''' )

        return
    # 日志输出
    def out(self, obj):
        print(time.strftime("%Y%m%d %H:%M:%S", time.localtime()) + "." + self.__module__ + self.name + "." + str(obj))
        # tools.out(obj)
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
                        self.doCmd(cmd)
                        time.sleep(1)
            except Exception as e:
                self.out(repr(e))
        return
    # 测试用
    def test(self):
        self.login()
        # 输入监控线程
        ThreadRun( "InputHello." + str(self.name),  self.inputHello ).start()

        tool.wait()
        return
    # 非函数调用 属性变量查看 其他的指令控制
    def doCmd(self, cmd):
        self.out("其他指令." + str(cmd))
        
        return

    # 认证登录
    def login(self):
        self.out("访问主页 获取 token session")
        responce = self.http.doGet('http://drrr.com/')
        re = responce.read()
        soup =BeautifulSoup.BeautifulSoup(re)
        nameList = soup.findAll('input',{'name':{'token'}})
        if(len(nameList) > 0):
            token = nameList[0]['data-value']
            token = tool.encode(token)
            self.out("抓取成功: ")
            self.out("token\t " + token)
            self.out("cookie\t " + tool.toString(self.http.getCookie()))
            self.out("模拟登录")
            responce=self.http.doPost('http://drrr.com/', {
                        "name":name,
                        "login":"ENTER",
                        "token":token,
                        "direct-join":"",
                        "language":"zh-CN",
                        "icon":icon,
                })
            if(responce != "error"):
                return True
            else:
                return False
        else:
            self.out("error！ 没能抓取到token")
        return False








if __name__ == '__main__':
    obj = Auto("Test")
    obj.test()