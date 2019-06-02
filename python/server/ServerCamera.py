#!/usr/bin/env python
#-*- coding:utf-8 -*- 
from include import *
from cvhelp import CvHelp

@singleton
class ServerCamera:
    """ 
        Service 
        管理摄像头 识别opencv 判断处理 发送监控提醒socket推送
    """ 
    def __init__(self, serverSocket=False):
        self.ifRtmpPush = "0"
        self.serverSocket = serverSocket    # 通过此来推送关键消息
        self.pipe = False
        return

    def start(self):
        ThreadRun("Camera", self.run).start()
        pass
# 开启摄像头监控识别
    def run(self):
        self.rtmpUrl = 'rtmp://39.107.26.100:1935:1935/myapp/test1'
        db = ServiceDb()
        mycv = CvHelp()
        sleep(3)
        # 视频来源
        filePath=C.filePath
        # filePath=''
        # camera = cv2.VideoCapture(filePath+"test2.mp4") # 从文件读取视频

        camera = cv2.VideoCapture(0) # 参数0表示第一个摄像头 摄像头读取视频
        if (camera.isOpened()):# 判断视频是否打开 
            print 'Open camera'
        else:
            print 'Fail to open camera!'
            return
        camera.set(cv2.CAP_PROP_FRAME_WIDTH, 1080)  # 2560x1920 2217x2217 2952×1944 1920x1080
        camera.set(cv2.CAP_PROP_FRAME_HEIGHT, 608)
        camera.set(cv2.CAP_PROP_FPS, 1)

        # 视频属性
        size = (int(camera.get(cv2.CAP_PROP_FRAME_WIDTH)), int(camera.get(cv2.CAP_PROP_FRAME_HEIGHT)))
        sizeStr = str(size[0]) + 'x' + str(size[1])
        fps = camera.get(cv2.CAP_PROP_FPS)  # 30p/self
        fps = int(fps)
        print 'size:'+ sizeStr + ' fps:' + str(fps)  
        ss = 300
        newSize = (ss, ss * size[1] / size[0])
        print ('toSize:',newSize)
        # 视频文件保存
        # fourcc = cv2.VideoWriter_fourcc(*'XVID')
        # out = cv2.VideoWriter(filePath+'res_mv.avi',fourcc, fps, size)
        self.rtmpInit()

        lineWidth = 2 + int((size[1]-400) / 400)# 400 1 800 2 1080 3
        textSize = size[1] / 1000.0# 400 0.45 
        heightDeta = size[1] / 20 + 10# 400 20
        count = 0
        faces = []
        while True:
            ###########################图片采集
            count = count + 1
            ret, frame = camera.read() # 逐帧采集视频流
            if not ret:
                break
            detectCount = 0
            if(count % fps == 0):
            ###########################图片处理
                # 探测图片中的人脸 延帧检测
                faces = mycv.classfier.detectMultiScale(frame,scaleFactor=1.1,minNeighbors=5,minSize=(5,5))
                detectCount = len(faces)
                pass
            for (x, y, w, h) in faces:
                # cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
                mycv.drawRect(frame, (x, y), (x+w, y+h), (128, 64, 255), line_width=lineWidth )


            # 绘制推送图片帧信息
            fpsshow = "Fps  :" + str(int(fps)) + "  Frame:" + str(count)  
            nframe  = "Play :" + str(int(count / fps))
            ntime   = "Time :" + time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
            # if(count % fps == 0):
            #     print(fpsshow + " " + ntime)
            mycv.drawText(frame, (0, heightDeta * 1), fpsshow, textSize=textSize, lineWidth=lineWidth )
            mycv.drawText(frame, (0, heightDeta * 2), nframe, textSize=textSize, lineWidth=lineWidth )
            mycv.drawText(frame, (0, heightDeta * 3), ntime, textSize=textSize, lineWidth=lineWidth )

            ############################图片输出
            self.rtmpPush(frame) # 存入管道
            path1 = filePath + "_temp_now.png" 
            mycv.save(path1, frame)
            # self.sendImg(newSize, path1)


            # out.write(frame)    # 存入视频文件
            # 当发现人脸 进行 操作 
            # 保存图片文件 
            # 记录数据库  
            # 推送提醒socket 
            if(detectCount > 0):
                tt = time.strftime("%Y%m%d%H%M%S", time.localtime())
                id = 'res_' + tt + '_' + str(count) + '.png'
                msg = Msg()
                msg.data['id'] = id
                msg.data['time']=tt
                msg.data['title'] = '有人出现'
                msg.data['text'] = '图片：'+id
                msg.data['type'] = 'push'
                path = filePath + id
                mycv.save(path, frame)
                db.insertFile(id, tt, path)
                if(self.serverSocket):
                    # self.serverSocket.sendImpl(msg.toString())
                    # 结果帧处理 存入文件 / 推流 / ffmpeg 再处理
                    frame = cv2.resize(frame, newSize)
                    path = filePath + "_temp_now_small.png"
                    mycv.save(path, frame)
                    self.sendImg(msg, path)
                    pass
                pass
            
            sleep(1)
            pass
        camera.release()
        # Release everything if job is finished
        # out.release()
        print("Over!")
        pass
# 初始化rtmp推送
    def rtmpInit(self):
        if(self.ifRtmpPush != '1'):
            return
        # 管道输出 ffmpeg推送rtmp
        command = ['ffmpeg',
            '-y',
            '-f', 'rawvideo',
            '-vcodec','rawvideo',
            '-pix_fmt', 'bgr24',
            '-s', sizeStr,
            '-r', str(fps),
            '-i', '-',
            '-c:v', 'libx264',
            '-pix_fmt', 'yuv420p',
            '-preset', 'ultrafast',
            '-f', 'flv', 
            self.rtmpUrl]
        self.pipe = sp.Popen(command, stdin=sp.PIPE) #,shell=False
        pass
    def rtmpPush(self, frame):




        if(self.pipe):
            self.pipe.stdin.write(frame.tostring()) 
        pass
    def sendImg(self, msg, path):
        # frame = mycv.getGray(frame) #0-255
        # frame = cv2.resize(frame, newSize)
        # # print(frame.size)
        # print(frame)
        # byts = tool.makeByte(frame)
        # msg = Msg()
        # msg.data['res'] = byts
        # msg.data['w'] = newSize[0]
        # msg.data['h'] = newSize[1]
        # msg.data['cmd'] = MSGTYPE.SYS_PHOTO #图片数据
        # self.serverSocket.sendImpl(msg.toString())
        with open(path, 'rb') as f:
            byts = base64.b64encode(f.read())
            msg.data['res'] = byts
            # msg.data['w'] = newSize[0]
            # msg.data['h'] = newSize[1]
            msg.data['cmd'] = MSGTYPE.SYS_PHOTO # 图片数据
            self.serverSocket.sendImpl(msg.toString())





# 关闭监控识别
    def stop(self):
        pass

# 开启推送视频
    def openPush(self):
        self.ifRtmpPush = "1"
# 关闭推送视频
    def closePush(self):
        self.ifRtmpPush = "0"




 
    def toString(self):
        res = "" 

        return res


if __name__ == '__main__':
    serviceCamera = ServerCamera(False)

    serviceCamera.start()
