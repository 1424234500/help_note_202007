useradmin 
bggzr
ChinaNet-jDXY
kmk5meml

#计划
#

输入 
# 摄像头采集
# 传感器数据采集
# 声音采集

输出
# 灯光
# 语音/音乐
# 电机移动
#

思考
# 图像分析 
# 声音分析
# 自发行动输出

监控
# 远程控制输出
# 远程获取输入
# 

###############################缺少
立体固定装置
开关电路还是 推挽电路？

胶布 临时固定黏贴材料 双面胶
###########################################33







//充电宝固定装置设计
8cm
充电宝立方体
14.5 y
6.5  x
2.0  z 微曲 2.12

3cm可用
2.3 4 5
0.3 0.3 0.25 0.25 


//H桥电机模块
前进		左右前
后退		左右退

左转		左空置	右前
			左后退 	右空置
			左后退	又前

右转
左刹车
右刹车
左空置
右空置

		IN1		IN2		IN3 	 IN4
左前	1/pwm	0		
左退	0		1/pwm
左空置	0		0
左刹车	1		1


//传感器
舵机
红vcc
橙信号
灰gnd
pwm#通道12 50hz
// T 20ms
# 0.5ms--------------0 度；      
#  1.0ms------------45 度；       
# 1.5ms------------90 度；      
#  2.0ms-----------135 度；       
#  2.5ms-----------180 度


//电阻色环识别s
：棕1，红2，橙3，黄4，绿5，蓝6，紫7，灰8，白9，黑0
123 4-宽-5
eg: 红2红2黑0橙10^3=1000=1k棕误差1%  -> 220 kΩ

//声音播放器
sudo apt-get install mplayer
wget http://blog.lxx1.com/wp-content/uploads/2016/07/shero.mp3
mplayer shero.mp3


// dev/video0 驱动配置
/etc/modules中添加bcm2835-v412就可以（请注意，是v412)，但我试了，不行。
bcm2835-v4l2  是l不是1

摄像头并输出RTMP：
sudo ffmpeg -f v4l2 -i /dev/video0 \
    -c libx264 -profile:v main -preset:v fast \
    -b:v 300k -s 640x480 -r 25 \
    -an \
    -f flv -y rtmp://127.0.0.1/live/livestream


还可以使用raspivid编码后用ffmpeg转封装输出：

sudo raspivid -fl -t 0 -w 640 -h 480 -b 1200000 -fps 15 \
    -pf baseline -o - | ffmpeg -f h264 -i - \
    -c copy -an -f flv -y rtmp://127.0.0.1/live/livestream

//摄像头模块 开机状态下插拔烧坏了!!!!!!!!!!!!!!!!!!!!!!!
通过raspi-config工具更新了操作并使能摄像头之后，它会告诉树莓派摄像头已经连接成功，并增加了两个命令行工具以供用户使用摄像头。

raspistill
raspivid 
测试模块
raspistill -v -o test.jpg
raspistill -o image.jpg -t 2000
raspistill -o image.jpg  -w 1280 -h 720
raspivid -o mv.h264 -t 10000 -w 1280 -h 720
sudo apt-get install -y gpac 
MP4Box -fps 30 -add keychain.h264 keychain.mp4

500万像素
分辨率：2952×1944
摄像头参数：
CMOS尺寸：1/4英寸
视场角（Diagonal）：72度
传感器最佳像素：1080p
支持1080P 30，720P 60，640*480P 60/90 视频录像
适用场合：航拍、小车实时拍照、室内外监控、拍照、录像。。。。
尺寸：25mm × 24mm× 9MM
//引脚 gpio
1、功能物理引脚：
从左到右，从上到下：左边基数，右边偶数：1-40
2、BCM:
编号侧重CPU寄存器，根据BCM2835的GPIO寄存器编号。
3、wpi：
  编号侧重实现逻辑，把扩展GPIO端口从0开始编号，这种编号方便编程。正如图3 WiringPi一栏。


//500w  2560*1920
//Pwm模块
树莓派3有两路硬件pwm四个输出口，BCM12与18为一组，13与19为一组。

p = GPIO.PWM(12, 50) 
p.start(0)
time.sleep(0.005)  
p.ChangeDutyCycle(dc)
time.sleep(0.005)  
p.stop() 





//关机
shutdown -r now  
shutdown -h now
sudo halt
poweroff
sudo passwd walkerdust 修改密码
等只有红灯亮时拔电源





//Raspbian系统版本 更新系统： 
sudo apt-get update
sudo apt-get upgrade
//配置时区
sudo dpkg-reconfigure tzdata  
Aisa Shanghai

//配置
debian 
$sudo raspi-config
Network Options 链接wifi
Change UserPassword 修改密码 
iwlist scan
#Advanced Options 打开ssh
tf卡目录boot下新建ssh文件
链接wifi 配置
sudo vi /etc/wpa_supplicant/wpa_supplicant.conf
network={
	ssid="afldjfalkdfj"
	psk="kmkasdfkasf"
	priority=5
}
sudo vi /etc/network/interfaces
	auto lo wlan0 <eth0>
	iface wlan0 inet dhcp
	wpa_conf /etc/wpa_supplicant/wpa_supplicant.conf


sudo ifup wlan0 启用（up）wlan0端口，即寻找可用WiFi并尝试连接。
ifdown wlan0
更新源 版本问题
sudo apt-get update 
sudo vi /etc/apt/sources.list  
deb http://cz.archive.ubuntu.com/ubuntu/ lucid main

sudo apt-get install <-y> python-rpi.gpio
	
apt-cache depends vim 版本错误 vim 依赖 
sudo apt-get remove vim 卸载重装
sudo apt-get install vim 卸载重装
sudo apt-get install git	


使支持ll命令
echo "alias ll='ls -alF'" >> ~/.bashrc && source ~/.bashrc



snap install snapweb	安装
snap refresh <snap name>  更新
snap revert <snap name>  反转版本
snap find ss-qt		查找
snap find  		显示的是一些我们推荐的featured snap:
snap find --section=database	 使用--section选项来显示你最关心的领域，目前这些
section是：featured, database, internet-of-things, media, messaging and ops
snap remove ubuntu-calculator-app


交叉编译   ??
$ sudo snap install classic --devmode --edge   
$ sudo classic.create   ??
手动挂挂载 
挂载命令 
sudo mount -o uid=pi,gid=pi /dev/sda1 /mnt/udisk
用完之后卸载 
sudo umount /mnt/1GB_USB_flash
如果想开机自动挂载，而不是每次手工执行，可以编辑 /etc/fstab 文件。在末尾添加一行：
/dev/sda1 /mnt/udisk vfat rw,defaults 0 0



#安装系统并远程连接 winscp ssh
格式化 选项Option里面设置“FORMAT SIZE ADJUSTMENT”为开启ON状态；
写入镜像
默认用户名：pi
默认密码：raspberry
ubuntu
email account

ssh key{
	1424234500@qq.com
	1234qwer
	http://blog.csdn.net/yy243/article/details/53243948
	
	mkdir ~/.ssh
	echo '' > ~/.ssh/id_rsa
	
	Generating public/private rsa key pair. 
	Enter file in which to save the key (/root/.ssh/id_rsa): 
	Created directory ‘/root/.ssh’. 
	Enter passphrase (empty for no passphrase): 
	Enter same passphrase again: 
	Your identification has been saved in /root/.ssh/id_rsa. 
	Your public key has been saved in /root/.ssh/id_rsa.pub. 
	（为了避免每次进行ssh连接时都需要输入passphrase，这里可以不用输入passphrase。）
	现在你的私钥被放在了~/.ssh/id_rsa 这个文件里，而公钥被放在了 ~/.ssh/id_rsa.pub 这个文件里。
	使用ssh key的目的是使得两台机器之间建立互信，从其中一台登陆到另一台时不需要密码。具体方式如下：

	1、先在主机A上创建密钥对
	ssh-keygen -t rsa
	这时可以在主机A上看到生成的秘钥~/.ssh/id_rsa 和公钥 ~/.ssh/ id_rsa.pub
	2、把主机A的公钥放在主机B上
	scp -r /root/.ssh/id_rsa.pub 192.168.31.147:/root/.ssh/authorized_keys
	
	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@         WARNING: UNPROTECTED PRIVATE KEY FILE!          @
	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	Permissions 0666 for '/home/walker/.ssh/id_rsa' are too open.
	It is required that your private key files are NOT accessible by others.
	This private key will be ignored.
	Load key "/home/walker/.ssh/id_rsa": bad permissions
	
	意思就是说密钥权限的文件不能为777，不能被其他用户读取。
	chmod 700 id_rsa 
	 
}





3、树莓派参数：
B型：
处理器	
BroadcomBCM2835（CPU，GPU，DSP和SDRAM，USB）
CPU
ARM1176JZF-S核心（ARM11系列）700MHz
GPU
Broadcom VideoCrore IV，OpenGL ES 2.0,1080p 30 h.264/MPEG-4 AVC高清解码器
内存
512MByte
USB 2.0
2（支持USB hub扩展）
影像输出
Composite RCA（PAL & NTSC），HDMI（rev 1.3 & 1.4），raw LCD Panels via DSI 14 HDMI resolution from 640x350 to 1920x1200 plus various PAL andNTSC standards
音源输出
3.5mm插孔，HDMI
板载存储
SD/MMC/SDIO卡插槽
网络接口
10/100以太网接口
外设
8xGPIO、UART、I2C、带两个选择的SPI总线，+3.3V，+5V，ground（负极）
额定功率
700mA（3.5W）
电源输入
5V / 通过MicroUSB或GPIO头
总体尺寸
85.60 x 53.98 mm（3.370 x 2.125 in）
操作系统
Debian GNU/linux，Fedora，Arch Linux ARM，RISC OS, XBMC

B+改进
• 更多的GPIO：B+将通用输入输出引脚增加到了40个，而Model B则只有26个；
• 更多的USB：B+提供了4个USB端口，对热插拔有着更好的兼容性(Model B只有2个)；
• 支持microSD：旧款的SD卡插槽，已经被换成了更漂亮的推入式microSD卡槽；
• 更低的功耗：将线性式稳压器换成了开关式，功耗降低了0.5W到1W；
• 更好的音频：音频电路部分采用了专用的低噪供电；
• 简洁的外形：USB接口被推到了主板的一边，复合视频移到了3.5mm音频口的位置，此外还增加了4个独立的安装孔。





//专用源配置
sudo vim /etc/apt/sources.list                                                 


中科大
deb http://mirrors.ustc.edu.cn/raspbian/raspbian/ stretch main contrib non-free rpi 
清华
deb https://mirrors.tuna.tsinghua.edu.cn/raspbian/raspbian/ stretch main contrib non-free rpi
大连东软
deb http://mirrors.neusoft.edu.cn/raspbian/raspbian/ stretch main contrib non-free rpi
重庆大学
deb http://mirrors.cqu.edu.cn/Raspbian/raspbian/ stretch main contrib non-free rpi
浙江大学
deb http://mirrors.zju.edu.cn/raspbian/raspbian/ stretch main contrib non-free rpi
阿里云
deb http://mirrors.aliyun.com/raspbian/raspbian/ stretch main contrib non-free rpi 
搜狐
deb http://mirrors.sohu.com/raspbian/raspbian/ stretch main contrib non-free rpi 
元智大学（中国台湾）
deb http://ftp.cse.yzu.edu.tw/Linux/raspbian/raspbian/ stretch main contrib non-free rpi 
北陆先端科学技术大学院大学（日本知名镜像站，日常出口带宽2g）
deb http://ftp.jaist.ac.jp/raspbian/ stretch main contrib non-free rpi
牛津大学
deb http://mirror.ox.ac.uk/sites/archive.raspbian.org/archive/raspbian/  stretch main contrib non-free rpi
美国Berkely大学
deb http://mirrors.ocf.berkeley.edu/raspbian/raspbian/ stretch main contrib non-free rpi
美国俄克拉荷马大学
deb http://reflection.oss.ou.edu/raspbian/raspbian/ stretch main contrib non-free rpi
南非知名软件源
deb http://mirror.liquidtelecom.com/raspbian/raspbian/ stretch main contrib non-free rpi 
默认源（带重定向by mirrorbrain）
deb http://mirrordirector.raspbian.org/raspbian/ stretch main contrib non-free rpi
官方源
deb https://archive.raspbian.org/raspbian/ stretch main contrib non-free rpi
 