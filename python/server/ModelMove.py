#!/usr/bin/env python
#-*- coding:utf-8 -*- 
from include import *

#####################
# //H桥电机模块
# 前进      左右前
# 后退      左右退

# 左转      左空置 右前
#             左后退     右空置
#             左后退 又前

# 右转
# 左刹车
# 右刹车
# 左空置
# 右空置

#         IN1     IN2     IN3      IN4
# 左前   1/pwm   0       
# 左退   0       1/pwm
# 左空置 0       0
# 左刹车 1       1
########################################
m_dc_default = 60
################################################
@singleton
class ModelMove:
    def __init__(self):

        self.m_hz = 10            #pwm 0 : no pwm
        self.m_dc_start = 30
        self.m_dc_stop = 90
        self.m_dc_default = (self.m_dc_start + self.m_dc_stop) / 2
        self.m_dc_now_left =  m_dc_default
        self.m_dc_now_right = m_dc_default
        self.m_dc_deta = 20
                            #rh黄-IN1  rb绿-IN2  lh蓝-IN3  lb红-IN4 39灰-地
        self.m_ports =      [31,       33,       35,       37]
        self.m_status =     [0, 0, 0, 0]    #端口使用状态  0关闭  / 1pwm开 / 2pwm关普通开

        self.setPorts(0, 0, 0, 0)
# pwm/非pwm开关控制 
# port[0] value=1 dc=80
# port[1] value=1 dc=90
    def setMovePortPwm(self, cc, value = 0, dc = m_dc_default):
        print('setMovePortPwm', self.m_ports[cc], value, dc)
        if(value == 1): #打开
            if(dc >= self.m_dc_stop):   #无需pwm
                if(self.m_status[cc] == 0):     #关闭状态
                    res, info = System().setPort(self.m_ports[cc], 1)   #开启端口
                    self.m_status[cc] = 2 
                elif(self.m_status[cc] == 1):   #pwm开启状态
                    res, info = System().closePortPwm(self.m_ports[cc])     #关闭pwm
                    print(res, info)
                    self.m_status[cc] = 0 
                    res, info = System().setPort(self.m_ports[cc], 1)   #开启端口
                    self.m_status[cc] = 2 
                elif(self.m_status[cc] == 2):   #已经开启端口
                    res = False
                    info = 'have open port ' + str(self.m_ports[cc])        #不操作
            else:                       #需要pwm
                if(self.m_status[cc] == 0):     #关闭状态
                    res, info = System().openPortPwm(self.m_ports[cc], self.m_hz, dc)     #开启pwm
                    self.m_status[cc] = 1 
                elif(self.m_status[cc] == 1):   #pwm开启状态
                    res = False
                    info = 'have open pwm ' + str(self.m_ports[cc])        #不操作
                elif(self.m_status[cc] == 2):   #已经开启端口
                    res, info = System().closePort(self.m_ports[cc])     #关闭端口
                    print(res, info)
                    self.m_status[cc] = 0
                    res, info = System().openPortPwm(self.m_ports[cc], self.m_hz, dc)     #开启pwm
                    self.m_status[cc] = 1 
        else:       #关闭
            if(self.m_status[cc] == 0):     #关闭状态
                res, info = System().closePort(self.m_ports[cc])        #不操作 再确认关闭端口
            elif(self.m_status[cc] == 1):   #pwm开启状态
                res, info = System().closePortPwm(self.m_ports[cc])     #关闭pwm
                self.m_status[cc] = 0 
            elif(self.m_status[cc] == 2):   #已经开启端口
                res, info = System().closePort(self.m_ports[cc])     #关闭端口
                self.m_status[cc] = 0 

        print(res, info)

# pwm 更新 调速dc 0/100
    def updateMovePortPwm(self, cc, dc = m_dc_default):
        print('updateMovePortPwm', cc, dc)

        if(dc >= self.m_dc_stop):   #无需pwm
            if(self.m_status[cc] == 0):   #已经关闭端口
                res = False
                info = 'have close port ' + str(self.m_ports[cc])        #不操作
            elif(self.m_status[cc] == 1):   #pwm开启状态
                res, info = System().closePortPwm(self.m_ports[cc])     #关闭pwm
                print(res, info)
                self.m_status[cc] = 0 
                res, info = System().setPort(self.m_ports[cc], 1)   #开启端口
                self.m_status[cc] = 2 
            elif(self.m_status[cc] == 2):   #已经开启端口
                res = False
                info = 'have update to open port ' + str(self.m_ports[cc])        #不操作
        else:                       #需要pwm
            if(self.m_status[cc] == 0):   #已经关闭端口
                res = False
                info = 'have close port ' + str(self.m_ports[cc])        #不操作
            elif(self.m_status[cc] == 1):   #pwm开启状态
                res, info = System().setPortPwm(self.m_ports[cc], self.m_hz, dc)    #更新pwm
            elif(self.m_status[cc] == 2):   #已经开启端口
                res, info = System().closePort(self.m_ports[cc])     #关闭端口
                print(res, info)
                self.m_status[cc] = 0
                res, info = System().openPortPwm(self.m_ports[cc], self.m_hz, dc)     #开启pwm
                self.m_status[cc] = 1 
        print(res, info)


# 根据values状态控制移动状态
    def setPorts(self, *values): 
        self.setMovePortPwm(0, values[0], self.m_dc_now_right)
        self.setMovePortPwm(1, values[1], self.m_dc_now_right)

        self.setMovePortPwm(2, values[2], self.m_dc_now_left)
        self.setMovePortPwm(3, values[3], self.m_dc_now_left)

# 单独更新dc 不变状态 value= 0~1 单边调速
    def updateLeft(self, value = 1):
        self.updateMovePortPwm(2, value * self.m_dc_now_left)
        self.updateMovePortPwm(3, value * self.m_dc_now_left)
# 单独更新dc 不变状态 value= 0~1 单边调速
    def updateRight(self, value = 1):
        self.updateMovePortPwm(0, value * self.m_dc_now_right)
        self.updateMovePortPwm(1, value * self.m_dc_now_right)

# 根据新修改过的dc left/right更新速度 90dc上下修改pwm为端口开闭
    def updatePorts(self): 
        self.updateMovePortPwm(0, self.m_dc_now_right)
        self.updateMovePortPwm(1, self.m_dc_now_right)

        self.updateMovePortPwm(2, self.m_dc_now_left)
        self.updateMovePortPwm(3, self.m_dc_now_left)
# 速度调控 快 慢 分档 dc 0-100
    def moveFaster(self, flag = 1):
        self.m_dc_now_right = self.m_dc_now_right + self.m_dc_deta * flag
        if(self.m_dc_now_right < self.m_dc_start):
            self.m_dc_now_right = self.m_dc_start
        elif(self.m_dc_now_right > self.m_dc_stop):
            self.m_dc_now_right = self.m_dc_stop

        self.m_dc_now_left = self.m_dc_now_left + self.m_dc_deta * flag
        if(self.m_dc_now_left < self.m_dc_start):
            self.m_dc_now_left = self.m_dc_start
        elif(self.m_dc_now_left > self.m_dc_stop):
            self.m_dc_now_left = self.m_dc_stop

        self.updatePorts()
    def moveFasterTo(self, dc = m_dc_default):
        if(dc > self.m_dc_stop):
            dc = self.m_dc_stop
        elif(dc < self.m_dc_start):
            dc = self.m_dc_start

        self.m_dc_now_right = dc
        self.m_dc_now_left = dc
        
        self.updatePorts()
    def getStatus(self):
        res = ''
        for ss in self.m_status:
            res = res + str(ss)
        return res

    def moveHead(self):
        #rh黄-IN1  rb绿-IN2  lh蓝-IN3  lb红-IN4 39灰-地
        self.setPorts(1, 0, 1, 0) 

    def moveBack(self):
        #rh黄-IN1  rb绿-IN2  lh蓝-IN3  lb红-IN4 39灰-地
        self.setPorts(0, 1, 0, 1) 
        
    def moveLeft(self): #原地转向
        self.setPorts(0.5, 0, 0, 0)
    def moveRight(self): #原地转向
        self.setPorts(0, 0, 0.5, 0) 

    def turnRevert(self): #取消单边降速状态
        self.updateLeft(1)
        self.updateRight(1)

    def turnLeft(self): #R 快 L慢/0/刹车 单边降速

        #rh黄-IN1  rb绿-IN2  lh蓝-IN3  lb红-IN4 39灰-地
        # self.setPorts(1, 0, 0, 0.5)
        self.updateLeft(0.5)

    def turnRight(self): #L 快 R慢/0/刹车

        #rh黄-IN1  rb绿-IN2  lh蓝-IN3  lb红-IN4 39灰-地
        # self.setPorts(0, 1, 1, 1) 
        self.updateRight(0.5)

    def stop(self):
        self.setPorts(1, 1, 1, 1)   #1111

    def space(self):
        self.setPorts(0, 0, 0, 0)  #0


# init
ModelMove()
