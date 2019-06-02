#!/usr/bin/env python
#-*- coding:utf-8 -*- 
import tornado.ioloop
import tornado.web

from include import *

############################
#/do/student/home/aaa
class HandlerStudent(tornado.web.RequestHandler):

    def post(self, method, params):
        self.set_header("Content-Type", "text/plain")
        self.write("StudentHandler post !method:" + method + " params:" + params)
    def get(self, method, params):
        params = params.encode('utf-8')
        method = method.encode('utf-8')
        print("class:  " + self.__class__.__name__)    #className
        print("method: " + method)    #list
        print("params: " + params)    #{arg1: 'a1', arg2: 'a2' }
        #检查成员
        ret = hasattr(self, method) #因为有func方法所以返回True 
        if(ret == True) :
            #获取成员
            method = getattr(self, method)#获取的是个对象
            method(params) 
        else :
            print("该方法不存在")
            self.write(" 该方法不存在 StudentHandler get !method:" + method + " params:" + params)



    
    def getports(self, params): 
        
        res = Tool.exe("uptime")

        print(res)

        self.write(res)
        return
