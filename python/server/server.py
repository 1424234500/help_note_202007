#!/usr/bin/env python
#-*- coding:utf-8 -*-   
 
from include import *

from ServiceServer import ServiceServer

from server_socket import ServerSocket
# from server_http import ServerHttp


from ServerCamera import ServerCamera
from ServerSensor import ServerSensor
############################
# 启动后台

# 初始化数据库
ServiceDb().init()


# Socket后台
serverSocket = ServerSocket("192.168.0.10", 8092)
# serverSocket = ServerSocket("127.0.0.1", 8092)
serverSocket.start()
sleep(1)
# ServiceHttp 处理http请求
# serverHttp = ServerHttp(8086)
# serverHttp.start()

# 线程 Opencv监控摄像头 识别图像 调用socket推送消息
serverCamera = ServerCamera(serverSocket)
serverCamera.start()

# 线程 各种传感器监控 轮循监控
# serverSensor = ServerSensor(serverSocket)
# serverSensor.start()

while 1:
    sleep(5)
    pass

















