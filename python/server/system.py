#!/usr/bin/env python
#-*- coding:utf-8 -*- 

import RPi.GPIO as GPIO    



from include import *


######################################
@singleton
class System: 

    #plan the ports to user
    #           L6  R6  L7  L8  R8  R9  R11 L4     L-6camera -5move  -4move -3move  -2move
    s_gpios = [ 11, 12, 13, 15, 16, 18, 22, 7,     29,        31, 33,35, 37 ]
    #                R-5 R-3 -2  -1
    s_gpioshigh = [  32, 36, 38, 40 ]
    #          R3 L5 
    s_gnds = [ 6, 9, 14, 20, 25, 30, 34, 39 ] 
    s_gin = {}
    s_gout = {}
    s_gnd = {}
    s_pwms = {} #pwm s

    def __init__(self):
        print('system.init')
        # BOARD编号方式，基于插座引脚编号    
        GPIO.setmode(GPIO.BOARD)
        GPIO.setwarnings(False)  
        #输出配置
        GPIO.setup(self.s_gpios, GPIO.OUT, initial=0)
        #输入配置 
        GPIO.setup(self.s_gpioshigh, GPIO.IN) 
        self.s_gin = self.inputPort(self.s_gpioshigh)
        self.s_gout = self.makePort(self.s_gpios)
        self.s_gnd = self.makePort(self.s_gnds)
        return
    def getGin(self):
        return self.s_gin
    def getGout(self):
        return self.s_gout
    def getGnd(self):
        return self.s_gnd




# 同步async 异步sync
# 摄像头舵机宣旋转
# 完全控制 生成dc区间序列 周期控制渐变 dc
# port, hz, dcFrom, dcTo, dcDeta, sleepTime
    def controlPwmAsync(self, port, hz, dcFrom, dcTo, dcDeta, sleepTime):
        timeStart = int(time.time()*1000)

        # print('from', dcFrom,'to->', dcTo,'deta', dcDeta, sleepTime) 
        pwm = GPIO.PWM(port, hz) #通道12 50hz
        pwm.start(0)    #空置

        # 12 15 deta:2 -> 12,14,16/15
        dcNow = dcFrom

        if(dcTo > dcFrom):  #递增
            while (dcNow <= dcTo):
                pwm.ChangeDutyCycle(dcNow)    #改变占比
                time.sleep(sleepTime)

                if(dcNow >= dcTo):
                    break
                dcNow = dcNow + dcDeta
                if(dcNow > dcTo):
                    dcNow = dcTo
        elif(dcTo < dcFrom): #递减
            while (dcNow >= dcTo):
                pwm.ChangeDutyCycle(dcNow)    #改变占比
                time.sleep(sleepTime)

                if(dcNow <= dcTo):
                    break
                dcNow = dcNow - dcDeta
                if(dcNow < dcTo):
                    dcNow = dcTo
        pwm.stop()

        timeStop = int(time.time()*1000)
        timeDeta = timeStop - timeStart

        return timeDeta

    def testPwm(self, port, hz, dc):
        self.p = GPIO.PWM(port, hz) #通道12 50hz
        self.p.start(0) 
        self.p.ChangeDutyCycle(dc)
        time.sleep(2)

        for d in range(15): 
            self.p.ChangeDutyCycle(d)
            time.sleep(0.3)
        # time.sleep(0.005)  
        p.stop()

    def openPortPwm(self, port, hz, dc):
        if(self.s_pwms.has_key(port)):
            res = False
            info = 'have open pwm: ' + str(port)
        else:
            self.s_pwms[port] = GPIO.PWM(port, hz) #通道12 50hz
            self.s_pwms[port].start(dc) 
            res = True
            info = 'open pwm port: ' + str(port) + ' hz: ' + str(hz) + ' dc: ' + str(dc)
        return res, info
    def setPortPwm(self, port, hz, dc):
        if(self.s_pwms.has_key(port)):
            self.s_pwms[port].ChangeDutyCycle(dc)
            res = True
            info = 'turn pwm port: ' + str(port) + ' hz: ' + str(hz) + ' dc->: ' + str(dc)
        else:
            res = False
            info = 'no exist pwm port: ' + str(port)
        return res, info
    def closePortPwm(self, port):
        if(self.s_pwms.has_key(port)):
            self.s_pwms[port].stop()
            self.s_pwms.pop(port)
            res = True
            info = 'close pwm port: ' + str(port)
        else:
            res = False
            info = 'no exist pwm port: ' + str(port)
        return res, info


# 重复设置输入输输出
    def turnOut(self, port, value=0):
        #输出配置
        GPIO.setup(port, GPIO.OUT, initial=0)
        return
    def turnIn(self, port):
        #输入配置 
        GPIO.setup(port, GPIO.IN) 
# 读取端口
    def getPort(self, port):
        res = GPIO.input(port)
        self.s_gin[port] = res
        return res
# 设置输出端口值
    def setPort(self, port, value=0):
        port = int(port)
        value = int(value)
        self.s_gout[port] = value
        GPIO.output(port, value)
        res = True
        info = ' set port ' + str(port) + ' ' + str(value)
        return res, info
    def setPorts(self, ports, value=0):
        for port in ports:
            self.setPort(port, value)
        return
    def openPort(self, port):
        return self.setPort(port, 1)
    def openPorts(self, ports):
        self.setPorts(ports, 1)
        return
    def closePort(self, port):
        return self.setPort(port, 0)
    def closePorts(self, ports):
        self.setPorts(ports, 0)
        return




        
    def inputPort(self, arr): 
        res = {}
        i = 0
        for port in arr: 
            status = GPIO.input(port)  
            res[port] = status
            i += 1
        return res

    def makePort(self, arr):
        res = {}
        i = 0
        for port in arr:  
            res[port] = 0
            i += 1   
        return res
    



 