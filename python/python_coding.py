#!/usr/bin/python
# -*- coding: UTF-8 -*-
# filename: hello.py

import sys
sys.path.append("../opencv/")
from filename import classname

print( "////////////////////////\n" )
print( "start-------------------" )
print( "Base data types Numbers[int,long,float,complex], String, List, Tuple, Dictionary" )
dir()#访问域
dir(os)

#类属性self
a = Student()
#当前方法名
print('the name of method is ## {} ##'.format(sys._getframe().f_code.co_name))
#当前类名
print('the name of class is ## {} ##'.format(self.__class__.__name__))
a.__name__
getattr(a,'__name__')
#获取类所有方法
dir(time)
sys._getframe().f_code.co_name
#检查类方法成员
ret = hasattr(obj,'func')#因为有func方法所以返回True
print(ret)
if(ret == True) :
#获取类方法l成员
ret = getattr(obj, 'func')#获取的是个对象
callable(ret) #是否可调用 函数#########################

	r = ret()
	print(r)
#反向类构建
file_name  模块名  
 module = __import__(file_name)
 AClass = getattr(module, class_name_str)()
 obj = AClass()
 obj = new.instance(AClass)

a = b = c = 1;
count, cc, str = 1, 2, "string";

#定义
word = 'word';
sentence = "this is a sentence";
paragraph = """ this is a   paragraph  """;

print( "----test string split repeat print(" )
print( sentence[0:5] * 6 + "hhh" )
tr.replace(old, new[, max])
str.replace("is", "was", 3);
#多行注释"""   '''

'a'->65
ord('a')
chr(65)
整数形式的字符串进行转
str()
int()

#数组  list ####################################
days = ['Monday', 'Tuesday', 'Wednesday',
        'Thursday', 'Friday'] ;
>>> sorted([5, 2, 3, 1, 4])
[1, 2, 3, 4, 5]
>>> student_objects = [
        Student('john', 'A', 15),
        Student('jane', 'B', 12),
        Student('dave', 'B', 10),
]
>>> sorted(student_objects, key=lambda student: student.age, reverse=True)
[('dave', 'B', 10), ('jane', 'B', 12), ('john', 'A', 15)]
>>> def numeric_compare(x, y):
        return x - y
        return cmp(x , y)
lambda x,y:x+y
cmp=lambda (x,y): cmp(x.get("name",""), y.get("name",""))
>>> sorted([5, 2, 4, 1, 3], cmp=numeric_compare)

# map  key排序
reslist = sorted(res.items(), cmp=lambda x,y: cmp(x, y)   )

# list 数组排序
# [('dd', 2), ('zk', 1)]  <- obj.items()
reslist = sorted(res, cmp=lambda x,y: cmp(x[0], y[0])   )


#字符串
name = name.strip() 去除行尾 特殊符号

截取 数组
str[0:3]
字符串匹配
str1 = "amsdflaskf1000slafj"
str1.find('1000')#可以查找出索引值  12
info=re.search(r'\d+',str1)#'\d'代表任意一个数字，'+'可以匹配数字一次或者无限次，只能匹配最前面的
re.search(r'', str).group() 分组展示字符串
'1000'  
info=re.findall(r'\d+',str1)#找到所有匹配的字符串，并把它们放到一个列表中
['1000','1200']
3、sub(pattern, from, to , count=0, flags=0)    将字符串中匹配正则表达式的部分替换为其他值
'aaaaaabbbbbcccccccc'
 re.sub(r'b+b', 'ddddd', s)
 'aaaaaadddddcccccccc'
re.split(r':| ',str6)#split用来分割字符串，':|'的意思是只要看见冒号和空格就会分割成一部分  
['imooc', 'java', 'c++', 'python', 'c#'] 
>>> str="hello boy<[www.doiido.com]>byebye"
>>> str.split("[")[1].split("]")[0]
'www.doiido.com'
>>> str.split("[")[1].split("]")[0].split(".")
['www', 'doiido', 'com']
#len(days) 获取长度
#days[0] 获取第0个元素 -1尾元素
#days.append('surday') 添加元素
#days.insert(1, 'sunday') 插入元素
#days.pop() 删除尾元素
#days.pop(2) 删除指定元素

#元组 tuple ###################################
#数据指向不变！！！！
#没有append()，insert()这样的方法。其他获取元素的方法和list是一样
#只有1个元素的tuple定义时必须加一个逗号,，来消除歧义
tupletest = ()
tup2 = (1, 2, 3, 4)

#相互转换###########
#tuple(list)
#list(tuple)

#返回多值###########
#return 1,2 #
#返回值是一个tuple！
#但是，在语法上，返回一个tuple可以省略括号，而多个变量可以同时接收一个tuple，
#按位置赋给对应的值，所以，Python的函数返回多值其实就是返回一个tuple


time = [1, 2];
print( days )
if ( 'Monday' in days):
    print('test in monday in days');
if('tu' not in days):
    print('tu not in days');

print( days[1:4] )
print( days + time )

#数据字典
print( "--test data directionary" )
dict = {};
dict['one'] = "this is one ";
dict[2] = 2;
dict2 = {'name':'Walker', 'age':18, 'dept': 'coder'};
print( dict['one'], dict[2], "   ", dict2 )
print( "keys:", )
print(  dict2.keys() )
print( " " + "values:", )
print( dict2.values() )
dict.clear() 清空
1：dict.copy：返回一个字典的浅复制
2:dict.get(key,default=None):返回指定键的值，如果值不在字典中返回default值）
3:dict.has_key(key):如果键在字典dict里返回true，否则返回false
dict.pop(key) 移除
4：dict.keys()
5:dict.items() ：以列表的形式返回遍历的键值对元组数组

#数组 长度
#遍历字典 编码utf unicode
s='林' #当程序执行时，无需加u，'林'也会被以unicode形式保存新的内存空间中,
#s可以直接encode成任意编码格式
list.clear()
s1=s.encode('utf-8')
s2=s.encode('gbk')
for i in range(len(arr)):
  arr[i]
for key in data:
        print(key+':'+data[key])
        print(type(key))

        kt = key.encode("utf-8")
        vt = data[key].encode("utf-8")


#数据类型转换
#str(object) -> string
#int(x[, base]) -> int 
strn = "100"
strn.index("0", beg=0, end=len(string)) #exception
strn.find("0", beg=0, end=len(string))  #-1
intn = 100 
if strn==intn:
    print( "strn==intn" )
elif int(strn)==intn:
    print( "int(strn)==intn" )
else :
    print( "what the ff" )

#JSON转换
# 使用 JSON 函数需要导入 json 库：import json。
# 函数  描述
string = json.dumps(obj) # 将 Python 对象编码成 JSON 字符串
obj = json.loads(string) # 将已编码的 JSON 字符串解码为 Python 对象
yaml.safe_load(list_dump)# 关于string 转obj unicode编码问题
v = obj['key']

#数学运算
a,b,c = 2, 3, 5
c=a+b;
print( 'a = 2, b = 3' )
print( 'a + b = ',  c )
c = a ** b;
print( 'a ** b = ', c )
c = b // a;
print( 'a // b = ', c )
a = 60;
b = 13;
c = a & b;
print( 'a = 0011 1100' )
print( 'b = 0000 1101' )
print( 'a & b = ', hex(c) )
print( 'a ^ b = ', a^b )

print( 'is 用于判断两个变量引用对象是否相同 == 判断两个变量值是否相等' )
return map[name_value] if map.has_key(name_value) else '' #3目运算

#循环
print( '---- while for ---------' )
arr = [1, 2, 3, 4, 5, 6];
even = [];
odd = [];
print( 'arr=',  arr )
while (len(arr) > 0 ):
    num = arr.pop();
    if(num % 2 == 0) :
        even.append(num);
    else :
        odd.append(num);
else :
  print( 'while else' )
arr=odd.extend(even)  #合并
arr = range(10);
print( 'even=', even )
print( 'odd =', odd )
print( 'for ai in arr : for ll in "python" ' )
for ai in arr :
    print( ai,'-', )
print(  )
for ll in 'Python' :
    print( ll,"-", )
else :
  print( 'for else' )
  
print( 'range make a sequence ', range(len(arr)) )
print( range(10) )


#时间格式化
import time
# 格式化成2016-03-20 11:45:39形式
print( time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())  )
# 格式化成Sat Mar 28 22:24:24 2016形式
print( time.strftime("%a %b %d %H:%M:%S %Y", time.localtime())  )
# 将格式字符串转换为时间戳
a = "Sat Mar 28 22:24:24 2016"
print( time.mktime(time.strptime(a,"%a %b %d %H:%M:%S %Y")) )
timestamp = time.mktime(time.strftime("%a %b %d %H:%M:%S %Y", time.localtime()))
# 获取当前时间时间戳
int(time.time()*1000)

import calendar
cal = calendar.month(2016, 1)
print( "以下输出2016年1月份的日历:" )
print( cal )

"""
%y 两位数的年份表示（00-99）
%Y 四位数的年份表示（000-9999）
%m 月份（01-12）
%d 月内中的一天（0-31）
%H 24小时制小时数（0-23）
%I 12小时制小时数（01-12）
%M 分钟数（00=59）
%S 秒（00-59）
%a 本地简化星期名称
%A 本地完整星期名称
%b 本地简化的月份名称
%B 本地完整的月份名称
%c 本地相应的日期表示和时间表示
%j 年内的一天（001-366）
%p 本地A.M.或P.M.的等价符
%U 一年中的星期数（00-53）星期天为星期的开始
%w 星期（0-6），星期天为星期的开始
%W 一年中的星期数（00-53）星期一为星期的开始
%x 本地相应的日期表示
%X 本地相应的时间表示
%Z 当前时区的名称
%% %号本身
"""

############################################
#函数
#可写函数说明 用参数名匹配参数值 默认值
def printme( str , age = 35 ):
   print( "打印任何传入的字符串,", str )
   return;
 
#调用print(me函数 )
printme( str = "My string");
#############################################
#装饰器 环绕执行
def deco(func):
    def wrapper(): #无参
    def wrapper(a, b):#定参
    def wrapper(*args, **kwargs):#带有不定参数的装饰器
    
        startTime = time.time()
        func()
        endTime = time.time()
        msecs = (endTime - startTime)*1000
        print("time is %d ms" %msecs)
    return wrapper
@deco12
@deco
def functionName():
    print("hello")
    time.sleep(1)
    print("world")

#######################################
#单例模式
#1.python的模块就是天然的单例模式，因为模块在第一次导入时，会生成.pyc文件，当第二次导入时，就会直接加载.pyc文件，而不会再次执行模块代码
# mysingle.py
class MySingle:
　　def foo(self):
　　　　pass

sinleton = MySingle()

#将上面的代码保存在文件mysingle.py中，然后这样使用：
from mysingle import sinleton
singleton.foo()

#2.
class ClassName(object):
    def __new__(cls):
        # 关键在于这，每一次实例化的时候，我们都只会返回这同一个instance对象
        if not hasattr(cls, 'instance'):
            cls.instance = super(ClassName, cls).__new__(cls)
        return cls.instance

#3.装饰器
def singleton(cls):
    instances = {}
    def getinstance(*args,**kwargs):
        if cls not in instances:
            instances[cls] = cls(*args,**kwargs)
        return instances[cls]
    return getinstance
    
@singleton
class MyClass:
    a = 1

##########################################
#全局变量
globvar = 1;
# 动态个数参数   元组()
def info(arg1, *vartuple ) :
   global globvar    # 使用 global 声明全局变量
   print( "输出: " )
   print( arg1 )
   for var in vartuple:
      print( var )
   return;
#第二种动态参数 **a 两个星号，必须有一个key，一个vlue
def f(**a):
  print(a,type(a))
  f(k1=123,k2='gyc')

# 调用print(info 函数 )
print(info( 10 ) )
print(info( 70, 60, 50 ) )

# 可写函数说明 匿名函数
sum = lambda arg1, arg2: arg1 + arg2;

"""
import support
# 现在可以调用模块里包含的函数了
support.print(_func("Runoob") )
import fibonacci
#要导入模块 fib 的 fibonacci 函数，使用如下语句：
from fib import fibonacci
#这个声明不会把整个 fib 模块导入到当前的命名空间中，它只会将 fib 里的 fibonacci 单个引入到执行这个声明的模块的全局符号表。
#把一个模块的所有内容全都导入到当前的命名空间也是可行的，只需使用如下声明：
from modname import *
from <filename> import <classname>

import template
te = template.Template

from template import *
te = Template

导入一个模块，Python 解析器对模块位置的搜索顺序是：
1、当前目录
2、如果不在当前目录，Python 则搜索在 shell 变量 PYTHONPATH 下的每个目录。
3、如果都找不到，Python会察看默认路径。UNIX下，默认路径一般为/usr/local/lib/python/。

1.如果导入的模块和主程序在同个目录下，直接import就行了

2.如果导入的模块是在主程序所在目录的子目录下，可以在子目录中增加一个空白的__init__.py文件，该文件使得python解释器将子目录整个也当成一个模块，然后直接通过“import 子目录.模块”导入即可。

3.如果导入的模块是在主程序所在目录的父目录下，则要通过修改path来解决，有两种方法：

(1)通过”import sys，sys.path.append('父目录的路径')“来改变，这种方法属于一次性的，只对当前的python解释器进程有效，关掉python重启后就失效了。

(2)直接修改环境变量：在windows中是 “ set 变量=‘路径’  ” 例如：set PYTHONPATH=‘C:\test\...’ 查看是否设置成功用echo %PYTHONPATH%,而且进到python解释器中查看sys.path,会发现已经有了新增加的路径了。这　种方式是永久的，一次设置以后一直都有效。在linux中是 "export 变量=‘路径’ “，查看是" echo $变量 "

通过修改path是通用的方法，因为python解释器就是通过sys.path去一个地方一个地方的寻找模块的。

"""
# 打印模块 所有函数和变量
import math
content = dir(math)
print( content )
"""
globals() 和 locals() 函数
根据调用地方的不同，globals() 和 locals() 函数可被用来返回全局和局部命名空间里的名字。
如果在函数内部调用 locals()，返回的是所有能在该函数里访问的命名。
如果在函数内部调用 globals()，返回的是所有在该函数里能访问的全局名字。
两个函数的返回类型都是字典。所以名字们能用 keys() 函数摘取。

当一个模块被导入到一个脚本，模块顶层部分的代码只会被执行一次。
因此，如果你想重新执行模块里顶层部分的代码，可以用 reload() 函数。该函数会重新导入之前导入过的模块。语法如下：
reload(module_name)

input([prompt]) 函数和 raw_input([prompt]) 函数基本类似，但是 input 可以接收一个Python表达式作为输入，并将运算结果返回。
"""

#文件处理
"""
# 打开一个文件
fo = open("foo.txt", "wb")
print( "文件名: ", fo.name )
print( "是否已关闭 : ", fo.closed )
print( "访问模式 : ", fo.mode )
print( "末尾是否强制加空格 : ", fo.softspace )

str = fo.read(10);
print( "读取的是 : ", str )

# 查找当前位置
position = fo.tell();
print( "当前文件位置 : ", position )
 
# 把指针再次重新定位到文件开头
position = fo.seek(0, 0);

fo.write( "www.runoob.com!\nVery good site!\n");

fo.close();
#以上实例输出结果：
##文件名:  foo.txt
##是否已关闭 :  False
#访问模式 :  wb
#末尾是否强制加空格 :  0
"""
行读取文件 
with open('music.txt', 'r') as f:  
    data = f.readlines()  #txt中所有读入data  
    
    if(count == -1):
        count = tool.getRandom(0, len(data))
    else:
        while(True):
            temp = tool.getRandom(0, len(data))
            if(temp != count):
                count = temp
                break
    name = data[count]
    name = name.strip()
"""
import os
# 重命名文件test1.txt到test2.txt。
os.rename( "test1.txt", "test2.txt" )
os.remove(file_name)
os.mkdir("newdir")
os.rmdir('dirname')
# 将当前目录改为"/home/newdir"
os.chdir("/home/newdir")
#getcwd()方法显示当前的工作目录。
os.getcwd()
"""

#异常处理
"""
#抛出异常
raise Exception("Invalid level!", level)
        
try:
<语句>        #运行别的代码
except <名字>：
<语句>        #如果在try部份引发了'name'异常
except <名字>，<数据>:
<语句>        #如果引发了'name'异常，获得附加的数据
else:
<语句>        #如果没有异常发生
try:
    return int(var)
except ValueError, Argument:
    print( "参数没有包含数字\n", Argument )
except Exception as e:
    print( '' )
else :
    print( '' )
"""

import sys;
x = ''''----test sys.stdout.write'''
sys.stdout.write(x + '\n');








# 输入 循环 随机数 猜数游戏
print( '----输入 循环 随机数 猜大小游戏' )
import random
m = -1;
s = int(random.uniform(1, 10));
while (m != s) :
  m = int ( input('input a unmber:'));
  if(m > s) :
    print('bigger');
  elif(m < s) :
    print('smaller');
  else :
    print('you win');
    break;





raw_input("\n\n Press the enter key to exit.");
print( "\nend----------------------" )
print( "////////////////////////" )






import threading
import time
 
class myThread (threading.Thread):
    def __init__(self, threadID, name, counter):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name
        self.counter = counter
    def run(self):
        print "Starting " + self.name
       # 获得锁，成功获得锁定后返回True
       # 可选的timeout参数不填时将一直阻塞直到获得锁定
       # 否则超时后将返回False
        threadLock.acquire()
        print_time(self.name, self.counter, 3)
        # 释放锁
        threadLock.release()
 
def print_time(threadName, delay, counter):
    while counter:
        time.sleep(delay)
        print "%s: %s" % (threadName, time.ctime(time.time()))
        counter -= 1
 
threadLock = threading.Lock()
threads = []
 
# 创建新线程
thread1 = myThread(1, "Thread-1", 1)
thread2 = myThread(2, "Thread-2", 2)
 
# 开启新线程
thread1.start()
thread2.start()
 
# 添加线程到线程列表
threads.append(thread1)
threads.append(thread2)
 
# 等待所有线程完成
for t in threads:
    t.join()








import binascii  
import struct  
print('整数之间的进制转换:')  
print("10进制转16进制", end=': ');example("hex(16)")  
print("16进制转10进制", end=': ');example("int('0x10', 16)")  
print("类似的还有oct()， bin()")  

print('\n-------------------\n')  

print('字符串转整数:')  
print("10进制字符串", end=": ");example("int('10')")  
print("16进制字符串", end=": ");example("int('10', 16)")  
print("16进制字符串", end=": ");example("int('0x10', 16)")  

print('\n-------------------\n')  

print('字节串转整数:')  
print("转义为short型整数", end=": ");example(r"struct.unpack('<hh', bytes(b'\x01\x00\x00\x00'))")  
print("转义为long型整数", end=": ");example(r"struct.unpack('<L', bytes(b'\x01\x00\x00\x00'))")  

print('\n-------------------\n')  

print('整数转字节串:')  
print("转为两个字节", end=": ");example("struct.pack('<HH', 1,2)")  
print("转为四个字节", end=": ");example("struct.pack('<LL', 1,2)")  

print('\n-------------------\n')  

print('字符串转字节串:')  
print('字符串编码为字节码', end=": ");example(r"'12abc'.encode('ascii')")  
print('数字或字符数组', end=": ");example(r"bytes([1,2, ord('1'),ord('2')])")  
print('16进制字符串', end=': ');example(r"bytes().fromhex('010210')")  
print('16进制字符串', end=': ');example(r"bytes(map(ord, '\x01\x02\x31\x32'))")  
print('16进制数组', end =': ');example(r'bytes([0x01,0x02,0x31,0x32])')  

print('\n-------------------\n')  

print('字节串转字符串:')  
print('字节码解码为字符串', end=": ");example(r"bytes(b'\x31\x32\x61\x62').decode('ascii')")  
print('字节串转16进制表示,夹带ascii', end=": ");example(r"str(bytes(b'\x01\x0212'))[2:-1]")  
print('字节串转16进制表示,固定两个字符表示', end=": ");example(r"str(binascii.b2a_hex(b'\x01\x0212'))[2:-1]")  
print('字节串转16进制数组', end=": ");example(r"[hex(x) for x in bytes(b'\x01\x0212')]")  






