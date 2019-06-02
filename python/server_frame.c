
#项目组件架构   Tomcat    python-web<GPIO>   python-socket  
#nginx          链接代理转发请求  并提供 图片/视频流推送-服务
#运行环境       PC  Raspberry sqlite数据库

# socket-python ----  socket-java ---- socket-android1
                                  ---- socket-android2
                                  ---- socket-android3
PI-mac
IP:  192.168.1.10
MAC: B8:27:EB:85:06:17

#项目部署流程
//启动脚本 cd shell ./do start

<PC>

    tomcat 8080    
        tomcat/bin/start.sh
        #http://127.0.0.1:8088/BaseSSM/lunch/list.do
    socket-server 8092
    socket-web  app    
    http-web    app
    
<Raspberry>

//  web tornado         短连接         <根据即时消息>获取静态资源
    python /help_note/python/server/server_web.py
    #http://127.0.0.1:8088/do/student/mm/a

//  socket-io           长连接-web     
    python /help_note/python/server/server_socket.py
    #127.0.0.1:8087 emit onMsg

//  socket              长连接-socket  推送即时信息
    python /help_note/python/server/server_socket.py
    #127.0.0.1:8086 emit onMsg

    python GPIO opencv  工具控制类  供python通信服务器调用 控制设备行为

//  Nginx  8088     <Raspberry>
    静态路由    前端页面    静态资源
    app/html-angular
    app/resource
    http://127.0.0.1:8088/app/#

    后台路由
    ->Tomcat
    ->Python
        -web
        -socketIo server 
        -socket client
 




监控设计




推送流工具
采集流 - cv处理 - 输出流 - 推送工具/部署站点 《 《 《 访问地址获取流
              文件读取流 - 推送工具/部署站点 《 《 《 访问地址获取流







自定义实现？： 
    图片采集 加工 定时覆盖 前端轮循短连接 介于浏览器同url不重新加载问题 规定时间轴取整 命名 定时更新前后端同步
                  定时推送 socket长连接

                  写入         流         前端video流加载
                            管道/文件                  

//nginx-rtmp直播点播系统

rtmp { # 配置RTMP模块
    server { # 服务器
        listen 1935; # 监听端口, 默认为1935
        chunk_size 4000; # 数据块大小 4000
        
        application hls {     
            live on;    
            hls on;    
            hls_path E:/nginx-rtmp/hls;    #文件存放地址,/tmp/hls
        }
        
        application myapp { # 应用名称, 可理解为直播房间的名称
            live on; # 直播 [on]开启
        }

    }
} 
http配置地址跳转 直播
location /hls {    
    types {    
        application/vnd.apple.mpegurl m3u8;    
        video/mp2t ts;    
    }    
    root E:/nginx-rtmp;    
    add_header Cache-Control no-cache;    
} 

//vlc播放地址
rtmp://127.0.0.1:1935/myapp/test1
//可用推送地址
ffmpeg -re -i test.mp4 -c copy -f flv rtmp://127.0.0.1:1935/myapp/test1

//hls模式
相对于常见的流媒体直播协议，例如RTMP协议、RTSP协议、MMS协议等，HLS直播最大的不同在于，直播客户端获取到的，并不是一个完整的数据流。HLS协议在服务器端将直播数据流存储为连续的、很短时长的媒体文件（MPEG-TS格式），而客户端则不断的下载并播放这些小文件，因为服务器端总是会将最新的直播数据生成新的小文件，这样客户端只要不停的按顺序播放从服务器获取到的文件，就实现了直播。由此可见，基本上可以认为，HLS是以点播的技术方式来实现直播。由于数据通过HTTP协议传输，所以完全不用考虑防火墙或者代理的问题，而且分段文件的时长很短，客户端可以很快的选择和切换码率，以适应不同带宽条件下的播放。不过HLS的这种技术特点，决定了它的延迟一般总是会高于普通的流媒体直播协议。
rtmp://127.0.0.1:1935/hls/test2
ffmpeg -re -i test.mp4 -c copy -f flv rtmp://127.0.0.1:1935/hls/test2




##################################################################################

#user  nobody;
worker_processes  1;

#error_log  logs/error.log;
#error_log  logs/error.log  notice;
#error_log  logs/error.log  info;

#pid        logs/nginx.pid;


events {
    worker_connections  1024;
}

rtmp { # 配置RTMP模块
    server { # 服务器
        listen 1935; # 监听端口, 默认为1935
        chunk_size 4000; # 数据块大小 4000
        

        application hls {     
            live on;    
            hls on;    
            hls_path E:/nginx-rtmp/hls;    #文件存放地址,/tmp/hls
        }
        
        application myapp { # 应用名称, 可理解为直播房间的名称
            live on; # 直播 [on]开启
        }

    }
}   



http {
    include       mime.types;
    default_type  application/octet-stream;

    #log_format  main  '$remote_addr - $remote_user [$time_local] "$request" '
    #                  '$status $body_bytes_sent "$http_referer" '
    #                  '"$http_user_agent" "$http_x_forwarded_for"';

    #access_log  logs/access.log  main;

    sendfile        on;
    #tcp_nopush     on;

    #keepalive_timeout  0;
    keepalive_timeout  65;

    #gzip  on;

    #Tomcat 
    upstream base {
        server 127.0.0.1:8085 weight=1;    
    }  
    #RaspBerry python tornado
    upstream python {
        server 127.0.0.1:8086 weight=1;    
    }  
    #RaspBerry python socket
    upstream socket {
        server 127.0.0.1:8087 weight=1;    
    }  
    
     
    server {
        listen 8088;
        server_name localhost;
        
        # rtmp hls http直播
        location /hls {    
            types {    
                application/vnd.apple.mpegurl m3u8;    
                video/mp2t ts;    
            }    
            root E:/nginx-rtmp;    
            add_header Cache-Control no-cache;    
        } 
        location /app {
            root E:/help_note/python;
            autoindex on;
        }
        location /do { 
            proxy_pass http://python;
        }
        location /BaseSSM { 
            proxy_pass http://base;
        }
        location / {
            root E:/help_note;
        }
    }

 

}































