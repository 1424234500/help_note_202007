#!/usr/bin/env python
#-*- coding:utf-8 -*- 
from include import *
##########################
# 自学习移动 地图生成
###########################

@singleton
class ControlMap:
    """ 
        auto move 
        and get the ways to map 
        send to master
    """ 

    def do(self, fromMsg):
        data = fromMsg["data"]

        #消息处理 默认发给请求者
        msg = Msg()
        msg.toSysKey = fromMsg["fromSysKey"]
        msg.toKey = fromMsg["fromKey"]
        msg.data = {}
        msg.msgType = 10                #单点回传
        msg.data["res"] = "true"
        msg.data["info"] = "info"
        msg.data["method"] = data.get("method", "no method ? ")

        msg = self.doMethod(msg, msg.data["method"], data.get("params", ""))
        return msg
 


    def doMethod(self, msg, method, params):
        # params = params.encode('utf-8')
        # method = method.encode('utf-8')

        # tool.doMethod(self, method, params)
        print("class:  " + self.__class__.__name__)    #className
        print("method: " + method)    #list
        print("params: " + params)    #{arg1: 'a1', arg2: 'a2' }
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
            return msg
 
            
 











 
    def toString(self):
        res = "" 

        return res

        