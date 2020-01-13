uname -a
    Linux walker 4.15.0-45-generic #48-Ubuntu SMP Tue Jan 29 16:28:13 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux
cat /proc/version ####正在运行的内核版本。
    Linux version 4.15.0-45-generic (buildd@lgw01-amd64-031) (gcc version 7.3.0 (Ubuntu 7.3.0-16ubuntu3)) #48-Ubuntu SMP Tue Jan 29 16:28:13 UTC 2019
cat /etc/issue ####显示的是发行版本信息
    Ubuntu 18.04.1 LTS \n \l
cat /proc/cpuinfo | more ####分页查看

du -sh * #查看文件大小 占用 ls -lth
df -h   #磁盘
## 基本命令
    whereis 
    which
    ls -lht <l>长信息 <h>size转换 <t>时间排序 <s>size排序 <d> 只显示目录 
    type ls 查看命令位置 查看执行结果?
    date --version / -v   --引领一整个英文单词
    whatis ls   简述
    man ls 帮助文档
    info ls 更详细的文档
    
        (1) CTRL+Z挂起进程并放入后台
    　 　(2) jobs 显示当前暂停的进程 ###########################################
    　 　(3) bg %N 使第N个任务在后台运行(%前有空格)
    　 　(4) fg %N 使第N个任务在前台运行
　　     默认bg,fg不带%N时表示对最后一个进程操作!
    
    id  查看当前用户组及其他状态
    last 查看远程登录记录
	apt-cache madison python-rpi.gpio	查看安装 的软件版本
    unzip opencv-2.4.13.zip
    
    命令行历史 history
    date &              #后台执行
    date && echo ''     #依次执行 逻辑控制
    wait 等待所有&执行完毕
    nohup ./startup.sh & 守护进程？无关终端 忽略所有挂断（SIGHUP）信号 无视注销/关闭终端
    ldconfig 通常在系统启动时运行，加载新的动态链接库时，就需要手工运行这个命令。 
    ln -s source     dist     #建立软连接 快捷方式
    ln     source     dist     #建立硬连接 硬链接不能连接两个不同文件系统上的文件 类似拷贝副本
## 用户 用户组 用户根目录 home
    cat /etc/passwd #查看用户根目录 命令sh环境
    usermod -d /home/walker walker     #修改用户目录
    chown -R wasup:wasgrp com 修改文件所属用户及组权限
    
    /bin  二进制可执行命令。该目录下存放着普通用户的命令
    /dev  系统的设备文件，即设备的驱动程序
    /home  用户主目录的基点
    /lost-found 这个目录平时是空的，当系统非正常关机而留下的“无家可归”的文件便会储存在这里
    /misc  储存着一些特殊的字符的定义
    /net  存放着和网络相关的一些文件
    /proc  存放着用户与内核的交互信息
    /sbin  系统的管理命令，这里存放的是系统管理员使用的程序
    /srv  系统启动服务时可以访问的数据库目录
    /tmp  临时文件，重启后自动清空
    /var  某些大文件的溢出区，比如各种服务的日志文件
    /boot  启动linux的核心文件
    /etc  系统所有的配置文件都在这个目录中
    /lib  存放着和系统运行相关的库文件 
    /media  存放着可移除的设备，比如软盘，光盘
    /mnt  挂载目录，是系统管理员临时安装文件的系统安装点
    /opt  (option : 自由选择)主要给源码安装软件时选择的安装目录位置
    /root  超级用户的目录
    /selinux 主要用来加固操作系统，提高系统的安全性
    /sys  管理设备文件
    /usr  最大的目录，存放着应用程序和文件
        find /usr/lib/x86_64-linux-gnu/ -name *perl*so*
        
        
        
## 安装ubuntu后操作记录
	修改apt源
	
	修改环境变量添加ls -lth
    alias ll='ls -alFh'
    
    
    英文版本
    安装中文输入法
    apt install ibus-pinyin
    设置系统为中文展示
    language 配置 input source chinese - pinyin 拖动汉语before english
    配置自动挂载磁盘 结合修改help_note目录git同步
    安装python git 
    gedit插件安装 编辑器
    sudo apt-get install gedit-plugins 
    点击应用关闭
    gsettings set org.gnome.shell.extensions.dash-to-dock click-action 'minimize'
    底座下靠
    chrome
    eclipse
    jdk
    tomcat resin
	maven
	idea
    


## vim  less 
    esc :set number 显示行号 
    esc :set nu
    esc /str 查找1 正向 支持 * 通配符号
    esc :{作用范围}s/{目标}/{替换}/{替换标志} g标示每行所有命中 全文替换 不要则只匹配每行第一个命中
        :%s/foo/bar/g
    esc ?str 查找2 反向  n next  shift+n/N previous
    esc shift + * 查找当前所在单词
    esc G shift + g 滚动最底部
    esc gg  滚动最顶部
    esc yw 复制当前到单词结尾
    esc p paste粘贴
    撤销：u
    恢复撤销：Ctrl + r
################################################################################################################eval xargs
    st="ls | more"
    `$st`   ####将 | 和 more 看成了参数，而不是将文件按页显示
    eval $st      ####双次解析 一次解析变量 二次 放置执行？ 同js php shell
#杀死指定规则进程pid获取
#字符分离数组
#截取
ps -elf | cut -c 9-15 
#kill
    '239 39234 2343' | xargs kill -9
    kill -9 25718 25719 25811 25812 依次排在后边
    killall nginx #删除所有依据名字
    ps -elf | grep <-v反转> 'aaa'
    xargs的默认命令是echo，空格是默认定界符
    xargs入模式
        -p 请求输入
        -d 指定分隔符
    echo "--help" | cat
    echo "--help" | xargs cat
    cat test.txt | xargs -n3 ####多行
    cat test.txt | xargs -d'S' ####设定分隔符
    arg.txt : 
        file1.txt
        file2.txt
    cat arg.txt | xargs -I {} cat -p {} -l  ####{}占位符 替换
    ->
    cat -p file1.txt -l
    cat -p file2.txt -l
####文件查找 文本查找 文本格式化 #######################################################################################
less比more更强大，提供翻页，跳转，查找等命令

##### strings --help    用于分析dump内存 过滤特殊字符
用法：strings [选项] [文件]
 打印 [文件] (默认为标准输入) 中可打印的字符串
 选项为：
  -a - --all                Scan the entire file, not just the data section [default]
  -d --data                 Only scan the data sections in the file
  -f --print-file-name      Print the name of the file before each string
  -n --bytes=[number]       Locate & print any NUL-terminated sequence of at
  -<number>                   least [number] characters (default 4).
  -t --radix={o,d,x}        Print the location of the string in base 8, 10 or 16
  -w --include-all-whitespace Include all whitespace as valid string characters
  -o                        An alias for --radix=o
  -T --target=<BFDNAME>     Specify the binary file format
  -e --encoding={s,S,b,l,B,L} Select character size and endianness:
                            s = 7-bit, S = 8-bit, {b,l} = 16-bit, {B,L} = 32-bit
  -s --output-separator=<string> String used to separate strings in output.
  @<file>                   Read options from <file>
  -h --help                 Display this information
  -v -V --version           Print the program's version number


#####awk --help
awk [-F|-f|-v] ‘BEGIN{} ####{command1; command2} END{}’ file
    -F指定分隔符，-f调用脚本，-v定义变量 var=value
    '  '          引用代码块
    BEGIN   初始化代码块，在对每一行进行处理之前，初始化代码，主要是引用全局变量，设置FS分隔符
    //          匹配代码块，可以是字符串或正则表达式
    {}           命令代码块，包含一条或多条命令
    ；          多条命令使用分号分隔
    END      结尾代码块，在对每一行进行处理之后再执行的代码块，主要是进行最终计算或输出结尾摘要信息
    $0          表示整个当前行 
    $1           每行第一个字段
    NF          字段数量变量    
    NR          每行的记录号，多文件记录递增
    FNR        与NR类似，不过多文件记录不递增，每个文件都从1开始  
    FS          BEGIN时定义分隔符
    RS       输入的记录分隔符， 默认为换行符(即文本是按一行一行输入)
    FILENAME 文件名
    OFS      输出字段分隔符， 默认也是空格，可以改为制表符等
    ORS        输出的记录分隔符，默认为换行符,即处理结果也是一行一行输出到屏幕
    -F'[:#/]'   定义三个分隔符
    
ps -lf | awk -Fwalker '{print NR,NF,$1,$NF}' OFS="\t"
ps -lf | awk -F" " 'NR!=1{print NR,NF,$1,$NF,($3>100 ? "yes":"no")}' OFS="\t" #不要第一行
-F'[ :]'   #' ' || '"' 多分隔符
----------------------------------------代码段落处理
ps -lf | awk -F" " '
BEGIN{before=0;after=0;deta=5000}
{
    res=system("date")
    if($4>deta){
        after++; 
        print $4,"large",$4">"deta
    }
    else {
        before++;
        print $4,"small----",$4"<"deta;
        print $4,"small",$4"<"deta
        
    }
}
END{printf "Total before:%-8s after:%-8s\n", before, after}
'
-----------------------------------

####sed --help
用法: sed [选项]... {脚本(如果没有其他脚本)} [输入文件]...
  -r    -regexp-extended    扩展正则!!!!!!!
  -n, --quiet, --silent
                 取消自动打印模式空间
  -e 脚本, --expression=脚本
                 添加“脚本”到程序的运行列表
  -f 脚本文件, --file=脚本文件
                 添加“脚本文件”到程序的运行列表
  --follow-symlinks
                 直接修改文件时跟随软链接
  -i[SUFFIX], --in-place[=SUFFIX]
  -i.backup     添加备份文件命名
                 edit files in place (makes backup if SUFFIX supplied)
  -l N, --line-length=N
                 指定“l”命令的换行期望长度
  --posix
                 关闭所有 GNU 扩展
  -E, -r, --regexp-extended
                 use extended regular expressions in the script
                 (for portability use POSIX -E).
  -s, --separate
                 consider files as separate rather than as a single,
                 continuous long stream.
      --sandbox
                 operate in sandbox mode.
  -u, --unbuffered
                 从输入文件读取最少的数据，更频繁的刷新输出
  -z, --null-data
                 使用 NUL 字符分隔各行
      --help     打印帮助并退出
      --version  输出版本信息并退出
如果没有 -e, --expression, -f 或 --file 选项，那么第一个非选项参数被视为
sed脚本。其他非选项参数被视为输入文件，如果没有输入文件，那么程序将从标准
输入读取数据。
| sed -r 's/[0-9]{8}.BIN/20200102.BIN/g' 
#取出5-10行
sed -n '5,10p' obcp-server29.log
#文件行管道替换
cat redis_cluster_7000.conf | sed s/7000/7001/g
#文件整体替换
sed -i.back "s/oldstring/newstring/g" `grep oldstring -rl yourdir`
#替换输出
sed s/7000/7002/ redis_cluster_7000.conf

#去掉控制台颜色代码##########
edjfl | sed -r "s/\x1B\[([0-9]{1,2}(;[0-9]{1,2})?)?[m|K]####g"

####find --help
    Usage: find [-H] [-L] [-P] [-Olevel] [-D debugopts] [path...] [expression]
    默认路径为当前目录；默认表达式为 -print
    表达式可能由下列成份组成：操作符、选项、测试表达式以及动作：
    操作符 (优先级递减；未做任何指定时默认使用 -and):
          ( EXPR )   ! EXPR   -not EXPR   EXPR1 -a EXPR2   EXPR1 -and EXPR2
          EXPR1 -o EXPR2   EXPR1 -or EXPR2   EXPR1 , EXPR2
    位置选项 (总是真): -daystart -follow -regextype
    普通选项 (总是真，在其它表达式前指定):
          -depth --help -maxdepth LEVELS -mindepth LEVELS -mount -noleaf
          --version -xdev -ignore_readdir_race -noignore_readdir_race
    测试(N可以是 +N 或-N 或 N):-amin N -anewer FILE -atime N -cmin  
          -cnewer 文件 -ctime N -empty -false -fstype 类型 -gid N -group 名称
          -ilname 匹配模式 -iname 匹配模式 -inum N -ipath 匹配模式 -iregex 匹配模式
          -links N -lname 匹配模式 -mmin N -mtime N -name 匹配模式 -newer 文件
          -nouser -nogroup -path PATTERN -perm [-/]MODE -regex PATTERN
          -readable -writable -executable
          -wholename PATTERN -size N[bcwkMG] -true -type [bcdpflsD] -uid N
          -used N -user NAME -xtype [bcdpfls]      -context 文本
find test</> | grep .png #查找当前路径 下 所有文件 深度优先 的 png图片文件
find test</> -name '.*.png'
find test -path "./Documents" -prune -o -path "./Desktop" -prune -o -name '.*.png' -o -name '*xml'      #例外 多个文件夹跳过  匹配文件
    [-o or  -a and  ! not   逻辑运算]
    [-path "./Desktop"  路径匹配]
    [-name "*.xml"  名字匹配] 
    [-iname "*.xMl" 忽略大小写名字匹配]   
    [-maxdepth 3    深度递归] 
    [-perm 777  权限] 
    [-user walker   用户]
    [-group sunk    用户组]
    [-size -10k 文件大小少于10k M G +大于]
    [-mtime -7  -七天前 +七天内 time天 min分 a访问 m修改 c权限改动]
    [-prune 不递归子目录]
    [-type f 文件]
    [-empty 空文件]
    [-exec rm -rf {} \  文件路径替换操作执行!]
find ./ -maxdepth 4 -type d    
    

find /var/svn/svnbackup -type f -name "new_*" -mtime +7 -exec rm -rf {} \;  #删除/var/svn/svnbackup目录下创建时间为7天之前，并且文件以new开头的的所有文件或文件夹； 
find ./ * -mtime 0 
      -mtime -7 表示七天之内;
      -mtime +7 表示七天之前;
      -mtime 0  表示1天之内;
      
#### grep  --help
grep [OPTIONS]PATTERN [FILE...] 
    PATTERN:是文本字符和正则表达式的元字符组合而成的匹配条件，
    用单引号‘ ’将pattern括起来以避免shell通配的影响，强引用不替换而显示字符本身。" " 双引号，
    字符串中的` ` ,$, \ 等特殊字符会被shell解释替换后，再传递给grep。
    对普通的字符串（没有特殊字符和空格的字符串）也可以不加引号，直接搜索。 
     OPTIONS：（这里给出常用的选项） 
    -i 忽略大小写 
    -c 显示被匹配到的行数 
    -n 输出行号 
    -v 反向选择，即找没有搜索字符串的行  #############3
    -o 仅显示匹配到的内容   grep -oe<只显示匹配内容><-C 5 前后五行><-A 5 前><-B 5 后> '.*\[.*\].*' test.sh
    -w 匹配单词 
    -A # 连同匹配行的下#行一并显示，#代表任意数字 
    -B # 连同匹配行的上#行一并显示，#代表任意数字 
    -C # 连同匹配行的上下#行一并显示，#代表任意数字 
    -l 只显示命中的文件名
    -E  相当于egrep 支持扩展的正则表达式     三种模式正则 grep 转义 \|   \+ 
#    https://blog.csdn.net/yufenghyc/article/details/51078107
#抓取ip port 格式化输出并排序
    cat ips.txt | grep -o "[0-9]\+\.[0-9]\+\.[0-9]\+\.[0-9]\+\:[0-9]\+" | awk -F':' '{print $1,$2}' OFS="\t" | sort -k 1 -n 
    
    -F  相当于fgrep 不支持正则表达式 
    --color对匹配的内容以颜色显示 
    -V  显示grep版本 
    -R
    -r 递归搜索目录或子目录下匹配的字所在文件 可配合find命令 ############### 
grep -rl 7000 ./*   #匹配所有文件子目录文件 输出概要或者文件列表
grep "7000" file1.txt file2.txt file3.txt   #匹配多个文件 
grep "7000" `find ./ -name "*conf" -o -name "*conf3" `  #匹配 查找出的文件列表  并过滤一个子列表
grep -C 10 -inoe  '.*MccpMgr.*' obcp-server29.log | less 
grep -ne  'getUserBean\|device:null' obcp-server29.log | grep -v '.*DEBUG.*'| grep -v '.*INFO.*' | less
####常用工具 wc tr base64 less
wc -l file #### 统计行数
wc -w file #### 统计单词数
wc -c file #### 统计字符数

echo '123456' | base64  #编码
echo "a b c" | tr ' ' "\n"  #行列转换

####设置时间
    ntpd -s -d  ####自动同步 
    配置服务
    vim /etc/ntpconf
    # You do need to talk to an NTP server or two (or three).
    # server ntp.your-provider.example
    在下面添加以下内容，是一些亲测可用的ntp服务器。第一行最后的perfer表示优先使用此服务器，也就是复旦大学的ntp服务器。添加之后按Ctrl+X保存退出。
    server ntp.fudan.edu.cn iburst perfer
    server time.asia.apple.com iburst
    server asia.pool.ntp.org iburst
    server ntp.nict.jp iburst
    server time.nist.gov iburst
    /etc/init.d/ntp restart    ####重启

####date --help
    date --set="1999-01-01 08:00:00" # 设置时间
    
    date +%Y-%m-%d
    2013-02-19  
    date "+%H:%M:%S"  
    13:13:59  
    date "+%Y-%m-%d %H:%M:%S"  
    2013-02-19 13:14:19   
    date -d today   
    date -d now  
    date -d tomorrow   "+%Y-%m-%d %H:%M:%S" 
    date -d yesterday  
    date -d "1 days"    # second | minutes | hours | days | months | years | 
    date -d "-1 days"
    Mon Feb 18 13:11:58 CST 2013  
    date -d now +%s #到ms级别
    date -d "2019-02-11 13:14:19" +%s #到s级别
    1549862059
    date -d @1549862059 "+%Y-%m-%d"   #反转
    2019-02-11

#### apt-get --help debian  源配置
{
    vim /etc/apt/sources.list                                                 
    ####for pi
    deb http://mirrors.aliyun.com/raspbian/raspbian/ stretch main contrib non-free rpi 
    ####for pc	
    对比原有配置 找到系统版本
    XXXX='bionic'
    deb http://mirrors.aliyun.com/ubuntu/ ${XXXXX} main restricted universe multiverse
    deb http://mirrors.aliyun.com/ubuntu/ ${XXXXX}-security main restricted universe multiverse
    deb http://mirrors.aliyun.com/ubuntu/ ${XXXXX}-updates main restricted universe multiverse
    deb http://mirrors.aliyun.com/ubuntu/ ${XXXXX}-proposed main restricted universe multiverse
    deb http://mirrors.aliyun.com/ubuntu/ ${XXXXX}-backports main restricted universe multiverse
    #deb-src http://mirrors.aliyun.com/ubuntu/ ${XXXXX} main restricted universe multiverse
    #deb-src http://mirrors.aliyun.com/ubuntu/ ${XXXXX}-security main restricted universe multiverse
    #deb-src http://mirrors.aliyun.com/ubuntu/ ${XXXXX}-updates main restricted universe multiverse
    #deb-src http://mirrors.aliyun.com/ubuntu/ ${XXXXX}-proposed main restricted universe multiverse
    #deb-src http://mirrors.aliyun.com/ubuntu/ ${XXXXX}-backports main restricted universe multiverse 
 
    apt autoremove 自动删除无依赖包
    apt-get update  更新源
    apt-get upgrade 更新已安装的包
    apt-get dist-upgrade 更新已安装的包 and auto dependcy
    apt-get install python<=2.7> <--reinstall> 安装包
    apt-get remove package 删除包
    apt-get remove package --purge 删除包，包括配置文件等
    apt-cache search package 搜索软件包
    apt-cache show package  获取包的相关信息，如说明、大小、版本等
    apt-get -f install  修复安装
    apt-get -f -y install  ???
    apt-get build-dep package 安装相关的编译环境
    apt-cache depends package 了解使用该包依赖那些包
    apt-cache rdepends package 查看该包被哪些包依赖
    apt-get source package  下载该包的源代码
    apt-get clean && apt-get autoclean 清理无用的包
    apt-get check 检查是否有损坏的依赖
    ####指定版本安装
    apt-cache madison <<package name>>
    apt-cache policy <<package>>
    将列出所有来源的版本。如下输出所示：
    apt-cache madison vim
       vim | 2:7.3.547-1 | http://debian.mirrors.tds.net/debian/ unstable/main amd64 Packages
       vim | 2:7.3.547-1 | http://debian.mirrors.tds.net/debian/ unstable/main Sources
    apt-get install <<package name>>=<<version>>
    apt-get install open-client=1:6.6p1-2ubuntu1

}
#### suse    zypper
{
安装源操作：zypper+ 参数
    repos, lr 列出所有定义的安装源。
    addrepo, ar 添加一个新的安装源。
    removerepo, rr 删除指定的安装源。
    renamerepo, nr 重命名指定的安装源。
    modifyrepo, mr 修改指定的安装源。
    refresh, ref 刷新所有安装源。
    clean 清除本地缓存。
    search, se 查找是否存在包
zypper addrepo -f http://mirrors.aliyun.com/opensuse/distribution/13.1/repo/oss/ openSUSE-13.1-Oss
zypper addrepo -f http://mirrors.aliyun.com/opensuse/distribution/13.1/repo/non-oss/ openSUSE-13.1-Non-Oss
zypper addrepo -f http://mirrors.aliyun.com/opensuse/update/13.1/ openSUSE-13.1-Update-Oss
zypper addrepo -f http://mirrors.aliyun.com/opensuse/update/13.1-non-oss/ openSUSE-13.1-Update-Non-Oss

    
    安装某个软件包
    zypper install package_name<=version>
    zypper install/remove/update package_name*
    要一次安装和删除多个包，请使用 +/- 或 ~/! 修改键一次性安装和删除包：
    zypper install emacs -vim
    zypper remove emacs +vim 可使用此命令来获取所有可用新包的列表：
    zypper list-updates  类似的，要列出所有所需的包，请使用：
    zypper list-patches
    install, in 安装软件包。
    remove, rm 删除软件包。
    verify, ve 检验软件包的依赖关系的完整性。
    update, up 将已经安装的软件包更新到新的版本。
    dist-upgrade, dup 执行整个系统的升级。
    source-install, si 安装源代码软件包和它们的编译依赖。


#### redhat yum     使用yum解决rpm依赖问题
    1、yum 安装操作
    sudo apt-get install yum
    yum repolist all    #查看您拥有的仓库
    1) 安装wget
    yum install -y wget
    2) 备份/etc/yum.repos.d/CentOS-Base.repo文件
    cd /etc/yum/repos.d/
    mv CentOS-Base.repo CentOS-Base.repo.back
    3) 下载阿里云的Centos-6.repo文件
    wget -O CentOS-Base.repo http://mirrors.aliyun.com/repo/Centos-7.repo
    wget -O CentOS-Base.repo http://mirrors.aliyun.com/repo/Centos-6.repo
    wget -O CentOS-Base.repo http://mirrors.aliyun.com/repo/Centos-5.repo

    4) 重新加载yum
    yum clean all
    yum makecache

    先在通互联网的机器上配置互联网yum源
    再安装#yum -y install yum-util* 工具
    缓存你需要安装的rpm，但是不安装，使用yum主要是自动解决依赖关系，把相关的依赖包一网打尽。
    使用命令：
    mkdir -p /tmp/yum
    yum install <package name> --downloadonly --downloaddir=/tmp/yum
    将需要的rpm包下载到/tmp/yum中，复制到你的环境中，使用
    rpm -Uvh *
    安装即可

##############################################################################
在 Linux 操作系统下，几乎所有的软件均通过RPM 进行安装、卸载及管理等操作。RPM 的全称为Redhat Package Manager（红帽子包管理器） ，是由Redhat 公司提出的，用于管理Linux 下软件包的软件。Linux 安装时，除了几个核心模块以外，其余几乎所有的模块均通过RPM 完成安装。RPM 有五种操作模式，分别为：安装、卸载、升级、查询和验证。
1、RPM 安装操作
rpm -i 需要安装的包文件名
rpm -i example.rpm 安装 example.rpm 包；
rpm -iv example.rpm 安装 example.rpm 包并在安装过程中显示正在安装的文件信息；
rpm -ivh example.rpm 安装 example.rpm 包并在安装过程中显示正在安装的文件信息及安装进度；
2、RPM 查询操作
rpm -qa | grep tomcat4 查看 tomcat4 是否被安装；
rpm -qip example.rpm 查看 example.rpm 安装包的信息；
rpm -qif /bin/df 查看/bin/df 文件所在安装包的信息；
rpm -qlf /bin/df 查看/bin/df 文件所在安装包中的各个文件分别被安装到哪个目录下；
3、RPM 卸载操作
rpm -e 需要卸载的安装包
在卸载之前，通常需要使用rpm -q …命令查出需要卸载的安装包名称。
rpm -e tomcat4 卸载 tomcat4 软件包
    
####apt-get install gcc gcc-c++ ####c++编译需要
############################################################################################网站信息抓取####################################################################################################
####whatweb
    apt-get install whatweb
    异常/usr/bin/whatweb: /usr/lib/ruby/vendor_ruby/rchardet/universaldetector.rb:39: invalid multibyte escape: /[\x80-\xFF]/ (SyntaxError)
    解决
    vi /usr/li b/ruby/vendor_ruby/rchardet/universaldetector.rb
    文件第一行加入
    # encoding: US-ASCII
    apt-get install nmap  ####渗透测试工具nmap:
####nginx搭建 rtmp模块 pcre openssl zlib
    http://blog.csdn.net/shuxiaogd/article/details/47662115
    wget http://nginx.org/download/nginx-1.8.0.tar.gz
    wget https://codeload.github.com/arut/nginx-rtmp-module/zip/master #master.zip
    wget ftp://ftp.csx.cam.ac.uk/pub/software/programming/pcre/pcre-8.39.tar.gz
    wget http://www.openssl.org/source/openssl-1.0.1c.tar.gz
    wget http://www.zlib.net/zlib-1.2.11.tar.gz
    cd nginx-1.10.1 
    ./configure --sbin-path=/usr/local/nginx/nginx --conf-path=/usr/local/nginx/nginx.conf --pid-path=/usr/local/nginx/nginx.pid --with-http_ssl_module --with-pcre=../pcre-8.39 --with-zlib=../zlib-1.2.11 --with-openssl=../openssl-1.0.1c --with-http_stub_status_module --add-module=../nginx-rtmp-module-master
    ./configure --sbin-path=/usr/local/nginx/nginx --conf-path=/usr/local/nginx/nginx.conf --pid-path=/usr/local/nginx/nginx.pid --with-http_ssl_module --with-pcre=../pcre-8.39 --with-zlib=../zlib-1.2.11  --with-md5=/root --with-http_ssl_module --with-openssl=../openssl-1.0.1c --add-module=../nginx-rtmp-module-master
    make
    make install
    
####haproxy socket代理搭建
    wget http://www.haproxy.org/
    tar -xzvf haproxy-1.7.8.tar.gz
    cd  haproxy-1.7.8
    make TARGET=linux26 #cat /proc/version
    make install PREFIX=/usr/local/haproxy

    kill启动后
    ./usr/local/haproxy/sbin/haproxy -f /usr/local/haproxy/conf/haproxy.cnf
    
    监控 
    listen  admin_stats
        bind 0.0.0.0:8888 
        mode  http 
        stats uri   /haproxy
        stats realm     Global\ statistics 
        stats auth  admin:admin
    #监控是否代理目标宕机
    listen test1
            bind 0.0.0.0:3306
            mode tcp
            #maxconn 4086
            #log 127.0.0.1 local0 debug
            server s1 192.168.111.101:3306 check port 3306
            server s2 192.168.111.102:3306 check port 3306
    http://192.168.111.100:8888/haproxy
    
####设置DNS
    DNS是用来解析域名用的，平时我们访问网站都是直接输入一个网址，
    而dns把这个网址解析到一个IP。关于dns的概念，如果你很陌生的话，
    那就去网上查一下吧。在linux下面设置dns非常简单，
    只要把dns地址写到一个配置文件中即可。这个配置文件就是/etc/resolv.conf
    1）一个IP后面可以跟多个域名，可以是几十个甚至上百个；
    2）每行只能有一个IP，也就是说一个域名不能对应多个IP；
    3）如果有多行中出现相同的域名（前面IP不一样），会按最前面出现的记录来解析。
    
####安装投影仪
**xrandr
xrandr 命令行可以很方便地切换双屏，常用方式如下，其他的可以自己探索：
xrandr --output VGA --same-as LVDS --auto
         打开外接显示器(最高分辨率)，与笔记本液晶屏幕显示同样内容（克隆）
xrandr --output VGA --same-as LVDS --mode 1024x768
         打开外接显示器(分辨率为1024x768)，与笔记本液晶屏幕显示同样内容（克隆）
xrandr --output VGA --right-of LVDS --auto
         打开外接显示器(最高分辨率)，设置为右侧扩展屏幕
xrandr --output VGA --off
          关闭外接显示器
xrandr --output VGA --auto --output LVDS --off
        打开外接显示器，同时关闭笔记本液晶屏幕（只用外接显示器工作）
xrandr --output VGA --off --output LVDS --auto
        关闭外接显示器，同时打开笔记本液晶屏幕 (只用笔记本液晶屏)
分辨率以适应投影仪。
xrandr -   分辨率以适应投影仪。

####Linux 网络和监控
**hostname <–d 显示机器所属域名> <–f 显示完整的主机名和域名> <–i 显示当前机器的ip地址>
**ping     网络畅通 网络速度
  ping ip <-c 2  只ping两次> <-W 2 超时两秒> 
**telnet    通过telnet协议连接目标主机，如果telnet连接可以在任一端口上完成即代表着两台主机间的连接良好。
  telnet ip port 
  echo " " telnet ip port 无交互式
  sleep 2 | telnet 192.168.119.166  21
  
**ifconfig  查看用户网络配置。它显示当前网络设备配置。对于需要接收或者发送数据错误查找，这个工具极为好
**iwconfig  是用于无线网卡的 . 你可以用他查看设置基本的Wi-Fi 网络信息,例如 SSID, channel和encryption.包括 接收灵敏度, RTS/CTS 分片大小,重传机制。
    wlp4s0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
    service network start/stop      #服务形式
    ifconfig wlp4s0 up/down    #关闭网络
    iwlist wlp4s0 scan | grep ESSID    #扫描wifi可用
    iwlist wlp4s0 scan | grep SSID | awk -F'"' '{print $2}'  #截取wifi-name
    
    iwconfig wlp4s0 essid <wifi-name>  #配置wifi  
    iwconfig wlp4s0 key <wifi-pwd>     #配置密码
    iwconfig wlp4s0 ap auto            #配置自动连接
    ifconfig wlp4s0 192.168.1.120      #配置ip
    **nslookup www.*    在 有ip地址时，可以用这个命令来显示主机名，可以找到给定域名的所有ip地址。而你必须连接到互联网才能使用这个命令。
    **traceroute www.*  查看数据包在提交到远程系统或者网站时候所经过的路由器的IP地址、跳数和响应时间。同样你必须链接到互联网才能使用这个命令
    **finger    查看用户信息。显示用户的登录名字、真实名字以及登录终端的名字和登录权限。这是unix一个很老的命令，现在已很少使用了。
    ethtool 允许你查看和更改网卡的许多设置（不包括Wi-Fi网卡）。你可以管理许多高级设置，包括tx/rx、校验及网络唤醒功能。下面是一些你可能感兴趣的基本命令：
    ethtool -i 显示一个特定网卡的驱动信息，检查软件兼容性时尤其有用
    ethtool -p 启动一个适配器的指定行为，比如让适配器的LED灯闪烁，以帮助你在多个适配器或接口中标识接口名称
    ethtool -s 显示网络统计信息
    ethtool speed <10|100|设置适配器的连接速度> 1000，单位是Mbps

####Linux系统的进程间通信的方式
    管道(pipe)：管道是一种半双工的通信方式，数据只能单向流动，而且只能在具有亲缘关系的进程间使用(进程的亲缘关系通常是指父子进程关系)。
    命名管道(named pipe)：命名管道也是半双工的通信方式，但是它允许无亲缘关系进程间的通信。
    信号量(semophore)：信号量是一个计数器，可以用来控制多个进程对共享资源的访问。它常作为一种锁机制，防止某进程正在访问共享资源时，其他进程也访问该资源。因此，主要作为进程间以及同一进程内不同线程之间的同步手段。
    消息队列(message queue)：消息队列就是一个消息的链表，存放在内核中并由消息队列标识符标识。消息队列克服了信号传递信息少、管道只能承载无格式字节流以及缓冲区大小受限等缺点。
    信号(sinal)：信号是一种比较复杂的通信方式，用于通知接收进程某个事件已经发生。
    共享内存(shared memory)：共享内存就是映射一段能被其他进程所访问的内存，这段共享内存由一个进程创建，但多个进程都可以访问。共享内存是最快的IPC方式，它是针对其他进程间通信方式运行效率低而专门设计的。它往往与其他通信机制，如信号配合使用，来实现进程间的同步和通信。
    套接字(socket)：套接字也是一种进程间通信机制，与其他通信机制不同的是，它可用于不同主机间的进程通信。
####Linux终端管理进程  memory ps top
    top命令 持续查看cpu 内存 进程 和 线程！
    top <-H, 查看线程级别> 
        <-p 2833, 查看指定pid> 
        <-b -n 1, 非交互模式, 只跑一次>  
        <-u walker, 只看某用户>
    top -b -n 1 -i -c
    top - 16:00:00 up 1 day,  7:20,  1 user,  load average: 1.93, 1.48, 0.90  
    #uptime 运行时间 登录用户数量 平均负载 5/10/15分钟
    任务: 285 total,   2 running, 233 sleeping,   0 stopped,   0 zombie 
    #进程数 总共 运行 休眠 停止 僵尸
    %Cpu(s):  8.2 us,  1.9 sy,  0.0 ni, 88.9 id,  1.0 wa,  0.0 hi,  0.0 si,  0.0 st
    #cpu使用 user用户 sys系统 nice调优 idle空闲 wait-io等待 hi-cpu处理硬中断 si-cpu处理软中断 st-虚拟机偷走的cpu
    #满负荷运行cpu的使用率最好是user空间保持在65%～70%，system空间保持在30%，空闲保持在0%~5% 。
    KiB Mem :  8084668 total,   807312 free,  4124104 used,  3153252 buff/cache
    KiB Swap:  1755988 total,  1755988 free,        0 used.  3252680 avail Mem 
    #free 全部可用内存、已使用内存、空闲内存、缓冲内存
    进�� USER      PR  NI    VIRT    RES    SHR �  %CPU %MEM     TIME+ COMMAND
     3332 walker    20   0 1829648 224564  64068 R 111.8  2.8   8:54.95 gedit
      754 root      20   0   47136  27848   2384 S  29.4  0.3   3:09.34 /sbin/moun+
      878 message+  20   0   51692   6164   3912 S   5.9  0.1   0:15.43 /usr/bin/d+
    22747 walker    20   0   51360   4004   3388 R   5.9  0.0   0:00.02 top -bn 1 +
    PR 进程的调度优先级。这个字段的一些值是’rt’。这意味这这些进程运行在实时态。
    NI 进程的nice值（优先级）。越小的值意味着越高的优先级。
    VIRT 进程使用的虚拟内存。
    RES 驻留内存大小。驻留内存是任务使用的非交换物理内存大小。
    SHR SHR是进程使用的共享内存。
    S 这个是进程的状态。它有以下不同的值:
        D – 不可中断的睡眠态。
        R – 运行态
        S – 睡眠态
        T – 被跟踪或已停止
        Z – 僵尸态
    %CPU 自从上一次更新时到现在任务所使用的CPU时间百分比。
    %MEM 进程使用的可用物理内存百分比。
    TIME+ 任务启动后到现在所使用的全部CPU时间，精确到百分之一秒。
    COMMAND 运行进程所使用的命令。
####show memory
    free -h
    cat /proc/meminfo  #(free / ps / top)等的组合显示
    vmstat <1 sleep> <5 count> 
    procs -----------memory---------- ---swap-- -----io---- --system-- -----cpu-----

关于was内存持续升高稳定占用80%问题    
    仅清除页面缓存（PageCache）
    # sync; echo 1 > /proc/sys/vm/drop_caches       
    清除目录项和inode
    # sync; echo 2 > /proc/sys/vm/drop_caches       
    清除页面缓存，目录项和inode
    # sync; echo 3 > /proc/sys/vm/drop_caches 
####ps

    ps H -eo user,pid,ppid,tid,time,%cpu --sort=+%cpu   #cpu使用倒序
    ps是显示瞬间进程的状态，并不动态连续；如果想对进程进行实时监控应该用top命令
    命令	含义 
       -e	显示所有进程,环境变量
        f	全格式
        h	不显示标题
        l	长格式
        w	宽输出
        a	显示终端上地所有进程,包括其他用户地进程
        r	只显示正在运行地进程
        x	显示没有控制终端地进程
        u	以用户为主的格式来显示程序状况
        au	显示较详细的资讯
        aux	显示所有包含其他使用者的行程
        -o c,C,f,g,G    按照指定格式输出
        args：进程名(command)
            c cmd   可执行地简单名称 
            C cmdline   完整命令行 
            f flags   长模式标志 
            g pgrp   进程地组ID 
            G tpgid   控制tty进程组ID 
            j cutime   累计用户时间 
            J cstime   累计系统时间 
            k utime   用户时间 
            K stime   系统时间 
            m min_flt   次要页错误地数量 
            M maj_flt   重点页错误地数量 
            n cmin_flt 累计次要页错误 
            N cmaj_flt 累计重点页错误 
            o session   对话ID 
            p pid   进程ID 
            P ppid   父进程ID 
            r rss   驻留大小 
            R resident 驻留页 
            s size   内存大小(千字节) 
            S share   共享页地数量 
            t tty   tty次要设备号 
            T start_time 进程启动地时间 
            U uid   UID
            u user   用户名
            v vsize   总地虚拟内存数量(字节) 
            y priority 内核调度优先级

####sort
    ps | sort -r    #字符串空排前
    sort 选项与参数：
    -f  ：忽略大小写的差异，例如 A 与 a 视为编码相同；
    -b  ：忽略最前面的空格符部分；
    -M  ：以月份的名字来排序，例如 JAN, DEC 等等的排序方法；
    -n  ：使用『纯数字』进行排序(默认是以文字型态来排序的)；
    -r  ：反向排序；
    -u  ：就是 uniq ，相同的数据中，仅出现一行代表；
    -t  ：分隔符，默认是用 [tab] 键来分隔；
    -k  ：以那个区间 (field) 来进行排序的意思
    ps -eo rss,pmem,pcpu,vsize,args |  sort -k 1 -r -n | less
        sort命令对ps结果进行排序
        -k 1 :按第一个参数 rss进行排
        -r：逆序
        -n：numeric，按数字来排序
    ps --sort=[+|-] key
    按CPU降序排列：ps aux --sort=[-|+]%cpu
    pstree  以显示进程信息。它以树的形式显示
    kill -9
    pgrep 会返回所有匹配这个关键词的进程ID。例如，你可以使用以下命令寻找Firefox的PID: pgrep firefox 
    pkill & killall pkill和killall命令可以根据进程的名字杀死一个进程。使用以下任一方法都可以杀死Firefox进程： pkill firefox  killall firefox 
    renice 用来改变进程的nice值。nice值代表进程的优先级。renice 19 pid    -19的nice值是非常高的优先级，相反，19是非常低的优先级。0是默认的优先级。

#### uniq --help    统计计数
用法：uniq [选项]... [文件]
Filter adjacent matching lines from INPUT (or standard input),
writing to OUTPUT (or standard output).

With no options, matching lines are merged to the first occurrence.

必选参数对长短选项同时适用。
  -c, --count           prefix lines by the number of occurrences 计数相邻同名
  -d, --repeated        only print duplicate lines, one for each group
  -D                    print all duplicate lines
      --all-repeated[=METHOD]  like -D, but allow separating groups
                                 with an empty line;
                                 METHOD={none(default),prepend,separate}
  -f, --skip-fields=N   avoid comparing the first N fields
      --group[=METHOD]  show all items, separating groups with an empty line;
                          METHOD={separate(default),prepend,append,both}
  -i, --ignore-case     ignore differences in case when comparing
  -s, --skip-chars=N    avoid comparing the first N characters
  -u, --unique          only print unique lines
  -z, --zero-terminated     line delimiter is NUL, not newline
  -w, --check-chars=N	对每行第N 个字符以后的内容不作对照
      --help		显示此帮助信息并退出
      --version		显示版本信息并退出


####linux性能监控 分析工具 监控 cpu mem netstat 
    apt-get install nmon 
    nmon -fT -s 5 -c 20
    nmon -f -T -s 5 -c 20 -m  ~/logs/
    -f标记，把nmon收集的数据保存到CSV格式的文件里，以_date_time.nmon方式命名。下面列出一些常用参数，更多可以查看帮助文档。
    -f 以后台方式运行nmon,把收集到的数据保存到csv文件中。 
    -t 包含top的输出------
    -T 输出最耗资源的进程
    -s 间隔时间
    -c 收集多少次 
    -m 生成目录
    好的 数据报表已经生成，可以下载出来再windows机器上用analyser日志分析工具打开
    nmon_analyser.xls excel脚本宏
    https://www.ibm.com/developerworks/community/wikis/home?lang=en#!/wiki/Power%20Systems/page/nmon_analyser
    选择文件转换为excel格式 
    excel图表展示

netstat
    netstat --help
    usage: netstat [-vWeenNcCF] [<Af>] -r         netstat {-V|--version|-h|--help}
           netstat [-vWnNcaeol] [<Socket> ...]
           netstat { [-vWeenNac] -i | [-cnNe] -M | -s [-6tuw] }
            -r, --route              显示路由表
            -i, --interfaces         display interface table
            -g, --groups             display multicast group memberships
            -s, --statistics         display networking statistics (like SNMP)
            -M, --masquerade         display masqueraded connections
            -v, --verbose            显示详细信息
            -W, --wide               don't truncate IP addresses
            -n, --numeric            不解析名称
            --numeric-hosts          不解析主机名
            --numeric-ports          忽略端口名称
            --numeric-users          忽略用户名
            -N, --symbolic           resolve hardware names
            -e, --extend             显示更多信息
            -p, --programs           display PID/Program name for sockets
            -o, --timers             display timers
            -c, --continuous         continuous listing
            -l, --listening          display listening server sockets
            -a, --all                display all sockets (default: connected)
            -F, --fib                display Forwarding Information Base (default)
            -C, --cache              display routing cache instead of FIB
            -Z, --context            display SELinux security context for sockets
      <Socket>={-t|--tcp} {-u|--udp} {-U|--udplite} {-S|--sctp} {-w|--raw}
               {-x|--unix} --ax25 --ipx --netrom
      <AF>=Use '-6|-4' or '-A <af>' or '--<af>'；默认： inet
    netstat -ano  所有 包括 udp 
    netstat -antl 所有 tcp
####telnet 通过 cmd 依靠ip/端口/用户名密码 远程登录
    service openbsd-inetd start  
    /etc/init.d/openbsd-inetd restart 
    1、首先查看telnet运行状态
    #netstat -a | grep telnet
    输出为空，表示没有开启该服务
     
    5、查看telnet运行状态
    #netstat -a | grep telnet
    输出：tcp　　0　　0 *:telnet　　*:*　　LISTEN
    此时表明已经开启了telnet服务。
        
        Telnet 客户端命常用命令：
    　　open : 使用 openhostname 可以建立到主机的 Telnet 连接。
    　　close : 使用命令 close 命令可以关闭现有的 Telnet 连接。
    　　display : 使用 display 命令可以查看 Telnet 客户端的当前设置。
    　　send : 使用 send 命令可以向 Telnet 服务器发送命令。支持以下命令：
    　　ao : 放弃输出命令。
    　　ayt : “Are you there”命令。
    　　esc : 发送当前的转义字符。
    　　ip : 中断进程命令。
    　　synch : 执行 Telnet 同步操作。
    　　brk : 发送信号。
    　　上表所列命令以外的其他命令都将以字符串的形式发送至 Telnet 服务器。例如，sendabcd 将发送字符串 abcd 至 Telnet 服务器，这样，Telnet 会话窗口中将出现该字符串。
    　　quit

####mv touch --help
    for i in `seq -w 10`; do touch -d "${i}/11/2011}" stu\_$i\_linux.jpg ; done
    touch -d "10/11/2011" ttt.txt2  #修改文件时间 文件修改时间
    touch -d  `  date -d '1 days' '+%Y-%m-%d %H:%M:%S'  ` test.txt 
    rename \_linux '' *.jpg
    rename '\_linux' '' *.jpg       
    mv命令既可以重命名，又可以移动文件或文件夹。     
    例子：将目录A重命名为B
    mv A B
    例子：将/a目录移动到/b下，并重命名为c
    mv /a /b/c
    mv abc 1234
####软链接 硬链接
    ln -s source     dist     #建立软连接 快捷方式
    ln     source     dist     #建立硬连接 硬链接不能连接两个不同文件系统上的文件 类似拷贝副本
####sh ./ bash dash各种语法错误
    原因在于两次执行的不是同一种shell，在用./sample的方式执行的时候，系统会使用脚本首行声明的/bin/bash来解释脚本，而用sh方式执行的时候，系统会调用sh
    ll `which sh`  
    /bin/sh -> dash*  
    ln -s /bin/bash /bin/sh #连接替换sh dash？
    切换bash dash
    输入bash即可
####回响
####
echo -e ${PATH}
    -n 不尾随换行符 文件追加 lf lrlf异常
    -e 启用解释反斜杠的转义功能
    -E 禁用解释反斜杠的转义功能(默认)
    --version 显示版本信息并退出
若-e 可用，则以下序列即可识别：
  \\    反斜杠
  \a    响铃声
  \b    退格
  \c    不再产生新的输出
  \e    转义符  
  \f    换页
  \n    新行
  \r    回车
  \t    水平制表符
  \v    竖直制表符
  \0NNN   字节数以八进制数 NNN (1至3位)表示     echo -e \x888
  \xHH    字节数以十六进制数 HH (1至2位)表示
系统	换行符
windows	\r\n
unix	\n
mac	\r
###进制转换 赋值
    let i=16#ff
    let aaa=n#[0 - n-1] #n进制定义
    let i=0xff  011
    echo 命令以十进制显示数据
    ((var=base#number));echo $var
    printf "%x\n" 65536
    
    bc命令格式转换
    echo "obase=进制;值" | bc
    echo "obase=16;65536" | bc
   
   
####环境变量
etc/profile, /etc/bashrc, .bash_profile和.bashrc的差别
调用顺序 
登陆Linux系统时： 
首先启动”/etc/profile”； 
然后启动 用户目录下的”~/.bash_profile” 附：(~/.bash_profile文件先调用~/.bashrc，然后再把PATH加载)； 
如果”~/.bash_login”和”~/.profile”文件存在的时候也会在执行”~ /.bash_profile”后被依次调用。
各个文件的作用 
/etc/profile：此文件为系统的每个用户设置环境信息,当用户第一次登录时,该文件被执行，并从/etc/profile.d目录的设置文件中搜集shell的设置； 
/etc/bashrc：为每一个运行bash shell的用户执行此文件，当bash shell被打开时，该文件被读取； 
~/.bash_profile：每个用户都可使用该文件输入专用于自己使用的shell信息，当用户登录时，该文件仅仅执行一次！默认情况下，他设置一些环境变量，执行用户的.bashrc文件， 
~/.bashrc:该文件包含专用于你的bash shell的bash信息,当登录时及每次打开新的shell时,该文件被读取； 
~/.bash_logout:当每次退出系统(退出bash shell)时,执行该文件；
区别 
/etc/profile是全局性的功能，其中设置的变量作用于所有用户，~/.bash_profile中设置的变量能继承/etc/profile中的变量并作用于用户。 
~/.bash_profile 是交互式、login 方式进入 bash 运行的；~/.bashrc 是交互式 non-login 方式进入 bash 运行的。

sh csh ksh bash dash 
#!/bin/sh
#!/bin/bash     #功能全面
执行命令 
在新的shell窗口环境执行sh
    ./test.sh   在当前的工作目录下执行test.sh
    test.sh     在环境变量中查找test.sh
    /data/shell/test.sh    在指定路径下查找test.sh
    bash /data/shell/test.sh    使用bash执行指定sh    不必赋予执行权限 不用文件第一行指定执行环境
在当前shell窗口环境执行sh
. test.sh   


#!/bin/bash
DIRNAME=$0
if [ "${DIRNAME:0:1}" = "/" ];then
    _NOW_DIR=`dirname $DIRNAME`
else
    _NOW_DIR="`pwd`"/"`dirname $DIRNAME`"
fi
echo $_NOW_DIR

./do show pp
$0<./do>-n取参数,  执行路径相对
$#<2>参数个数,
$@<".do" "show" "pp"> 数组
$*<"./do show pp"> 串
$?<int 0/1>函数返回值 
$$<PID 59>

   

    export JAVA_HOME=/home/walker/software/jdk1.7.0_79
    export CLASSPATH=$JAVA_HOME/bin   
    export PATH=$PATH:$CLASSPATH
    source /etc/profile
    
    # export CLASSPATH=$JAVA_HOME/lib/dt.jar:$JAVA_HOME/lib/tools.jar:$JAVA_HOME/bin
####eclipse高版本配置 当path无效
    ln -s /home/walker/software/jdk11 jre
    
    
    
    
####防火墙问题
    一、Linux下开启/关闭防火墙命令
    1、永久性生效，重启后不会复原。
    开启： chkconfig iptables on
    关闭： chkconfig iptables off
    2、 即时生效，重启后复原
    开启： service iptables start
    关闭： service iptables stop
    需要说明的是对于Linux下的其它服务都可以用以上命令执行开启和关闭操作。
    在当开启了防火墙时，做如下设置，开启相关端口，
    修改/etc/sysconfig/iptables 文件，添加以下内容：
    -A RH-Firewall-1-INPUT -m state --state NEW -m tcp -p tcp --dport 80 -j ACCEPT
    -A RH-Firewall-1-INPUT -m state --state NEW -m tcp -p tcp --dport 22 -j ACCEPT
    二、UBuntu关闭防火墙
    iptables -A INPUT -i !   PPP0   -j ACCEPT
    三、CentOS Linux 防火墙配置及关闭
    执行”setup”命令启动文字模式配置实用程序,在”选择一种工具”中选择”防火墙配置”,然后选择”运行工具”按钮,出现防火墙配置界面,将”安全级别”设为”禁用”,然后选择”确定”即可.
    或者用命令:
    #/sbin/iptables -I INPUT -p tcp –dport 80 -j ACCEPT
    #/sbin/iptables -I INPUT -p tcp –dport 22 -j ACCEPT
    #/etc/rc.d/init.d/iptables save
    这样重启计算机后,防火墙默认已经开放了80和22端口
    这里应该也可以不重启计算机：
    #/etc/init.d/iptables restart
    关闭防火墙服务即可：
    查看防火墙信息：
    #/etc/init.d/iptables status
    关闭防火墙服务：
    #/etc/init.d/iptables stop
####解压问题
    语法：tar [主选项+辅选项] 文件或者目录
    使用该命令时，主选项是必须要有的，它告诉tar要做什么事情，辅选项是辅助使用的，可以选用。
    主选项：
    c 创建新的档案文件。如果用户想备份一个目录或是一些文件，就要选择这个选项。相当于打包。
    x 从档案文件中释放文件。相当于拆包。
    t 列出档案文件的内容，查看已经备份了哪些文件。
    特别注意，在参数的下达中， c/x/t 仅能存在一个！不可同时存在！因为不可能同时压缩与解压缩。
    辅助选项：
    -z ：是否同时具有 gzip 的属性？亦即是否需要用 gzip 压缩或解压？ 一般格式为xx.tar.gz或xx. tgz
    -j ：是否同时具有 bzip2 的属性？亦即是否需要用 bzip2 压缩或解压？一般格式为xx.tar.bz2  
    -v ：压缩的过程中显示文件！这个常用
    -f ：使用档名，请留意，在 f 之后要立即接档名喔！不要再加其他参数！
    -p ：使用原文件的原来属性（属性不会依据使用者而变）
    -A
    xz -d linux-3.12.tar.xz && tar -xvf linux-3.12.tar
    tar -xvJf  node-v6.10.1-linux-x64.tar.xz
    
    tar -tvf  file.gz  #查看tar包文件列表 
    tar -xvf file.tar ####解压 tar包 
    tar -xzvf file.tar.gz ####解压tar.gz 
    tar -xjvf file.tar.bz2 ####解压 tar.bz2 
    tar -xzvf file.tar.Z ####解压tar.Z 
    --exclude FILE  在压缩的过程中，不要将 FILE 打包！

    将整个 /etc 目录下的文件全部打包成为 /tmp/etc.tar
    tar -cvf /tmp/etc.tar /etc　　　　<==仅打包，不压缩！
    tar -czvf /tmp/etc.tar.gz /etc　　<==打包后，以 gzip 压缩
    tar -cjvf /tmp/etc.tar.bz2 /etc　　<==打包后，以 bzip2 压缩
    tar -rvf file.tar test.txt   #追加文件 追加操作只针对没有压缩的tar包才有效
    
    unrar e file.rar ####解压rar 
    zip -r xxx.zip ./*  #当前目录的内容为xxx.zip文件
    unzip file.zip ####解压zip 
    ####对于.7z
    支持 7Z,ZIP,Zip64,CAB,RAR,ARJ,GZIP,BZIP2,TAR,CPIO,RPM,ISO,DEB 压缩文件格式
    安装： apt-get install p7zip p7zip-full p7zip-rar
    7z a yajiu.7z yajiu.jpg yajiu.png 将yajiu.jpg和yajiu.png压缩成一个7z包
    7z a yajiu.7z *.jpg 将所有.jpg的文件压缩成一个7z包
    7z a yajiu.7z yajiu 将文件夹yajiu压缩成一个7z包
    7z e yajiu.7z 将yajiu.7z中的所有文件解压出来，e是解压到当前路径
    7z x yajiu.7z 将yajiu.7z中的所有文件解压出来，x是解压到压缩包命名的目录下

####挂载ntfs磁盘问题
    apt-get install ntfsprogs
    ntfsfix /dev/sda5 
    
####文件夹限额
dd if=/dev/zero ibs=10M count=512 of=/root/disk.img
    说明:
    if=/dev/zero：表示输入文件为/dev/zero，一个虚拟的设备，顾名思义，里边的数据全是0
    ibs=10M： 表示每次读取的块大小为10M,这个数值的大小跟内存有关，如果你要每次读1G的数据
    count=512：表示共读取1024块  512 * 10M = 5120M = 5GB
    of=/dfs2：输出文件
losetup /dev/loop0 /root/disk.img   #挂载镜像
mkfs.ext3 /dev/loop0    #格式化
mkdir /test 
mount -t ext3 /dev/loop0 /test  #文件夹挂载绑定镜像限额
umount /test    #卸载文件夹
losetup -d /dev/loop0   #卸载镜像
rm -f /root/disk.img    #删除镜像

dirname='test10MB'  #文件名
loop='/dev/loop20'  #loop id
imgfile="/${dirname}"   #镜像放置位置
sudo dd if=/dev/zero ibs=10M count=1 of=${imgfile}  #新建镜像
sudo losetup ${loop} ${imgfile}  #挂载镜像
sudo mkfs.ext3 ${loop}    #格式化文件
mkdir ${dirname}
sudo mount -t ext3 ${loop} ${dirname}


####挂载磁盘为虚拟路径
    mount /dev/sda6 /home/e
    fdisk -l    #磁盘
    df -h                          # 查看已经挂载的磁盘
    mkfs.ext4 /dev/vdb             # 初始化磁盘
    mount /dev/vdb /u01            # mount 磁盘到/u01，保证/u01为空
    blkid                          # 获取磁盘的uuid和属性，用uuid来进行开机mount
    vim /etc/fstab                 # 开机mount，模板是UUID=********** /home/u01  ntfs  defaults  1 1
    mkfs.ext4 /dev/vdb  #初始化磁盘 格式化？  
    unmount /dev/vdb #扩容 取消挂载 重新处理 后 再挂载
    e2fsck -f /dev/vdb   # 诊治数据磁盘，返回磁盘信息
    resize2fs /dev/vdb   # 重置数据磁盘大小
####启动项
    1.操作系统接管硬件以后，首先读入 /boot 目录下的内核文件
    2.内核文件加载以后，就开始运行第一个程序 /sbin/init，它的作用是初始化系统环境。由于init是第一个运行的程序，它的进程编号（pid）就是1。其他所有进程都从它衍生，都是它的子进程。
    注意如果脚本需要用到网络，则NN需设置一个比较大的数字，如99。
    sudo update-rc.d test defaults 95 #优先级配置
####总启动项 在 /etc/init.d文件夹下是全部的服务程序，将脚本复制或者软连接到/etc/init.d/目录下，
ls /etc/init.d
####各级别启动目录 软连接 init.d目录下的应用 每个rc(1-6).d只链接它自己启动需要的相应的服务程序！
ls /etc/ | grep rc
rc0.d # 0 - 停机（千万别把initdefault设置为0，否则系统永远无法启动）
rc1.d # 1 - 单用户模式
rc2.d # 2 - 多用户，没有 NFS
rc3.d # 3 - 完全多用户模式(标准的运行级)
rc4.d # 4 - 系统保留的
rc5.d # 5 - X11 （x window)
rc6.d # 6 - 重新启动
rcS.d
####每个级别都会在在对应的目录下有对应的启动文件
    ls /etc/rc3.d/
    初始化操作都在 /etc/init/*.conf文件中完成     */
    cat /etc/init/anacron.conf 
    start on runlevel [2345]
    stop on runlevel [!2345]
    #####启动1
    vim /etc/rc.local
    /etc/init.d/test.sh start 
    #####启动2
    cp test.sh /etc/profile.d/ 
    #####启动3
    cp test.sh /etc/init.d/
    ln -s /etc/init.d/test.sh /etc/rc3.d/init.d/
    vim 启动文件，文件前面务必添加如下三行代码，否侧会提示chkconfig不支持
    #!/bin/sh #告诉系统使用的shell,所以的shell脚本都是这样
    #chkconfig: 35 20 80 #分别代表运行级别，启动优先权，关闭优先权，此行代码必须
    #description: http server #（ 两行都注释掉！！！，此行代码必须
    chkconfig --add test.sh
####用户组问题
    adduser walker 新建用户
    useradd -g root -s /home/walker -m walker
    passwd walker 修改密码
    userdel walker 删除用户
    groupadd admin 用户组
    groupdel admin 删除组
    
# usermod -s /bin/ksh -d /home/z –g developer sam
此命令将用户sam的登录Shell修改为ksh，主目录改为/home/z，用户组改为developer。
    usermod -g 用户组 用户名
    强行设置某个用户所在组
    usermod -G 用户组 用户名
    把某个用户改为 group(s)
    usermod -a -G 用户组 用户名
    把用户添加进入某个组(s）
    su - 而不是su，这是因为su -和su的区别在于su - 拥有root的环境变量即 / 目录下的 .bash_profile和 .bashrc文件，而su只拥有当前用户环境
####修改用户名
    usermod -l walker walkerdust
####初次登录ubuntu的root登录问题
    输入 root 密码 安装时 设置的是用户密码 而不是root 密码 ununtu 只能调用 root 不能直接 root登录
    输入 passwd root

####编译安装ffmpeg
        http://ffmpeg.org/releases/ffmpeg-2.8.11.tar.gz
    wget -c http://ffmpeg.org/releases/ffmpeg-3.0.tar.bz2 
    tar xvf ffmpeg-3.0.tar.bz2 
    cd ffmpeg-3.0 
    ./configure --host-cppflags=-fPIC --host-cflags=-fPIC --enable-shared 
    make 
    make install
     
####openssl安装
    这里需要特别的注意：openssl 版本不能太高，太高有些接口与libRTMP 的接口不一样，会导致libRTMP编译不能通过。我这里安装的是openssl-1.0.1f。
    1、下载地址：http://www.openssl.org/source/ 下一个新版本的OpenSSL，我下的版本是：openssl-1.0.1f
    2、在下载的GZ目录中，用命令执行：tar -xvf openssl-1.0.1f.tar.gz
    3、进入解压的目录：openssl-1.0.1f  [.......]#cd openssl-1.0.1f
    4、[.....openssl-1.0.1f]# ./config --prefix=/usr/local/openssl
    5[...../openssl-1.0.1f]# ./config -t
    6[...../openssl-1.0.1f]# make depend
    7[...../openssl-1.0.1f]# cd /usr/local
    8/usr/local]# ln -s openssl ssl
    9 [...../openssl-1.0.1f]#make install
    10在/etc/ld.so.conf文件的最后面，添加如下内容：
    /usr/local/openssl/lib
    11...]# ldconfig
    12添加OPESSL的环境变量：
    在etc／的profile的最后一行，添加：
    export OPENSSL=/usr/local/openssl/bin
    export PATH=$OPENSSL:$PATH:$HOME/bin
    13退出命令界面，再从新登录。
    14、以上OPENSSL就安装完毕，下面进行一些检查。
    15依次如下执行：
    cd /usr/local
    ldd /usr/local/openssl/bin/openssl
    会出现类似如下信息：
        linux-vdso.so.1 =>  (0x00007fff2116a000)
        libdl.so.2 => /lib/x86_64-linux-gnu/libdl.so.2 (0x00007f378e239000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f378de7c000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f378e44f000)
    16查看路径
    ...]# which openssl
    /usr/local/openssl/bin/openssl
    17查看版本
    ...]# openssl version
    OpenSSL 1.0.1f 6 Jan 2014

####定时任务
crontab -e #编辑
crontab -l  #列表 
执行日志 tail -f /var/spool/mail/root
Cron是Unix系统的一个配置定期任务的工具，用于定期或者以一定的时间间隔执行一些命令或者脚本； 基于每个用户的，每一个用户（包括root用户）都拥有自己的crontab。
*/1 * * * * date >> ~/logs/crontab.log  #定时每m测试crontab状况
*/5 * * * * /usr/local/tomcat-6.0.41/tomcat_cardniu_stat/monitor.sh ####增量5m
0 0 * * *  /home/pi/backup.sh ####0h0m

注意!!!!
%是有特殊含义 表示换行    常用的date +%Y%m%d在crontab里是不会执行的，应该换成date +\%Y\%m\%d
上下文环境变量不会加载 可手动加载    多条语句时，用分号“；”隔开
*/1 * * * * . /etc/profile; echo `date "+\%Y-\%m-\%d \%H:\%M:\%S"`" crontab trigger 1m " >> ~/logs/crontab.log  #定时每m测试crontab状况

#### service crond restart
service cron status
/etc/init.d/cron {start|stop|status|restart|reload|force-reload} ####重启服务
其中排列意思为：
http://cron.qqe2.com/
Bash
    #    m    h    dom    mon    dow    user    command
    #  分    时    日    月      周    用户    命令
    #
    #       m:表示分钟1～59 每分钟用*或者 */1表示 0表示整点 *表示启动时间开始 每增加/1单位
    #       h:表示小时1～23（0表示0点）   21-23，23-6
    #     dom:表示日期1～31
    #     mon:表示月份1～12
    #     dow:标识号星期0～6（0表示星期天）
    #    user:表示执行命令的用户
    # command:表示要执行的命令
    #
    #   * 代表任意数值
例程如下：
Bash
    30 21 * * * /usr/local/etc/rc.d/lighttpd restart
    #每晚的21:30重启apache。
    45 4 1,10,22 * * /usr/local/etc/rc.d/lighttpd restart
    #每月1、10、22日的4 : 45重启apache。
    10 1 * * 6,0 /usr/local/etc/rc.d/lighttpd restart
    #每周六、周日的1 : 10重启apache。
    0,30 18-23 * * * /usr/local/etc/rc.d/lighttpd restart
    #在每天18 : 00至23 : 00之间每隔30分钟重启apache。
    0 23 * * 6 /usr/local/etc/rc.d/lighttpd restart
    #每星期六的11 : 00 pm重启apache。
    * 0/1 * * * /usr/local/etc/rc.d/lighttpd restart
    #每一小时整点重启apache
    * 23-7/1 * * * /usr/local/etc/rc.d/lighttpd restart
    #晚上11点到早上7点之间，每隔一小时重启apache
    * 0/10 23-6 * * ?
    0 21-23,0-8 * * *
    
    0 11 4 * mon-fri /usr/local/etc/rc.d/lighttpd restart
    #每月的4号与每周一到周三的11点重启apache
    0 4 1 jan * /usr/local/etc/rc.d/lighttpd restart
    #一月一号的4点重启apache



####管道 多进程 并发
    1.1. linux后台进程 
    Unix是一个多任务系统，允许多用户同时运行多个程序。shell的元字符&提供了在后台运行不需要键盘输入的程序的方法。输入命令后，其后紧跟&字符，该命令就会被送往到Linux后台执行，而终端又可以继续输入下一个命令了。 
    比如： 
    sh a.sh & 
    这三个命令就会被同时送往linux后台执行，在这个程度上，认为这三个命令并发执行了。
    1.2. linux文件描述符
    文件描述符（缩写fd）在形式上是一个非负整数。实际上，它是一个索引值，指向内核为每一个进程所维护的该进程打开文件的记录表。当程序打开一个现有文件或者创建一个新文件时，内核向进程返回一个文件描述符。每一个unix进程，都会拥有三个标准的文件描述符，来对应三种不同的流：
    文件描述符	名称
    0	Standard Input
    1	Standard Output
    2	Standard Error
    每一个文件描述符会对应一个打开文件，同时，不同的文件描述符也可以对应同一个打开文件；同一个文件可以被不同的进程打开，也可以被同一个进程多次打开。
    在/proc/PID/fd中，列举了进程PID所拥有的文件描述符，例如
    #!/bin/bash
    source /etc/profile;
    # $$表示当前进程的PID
    PID=$$
    # 查看当前进程的文件描述符指向
    ll /proc/$PID/fd
    # 文件描述符1与文件tempfd1进行绑定
    ( [ -e ./tempfd1 ] || touch ./tempfd1 ) && exec 1<>./tempfd1
    [ouyangyewei@localhost learn_linux]$ sh learn_redirect.sh 
    total 0
    lrwx------. 1 ouyangyewei ouyangyewei 64 Jan  4 22:17 0 -> /dev/pts/0
    lrwx------. 1 ouyangyewei ouyangyewei 64 Jan  4 22:17 1 -> /dev/pts/0
    lrwx------. 1 ouyangyewei ouyangyewei 64 Jan  4 22:17 2 -> /dev/pts/0
    lr-x------. 1 ouyangyewei ouyangyewei 64 Jan  4 22:17 255 -> /home/ouyangyewei/workspace/learn_linux/learn_redirect.sh
    -------------------
    [ouyangyewei@localhost learn_linux]$ cat tempfd1 
    total 0
    lrwx------. 1 ouyangyewei ouyangyewei 64 Jan  4 22:17 0 -> /dev/pts/0
    lrwx------. 1 ouyangyewei ouyangyewei 64 Jan  4 22:17 1 -> /home/ouyangyewei/workspace/learn_linux/tempfd1
    lrwx------. 1 ouyangyewei ouyangyewei 64 Jan  4 22:17 2 -> /dev/pts/0
    lr-x------. 1 ouyangyewei ouyangyewei 64 Jan  4 22:17 255 -> /home/ouyangyewei/workspace/learn_linux/learn_redirect.sh
    -------------------
    上述的例子中第12行，将文件描述符1与文件tempfile进行了绑定，此后，文件描述符1指向了tempfile文件，标准输出被重定向到了文件tempfile中。
    1.3. linux管道
    在Unix或类Unix操作系统中，管道是一个由标准输入输出链接起来的进程集合，因此，每一个进程的输出将直接作为下一个进程的输入，
    linux管道包含两种：
    匿名管道 命名管道
    管道有一个特点，如果管道中没有数据，那么取管道数据的操作就会滞留，直到管道内进入数据，然后读出后才会终止这一操作；同理，写入管道的操作如果没有读取管道的操作，这一动作就会滞留。
    1.3.1. 匿名管道
    在Unix或类Unix操作系统的命令行中，匿名管道使用ASCII中垂直线|作为匿名管道符，匿名管道的两端是两个普通的，匿名的，打开的文件描述符：一个只读端和一个只写端，这就让其它进程无法连接到该匿名管道。
    cat file | less
    1
    1
    为了执行上面的指令，Shell创建了两个进程来分别执行cat和less。下图展示了这两个进程是如何使用管道的：
    unix_unnamed_pipe 
    有一点值得注意的是两个进程都连接到了管道上，这样写入进程cat就将其标准输出（文件描述符为fd 1）连接到了管道的写入端，读取进程less就将其标准输入（文件描述符为fd 0）连接到了管道的读入端。实际上，这两个进程并不知道管道的存在，它们只是从标准文件描述符中读取数据和写入数据。shell必须要完成相关的工作。
    1.3.2. 命名管道（FIFO，First In First Out）
    命名管道也称FIFO，从语义上来讲，FIFO其实与匿名管道类似，但值得注意：
    在文件系统中，FIFO拥有名称，并且是以设备特俗文件的形式存在的；
    任何进程都可以通过FIFO共享数据；
    除非FIFO两端同时有读与写的进程，否则FIFO的数据流通将会阻塞；
    匿名管道是由shell自动创建的，存在于内核中；而FIFO则是由程序创建的（比如mkfifo命令），存在于文件系统中；
    匿名管道是单向的字节流，而FIFO则是双向的字节流；
    比如，可以利用FIFO实现单服务器、多客户端的应用程序: 
    unix_named_pipe

##/dev/null  ： 空设备，是一个特殊的设备文件，弃一切写入其中的数据（但报告写入操作成功），读取它则会立即得到一个EOF。
    称为位桶(bit bucket)或者黑洞(black hole)。
    通常被用于丢弃不需要的输出流
    提供无限的空字符(NULL, ASCII NUL, 0x00)。
    nohup ./start.sh >/dev/null 2>&1 &      #正常日志丢弃 异常日志标准输出
 

##最大设备数限制 too many open files 异常
1.查看当前进程设备数 最大限制    查看系统限制最大设备数 每个进程限制
    #系统文件数总数 
    cat /proc/sys/fs/file-nr    #总数1
    cat /etc/security/limits.conf
    ulimit -a
    已打开         总限制file-max
    1184	0	6815744
    #进程限制数 suse出现进程限制和ulimit不一致问题?
    cat /proc/${pid}/limits
    #查询规则进程的文件占用数 分组统计

    #方式a
    ps -elf | grep java | grep -v grep | awk '{print $4}' | xargs -I {} lsof -p {} | awk '{print $1,$2}' | uniq -c | grep -v 'COMMAND PID' 
    #方式b
    lsof -n | awk '{print $1,$2}' | uniq -c | sort -k 1 -r   
    #lsof -p不准确？？
    #系统的fd使用情况 而ulimit的配置是针对单用户？ 分组排序前十
    #方式c  依赖管理员用户  !!
    sudo find /proc -print | grep -P '/proc/\d+/fd/'| wc -l #总数2
    sudo find /proc -print | grep -P '/proc/\d+/fd/'| awk -F '/' '{print $3}' | uniq -c | sort -rn | head
         a  exe  pid    b   c    
        66 java 1903
        505 java 2147       218
        168 java 2621       80
        395 java 3257       204
        549 java 3361       356
        216 java 3877       .

        1903                4401
3.修改系统最大进程数 最大设备数
    vim /etc/sysctl.conf 
        fs.file-max = 1000000
        net.ipv4.ip_conntrack_max = 1000000
        net.ipv4.netfilter.ip_conntrack_max = 1000000
2.优化代码 修改限制
    永久修改
    vim /etc/security/limits.conf
    # 添加如下的行
    * soft nofile 60000
    * hard nofile 61000
    以下是说明：
    * 代表针对所有用户
    noproc 是代表最大进程数
    nofile 是代表最大文件打开数
    添加格式：
    username|@groupname type resource limit
    username|@groupname：设置需要被限制的用户名，组名前面加@和用户名区别。也可以用通配符*来做所有用户的限制。
    type：有 soft，hard 和 -，soft 指的是当前系统生效的设置值。hard 表明系统中所能设定的最大值。soft 的限制不能比har 限制高。用 - 就表明同时设置了 soft 和 hard 的值。
    resource：
    core - 限制内核文件的大小(kb)
    date - 最大数据大小(kb)
    fsize - 最大文件大小(kb)
    memlock - 最大锁定内存地址空间(kb)
    nofile - 打开文件的最大数目
    rss - 最大持久设置大小(kb)
    stack - 最大栈大小(kb)
    cpu - 以分钟为单位的最多 CPU 时间
    noproc - 进程的最大数目
    as - 地址空间限制
    maxlogins - 此用户允许登录的最大数目
##ulimit使用的基本格式为：ulimit -a [options] [limit]
具体的options参数含义如下表所示：
-a 显示当前系统所有的limit资源信息。 
-H 设置硬资源限制，一旦设置不能增加。
-S 设置软资源限制，设置后可以增加，但是不能超过硬资源设置。
-c 最大的core文件的大小，以 blocks 为单位。
-f 进程可以创建文件的最大值，以blocks 为单位.
-d 进程最大的数据段的大小，以Kbytes 为单位。
-m 最大内存大小，以Kbytes为单位。
-n 查看进程可以打开的最大文件描述符的数量。
-s 线程栈大小，以Kbytes为单位。
-p 管道缓冲区的大小，以Kbytes 为单位。
-u 用户最大可用的进程数。
-v 进程最大可用的虚拟内存，以Kbytes 为单位。
-t 最大CPU占用时间，以秒为单位。
-l 最大可加锁内存大小，以Kbytes 为单位。 


#### lsof --help 系统 文件还原 进程
   lsof(list open files)是一个列出当前系统打开文件的工具。在linux环境下，任何事物都以文件的形式存在，
    通过文件不仅仅可以访问常规数据，还可以访问网络连接和硬件。
    所以如传输控制协议 (TCP) 和用户数据报协议 (UDP) 套接字等，系统在后台都为该应用程序分配了一个文件描述符，
    无论这个文件的本质如何，该文件描述符为应用程序与基础操作系统之间的交互提供了通用接口。
    因为应用程序打开文件的描述符列表提供了大量关于这个应用程序本身的信息，因此通过lsof工具能够查看这个列表对系统监测以及排错将是很有帮助的。
    /proc/1917  某进程动id下的 内存文件配置 还原文件？
    [1]+  已停止               ./pipe_maker.sh
    1.找到目标文件使用进程pid 7570 该文件动文件描述符 255r
    lsof | grep pipe_maker
    pipe_make 7570                walker  255r      REG                8,6      2522      17692 /home/walker/e/help_note/shell/pipe_maker.sh
    2.查看该进程文件列表
    ll /proc/7570/fd 
    lrwx------ 1 walker walker 64 1月  24 15:36 1000 -> '/home/walker/e/help_note/shell/make.7570.fifo (deleted)'
    lrwx------ 1 walker walker 64 1月  24 15:36 2 -> /dev/pts/0
    lr-x------ 1 walker walker 64 1月  24 15:36 255 -> /home/walker/e/help_note/shell/pipe_maker.sh* (deleted)
    3.读取 转储目标文件 
    cat /proc/7570/fd/255 > pipe_maker.sh
    lsof输出各列信息的意义如下：
    COMMAND：进程的名称 PID：进程标识符
    USER：进程所有者
    FD：文件描述符，应用程序通过文件描述符识别该文件。如cwd、txt等 TYPE：文件类型，如DIR、REG等
    DEVICE：指定磁盘的名称
    SIZE：文件的大小
    NODE：索引节点（文件在磁盘上的标识）
    NAME：打开文件的确切名称
    FD 列中的文件描述符cwd 值表示应用程序的当前工作目录，这是该应用程序启动的目录，除非它本身对这个目录进行更改,txt 类型的文件是程序代码，如应用程序二文件本身或共享库，如上列表中显示的 /sbin/init 程序。
    lsof abc.txt #显示开启文件abc.txt的进程 
    lsof -c abc #显示abc进程现在打开的文件 
    lsof -p 1234 #列出进程号为1234的进程所打开的文件 
    lsof -g gid #显示归属gid的进程情况 
    lsof +d /usr/local/ #显示目录下被进程开启的文件 
    lsof +D /usr/local/ E同上，但是会搜索目录下的目录，时间较长 
    lsof -d 4 #显示使用fd为4的进程 
    lsof -i #show port tcp
    lsof -i[46] [protocol][@hostname|hostaddr][:service|port]   46 --> IPv4 or IPv6   protocol --> TCP or UDP   hostname --> Internet host name   hostaddr --> IPv4地址   service --> /etc/service中的 service name (可以不止一个)   port --> 端口号 (可以不止一个)
    lsof -i:8091 端口
    
    
批量操作 重命名
7、把格式 *_?.jpg 的文件改为 *_0?.jpg：
for var in `ls *_?.jpg`; do mv "$var" `echo "$var" |awk -F '_' '{print $1 "_0" $2}'`; done
8、把文件名的前三个字母变为 vzomik：
for var in `ls`; do mv -f "$var" `echo "$var" |sed 's/^.../vzomik/'`; done
10. 把.txt变成.txt_bak 的后缀
ls *.txt|xargs -n1 -i{} mv {} {}_bak
xargs -n1 –i{} 类似for循环，-n1意思是一个一个对象的去处理，-i{} 把前面的对象使用{}取代，mv {} {}_bak 相当于 mv 1.txt 1.txt_bak
find ./*.txt -exec mv {} {}_bak \;  
这个命令中也是把{}作为前面find出来的文件的替代符，后面的”\”为”;”的脱意符，不然shell会把分号作为该行命令的结尾.
    
