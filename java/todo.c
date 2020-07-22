jdk1.8特性使用熟练
设计模式使用

实际使用的项目？
功能 
    主页展示 介绍
    //数据库数据通用展示 管理 接口
    //权限管理模块 登录 角色 权限 session token   
     //   用户 - 部门 - 角色 地域爬取数据 用户模拟定期造数
    //    角色 - 权限
         
    //便捷接口在线测试swagger
    //文件管理 上传下载
    //quartze在线管理 集群模式
    //自动化打包部署问题 idea依赖
    //jpa分表插件sharding使用 联合多数源配置 
    //json格式化jackson解决
     
    模拟用户访问造数压力监控一体化 构造用户量 模拟用户  熔断限流
    在线管理 移动端推送 短信 邮件  （验证码）
    
    权限 用户 管理员 分级 菜单  shiro 框架使用
    12306抢票爬取 
    
面试刷题 
基础算法 lee code
//redis注册中心
//配置中心 临时 
guava 限流 布隆过滤器   熔断限流框架sentinel 
kafka 替换redis队列   消息队列使用设计模式
消息队列使用思想
zookeeper的锁用法 其他用法
elasticsearch

集成dubbo monitor ？监控
Apollo配置中心?

wiki功能
在线小工具集合  
	在线java算法演示中心
	在线各语言 shell python编辑器
https 
 
//框架实现原理 
Spring bean创建原理 ioc/aop 
Springboot 启动 
	//配置 切换profile --spring.profiles.active=prod
	事务级别 
//SpringMVC 介绍自实现
// 动态代理proxy 

研究kafka源码社区


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


/*redis 订阅发布模式*/
/*redis 队列共享数据*/
压力测试性能


/*jvm gc核心日志 核心监控 调优 dump*/
/*jstack */
//多数据源 
//mysql oracle 分表案例 分表插件sharding
/*java core 导出 分析*/

 
//后台开发学习//////////////////////////////////////////////////////////////////////////////////

//Java学习----------------------------------看书 Thinking in Java---------------------
//thread 并发 同步锁 几种方式
//看书 通读 详细  
//ThreadLocal Context上下文 全局变量 
//线程池 - 单/多线程池队列 -> 高并发 - 定时任务调度《队列 生产者 消费者模型》
//进程通信 远程调用RPC 共享内存IPC
//classloader 注入原理 工具

 

专业的软件干专业的事情：nginx做反向代理，db做固化，cache做缓存，mq做通道

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





//接口接入----------------
百度文本语音转换
百度文本安全脏话识别
京东Alpha人工智能接口


//设计跳板机 socket 路由表 路由器


//TCP/IP socket/应用层协议/mqtt/http/自己的协议@
Android 进程 jni 从底层向上 模拟系统信息 工具连点器
Android 设备控制器 - 设备socket - socketServer<net> - 终端socket
设备端 socket适配管理s



//Linux-------------------------------------
Shell多进程 管道 同步 队列 生产者 消费者 进程通信
内核驱动编写test



 
