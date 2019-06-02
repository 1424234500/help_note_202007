#!/usr/bin/python
#-*- coding:utf-8 -*-  
 
import json
import time
import BeautifulSoup
import tool
from http import Http
from tool import ThreadRun
import re

# 百度接口  语音合成
class AutoBaidu:
    def __init__(self, name="0000000"):
        self.http = Http()
        self.name = name
        # https://console.bce.baidu.com/ai/?_=1533038198056&fromai=1#/ai/speech/app/detail~appId=464300
        self.appId = "11615410"
        self.appKey = "zzTM1VXx7Edmj4QXqCcnhZfF"
        self.appSecret = "jekAAbrElm87rpMM7jVBFFuKrm8ZWbwy"
        self.loginRes = {}
        self.access_token = ""
    def out(self, obj):
        print(self.__module__ + "." + self.name + "." + str(obj))
    def login(self):
        tool.line()
        self.out("百度接口token获取")
        res = False
        obj = self.http.doJson("https://openapi.baidu.com/oauth/2.0/token?grant_type=client_credentials&client_id="+self.appKey+"&client_secret="+self.appSecret)
        token = obj.get("access_token", "")
        # scope中含有audio_tts_post 表示有语音合成能力，
        # 没有该audio_tts_post 的token调用接口会返回502错误。
        # 在结果中可以看见 token = 1.a6b7dbd428f731035f771b8d********.86400
        # .1292922000-2346678-124328，在2592000秒（30天）后过期。
        if(token != ""):
            self.access_token = token
            self.loginRes = obj
            res = True
        else:
            self.out("接口认证失败")
            self.out(str(obj))
            res = False
        return res

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

    def getAudio(self, text=""):
        flag = False
        res = ""
        if(text == ""):
            return flag,res
        url = "http://tsn.baidu.com/text2audio?lan=zh&ctp=1&cuid="+self.name+"&tok="+ self.access_token + "&tex=" + self.http.encode(text) + "&vol=13&per=0&spd=5&pit=5&aue=3"
        responce = self.http.do(url )
# tex	必填	合成的文本，使用UTF-8编码。小于2048个中文字或者英文数字。（文本在百度服务器内转换为GBK后，长度必须小于4096字节）
# tok	必填	开放平台获取到的开发者access_token（见上面的“鉴权认证机制”段落）
# cuid	必填	用户唯一标识，用来计算UV值。建议填写能区分用户的机器 MAC 地址或 IMEI 码，长度为60字符以内
# ctp	必填	客户端类型选择，web端填写固定值1
# lan	必填	固定值zh。语言选择,目前只有中英文混合模式，填写固定值zh
# spd	选填	语速，取值0-15，默认为5中语速
# pit	选填	音调，取值0-15，默认为5中语调
# vol	选填	音量，取值0-15，默认为5中音量
# per	选填	发音人选择, 0为普通女声，1为普通男生，3为情感合成-度逍遥，4为情感合成-度丫丫，默认为普通女声
# aue	选填	3为mp3格式(默认)； 4为pcm-16k；5为pcm-8k；6为wav（内容同pcm-16k）; 注意aue=4或者6是语音识别要求的格式，但是音频内容不是语音识别要求的自然人发音，所以识别效果会受影响。

        if(type(responce) == str):
            res = "转换接口访问失败" + str(text)
        else:
            header = responce.headers
            # Content-Type: audio/mp3；
            # Content-Type: application/json
            ct = header.get("Content-Type", "")
            if(ct == "application/json"):
                obj = tool.toJson(responce.read())
                # {"err_no":500,"err_msg":"notsupport.","sn":"abcdefgh","idx":1}
                code = obj.get("err_no", "")
                if(str(code)[0:1] == "5"):
                    if(code == 500):
                        info = "不支持输入"
                    elif(code == 501):
                        info = "输入参数不正确"
                    elif(code == 502):
                        info = "token验证失败"
                    elif(code == 503):
                        info = "合成后端错误"
                    else:
                        info = "其他错误" + str(code)
                    info = info + " " + obj.get("err_msg", "")
                else:
                    info = str(obj)
                flag = False
                res = info
            else:
                flag = True
                res = url
                self.out("转换文本[" + text + "] -> " + res)
        return flag,res
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
                        self.getAudio(cmd)
                        time.sleep(1)
            except Exception as e:
                self.out(repr(e))
        return
    def test(self):
        self.login()
        ThreadRun( "InputHello." + str(self.name),  self.inputHello ).start()
        flag,res= self.getAudio("百度你好")
        print(flag)
        print(res)
        tool.wait()
        return
if __name__ == '__main__':
    obj = AutoBaidu("Test")
    obj.test()