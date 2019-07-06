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
./src/redis-cli <-c 集群模式> <-h host/12.0.0.1> <-p port/6379> <-a password>  <set key value>

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

//集群模式 哨兵模式（sentinel） （主从复制、读写分离、主从切换）
1）redis cluster集群方案;

a.复制redis.conf 修改为 redis_cluster_7000->7005.conf 修改端口  已备份至redis/
port  7000     #端口7000,7002,7003        
bind 本机ip     #默认ip为127.0.0.1 需要改为其他节点机器可访问的ip 否则创建集群时无法访问对应的端口，无法创建集群
daemonize    yes  #redis后台运行
pidfile  /var/run/redis_7000.pid  #pidfile文件对应7000,7001,7002
cluster-enabled  yes  #开启集群  把注释#去掉
cluster-config-file  nodes_7000.conf   #集群的配置  配置文件首次启动自动生成 7000,7001,7002
cluster-node-timeout  15000     #请求超时  默认15秒，可自行设置
appendonly  yes           #aof日志开启  有需要就开启，它会每次写操作都记录一条日志　

#启动 至少六个节点
./src/redis-server redis_cluster_7000.conf 
./src/redis-server redis_cluster_7001.conf 
./src/redis-server redis_cluster_7002.conf 
./src/redis-server redis_cluster_7003.conf 
./src/redis-server redis_cluster_7004.conf 
./src/redis-server redis_cluster_7005.conf 
#启动工具
#vim utils/create-cluster/create-cluster #设置端口起点为6999 数量
#cd utils/create-cluster/
#./create-cluster stop/start
#确认启动
ps -elf | grep redis

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
CLUSTER INFO 打印集群的信息  
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


2）master/slave主从方案;
3）哨兵模式来进行主从替换以及故障恢复;    热切主从 defult 26379
SENTINEL get-master-addr-by-name <master name>获取当前的主服务器IP地址和端口
SENTINEL slaves <master name>获取所有的Slaves信息

//测试
./runtest 




//环境状态监控
info 展示redis状态
flushall 清空
flushdb
redis-cli info | grep role //查看主从
role:slave
role:master

关于持久化的几个问题：
RDB 模式：Redis 在指定的时间间隔上对数据集做快照。RDB 对日常备份和灾备都非常方便，而且对性能没有太大的影响。通常定时，比如每5分钟来做快照，但是使用它还是会丢数据。
AOF：Redis 服务器端将它收到的所有写操作以追加写方式写入到日志文件中，以便在服务器重启时重新执行。AOF有较强的灵活性，比如每秒刷新，每次写就刷新等；但是，AOF 文件通常比 RDB 文件大。根据不同的写入模式，AOF 通常会比 RDB 慢。
默认开启 RDB，关闭 AOF。用户可以将两者都关闭，或者将两者都开启。官方不建议单独使用 AOF。如果对数据丢失有一定的容忍度，比如五分钟，则可以使用 RDB；否则，建议两者同时使用。



//发布订阅模式
publish chat aaa                  //发布一个chat主题的消息，内容为aaa
subscribe chat                    //订阅一个chat主题的消息
PSUBSCRIBE *                      //订阅所有消息

//#########数据结构 关系型 非关系型转换
key的存活时间：
无论什么时候，只要有可能就利用key超时的优势。一个很好的例子就是储存一些诸如临时认证key之类的东西。当你去查找一个授权key时——以OAUTH为例——通常会得到一个超时时间。
这样在设置key的时候，设成同样的超时时间，Redis就会自动为你清除。

关系型数据库的redis
1: 把表名转换为key前缀 如, tag:
2: 第2段放置用于区分区key的字段--对应mysql中的主键的列名,如userid
3: 第3段放置主键值,如2,3,4...., a , b ,c
4: 第4段,写要存储的列名
例：user:userid:9:username


//##########基本命令

 
1	del key
该命令用于在 key 存在时删除 key。
2	dump key 
序列化给定 key ，并返回被序列化的值。
3	exists key 
检查给定 key 是否存在。
4	expire key seconds
为给定 key 设置过期时间。
5	expireat key timestamp 
expireat 的作用和 expire 类似，都用于为 key 设置过期时间。 不同在于 expireat 命令接受的时间参数是 unix 时间戳(unix timestamp)。
6	pexpire key milliseconds 
设置 key 的过期时间以毫秒计。
7	pexpireat key milliseconds-timestamp 
设置 key 过期时间的时间戳(unix timestamp) 以毫秒计
8	keys pattern 
查找所有符合给定模式( pattern)的 key 。
9	move key db 
将当前数据库的 key 移动到给定的数据库 db 当中。
10	persist key 
移除 key 的过期时间，key 将持久保持。
11	pttl key 
以毫秒为单位返回 key 的剩余的过期时间。
12	ttl key 
以秒为单位，返回给定 key 的剩余生存时间(ttl, time to live)。
13	randomkey 
从当前数据库中随机返回一个 key 。
14	rename key newkey 
修改 key 的名称
15	renamenx key newkey 
仅当 newkey 不存在时，将 key 改名为 newkey 。
16	type key 
返回 key 所储存的值的类型。


1	hdel key field1 [field2] 
删除一个或多个哈希表字段
2	hexists key field 
查看哈希表 key 中，指定的字段是否存在。
3	hget key field 
获取存储在哈希表中指定字段的值。
4	hgetall key 
获取在哈希表中指定 key 的所有字段和值
5	hincrby key field increment 
为哈希表 key 中的指定字段的整数值加上增量 increment 。
6	hincrbyfloat key field increment 
为哈希表 key 中的指定字段的浮点数值加上增量 increment 。
7	hkeys key 
获取所有哈希表中的字段
8	hlen key 
获取哈希表中字段的数量
9	hmget key field1 [field2] 
获取所有给定字段的值
10	hmset key field1 value1 [field2 value2 ] 
同时将多个 field-value (域-值)对设置到哈希表 key 中。
11	hset key field value 
将哈希表 key 中的字段 field 的值设为 value 。
12	hsetnx key field value 
只有在字段 field 不存在时，设置哈希表字段的值。
13	hvals key 
获取哈希表中所有值
14	hscan key cursor [match pattern] [count count] 
迭代哈希表中的键值对。

1	blpop key1 [key2 ] timeout 
移出并获取列表的第一个元素， 如果列表没有元素会阻塞列表直到等待超时或发现可弹出元素为止。
2	brpop key1 [key2 ] timeout 
移出并获取列表的最后一个元素， 如果列表没有元素会阻塞列表直到等待超时或发现可弹出元素为止。
3	brpoplpush source destination timeout 
从列表中弹出一个值，将弹出的元素插入到另外一个列表中并返回它； 如果列表没有元素会阻塞列表直到等待超时或发现可弹出元素为止。
4	lindex key index 
通过索引获取列表中的元素
5	linsert key before|after pivot value 
在列表的元素前或者后插入元素
6	llen key 
获取列表长度
7	lpop key 
移出并获取列表的第一个元素
8	lpush key value1 [value2] 
将一个或多个值插入到列表头部
9	lpushx key value 
将一个值插入到已存在的列表头部
10	lrange key start stop 
获取列表指定范围内的元素
11	lrem key count value 
移除列表元素
12	lset key index value 
通过索引设置列表元素的值
13	ltrim key start stop 
对一个列表进行修剪(trim)，就是说，让列表只保留指定区间内的元素，不在指定区间之内的元素都将被删除。
14	rpop key 
移除并获取列表最后一个元素
15	rpoplpush source destination 
移除列表的最后一个元素，并将该元素添加到另一个列表并返回
16	rpush key value1 [value2] 
在列表中添加一个或多个值
17	rpushx key value 
为已存在的列表添加值

//set

1	sadd key member1 [member2] 
向集合添加一个或多个成员
2	scard key 
获取集合的成员数
3	sdiff key1 [key2] 
返回给定所有集合的差集
4	sdiffstore destination key1 [key2] 
返回给定所有集合的差集并存储在 destination 中
5	sinter key1 [key2] 
返回给定所有集合的交集
6	sinterstore destination key1 [key2] 
返回给定所有集合的交集并存储在 destination 中
7	sismember key member 
判断 member 元素是否是集合 key 的成员
8	smembers key 
返回集合中的所有成员
9	smove source destination member 
将 member 元素从 source 集合移动到 destination 集合
10	spop key 
移除并返回集合中的一个随机元素
11	srandmember key [count] 
返回集合中一个或多个随机数
12	srem key member1 [member2] 
移除集合中一个或多个成员
13	sunion key1 [key2] 
返回所有给定集合的并集
14	sunionstore destination key1 [key2] 
所有给定集合的并集存储在 destination 集合中
15	sscan key cursor [match pattern] [count count] 
迭代集合中的元素

//zset z轴有序列表
//以查询键为score  member为值  方便做区间查询 分页

1	zadd key score1 member1 [score2 member2] 
向有序集合添加一个或多个成员，或者更新已存在成员的分数
2	zcard key 
获取有序集合的成员数
3	zcount key min max 
计算在有序集合中指定区间分数的成员数
4	zincrby key increment member 
有序集合中对指定成员的分数加上增量 increment
5	zinterstore destination numkeys key [key ...] 
计算给定的一个或多个有序集的交集并将结果集存储在新的有序集合 key 中
6	zlexcount key min max 
在有序集合中计算指定字典区间内成员数量 [附加序列号]
7	zrange key start stop [withscores] 
通过索引区间返回有序集合成指定区间内的成员
    zrange add:kkd 0 -1
    
8	zrangebylex key min max [limit offset count] 
通过字典区间返回有序集合的成员
9	zrangebyscore key min max [withscores] [limit] 
通过分数返回有序集合指定区间内的成员
10	zrank key member 
返回有序集合中指定成员的索引
11	zrem key member [member ...] 
移除有序集合中的一个或多个成员
12	zremrangebylex key min max 
移除有序集合中给定的字典区间的所有成员
13	zremrangebyrank key start stop 
移除有序集合中给定的排名区间的所有成员
14	zremrangebyscore key min max 
移除有序集合中给定的分数区间的所有成员
15	zrevrange key start stop [withscores] 
返回有序集中指定区间内的成员，通过索引，分数从高到底
16	zrevrangebyscore key max min [withscores] 
返回有序集中指定分数区间内的成员，分数从高到低排序
17	zrevrank key member 
返回有序集合中指定成员的排名，有序集成员按分数值递减(从大到小)排序
18	zscore key member 
返回有序集中，成员的分数值
19	zunionstore destination numkeys key [key ...] 
计算给定的一个或多个有序集的并集，并存储在新的 key 中
20	zscan key cursor [match pattern] [count count] 
迭代有序集合中的元素（包括元素成员和元素分值）

