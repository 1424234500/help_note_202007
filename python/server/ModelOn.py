#!/usr/bin/env python
#-*- coding:utf-8 -*- 
from include import *

#####################
# 通用型 开关量传感器模块
# 
# 烟雾模块Mq2   是否有害气体
# 光敏模块      是否强光 
# 声音模块      是否嘈杂
# 红外避障      是否有障碍物
# 人体红外      是否有人经过 两种模式  L模式是不可重复触发 封锁时间2.5s H模式是可以重复触发 会一直输出高电平

########################################
################################################
@singleton
class ModelOn:
    def __init__(self):
        self.m_ports = (16, 18, 22, 32)
        self.m_status = {}
    def get(self, callback):
        self.callback = callback
        ThreadRun("Get status", self.threadQueryRun).start()
        return
    def threadQueryRun(self):
        tm = timeMark()

        res = []
        i = 0
        for port in self.m_ports:
            va = System().getPort(port)
            res.append(va)  # int(random.uniform(1, 10))
            self.m_status[port] = va
            i += 1

        timeOut(tm, '通用开关量监控')

        self.callback(res)
        return
