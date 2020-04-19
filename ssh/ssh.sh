####ssh scp putty<终端>  依靠ip/端口/用户名密码 远程登录
#scp命令传输上传下载文件 
####上传文件
scp -p xxx.gz icbcmon@122.1.2.3:/approot/
scp -p xxx.jar walker@39.106.111.11:/home/walker/
####下载 文件<夹>  到/root
scp <-r> root@43.224.34.73:/home/lk /root
scp -r walker@39.106.111.11:/home/walker/apache-tomcat-8.5.42/webapps/walker-web/WEB-INF/classes/com/walker/web/controller /home/walker/e/workspace/ssmcopy

    -1  强制scp命令使用协议ssh1  
    -2  强制scp命令使用协议ssh2  
    -B  使用批处理模式（传输过程中不询问传输口令或短语）  
    -C  允许压缩。（将-C标志传递给ssh，从而打开压缩功能）  
    -p 保留原文件的修改时间，访问时间和访问权限。  
    -q  不显示传输进度条。  
    -r  递归复制整个目录。  
    -v 详细方式显示输出。
    
####免密码登录sshpass
apt-get install sshpass
wget http://sourceforge.net/projects/sshpass/files/sshpass/1.05/sshpass-1.05.tar.gz  
tar xvzf sshpass-1.05.tar.gz  
./configure 
make  
make install
 -p "XXX" ssh user@IP
####首次需要ssh 直接登录一次 
####之后才能使用sshpass登录?
#ssh密钥配置
ssh-keygen -t rsa -P '' -f ~/.ssh/id_rsa
参数说明： 
-t 加密算法类型，这里是使用rsa算法 
-P 指定私钥的密码，不需要可以不指定 
-f 指定生成秘钥对保持的位置 
#server config   配置允许ssh信任
sudo vim /etc/ssh/sshd_config
    RSAAuthentication yes 
    PubkeyAuthentication yes 
    AuthorizedKeysFile %h/.ssh/authorized_keys
	#不配置默认#StrictModes yes 
	StrictModes no		
#create pub and private key
ssh-keygen -t rsa   	
ssh-add ~/.ssh/id_rsa
cat ~/.ssh/id_rsa.pub >> ~/.ssh/authorized_keys
chmod 644 ~/.ssh/authorized_keys
chmod 700 ~/.ssh
>restart
service ssh restart        
service sshd restart   
/etc/init.d/ssh restart
>check
ssh localhost 
//client config 自动化ssh密钥免密码
ssh-keygen -t rsa 
######ss客户端公钥发送个服务端 追加到服务端对应用户的  ~/.ssh/authorized_keys
ssh root@127.23.1.2 'mkdir -p ~/.ssh && cat >> ~/.ssh/authorized_keys' < ~/.ssh/id_rsa.pub 
||
ssh-copy-id root@127.23.1.2
||
scp ~/.ssh/id_rsa.pub icbcmon@122.1.2.3:/approot/id_rsa.pub.new
ssh root@127.23.1.2 "cat ~/.ssh/id_rsa.pub.new >> ~/.ssh/authorized_keys"        


##ssh 远程登录 和 执行命令 
#环境变量特殊 java!!!!!!!!自行导入相关软件指令
它不会去执行/etc/profile文件，而会去用户的HOME目录检查.bashrc并加载
vim ~/.bashrc       #当前用户
export JAVA_HOME=/approot/jdk1.8.0_171 && export CLASSPATH=$JAVA_HOME/bin && export PATH=$PATH:$CLASSPATH

ssh username@127.23.1.2 "ls -lth /home/walker | grep hello "        
ssh username@127.23.1.2 < fff.sh >ssh file download
ssh user@host 'tar cz src' | tar xzv
cd && tar czv src | ssh user@host 'tar xz'


配置了秘钥登陆，免去输入密码，但是第一次登陆时会有一个提示动作
The authenticity of host ‘192.168.10.14 (192.168.10.14)’ can’t be established.
ECDSA key fingerprint is SHA256:zCrwLrWV8zc9FMtIt0C+bV+CR3yfEcXsgpSSD4/x2yk.
ECDSA key fingerprint is MD5:6b:a0:a2:ab:08:c0:33:b1:df:2f:63:f0:9d:ba:9c:1f.
Are you sure you want to continue connecting (yes/no)?

通过ssh指定参数 StrictHostKeyChecking no 可以跳过检查，或者改ssh配置文件。
这里选择跳过：
ssh -o “StrictHostKeyChecking no” root@192.168.10.14


# -A 开启认证代理连接转发功能
# -C 表示对所有的输入输出都压缩，使用的是gzip压缩
# -N 表示不执行远程指令
# -f 表示后台执行ssh指令,一般 Nf 一起使用就可以不登录远程服务器了
# -L 表示建立本地隧道
ssh -A -CNfL 8888:127.0.0.1:8080 root@目标服务器


1. -D 动态隧道
通过 -D 参数，我们可以实现一个简单的代理服务器。
命令格式：
ssh -D [bind_address:]port root@服务器ip
在平常，我们的电脑是无法访问谷歌的，但是现在我们手上有一台服务器A可以访问谷歌。现在我们就可以通过ssh -D来让服务器A变成一个代理服务器，从而让我们的电脑可以访问谷歌。
# 绑定本地的8080端口，后面发往8080端口的请求都会通过ssh隧道发给服务器A，由服务器Alain进行请求后再将响应返回给我们
ssh -D 127.0.0.1:8080 root@服务器A的ip

之后我们需要设置一下浏览器的代理，地址使用127.0.0.1:8080。之后浏览器的请求都会走向8080端口，到8080端口后，经过ssh隧道发向服务器A，服务器把这个请求发往目标服务器，之后拿到响应内容后返回给我们。整个过程就是一个正向代理的过程。
ssh的这个功能和shadowsocks的工作流程基本一样，但是笔者简单测试了下，使用ssh隧道构建的代理服务器无论是性能还是稳定性都远不如shadowsocks。具体的原因笔者也没有很深入的去研究，不过可能这就是ssh动态隧道很少被人使用的原因吧。

2. -L 本地隧道
本地隧道也叫正向隧道，通过本地隧道，我们可以让目标服务器将我们本地的端口转发到具体其他地址的端口。
命令格式：
ssh -L [bind_address:]port:host:hostport root@服务器ip
假设我们现在有个内网服务器A上有一个进程占用8080端口，我们的电脑要访问内网服务器只能通过跳板机，也就是服务器B来访问。这时候我们要在本地访问服务器A上那个8080的进程要怎么做呢？ssh就可以帮我们做到
# 监听了本地的8888端口，所有发往8888端口的请求都会发给服务器B，服务器B再将请求发给 '服务器A的ip:8080'，之后拿到响应后返回
# 前面的127.0.0.1可以不填，不填的话默认就是绑定在127.0.0.1上面
ssh -L [127.0.0.1:]8888:服务器A的ip:8080 root@服务器B的ip
执行了上面的命令后，我们就可以直接通过127.0.0.1:8888就可以访问服务器A上的那个8080的进程。本地隧道建立后，所有发往127.0.0.1:8888地址的请求都会通过隧道发给服务器B，然后服务器B帮我们把请求发给配置好的服务器A的ip:8080，之后拿到请求返回给我们。
为了更好的理解本地隧道的工作原理，我们再模拟一个场景。假设我们现在可以直接访问服务器A的网络，但是A的8080端口并不对外开放，我们只能通过ssh协议登陆服务器。这时候应该怎么配置ssh隧道来访问8080端口呢？
# 那个'127.0.0.1:8080'配置的是服务器A要转发的地址，以服务器A的角度来看，要访问的就是127.0.0.1的8080端口
ssh -L [127.0.0.1:]8888:127.0.0.1:8080 root@服务器A的ip
1
2
看到上面的配置，如果不知道本地隧道的转发原理的可能会比较懵。
前面的[127.0.0.1:]8888配置了要监听的地址端口。接着127.0.0.1:8080我们可以理解为只是配置一个地址，来告诉远程的服务器等会要把请求发到哪个地址。我们现在是把服务器A来当代理服务器，也就是服务器A接收到隧道传过来的请求后，就直接把对应的配置127.0.0.1:8080拿到，往这个地址转发。因此，后面那个配的是目标服务器要访问的地址。
可以看出，本地隧道玩的是反向代理。
3. -R 远程隧道 —— 内网穿透
远程隧道，也可以称为反向隧道。通过远程隧道，我们可以实现内网穿透。
命令格式：
ssh -R [bind_address:]port:host:hostport root@服务器ip
# bind_address 表示远程服务器绑定的ip地址。不过经笔者测试，这个参数好像并没有什么用，无论填什么都不会改变监听地址
# port 远程服务器要监听的端口
# host 要转发的ip地址。后面会在本地去访问这个ip
# hostport 要转发的端口
由于ipv4资源的紧缺，我们上网分配到的ip一般都是内网ip，由于是内网ip，其他局域网以外的服务器就没办法访问到我们的电脑了。
如果我们在自己的电脑上部署了一个网站，想要其他人可以访问到，就需要用到内网穿透的功能。用ssh的隧道加一个有公网ip的服务器，我们就可以实现内网穿透。
假设我们本地部署了一个网站，占用端口8080，手上有一个服务器A，我们可以这么配置：
# 在服务器A上面监听一个8888的端口，之后只要有人访问端口8888，ssh将会将请求经过隧道发送给我们的电脑上
# 之后我们的电脑就把请求发给配置好的地址 '127.0.0.1:8080'上，然后把响应内容返回给调用者。
ssh -R 8888:127.0.0.1:8080 root@服务器A
这个和本地隧道其实就是反过来的关系。访问者把请求发到远程服务器，然后远程服务器把请求转发到本地，本地通过配置好的地址去转发请求，最后返回结果。也就是说，后面配置的’127.0.0.1:8080’是以本地电脑的身份去访问的，所以可以实现内网穿透。
显然，远程隧道也是属于反向代理的一种。
使用远程隧道时要注意，一般云服务器上的ssh服务默认是禁止做远程隧道转发的。当我们执行上诉命令时，它会只绑定自己的回环ip 127.0.0.1，这样外部的访问就无法访问到我们绑定的端口了，就不能达到内网穿透的功能了。
通过编辑sshd的配置文件我们可以将ip绑定到0.0.0.0上，使所有人都可以访问这个端口。
vim /etc/ssh/sshd_config
# 将对应的配置项 GatewayPorts 的值修改成 yes
GatewayPorts yes

/etc/rc.d/init.d/ssh restart
或者
sevice ssh restart
restart 包括了stop，start。

 

