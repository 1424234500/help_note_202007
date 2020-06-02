//问题场景
https://zhuanlan.zhihu.com/p/37405836
创建订单的操作，在订单创建完成之后，需要触发一系列其他的操作，比如进行用户订单数据的统计、给用户发送短信、给用户发送邮件等等，就像这样
createOrder(...){
 ...
 statOrderData(...);
 sendSMS();
 sendEmail();
}

//为何选择她
Kafka is used for building real-time data pipelines and streaming apps. It is horizontally scalable, fault-tolerant, wicked fast, and runs in production in thousands of companies.


传统的MQ大多数是基于内存做的处理，并且消费即清除掉
redis基于内存的消息队列，
	不能做到及时的持久化  
	更适用于短队列，和缓存的用处。

kafka
	基于硬盘存储且有序的保存。 
	被称为一个日志提交系统 	用于记录用户行为以及一系列日志消息，并且支持流处理
  	把一个场景的数据分配给多个系统或业务进行分析或处理
		提供了 Consumer Group 的概念，每个系统基于自己的Consumer Group 去消费数据并记录自己的消息偏移量（offset），与其他的消费者互不干涉。


//基本概念 

Producer：消息生产者，负责把产生的消息发送到Kafka服务器上。

Consumer：消息消费者，从Kafka服务器读取消息。

Consumer Group：消费者群组，每个消息消费者可以划分为一个特定的群组。

Topic： 它相当于消息的"身份标识"，消息生产者产生消息时会给它贴上一个Topic标签，当消息消费者需要读取消息时，可以根据这个Topic读取特定的数据。

Broker：Kafka集群中包含的服务器。

//环境搭建 集群 自带zookeeper
wget https://mirrors.tuna.tsinghua.edu.cn/apache/kafka/2.5.0/kafka_2.12-2.5.0.tgz





 


  


//常用配置
，生产者的配置
acks：指定了有多少个副本分区收到消息之后，生产者才算是消息写入成功

acks=0 ，生产者在成功写入消息之后是不会等待来自服务器的任何问题，也就是说中间不管出现任何问题生产者都不知道，消息也丢失了，但是这种话方式可以提高kafka的吞吐量
acks = 1 只要集群分区leader收到消息那么生产者就会收到一个kafka的成功响应，为了避免消息丢失生产者会重试，但是如果这个时候分区leader宕机了，在分区leader选举出来之前，消息依然会丢失
acks = all，当所有的分区follower和分区leader都收到消息之后就才会给到成功响应，他保证不止一台服务器收到消息，尽管此时有broker宕机，也能保证整个服务是可用的，并且数据一致
timeout.ms： 和acks对应如果在设定时间内没有收到所有的分区follower和leader的响应，则会抛出超时

buffer.memory：缓存区大小，如果生产者写入速度超过发送到服务器的速度，会导致生产者空间不足。这个时候要么抛出一个异常要么send方法被阻塞
这里可以设置阻塞的时间block.on.buffer.full （0.9 之前），max.block.ms（0.9之后）

compression.type：发送消息时是否压缩，默认是不会压缩的。这里提供选择压缩算法

snappy cpu占用少
gzip 压缩比更高
lz4
retries：生产者收到临时性错误，此参数决定了生产者重试次数，达到这个次数会放弃重试
默认情况下重试间隔是100ms，可以通过retry.backoff.ms来设置间隔时间大小
出现临时性错误比如，leader未选举出来。

batch.size：多个消息发送到同一个分区的时候生产者，会把他们放在同一个批次内，此参数指定批次使用内存大小，批次满了之后，会把所有的消息发送出去。如果设置太小，这里就会更频繁的发送消息

linger.ms：发送消息之前等待更多的消息加入批次的时间，增加更大，每次多送一些消息，增大吞吐量，会稍有延时

max.in.flight.requests.per.connection：此参数决定了生产者收到响应之前可以发送多少个消息，值越高内存越高，吞吐量随之提升设置为1，可以保证所有消息都是按照发送的顺序写入服务，无论中间是否出现重试

request.timeout.ms：指定生产者发送数据时等待服务器的响应时间

metadata.fetch.timeout.ms：
生产者获取元数据时候等待服务器的响应时间，（比如找到分区的leader是哪台broker）

mac.block.ms：
发送消息时候获取元数据的阻塞时间，到达时间抛出超时异常

max.request.size：
此参数设置生产者发送请求的大小，与broker节点的配置message.max.bytes匹配

2，消费者的配置
fetch.min.bytes：broker在收到消费者的拉取数据请求时，可用的数据量少于fetch.min.bytes的指定大小，那么他会等到有足够的大小的时候才返回给消费者，降低消费这和broker工作负载如果当在整个topic不活跃时段，就不需要一直处理消息，可以调整稍大降低工作负载

fetch.max.wait.ms：通过fetch.min.bytes这个属性设置要足够的数据返回给消费者，而此属性，则指定broker的等待时间，默认500ms，如果没有足够的数据大小，最终导致500ms的延迟。要么满足等待时间，要么满足设定的大小。

max.partition.fetch.bytes：此属性指定了返回给消费者的最大字节数，默认1MB。
poll方法从每个分区拉取数据最多不超过max.partition.fetch.bytes 指定的字节
max.partition.fetch.bytes 能够比broker的max.message.size属性大，
否则消费者可能无法读取这些消息。

session.timeout.ms：指定在消费者死亡之前与服务器断开连接的时间，默认3s
如果消费者没有在指定的时间内发送心跳给群组协调器，就被认为死亡，此时会触发再均衡
此属性与heartbeat.interval.ms 相关，heartbeat.interval.ms指定了poll方法向协调器发送心跳的频率，heartbeat.interval.ms必须要比session.timeout.ms小，一般1:3。
此属性设置时间断可以更快的检测宕机消费者，不过可能导致意外过多的再均衡。

auto.offset.reset：该属性指定了消费者在一个没有偏移量分区，或者偏移量无效的情况下如果处理latest在偏移量无效的情况下，从最新的开始读取，earliest 在偏移量无效时候从最新的开始读取

enable.auto.commit：是否自动提交偏移量，如果是true 可以通过auto.commit.interval.ms 来控制提交偏移量的提交频率

partition.assignment.strategy：指定默认的分区的分配策略

Range： 分配连续的分区给消费者
RoundRobin ：均衡分配
max.poll.records
单次返回的记录数量
 



//常用指令
1. 创建Topic

使用Kafka，我们首先需要创建一个Topic，这样后续消息生产者和消息消费者才能针对性的发送和消费数据，
> bin/kafka-topics.sh --create --zookeeper localhost:2181 --replication-factor 1 --partitions 1 --topic test
这样我们就创建了一个名为test的Topic。

我们也可以通过命令来查看我们已经创建的 Topic，

> bin/kafka-topics.sh --list --zookeeper localhost:2181
test
2. 发送消息

前面介绍Kafka专业术语中已经阐述，Kafka使用过程中首先需要消息生产者发送消息，那么消费者才可以读取到消息。

启动一个终端A，执行下面命令，

> bin/kafka-console-producer.sh --broker-list localhost:9092 --topic test
>hello world
>
当执行producer脚本后，会出现消息输入提示符，这是我们可以输入消息(数据)，然后它会发送到对应的服务器(Broker)。

3. 消费消息

现在管道中已经有了数据，接下来我就可以使用消费者去读取数据。

另外启动一个终端B，执行下面命令，

> ./bin/kafka-console-consumer.sh --bootstrap-server localhost:9092 --topic test --from-beginning
hello world
可以看到，消息消费者一直处于监听状态，每当在终端A输入一条消息，终端B也会更新一条消息。





//java接入
创建一个kafka的producer
Properties props = new Properties();
props.put("bootstrap.servers", "url:port");
props.put("key.deserializer", "org.apache.kafka.common.serialization.StringDeserializer");
props.put("value.deserializer", "org.apache.kafka.common.serialization.StringDeserializer");
KafkaProducer<String, String> kafkaProducer = new KafkaProducer<>(props);

发送消息到kafka

ProducerRecord<String, String> producerRecord = new ProducerRecord<>("topic1","key1","value ...");
kafkaProducer.send(producerRecord);
 

生产者三种发送消息方式：

发送-并忘记
  把消息发送给kafka之后不关心是否到达，大多数情况下是正常的，就算有问题，生产者也会自动开始重试，但是这种可能会出现丢失数据
同步发送
 是用send发送返回一个Future对象，调用get方法开始等待kafka返回结果，此方法会降低kafka吞吐量
ProducerRecord<String, String> producerRecord = new ProducerRecord<>("topic1","key1","value ...");
kafkaProducer.send(producerRecord).get();
异步发送
 调用send方法指定回调函数，服务器响应时会调用该函数
class KafkaProducerCallback implements Callback {
    @Override
    public void onCompletion(RecordMetadata recordMetadata, Exception e) {
      if (e == null) {
        System.out.println(recordMetadata.offset());
        System.out.println(recordMetadata.partition());
      } else {
        e.printStackTrace();
      }
    }
}
        
ProducerRecord<String, String> producerRecord = new ProducerRecord<>("topic1", "key1", "value ...");
kafkaProducer.send(producerRecord, new KafkaProducerCallback());
 
消费者订阅消息，并且按照partition内消息生产的顺序读取，消费者通过offset来区分是否已经读取过，消费者会把每个分区的最后读取的offset保存在 “_consumer_offset ”这个topic上，这时候消费者如果宕机，不会丢失掉读取的记录。

消费组是由若干个消费者组成的，主题当中每一个分区只会被消费组当中一个消费者消费，如果一个消费者宕机之后会有另外一个消费者接替消费，这种分区对应消费者的关系在这里叫作所有权。

一个分区只会分配给一个消费者当消费者的数量大于分区数，那么这个时候多余的消费者则会闲置。

消费者的再均衡
      分区的所有权转交给另外一个消费者叫作再均衡（比如一个消费者宕机了，另外一个消费者就会继续接替他的分区，继续消费）以此机制消费者有更好的伸缩性，高可用，消费者通过像群组协调器的broker发送心跳来维持他们和消费组的从属关系，和分区所有权关系，如果消费者的心跳断掉之后，那么群组协调器（后面的文章会讲到）会触发一次再均衡

 集群由多个broker组成，主题分为多个分区，一个分区会在多个broker上，多个broker上的分区会有一个分区leader，该分区leader负责处理生产者和消费者对于该分区的请求。除了这个分区leader，其他的broker上的该分区称为follower（追随者），follower的主要工作是从leader分区当中复制消息，当分区中的leader节点宕机之后，会由若干个follower当中选举一个新的分区leader，依照消费者图改造一下如下图。
 



