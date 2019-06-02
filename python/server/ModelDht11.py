#!/usr/bin/env python
#-*- coding:utf-8 -*- 
from include import *

#####################
# 温湿度模块Dht11
# VCC 3v
# GND
# DATA 串行数据 单总线
# 一次传输40位数据=8bit湿度整数数据 + 8bit湿度小数数据 + 8bint温度整数数据 + 8bit温度小数数据 + 8bit校验位 
 


########################################
################################################
@singleton
class ModelDht11:
    def __init__(self):
                    #data
        self.m_port = 12
        self.m_status = 0
        System().closePort(self.m_port)

    def get(self, callback):
        self.callback = callback
        ThreadRun("getT", self.threadQueryRun).start()
        return
    def threadQueryRun(self):
        tm = timeMark()

        data = self.readData()
        res = self.parseData(data)

        timeOut(tm, '温度读取')

        self.callback(res)
        return
    def readData(self):
        port = self.m_port
        data = []
        system = System()
        system.turnOut(port)
        system.closePort(port)
        time.sleep(0.02)
        system.openPort(port)
        system.turnIn(port)
        while(system.getPort(port) == 0):
            continue
        while(system.getPort(port) == 1):
            continue
        cc = 0
        while(cc < 40):
            bb = 0
            while(system.getPort(port) == 0):
                continue
            while(system.getPort(port) == 1):
                bb += 1
                if(bb > 100):
                    break
            if(bb < 8):
                data.append(0)
            else:
                data.append(1)
            cc += 1
        return data
        
    def parseData(self, data):

        out("Sensor DHT11 is working.")
        out(data)   

        humidity_bit = data[0:8]  
        humidity_point_bit = data[8:16]  
        temperature_bit = data[16:24]  
        temperature_point_bit = data[24:32]  
        check_bit = data[32:40]  

        humidity = 0  
        humidity_point = 0  
        temperature = 0  
        temperature_point = 0  
        check = 0  

        for i in range(8):  
            humidity += humidity_bit[i] * 2 ** (7-i)  
            humidity_point += humidity_point_bit[i] * 2 ** (7-i)  
            temperature += temperature_bit[i] * 2 ** (7-i)  
            temperature_point += temperature_point_bit[i] * 2 ** (7-i)  
            check += check_bit[i] * 2 ** (7-i)  

        tmp = humidity + humidity_point + temperature + temperature_point  

        out( "temperature :", temperature, "*C, humidity :", humidity, "% check :", check, ", tmp :", tmp  )
        return temperature, humidity 



# channel =4   
# data = []  
# j = 0  
  
# GPIO.setmode(GPIO.BCM)  
  
# time.sleep(1)  
  
# GPIO.setup(channel, GPIO.OUT)  
# GPIO.output(channel, GPIO.LOW)  
# time.sleep(0.02)  
# GPIO.output(channel, GPIO.HIGH)  
# GPIO.setup(channel, GPIO.IN)  
  
# while GPIO.input(channel) == GPIO.LOW:  
#   continue  
# while GPIO.input(channel) == GPIO.HIGH:  
#   continue  
  
# while j < 40:  
#   k = 0  
#   while GPIO.input(channel) == GPIO.LOW:  
#     continue  
#   while GPIO.input(channel) == GPIO.HIGH:  
#     k += 1  
#     if k > 100:  
#       break  
#   if k < 8:  
#     data.append(0)  
#   else:  
#     data.append(1)  
  
#   j += 1  
  
# GPIO.cleanup() 