#!/usr/bin/env python
#-*- coding:utf-8 -*- 
from include import *

#####################
# 数码管F3461BH
# 译码器38
# 9端口 
# 3线 控8口 7个led         +   1dot + 1open
# 4线 7led+1open + 1&
# 3  4  5  6  7  8  9
nums =(
    (0, 0, 0, 0, 0, 0, 1),  #0
    (1, 0, 0, 1, 1, 1, 1),  #1
    (0, 0, 1, 0, 0, 1, 0),  #2
    (0, 0, 0, 0, 1, 1, 0),  #3
    (1, 0, 0, 1, 1 ,0, 0),  #4
    (0, 1, 0, 0, 1, 0, 0),  #5
    (0, 1, 0, 0, 0, 0, 0),  #6
    (0, 0, 0, 1, 1, 1, 1),  #7
    (0, 0, 0, 0, 0, 0, 0),  #8
    (0, 0, 0, 0, 1, 0, 0),  #9
)
# 
PIN_DATA = 24   
### 定义单个数码管各段led对应的GPIO

### 定义1到4号数码管阳极对应的GPIO
DIGIT1 = 16   

# RPi.GPIO.output(LED_A, False)   
# RPi.GPIO.output(LED_DP, not showDotPoint)  
# 
######################################
class ModelNum:
# default位置角度 
    def __init__(self):
        print('ModelNum.init')

        self.m_ports =      [31,       33,       35,       37]
        self.s_ports = ()
        self.m_status =     [0, 0, 0, 0]    #端口使用状态  0关闭 2pwm关普通开
        self.num = 0
        return

    def setNum(self, num=0):
        self.num = 0

        return


# init
# ModelTurn()
if __name__ == "__main__":
    pass



