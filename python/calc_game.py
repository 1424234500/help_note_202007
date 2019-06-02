#!/usr/bin/python
# -*- coding: UTF-8 -*-

import tool

"""

me 13042    432     598

xx 8000     1580    190
best sm       gj   fy
min         400       500

d-sm = 1900 v    
d-gj = 10 v
d-fy = 20 v
8000 / (y - 190) * (1580 - z) = x

min = y/10 + z/20 
"""
lll = [] 
gjdefault = 412
fydefault = 640
smdefault = 27906
smnowneed = 33840
gj = gjdefault
for i in range(20):
    cc = 8000 / (gj - 190) #回合
    print("count:" + str(cc))
    fy=640
    smp = (1580 - fy)      #每回合消耗
    sm = smp * cc           #总消耗
    ttt = (gj-gjdefault)/10 + (fy-fydefault)/20
    while ( sm >= smdefault and ttt < 10):

        smp = (1580 - fy)      #每回合消耗
        sm = smp * cc           #总消耗
        ttt = (gj-gjdefault)/10 + (fy-fydefault)/20
        
        obj={"ttt":ttt,"gj":gj,"fy":fy,"sm":sm,"cc":cc}
        print(obj)
        lll.append(obj)
        fy += 20
    gj += 10
    
reslist = sorted(lll, cmp=lambda x,y: cmp(x["sm"], y["sm"])   )

for obj in reslist:
    print(obj)
print "-----------"
for obj in lll:
    print(obj)









