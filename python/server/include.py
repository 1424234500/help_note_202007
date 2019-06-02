#!/usr/bin/env python
#-*- coding:utf-8 -*-  
#############################
# 导入常用工具模块
import sys
import os
import json
import re
import codecs
import time
import threading
import thread
import subprocess as sp
import numpy as np
import socket
import struct
import yaml
import random   # int(random.uniform(1, 10))
import uuid
import base64


# module = __import__(controller)  #这句话就相当于import controller as module

##############################
# 导入父目录为可引用路径
sys.path.append("../")
sys.path.append("../opencv/")

##########################
# 导入单例装饰器函数 : @singleton
from python_singleton import singleton
# 导入工具 模块 .py : tool.exe()
import tool
import C
import MSGTYPE



def sleep(mills):
    tool.sleep(mills)
# 日志
def out(*objs):
    print(objs)
    return
# 耗时
def timeMark():
    return int(time.time()*1000)
def timeOut(timeStart, info=''):
    timeStop = int(time.time()*1000)
    timeDeta = timeStop - timeStart
    out(info + ' cost ' + str(timeDeta))

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

 

from python_sqlite import Database

# 数据库工具
from ServiceDb import ServiceDb 

# 导入普通类
from template import Template
# from cv_makecolor import MakeColor

# 导入模块Class
try:
    from system import System
    from ModelTurn import ModelTurn
    from ModelMove import ModelMove
    from ModelOn import ModelOn
    from ModelHcSro4 import ModelHcSro4
    from ModelDht11 import ModelDht11
except Exception as e:
    print("Error import !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  ")
    print(e) 

# 导入服务
from Msg import Msg











