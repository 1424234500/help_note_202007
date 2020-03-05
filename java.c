JAVA_HOME
C:\Program Files\Java\jdk-9
PATH
%JAVA_HOME%\bin;%JAVA_HOME%\jre\bin

export JAVA_HOME=/mnt/d/linux/jre1.8.0_202
export CLASSPATH=.:$JAVA_HOME/jre/lib/rt.jar:$JAVA_HOME/lib/dt.jar:$JAVA_HOME/lib/tools.jar
export PATH=$JAVA_HOME/bin:$PATH


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


////////////////////////////////core dump gc分析工具
jca457.jar  ha456.jar   gcviewer.jar

http://www.tagtraum.com/download/gcviewer-1.29-bin.zip


///////////////////////////// ibm jdk1.6 jvm参数
https://www.ibm.com/support/knowledgecenter/en/SSYKE2/earlier_releases/earlier_releases.html

-X ：非标准选项
-XX：非稳定选项
在选项名前用 “+” 或 “-” 表示开启或关闭特定的选项，例：
    -XX:+UseCompressedOops：表示开启 压缩指针
    -XX:-UseCompressedOops：表示关闭 压缩指针

1.堆分配参数
-XX:MaxDirectMemorySize=<size>  最大堆外内存设置 1.8？
    Setting	Value	Default
    <size>	[1[k|K|m|M|g|G] or greater]	-
-Xmn10M：设置新生代区域大小为10M
-XX:NewSize=2M：设置新生代初始大小为2M
-XX:MaxNewSize=2M：设置新生代最大值为2M
- - ##（如果以上三个同时设置了，谁在后面谁生效。生产环境使用-Xmn即可，避免抖动）
-Xms128M：设置java程序启动时堆内存128M（默认为物理内存1/64,且小于1G）
-Xmx256M：设置最大堆内存256M，超出后会出现 OutOfMemoryError（默认为物理内存1/64,且小于1G）
- - ##（生产环境 -Xms 与 -Xmx 最好一样，避免抖动）
-Xss1M：设置线程栈的大小 1M（默认1M）
- - ##  -XX:ThreadStackSize，-Xss 设置在后面，以-Xss为准；  -XX:ThreadStackSize设置在后面，主线程以 -Xss为准，其他线程以  -XX:ThreadStackSize为准
-XX:MinHeapFreeRatio=40：设置堆空间最小空闲比例（默认40）（当-Xmx与-Xms相等时，该配置无效）
-XX:MaxHeapFreeRatio=70：设置堆空间最大空闲比例（默认70）（当-Xmx与-Xms相等时，该配置无效）
-XX:NewRatio=2：设置年轻代与年老代的比例为2:1
-XX:SurvivorRatio=8：设置年轻代中eden区与survivor区的比例为8：1
-XX:MetaspaceSize=64M：设置元数据空间初始大小（取代-XX:PermSize）
-XX:MaxMetaspaceSize=128M：设置元数据空间最大值（取代之前-XX:MaxPermSize）
-XX:TargetSurvivorRatio=50：设置survivor区使用率。当survivor区达到50%时，将对象送入老年代
-XX:+UseTLAB：在年轻代空间中使用本地线程分配缓冲区(TLAB)，默认开启
-XX:TLABSize=512k：设置TLAB大小为512k
-XX:+UseCompressedOops：使用压缩指针，默认开启
-XX:MaxTenuringThreshold=15：对象进入老年代的年龄（Parallel是15，CMS是6）

2.垃圾回收器相关
-XX:MaxGCPauseMillis：设置最大垃圾收集停顿时间（收集器工作时会调整其他参数大小，尽可能将停顿控制在指定时间内）
-XX:+UseAdaptiveSizePolicy：打开自适应GC策略（该摸式下，各项参数都会被自动调整）
-XX:+UseSerialGC：在年轻代和年老代使用串行回收器
-XX:+UseParallelGC：使用并行垃圾回收收集器，默认会同时启用 -XX:+UseParallelOldGC（默认使用该回收器）
-XX:+UseParallelOldGC：开启老年代使用并行垃圾收集器，默认会同时启用 -XX:+UseParallelGC
-XX:ParallelGCThreads=4：设置用于垃圾回收的线程数为4（默认与CPU数量相同）
-XX:+UseConcMarkSweepGC：使用CMS收集器（年老代）
-XX:CMSInitiatingOccupancyFraction=80：设置CMS收集器在年老代空间被使用多少后触发
-XX:+CMSClassUnloadingEnabled：允许对类元数据进行回收
-XX:+UseCMSInitiatingOccupancyOnly：只在达到阈值的时候，才进行CMS回收
-XX:+UseG1GC：使用G1回收器
-XX:G1HeapRegionSize=16m：使用G1收集器时设置每个Region的大小（范围1M - 32M）
-XX:MaxGCPauseMillis=500 ：设置最大暂停时间（毫秒）
-XX:+DisableExplicitGC：禁止显示GC的调用（即禁止开发者的 System.gc();）


2.GC日志
-XX:+PrintGCDetails：打印GC信息
-XX:+PrintGCTimeStamps ：打印每次GC的时间戳（现在距离启动的时间长度）
-XX:+PrintGCDateStamps ：打印GC日期
-XX:+PrintHeapAtGC：每次GC时，打印堆信息
-Xloggc:/usr/local/tomcat/logs/gc.$$.log ：GC日志存放的位置
-XX:+UseGCLogFileRotation  ： 开启滚动日志记录
-XX:NumberOfGCLogFiles=5 ：滚动数量，命名为filename.0, filename.1 .....  filename.n-1,  然后再从filename.0 开始，并覆盖已经存在的文件
-XX:GCLogFileSize=8k  :  每个文件大小，当达到该指定大小时，会写入下一个文件

3.堆快照
-XX:+HeapDumpOnOutOfMemoryError：出现内存溢出时存储堆信息，配合 -XX:HeapDumpPath 使用
-XX:HeapDumpPath=/usr/local/tomcat/logs/oom.%t.log：堆快照存储位置
-XX:+UseLargePages：使用大页  
-XX:LargePageSizeInBytes=4m：指定大页的大小（必须为2的幂）






//////////////////////////////////////////////////////////////////cpu冲高
可能原因：
线程中有无限空循环、无阻塞、正则匹配或者单纯的计算
发生了频繁的gc
多线程的上下文切换

步骤：
1.查看日志，没有发现集中的错误日志，初步排除代码逻辑处理错误。
2.首先联系了内部下游系统观察了他们的监控，发现一起正常。可以排除下游系统故障对我们的影响。
3.查看provider接口的调用量，对比7天没有突增，排除业务方调用量的问题。
4.查看tcp监控，TCP状态正常，可以排除是http请求第三方超时带来的问题。
5.查看机器监控，6台机器cpu都在上升，每个机器情况一样。排除机器故障问题。

top -Hp $pid    #查看该pid下线程对应的系统占用情况。
#导出操作系统cpu信息
ps H -eo user,pid,ppid,tid,time,%cpu --sort=%cpu  | awk '{printf "0x%x\t %s\n", $4, $0}'
ps H -eo user,pid,ppid,tid,time,%cpu,command --sort=%cpu  | awk '{printf "0x%x\t %s\n", $4, $0}'
netstat -natl #网络连接信息
#获取服务器nmon日志
#数据库连接池 进程等情况
#redis信息快照  


///////////////////////////////////javacore分析线程栈
javacore分析  需要获取多次 Javacore 并进行比较，发现哪些是“变”的部分，哪些是“不变”的部分
除了线程信息外，还能提供关于操作系统，应用程序环境，线程，程序调用栈，锁，监视器和内存使用等相关信息
TITLE 信息块：描述 Javacore 产生的原因，时间以及文件的路径。常见的 Javacore 产生的原因可以参考文章
    1TISIGINFO  Dump Event "user"   user：SIGQUIT 信号 gpf：程序一般保护性错误导致系统崩溃 systhrow：JVM 内部抛出的异常 
GPINFO 信息块：GPF（一般保护性错误）信息
ENVINFO 信息块：系统运行时的环境和 JVM 参数
MEMINFO 信息块：内存使用情况和垃圾回收情况
LOCKS 信息块：用户监视器（monitor）和系统监视器（monitor）情况
CLASSES 信息块：类加载信息
THREADS 信息块：所有 java 线程的状态信息和执行堆栈
    死锁（Deadlock）【重点关注】：一般指多个线程调用间，进入相互资源占用，导致一直等待无法释放的情况。
    执行中（Runnable）【重点关注】：一般指该线程正在执行状态中，该线程占用了资源，正在处理某个请求，有可能在对某个文件操作，有可能进行数据类型等转换等。  结合ps线程耗cpu使用!!!
    等待资源（Waiting on condition）【重点关注】：等待资源，如果堆栈信息明确是应用代码，则证明该线程正在等待资源，一般是大量读取某资源、且该资源采用了资源锁的情况下，线程进入等待状态。又或者，正在等待其他线程的执行等。
    等待监控器检查资源（Waiting on monitor）
    暂停（Suspended）
    对象等待中（Object.wait()）
    阻塞（Blocked）【重点关注】：指当前线程执行过程中，所需要的资源长时间等待却一直未能获取到，被容器的线程管理器标识为阻塞状态，可以理解为等待资源超时的线程。这种情况在应用的日志中，一般可以看到 CPU 饥渴，或者某线程已执行了较长时间的信息。
    停止（Parked）



///////////////////////////////////////mem内存冲高  堆外内存问题  
was ehcache
https://www.jianshu.com/p/17e72bb01bf1
简单使用方式 nio-bytebuffer unsafe
ByteBuffer buffer = ByteBuffer.allocateDirect(10 * 1024 * 1024);
Unsafe unsafe = Unsafe.getUnsafe();
unsafe.allocateMemory(1024);
unsafe.reallocateMemory(1024, 1024);
unsafe.freeMemory(1024);

-XX:MaxDirectMemorySize=40M，将最大堆外内存设置为40M。  
-XX:+DisableExplicitGC，禁止代码中显式调用System.gc()。
-XX:+PrintGCDetails 

其垃圾回收依赖于代码显式调用System.gc()。

考虑使用缓存时，本地缓存是最快速的，但会给虚拟机带来GC压力。
使用硬盘或者分布式缓存的响应时间会比较长，这时候「堆外缓存」会是一个比较好的选择。

Ehcache 支持分配堆外内存，又支持KV操作，还无需关心GC    被广泛用于Spring，Hibernate缓存，并且支持堆内缓存，堆外缓存，磁盘缓存，分布式缓存。

堆外内存可以减少GC的压力，从而减少GC对业务的影响。


数据采集
原文链接：https://blog.csdn.net/lycyingO/article/details/80854669
jmap -dump:format=b,file=75.dump 75 通过分析堆内存找到DirectByteBuffer的引用和大小
部署一个升级基础软件之前的版本，持续观察
部署另一个版本，更改EhCache限制其大小到1024M
考虑到可能由Docker的内存分配机制引起，部署一实例到实体机


pmap -x ${pid}  | sort -n -k3 -r
大量申请64M大内存块的原因是由Glibc

#查看内存！！！会影响服务 注意dump的内存块大小，慎用
cat maps | sed -e "s/\([0-9a-f]\{8\}\)-\([0-9a-f]\{8\}\)/0x\1 0x\2/" | awk '{printf("\033[0;33m[%8d Page]\033[0m \033[0;35m[%8d KB]\033[0m %s\n", (0+$2 - $1)/4096, (0+$2 - $1)/1024, $0)}'


sudo grep rw-p /proc/${pid}/maps | sed -n 's/^\([0-9a-f]*\)-\([0-9a-f]*\) .*$/\1 \2/p' | head | while read start stop; do 
    sudo gdb --batch --pid ${pid} -ex "dump memory ${pid}-$start-$stop.dump 0x$start 0x$stop"
done

strings -n 10 *dump # 过滤特殊字符和过短行 查看内存

//常见堆外操作
unsafe
ByteBuffer.allocateDirect
GZIPInputStream使用Inflater申请堆外内存，Deflater释放内存，调用close()方法来主动释放。如果忘记关闭，Inflater对象的生命会延续到下一次GC。在此过程中，堆外内存会一直增长

///////////////////////////////////////mem内存冲高  堆内内存问题  
//jdk1.6 中 Oracle可视化监控
$JAVA_HOME/bin/jvisualvm.exe
naming-strategy=cn.studyBoot.dao.strategy.UpperTableStrategy

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
    

###########################javacore 获取方式
#IBM jre
kill -3
#ORACLE JDK
jstack -l $pid #采集java线程栈 


#JDK才有的jvm分析工具  jre不可用！
#采集最消耗cpu的线程tid pid ppid command 
#采集java线程栈 
#采集jmap
###################################################################################
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
jps  #查看java程序的pid<-q> 和 commond <-v>

jstack -l $pid > $file_jstack      #采集java线程栈 

jmap -dump:format=b,live,file=$file_jmap $pid       #采集jmap
#jhat -J-Xmx1024M $jmap_file #等待访问 http://127.0.0.1:7000
jvisualvm $file_jmap &  #图形化分析工具
jconsole    #图形化java控制台

#####################################################################################




//////////////////////////////////////cpu冲高 jit
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
2.dubbo加载xml修改地址无效?用户目录日志缓存zookeeper    ~/.dubbo/xxx




//注册中心
zookeeper安装启动 port:2181
wget https://mirrors.tuna.tsinghua.edu.cn/apache/zookeeper/zookeeper-3.4.14/zookeeper-3.4.14.tar.gz
tar -xzvf zookeeper-3.4.14.tar.gz
cd zookeeper-3.4.14
#复制并替换端口 配置
sed s/2181/8096/g conf/zoo_sample.cfg > conf/zoo.cfg	
#vi conf/zoo.cfg     #修改 数据路径 
#    dataDir=~/log/zookeeper
bin/zkServer.sh stop
bin/zkServer.sh start #</stop/status>

bin/zkCli.sh -server 127.0.0.1:2181  #测试
    ls /    4）查看有哪些zookeeper节点； 
    ls /daily_orderServer_group（节点名称） 5）查看注册了哪些服务，如图2； 

注意防火墙


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
wget https://cdn.npm.taobao.org/dist/node/v12.10.0/node-v12.10.0-linux-x64.tar.xz
xz -d node-v12.10.0-linux-x64.tar.xz
tar -xvf node-v12.10.0-linux-x64.tar
mv node-v12.10.0-linux-x64/ nodejs
echo 'export PATH=$PATH:'`pwd -LP`'/nodejs/bin'  | sudo tee -a /etc/profile
source /etc/profile
npm -v

/////////////////////////////////////////////////////was
/washome/IBM/WebSphere/AppServer/bin/startManager.sh
/washome/IBM/WebSphere/AppServer/profiles/AppSrv02/bin/startNode.sh
/washome/IBM/WebSphere/AppServer/profiles/AppSrv02/bin/startServer.sh  server1 --servername

cd /washome/IBM/WebSphere/AppServer/bin

1.列出现有概要文件
./manageprofiles.sh -listProfiles
2.刷新概要文件注册表
./manageprofiles.sh -validateAndUpdateRegistry
3.删除概要文件
./manageprofiles.sh -deleteAll
./manageprofiles.sh -delete -profileName AppSrv01
若过于慢 则直接删除对于目录 然后 刷新 然后删除


第一步 ：
./manageprofiles.sh -create -profileName  server1 -profilePath /washome/IBM/WebSphere/AppServer/profiles/server1

第三步：启动管理节点

/washome/IBM/WebSphere/AppServer/profiles/Dmgr01/bin/startManager.sh
1
第四步：查看SOAP端口

grep SOAP /washome/IBM/WebSphere/AppServer/profiles/Dmgr01/logs/AboutThisProfile.txt
得到管理 SOAP 连接器端口： 8879
第五步：增加应用概要

/washome/IBM/WebSphere/AppServer/profiles/AppSrv01/bin/addNode.sh 127.0.0.1 8879
1
如果添加时出错，例如：The system cannot create a SOAP connector to connect to host 127.0.0.1 at port 8879
此时 使用命令 hostname 得到主机名
切换到“/washome/IBM/WebSphere/AppServer/profiles/AppSrv02/bin/”下：
执行 ：./syncNode.sh 主机名 8879

第六步：启动

/washome/IBM/WebSphere/AppServer/profiles/AppSrv01/bin/startNode.sh
1
此时如果出现端口被占用的情况

这时候

ps -ef | grep java
ps -ef | grep was
1
2
能结束掉的进程都结束掉

第七步：这个时候就可以通过浏览器访问was控制平台

http://你的ip地址:9060/washome/IBM/console/login.do
1
然后开始新建服务server1
第八步：再命令行开启server1服务

cd /washome/IBM/WebSphere/AppServer/profiles/AppSrv01/bin/
./startServer.sh server1

1
2
3
此时如果发现网页登录不了，那么你就去查看一下你服务器的防火墙状态

 service iptables status
 一般都是开着的，如果开着的话就关闭就好了
 service iptables stop
 当然，你也可以设置filter让特定IP访问
1
2
3
4
完毕收工。

2.简单化配置
不需要创建 _portdef_AppSvr.props以及_portdef_DMgr.props文件
直接创建两个概要

创建管理概要
./manageprofiles.sh
-create
-profileName  Dmgr01
-profilePath  /washome/IBM/WebSphere/AppServer/profiles/Dmgr01
-templatePath  /washome/IBM/WebSphere/AppServer/profileTemplates/dmgr/

创建应用概要
./manageprofiles.sh
-create
-templatePath  /washome/IBM/WebSphere/AppServer/profileTemplates/default 
-profileName  AppSvr02
-profilePath   /washome/IBM/WebSphere/AppServer/profiles/AppSvr02 

1
2
3
4
5
6
7
8
9
10
11
12
13
14
这样也是可以的。
————————————————
版权声明：本文为CSDN博主「先定个小目标」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/sinat_30035833/article/details/87965839






