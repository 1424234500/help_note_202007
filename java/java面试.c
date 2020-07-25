
java.util.Map;它有四个实现类,分别是HashMap Hashtable LinkedHashMap 和TreeMap.

hashmap 数组链表 基于哈希表实现 hashCode()和equals()	可以调优初始容量和负载因子。 key可以为Null，value可以null  key hashcode equal
	hash冲突 导致退化链表	加载因子为0.75 超过扩容 理想状态数组 链表长度0/1
		hashmap并发环形链 多线程同时put扩容  元素都需要被重算rehash重hash transfer移动 并发导致环型链
			HashMap在put的时候，插入的元素超过了容量（由负载因子决定）的范围就会触发扩容操作，就是rehash，
			这个会重新将原数组的内容重新hash到新的扩容数组中，
			在多线程的环境下，存在同时其他的元素也在进行put操作，如果hash值相同，可能出现同时在同一数组下用链表表示，
			造成闭环，导致在get时会出现死循环，所以HashMap是线程不
ConcurrentHashMap
	initialCapacity：初始总容量，默认16
	loadFactor：加载因子，默认0.75
	concurrencyLevel：并发级别，默认16

	JDK1.7版本的ReentrantLock+Segment+HashEntry+数组链表 分段锁  Segment的大小最多65536个  concurrencyLevel/DEFAULT_CONCURRENCY_LEVEL =16  
		其中并发级别控制了Segment的个数，在一个ConcurrentHashMap创建后Segment的个数是不能变的，扩容过程过改变的是每个Segment的大小。 
		段Segment继承了重入锁ReentrantLock（AQS），每个锁控制的是一段，每个Segment越来越大，锁的粒度大 效率 退化hashtable？
		并发加锁 高并发下单 细分多key锁？
		缺点 分成很多段 浪费内存空间(不连续，碎片化) 
 	
	二次hash的方式（Segment分段 -> HashEntry）能够快速的找到查找的元素
	
	
	并发size一致性
		不加锁 多次计算ConcurrentHashMap的size 3次结果一致 
		否则 给每个Segment加上锁，然后计算ConcurrentHashMap的size返回 
	
	JDK1.8版本中synchronized+CAS+HashEntry++数组链表8/红黑树 二分红黑树查找键  加快检索 实现compareable
		
		红黑树 
			节点多时效率提升明显 占用额外空间
		为什么是synchronized
			API这个级别的，后续的性能优化空间很小 
			JDK优化 锁粗化、锁消除、锁自旋	
	并发size 计算好的，然后你size的时候直接给你
 
	
 
			
LinkedHashMap保存了记录的插入顺序 
Hashtable	synchronized kv均不为null	所有涉及到多线程操作的都加上了synchronized关键字
treemap 有序规则 基于红黑树实现。TreeMap没有调优选项，因为该树总处于平衡状态。 按自然顺序或自定义顺序遍历键(key)。
HashSet是通过HasMap来实现的 保持HashMap的Value为常量，相当于在HashMap中只对Key对象进行处理。

AtomicInteger
CAS 会出现的问题：ABA 版本号，每次修改，版本号加 1

 


链表的时间复杂度是O(n)，红黑树的时间复杂度O(logn)
static final int hash(Object key) {
    int h;
    return (key == null) ? 0 : (h = key.hashCode()) ^ (h >>> 16);
}
长度为2的n次方，这样(n-1)&hash就等价于hash%n。因为&运算的效率高于%运算



0.jvm原理  构成
类加载器 bootstrap extclassLoader appbootstrap userbootstrap
		Jvm new对象机制 堆分配 内存回收 
		class加载机制 双亲委派父类识别优先加载，避免根类加载器jdk被串改？保证了java程序的稳定性 缓存机制 	


本地方法栈（native method stack） 线程独有周期 登记native jni c栈，然后在execution engine执行的时候加载本地方法库。系统c指令编程实现

栈 栈内存 线程独有周期 栈不存在垃圾回收 局部变量 立即数
	一个方法一个栈帧 一个栈帧多条指令 多行代码
	线程结束栈就是释放了 类变量、引用类型变量、实例方法等 栈内存分配好。
	递归 压栈不当 栈溢出问题


方法区 虚拟机启动 全局共享 类信息、常量、静态变量、机器指令集（class转汇编 代码就是汇编指令集合） 不gc 类似堆永久代
	解释器：一条一条地读取，解释并且执行字节码指令。因为它一条一条地解释和执行指令，所以它可以很快地解释字节码
	即时(Just-In-Time)编译器（JIT ?）热点代码：合适的时候缓存解释编译的jni/汇编指令集合 
	native方法修饰的修饰的方法PC程序计数器为undefined 系统负责给结果 系统内核栈
	
程序计数器 线程独有周期 方法区中的方法字节码由引擎读取下一条指令，它是一个非常小的内存空间。、
	为什么有这种东西呢，大家都知道每个线程都是有一个程序计数器的，是的，相当一个指针。


堆（heap）new 堆分配 对象 gc管理 也是Java虚拟机共享区。
	main函数就是个非守护线程，虚拟机的gc就是一个守护线程 只要有任何非守护线程还没有结束，java虚拟机的实例都不会退出
 
 

#gc 是否存活
引用计数法 实现简单，效率高	无法循环依赖问题
	给对象中添加一个引用计数器，每当有一个地方引用它，计数器就加1；当引用失效，计数器就减1；任何时候计数器为0的对象就是不可能再被使用的。

可达性分析算法(标记)
	GC Roots 的对象作为起点，从这些节点开始向下搜索，节点所走过的路径称为引用链，当一个对象到 GC Roots 没有任何引用链相连的话，则证明此对象是不可用的。
	可作为GC ROOT的对象：
	栈中引用的对象，
	方法区  类的静态属性、常量引用的对象、引用的对象 
	本地方法栈中引用的对象	main入口
	
#gc 垃圾收集算法
标记-清除算法 复制算法 标记-整理算法
分代收集算法 主流的垃圾收集器都会采用分代回收算法

1:新生代	8:Eden 区＋1:Survior1(from) 区＋1:Survior2(to) 区		 比例–XX:SurvivorRatio
	new对象 Eden区 当前区满 再次new 不够 触发Minor GC 清理无效 复制算法 有效数据到新区域(能容纳的前提下)
		mv Eden&from to	复制到新区to
		to++			新区to的所有人年龄++	
		rm Eden&from 	删除旧区
		晋升老年代要求：
			年龄直到15:-XX:MaxTenuringThreshold 
			相同年龄所有对象大小的总和大于 Survivor 空间的一半
	Minor GC非常频繁，回收速度一般也比较快。

2:老年代(Tenure) 需要分配一块较大的连续内存空间直接进入（比如：字符串、数组） 避免为大对象分配内存时由于分配担保机制带来的复制而降低效率。
	标记-清除算法
	Major GC/Full GC 指发生在老年代的GC，出现了Major GC经常会伴随至少一次的Minor GC（并非绝对），Major GC的速度一般会比Minor GC的慢10倍以上。
	碎片化问题 整理

永久代 的区域（永久代使用的是JVM的堆内存空间，而元空间使用的是物理内存，直接受到本机的物理内存限制）。
	jdk6 常量直接分配到这里
	jdk8无永久代 而是元空间（Permanent）
 

#gc 垃圾收集器
如果说收集算法是内存回收的方法论，那么垃圾收集器就是内存回收的具体实现。
CMS收集器 获取最短回收停顿时间为目标的收集器。它而非常符合在注重用户体验的应用上使用。 第一款真正意义上的并发收集器，它第一次实现了让垃圾收集线程与用户线程（基本上）同时工作。
G1收集器 针对配备多颗处理器及大容量内存的机器. 以极高概率满足GC停顿时间要求的同时,还具备高吞吐量性能特征.


#java对象头
哈希码（HashCode）、GC分代年龄、锁状态标志、线程持有的锁、偏向线程 ID、偏向时间戳等

#jmm原理 并发锁 问题原理 

Java内存模型的工作逻辑，相似 CPU缓存一致性 		并发编程安全需要具备的三大特性	原子性、可见性和有序性
	#本地内存 线程都有私有工作内存
		共享变量存储于主内存中，每个线程都可以访问。
		每个线程都有私有的工作内存，或称本地内存。这只是个逻辑概念，其实质是涵盖了寄存器、缓存、编译器优化和硬件等。
		共享变量只以副本的形式，存储在本地内存中。
		线程不能直接操作主内存，只有操作了本地内存中的副本，才能刷新到主内存中。
		每个线程也不能操作其它线程的私有的本地内存 
	
	#CPU缓存
		主存复制一份到CPU缓存
		CPU缓存中读取数据并计算；
		回写主存中。

原子性
	简单的读取和赋值	a=1		atomicInteger
	非原子				a=b i++    
	原子性不一定保证可见性。比如 CAS 只解决了比较和更新的原子性的问题，要保证可见性，需要加锁或者是用 volatile 修饰变量。 
	
可见性	volatile	锁 
	通过synchronized关键字同步，锁释放前，对变量的修改刷新到主内存中；
	通过Lock接口实现类实现同步，锁unlock前，把修改刷新到主内存中；
	使用volatile关键字，当某线程修改了工作内存中的共享变量副本，直接刷新主存，并且其它线程会立刻收到共享变量副本失效的信息 使用时被迫刷新 达到一致性
	
	多线程并发i++可能比预期小 cpu多核多线程 本地内存还是cpu缓存导致 脏读写
	
有序性
	充分利用硬件性能，编译器和指令器有可能会对程序指令进行重排序 
	JMM基于一套原生Happens-before原则，来确保了多线程下一定程度的有序性。具体说来：

	程序次序规则：即便发生了重排序，在一个线程内最终的运行结果会与程序编写顺序的结果一致。
	锁定规则：先unlock再lock。即一个锁是锁定状态，需要先解锁才能再加锁。
	volatile规则：如果一个线程对volatile变量读，另一个线程对该变量写，那么写操作一定发生在读操作之前。
	传递规则：如果操作A先于B，B先于C，那么A肯定先于C。
	线程启动规则：线程的start方法先于其它操作。
	线程中断规则：必须是先有interrupt()方法调用，才有中断信号的捕获。
	线程终结规则：线程的所有操作都必须先于线程死亡。
	对象终结规则：一个对象的初始化先于对象GC之前。 
 
#Java并发线程协作jmm volatile  锁 sync和 lock 介绍 差别 公平性  抢占资源 wait sleep   threadpool
多核多线程cpu cpu-cache mem  cpu缓存一致性
 

2.锁概念 
#乐观锁 基本没人抢 读多写少
	查询 若没变则修改 	写多时会导致总是变化 而导致重新查询后 再次尝试修改 低效
	原子类（CAS Compare And Swap实现） 多线程累加器 

#悲观锁 总会有人抢我的 写多
	加锁 查询 修改  
	for update（锁定查询的行）
	synch
	
4.final 作用 初始化 闭包? 生命周期改变 子线程可见域
	java1.8的编译变得更加智能 无修改情况下 默认final	认为你只是忘记加final声明了而已。如果你重新给局部变量改变了值或引用，那就无法默认为final了
	java局部变量存储在栈上，实例变量或者静态变量存储在堆中
	java内部类访问局部变量都是通过副本的方式，可以通过显示final 
	
5.volatile 并发关键字 不cpu缓存 不本地内存 写时直接写入主存  读时直接读主存  	禁止指令重排序优化
CPU内存屏障	JMM对volatile的插入策略：
	StoreStore屏障 		volatile写 		StoreLoad屏障。
	LoadLoad屏障 		volatile读		LoadStore屏障。
 

	有限的一些情形下使用 volatile 变量替代锁（简单 性能）  原子操作 1.对变量的写操作不依赖于当前值。  2.该变量没有包含在具有其他变量的不变式中。
	可见性 : 对一个 volatile 的变量的读，总是能看到任意线程对这个变量最后的写入.
	原子性 : 对于单个 volatile 变量的读或者写具有原子性，复合操作不具有.(如 i++)
	互斥性 : 同一时刻只允许一个线程对变量进行操作.(互斥锁的特点)
	确保通过排他锁单独获得这个变量
	
	正确使用 volatile 
		模式：状态标志	仅仅是使用一个布尔状态标志，用于指示发生了一个重要的一次性事件，例如完成初始化或请求停机。
		模式：volatile bean  JavaBean 的所有数据成员都是 volatile 类型的，并且 getter 和 setter 方法必须非常普通 —— 除了获取或设置相应的属性外，不能包含任何逻辑。 
		
6.Synchronized 悲观锁 自动释放 不能被继承 尽量减少锁区间范围 jdk对此关键字的优化极大，同时语义清晰、操作简单、无需手动关闭，所以推荐使用 
 
jmm内存屏障
	当线程获取锁时，加载主存 JMM会把该线程对应的本地内存置为无效。使得被监视器保护的临界区代码必须从主内存中读取共享变量。
	当线程释放锁时，回写主存 JMM会把该线程对应的本地内存中的共享变量刷新到主内存中
	monitorenter屏障	同步代码块开始位置	同步代码块结束处和异常处	monitorexit屏障	

关键字不可继承
 
	非公平 运气获取
	原子性：可重入 下一个CPU时间片还是只能被他自己获取到，直到所有代码执行完
	可见性：获取锁时 主存加载到本地内存   解锁时 回写主存   主存一致性
	可重入性：获得一次锁之后，如果调用其它同步方法，不需要重新获取锁，可以直接使用。
	不可中断性：一旦这个锁被某线程获得，其他线程只能等待或者阻塞。Lock 锁可以中断或者退出等待（超时机制）。
	
	对于普通同步方法，锁是当前实例 this。
	对于静态同步方法，锁是当前类 XXX.class。
	对于同步方法块，锁是 synchronized 括号里配置的对象。 not null !!!
	
	JDK 1.6 效率优化 
	锁升级	主要想要避免线程阻塞切换cpu上下文 用户态和内核态切换   短时间内的自旋等待 避免切换 取舍
	无锁状态、								多线程循环尝试获取（CAS）
	偏向锁状态、							竞争不大 减少锁操作不释放	单线程？遇到竞争才会释放锁，线程不会主动释放偏向锁		关闭偏向锁：-XX:-UseBiasedLocking=false 默认进入轻量级锁	JDK5中默认关闭 	JDK6中默认开启
	轻量级锁状态、							当锁是偏向锁的时候，被另外的线程所访问，偏向锁就会升级为轻量级锁，其他线程会通过自旋的形式尝试获取锁，不会阻塞，从而提高性能 自旋消耗cpu！！！
	重量级锁状态							等待锁的线程都会进入阻塞状态	重量级锁通过对象头里的监视器 monitor 本质是依赖于 操作系统的Mutex Lock实现 
	随着竞争情况逐渐升级。锁可以升级但不能降级 
 
	阻塞 wait/notify等方法也依赖于monitor对象 只有在同步的块或者方法中才能调用wait/notify等方法，否则会抛出java.lang.IllegalMonitorStateException异常 
	用户态和内核态切换 内核调度	高消耗 线程的阻塞和唤醒需要CPU从用户态转为核心态


	自旋锁 JDK 1.4.2引入，默认关闭，但是可以使用-XX:+UseSpinning开开启，JDK1.6中默认开启。同时自旋的默认次数为10次，可以通过参数-XX:PreBlockSpin来调整。
		自旋锁适用于锁保护的临界区很小的情况，临界区很小的话，锁占用的时间就很短。自旋等待不能替代阻塞，虽然它可以避免线程切换带来的开销，但是它占用了CPU处理器的时间。如果持有锁的线程很快就释放了锁，那么自旋的效率就非常好
	自适应自旋锁	JDK 1.6引入	线程如果自旋成功了，那么下次自旋的次数会更加多，因为虚拟机认为既然上次成功了，那么此次自旋也很有可能会再次成功，那么它就会允许自旋等待持续的次数更多。反之，如果对于某个锁，很少有自旋能够成功，那么在以后要或者这个锁的时候自旋的次数会减少甚至省略掉自旋过程，以免浪费处理器资源
	JVM检测到不可能存在共享数据竞争，这是JVM会对这些同步锁进行锁消除。	锁消除的依据是逃逸分析的数据支持

	锁粗化 多个锁融合一个锁 避免频繁加锁解锁
 
	锁对象不能为空
	作用域不宜过大
	避免死锁



7.Lock	必须finally手动释放  AbstractQueuedSynchronizer(AQS) + CAS	复杂实现 可(超时)判断 分布式锁  
	AQS 提供了一个基于FIFO队列，可以用于构建锁或者其他相关同步装置的基础框架
	原理通过unsafe修改对象的标志字段 unsafe.compareAndSwapInt(this, stateOffset, expect, update);
代码级别的并发，需要使用锁实现提供的独特机制，例如：读写分离、分段、中断、共享、重入等 synchronized 不支持的机制。
	问题：多次重入  多次释放
	重入锁（ReentrantLock）	  
		公平锁（FairSync）		有序先到先得 维护顺序队列
		非公平锁（NonfairSync） sync队列
	读锁（ReadLock） 支持重进入的共享锁  读锁的存在意味着不允许其他写操作的存在 多人可同时读
	写锁（WriteLock）支持重进入的排它锁	有读不让写，有写不让读（是否等写途中不允许新的读，避免长时间等待）
	
0死锁 哲学家就餐问题
互斥条件：进程要求对所分配的资源进行排它性控制，即在一段时间内某资源仅为一进程所占用。
请求和保持条件：当进程因请求资源而阻塞时，对已获得的资源保持不放。
不剥夺条件：进程已获得的资源在未使用完之前，不能剥夺，只能在使用完时由自己释放。
环路等待条件：在发生死锁时，必然存在一个进程--资源的环形链。

预防死锁：
一次性分配所有资源12（资源编码组合状态）（破坏请求条件）
拿不到资源2就释放已有资源1（破坏请保持条件）
资源12有序分配法 释放则相反（破坏环路等待条件） 


8.ThreadPoolExecutor 
ThreadLocal  数据副本 线程切面耗时
	线程同步问题

	sleep：定时器唤醒	不释放锁
	wait： 需要在同步块里 notify随机唤醒/notifyAll唤醒所有
	park： 需要在同步块里 unpark唤醒指定
	Condition：signal随机唤醒/signalAll
	
	线程池构造 队列选择  队列容量 分工核心数评估
	拒绝策略s
	线程状态

	ExecutorService工厂制造 fixed固定数量 sing单线 sch单线周期(间隔时间or固定时间)
		ThreadPoolExecutor(int corePoolSize,		//核心数
									线程池个数=CPU的数量*CPU的使用率*（1+等待时间/计算时间）
		
                              int maximumPoolSize,	//最大数
                              long keepAliveTime,	//非核心存活时间
                              TimeUnit unit,		//时间单位
                              BlockingQueue<Runnable> workQueue,	//队列实现
									SynchronousQueue  eg:  4, 100 	    直接提交队列：没有容量，每一个插入操作都要等待一个相应的删除操作。通常使用需要将maximumPoolSize的值设置很大，否则很容易触发拒绝策略。
									ArrayBlockingQueue	有界的任务队列 
									LinkedBlockingQueue	无界(可指定容量有界)的任务队列：线程个数最大为corePoolSize，如果任务过多，则不断扩充队列，直到内存资源耗尽。
									PriorityBlockingQueue	优先任务队列：是一个无界的特殊队列，可以控制任务执行的先后顺序，而上边几个都是先进先出的策略。 
									DelayQueue 是 Delayed 元素的一个无界阻塞队列，只有在延迟期满时才能从中提取元素。该队列的头部 是延迟期满后保存时间最长的 Delayed 元素。如果延迟都还没有期满，则队列没有头部，并且 poll 将返回 null。
                              ThreadFactory threadFactory,			//工厂覆盖
                              RejectedExecutionHandler handler) 	//丢弃模式
									JDK提供的线程池拒绝策略
									策略名称	描述
									AbortPolicy	该策略会直接抛出异常，阻止系统正常 工作。线程池默认为此。
									CallerRunsPolicy	只要线程池未关闭，该策略直接在调用者线程中，运行当前被丢弃的任务。
									DiscardOledestPolicy	该策略将丢弃最老的一个请求，也就是即将被执行的一个任务，并尝试重新提交当前任务。
									DiscardPolicy	该策略默默地丢弃无法处理的任务，不予任务处理。
									
									
		添加任务corePoolSize -> workQueue -> maximumPoolSize -> handler  
			优先顺序 核心线程corePoolSize、任务队列workQueue、额外线程直到maximumPoolSize，如果三者都满了，使用handler处理被拒绝的任务。 	
			然后直到队列消费完毕才会根据adle time来关闭额外的线程!!!
			线程池复用线程 异常的线程, 不会重新放入线程池, 会删除掉 重新创建！！！！

	线程池有四种状态，分别为RUNNING、SHURDOWN、STOP、TERMINATED。
	线程池创建后处于RUNNING状态。
	调用shutdown后处于SHUTDOWN状态,正常关闭，停止接收新的任务，继续执行已经提交的任务（包含提交正在执行和提交未执行）直到完毕后自动关闭！     
	调用shutdownNow后处于STOP状态，发出interrupted以中止线程的运行。各个线程会抛出InterruptedException异常（前提是线程中运行了sleep、interrupted等方法） 队列中的任务移除并以列表形式返回
	
		如何实现线程池 所有任务执行完毕后关闭
		CountDownLatch并发计数器 实现超时等待	CountDownLatch.await(300,TimeUnit.SECONDS);
		 
		es.shutdown();  
		if(!es.awaitTermination(20,TimeUnit.SECONDS)){//20S
		   System.out.println(" 到达指定时间，还有线程没执行完，不再等待，关闭线程池! 返回剩余任务");
		   List<Obj> last = es.shutdownNow();  
		}
	当线程池处于SHUTDOWN或STOP状态，并且所有工作线程已经销毁，任务缓存队列已经清空或执行结束后，线程池被设置为TERMINATED状态。
 
9.Redis 分布式锁 其他实现的锁 缓存穿透击穿雪崩 一致性
	为什么快
		内存数据库 简单存取 单线程的IO复用模型	单线程来轮询描述符
		sds数据结构 存放字节/字符串和浮点型数据 空间换时间 避免\0空字符 len长度慢
		
		typedef struct sdshdr8 { //8表示字符串最大长度是2^8-1 （长度为255） 
			uint8_t len;//表示当前sds的长度(单位是字节)
			uint8_t alloc; //表示已为sds分配的内存大小(单位是字节)
			unsigned char flags; //用一个字节表示当前sdshdr的类型，因为有sdshdr有五种类型，所以至少需要3位来表示000:sdshdr5，001:sdshdr8，010:sdshdr16，011:sdshdr32，100:sdshdr64。高5位   用不到所以都为0。
			char buf[];//sds实际存放的位置
		}; 

	缓存穿透
	缓存没有命中-数据库也没有命中-查询失败-加剧反复查询   数据库反复查询
		缓存空对象 过期时间		存储null占用空间 取舍	一段时间的不一致性 
		
		并非全局map而低消耗预先知道数据库有没有  
		布隆过滤器（预热初始化key）	预计容量,容错率 -> 容器长度,hash个数      ?guava 性能!
		
		
	缓存击穿 
	热点数据-突然失效-并发查询数据库
		限流降级 熔断模式
		不同过期时间 避免同时失效

	缓存雪崩
	缓存宕机-大量访问导致数据库宕机
		避免宕机 redis高可用 集群主备 同城双活
		限流降级 熔断模式 成功率过低则限流 逐渐阶梯放开
		数据预热 不同过期时间 避免同时失效
		
	数据一致性
		缓存更新还是删除？ 		修改缓存value的成本较高，一般选择直接淘汰缓存。
		
		不可取 先更新/删除缓存，再修改数据库(可能失败)	多线程情况 存在缓存又被写入 

		先更新数据库，再更新/删除缓存
			功能问题：请求A和请求B进行更新操作 后来先更新缓存会导致脏A
			性能问题：读少写多的情况导致浪费，删除可迟加载  
	　　 
			功能问题：请求A和请求B进行操作 A删缓存 B查出又设置了旧缓存 导致脏旧
				解决方案：延迟双删， 删除缓存，更新数据库之后，延迟一段时间再次删除缓存（若失败? 重试几次报警记录日志=人工介入？）
					mysql主从读写分离：未主从同步时 依然有问题 延时间隔  

	一致性哈希和随机树：用于缓解万维网上热点的分布式缓存协议
		容错性和可扩展性 缓存集群分片时 都会涉及 多服务器节点 增加 删除节点后 
		如何保持旧的节点依然受理相同请求 
		如何保持新的节点列表负载均衡 数据倾斜
		取模法进行缓存时 	n%4 -> n%3   n%4 -> n%5	大多数数据的映射关系都会失效
		
		方案: 
			treemap记录serverIp的分区hash区间 hash环    打乱随机
						循环 100(s1)   200(s2)  800(s3)		1000(s2)   2000(s1)  8000(s3)	156 命中s2
			删除节点	循环 100(s1)   			800(s3)		1000(s2)  			 8000(s3)	156 命中s3	失效节点顺位到下一个相邻节点
			添加节点	循环 100(s1)   300(s4)  800(s3)		1000(s2)   3000(s4)  8000(s3)	156 命中s4	新增节点拦截下一个相邻节点    需补充缓存
			
			通过缓存key相同hash算法 拿到hashcode 去treemap里找到该hashcode的相邻的serverIp
			数据倾斜问题 serverIp的分区hash区间  记录多个虚拟节点机制 设置为32甚至更大 
	 
	高并发下单减少库存如何设计  redis缓存+分区段锁 —> 队列 -> 数据库行锁修改
		分别预热加载库存量到缓存redis的多个key num
		库存协调器 分派路由订单到 多个key 需加分布式锁! 并行加锁自减计数 并提交修改数据库的操作到 唯一队列
		队列消费 加锁数据库消费修改库存
		
		很大几率会出现有的库存块内的库存key总数消耗完了但有的还剩余
		库存协调器分配算法! 最小连接数 ip hash环 一致性 删除已无库存节点
 
	redis预热 读写分离主从问题怎么预热？？
	redis主动清理缓存策略??? 
		
90.消息队列 #kafka
解耦、异步、削峰

缺点#
系统的可用性降低
系统引入的外部依赖越多，系统越容易挂掉，本来只是A系统调用BCD三个系统接口就好，ABCD四个系统不报错整个系统会正常运行。引入了MQ之后，虽然ABCD系统没出错，但MQ挂了以后，整个系统也会崩溃。
系统的复杂性提高
引入了MQ之后，需要考虑的问题也变得多了，如何保证消息没有重复消费？如何保证消息不丢失？怎么保证消息传递的顺序？

重复消费 幂等性，就一个数据，或者一个请求，给你重复来多次，你得确保对应的数据是不会改变的，不能出错。
	数据库主键查一下
	写redis，那没问题了，反正每次都是set，天然幂等性


一致性问题
	A系统发送完消息直接返回成功，但是BCD系统之中若有系统写库失败，则会产生数据不一致的问题。
	把自己消费过的消息的offset提交一下，代表我已经消费过了
	
事务机制一搞，基本上吞吐量会下来，因为太耗性能
事务机制和cnofirm机制最大的不同在于，事务机制是同步的，你提交一个事务之后会阻塞在那儿，但是confirm机制是异步的，你发送个消息之后就可以发送下一个消息，然后那个消息rabbitmq接收了之后会异步回调你一个接口通知你这个消息接收到了。
所以一般在生产者这块避免数据丢失，都是用confirm机制的。
kafka会自动提交offset，那么只要关闭自动提交offset，在处理完之后自己手动提交offset，就可以保证数据不会丢。但是此时确实还是会重复消费，比如你刚处理完，还没提交offset，结果自己挂了，此时肯定会重复消费一次，自己保证幂等性就好了。
给这个topic设置replication.factor参数：这个值必须大于1，要求每个partition必须有至少2个副本
在kafka服务端设置min.insync.replicas参数：这个值必须大于1，这个是要求一个leader至少感知到有至少一个follower还跟自己保持联系，没掉队，这样才能确保leader挂了还有一个follower吧
在producer端设置acks=all：这个是要求每条数据，必须是写入所有replica之后，才能认为是写成功了
在producer端设置retries=MAX（很大很大很大的一个值，无限次重试的意思）：这个是要求一旦写入失败，就无限重试，卡在这里了
我们生产环境就是按照上述要求配置的，这样配置之后，至少在kafka broker端就可以保证在leader所在broker发生故障，进行leader切换时，数据不会丢失


	
10.Netty IO NIO react模式 哪些插件	cpu稀疏型  Netty In Action书籍！！！
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

	零拷贝 
		OS 层面上的 Zero-copy 通常指避免在 用户态(User-space) 与 内核态(Kernel-space) 之间来回拷贝数据
			Linux 提供的 mmap 系统调用 用户空间内存相互映射内核空间内存 不需要在 用户态(User-space) 与 内核态(Kernel-space) 之间拷贝数据, 提高了数据传输的效率.
		Netty 中的 Zero-copy不太一样 完全是在用户态(Java 层面) 优化数据操作   仿真C内存模型？
			CompositeByteBuf 将多个 ByteBuf 合并为一个逻辑上的 ByteBuf, 避免了各个 ByteBuf 之间的拷贝 指针起始位置共享内存分区 
			通过FileChannel.tranferTo 实现文件传输发送到目标 Channel, 避免了传统通过循环 write 方式导致的内存拷贝问题.


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
事务隔离级别					脏读	不可重复读	幻读
读未提交（read-uncommitted）	是		是			是
不可重复读（read-committed）	否		是			是
可重复读（repeatable-read）		否		否			是
串行化（serializable）			否		否			否	

mysql主从同步延时???
	Master负载过高、Slave负载过高、网络延迟、机器性能太低、MySQL配置不合理。
	show slave status 命令输出的Seconds_Behind_Master参数的值来判断： 
	NULL，表示io_thread或是sql_thread有任何一个发生故障； 
B-Tree可以对<，<=，=，>，>=，BETWEEN，IN，以及不以通配符开始的LIKE使用索引。



12.dubbo zookeeper monitor 监控中心 服务治理 架构 关系  dubbo原理
	优雅下线 java shutdownHook 主动上报关闭
	



spring如何实现循环依赖
	三级缓存 1留白，2填空，3扩展

准备
cpu缓存填充?
jmm 

dubbo 设计框架 负载均衡 spi机制 zk选举 分布式锁 
 

mysql 事务、锁、索引、b+树，主从

mq，rocketmq
	为什么用
	重复消费，顺序消息，事务消息，高可用，消息丢失，挤压场景
 

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
spring bean创建过程 生命周期  父子容器
	循环依赖
		构造注入 不行
		属性方法 可以
		
springboot和springmvc区别联系
	启动流程 如何实现的自动配置



阿里一面：

自我介绍、自己做的项目和技术领域
说一下sync的底层实现，锁优化，和lock的对比
讲一下JVM参数调优详细过程
为什么这么设置？好处是什么？描述gc场景，如何去分析gc日志？
redis数据结构，使用场景，微博场景使用redis如何去设计用户关系？
线程池参数设定，为什么这么设定，作用？7大参数
spring的循环依赖如何解决？为什么要三级缓存？
优先级队列的底层原理？
阿里二面：

自我介绍一下吧
聊项目
结合你项目问你如何设计，提出漏洞，你怎么解决？如何改进，万一挂了？加一台机器有没有问题？如果我非要不出问题怎么办？
高并发下单扣库存场景如何设计
rocketMQ架构设计原理
Dubbo框架实现原理
最近读了什么书？平时怎么学习？
常用的负载均衡，该怎么用，你能说下吗？
阿里三面：

这一面主要问项目，给你的压力感比较强
结合项目问，为什么这么设计？让你去优化，你怎么优化，引导你用一个合理的更好的方式去优化，数据库的设计等
在公司做了什么事情，各个系统业务线都是做什么的，你的绩效，手写算法链表反转？
阿里四面：

JVM的主要组成部分及其作用？
JVM运行时数据区包含哪些？
JVM垃圾回收机制，何时触发MinorGC等操作
JVM的垃圾回收算法：
JVM 调优的工具？
常用的JVM调优参数？
堆栈的区别？
详细介绍一下 CMS 垃圾回收器？
怎么判断对象是否可以被回收？
新生代垃圾回收器和老生代垃圾回收器都有哪些？有什么区别？
java类加载过程?
把你知道的中间件都说一下吧（瞬间懵了一下）
 






