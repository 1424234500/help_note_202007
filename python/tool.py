#!/usr/bin/env python
#-*- coding:utf-8 -*-  

import json
import os
import sys
import time
import uuid
import threading
import random
import ast

########################################
# from cv_makecolor import MakeColor
# 不需要上下文的工具类
############################
# 使用方式 
# import tool
# tool.exe

# img二维数组 压缩 value=0-255 100/height
# 1字节Byte = 8bit = 256编码  16进制2位 2f
def makeByte(img):
    res = ''
    size = img.size
    for row in img:
        for col in row:
            res += hex(col)[2:4]

    return res
# 按权重分配随机数选择器 1024 512 ... 1
def getRandomWeight(start=0, stop=5, step=3):
    res = 0
    size = stop - start # 5    2^5=32-1=31=16 8 4 2 1 ->
    area = []
    cc = 1
    for i in range(size): #   0, 1, 2, 3, 4
        for j in range(cc): # 1, 2, 4, 8, 16   1 3 9 27
            area.append(i)  # 0, 1,1, 2,2,2,2, 3,3,3,3,3,3,3,3,
        cc = cc * step
    ran = int(random.uniform(0, len(area)) ) # getRandom(0, len(area)) # 0,1,2
    res = size - 1 - area[ran]    # 0,1 -> 1,0

    return res
def getRandom(start=0, stop=10):
    if(start < 0):
        start = 0
    if(stop <= start):
        stop = start + 1
    msec = getNowTime() + int(random.uniform(0, 100) )
    # 时间轴 毫秒+随机数100 投影到目标区间
    return int(msec % (stop - start) + start)

def getUuid():
    return (str(uuid.uuid1())).split("-")[0]
# 编码问题  
def encode(string):
    t = type(string)
    res = string
    if(t == unicode):
        # res = res.encode('unicode-escape').decode('string_escape') 
        res = res.encode('utf-8')
        # print(t, string, "->", res)
    elif(t == int):
        pass
    else:
        pass
    return res

# 递归转换对象词典 为 utf encode 避免Unicode!!!!!!!!!!!!
def makeObj(data):
    # if this is a list of values, return list of byteified values
    if isinstance(data, list):
        return [ makeObj(item) for item in data ]
    # if this is a dictionary, return dictionary of byteified keys and values
    # but only if we haven't already byteified it
    if isinstance(data, dict):
        res = {}
        for key, value in data.iteritems():
            res[encode(key)] = makeObj(value)
        return res
    # if it's anything else, return it in its original form
    return encode(data)
# 通过字符串 解析为json 并编码 Unicode
def toJson(jsonStr):
    # print("toJson")
    # print(jsonStr)
    # print(type(jsonStr))
    if isinstance(jsonStr, dict):
        return makeObj(jsonStr)
    if(jsonStr == None or jsonStr == ""):
        return {}
    if(type(jsonStr) is str and jsonStr.strip()[0:1] != "{" and jsonStr.strip()[0:1] != "["):
        return {"error":jsonStr}
    # json.loads(jsonStr) 针对单引号问题ast.literal_eval(jsonStr)
    return makeObj(json.loads(jsonStr) )



# 获取某个模块或者 class 值为value的变量名
def getClassName(cla, value):
    keys = dir(cla)
    for key in keys:
        ret = hasattr(cla, key) 
        if(ret == True) :
            method = getattr(cla, key)#获取的是个对象
            if(value == method):
                return key

    return "None key"


#exe the shell cmd, return the string encode by utf-8
def exe(str):
    # (status, output) = commands.getstatusoutput(str)
    # return output
    return os.popen(str).read().encode('utf-8') 

# do the method of the class, *params动态参数 元组 也可以作为动态参数传递
def doMethod(cls, methodName, *params):
    print('# do method')
    print("class:  " + cls.__class__.__name__)    #className
    print("method: " + methodName)    #list
    print("params: " + str(params))    #{arg1: 'a1', arg2: 'a2' }
    #检查成员
    ret = hasattr(cls, methodName) #因为有func方法所以返回True 
    if(ret == True) :
        #获取成员
        method = getattr(cls, methodName)#获取的是个对象
        # length = len(params)
        # if(length == 0):
        #     return method()
        # else:
        return method(*params)
    else :
        print("Error! 该方法不存在")
    return ''

def sleep(mills):
    time.sleep(mills)

# time 199313231000
def getNowTime():
    return int(time.time()*1000)
def parseTime(timeStamp = 0, format = "%Y-%m-%d %H:%M:%S"):
    # 使用time
    timeArray = time.localtime(timeStamp)
    res = time.strftime(format, timeArray)
    return res
def line():
    print("--------------------------------")
def toString(dictObj):
    res = "[ "
    for key in dictObj.keys():
        res = res + '' + key + ':' + dictObj[key] + ","
    res = res[0:len(res)-1] + " ]"
    return res
# 补齐长度
def fill(argStr, char=' ', toLen = 10):
    length = len(argStr)
    charLen = len(char)
    for i in range((toLen - length) / charLen):
        argStr = argStr + str(char)
    return argStr
def wait(waitTime=0):
    if(waitTime == 0):
        while(True):
            time.sleep(888)
    else:
        sleep(1.0 * waitTime / 1000)
    return waitTime
def calcTime(mills=60000):
    mills = int(mills)
    levh = 60 * 60 * 1000
    levm = 60 * 1000
    levs = 1000
    if(mills / levh > 0):
        res = str(mills / levh ) + "h" + str(mills % levh / levm) + "m"
    elif(mills / levm > 0):
        res = str(mills / levm) + "m" + str(mills % levm / levs) + "s"
    elif(mills / levs > 0):
        res = str(mills / levs) + "s" + str(mills % levs / 1) + "ms"
    else:
        res = str(mills) + "ms"
    return res
# 日志输出
def out(obj):
    print(time.strftime("%Y%m%d %H:%M:%S", time.localtime()) + "." + str(obj))
    return



# 线程操作类
class ThreadRun (threading.Thread):
    def __init__(self, name, runCallback, daemon=True):
        threading.Thread.__init__(self)
        self.name = name
        self.runCallback = runCallback
        self.setDaemon(daemon)  # 子线程随主线程退出

    def run(self):
        print "============Thread Start " + self.name
        self.runCallback()
        print "==Thread Stop  " + self.name




if __name__ == '__main__':
    res = {}
    cc = 1000
    ss = 5
    for i in range(cc):
        geti = getRandomWeight(0, ss)
        res[str(geti)] = res.get(str(geti), 0) + 1

    reslist = sorted(res.items(), cmp=lambda x,y: cmp(x, y)   )
    print(reslist)

