#
#	bat 编程
#
cmd路径 \ 反斜杠 linux
1.start b.bat 新开cmd窗口 
2.call b.bat 不显示 路径执行  命令/bat 等待后续
3.b.bat 直接调用exe终止 当前bat后续代码 而 call不会

%1% 取出第一个参数



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


cd /home 进入 '/ home' 目录' 
　　cd .. 返回上一级目录 
　　cd ../.. 返回上两级目录 
　　cd 进入个人的主目录 
　　cd ~user1 进入个人的主目录 
　　cd - 返回上次所在的目录 
　　pwd 显示工作路径 
　　ls 查看目录中的文件 
　　ls -F 查看目录中的文件 
　　ls -l 显示文件和目录的详细资料 
　　ls -a 显示隐藏文件 
　　ls *[0-9]* 显示包含数字的文件名和目录名 
　　tree 显示文件和目录由根目录开始的树形结构(1) 
　　lstree 显示文件和目录由根目录开始的树形结构(2) 
　　mkdir dir1 创建一个叫做 'dir1' 的目录' 
　　mkdir dir1 dir2 同时创建两个目录 
　　mkdir -p /tmp/dir1/dir2 创建一个目录树 
　　rm -f file1 删除一个叫做 'file1' 的文件' 
　　rmdir dir1 删除一个叫做 'dir1' 的目录' 
　　rm -rf dir1 删除一个叫做 'dir1' 的目录并同时删除其内容 
　　rm -rf dir1 dir2 同时删除两个目录及它们的内容 
　　mv dir1 new_dir 重命名/移动 一个目录 
　　cp file1 file2 复制一个文件 
　　cp dir/* . 复制一个目录下的所有文件到当前工作目录  */
　　cp -a /tmp/dir1 . 复制一个目录到当前工作目录 
　　cp -a dir1 dir2 复制一个目录 
　　ln -s file1 lnk1 创建一个指向文件或目录的软链接 
　　ln file1 lnk1 创建一个指向文件或目录的物理链接 
　　touch -t 0712250000 file1 修改一个文件或目录的时间戳 - (YYMMDDhhmm)
文件搜索

find / -name file1 从 '/' 开始进入根文件系统搜索文件和目录 
　　find / -user user1 搜索属于用户 'user1' 的文件和目录 
　　find /home/user1 -name \*.bin 在目录 '/ home/user1' 中搜索带有'.bin' 结尾的文件 
　　find /usr/bin -type f -atime +100 搜索在过去100天内未被使用过的执行文件 
　　find /usr/bin -type f -mtime -10 搜索在10天内被创建或者修改过的文件 
　　find / -name \*.rpm -exec chmod 755 '{}' \; 搜索以 '.rpm' 结尾的文件并定义其权限 
　　find / -xdev -name \*.rpm 搜索以 '.rpm' 结尾的文件，忽略光驱、捷盘等可移动设备 
　　locate \*.ps 寻找以 '.ps' 结尾的文件 - 先运行 'updatedb' 命令 
　　whereis halt 显示一个二进制文件、源码或man的位置 
　　which halt 显示一个二进制文件或可执行文件的完整路径
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

df -h 显示已经挂载的分区列表 
　　ls -lSr |more 以尺寸大小排列文件和目录 
　　du -sh dir1 估算目录 'dir1' 已经使用的磁盘空间' 
　　du -sk * | sort -rn 以容量大小为依据依次显示文件和目录的大小 
　　rpm -q -a --qf '%10{SIZE}t%{NAME}n' | sort -k1,1n 以大小为依据依次显示已安装的rpm包所使用的空间 (fedora, redhat类系统) 
　　dpkg-query -W -f='${Installed-Size;10}t${Package}n' | sort -k1,1n 以大小为依据显示已安装的deb包所使用的 空间 (ubuntu, debian类系统)
2Windows命令
 
cd 改变当前目录
dir 显示文件列表
diskcopy 复制软盘
format 格式化磁盘
md 建立子目录
type 显示文件内容
rd 删除目录
ren 改变文件名
……
cls 清屏
正在执行命令的命令提示符
正在执行命令的命令提示符
〔适用场合〕 屏幕上太乱了，或是屏幕上出现乱码了，清除屏幕上显示内容但不影响电脑内部任何信息
〔用法〕 cls+回车
move 移动文件，改目录名
〔适用场合〕 移动文件到别的目录
〔用 法〕 move 文件名 目录[\文件] 移动文件至新目录下
move 目录 目录名 改目录名
〔例 子〕 c:\>move c:\autoexec.bat c:\old
移动autoexec.bat文件至old目录下
c:\>move c:\config.sys c:\old
移动config.sys文件至old目录下
more 分屏显示
〔适用场合〕 当输出很多一屏显示不下时采用，几乎适合所有命令，尤其是type等命令时很有用。使用more时磁盘不能有写保护，也不适合光驱。
〔用法〕 命令 | more 分屏显示文件内容
more < [文件名] 分屏显示文件内容
〔例 子〕C:\>type msdos.w40 | more
xcopy 加强版复制
〔适用场合〕 在进行连同子目录一起拷贝时很有用，在拷贝大量文件时比COPY命令要快得多
〔用 法〕 xcopy [文件名] [目录] 将指定文件拷贝到指定目录
xcopy [源目录] [目的目录] 将源目录连子目录拷到目的目录下
xcopy *.* [目录] /s 将文件与非空子目录拷贝到指定目录
其它常用参数还有：v 拷贝后校验，会影响速度
e 与s 相似，但即使子目录是空的也会拷贝
帮助

〔适用场合〕 当想具体了解DOS命令的使用方法时使用
〔用 法〕 help 提供所有DOS命令帮助
help （+DOS命令）提供有关（DOS）命令的帮助
如果你只大致记得某个命令，可以在提示符后直接输入help命令，然后将出现下面的画面：
attrib 设置文件属性
〔适用场合〕想对文件做较特殊的处理时
〔用法〕 attrib 显示所有文件的属性
attrib +r或-r [文件名] 设置文件属性是否为只读
attrib +h或-h [文件名] 设置文件属性是否隐含
attrib +s或-s [文件名] 设置文件属性是否为系统文件
attrib +a或-a [文件名] 设置文件属性是否为归档文件
attrib /s 设置包括子目录的文件在内的文件属性
〔例 子〕C:\TEST>attrib +r wina20.386
C:\>attrib +h *.* /s 隐含所有文件
date 显示及修改日期
〔适用场合〕 想知道或修改时间和日期
〔用 法〕 date 显示和改变当前日期
〔例 子〕C:\>date 09-20-1996 将日期改为1996年9月20日
C:\>date
Current date is Tue 08-20-1996
Enter new date (mm-dd-yy):09-20-1996
按月-日-年的顺序修改当前日期直接按回车键忽略修改日期
设置卷标

〔适用场合〕 用来为磁盘做个标记
〔用 法〕 label 显示磁盘卷标
label [盘符] [卷标名] 设定指定盘的卷标
〔例 子〕C:\>label
Volume in drive C is WANG
Volume Serial Number is 2116-1DD0
volume label （11 characters,Enter for none)?
可以输入卷标，直接回车后
Delete current volume label (Y/N)?
按y删除旧卷标，按n不更改
碎片整理

〔适用场合〕磁盘读写次数很多，或磁盘使用时间很长了，可能需要使用这条命令整理磁盘。磁盘碎片并不是指磁盘坏了，而只是由于多次的拷贝和删除文件后，磁盘使用会很不连贯，致使速度变慢。
〔用 法〕1. C:\>defrag
⒉ 选择要整理的磁盘
⒊ 电脑分析磁盘状况，然后告诉我们磁盘有多少需整理。按Esc键
⒋ 选择Optimization Method(磁盘优化方法），选择"全部优化"或"仅优化文件"
⒌ 选择Begin Optimization 开始整理
⒍ 整理完后，按回车键
⒎ 按Esc退出。
调用建立

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

 


