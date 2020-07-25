

环形链检测问题
	快慢指针
	时钟
	
	
拜占庭将军问题
	分布式容错选举问题
	
	







红黑树的5个性质：

1.每个结点要么是红的要么是黑的。
2.根结点是黑的。
3.每个叶结点（叶结点即指树尾端NIL指针或NULL结点）都是黑的。
4.如果一个结点是红的，那么它的两个儿子都是黑的。
5. 对于任意结点而言，其到叶结点树尾端NIL指针的每条路径都包含相同数目的黑结点。

b+树???


平衡二分查找



java内置注解

@Override

覆盖父类方法

@Deprecated(不赞成)

用于方法，表明方法已过期，不建议使用

@Suppvisewarning 

忽略警告，例如当我们要使用已过时方法，有的编译器会出现警告，

@Suppvisewarning（"deprecation"）表示忽略此警告



@Target
声明注解用在什么地方 ElementType.CONSTRUCTOR 用于构造器  ElementType.FIELD 用于成员属性 ElementType.LOCAL_VARIABLE 局部变量 ElementType.METHOD 方法   
@Rentention
注解信息保留到什么时候 RententionPolicy.SOURCE 只在源代码中保留，编译阶段抛弃 RententionPolicy.CLASS 只保留到编译阶段(CLASS文件)，VM中运行时抛弃 RententionPolicy.RUNTIME 运行时也保留，可通过反射机制获取注解信息
@Document
注解将被包含至javadoc中
备注: javadoc是Sun公司提供的一种技术，能从源代码中抽取类、方法、成员、注释等生成一个和源代码配套的API帮助文档
指令: javadoc xxx.java
 
@Inherited 
子类可继承父类的此种注解（如果父类有的话） 
Spring bean加载优先注解 
@Ordered


transient关键字修饰之后呢？
静态变量是不会被序列化的
实现Serilizable接口，将不需要序列化的属性前添加关键字transient，序列化对象的时候，这个属性就不会序列化到指定的目的地中




