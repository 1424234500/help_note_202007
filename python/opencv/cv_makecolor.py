#!/usr/bin/python
#-*- coding:utf-8 -*-  
from cvhelp import CvHelp
import time
import os

class MakeColor:
    """A simple example class""" 

    id = ""
    name = ""

    def __init__(self):
        self.id = "test id"
        self.name = "test name"
        
    def set(self, id, name):
        self.id = id
        self.name = name

        return self

    def toString(self):
        res = ""
        res = self.id + " - " + self.name

        return res

    def make(self, name='test',count='1'):
        print('cv_makecolor 开始make图片线程 ' + name)
        cvhelp = CvHelp()
        name = '../app/resource/image/frame'

        delfile = 'rm ' + name + '*'
        print(delfile, os.popen(delfile).read())
        
        endname = '.png'
        width = 400
        height = 400
        image = cvhelp.createImage(width, height,(100,20,0))
        cvhelp.save(name+endname, image)
        # //r,g,b 
        max = 240
        deta = 120
        sleep = 10#0.020;
        # //max进制 
        # //rmax      g0      b0  
        # //rmax      gmax    b0
        # //r0        gmax    b0
        # //r0        gmax    bmax
        # //r0        g0      bmax
        # //rmax      g0      bmax
        # //rmax      g0      b0
        r = max
        g = 0
        b = 0  
        ff = 0
        oldf = -1
        oldname = ''
        oldoldname = ''
        flagThread = True
        ffff = 0
        i = 0
        while (flagThread):
            oldf = ff;

            if(oldf == 5 and ff == 0):
                ffff = 1

            if(r >= max     and g == 0       and b == 0): 
                ff = 0  
            if(r >= max     and g >= max     and b == 0): ff = 1;  
            if(r == 0       and g >= max     and b == 0): ff = 2;  
            if(r == 0       and g >= max     and b >= max): ff = 3;  
            if(r == 0       and g == 0       and b >= max): ff = 4;  
            if(r >= max     and g == 0       and b >= max): ff = 5;  
            
            switch = ff%6

            if(switch == -1 or switch == 0):
                g+=deta;            
            if(switch == 1):
                r-=deta;
            if(switch == 2):   
                b+=deta;
            if(switch == 3):
                g-=deta;
            if(switch == 4):
                r+=deta;
            if(switch == 5):
                b-=deta;


            print(i, r, g, b)

            # if(ffff == 1):

            delfile = 'rm ' + oldoldname
            print(delfile, os.popen(delfile).read())
            # os.remove(my_file)

            image = cvhelp.drawRect(image, (0,0), (width,height), (r, g, b), fill=True)
            filename = name + time.strftime("%Y%m%d%H%M" , time.localtime()) + str(int(time.strftime("%S" , time.localtime()))/10) + endname
            cvhelp.save(filename, image)
            oldoldname = oldname
            oldname = filename
            i = i + 1
            time.sleep(sleep)




if __name__ == '__main__':
    obj = MakeColor()
    obj.make()