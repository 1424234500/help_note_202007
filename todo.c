实际使用的项目？
功能 
    主页展示 介绍
    //数据库数据通用展示 管理 接口
    //权限管理模块 登录 角色 权限 session token  
     //   用户 - 部门 地域爬取数据
    //    角色
         
    //便捷接口在线测试swagger
    //文件管理 上传下载
    //quartze在线管理 集群模式
    //自动化打包部署问题 idea依赖
    //jpa分表插件sharding使用 联合多数源配置 
    //json格式化jackson解决
     
    模拟用户访问造数压力监控一体化 构造用户量 模拟用户  熔断限流
    推送提醒服务 在线管理
    集成dubbo monitor ？
    wiki功能
    权限 用户 管理员 分级 菜单
    12306抢票爬取 
    
面试刷题 
基础算法 lee code
//redis注册中心
kafka 替换redis队列  
熔断限流框架sentinel 
在线小工具集合  
	在线java算法演示中心
	在线各语言 shell python编辑器

Prometheus监控服务器群 


面试

 
框架实现原理 
Spring bean创建原理 ioc/aop 
Springboot 启动 
	配置 切换profile --spring.profiles.active=prod
	事务级别 
SpringMVC 介绍自实现
mybatis 动态代理proxy 

	

Jvm new对象机制 堆分配 内存回收 
	class加载机制 双亲委派父类识别优先加载，避免根类加载器jdk被串改？ 缓存机制 	

jdk差异 1.8 hashmap实现差别 红黑树 hash地址 数组链表 以对象为键 有什么问题Java排序 哪些比较器 自定义实现
	key过多阈值转换红黑树，对于实现了Comparable 接口的键(对象)，插入或删除的操作会更简单  二分红黑树查找键 而非简单hash查找键


#Java并发线程协作 volatile  锁 sync和 lock 介绍 差别 公平性  抢占资源 wait sleep   threadpool

修改场景：并发
	i++  读取 修改 写入问题
		多线程并发i++可能比预期小 cpu多核多线程脏读写
	我必须是看到数据才决定的更改，若在保存前变了，得在变了的基础上重新修改
1.保证原子性 并发 
#方案： 
	是否需要先比较再修改 
	volatile 是否满足要求
	锁
	
#原子性是否保证可见性？
	原子性不一定保证可见性。比如 CAS 只解决了比较和更新的原子性的问题，要保证可见性，需要加锁或者是用 volatile 修饰变量。 		

2.锁概念 
#乐观锁 基本没人抢 读多写少
	查询 若没变则修改 	写多时会导致总是变化 而导致重新查询后 再次尝试修改 低效
	原子类（CAS Compare And Swap实现） 多线程累加器 

#悲观锁 总会有人抢我的 写多
	加锁 查询 修改  
	for update（锁定查询的行）
	sync
	
4.final 作用 初始化 闭包? 生命周期改变 子线程可见域
5.volatile 并发关键字 不缓存 写时直接写入主存  读时直接读主存  
	有限的一些情形下使用 volatile 变量替代锁（简单 性能）  1.对变量的写操作不依赖于当前值。  2.该变量没有包含在具有其他变量的不变式中。
	可见性 : 对一个 volatile 的变量的读，总是能看到任意线程对这个变量最后的写入.
	原子性 : 对于单个 volatile 变量的读或者写具有原子性，复合操作不具有.(如 i++)
	互斥性 : 同一时刻只允许一个线程对变量进行操作.(互斥锁的特点)
	确保通过排他锁单独获得这个变量
	
	正确使用 volatile 
		模式：状态标志	仅仅是使用一个布尔状态标志，用于指示发生了一个重要的一次性事件，例如完成初始化或请求停机。
		模式：volatile bean  JavaBean 的所有数据成员都是 volatile 类型的，并且 getter 和 setter 方法必须非常普通 —— 除了获取或设置相应的属性外，不能包含任何逻辑。
6.Synchronized 悲观锁 自动释放 不能被继承 尽量减少锁区间范围   简化代码尽量使用
	非公平
	原子性：可重入 下一个CPU时间片还是只能被他自己获取到，直到所有代码执行完
	可见性：对一个 synchronized 修饰的变量解锁之前，必须先把此变量同步回主存中。
	可重入性：获得一次锁之后，如果调用其它同步方法，不需要重新获取锁，可以直接使用。
	不可中断性：一旦这个锁被某线程获得，其他线程只能等待或者阻塞。Lock 锁可以中断或者退出等待（超时机制）。
	
	对于普通同步方法，锁是当前实例 this。
	对于静态同步方法，锁是当前类 XXX.class。
	对于同步方法块，锁是 synchronized 括号里配置的对象。
	
	jse1.6 效率优化 
	锁升级	主要想要避免其他线程阻塞切换cpu上下文
	无锁状态、								多线程循环尝试获取（CAS）
	偏向锁状态、							竞争不大 减少锁操作不释放	单线程？遇到竞争才会释放锁，线程不会主动释放偏向锁		关闭偏向锁：-XX:-UseBiasedLocking=false 默认进入轻量级锁
	轻量级锁状态、							当锁是偏向锁的时候，被另外的线程所访问，偏向锁就会升级为轻量级锁，其他线程会通过自旋的形式尝试获取锁，不会阻塞，从而提高性能
	重量级锁状态							等待锁的线程都会进入阻塞状态
	随着竞争情况逐渐升级。锁可以升级但不能降级 
 
	锁对象不能为空
	作用域不宜过大
	避免死锁

7.Lock	必须finally手动释放  AbstractQueuedSynchronizer(AQS)	复杂实现 可(超时)判断 分布式锁  
代码级别的并发，需要使用锁实现提供的独特机制，例如：读写分离、分段、中断、共享、重入等 synchronized 不支持的机制。
	问题：多次重入  多次释放
	重入锁（ReentrantLock）	
		公平锁（FairSync）
		非公平锁（NonfairSync）
	读锁（ReadLock） 支持重进入的共享锁  读锁的存在意味着不允许其他写操作的存在
	写锁（WriteLock）支持重进入的排它锁 



8.ThreadPoolExecutor 
ThreadLocal  数据副本 线程切面耗时
	线程同步问题

	sleep：定时器唤醒	不释放锁
	wait： 需要在同步块里 notify随机唤醒/notifyAll唤醒所有
	park： 需要在同步块里 unpark唤醒指定
	Condition：signal随机唤醒/signalAll
	
	线程池构造 队列选择  队列容量 分工核心数评估
	拒绝策略
	线程状态

	ExecutorService工厂制造 fixed固定数量 sing单线 sch单线周期(间隔时间or固定时间)
		ThreadPoolExecutor(int corePoolSize,		//核心数
									线程池个数=CPU的数量*CPU的使用率*（1+等待时间/计算时间）
		
                              int maximumPoolSize,	//最大数
                              long keepAliveTime,	//非核心存活时间
                              TimeUnit unit,		//时间单位
                              BlockingQueue<Runnable> workQueue,	//队列实现
									SynchronousQueue  eg:  4, 100 	    直接提交队列：没有容量，每一个插入操作都要等待一个相应的删除操作。通常使用需要将maximumPoolSize的值设置很大，否则很容易触发拒绝策略。
									ArrayBlockingQueue	有界的任务队列：任务大小通过入参 int capacity决定，当填满队列后才会创建大于corePoolSize的线程。
									LinkedBlockingQueue	无界(可指定容量有界)的任务队列：线程个数最大为corePoolSize，如果任务过多，则不断扩充队列，知道内存资源耗尽。
									PriorityBlockingQueue	优先任务队列：是一个无界的特殊队列，可以控制任务执行的先后顺序，而上边几个都是先进先出的策略。 
							  
                              ThreadFactory threadFactory,			//工厂覆盖
                              RejectedExecutionHandler handler) 	//丢弃模式
																  JDK提供的线程池拒绝策略
									策略名称	描述
									AbortPolicy	该策略会直接抛出异常，阻止系统正常 工作。线程池默认为此。
									CallerRunsPolicy	只要线程池未关闭，该策略直接在调用者线程中，运行当前被丢弃的任务。
									DiscardOledestPolicy	该策略将丢弃最老的一个请求，也就是即将被执行的一个任务，并尝试重新提交当前任务。
									DiscardPolicy	该策略默默地丢弃无法处理的任务，不予任务处理。
									
									
		添加任务
			优先顺序 核心线程corePoolSize、任务队列workQueue、最大线程maximumPoolSize，如果三者都满了，使用handler处理被拒绝的任务。 		


9.Redis分布式锁 其他实现的锁 缓存穿透击穿雪崩 一致性
	缓存穿透
	缓存没有命中-数据库也没有命中-查询失败-加剧反复查询   数据库反复查询
		缓存空对象 过期时间		存储null占用空间 取舍	一段时间查询和数据库不一致 
		
	缓存击穿
	热点数据-突然失效-并发查询数据库

	缓存雪崩
	缓存宕机-大量访问导致数据库宕机
		避免宕机 redis高可用 集群主备 同城双活
		限流降级 熔断模式 成功率过低则限流 逐渐阶梯放开
		数据预热 不同过期时间 避免同时失效
#kafka

	
10.Netty IO NIO react模式 哪些插件	cpu稀疏型
	处理多个连接
	BIO 多线程阻塞等待网络流写入
	场景：
		每次有一个客户端连接进来的时候，都会有一个新的线程去处理，缺点显而易见，如果连接比较多的时候，我们就要建立大量的线程去一一处理
 		Socket socket = ServerSocket.accept();
		来一个长连接，记录句柄到list中，开一个子线程负责死循环监控读取该句柄的写入流	
		不具备弹性伸缩	线程个数和并发访问数成线性正比	性能急剧下降
	NIO 线程阻塞的方式监听 IO 事件	
		IO多路复用	避免由于频繁IO阻塞导致的线程挂起 JDK1.6版本使用epoll替代了传统的select/poll
		场景：
		Channel（通道）、Buffer（缓冲区）、Selector（选择器）
		serverSocketChannel.configureBlocking(false);
 		serverSocketChannel.register(selector, SelectionKey.OP_ACCEPT);
		一个IO线程可以并发处理N个句柄读取
		
	NIO2.0 AIO 异步非阻塞式IO		在Linux系统上，AIO的底层实现仍使用EPOLL		Netty整体架构是reactor模型, 而AIO是proactor模型
	server.accept(null, new CompletionHandler<AsynchronousSocketChannel, Object>() {

	Reactor模式
		没有Queue来做缓冲，每当一个Event输入到Service Handler之后，会立刻分发给对应的Request Handler来处理

最原始的网络编程思路就是服务器用一个while循环，不断监听端口是否有新的套接字连接，如果有，那么就调用一个处理函数(线程)处理
BIO模式

缺点在于资源要求太高，系统中创建线程是需要比较高的系统资源的，如果连接数太高，系统无法承受，而且，线程的反复创建-销毁也需要代价。
改进方法是：
采用基于事件驱动的设计，当有事件触发时，才会调用处理器进行数据处理。使用Reactor模式，对线程的数量进行控制，一个线程处理大量的事件
	
Java的NIO模式的Selector网络通讯，其实就是一个简单的Reactor模型。可以说是Reactor模型的朴素原型。
Reactor模式，是基于Java NIO的，在他的基础上，抽象出来两个组件——Reactor和Handler两个组件：
（1）Reactor：负责响应IO事件，当检测到一个新的事件，将其发送给相应的Handler去处理；新的事件包含连接建立就绪、读就绪、写就绪等。
（2）Handler:将自身（handler）与事件绑定，负责事件的处理，完成channel的读入，完成处理业务逻辑后，负责将结果写出channel。

	
11.Sql	
Sql三种连接 集合关系  
MySQL调优 哪些索引 多键索引
	引擎区别   建表 量级分表 
	联合索引 最左前缀原则  查询优化
	Innodb ：数据完整性，并发性处理，擅长更新，删除。
	myisam：高速查询及插入。擅长插入和查询
	普通索引,index：对关键字没有要求。
	唯一索引,unique index：要求关键字不能重复。同时增加唯一约束。
	主键索引,primary key：要求关键字不能重复，也不能为NULL。同时增加主键约束。
	全文索引,fulltext key：关键字的来源不是所有字段的数据，而是从字段中提取的特别关键词
	执行计划explan f5 *具体字段 where子查询减少 优先筛选少行 EXISTS  对索引列使用OR无效 
	awr报告
	




准备

dubbo 设计框架 负载均衡 spi机制 zk选举 分布式锁 

redis aof、rdb、rewire 主从 cluster 基本类型 set zset list hash string 
expire ttl 
缓存击穿 穿透 雪崩 数据一致性，一致性hash，布隆过滤器

mysql 事务、锁、索引、b+树，主从

mq，rocketmq
	为什么用
	重复消费，顺序消息，事务消息，高可用，消息丢失，挤压场景
	
netty，零拷贝，bio，nio，aio，架构设计

算法，快速排序，堆排序，二叉树，链表反转，成环，环节点，跳楼梯
	双指针，dp，递归，手写红黑树？

网络，http,tcp,https,udp,7层网络协议

分布式事务实现，架构，
	抢红包
	，高并发下单



题0
sync底层实现，锁优化，lock对比
jvm调优详细，如何设置，好处，gc分析
redis数据结构，场景，微博场景如何设计用户关系
线程池设定 为什么
spring如何循环依赖，为什么三级缓存
优先级队列原理

项目如何设计 漏洞解决 改进 挂了？ 扩容？
高并发下单减少库存如何设计
rocketmq架构方向设计
dubbo框架原理
最近读了什么书  如何学习

项目为何这样设计，如何优化，合理更好的方式优化，数据库设计
公司做啥了，绩效如何，手写算法链表反转

jvm，sms过程，full gc做啥了
所了解的所有中间件？

为什么来，以前为什么不来，毕业到现在有什么改变





题1
b和b+树
排序算法 思想 时间复杂度 空间复杂度
两数之和三数和

tcp三次 四次 区别 为什么 
tcp udp区别
tcp粘包拆包
保持连接

并发 死锁条件 如何避免
线程状态 如何转换
linux常用指令

数据库范式 如何应用 取舍
数据库索引 底层实现mysql
mysql引擎innodb myisam区别场景
数据库事务 隔离级别
sql优化思路
外键 注意
设计数据库表 时间空间 冗余

类和对象
static final区别
synchronized 底层实现 其他锁 reentrantLock
	实现单缓冲区的生产消费模型

bio nio aio netty
接口 抽象类区别
hashmap hashtable hashset 如何去重 hash规则
concurrentHashmap 为什么安全
数字和字符串相互转换
线程状态 线程方法 join yield
线程池 如何创建 各个参数
jvm参数 xms xmx
设计模式 单例几种写法 策略设计模式  


springmvc原理 哪些设计模式
spring 依赖注入的几种方式 注解 xml配置 
spring哪些框架组件 分别做什么
	 动态代理原理
	 事务实现原理
spring bean创建过程 生命周期 循环依赖 父子容器
springboot和springmvc区别联系
	启动流程 如何实现的自动配置













消息服务器架构
    10台 经过代理 每台保持用户连接 
    每台收到数据后 处理业务 
    中转队列广播到每台 发布订阅 1->N 
    10台 每台接收后都做分发给各自的用户

树形路由节点广播模式 单用户登录 同用户多端使用帐号后缀方式
以ip段位分区 0,256  0,4
路由表 本地广播 向上传递
                                                           lv0
       
                            lv1.0                                                       lv1.1
        
    lv1.0.0[0,3]   lv1.0.1[4,7]     lv1.0.3[8,11]   lv1.0.4[12,15]      lv1.1.0[16,19]       lv1.1.1[20,23]
    
java UnSafe 类 


订阅模型
/*redis 订阅发布模式*/
/*redis 队列共享数据*/
分布式存储/并发/服务化 横向扩容
压力测试性能

限流
队列 延时 
代理时url限制
接口访问次数控制
数据库连接数 连接池

/*jvm gc核心日志 核心监控 调优 dump*/
/*jstack */

/////////////////////////////////////////////////////
//多数据源 
//mysql oracle 分表案例 分表插件sharding
////////////////////////////////////////////////////
////////////////////////////
/*java core 导出 分析*/

路由层
1.  基于 spirng 路由功能
2.  支持 http协议中 GET/POST/DELTE/PUT等方法
3.  支持REST风格请求及普通http请求
控制器层
1.  支持Controller及RestController
2.  请求参数形式多样化
3.  参数格式统一转换为json
业务逻辑层
1.  接收json格式数据，处理业务逻辑，调用数据访问层。
数据访问层
2.  业务逻辑持久化数据的中间层。调用数据库或文件系统
持久化层
1.基于MyBatis持久化框架
2.结合sharding-jdbc分表分库
3.支持多数据库


 
//后台开发学习//////////////////////////////////////////////////////////////////////////////////

//Java学习----------------------------------看书 Thinking in Java---------------------
//thread 并发 同步锁 几种方式
//看书 通读 详细  
//ThreadLocal Context上下文 全局变量 
//线程池 - 单/多线程池队列 -> 高并发 - 定时任务调度《队列 生产者 消费者模型》
//进程通信 远程调用RPC 共享内存IPC
//classloader 注入原理 工具


掌握JVM内存分配、JVM垃圾回收；类装载机制； 性能优化； 反射机制；多线程；IO/NIO； 网络编程；常用数据结构和相关算法
动态代理
锁


《深入理解计算机系统》，《tcp/ip详解 卷一、二、三》，《数据结构与算法》

了解分布式、缓存、消息、搜索
jvm 原理 调优
Java IO nio 多线程
分布式SOA服务框架：Dubbo、zookeeper、Proxy、RestFul
// rpc rmi
// Redis、ehcache
设计模式
Sql优化理论
// Spring、SpringMVC、iBatis
分布式 多线程 高性能 大数据-高并发经验

//部分源码解析博客 netty sort springMVC 注解
//数据库MongloDB







二、中级工程师

1、对于Java基础技术体系（包括JVM、类装载机制、多线程并发、IO、网络）有一定的掌握和应用经验。

掌握JVM内存分配、JVM垃圾回收；类装载机制； 性能优化； 反射机制；多线程；IO/NIO； 网络编程；常用数据结构和相关算法。

2、对面向对象的软件开发思想有清晰的认识、熟悉掌握常用的设计模式；设计模式；单例模式；工厂模式；代理模式；模板方法模式；责任链模式等。

3、熟练掌握目前流行开源框架(spring/springmvc/ibatis)，并且对其核心思想、实现原理有一定认知；开源框架：spring；hibernate。

4、熟悉Oracle、MySQL等数据库开发与设计以及缓存系统Redis或 Memcached的设计和研发；关系数据库：oracle；PostgreSQL  缓存系统：Redis（Nosql）缓存系统：Memcached。

5、熟悉底层中间件、分布式技术（包括缓存、消息系统、热部署、JMX等）、底层中间件：应用服务器：Jetty(Tomcat)、 消息中间件：ActiveMQ、RabbitMQ、事务处理中间件：数据访问中间件：ODBC、工作流中间件：JBPM，分布式技术：缓存系统、消息系统、Restful、热部署、JMX。

6、至少一种Java 应用服务器如tomcat、Jetty。

7、精通shell编程，熟练应用awk、sed、grep、strace、tcudump、gdb等常用命令。

8、有大型分布式、高并发、高负载（大数据量）、高可用性系统设计开发经验，分布式：（多节点部署）、高并发、高负载（大数据量）、高稳定、高可用。

9、对配置管理和敏捷研发模式有所了解，配置管理工具：SVN、Github。

10、业务能力：系统升级、双机、部署、容灾、备份恢复、DFX。

11、加分技术：脚本语言：Python，远程调用，精通Internet基本协议（如TCP/IP、HTTP等）内容及相关应用。有一定安全意识并了解常见的安全问题解决方案。熟悉常见的一些解决方案及其原理：单点登录、分布式缓存、SOA、全文检索、消息中间件，负载均衡、连接池、nosql、流计算等。

三、高级工程师

1、JAVA。要想成为JAVA（高级）工程师肯定要学习JAVA。一般的程序员或许只需知道一些JAVA的语法结构就可以应付了。但要





-----------框架集成 框架自实现封装-----------------
SOA服务框架：Dubbo、zookeeper、Proxy、RestFul
缓存：Redis、ehcache
分布式消息中间件：KafKa+Flume+ZookeeperKeepalived+Nginx+Proxy
负载分布式文件：FastDFS
SSO框架：CAS单点登录
模块化管理：Maven
数据库连接池：Alibaba Druid
核心框架：Spring framework
安全框架：Apache Shiro
视图框架：Spring MVC
富文本：CKEcitor
动态页签：Jerichotab、对话框：jQuery jBox
树结构控件：jQuery zTree报表：Echarts、JasperReports
服务端验证：Hibernate Validator
布局框架：SiteMesh
工作流引擎：Activiti 5.15
任务调度：quartz 1.8.5
持久层框架：MyBatis
日志管理：SLF4J 1.7、Log4j
前端框架：Bootstrap 4 metronic
客户端验证：JQuery Validation





//接口----------------
百度文本语音转换
京东Alpha人工智能接口



//项目开发-----------------
nginx文件服务器

多服务器 启动-关闭-日志-监控 批量统一配置管理系统
AServer:
    ssh登录
    start shell http start 
    stop shell  kill pid
    log         cat log.file


//第三方推送平台服务器
//设计跳板机 socket 路由表 路由器


//TCP/IP socket/应用层协议/mqtt/http/自己的协议@
Android 进程 jni 从底层向上 模拟系统信息 工具连点器
Android 设备控制器 - 设备socket - socketServer<net> - 终端socket
设备端 socket适配管理



//Linux-------------------------------------
Shell多进程 管道 同步 队列 生产者 消费者 进程通信
内核驱动编写test


//设备-------------------------------------------------------------------------------------------------
$外形造型设计
$图像流处理 传输
3d打印机
外观 组件 设计 结合传感器 和 输出 设备 ////////////////////////// 


    pi端
    
结合python opencv rtmp模块 树莓派摄像头 推送直播 监控系统
           简易识别物体 保存照片 并 推送消息

//实时监控视频有困难 延时 帧率 图像处理cpu压力  传输带宽 速度 
解决方案：
    自定义压缩 灰度图 缩小 压缩字节 socket传输 自定义解码显示层    

    
    手机端
        http访问静态 图片资源
        socket交互控制系统 并 获取推送 并 去主动获取高质量关键图片 获取系统环境监控信息并展示
        rtmp直播地址监控
        
红外 避障 测距 模块实现
自移动 地图探测 推送远程地图识别

//输入
--监控 输入
指令 控制 端口 
指令 控制 行为 <移动 组合开关>

--自发输入 传感器检测 状态 监控 
自学习地图探测生成

录像 ////
录音 ////

光
声音
湿度
烟雾
红外


//分析 加工
--图像处理 opencv
图像视频流合成 加工 分析结果 反馈监控

--机器学习

//输出
动力
终端监控传输 图像 声音 文本

额外反馈 警报 终端 
避障碍
开关状态 传感器

 
