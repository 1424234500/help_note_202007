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
    推送提醒服务
    集成dubbo monitor
    
面试刷题 基础算法 lee code
redis注册中心
kafka 替换redis队列
分布式一致性
锁 乐观 悲观死锁

富文本 wiki功能

在线小工具集合

Prometheus监控服务器群

socket服务器 分布式部署 实现通信
app聊天


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
《深入理解计算机系统》，《tcp/ip详解 卷一、二、三》，《数据结构与算法》
熟悉io、多线程、集合等基础框架，了解分布式、缓存、消息、搜索
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


//Java学习----------------------------------看书 Thinking in Java---------------------
//thread 并发 同步锁 几种方式
//看书 通读 详细  
//ThreadLocal Context上下文 全局变量 
//线程池 - 单/多线程池队列 -> 高并发 - 定时任务调度《队列 生产者 消费者模型》
//进程通信 远程调用RPC 共享内存IPC
//classloader 注入原理 工具

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

 
