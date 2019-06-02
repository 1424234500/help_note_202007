## 记事本
notepad++ c语言显示 ./正则加粗 //注释变色 1.序号变色 #号变色
retext   md格式    见markdown.md介绍使用方式

## 命令执行注释规范
date --help
Display the current time in the given FORMAT, or set the system date.
Usage: date [-u|--utc|--universal] [MMDDhhmm[[CC]YY][.ss]]
  -d, --date=STRING          display time described by STRING, not 'now'
      --debug                annotate the parsed date,
  -f, --file=DATEFILE        like --date; once for each line of DATEFILE
  -r, --reference=FILE       display the last modification time of FILE
  -s, --set=STRING           set time described by STRING
  -u, --utc, --universal     print or set Coordinated Universal Time (UTC)
      --help		显示此帮助信息并退出
      --version		显示版本信息并退出


# help_note
这是学习途中所涉及到的 脚本类的各种语言(cmd,shell,python...) 各种帮助文档(正则,wireshark,nginx,makefile,git,gcc,ffmpeg,opencv,mysql,oracle,redis...) 及demo案例以及工具(个人项目git同步,差异制作补丁,cmd启动常用软件...)

# 项目路径结构
    
## python
* server
python后台通信服务提供以及树莓派专用的GPIO控制
    * server_http.py    基于python-tornado模块提供的http后台服务
    * HandlerSystem.py  tornado的树莓派系统业务处理
    * HandlerStudent.py tornado的简易表业务处理

    * server.py 树莓派后台服务器整合启动 连接各个GPIO各个后台服务集成长连接通信

    * ServiceServer.py  socket的树莓派系统业务处理
    * ServiceCamera.py  树莓派视频采集识别推送rtmp模块

    * server_socket.py 基于socket模块提供的长连接通信服务
    * server_socketio.py 基于Flask socketio模块提供的websocket后台服务

    * system.py    树莓派GPIO控制基本工具
    * ModelMove.py 逻辑控制四个端口的开1关0pwm来实现小车移动和调速
    * ModelTurn.py 逻辑控制一个端口的pwm来控制G90舵机的旋转
* opencv
opencv-python的使用学习
    * cvhelp.py  opencv常用图形学处理及其工具类(初学老是记不住官方opencv api倒是会很容易的想起自己封装的工具函数别名) 简单图形处理 人脸检测测试 数独的简易knn文字训练和识别案例
    * Sudo.py    数独的解答算法
* http.py   python http访问工具类 包含了json->dict解析 get post cookie session集成
* socketIo.py   python socketIo-client 客户端工具 实现长连接
* auto163.py    通过http调用网易云搜索音乐分享实际地址
* robot.py  融合sqlite、http实现图灵123机器人智能应答接口并记录数据库日志
* python_sqlite.py  sqlite3工具类dao
* python_singleton.py   装饰器实现的单例注解工具
* show_dir.py   文件夹递归遍历文件处理
* tool.py   常用python工具类 比如递归编码dict 随机数 时间格式化等
* python_coding.py  python编程的常用语法 dict list string 相关数据操作api
## cmd
把该路径添入到windows环境变量path中，便可以根据该路径下的脚本名快捷调用bat eg: win+R cc/enter即可打开取色器
* ss.bat
    * windows开机后，使用该脚本快速一口气启动常用的全部软件，就不用再到处点点点了（虽然也可设置软件开机启动的说，但是个人比较排斥启动项）
* ls.bat
    * 实际上是调用的dir，因为习惯了ls ll，cmd环境下没有很难受
* cc.exe 颜色取色器
* no.bat 实现命令重启node
## shell
* do
    * 各种do_*.sh文件的启动入口
    ./do socket all 打包socket项目 压缩 上传 解压 重启
* do_git.sh
    * 个人的各git仓库路径配置，实现./do update/push/init 来达到初始化 更新 推送所有配置    的项目
* help_git.sh
    * 工作所需要的 仓库a提交后需要差异同步到仓库b
* shell_help.c
    * shell学习中整理的和遇到的一些常识性问题介绍
* shell_coding.c
    * shell编程学习中整理的常用的语法规则 if for function 数组 字符串等操作
* help_server.sh    shell程序管理工具 只编写其中的执行命令和日志文件后 即可方便的实现该程序的 日志 重启


