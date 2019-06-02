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
#        http://content.icbc.com.cn/site1/a5f9ff6d068a46e68d363426ca69bd07/login_unfirst.html?pageOrder=login_unfirst.html;index.html&_mp_cmp_ttime=1548294412328
# "http://content.icbc.com.cn/site1/a5f9ff6d068a46e68d363426ca69bd07/login_unfirst.html?pageOrder=login_unfirst.html;index.html&_mp_cmp_ttime=1545268253550"
#http://content.icbc.com.cn/site1/a5f9ff6d068a46e68d363426ca69bd07/login_unfirst.html?pageOrder=login_unfirst.html;index.html&_mp_cmp_ttime=1552005766720
        ttt = str(tool.getNowTime())
        kkk = 'a5f9ff6d068a46e68d363426ca69bd07'
        url = "http://content.icbc.com.cn/site1/" + kkk + "/login_unfirst.html?pageOrder=login_unfirst.html;index.html&_mp_cmp_ttime=" + ttt
        
        
#BIGipServerwifi_ContextPlat_80_Pool	2097346570.20480.0000	N/A	N/A	N/A	59				
#cmp_glb_param	98f7808c851a9f53da5f0c3f1639b678	N/A	N/A	N/A	46				
#layerNettimeType	true	N/A	N/A	N/A	23				
#layerPosterType	true	N/A	N/A	N/A	22				
#layerSafeType	true	N/A	N/A	N/A	20

#Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8
#Accept-Encoding: gzip, deflate
#Accept-Language: en-US,en;q=0.9,zh-CN;q=0.8,zh;q=0.7
#Connection: keep-alive

        header = {
            "Cookie"    : "BIGipServerwifi_ContextPlat_80_Pool=2097346570.20480.0000; layerSafeType=true; layerPosterType=true; layerNettimeType=true; cmp_glb_param=98f7808c851a9f53da5f0c3f1639b678"
            
        }
        self.http.addHeader(header)
        
        self.http.show()
        responce = self.http.doGet(url)
        re = responce.read()
        soup =BeautifulSoup.BeautifulSoup(re)
        nameList = soup.findAll('button',{'id':{'login_btn'}})
        if(len(nameList) > 0):
            self.out(nameList)
            self.out("抓取成功: ")
            self.http.show(responce)
            self.out("模拟登录")
# http://content.icbc.com.cn/cmp/AuthSkipController.do?method=authSkip&ajaxRequest=true
            url = "http://content.icbc.com.cn/cmp/AuthSkipController.do?method=authSkip&ajaxRequest=true"
#{"msg":"GlbInfo检查不通过","retCode":1,"success":false,"data":{"needJump":"http%3A%2F%2Fwww.baidu.com%2F"}}

            json=self.http.doJson(url)
            self.out((json))
            self.out(json["msg"])
            self.out(json["data"]["needJump"])
        else:
            self.out("error！ 没能抓取到token")
        return False








if __name__ == '__main__':
    obj = Auto("Test")
    obj.test()
