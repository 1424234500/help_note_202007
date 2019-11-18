


//maven 项目模块拆分
java 后台 jdk maven springboot/ 
    core 
        annotation
        cache       缓存           ehcache redis map db
        database    数据库         mysql oracle redis      c3p0 dbcp
        
        file        文件操作上传下载 分布式虚拟存储 网络存储 网盘？？？         
        http        网络访问
        service     服务化          rmi dubbo webservice
        
        encode      编码解码加密      md5 sha crc pingyin 
        
        pipe        生产消费者模式      
        route       发布订阅者模式      
        scheduler   定时器         quartz
        
        util        通用工具

vue 前端





JAVA_HOME
C:\Program Files\Java\jdk-9
PATH
%JAVA_HOME%\bin;%JAVA_HOME%\jre\bin


//反编译
javap -v ServiceImpl.class
javap -verbose ServiceImpl.class

eclipse启动jvm内存
eclipse启动程序 jvm 内存不够oom
Jdk edit 附加参数
-Xmx1024M


J2SE 8 = 52,
J2SE 7 = 51,
J2SE 6.0 = 50,
J2SE 5.0 = 49,
JDK 1.4 = 48,
JDK 1.3 = 47,
JDK 1.2 = 46,
JDK 1.1 = 45



性能分析  cpu冲高时
线程中有无限空循环、无阻塞、正则匹配或者单纯的计算
发生了频繁的gc
多线程的上下文切换

1.查看日志，没有发现集中的错误日志，初步排除代码逻辑处理错误。
2.首先联系了内部下游系统观察了他们的监控，发现一起正常。可以排除下游系统故障对我们的影响。
3.查看provider接口的调用量，对比7天没有突增，排除业务方调用量的问题。
4.查看tcp监控，TCP状态正常，可以排除是http请求第三方超时带来的问题。
5.查看机器监控，6台机器cpu都在上升，每个机器情况一样。排除机器故障问题。

top -Hp $pid    #查看该pid下线程对应的系统占用情况。

#导出操作系统cpu信息
ps H -eo user,pid,ppid,tid,time,%cpu --sort=%cpu  | awk '{printf "0x%x\t %s\n", $4, $0}'
ps H -eo user,pid,ppid,tid,time,%cpu,command --sort=%cpu  | awk '{printf "0x%x\t %s\n", $4, $0}'

    netstat -natl > netstat.log     #导出网络连接信息
    #获取服务器nmon日志
    #数据库连接池 进程等情况
    #redis信息快照  


#JDK才有的jvm分析工具  jre不可用！
#采集最消耗cpu的线程tid pid ppid command 
#采集java线程栈 
#采集jmap
#################################################
pid=`ps -elf | grep eclipse/jre | grep -v grep | awk '{print $4}' `   #获取pid
ti=`date "+%Y%m%d-%H%M%S"`    #时间戳
key=$pid.$ti        #命名键
file=~/logs         #存储根路径
file_cpu_thread=$file/$key.cpu_thread.log
file_jstack=$file/$key.jstack.log
file_jmap=$file/$key.jmap_dump.hprof

#采集最消耗cpu的线程tid pid ppid command 可根据tid->16进制查找java线程栈
#ps H -eo user,pid,ppid,tid,time,%cpu --sort=%cpu  > $file_cpu_thread    
ps H -eo user,pid,ppid,tid,time,%cpu --sort=%cpu  | awk '{printf "0x%x\t %s\n", $4, $0}'  > $file_cpu_thread  #附带自动转换16进制
jps  #查看java程序的pid 和 commond <-q>

jstack -l $pid > $file_jstack      #采集java线程栈 
#kill -3 [pid]   #自动生成java core ?

jmap -dump:format=b,live,file=$file_jmap $pid       #采集jmap
#jhat -J-Xmx1024M $jmap_file #等待访问 http://127.0.0.1:7000
jvisualvm $file_jmap &  #图形化分析工具

#########################################################

///////////////////////////////////
javacore分析常见问题
//////////////////////////////////////
jit引起一些cpu飚高
https://www.ezlippi.com/blog/2018/01/linux-high-load.html

JIT分层编译相关概念
需要注意的是,jdk1.8默认开启了分层编译,在1.7版本你可以通过-XX:+TieredCompilation开启分层编译,关于分层编译网上介绍的文章不多,主要分为C1和C2编译器,C1又称为客户端编译,C2编译器称为服务端编译器,通过抓取jvm进程线程堆栈也可以发现C1和C2编译线程的足迹,整个JIT的编译级别有以下5种:
0：解释执行,这是最慢的一种方式
1：简单C1编译代码
2：受限的C1编译代码,不做性能分析，根据方法调用次数和方法内部循环次数来启动
3：完全C1编译代码,编译器收集分析信息之后做的编译
4：C2编译代码,编译最慢,编译后执行速度最快
jvm启动参数
    JIT相关JVM参数简介    -XX:+TieredCompilation
    选项	默认值	解释
    CompileThreshold	1000 or 1500/10000	编译阈值,方法执行多少次后进行编译
    PrintCompilation	false	jit编译时输出日志
    InitialCodeCacheSize	160K (varies)	初始codecache大小
    ReservedCodeCacheSize	32M/48M	codecache最大值
    ExitOnFullCodeCache	false	codecache满了退出jvm
    UseCodeCacheFlushing	false	codecache满了时清空一半的codecache
    PrintFlagsFinal	false	打印所有的jvm选项
    PrintCodeCache	false	jvm退出时打印codecache
    PrintCodeCacheOnCompilation	false	编译时打印codecache使用情况

0最开始都是解释执行
1理想情况下应转成level3编译
2根据C1队列长度和C1编译线程数来调整编译的阈值
3根据C2队列长度可能转向C2编译
4根据C2队列长度、C2编译线程数调整level4编译阈值
如果方法非常小,没什么可以优化的空间，直接转level1编译
最常见的编译层次转换:0 -> 3 -> 4

解决方案
1）为了避免CodeCache满导致JIT停止编译或者CodeCacheFlushing 
获取到当前JIT的CodeCache大小  空间可能不够用，另一方面是CodeCache是不会回收的，所以会累积的越来越多 推荐调大
jinfo -flag ReservedCodeCacheSize ${pid} //常在64 bit机器上默认是48m，当code cache用满了后，编译优化就被禁掉了，此时会回归到解释执行，RT可想而知不会好到哪去
    -XX:ReservedCodeCacheSize=251658240
根据实际情况调整ReservedCodeCacheSize的大小,最后调整之后我们在jvm启动脚本中加上了如下两个参数:
    -XX:ReservedCodeCacheSize=512m
    -XX:-UseCodeCacheFlushing   (启用回收)
2) 编写预热代码
    编写WarmUpContextListener实现Spring的ApplicationContextAware接口，确保在Web容器启动完成前,调用需要预热的方法；
    WarmUpContextListener读取预先配置好的参数,包括要调用的目标方法、请求参数、执行次数和超时时间;
    新建线程池执行目标方法,执行N次触发JIT编译;
    执行完成,关闭预热线程池;
    Web容器启动完成,对外发布服务。
经过以上两个步骤之后,我们的系统就没出现过因jit导致的负载高的场景。









jdk1.6 中 Oracle可视化监控
$JAVA_HOME/bin/jvisualvm.exe

naming-strategy=cn.studyBoot.dao.strategy.UpperTableStrategy



//jmap jhat jstat jstack  jps     
jmap [option] $pid
jmap [option] [server_id@]<remote server IP or hostname>
    -<none> 这个意思是说，jmap可以不加任何option参数信息，只是指定Java进程的进程号。这种情况下，jmap命令将按照Linux操作系统进程内存分析命令pmap的相关性，输出内存分析结果。
    -heap 查看整个JVM内存状态   改参数将输出当前指定java进程的堆内存概要信息。  使用CMS GC 情况下，jmap -heap的执行有可能会导致JAVA 进程挂起
    -clstats 该参数将打印出当前java进程中，存在的每个类加载器，以及通过该类加载器已经完成加载的各类信息，包括但不限于类加载器的活动情况、已经加载的类数量、关联的父类加载器等等（class文件通过类加载器完成的载入、连接、验证初始化等过程可以在这个命令的输出详情中具体体现出来）。
    finalizerinfo 该参数可打印出等待终结的对象信息，当Java进程在频繁进行Full GC的时候，可以通过该命令获取问题的排查依据。
    -histo[:live] 查看JVM堆中对象详细占用情况 该参数可以输出每个class的实例数目、内存占用、类全名等信息。如果live子参数加上后,只统计活的对象数量。该命令非常有用，举个例子，你可以使用该名了检查软件系统的某种设计模式是否符合设计预期。
    -dump:<dump-options> 取得当前指定java进程堆内存中各个class实例的详细信息，并输出到指定文件。dump命令还有三个子参数分别是。
        live只分析输出目前有活动实例的class信息；
        format输出格式，默认为“b”，可以使用配套的分析软件进行分析；
        file子参数可以指定输出的文件，注意，如果输出文件已经存在，则可以使用-F 参数来强制执行命令。
    案例：
    jmap -dump:format=b,file=文件名 [pid]

//在远程服务器server_address上执行:
    1:服务器启动java应用，查询该进程的pid
    2:rmiregistry -J-Xbootclasspath/p:$JAVA_HOME/lib/sa-jdi.jar &
    3:执行jsadebugd pid server-id
在客户端执行:
    jmap -heap server_id@server_address
    
    
1. JVM执行异常时，自动生成Javacore
1.1 发生了引起JVM停止运行的本地错误时，会自动产生Javacore文件
1.2 JVM内存不足时，会自动产生Javacore文件
2. 触发JVM生成JDK
2.1 （常用）从命令行中发出kill -3 <pid>指令，生成Javacore
2.2 在应用中调用com.ibm.jvm.Dump.JavaDump()方法，生成Javacore
2.3 使用WAS wsadmin utility命令生成Javacore, 以Jython语言为例：
jvm = AdminControl.completeObjectName('type=JVM,process=server1,*')
AdminControl.invoke(jvm, 'dumpThreads')
2.4 可以配置dump agent触发生成Javacore
dump agent提供了一些可配置的选项，详细见文档
      
///////////////////////////////////////////////////////////////////
//dubbo zookeeper java 安装环境      
      
0. Container: provider的运行容器。
1. Provider: 服务提供者在启动时，向注册中心注册自己提供的服务。 Java项目
2. Consumer: 服务消费者在启动时，向注册中心订阅自己所需的服务。 Java项目
             从提供者地址列表中，基于软负载均衡算法，选一台提供者进行调用，如果调用失败，再选另一台调用。 
3. Registry: 注册中心返回服务提供者地址列表给消费者，如果有变更，注册中心将基于长连接推送变更数据给消费者。 zookeeper redis
4. Monitor : 服务消费者和提供者，在内存中累计调用次数和调用时间，定时每分钟发送一次统计数据到监控中心。    

常见问题
1.dubbo配置xml只会读取resource下面? System属性也无效
2.dubbo加载xml修改地址无效?用户目录日志缓存zookeeper




//注册中心
zookeeper安装启动 port:2181
wget https://mirrors.tuna.tsinghua.edu.cn/apache/zookeeper/zookeeper-3.4.14/zookeeper-3.4.14.tar.gz
tar -xzvf zookeeper-3.4.14.tar.gz
cd zookeeper-3.4.14
cp conf/zoo_sample.cfg conf/zoo.cfg
#vi conf/zoo.cfg     #修改 数据路径 
#    dataDir=~/log/zookeeper

bin/zkServer.sh start #</stop/status>
bin/zkCli.sh -server 127.0.0.1:2181  #测试
    ls /    4）查看有哪些zookeeper节点； 
    ls /daily_orderServer_group（节点名称） 5）查看注册了哪些服务，如图2； 

注意防火墙

//tomcat
wget https://mirrors.tuna.tsinghua.edu.cn/apache/tomcat/tomcat-8/v8.5.42/bin/apache-tomcat-8.5.42.tar.gz
tar -xvf apache-tomcat-8.5.42.tar.gz
#配置端口
vim conf/server.xml
<Connector port="8090" protocol="HTTP/1.1"
               connectionTimeout="20000"
               redirectPort="8443" />

#配置mannager ip控制
<Valve className="org.apache.catalina.valves.RemoteAddrValve"
         allow="d+\.\d+\.\d+\.\d+|::1|0:0:0:0:0:0:0:1" />
#配置角色 后台管理权限
vim conf/tomcat-users.xml
  <role rolename="tomcat"/>
  <user username="walker" password="qwer" roles="tomcat"/>


//监控中心


//监控中心 new  https://gitee.com/handu/dubbo-monitor/tree/master
wget https://codeload.github.com/1424234500/dubbo-monitor/zip/master
修改pom.xml   dubbo版本 编译报错StringUtil.isEmpty 切换dubbo的工具导入
配置数据源mysql 建表 修改帐号密码 zookeeper地址
mvn package 生成war 部署



#org.springframework.web.context.ConfigurableWebApplicationContext.setId 在工程中spring-2.5.6.SEC03.jar 和 spring-context-3.2.9.RELEASE.jar 中都有。
问题解决：删掉spring-2.5.6.SEC03.jar后正常，奇怪的是此问题在tomcat7中并没有出现，但是tomcat8下就会出错。
tomcat/bin/startup.sh 启动tomcat
http://127.0.0.1:8080/dubbo-monitor
walker/qewr



//配置tomcat特定jdk jre
vim tomcat/bin/setclasspath.sh
# -----------------------------------------------------------------------------
#  Set JAVA_HOME or JRE_HOME if not already set, ensure any provided settings
#  are valid and consistent with the selected start-up options and set up the
#  endorsed directory.
#
#  $Id: setclasspath.sh 1430568 2013-01-08 22:08:57Z schultz $
# -----------------------------------------------------------------------------
set JAVA_HOME=/home/walker/software/jdk1.7.0_80/
set JRE_HOME=/home/walker/software/jdk1.7.0_80/jre


    

//tomcat maven web
配置  Project Facets 
Dynamic Web Module 3.0
Java 1.8
配置  Java Compiler
jdk1.8
配置  Java Build Path
jdk1.8
配置  Deployment Assembly

配置tomcat特定jdk eclipse 
导入tomcat可选定jdk


idea部署tomcat web项目
artifacts
__:war exploded 
　　热部署
　　不会自动copy配置文件到目录？
___:war
　　发布模式,这是先打成war包,再部署
debug configuration tabs
tomcat
add war artifacts
application context : url !!! /walker-web


//反编译 jd-gui 依赖jdk1.7异常 无注册表信息
java -jar jd-gui.exe



//node
wget http://nodejs.org/dist/latest/node-v10.11.0-linux-x64.tar.gz 
wget https://cdn.npm.taobao.org/dist/node/v12.10.0/node-v12.10.0-linux-x64.tar.xz
xz -d node-v12.10.0-linux-x64.tar.xz
tar -xvf node-v12.10.0-linux-x64.tar
mv node-v12.10.0-linux-x64/ nodejs
sudo echo 'export PATH=$PATH:'`pwd -LP`"/nodejs/bin" >> /etc/profile
source /etc/profile
npm -v


//华为推送
V3
https://developer.huawei.com/consumer/cn/service/hms/catalog/huaweipush_v3.html?page=hmssdk_huawei_serviceChangeDescription
V2
https://developer.huawei.com/consumer/cn/service/hms/catalog/huaweipush_agent.html







