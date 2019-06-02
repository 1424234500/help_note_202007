

numpy np 
矩阵 数学计算工具 


NumPy数组是一个多维数组对象，称为ndnp.array。其由两部分组成：
•实际的数据
•描述这些数据的元数据
大部分操作仅针对于元数据，而不改变底层实际的数据。
关于NumPy数组有几点必需了解的：
•NumPy数组的下标从0开始。
•同一个NumPy数组中所有元素的类型必须是相同的。



ndnp.array.ndim：数组的维数（即数组轴的个数），等于秩。最常见的为二维数组（矩阵）。
•ndnp.array.shape：数组的维度。为一个表示数组在每个维度上大小的整数元组。例如二维数组中，表示数组的“行数”和“列数”。ndnp.array.shape返回一个元组，这个元组的长度就是维度的数目，即ndim属性。
•ndnp.array.size：数组元素的总个数，等于shape属性中元组元素的乘积。
•ndnp.array.dtype：表示数组中元素类型的对象，可使用标准的Python类型创建或指定dtype。另外也可使用前一篇文章中介绍的NumPy提供的数据类型。
•ndnp.array.itemsize：数组中每个元素的字节大小。例如，一个元素类型为float64的数组itemsiz属性值为8(float64占用64个bits，每个字节长度为8，所以64/8，占用8个字节），又如，一个元素类型为complex32的数组item属性为4（32/8）。
•ndnp.array.data：包含实际数组元素的缓冲区，由于一般通过数组的索引获取元素，所以通常不需要使用这个属性。

//数组属性
arr.shape
(40,20)



//opencv img 转 numpy array
samples = np.array(samples,np.float32)

//随机数组
np.random.randint(10, size=(4, 2))  //0~10 排列成 4row 2col 二维数组
np.random.randint(10, size=3)       //一维数组 3col
np.random.random(4)      //double 0~1 随机数 4个
np.random.random(4, 2)   //double 0~1 随机数 4x2 个 4row 2col 二维数组
//数列数组
np.arange(<0,>4<,1>)


//创建数组  int float
import numpy as np
>>> a = np.array( [2,3,4] )　　　
>>> a.dtype
    dtype('int32') 
>>> b = np.array([1.2, 3.5, 5.1])　　　
>>> b.dtype
    dtype('float64')

//二维数组
>>> b = np.array( [ (1.5,2,3), (4,5,6) ] )　　 
>>> c = np.array( [ [1,2], [3,4] ], dtype=complex/int32/float64)
>>> c
    np.array([[ 1.+0.j,  2.+0.j],
　　　    [ 3.+0.j,  4.+0.j]])

//数列形式的数组: 
np.arange(<0,>4<,1>)
        [0,1,2,3]
>>> np.arange(10, 30, 5)  
    np.array([10, 15, 20, 25])  
//浮点数个数精度问题 使用此获得预期个数5
>>> np.linspace(-1, 0, 5)
        np.array([-1.  , -0.75, -0.5 , -0.25,  0.  ])
//数组规划 规格 必须完全分配 标准化矩阵
b= np.arange(0,12,1).reshape(3,4<-1>)   //copy
b.shape = (3<-1>, 4)    //self
b.resize(3, 4)  //self
a = np.floor(10*np.random.random((3,4)))
a.ravel()   //化为一维  copy

//设置强制打印所有数组
set_printoptions(threshold='nan')


//数组运算 ！元素逐个计算
a=np.arange(4) [0,1,2,3]
b=np.array(    [10,11,12,13])
c=b-a          [10,10,10,10]
d=b**2 <1/2.>        [0,1,4,9]    n次方 
e=10*np.sin(a)
f=a<35  [True,True,False...]
    //与其他矩阵语言不同，NumPy中的乘法运算符*按元素逐个计算，矩阵乘法可以使用dot函数或创建矩阵对象实现(后续章节会介绍)
a=np.array([ [1,2,3], [1,2,4] ])
b=np.array(  [1,1,1], [2,2,2] ])
c=a*b   [
            [1,2,3],
            [2,4,8],
        ]
>>> c = b.reshape(4,-1)
>>> a
array([[ 2,  2,  2,  2],
       [ 1,  1,  1,  1],
       [ 8,  9, 10, 11]])
>>> c
array([[ 2,  2,  2],
       [ 2,  1,  1],
       [ 1,  1,  8],
       [ 9, 10, 11]])
>>> np.dot(a,c)     //矩阵乘法
array([[ 28,  28,  44],
       [ 14,  14,  22],
       [143, 145, 226]])

    //操作符如+=和*=用来更改已存在数组而不创建一个新的数组。
a*= 3
b+= a
>>> a= np.ones(3, dtype=np.int32)  
>>> b= np.linspace(0,np.pi,3)  
>>> b.dtype.name  
    'float64'

//数组方法
运算将数组看作是一维线性列表
a.sum()
a.min()
a.max()
>>> b = np.arange(0,12,1).reshape(3,4)
>>> b.sum(axis=0)   # 计算每一列的和，注意理解轴的含义  
    array([12, 15, 18, 21])
>>> b.cumsum(axis=1)    # 计算每一行的累积和  
array([[ 0, 1, 3, 6],  
            [ 4, 9, 15, 22],  
            [ 8, 17, 27, 38]]) 

//数组选择器 按元素操作！！
a = np.arange(12) ** 3  //[0,1,8,27,...]
a[2:5]  //[8,27,64]     截取
a[0:6:2] = 1000 //0-6 隔一个元素 选择器 赋值 -> a[0, 2, 4, ] = 1000
a[::-1] //反转
a[-1]   //尾元素

//多维数组选择器 可赋值
a = a.reshape(3, 4)
    [[ 0  1  2  3]
     [ 4  5  6  7]
     [ 8  9 10 11]]

a[2, 3] //11
a[0:2, 1] //0-2行的1号元素 [1,5] 行号可以大于len 但列号不能
a[:, 1] //每行的1号元素
a[1:3, : ]  //1-3行的 所有元素

a[..., 3] //多维自动补齐
a[2, ..., 4,:]

//遍历 从一维度开始
for people in world:
    for properties in people:
        for event in properties :

for map in a.flat:  //元素遍历
    print map 





