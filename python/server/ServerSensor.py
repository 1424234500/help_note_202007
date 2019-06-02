#!/usr/bin/env python
#-*- coding:utf-8 -*- 
from include import *


@singleton
class ServerSensor:
    """ 
        Service 
        轮循监控传感器状态
    """ 
    def __init__(self, serverSocket):
        self.serverSocket = serverSocket    # 通过此来推送关键消息
        return

    def start(self):
        ThreadRun("Sensor", self.run).start()
        pass
# 开启轮循
    def run(self):
        nowt = 0
        min = 0.1
        de = 1 / min
        while(True):

            if(nowt % (100 * de / 5) == 0):             # 0.2s
                pass
            if(nowt % (1 * de) == 0):             # 1S
                pass
            if(nowt % (2 * de) == 0):           # 2S
                # ModelHcSro4().get(self.callbackHcSro4)  # 超声波
                ModelOn().get(self.callbackOn)      #通用状态
                pass
            if(nowt % (5 * de) == 0):           # 5S
                pass
            if(nowt % (10 * de) == 0):           # 10S
                pass
            if(nowt % (150 * de) == 0):           # 120S
                pass
                ModelDht11().get(self.callbackDht11)    # 温湿度


            nowt += 1
            nowt = nowt % 6000
            sleep(min)

        return

    def callbackOn(self, res=   [0, 1, 0, 0]):
        pass
        print(res)
    def callbackDht11(self, res=(0, 0)):
        print(res)
        pass
    def callbackHcSro4(self, res=0):
        pint(res)
        pass




if __name__ == '__main__':
    serviceSensor = ServerSensor(False)

    serviceSensor.start()
