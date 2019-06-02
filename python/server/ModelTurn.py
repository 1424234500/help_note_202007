#!/usr/bin/env python
#-*- coding:utf-8 -*- 
from include import *

#####################
# 舵机转向模块
# 红vcc
# 橙信号   29端口 pwm控位
# 灰gnd
#  
# 转动规则 pwm 
# 频率 50hz / T:20ms
# 转动角度    周期内持续时间
# 
#  
t_time_default = 2000
t_default = 90
t_turn_default = 15 #默认左右转动15d

######################################
@singleton
class ModelTurn:
    test = ''
# default位置角度 
    def __init__(self, port=29):
        print('ModelTurn.init')
        ########################################
        # 20ms周期中 调整dc以控制角度 dc=k角度 dc的持续变动非跃迁 以实现角度的持续变动    T=T20+sleep
        #                                      1-sleep-2-sleep-3-sleep-4-sleep-5          10 20 30 40 50 
        #              端口29
        self.t_port = port
        self.t_hz = 50           #20ms 周期 1s 50T 舵机需要周期决定 
        self.t_t = 1000 / self.t_hz   #T 20ms
        self.t_count = 80        #转动180d 需要变换100c  最快变换速度1s/50c -> 2s移动完毕

        self.t_time_default = t_time_default#4000       #转动180d 4s 控制速度   最快(20+2)*t_count ms
        self.t_sleep_min = 0.002         # s最小延时 2ms
        self.t_sleep_default = (self.t_time_default / self.t_count - 1000 / self.t_hz) / 1000.0 #0.020  4000ms/100c=1000ms/50c + sleep:20ms
        self.t_min_time = (1000 / self.t_hz + self.t_sleep_min) * self.t_count  # 最小180d变换时间 ms


        # dc 
        self.t_dc_start = 1                         #最小dc
        self.t_dc_stop = 12
        self.t_dc_default = 6.2#(self.t_dc_start + self.t_dc_stop) / 2               #默认dc
        self.t_dc_deta = 1.0 * (self.t_dc_stop - self.t_dc_start) / self.t_count      #最小转动dc差值 16/80=0.2
        self.t_dc_now = self.t_dc_default

        # degree 度数定义
        self.t_start = 0                             #最小度数
        self.t_stop = 180
        self.t_default = (self.t_start + self.t_stop) / 2
        self.t_deta = 1.0 * (self.t_stop - self.t_start) / self.t_dc_deta   #最小转动度数
        self.t_now = self.t_default

        self.t_turn_degree2dc =  1.0 * (self.t_dc_stop - self.t_dc_start) / (self.t_stop - self.t_start) #12 转换degree为dc 0/15 y 0/180 x         y = 12*x + t_dc_start
        
        #return 复位90d
        System().openPortPwm(self.t_port, self.t_hz, self.t_dc_default)
        time.sleep(1)
        System().closePortPwm(self.t_port)
        return 

    def turnRight(self, deta = t_turn_default ):
        return self.turnDeta(deta)
    def turnLeft(self, deta = t_turn_default ):
        return self.turnDeta(-deta)
# 转至指定角度 45 90 135 移动速度3000
    def turnTo(self, toDegree = t_default, speed = t_time_default):
        detaDegree = toDegree - self.t_now
        return self.turnDeta(detaDegree, speed)

# 相对现在转一定角度 增加度数/减少度数 移动速度:3000ms 转动180d耗时
    def turnDeta(self, detaDegree = 0, speed = t_time_default):
        costTime = 0
        print('from', self.t_now, '->', detaDegree)

        (ifMove, dcMoveFrom, dcMoveTo, toDegree, info) = self.calcTurn(detaDegree)
        self.t_now = toDegree    #更新当前度数为预期度数

        # print('dc: ' + info, ifMove,'from', dcMoveFrom, 'to',dcMoveTo)
        if(ifMove):
            sleepTime = self.calcSpeed(speed)
            # port, hz, dcFrom, dcTo, dcDeta, sleepTime
            # System().openPortPwm(self.t_port, self.t_hz, dcMoveTo)
            # time.sleep(0.5)
            # System().closePortPwm(self.t_port)
            # costTime = 999
            costTime = System().controlPwmAsync(self.t_port, self.t_hz, dcMoveFrom, dcMoveTo, self.t_dc_deta, sleepTime)
            self.t_dc_now = dcMoveTo  #更新当前dc为新dc
            print('耗时: ' + str(costTime))
            # time.sleep(0.2)
        return (ifMove, info, costTime)


# 计算 速度对应的sleep时间 计算周期以此控制周期频率 控制转动速度
    def calcSpeed(self, speed):
        if(speed <= self.t_min_time):
            sleepTime = self.t_sleep_min #最快速度 sleep
        else:
            sleepTime = (speed / self.t_count - 1000 / self.t_hz) / 1000.0 #0.020  4000ms/100c=1000ms/50c + sleep:20ms
        return sleepTime

# 计算 转动角度后的预期 结果 from to pEnd info 并转换为dc制
# return (是否需要移动, fromDc, toDc, toDegree, 说明)
    def calcTurn(self, degree = 0):
        ifOk = False        
        info = ''
        if(degree > 0): #右转 增加度数
            if(self.t_now < self.t_stop):
                if(self.t_now + degree > self.t_stop):    #转动结果度数大于了最大度数
                    pEnd = self.t_stop
                    info = '转向到(最大): ' + str(pEnd)
                else:
                    pEnd = self.t_now + degree
                    info = '转向到: ' + str(pEnd)
            else:
                pEnd = self.t_now
                info = '已经转向到最大: ' + str(pEnd)
        else:       #左转 减少度数
            if(self.t_now > self.t_start):
                if(self.t_now + degree < self.t_start):   #小于了最小度数
                    pEnd = self.t_start
                    info = '转向到(最小): ' + str(pEnd)
                else:
                    pEnd = self.t_now + degree
                    info = '转向到: ' + str(pEnd)
            else:
                pEnd = self.t_now
                info = '已经转向到最小: ' + str(pEnd)


        if(pEnd == self.t_now):  #无操作
            info = '无操作 ' + info
        else:
            info = '从: ' + str(self.t_now) + ' ' + info
            ifOk = True 
        dcMoveF = self.t_now * self.t_turn_degree2dc + self.t_dc_start
        dcMoveT = pEnd * self.t_turn_degree2dc + self.t_dc_start

        return (ifOk, dcMoveF, dcMoveT, pEnd, info)
# init
# ModelTurn()
if __name__ == "__main__":

    m = ModelTurn()
    m.turnTo(0) 
    m.turnTo(180) 
    m.turnTo(0)
    m.turnTo(90)



