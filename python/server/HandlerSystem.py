#!/usr/bin/env python
#-*- coding:utf-8 -*- 

import tornado.ioloop
import tornado.web

########################################
from include import *
############################

#/do/system/home/aaa
class HandlerSystem(tornado.web.RequestHandler): 
    def post(self, method, params):
        self.get(method, params)
        return
    def get(self, method, params):
        params = params.encode('utf-8')
        method = method.encode('utf-8')
        

        # tool.doMethod(self, method, params)
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
        
        return



# left right head back space stop
    def move(self, params):
        if(params == 'left'):
            ModelMove().turnLeft()
        elif(params == 'right'):
            ModelMove().turnRight()
        elif(params == 'head'):
            ModelMove().moveHead()
        elif(params == 'back'):
            ModelMove().moveBack()
        elif(params == 'space'):
            ModelMove().space()
        elif(params == 'stop'):
            ModelMove().stop()
        elif(params == 'faster'):
            ModelMove().moveFaster(1)
        elif(params == 'slower'):
            ModelMove().moveFaster(-1)
        elif(params == 'turnrevert'):
            ModelMove().turnRevert()

            
        res = {
            "control":params,
        }
        print(res)
        self.write(res)
        return
# 0 1 
    def cameraTurn(self, params):
        # obj = json.loads(params)
        if(params == "0"):
            deta = 20
            (ifMove, info, costTime) = ModelTurn().turnDeta(deta)
        elif(params == "1"):
            deta = -20
            (ifMove, info, costTime) = ModelTurn().turnDeta(deta)
        else:
            deta = 0
            (ifMove, info, costTime) = ModelTurn().turnTo()

        res = {
            "ifmove":ifMove,
            "info":info,
            "costtime":costTime,
        }
        print(res)
        self.write(res)
        return
# 20-0  20-1
    def setports(self, params):    
        port = params.split("-")[0]
        value = params.split("-")[1] 
        print(port, value)
        if(value == "0"):
            System().closePort(int(port))
        else:
            System().openPort(int(port))
            
        self.getports(params)
        return

    def getports(self, params): 
        res = {
            "gin" : System().getGin(),
            "gout" : System().getGout(),
            "gnd" : System().getGnd(), 
        }
        # print(res)
        
        self.write(res)
        return

    def home(self, params) : 
        res = 'home'
        print(res)
        self.write(res)
        return
        
        
        
        
        
        
        
        

        
        
        




 