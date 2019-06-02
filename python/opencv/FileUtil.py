#!/usr/bin/python
#-*- coding:utf-8 -*-  

import os 
import re
import sys
import time
from sys import argv


"""文件工具类"""
class FileUtil:

    """
    获取某目录下的所有文件名 及其子目录名 及其子文件名 
        params: 需要列表的文件夹
        return: 文件集合 所属文件夹序号集合 文件夹集合dirs  (files, counts, dirs)
    """
    def getSamplesLabelsDirnames(self, dir, withFilePath=True, withDirPath=False) :
        files = []
        counts = []
        dirs = []
        count = 0

        root = dir
        ind = dir.find("/") + 1
        if(ind >= 1):
            root = dir[ind:]
        dir = os.path.abspath('.') + "/" + dir
        length = len(dir) + 1
        # print(dir)
        # print("-----------")
        for parent, dirnames, filenames in os.walk(dir):  
        # 三个参数：分别返回1.父目录 2.所有文件夹名字（不含路径） 3.所有文件名字
            dirName = parent
            if( not withDirPath):
                if(len(parent) <= length):
                    dirName = root
                else:
                    dirName = parent[length:]
            # print(parent, dirName)
            dirs.append(dirName)
            for filename in filenames:  # 输出文件信息  
                ##输出文件路径信息
                #self.pr(parent, filename)
                if(withFilePath):
                    filename = os.path.join(parent, filename)
                files.append(filename)
                counts.append(count)
            count = count + 1
        files = tuple(files)
        counts = tuple(counts)
        dirs = tuple(dirs)
        return (files, counts, dirs)
    #递归转换 多维 -> 一维 
    def turnArray(self, dirs, args):
        if(args and (type(args) is list) ):
            for arr in args :
                self.turnArray(dirs, arr)
        else:
            if(args):
                # print('false ' + str(args))
                dirs.append(args)
        return 
    def getLevel(self, path):
        res = 0
        strs = path.split("/")
        name = strs[-1]
        res = len(strs)
        #print("path:" + str(path) + " res:" + str(res) )
        return res
    def pr(self, parent, filename):
        #lev = getLevel(parent)
        for i in range(len(parent)) :
            #print(" ",)
            sys.stdout.write(" ")
        #sys.stdout.write("/" + filename);
        filepath = os.path.join(parent, filename)
        filesize = os.path.getsize(filepath)
        print(filename + "\t@size=" + str(self.calSize(filesize)))

        return

    def calSize(self,len) :
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

 

if __name__ == '__main__':  
    fileUtil = FileUtil()
    # files, labels, dirs = fileUtil.getSamplesLabelsDirnames('number', withFilePath=False, withDirPath=False)
  
    # print(files)
    # print(labels)
    # print(dirs)

    files, labels, dirs = fileUtil.getSamplesLabelsDirnames('number/6', withFilePath=False, withDirPath=False)
  
    print(files)
    print(labels)
    print(dirs)

