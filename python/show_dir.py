#!/usr/bin/python
# -*- coding: UTF-8 -*-
# filename:

#urllib to control the web html
#import urllib.request
import re
import sys,os
import time
from sys import argv


"""
Show the dir ls ll level 
"""
def file(dir, level=998) :
    print("-----------------------------")
    dir = os.path.abspath('.') + "/" + dir
    print("Show file: " + dir + "    level: " + str(level))

    #files = os.popen('ls -l ' + dir).readlines()
    #for ff in files :
    #    #print (ff,) 
    #    sys.stdout.write(ff)
    baseLevel = getLevel(dir)
    print("-----------------------------")
    for parent, dirnames, filenames in os.walk(dir):  
# 三个参数：分别返回1.父目录 2.所有文件夹名字（不含路径） 3.所有文件名字
        if getLevel(parent) - baseLevel >= level :
            print( parent + "\t\t##dirs:" + str(len(dirnames)) + " files:" + str(len(filenames)) )
            continue
        else :
            print(parent)
        #print(" dirs:")
        #for dirname in dirnames:  # 输出文件夹信息 
        #    print (" " + dirname)
        #print(" files:")
        
            
        for filename in filenames:  # 输出文件信息  
            filepath = os.path.join(parent, filename)
            
            # 输出文件路径信息
            pr(parent, filename)

    print("-----------------------------")
    #print(os. system('ll ' + dir))

    return
def getLevel(path):
    res = 0
    strs = path.split("/")
    name = strs[-1]
    res = len(strs)
    #print("path:" + str(path) + " res:" + str(res) )
    return res
def pr(parent, filename):
    #lev = getLevel(parent)
    for i in range(len(parent)) :
        #print(" ",)
        sys.stdout.write(" ")
    #sys.stdout.write("/" + filename);
    filepath = os.path.join(parent, filename)
    filesize = os.path.getsize(filepath)
    print(filename + "\t@size=" + str(calSize(filesize)))

    return

def calSize(len) :
    gb = len / (1024 * 1024 * 1024) #GB 
    mb = len % (1024 * 1024 * 1024) / (1024 * 1024) #MB
    kb = len % (1024 * 1024 * 1024) % (1024 * 1024) / 1024 #KB
    b  = len % (1024 * 1024 * 1024) % (1024 * 1024) % 1024 #B
    if gb > 0:
        res = str(gb) + "." + str(mb / 100) + "GB"
    elif mb > 0:
        res = str(mb) + "." + str(kb / 100) + "MB"
    elif kb > 0:
        res = str(kb) + "." + str(b / 100) + "KB"
    else :
        res = str(b) + "B"
    #print("" + str(len) + "->" + res)
    return res

def main() :
    print("len(argv)=" , len(argv), "argv=", argv)
    if( len(argv) <= 1 ):
        print('usage: python ll.py <dir | file> <level=3>')
        sys.exit(1)
    else:
        if( len(argv) > 2 ):
            file(argv[1], int(argv[2]))
        else:
            file(argv[1])

    return



################################## 
main()
sys.exit(0)






