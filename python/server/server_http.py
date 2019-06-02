#!/usr/bin/env python
#-*- coding:utf-8 -*-  
import tornado.ioloop
import tornado.web  
import tornado.httpserver  
from include import *

########################################
#####################self

from HandlerTest import HandlerTest
from HandlerStudent import HandlerStudent
from HandlerSystem import HandlerSystem




#####################
@singleton
class ServerHttp:

    def __init__(self, port):
        self.port = port
        self.application = tornado.web.Application([ 
            (r"/", HandlerTest),
            (r"/+do/+student/+(?P<method>.+)/+(?P<params>.*)", HandlerStudent),
            (r"/+do/+system/+(?P<method>.+)/+(?P<params>.*)", HandlerSystem), #非raspberry上运行需要屏蔽此服务

        ])
        return 
    def start(self):
        port = self.port
        print("Start server http " + str(port))
        self.application.listen(port)
        tornado.ioloop.IOLoop.instance().start()

'''
1、在路由映射条件里用正则匹配访问路径后缀
2、给每一个正则匹配规则(?P<设置名称>)设置一个名称，
3、在逻辑处理的get()方法或post()方法，接收这个正则名称，就会接收到用户访问的后缀路径
'''

if __name__ == "__main__":
    serverHttp = ServerHttp(8086)
    serverHttp.start()
    
    # print("Start server http ")
    # application.listen(8086)
    # tornado.ioloop.IOLoop.instance().start()



