#!/usr/bin/python
# -*- coding: UTF-8 -*-


class Base :
    def __init__(self):
        out("Base init")
    # 动态个数参数  
    def out(self, arg1, *vartuple ) :  
       print( arg1 )
       for var in vartuple:
          print( var )
       return;
class People :
    age = 19
    def __init__(self):
        out("Base People init")
        self.egg = 18
    def eat(self) :
        print("人总要吃饭")
    
class Student(Base, People) :   #继承
    '类说明'
    COUNT = 0   #公有静态变量?
    __privateName = "private" #私有
    #构造函数 析构函数 self必带 
    def __init__(self, name):
        self.name = name 
        Student.COUNT += 1 
        print(self)
        print(self.__class__) 
    def __del__(self):
        class_name = self.__class__.__name__
        print (class_name, "销毁")
 
    def show(self):
        self.eat()
        self.out("age:", self.age, People.age)
        self.out("name:", self.name)
        self.out("private全局变量:", Student.__privateName, self.__privateName)
        
        print ("Total Student %d" % Student.COUNT)

stu = Student("walker")
stu1 = Student("walker1")
stu2 = Student("walker2")
stu.show()
stu.out("out-of-ff")
del stu



"""
#del emp1.age  # 删除 'age' 属性
#你也可以使用以下函数的方式来访问属性：
#getattr(obj, name[, default]) : 访问对象的属性。
#hasattr(obj,name) : 检查是否存在一个属性。
#setattr(obj,name,value) : 设置一个属性。如果属性不存在，会创建一个新属性。
#delattr(obj, name) : 删除属性。
Python内置类属性
__dict__ : 类的属性（包含一个字典，由类的数据属性组成）
__doc__ :类的文档字符串
__name__: 类名
__module__: 类定义所在的模块（类的全名是'__main__.className'，如果类位于一个导入模块mymod中，那么className.__module__ 等于 mymod）
__bases__ : 类的所有父类构成元素（包含了一个由所有父类组成的元组）


类的私有属性
__private_attrs：两个下划线开头，声明该属性为私有，不能在类的外部被使用或直接访问。在类内部的方法中使用时 self.__private_attrs。
类的方法
在类的内部，使用 def 关键字可以为类定义一个方法，与一般函数定义不同，类方法必须包含参数 self,且为第一个参数
类的私有方法
__private_method：两个下划线开头，声明该方法为私有方法，不能在类地外部调用。在类的内部调用 self.__private_methods








"""
