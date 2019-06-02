1、搭建telnet服务器

2、搭建DHCP服务器

3、搭建ＤＮＳ服务器

4、搭建sendmail服务器

5、搭建FTP服务器

6、搭建web服务器 安装 apache tomcat

7、搭建samba服务器

 

一、搭建telnet服务器

1、查看是否有telnet服务

rpm –qa|grep telnet

显示：telnet-0.17-39.el5 还需安装telnet-server-0.17-39.el5

2、挂载

mkdir /mnt/cdrom

mount –t iso9660 /dev/cdrom /mnt/cdrom

3、找到server文件夹

cd /mnt/cdrom/Server

4、安装telnet服务

ls telnet*

rpm –ivh telnet-server-0.17-39.el5.i386.rpm

5、检查安装

rpm -qa|grep telnet

6、开启23端口

chkconfig --list 查看端口是否开启

chkconfig telnet on 或 service telnet start 或 ntsysv

7、用"telnet ip地址"登录，退出ctrl + D

 

二、搭建DHCP服务器

1、查看是否有DHCP服务

rpm –qa|grep dhcpt

2、挂载

mkdir /mnt/cdrom

mount –t iso9660 /dev/cdrom /mnt/cdrom

3、找到server文件夹

cd /mnt/cdrom/Server

4、安装dhcp服务

ls dhcp*

rpm –ivh dhcp-3.05-18.el5.i386.rpm

5、检查安装。

rpm -qa|grep dhcp

6、配置文件

实例文件vi /usr/share/doc/dhcp-3.05/dhcpd.conf.sample

租约实效文件vi /var/lib/dhcpd/dhcpd.leases

复制配置文件

cp /usr/share/doc/dhcp-3.05/dhcpd.conf.sample /etc/dhcpd.conf

vi /etc/dhcpd.conf

①修改子网subnet、子网掩码netmask、路由routers、dns服务器



②可分配地址段



③租约



④为指定的计算机保留ＩＰ



7、开启端口

chkconfig --list 查看端口是否开启

chkconfig dhcpd on 或 service dhcpd start 或 ntsysv

 

三、搭建ＤＮＳ服务器

1、查看是否有dns服务

rpm –qa|grep bind

2、挂载

mkdir /mnt/cdrom

mount –t iso9660 /dev/cdrom /mnt/cdrom

3、找到server文件夹

cd /mnt/cdrom/Server

4、安装dns服务

ls bind*

rpm –ivh bind-9.3.4-10.el5.i386.rpm

rpm –ivh bind-chroot-9.3.4-10.p1.el5.i386.rpm

ls caching*

rpm –ivh caching-nameserver-9.3.4-10.p1.el5.i386.rpm

5、检查安装

rpm -qa|grep bind

rpm -qa|grep caching

6、4个配置文件

（1）cd /var/named/chroot/etc

复制主配置文件 cp -p named.caching-nameserver.conf named.conf

    vi named.conf

修改15行为 listen-on port 53 { any; }；

27行为 allow-query { any; };

（2）cd /var/named/chroot/etc

    vi named.rfc1912.zones

    修改正向、逆向文件的名称



（3）配置正向解析文件

    cd /var/named/chroot/var/named

    cp -p localdomain.zone fendou.zone（正向解析文件名）

    vi fendou.zone (正向解析文件名)



（4）配置逆向解析文件

    cd /var/named/chroot/var/named

    cp -p named.local 11.168.192（逆向解析文件名）

    vi 11.168.192（逆向解析文件名）



7、开启端口

chkconfig --list 查看端口是否开启

chkconfig named on 或 service named start 或 ntsysv

 

四、搭建sendmail服务器

    先在named.rfc1912.zones文件中添加正向、逆向区域，并在正向、逆向文件中加入相应内容。

（一）安装sendmail

1、查看是否有sendmail服务

rpm –qa|grep sendmail

2、挂载

mkdir /mnt/cdrom

mount –t iso9660 /dev/cdrom /mnt/cdrom

3、找到server文件夹

cd /mnt/cdrom/Server

4、安装sendmail服务

ls sendmail*

rpm –ivh sendmail-cf-8.13.8-2.el5.i386.rpm

rpm –ivh sendmail-doc-8.13.8-2.el5.i386.rpm

5、检查安装

rpm -qa|grep sendmail

6、配置文件

vi /etc/mail/sendmail.mc

:set nu

:116

修改Addr = 0.0.0.0 对外开放



52行 安全认证

7、mc sendmail.mc > sendmail.cf

8、vi /etc/mail/local-host-names

加入fendoul.com,保存。

在ip设置中将DNS中的hostname 改为fendou.com

9、service sendmail start

（二）安装dovecot

1、查看是否有dovecot服务

rpm –qa|grep dovecot

2、挂载

mkdir /mnt/cdrom

mount –t iso9660 /dev/cdrom /mnt/cdrom

3、找到server文件夹

cd /mnt/cdrom/Server

4、安装dovecot服务

rpm –ivh perl-DBI-1.5.2-2.el5.i386.rpm

rpm –ivh mysql-5.045-7.el5.i386.rpm

rpm –ivh postgresql-libs-8.1.11-1.el5_1.1.i386.rpm

rpm –ivh dovecot-1.0.7-7.el5.i386.rpm

5、检查安装

rpm -qa|grep dovecot

6、配置文件

vi /etc/dovecot.conf

:set nu

:20

去掉20行前面的 #

改为protocols = imp imps pop3 pop3s

7、开启服务

service named start

service sendmail start

service dovecot start

（三）使用sendmail发送邮件

1、创建用户

    useradd -g mail -s /sbin/nologin test1 不具有登录权限

    passwd test1

    useradd -g mail -s /sbin/nologin test2

    passwd test2

2、发送邮件



3、查看邮件

vi /var/spool/mail/test2 或 vi /var/spool/mail/root

 

五、搭建FTP服务器

1、查看是否有FTP服务

rpm –qa|grep vsftp

2、挂载

mkdir /mnt/cdrom

mount –t iso9660 /dev/cdrom /mnt/cdrom

3、找到server文件夹

cd /mnt/cdrom/Server

4、安装vsftp服务

ls vsftp*

rpm –ivh vsftpd-2.0.5-12.el5.i386.rpm

5、检查安装

rpm -qa|grep vsftp

6、配置文件

vi /etc/vsftpd/vsftpd.conf

允许匿名登录

本地登录 

允许写 

权限  

项目说明：

(1)连接选项

    listen_address

    listen_port

(2)超时选项

57行：    idle_session_timeout

(3)负载控制

    max_clients 最大登录用户数

    max_per_ip 同一ip下的链接数

    anon_max_rate 匿名登录最大下载速率

    user_config_dir=/etc/vsftpd/userconf/ 创建用户同名文件的存放目录

(4)用户选项

    anonymous_enable 允许匿名登录

    anon_root= /var/ftp/pub 显示用户

 

7、开启服务

chkconfig vsftpd on 或 service vsftpd start

8、使用FTP 匿名登录



 

六、搭建web服务器

    1、查看是否有HTTP服务

rpm –qa|grep httpd

2、挂载

mkdir /mnt/cdrom

mount –t iso9660 /dev/cdrom /mnt/cdrom

3、找到server文件夹

cd /mnt/cdrom/Server

4、安装httpd服务

ls httpd*

rpm –ivh apr-1.2.7-11.el5.i386.rpm

rpm –ivh postgresql-libs-8.1.11-1.el5_1.1.i386.rpm

rpm –ivh apr-util-1.2.7-7.el5.i386.rpm

rpm –ivh httpd-2.2.3-22.el5.i386.rpm

5、检查安装

rpm -qa|grep httpd

6、配置文件

vi /etc/httpd/conf/httpd.conf

①57行：ServerRoot http运行目录

②68行：TimeOut      超时

③134行：Listen          监听端口（80）

④251行：ServerAdmin 邮箱地址

⑤265行：ServerName 写域名或IP地址

⑥281行：DocumentRoot 访问网页目录

⑦391行：DirectoryIndex 默认访问的页面（首页）

⑧747行：AddDefaultCharset 默认字体编码

⑨目录设置：

<Directoryf>

    Order allow.deny

    Allow from 192.168.1.0/24

    Deny from 192.168.1.200

</Directory>

 

⑩虚拟目录：958行

<VirturalHost*: 80> 注释：*指当前本地ip地址（可不写）

    ServerName www.fendoujiaoyu.com

    DocumentRoot /var/www/html

</VirturalHost>

<VirturalHost*: 80>

    ServerName bbs.fendoujiaoyu.com

    DocumentRoot /var/www/html/pbbs

</VirturalHost>

 

7、开启服务

chkconfig httpd on 或 service httpd start

安装apache Tomcat

1、先把安装文件放到Linux下，然后找到它的目录；

cd apache+tomcat+jdk_for_linux/

2、解压缩

tar -xf apache-tomcat-5.5.27.tar.gz

3、执行

./jdk-6u1-linux-i586.bin

4、配置环境变量

cd /etc

vi profile



（1）添加以下内容：

    JAVA_HOME=/home/loocao/software/java/jdk1.6.0_01 //写上正确的路径

    JRE_HOME=$JAVA_HOME/jre

CLASSPATH=.:$ JAVA_HOME/lib:$ JRE_HOME/lib:$ CLASSPATH

PATH=$ JAVA_HOME/lib:$ JRE_HOME/lib:$ PATH

（2）在45行后添加JAVA_HOME JRE_HOME CLASSPATH

（3）:wq!保存退出。

（4）reboot 重启

（5）java -version 若显示java version "1.6.0_01"表示配置成功

（6）cd apache-tomcat-5.5.27/bin

（7）在bin下执行 ./startup.sh

                 ./shutdown.sh 关闭

 

七、搭建samba服务器

    1、查看是否有samba服务

rpm –qa|grep samba

默认安装：

    samba-common-3.0.33-3.7.el5

    samba-c l i e n t-3.0.33-3.7.el5

2、挂载

mkdir /mnt/cdrom

mount –t iso9660 /dev/cdrom /mnt/cdrom

3、找到server文件夹

cd /mnt/cdrom/Server

4、安装samba服务

ls samba*

rpm –ivh samba-3.0.33-3.7.el5.i386.rpm

rpm –ivh perl-Convert-ASN1-0.20-1.1.noarch.rpm

5、检查安装

rpm -qa|grep samba

6、配置文件

vi /etc/samba/smb.conf

（1）修改



     74行：workgroup = 组名

         75行：解释说明

         77行：另一个名字

80行：允许访问的ip及子网

分号为注释

 

（2）



101行：设置安全的（share为所有人可访问，user为指定用户访问）

（3）

         

124行： 域名可访问

        （4）



        249行：设置主目录comment = Home Directories

     250行：是否可见

        251行：是否可写

        252行：固定的用户

        253行：固定用户的域名

（5）



283行：设置主目录

284行：设置主目录路径

285行：是否设为公共

286行：是否可写

287行：是否可打印

288行：可写的列表：如 用户名+组名 ，表示用户和组成员都可写。

（6）建立主目录，并将其与所有的用户都改为在设定的组内，改权限为777；

（7）用命令testparm测试是否配置正确。

7、开启服务

service smb start

8、在Linux图形界面下，

⑴ 选择places → Connect to Server…

⑵在出现的窗口中，service type：选择windows share；

⑶在server后输入ip地址，connect。

9、双击出现的smb 图标。
