#!/usr/bin/env python
#-*- coding:utf-8 -*- 
from include import *

@singleton
class Template:
    """A simple example class""" 

    id = ""
    name = ""

    def doMethod(self, method, params):
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
            return method(params) 
        else :
            print("Error ! 该方法不存在")
            return ""

    def __init__(self):
        self.id = "test id"
        self.name = "test name"
        
    def set(self, id, name):
        self.id = id
        self.name = name

        return self

    def toString(self):
        res = ""
        res = self.id + " - " + self.name

        return res

if __name__ == '__main__':
    temp = Template()

    while 1:
        pass