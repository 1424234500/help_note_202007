#!/usr/bin/python
#-*- coding:utf-8 -*-  
import urllib
import re
import urllib2
import cookielib
import tool
import traceback

class Http:
    def __init__(self):
        self.cookie = cookielib.CookieJar()
        self.cookieHander = urllib2.HTTPCookieProcessor(self.cookie)
        self.opener = urllib2.build_opener(self.cookieHander)

        header = {
            "User-Agent":"Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36",
            
        }
        turnHeader = []
        for item in header.keys():
            turnHeader.append( (item, header[item]) )
            
        self.opener.addheaders = turnHeader
        # urllib2.install_opener(opener)  
        return
    def makeOpener(self, cookies, headers):
        
        return
    def addHeader(self, header={}):
        turnHeader = self.opener.addheaders
        for item in header.keys():
            turnHeader.append( (item, header[item]) )
        self.opener.addheaders = turnHeader
        
    def out(self, *obj):
        print("http." + str(obj))

    def getCookie(self):
        res = {}
        for item in self.cookie:
            res[item.name] = item.value
        return res

    def show(self, response=""):
        if (response != ""):
            tool.line()
            self.out("Code: " + str(response.getcode()))
            self.out("Res : " + str(response.msg))
            self.out("Headers : ")
            print(response.headers)
        
    
        tool.line()
        try:
            for item in self.cookie:
                self.out("Cookie: ", item.name, item.value)

            self.out("Headers Add : ")
            header = self.opener.addheaders
            for key, value in header:
                self.out("Headers Add ", key, value)
        except Exception as e:
            print(traceback.format_exc())
        tool.line()
        return


    # 网络文件信息头获取
    def getHeader(self, url):
    # meta = req.info()
    # file_size = int(meta.getheaders("Content-Length")[0])
    # content_type = meta.getheaders('Content-Type')[0].split(';')[0]
    # print file_size, content_type
# Date: Tue, 15 May 2018 13:23:07 GMT
# Server: openresty/1.11.2.5
# Content-Type: audio/mpeg
# Content-Length: 2949164
# x-nos-request-id: 1698868f-ee9b-4b01-bbae-f127b961dcea
# x-nos-owner-productid: 177408e1ca784c08b4cb35ef81d304ee
# ETag: 2c10ad1f64bdfc097785b0ca1b32fdbd
# Content-Disposition: inline; filename="97c4%2Fac9d%2Fd676%2F2c10ad1f64bdfc097785b0ca1b32fdbd.mp3"
# Last-Modified: Thu, 02 Nov 2017 12:16:57 Asia/Shanghai
# Age: 6187682
# X-Via: 1.1 ingdianxin173:9 (Cdn Cache Server V2.0)[22 200 0], 1.1 PSfjfzdx2go80:2 (Cdn Cache Server V2.0)[0 200 0], 1.1 PSshqzdx4dp241:3 (Cdn Cache Server V2.0)[0 200 0]
# X-Ws-Request-Id: 5b5949dd_PSshqzdx4ny239_22865-38924
# Connection: close
# cdn-user-ip: 101.225.89.253
# cdn-ip: 101.227.97.241
# cdn-source: chinanetcenter
# Access-Control-Allow-Credentials: true
# Access-Control-Allow-Headers: DNT,X-CustomHeader,Keep-Alive,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,Content-Type
# Access-Control-Allow-Methods: GET,POST,OPTIONS
# Access-Control-Allow-Origin: *

        res = {}
        try:
            response = self.opener.open(url)
            header = response.headers
            res = header
            # self.show(response)
        except Exception as e:
            tool.line()
            self.out(str(url))
            print(traceback.format_exc())
        return res
    def existAudio(self, url, mimeType="audio"):
        return True
        # try:
        #     response = self.opener.open(url)
        #     code = str(response.getcode())
        #     head = response.headers
        #     ttype = head.get("Content-Type", "")
        #     size = int(head.get("Content-Length", 0))
        #
        #     if(code[0:1] == "2" or re.search(mimeType, ttype) != None or size > 0):
        #         return True
        #     tool.line()
        #     self.out(ttype)
        #     self.out(str(size))
        #     self.out(str(head))
        #     # self.show(response)
        # except Exception as e:
        #     tool.line()
        #     self.out(str(url))
        #     print(traceback.format_exc())
        #
        # return False

    def encode(self, text=""):
        if(type(text) == str):
            return urllib.quote(text)
        elif(type(text) == dict):
            return urllib.urlencode(text)
        return text
    def decode(self, text=""):
        if(type(text) == str):
            return urllib.unquote(text)
        elif(type(text) == dict):
            return urllib.urldecode(text)
        return text
    # 访问地址后 set-cookie自动被设置
    def doGet(self, url):
        response = "error" 
        try:
            self.out(url)
            response = self.opener.open(url)
            # self.show(response)
        except Exception as e:
            tool.line()
            self.out(str(url))
            print(traceback.format_exc())
        return response
    def doPost(self, url=None, postData=None):
        response = "error" 
        try:
            self.out(url)
            if(postData != None):
                postData = urllib.urlencode(postData)
                self.out(postData)
                response = self.opener.open(url, postData) 
            else:
                response  = self.opener.open(url)
            # self.show(response)
        except Exception as e:
            tool.line()
            self.out(str(url))
            self.out(str(postData))
            print(traceback.format_exc())
        return response
    def do(self, url=None, postData=None):
        if(url != None and url != ""):
            return self.doPost(url, postData)
        return "error, url=null?"
    def doJson(self, url="", postData=None):
        res = {}
        responce = self.do(url, postData)
        if(type(responce) == str):
            jsonStr = responce
        else:
            jsonStr = responce.read()
        if(jsonStr != None and type(jsonStr) == str):
            jsonStr = jsonStr.strip()
            res = tool.toJson(jsonStr)
        else:
            self.out("responce 读取失败,url:" + str(url) + " data:" + str(postData))
        return res















