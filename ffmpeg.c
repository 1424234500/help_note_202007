
ffmpeg  -f v4l2 -s 640x480 -r 25 -i /dev/video0 -vcodec h264 -preset veryfast -tune zerolatency  -g 6 -threads 4 -f flv rtmp://39.107.26.100:1935:1935/myapp/test1
ffmpeg  -f v4l2 -s 640x480 -r 5 -i /dev/video0 -vcodec h264 -preset veryfast -tune zerolatency  -g 6 -threads 4 -f flv rtmp://39.107.26.100:1935:1935/myapp/test1
ffmpeg  -f v4l2 -s 800x600 -r 1 -i /dev/video0 -vcodec h264 -preset medium -tune zerolatency  -g 6 -threads 4 -f flv rtmp://39.107.26.100:1935:1935/myapp/test1
ffmpeg  -f v4l2 -s 800x600 -r 1 -i /dev/video0 -vcodec h264  -profile:v baseline  -preset veryfast -tune zerolatency  -g 6 -threads 4 -f flv rtmp://39.107.26.100:1935:1935/myapp/test1


ffmpeg  -f v4l2 -s 800x600 -r 1 -i /dev/video0 -vcodec h264     -g 6 -threads 4 -f flv rtmp://39.107.26.100:1935:1935/myapp/test1


ffmpeg  -f v4l2 -s 200x150 -r 5 -i /dev/video0 -vcodec h264 -preset veryfast -tune zerolatency  -g 6 -threads 4 -f flv rtmp://39.107.26.100:1935:1935/myapp/test1


raspivid -t 0 -w 320 -h 240 -o - | ffmpeg -i - -s 320x240 -f mpeg1video -b 800k -r 30 rtmp://39.107.26.100:1935:1935/myapp/test1


sudo ffmpeg -f v4l2 -i /dev/video0 -c libx264 -profile:v high -preset:v medium \
   -b:v 300k -s 800x600 -r 30 -an \
    -f flv -y rtmp://39.107.26.100:1935:1935/myapp/test1

sudo ffmpeg -f v4l2 -i /dev/video0 -c libx264 -profile:v main -preset:v medium \
   -b:v 300k -s 800x600 -r 25 -an \
    -f flv -y rtmp://39.107.26.100:1935:1935/myapp/test1
2560x1920  -fflags nobuffer 
rtmp://127.0.0.1:1935/myapp/test1
rtmp://192.168.191.1:1935/myapp/test1
rtmp://39.107.26.100:1935:1935/myapp/test1
2560*1920 
可以修改 profile 为 high, main, baseline 
可是修改 preset 为 veryfast, fast, medium, slow, slower

//采集视频
1、列表本机的视音频设备 
ffplay -list_devices true -f dshow video=0
ffmpeg -list_devices true -f dshow video=0
"Integrated Camera"
"Internal Microphone (Conexant SmartAudio HD)"
这句话列出了我电脑上的摄像头和音频设备
2、窗口播放  不配置-i则窗口播放
ffplay -f dshow video="Integrated Camera"
这句话打开了我的摄像头 -i 输出文件流
3、捕获  
ffmpeg -f dshow -i video="Integrated Camera" e:/nginx-rtmp/test2.mp4 
这句话开始采集视频。音频部分未加上。

ffmpeg -f dshow -i video="Integrated Camera" flv rtmp://127.0.0.1:1935/myapp/test1


ffmpeg -f dshow -i video="Integrated Camera" -s 640x360 -vcodec libx264 -b:v 1000k   -ab 128k -f flv rtmp://127.0.0.1:1935/myapp/test1
//10s延时 无配置采集推送rtmp
ffmpeg -f dshow -i video="Integrated Camera" -s 320x240 -f flv rtmp://127.0.0.1:1935/myapp/test1 
ffmpeg -f dshow -i video="Integrated Camera" -f flv rtmp://127.0.0.1:1935/myapp/test1 
ffplay -f dshow video="Integrated Camera"  -video_size 1280x720

ffmpeg -f dshow -i video="Integrated Camera" -s 640x480 -f flv rtmp://127.0.0.1:1935/myapp/test1 
ffmpeg -f dshow -i video="Integrated Camera" -s 640x480 -f flv rtmp://39.107.26.100:1935/myapp/test1 
ffmpeg -y -f rawvideo -vcodec rawvideo -pix_fmt bgr24 -i - -c:v libx264 -pix_fmt yuv420p -preset ultrafast -f flv rtmp://39.107.26.100:1935/myapp/test1
-vf drawtext="fontfile=arial.ttf:x=w-tw:fontcolor=white:fontsize=30:text='%{localtime:%H\:%M\:%S}'"
-c:a copy -c:v libx264 -vpre slow 
ffmpeg -f dshow -i video="Integrated Camera" -s 1280x720 -c:a copy -c:v libx264 -f flv rtmp://39.107.26.100:1935/myapp/test1 
ffmpeg -f dshow -i video="Integrated Camera"  -c:a copy -c:v libx264 -f flv rtmp://39.107.26.100:1935/myapp/test1 

rtmp://127.0.0.1:1935/myapp/test1
rtmp://192.168.191.1:1935/myapp/test1
rtmp://39.107.26.100:1935:1935/myapp/test1

ffmpeg -f image2pipe -r 10 -vcodec mjpeg -i /tmp/my_fifo
-f强制指定了输入文件的格式，就是从流中读取数据
-r指定了帧率
-vcodec应该是指定了该流的文件格式
/tmp/my_fifo 是自己提前创建好的fifo，通过mkfifo /tmp/my_fifo创建
执行这条指令之后，ffmpeg会阻塞监听直到my_fifo中有数据并且pipe关闭为止

ffmpeg -f dshow -i video="Integrated Camera" -tune zerolatency -vcodec libx264 -preset ultrafast -b:v 400k -s 720x576 -r 25 -f flv rtmp://39.107.26.100:1935/myapp/test1 
ffmpeg -f dshow -i video="Integrated Camera" -vcodec libx264 -b:v 400k -s 720x576 -r 25 -f flv rtmp://39.107.26.100:1935/myapp/test1 


1、将文件当做直播送至live
ffmpeg -re -i localFile.mp4 -c copy -f flv rtmp://server/live/streamName
2、将直播媒体保存至本地文件
ffmpeg -i rtmp://server/live/streamName -c copy dump.flv
3、将其中一个直播流，视频改用h264压缩，音频不变，送至另外一个直播服务流
ffmpeg -i rtmp://server/live/originalStream -c:a copy -c:v libx264 -vpre slow -f flv rtmp://server/live/h264Stream
4、将其中一个直播流，视频改用h264压缩，音频改用faac压缩，送至另外一个直播服务流
ffmpeg -i rtmp://server/live/originalStream -c:a libfaac -ar 44100 -ab 48k -c:v libx264 -vpre slow -vpre baseline -f flv rtmp://server/live/h264Stream
5、将其中一个直播流，视频不变，音频改用faac压缩，送至另外一个直播服务流
ffmpeg -i rtmp://server/live/originalStream -acodec libfaac -ar 44100 -ab 48k -vcodec copy -f flv rtmp://server/live/h264_AAC_Stream
6、将一个高清流，复制为几个不同视频清晰度的流重新发布，其中音频不变
ffmpeg -re -i rtmp://server/live/high_FMLE_stream -acodec copy -vcodec x264lib -s 640×360 -b 500k -vpre medium -vpre baseline rtmp://server/live/baseline_500k -acodec copy -vcodec x264lib -s 480×272 -b 300k -vpre medium -vpre baseline rtmp://server/live/baseline_300k -acodec copy -vcodec x264lib -s 320×200 -b 150k -vpre medium -vpre baseline rtmp://server/live/baseline_150k -acodec libfaac -vn -ab 48k rtmp://server/live/audio_only_AAC_48k
7、功能一样，只是采用-x264opts选项
ffmpeg -re -i rtmp://server/live/high_FMLE_stream -c:a copy -c:v x264lib -s 640×360 -x264opts bitrate=500:profile=baseline:preset=slow rtmp://server/live/baseline_500k -c:a copy -c:v x264lib -s 480×272 -x264opts bitrate=300:profile=baseline:preset=slow rtmp://server/live/baseline_300k -c:a copy -c:v x264lib -s 320×200 -x264opts bitrate=150:profile=baseline:preset=slow rtmp://server/live/baseline_150k -c:a libfaac -vn -b:a 48k rtmp://server/live/audio_only_AAC_48k
8、将当前摄像头及音频通过DSSHOW采集，视频h264、音频faac压缩后发布
ffmpeg -r 25 -f dshow -s 640×480 -i video=”video source name”:audio=”audio source name” -vcodec libx264 -b 600k -vpre slow -acodec libfaac -ab 128k -f flv rtmp://server/application/stream_name
9、将一个JPG图片经过h264压缩循环输出为mp4视频
ffmpeg.exe -i INPUT.jpg -an -vcodec libx264 -coder 1 -flags +loop -cmp +chroma -subq 10 -qcomp 0.6 -qmin 10 -qmax 51 -qdiff 4 -flags2 +dct8x8 -trellis 2 -partitions +parti8x8+parti4x4 -crf 24 -threads 0 -r 25 -g 25 -y OUTPUT.mp4
10、将普通流视频改用h264压缩，音频不变，送至高清流服务(新版本FMS live=1)
ffmpeg -i rtmp://server/live/originalStream -c:a copy -c:v libx264 -vpre slow -f flv “rtmp://server/live/h264Stream live=1〃
时间显示
ffplay jidu.mp4 -vf drawtext=”fontfile=arial.ttf:x=w-tw:fontcolor=white:fontsize=30:text=’%{localtime:%H\:%M\:%S}’“



