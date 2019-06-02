//wireshark抓包工具

安装wireshark winCap

//获取程序exe的tcp port
tasklist 获取程序pid
netstat -ano  tcp/udp-port -> pid -> exe


//过滤器使用
ip地址过滤
ip.addr == 122.19.45.122
即会显示与这个ip之间的通信 包括 tcp/udp 三次握手 http 数据包

协议过滤
http 
tcp
udp
telnet


tcp dst port 3128  //捕捉目的TCP端口为3128的封包。
ip src host 10.1.1.1  //捕捉来源IP地址为10.1.1.1的封包。
host 10.1.2.3  //捕捉目的或来源IP地址为10.1.2.3的封包。
ether host e0-05-c5-44-b1-3c //捕捉目的或来源MAC地址为e0-05-c5-44-b1-3c的封包。如果你想抓本机与所有外网通讯的数据包时，可以将这里的mac地址换成路由的mac地址即可。
src portrange 2000-2500  //捕捉来源为UDP或TCP，并且端口号在2000至2500范围内的封包。
not imcp  //显示除了icmp以外的所有封包。（icmp通常被ping工具使用）
src host 10.7.2.12 and not dst net 10.200.0.0/16 //显示来源IP地址为10.7.2.12，但目的地不是10.200.0.0/16的封包。
(src host 10.4.1.12 or src net 10.6.0.0/16) and tcp dst portrange 200-10000 and dst net 10.0.0.0/8  //捕捉来源IP为10.4.1.12或者来源网络为10.6.0.0/16，目的地TCP端口号在200至10000之间，并且目的位于网络 10.0.0.0/8内的所有封包。
src net 192.168.0.0/24 
src net 192.168.0.0 mask 255.255.255.0  //捕捉源地址为192.168.0.0网络内的所有封包。

tcp.port == 25  //显示来源或目的TCP端口号为25的封包。 
tcp.dstport == 25  //显示目的TCP端口号为25的封包。 
tcp.flags  //显示包含TCP标志的封包。 
tcp.flags.syn == 0×02  //显示包含TCP SYN标志的封包。 

英文语法 或者 c语法
eq ==
ne !=
gt >
lt <
ge >=
le <=
and &&
or ||
xor ^^ 异或
not !

//大多数防火墙已知 SYN/FIN 包, 别的一些组合,例如SYN/FIN/PSH, SYN/FIN/RST, SYN/FIN/RST/PSH。很明显，当网络中出现这种包时，很你的网络肯定受到攻击了。

//阅读tcp/udp包 
TCP包，然后选择Wireshark工具栏菜单的"Following TCP Streams"选项
跟踪流
解码数据为ascll hex c 


//包分析
0000   18 31 bf 4e 20 2b 78 44 fd 40 b9 bd 08 00 45 00  .1.N +xD.@....E.
    [len 139] 同时说明是高位前置 大端模式
0010   00 8b 07 d8 40 00 74 06 b0 65 b7 02 d6 7a c0 a8  ....@.t..e...z..
0020   00 0a 75 32 f6 bb 7f 7a f1 93 70 03 10 c1 50 18  ..u2...z..p...P.
0030   1a 62 17 be 00 00 26 11 00 00 29 94 98 b5 85 11  .b....&...).....
0040   4b 4e 1e 08 1f 08 00 11 11 00 00 29 94 98 b5 85  KN.........)....
0050   11 4b 4e 81 97 1f 08 00 18 18 00 00 29 94 98 b5  .KN.........)...
0060   6f d5 65 43 14 2d 1d a4 0f 81 32 31 39 39 51 54  o.eC.-....2199QT
0070   15 11 00 00 29 94 98 b5 85 11 4b 4e 63 4c 2e 00  ....).....KNcL..
0080   00 18 18 00 00 29 94 98 b5 6f d5 65 43 14 2d 1d  .....)...o.eC.-.
0090   b3 18 81 32 31 39 39 51 54                       ...2199QT



//配置捕获
Interface：指定在哪个接口（网卡）上抓包（系统会自动选择一块网卡）。

Limit each packet：限制每个包的大小，缺省情况不限制。

Capture packets in promiscuous mode：是否打开混杂模式。如果打开，抓   取所有的数据包。一般情况下只需要监听本机收到或者发出的包，因此应该关闭这个选项。

Filter：过滤器。只抓取满足过滤规则的包。

File：可输入文件名称将抓到的包写到指定的文件中。

Use ring buffer： 是否使用循环缓冲。缺省情况下不使用，即一直抓包。循环缓冲只有在写文件的时候才有效。如果使用了循环缓冲，还需要设置文件的数目，文件多大时回卷。

Update list of packets in real time：如果复选框被选中，可以使每个数据包在被截获时就实时显示出来，而不是在嗅探过程结束之后才显示所有截获的数据包。







