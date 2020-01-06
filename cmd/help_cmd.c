#
#	bat 编程
#
cmd路径 \ 反斜杠 linux
1.start b.bat 新开cmd窗口 
2.call b.bat 不显示 路径执行  命令/bat 等待后续
3.b.bat 直接调用exe终止 当前bat后续代码 而 call不会

%1% 取出第一个参数

字符串替换
@echo off REM 字符串替换 set str=待替换文本信息XXX echo 对“%str%”中的“XXX”进行替换，替换为“YYY” REM 替换str中的XXX为YYY set str2=%str:XXX=YYY% echo - echo 替换后为：%str2% echo - pause

IF /? 帮助文档 命令介绍

分支控制 EQU NEQ LSS LEQ GTR GEQ
IF EXIST FILENAME. （
    del filename.
) ELSE （
    echo filename. missing.
)

for
for  %%I in (ABC) do echo %%I
pause

@echo off
set num=0
:ok
set /a num+=1
echo.test-%num%
if "%num%"=="10" pause&&echo.over！
goto ok


tasklist | find /i "node.exe" && taskkill /f /t /im node.exe

tasklist | find /i "node.exe" || start "node" node proxy.js 

copy  复制文件
xcopy 复制文件夹

等待耗时sleep
TIMEOUT /T 2


文件搜索grep ?
find /?
    文件目录检索批量 文本关键词
    find /I /N "keys" *



计算机管理
任务计划程序
启动配置
msconfig


//双网卡设置
无线局域网适配器 WLAN 2: 内网
   连接特定的 DNS 后缀 . . . . . . . :
   本地链接 IPv6 地址. . . . . . . . : fe80::dda8:653d:8109:5298%22
192.168.2.90
255.255.255.0
192.168.2.1

无线局域网适配器 WLAN: 外网
   连接特定的 DNS 后缀 . . . . . . . :
   本地链接 IPv6 地址. . . . . . . . : fe80::5156:591e:35a0:92e0%7
192.168.104.235
255.255.255.0
192.168.104.254

//重置ipv4 避免127.0.0.1失效问题
netsh int ip reset
设置内网静态ip 掩码 不要网关！！    dns解析服务器 114.114.114.114 
设置外网自动ip 自动掩码 自动网关
接下来的route应该会有一个0.0.0.0外网路由
// 0.0.0.0          0.0.0.0  192.168.104.254   192.168.104.77     55
// 0.0.0.0          0.0.0.0      192.168.2.1     192.168.2.24     50
配置路由
route delete 0.0.0.0 //设置了网关就得删除默认路由 网关==路由 (-p 永久有效 异常?)  
//配置映射 路由  192.168.2.*->192.168.2.1 内网配置路由
route -p add 192.168.2.0 mask 255.255.255.0 192.168.2.1
route -p add 122.0.0.0 mask 255.0.0.0 192.168.2.1

route delete 192.168.2.0
route delete 122.0.0.0
//最后面 * -> 192.168.104.254 外网  默认配置
route -p add 0.0.0.0 mask 0.0.0.0 192.168.104.254  metric 400


//热点
netsh wlan set hostednetwork mode=allow ssid=dust7.11 key=9012345678
netsh wlan start hostednetwork 

//跟踪路由跳转
tracert ip
C:\WINDOWS\system32>tracert -d 122.20.61.29
通过最多 30 个跃点跟踪到 122.20.61.29 的路由
  1     1 ms    <1 毫秒    1 ms  192.168.2.1
  2     2 ms     2 ms     1 ms  84.232.63.252
  3     *        *        *     请求超时。
  4     2 ms     7 ms    17 ms  84.232.4.156
  5     4 ms     3 ms     2 ms  84.15.36.161
  6     4 ms     5 ms     3 ms  84.99.20.61
  7     4 ms     4 ms     3 ms  84.99.20.10
  8    39 ms    43 ms    39 ms  84.15.36.62
  9    48 ms    42 ms    39 ms  122.63.20.6
 10    38 ms    38 ms    38 ms  122.63.4.18
 11    39 ms    40 ms    48 ms  122.20.61.29

dxdiag 查看direct 和 硬件设备信息 系统版本 windows10 专业版64(10.0, 版本 16299)

//启动路径
第一步：找到注册表的启动项位置：HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run主键
第二步：在另边点击右键：新建“字符串值”，取名“QQ”如下图：
第三步：找到你所要增加启动项的软件目录：
如我的QQ是目录是：D:\Program Files\Tencent\QQ\qq.exe
第三步：双击你刚新建军的"qq"字符串值项,即：
编辑字符串数值数据：将第三步找到的软件目录复制到下面图的“数值数据栏内” 
确定后，关闭注册表，OK，你的XP系统启动项设置成功了
P.S. 
1.Run键r
　　Run键是病毒最青睐的自启动之所，该键位置是[HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run]和[HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Run]，其下的所有程序在每次启动登录时都会按顺序自动执行。
　　还有一个不被注意的Run键，位于注册表[HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer\Run]和[HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\Explorer\Run]，也要仔细查看。

　　2.RunOnce键
　　RunOnce位于[HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\RunOnce]和[HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\RunOnce]键，与Run不同的是，RunOnce下的程序仅会被自动执行一次。

　　3.RunServicesOnce键
　　RunServicesOnce键位于[HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\RunServicesOnce]和[HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\RunServicesOnce]下，其中的程序会在系统加载时自动启动执行一次




//dns树 本机-hosts  ->  ip配置 dns -> other dns
//域名-ip转换表 
C:\Windows\System32\drivers\etc\hosts

ipconfig /flushdns  //fulush refresh
//ip-mac转换表(!rarp) 该命令显示和修改“地址解析协议 (ARP)”缓存中的项目。ARP 缓存中包含一个或多个表，它们用于存储 IP 地址及其经过解析的以太网或令牌环物理地址。 
arp -a 

ping -a ip  ping -a 将地址解析为计算机名。用户名
nbtstat -a ip 来获得更详细的信息，包括计算机的名称已经硬件Mac地址，这样不论他们怎么变化遁形，都逃不过你的法眼啦，赶紧试试吧。

ping 目标计算机名
nbtstat -a 目标计算机名（可以省去）
////////////////////ip和用户名互转

ping -l 1472 -f www.baidu.com //mtu 不分包测试 1500默认 = 1472 + 28 = 8icmp 20ip
ping中"-l"指定的是IP包中数据净荷的长度,加上8字节的ICMP封装和20字节的IP报头
1、查看自己当前网络的 MTU 值，请命令提示符下输入以下命令并回车：
netsh interface ipv4 show subinterfaces

runas /user:administrator "cmd /k"



netplwiz”打开“用户账户”面板




重置网络连接
netsh int ip reset
netsh winhttp reset proxy
ipconfig /flushdns
重置winsock
netsh winsock reset
1366X768
“开始”--输入“regedit”依次找到：
HKEY_LOCAL_MACHINE/SYSTEM/ControlSet001/Control/GraphicsDrivers/Configuration

然后右键点击Configuration，选择查找，输入Scaling，在右框内即可看到scaling，
右键scaling选择修改，将数值改为3即可。

gpedit.msc
计算机配置"-"windows设置"-"安全设置"
-"软件设置策略",右击"软件设置策略"点"新建策略"-"其它规则"-右击"其它规则"-"新路径规则把你要阻止的某些软件放在一个盘里面就OK了..


//端口开放 入站规则
1、点开始——控制面板；
2、点系统和安全；
3、点Windows防火墙；
4、点高级设置；
5、点入站规则，点新建规则；

方法一：利用注册表
　　1、按下Win+R组合键，在运行命令中输入“regedit”回车。
　　2、在出现的注册表编辑器界面，依次展开
HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\NlaSvc\Parameters\Internet，点击选中Internet项目后，右侧窗口找到“EnableActiveProbing”值，双击打开编辑AWORD（32位）值对话框。
　　3、在编辑AWORD（32位）值对话框，将数值数据修改成“0（默认为1）”，完成后，点击确定保存即可，再次重启电脑，宽带连接成功后就不会再出现自动登陆的界面了！
　　方法二：利用本地组策略编辑器
　　原理是一样的，都是禁用Windows网络连接状态指示器活动测试。
　　1、按下Win+R组合键，在运行命令中输入“gpedit.msc”后回车（参考方法一）。
　　2、在本地组策略编辑器界面，依次展开计算机配置-》管理模板-》系统-》Internet通信管理，然后单击选中“Internet 通信设置”后，在右侧窗口找到并双击“关闭Windows网络连接状态指示器活动测试”。
　　3、在关闭Windows网络连接状态指示器活动测试对话框，点击选择左上角“已启用”，然后点击确定，退出设置界面即可。
　　以上就是Win8.1系统如何禁止连接宽带后自动打开微软网页的介绍了，使用这两个方法都能有效地防止微软网页自动打开
netstat -ano，列出所有端口的情况。在列表中我们观察被占用的端口
查看被占用端口对应的PID，：netstat -aon|findstr "49157"
输入tasklist|findstr "2720"，回车，查看是哪个进程或者程序占用了2720端口，结果是：svchost.exe
taskkill /f /t /im Tencentdl.exe。

Win+R，然后在弹出面板中输入“netplwiz”打开“用户账户”面板，接下来取消面板顶端的“要使用本计算机，用户必须输入用户名和密码”复选框并确定。这
cls

shutdown -h now 关闭系统(1) 
　　init 0 关闭系统(2) 
　　telinit 0 关闭系统(3) 
　　shutdown -h hours:minutes & 按预定时间关闭系统 
　　shutdown -c 取消按预定时间关闭系统 
　　shutdown -r now 重启(1) 
　　reboot 重启(2) 
　　logout 注销
　　
dir /?
    dir /N /S /A:-L-S-H-D


cd /home 进入 '/ home' 目录' 
　　cd .. 返回上一级目录 
　　cd ../.. 返回上两级目录 
　　 
 
文件系统

mount /dev/hda2 /mnt/hda2 挂载一个叫做hda2的盘 - 确定目录 '/ mnt/hda2' 已经存在 
　　umount /dev/hda2 卸载一个叫做hda2的盘 - 先从挂载点 '/ mnt/hda2' 退出 
　　fuser -km /mnt/hda2 当设备繁忙时强制卸载 
　　umount -n /mnt/hda2 运行卸载操作而不写入 /etc/mtab 文件- 当文件为只读或当磁盘写满时非常有用 
　　mount /dev/fd0 /mnt/floppy 挂载一个软盘 
　　mount /dev/cdrom /mnt/cdrom 挂载一个cdrom或dvdrom 
　　mount /dev/hdc /mnt/cdrecorder 挂载一个cdrw或dvdrom 
　　
　　mount -o loop file.iso /mnt/cdrom 挂载一个文件或ISO镜像文件 
　　mount -t vfat /dev/hda5 /mnt/hda5 挂载一个Windows FAT32文件系统 
　　mount /dev/sda1 /mnt/usbdisk 挂载一个usb 捷盘或闪存设备 
　　mount -t smbfs -o username=user,password=pass //WinClient/share /mnt/share 挂载一个网络共享
磁盘空间
 

〔适用场合〕 经常需要输入重复的命令时，有非常大的用处
〔用 法〕 doskey
将doskey驻留内存，开辟出缓冲区，以后输入的命令都将保存在缓冲区中，可以随时调用
doskey [宏命令名]=[命令名]
将宏命令定义为命令，以后输入宏命令，电脑就会执行相应的命令
doskey /reinstall 重新安装doskey
doskey /bufsize= 设置缓冲区的大小
doskey /macros 显示所有doskey宏
doskey /history显示内存中所有命令
doskey /insert|overstrike 设置新键入的字符是否覆盖旧的字符
〔例 子〕C:\>DOSKEY
C:\>dir
C:\>copy C:\temp\*.* a:
C:\>del c:\temp\*.*
C:\>copy b:\*.* c:\temp
上述四条命令都已被保存，用光标控制键的上下可以依次选择使用或修改,也可以用F7键列出保存的所有命令
C:\>doskey di=dir/w/p 定义di为宏命令，意思是执行dir/w/p

 


