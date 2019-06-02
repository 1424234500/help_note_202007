#!/usr/bin/python
# -*- coding: UTF-8 -*-
# filename:

#urllib模块提供了读取Web页面数据的接口
import urllib.request
#re模块主要包含了正则表达式
import re
import sys
import time


#定义一个getHtml()函数
def get_Html(url):
    page = urllib.request.urlopen(url)  # urllib.urlopen()方法用于打开一个URL地址
    html = page.read()  # read()方法用于读取URL上的数据,返回的是byte
    # print(type(html))
    html = html.decode('utf-8')
    with open("file", 'w',encoding='utf-8') as new:# 将html保存为file文件
        new.write(html)
    return html




oldpercent = 0
def cbk(a, b, c):
    '''回调函数
    @a: 已经下载的数据块
    @b: 数据块的大小
    @c: 远程文件的大小
    '''
    global  oldpercent
    per = 100.0 * a * b / c
    if oldpercent <= 0 :
        sys.stdout.write('#')
        sys.stdout.flush()
    if per >= 100:
        per = 100
        print('#')
        oldpercent = 0
    else:
        newpercent = int(per) // 5
        if newpercent > oldpercent :
            for i in range(newpercent - oldpercent) :
                #sys.stdout.write('%.0f%% ' % per)
                sys.stdout.write('=')
                sys.stdout.flush()
            oldpercent=newpercent


def get_Image(html):
    reg = r'data-original="(http.*?.jpg)"'# 正则表达式，得到图片地址
    #匹配data-original="http://img95.699pic.com/photo/50013/7645.jpg_wh300.jpg"
    print(reg)
    imgre = re.compile(reg)     # re.compile() 可以把正则表达式编译成一个正则表达式对象.
    imglist = re.findall(imgre, html)      # re.findall() 方法读取html 中包含 imgre（正则表达式）的数据
    x = 0
    for imgurl in imglist:
        #把筛选的图片地址通过for循环遍历并保存到本地
        local = 'F:\py\download\%s.jpg' % x
        print('下载' + imgurl + ' -> ' + local)
        urllib.request.urlretrieve(imgurl,local, cbk)
        #核心是urllib.urlretrieve()方法,直接将远程数据下载到本地，图片通过x依次递增命名
        x += 1
    return imglist

def get_URL(html,reg):
    print("匹配",html," 正则",reg)

    html = get_Html("http://699pic.com/zhuanti/hangpai.html")

    imgre = re.compile(reg)     # re.compile() 可以把正则表达式编译成一个正则表达式对象.
    imglist = re.findall(imgre, html)      # re.findall() 方法读取html 中包含 imgre（正则表达式）的数据
    x = 0

    for imgurl in imglist:
        print(imgurl)
       # print('下载' + imgurl + ' -> ' + local)
       # urllib.request.urlretrieve(imgurl,local, cbk)
        #核心是urllib.urlretrieve()方法,直接将远程数据下载到本地，图片通过x依次递增命名
        x += 1
    print("匹配结束")

    return imglist



html =  "http://699pic.com/zhuanti/hangpai.html"
#reg = r'data-original="(http.*?.jpg)"'# 正则表达式，得到图片地址
#list = get_Image()
#m = re.match(r'hello', 'hello world!')

#reg = r'data-original="((http)|(https).*)"'# 正则表达式，得到图片地址
#reg = r'<tr>(.*?)</tr>'
reg = r"(?<=href=\").+?(?=\")|(?<=href=\').+?(?=\')"

list = get_URL(html, reg)

for l in list :
    print(l)





