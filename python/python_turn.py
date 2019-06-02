#!/usr/bin/python
#!/usr/bin/python
# -*- coding: UTF-8 -*-
# filename: 

import re
import os
import sys
import time
from sys import argv


def showList(list):
    #print(list)
    for i in range(len(list)):
    	sys.stdout(list[i])
    return

def fixPrint(path) :
    keyword = "print" 
    tokeyword = "print("
    newLines = []
    file = open(path,"r")
    all_the_text = file.readlines( )
    for line in all_the_text:
        index = line.find(keyword)
        #检查当前行是否有print 同时是否已经有()了
        if(index>=0 and line[index+len(keyword):index+8].find('(')==-1):
            #对有print的数据进行处理,
            line = line.replace(keyword,tokeyword) 
            line = line.replace(";", "")
            if(line.find("\n")>0):
                line =  line.replace("\n"," )" +"\n") 
            else:
                line+=")"
        newLines.append(line)
    file.close()

     #直接覆盖掉原来的文件 
    newFile = open(path,"w")
    for line in newLines:
      	newFile.write(line)
    newFile.close()
    return 

def main() :
    print("len(argv)=" , len(argv), "argv=", argv)
    if( len(argv) <= 0 ):
        print('usage: python ll.py <dir | file> ')
        sys.exit(1)
    else: 
    	fixPrint(argv[1])
    return

################################## 
main()
sys.exit(0)