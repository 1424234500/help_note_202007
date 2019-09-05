//redis 数据库
//安装 
sudo apt-get update
sudo apt-get install make
sudo apt-get install gcc
wget http://download.redis.io/releases/redis-5.0.3.tar.gz
tar -xzvf redis-5.0.3.tar.gz
cd redis-5.0.3
make    #make MALLOC=libc
make install PREFIX=.  #选定目录安装生成bin目录  默认/usr/local/bin/
//测试 依赖tcl
wget http://downloads.sourceforge.net/tcl/tcl8.6.1-src.tar.gz  
sudo tar -xzvf tcl8.6.1-src.tar.gz
cd  tcl8.6.1/unix
sudo ./configure  
sudo make  
sudo make install  


./src/redis-server.sh <redis.conf>
./src/redis-cli <-c 集群模式> <-h host/12.0.0.1> <-p port/6379> <-a password> <-n 0数据库编号>  <set key value>

Usage: redis-cli [OPTIONS] [cmd [arg [arg ...]]]
  -h <hostname>      Server hostname (default: 127.0.0.1).
  -p <port>          Server port (default: 6379).
  -s <socket>        Server socket (overrides hostname and port).
  -a <password>      Password to use when connecting to the server.
                     You can also use the REDISCLI_AUTH environment
                     variable to pass this password more safely
                     (if both are used, this argument takes predecence).
  -u <uri>           Server URI.
  -r <repeat>        Execute specified command N times.
  -i <interval>      When -r is used, waits <interval> seconds per command.
                     It is possible to specify sub-second times like -i 0.1.
  -n <db>            Database number.
  -x                 Read last argument from STDIN.
  -d <delimiter>     Multi-bulk delimiter in for raw formatting (default: \n).
  -c                 Enable cluster mode (follow -ASK and -MOVED redirections).

//修改配置 redis.conf
    daemonize：如需要在后台运行，把该项的值改为yes
    pdifile：把pid文件放在/var/run/redis.pid，可以配置到其他地址
    bind：指定redis只接收来自该IP的请求，如果不设置，那么将处理所有请求，在生产环节中最好设置该项
    port：监听端口，默认为6379
    timeout：设置客户端连接时的超时时间，单位为秒
    loglevel：等级分为4级，debug，revbose，notice和warning。生产环境下一般开启notice
    logfile：配置log文件地址，默认使用标准输出，即打印在命令行终端的端口上
    database：设置数据库的个数，默认使用的数据库是0
    save：设置redis进行数据库镜像的频率
    rdbcompression：在进行镜像备份时，是否进行压缩
    dbfilename：镜像备份文件的文件名
    dir：数据库镜像备份的文件放置的路径
    slaveof：设置该数据库为其他数据库的从数据库
    masterauth：当主数据库连接需要密码验证时，在这里设定
    requirepass：设置客户端连接后进行任何其他指定前需要使用的密码
    maxclients：限制同时连接的客户端数量
    maxmemory：设置redis能够使用的最大内存
    appendonly：开启appendonly模式后，redis会把每一次所接收到的写操作都追加到appendonly.aof文件中，当redis重新启动时，会从该文件恢复出之前的状态
    appendfsync：设置appendonly.aof文件进行同步的频率
    vm_enabled：是否开启虚拟内存支持
    vm_swap_file：设置虚拟内存的交换文件的路径
    vm_max_momery：设置开启虚拟内存后，redis将使用的最大物理内存的大小，默认为0
    vm_page_size：设置虚拟内存页的大小
    vm_pages：设置交换文件的总的page数量
    vm_max_thrrads：设置vm IO同时使用的线程数量
    自动存储
    vim redis.conf
    #   after 900 sec (15 min) if at least 1 key changed
    #   after 300 sec (5 min) if at least 10 keys changed
    #   after 60 sec if at least 10000 keys changed
    save 1800 1
    save 600 100000
    
    
    
    
    
//集群模式 哨兵模式（sentinel） （主从复制、读写分离、主从切换）
1）redis cluster集群方案;

a.复制redis.conf 修改为 redis_cluster_7000->7005.conf 修改端口  已备份至redis/
    port  7000     #端口7000,7002,7003        
    pidfile  /var/run/redis_7000.pid  #pidfile文件对应7000,7001,7002
    dbfilename dump_7000.rdb    #持久化文件 隔离
    cluster-config-file  nodes_7000.conf   #集群的配置  配置文件首次启动自动生成 7000,7001,7002

    bind 本机ip     #默认ip为127.0.0.1 需要改为其他节点机器可访问的ip 否则创建集群时无法访问对应的端口，无法创建集群
    daemonize    yes  #redis后台运行
    cluster-enabled  yes  #开启集群  把注释#去掉
    cluster-node-timeout  15000     #请求超时  默认15秒，可自行设置
    appendonly  yes           #aof日志开启  有需要就开启，它会每次写操作都记录一条日志　


#关闭
    ps -elf | grep redis | grep 700 | awk '{print $4}' | xargs kill -9
#1.启动 至少六个节点
    ./src/redis-server redis_cluster_7000.conf 
    ./src/redis-server redis_cluster_7001.conf 
    ./src/redis-server redis_cluster_7002.conf 
    ./src/redis-server redis_cluster_7003.conf 
    ./src/redis-server redis_cluster_7004.conf 
    ./src/redis-server redis_cluster_7005.conf 
#2.工具启动
#vim utils/create-cluster/create-cluster #设置端口起点为6999 数量
#cd utils/create-cluster/
#./create-cluster stop/start
#确认启动
    ps -elf | grep redis | grep 700
#新版redis不用 redis-trib.rb   自动设置前三为主master 后三为从slave
    ./src/redis-cli --cluster create 127.0.0.1:7000 127.0.0.1:7001 127.0.0.1:7002 127.0.0.1:7003 127.0.0.1:7004 127.0.0.1:7005 --cluster-replicas 1
#测试
    ./src/redis-cli -c -p 7000
    set test:clu:3 3
        -> Redirected to slot [6005] located at 127.0.0.1:7001
        OK
        
#设置键值 分配到目标redis 设置值    CRC16(key) % 16384

#集群清理数据 分别登录每台master
./src/redis-cli -c -p 7000 flushall
./src/redis-cli -c -p 7001 flushall
./src/redis-cli -c -p 7002 flushall

//集群主从相关命令
#### 集群(cluster)
CLUSTER INFO 打印集群的信息    三主三备 slot分配
CLUSTER NODES 列出集群当前已知的全部节点（node）。以及这些节点的相关信息。  
#### 节点(node)
CLUSTER MEET <ip> <port> 将 ip 和 port 所指定的节点加入到集群其中。让它成为集群的一份子。  
CLUSTER FORGET <node_id> 从集群中移除 node_id 指定的节点。  
CLUSTER REPLICATE <node_id> 将当前节点设置为 node_id 指定的节点的从节点。  
CLUSTER SAVECONFIG 将节点的配置文件保存到硬盘里面。  
#### 槽(slot)  
CLUSTER ADDSLOTS <slot> [slot ...] 将一个或多个槽（slot）指派（assign）给当前节点。  
CLUSTER DELSLOTS <slot> [slot ...] 移除一个或多个槽对当前节点的指派。  
CLUSTER FLUSHSLOTS 移除指派给当前节点的全部槽，让当前节点变成一个没有指派不论什么槽的节点


//数据迁移  单对单
零、aof日志
    redis-cli -h 202.102.221.12 -a password --pipe < appendonly.aof
    redis-cli -h 202.102.221.11 -a password config set appendonly no
一、move
    move key db 内部数据库db移动
二、dump + restore    序列化 后 反序列化
    127.0.0.1:6379> dump key1
        "\x00\bFederico\x06\x00L\x88\xd4\xb3U/Y\xae"
    127.0.0.1:6380> restore key1 0 "\x00\bFederico\x06\x00L\x88\xd4\xb3U/Y\xae"
三、migrate
  migrate用于在Redis实例间进行数据迁移，实际上migrate命令是将dump、restore、del三个命令进行组合，从而简化了操作流程。migrate命令具有原子性，从Redis 3.0.6版本后已经支持迁移多个键的功能。migrate命令的数据传输直接在源Redis和目标Redis上完成，目标Redis完成restore后会发送OK给源Redis。
migrate参数：
    host：目标Redis的IP地址
    port：目标Redis的端口
    key|""：Redis 3.0.6 后如果需要迁移多个键，此处为空字符串""
    destination-db：目标Redis的数据库索引
    timeout：迁移的超时时间（单位为毫秒）
    [auth mypassword] 密码 3.0以后
    copy：如果添加此选项后，迁移后不删除源键。
    replace：如果添加此选项migrate不管目标Redis是否存在该键都会正常迁移进行数据覆盖
    keys：如果要删除多个建，填写keys key1 key2 key3
127.0.0.1:6379> MIGRATE 127.0.0.1 7000 '3' 0 1000 copy replace

命令：redis-cli [-n [0-15]] keys '*' | xargs -I '{}' redis-cli [-n [0-15]] migrate 目标IP 6379 '' [0-15] 10000 COPY REPLACE keys '{}'
#单key还是批量? 单台模式 127.0.0.1:7000的key取出来 全部 用7000的身份主动导入覆盖到 6379去
./src/redis-cli -h 127.0.0.1 -p 7000 keys '*' | xargs -I {} ./src/redis-cli -h 127.0.0.1 -p 7000 migrate 127.0.0.1 6379 '' 0 10000  COPY REPLACE keys {}
# 单key模式
./src/redis-cli -h 127.0.0.1 -p 7000 keys '*' | xargs -I {} ./src/redis-cli -h 127.0.0.1 -p 7000 migrate 127.0.0.1 6379 {} 0 10000 COPY REPLACE 
# 高版本批量模式 单台可用 集群不能批量插入跨节点
不带密码
./src/redis-cli -h 127.0.0.1 -p 7000 migrate 127.0.0.1 6379 '' 0 10000 COPY REPLACE keys `./src/redis-cli -h 127.0.0.1 -p 7000 keys '*' `
#带密码
./src/redis-cli -h 127.0.0.1 -p 7000 migrate 127.0.0.1 6379 '' 0 10000 auth password COPY REPLACE keys `./src/redis-cli -h 127.0.0.1 -p 7000 keys '*' `

#   把集群模式单台 自动读取转移 127.0.0.1:7000的key取出来 全部 用7000的身份主动导入覆盖到 6379去
./src/redis-cli -c -h 127.0.0.1 -p 7000 keys '*' | xargs -I {} ./src/redis-cli -c -h 127.0.0.1 -p 7000 migrate 127.0.0.1 6379 '' 0 10000 COPY REPLACE keys {}

//数据迁移 集群 单/多 -> 多
#清理密码 避免异常 注意改回去
    ./src/redis-cli config set requirepass ""
#从单台 或者 集群127.0.0.1:6379 导入到集群 127.0.0.1:7000-7005  
    ./src/redis-cli -c -h  127.0.0.1 -p 7000  --cluster import 127.0.0.1:7000 --cluster-from  127.0.0.1:6379   --cluster-copy --cluster-replace


//数据迁移 集群 多 -> 单   集群配置减少到单台 slot 和 数据合并到单台 数据量?
Redis 集群有16384个哈希槽,CRC16校验后对16384取模5461 5461 5462.集群的每个节点负责一部分hash槽,举个例子,比如当前集群有3个节点,
    dfa3ed66a30ae179da2a394dc66bdab491c31043 127.0.0.1:7002@17002 myself,master - 0 1562913105000 3 connected 10923-16383
    cc1ffe732b3d0bf6f6f3da07c264b668af3dc048 127.0.0.1:7001@17001 master - 0 1562913108254 2 connected 5461-10922
    0f15549cc26f77616932029ee0794686aa4daeaf 127.0.0.1:7000@17000 master - 0 1562913110261 1 connected 0-5460

把B节点上5462个slots移动A节点上
./src/redis-cli reshard --from cc1ffe732b3d0bf6f6f3da07c264b668af3dc048  --to dfa3ed66a30ae179da2a394dc66bdab491c31043  --slots 5462 --yes 10.10.10.126:7000
把C节点上的5461个slots移动A节点上
./redis-trib.rb reshard --from e7005711bc55315caaecbac2774f3c7d87a13c7a    --to 6a85d385b2720fd463eccaf720dc12f495a1baa3  --slots 5461 --yes 10.10.10.126:7000

//哨兵主从切换
2）master/slave主从方案;
3）哨兵模式来进行主从替换以及故障恢复;    热切主从 defult 26379
SENTINEL get-master-addr-by-name <master name>获取当前的主服务器IP地址和端口
SENTINEL slaves <master name>获取所有的Slaves信息

sentinetl.conf  配置监控节点 sentinel myid xxxx sentinel monitor mymaster xxx 2      自动生成 展示所有从节点  解除哨兵关联!!!  需要关闭所有节点 修改所有配置后 一一重启
redis.conf  配置slaveof 主节点       自动生成 



//测试
./runtest 




//环境状态监控
info 展示redis状态 多数据库信息
    # Keyspace
    db0:keys=2,expires=0,avg_ttl=0
    db2:keys=3,expires=0,avg_ttl=0

save rdb持久化
flushall 清空 当前数据库redis-cli -n 0-15 
flushdb 清空所有数据库
redis-cli info | grep role //查看主从
role:slave
role:master

关于持久化的几个问题：
RDB 模式：Redis 在指定的时间间隔上对数据集做快照。RDB 对日常备份和灾备都非常方便，而且对性能没有太大的影响。通常定时，比如每5分钟来做快照，但是使用它还是会丢数据。
AOF：Redis 服务器端将它收到的所有写操作以追加写方式写入到日志文件中，以便在服务器重启时重新执行。AOF有较强的灵活性，比如每秒刷新，每次写就刷新等；但是，AOF 文件通常比 RDB 文件大。根据不同的写入模式，AOF 通常会比 RDB 慢。
默认开启 RDB，关闭 AOF。用户可以将两者都关闭，或者将两者都开启。官方不建议单独使用 AOF。如果对数据丢失有一定的容忍度，比如五分钟，则可以使用 RDB；否则，建议两者同时使用。




