#!/usr/bin/env python
#-*- coding:utf-8 -*- 
from include import *

#####################
# 超声波模块HcSro4
# VCC 5v 15mA
# GND
# TRIG  触发控制信号输入10uS TTL脉冲
# ECHO  回响输出    TTL电平

# 工作频率 40kHz
# 射程 2cm -> 4M
# 角度  15
# 尺寸  45x20x15mm


########################################
################################################
# @singleton
class ModelHcSro4:
    def __init__(self):
                            #trig   echo
        self.m_ports =      [31,       33]
        self.m_status =     [0, 0]

        System().closePorts(self.m_ports)

    def get(self, callback):
        self.callback = callback
        ThreadRun("qeurySpan", self.threadQueryRun).start()
        return
    def threadQueryRun(self):
        System().openPort(self.m_ports[0])
        time.sleep(0.00015)
        System().closePort(self.m_ports[0])
        while not System().getPort(self.m_ports[1]):
            pass
        t1 = time.time()
        while System().getPort(self.m_ports[1]):
            pass
        t2 = time.time()
        res = (t2-t1)*340*100/2
        self.callback(res)
        return

# init
ModelHcSro4()
