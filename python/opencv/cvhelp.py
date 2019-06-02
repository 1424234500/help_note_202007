#!/usr/bin/python
#-*- coding:utf-8 -*-  
import cv2
import numpy
import numpy as np
import time
import sys
import subprocess as sp

sys.path.append("../")
# 导入单例装饰器函数 : @singleton
from python_singleton import singleton
from Sudo import *
from FileUtil import *

@singleton
class CvHelp:

    """ My OpenCv helper """ 
# 初始化
    def __init__(self):
        self.id = "test id"
        self.name = "test name"
        self.classfier = cv2.CascadeClassifier("haarcascade_frontalface_default.xml")  

#################################################################

    #轮廓检测绘制
    def getContours(self, img):
        # cv2.findContours(image, mode, method[, contours[, hierarchy[, offset ]]])  
        # 返回两个值：contours：hierarchy。
        # 参数
        # 第一个参数是寻找轮廓的图像；
        # 第二个参数表示轮廓的检索模式，有四种（本文介绍的都是新的cv2接口）：
        #     cv2.RETR_EXTERNAL表示只检测外轮廓
        #     cv2.RETR_LIST检测的轮廓不建立等级关系
        #     cv2.RETR_CCOMP建立两个等级的轮廓，上面的一层为外边界，里面的一层为内孔的边界信息。如果内孔内还有一个连通物体，这个物体的边界也在顶层。
        #     cv2.RETR_TREE建立一个等级树结构的轮廓。
        # 第三个参数method为轮廓的近似办法
        #     cv2.CHAIN_APPROX_NONE存储所有的轮廓点，相邻的两个点的像素位置差不超过1，即max（abs（x1-x2），abs（y2-y1））==1
        #     cv2.CHAIN_APPROX_SIMPLE压缩水平方向，垂直方向，对角线方向的元素，只保留该方向的终点坐标，例如一个矩形轮廓只需4个点来保存轮廓信息
        #     cv2.CHAIN_APPROX_TC89_L1，CV_CHAIN_APPROX_TC89_KCOS使用teh-Chinl chain 近似算法
        binary = self.getBinary(img)  
        _, contours, hierarchy = cv2.findContours(binary,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)  
        # 需要搞一个list给cv2.drawContours()才行！！！！！
        c_max = []
        for i in range(len(contours)):
            cnt = contours[i]
            area = cv2.contourArea(cnt)
            # 处理掉小的轮廓区域，这个区域的大小自己定义。
            if(area < (1000)):
                c_min = []
                c_min.append(cnt)
                # thickness不为-1时，表示画轮廓线，thickness的值表示线的宽度。
                cv2.drawContours(img, c_min, -1, (0,255,0), thickness=-1)
                continue
            c_max.append(cnt)
        cv2.drawContours(img, c_max, -1, (0, 0, 255), thickness=2)

        return img
    #直方图均衡化处理
    def getLut(self, img):
        image = img  

        lut = np.zeros(256, dtype = image.dtype )#创建空的查找表
        hist= cv2.calcHist([image], #计算图像的直方图
            [0], #使用的通道
            None, #没有使用mask
            [256], #it is a 1D histogram
            [0.0,255.0])
            
        minBinNo, maxBinNo = 0, 255

        #计算从左起第一个不为0的直方图柱的位置
        for binNo, binValue in enumerate(hist):
            if binValue != 0:
                minBinNo = binNo
                break
        #计算从右起第一个不为0的直方图柱的位置
        for binNo, binValue in enumerate(reversed(hist)):
            if binValue != 0:
                maxBinNo = 255-binNo
                break
        #print (minBinNo, maxBinNo)

        #生成查找表，方法来自参考文献1第四章第2节
        for i,v in enumerate(lut):
            if i < minBinNo:
                lut[i] = 0
            elif i > maxBinNo:
                lut[i] = 255
            else:
                lut[i] = int(255.0*(i-minBinNo)/(maxBinNo-minBinNo)+0.5)

        #计算
        result = cv2.LUT(image, lut) 

        return result    
    #hough直线检测
    def getHough(self, img):  
        img = self.getGray(img)
        img = cv2.GaussianBlur(img,(3,3),0)
        edges = self.testCanny(img)#cv2.Canny(img, 50, 150, apertureSize = 3)
        lines = cv2.HoughLines(edges,1,np.pi/180,118)
        result = img.copy()

        #经验参数
        minLineLength = 200
        maxLineGap = 15
        lines = cv2.HoughLinesP(edges,1,np.pi/180,80,minLineLength,maxLineGap)
        #print(lines)
        for line in lines:
            for x1,y1,x2,y2 in line:
                cv2.line(result,(x1,y1),(x2,y2),(0, 0, 255),3)
        return result 
    #canny边缘检测
    def getCanny(self, img):
        img = self.getGray(img)

        img = cv2.GaussianBlur(img,(3,3),0)  
        canny = cv2.Canny(img, 50, 150, apertureSize = 3)  
        return canny
    #laplacian算子
    def getLaplacian(self, imgg):
        img = self.getGray(imgg)
    
        gray_lap = cv2.Laplacian(img,cv2.CV_16S,ksize = 3)
        imgLaplacian = cv2.convertScaleAbs(gray_lap)

        imgGaussian = cv2.GaussianBlur(img,(5,5),1.5)  #去噪

        #dst = cv2.Laplacian(src, ddepth[, dst[, ksize[, scale[, delta[, borderType]]]]])  
        # 如果看了上一篇Sobel算子的介绍，这里的参数应该不难理解。 
        # 前两个是必须的参数：
        # •第一个参数是需要处理的图像；
        # •第二个参数是图像的深度，-1表示采用的是与原图像相同的深度。目标图像的深度必须大于等于原图像的深度；
        # 其后是可选的参数：
        # •dst不用解释了；
        # •ksize是算子的大小，必须为1、3、5、7。默认为1。
        # •scale是缩放导数的比例常数，默认情况下没有伸缩系数；
        # •delta是一个可选的增量，将会加到最终的dst中，同样，默认情况下没有额外的值加到dst中；
        # •borderType是判断图像边界的模式。这个参数默认值为cv2.BORDER_DEFAULT。
        gray_lap = cv2.Laplacian(imgGaussian,cv2.CV_16S,ksize = 3)
        imgLaplacian = cv2.convertScaleAbs(gray_lap)

        return imgLaplacian
    #sabel算子
    def getSabel(self, imgg):
        img = self.getGray(imgg)

        #dst = cv2.Sobel(src, ddepth, dx, dy[, dst[, ksize[, scale[, delta[, borderType]]]]])  
        #•图形，
        #•深度，-1表示采用的是与原图像相同的深度。目标图像的深度必须大于等于原图像的深度 
        #•dx和dy表示的是求导的阶数，0表示这个方向上没有求导，一般为0、1、2
        #•ksize是Sobel算子的大小，必须为1、3、5、7。
        #•scale是缩放导数的比例常数，默认情况下没有伸缩系数；
        #•delta是一个可选的增量，将会加到最终的dst中，同样，默认情况下没有额外的值加到dst中；
        #•borderType是判断图像边界的模式。这个参数默认值为cv2.BORDER_DEFAULT。
        x = cv2.Sobel(img,cv2.CV_16S,1,0)
        y = cv2.Sobel(img,cv2.CV_16S,0,1)
        #Sobel函数求完导数后会有负值，还有会大于255的值。而原图像是uint8，即8位无符号数，所以Sobel建立的图像位数不够，会有截断。因此要使用16位有符号的数据类型，即cv2.CV_16S。
        #在经过处理后，别忘了用convertScaleAbs()函数将其转回原来的uint8形式。否则将无法显示图像，而只是一副灰色的窗口
        absX = cv2.convertScaleAbs(x)   # 转回uint8
        absY = cv2.convertScaleAbs(y)
        #Sobel算子是在两个方向计算的，最后还需要用cv2.addWeighted(...)函数将其组合起来
        imgSabel = cv2.addWeighted(absX,0.5,absY,0.5,0)

        return imgSabel
    #初级滤波
    def getBlur(self, imgg, count=1):
        img = self.getGray(imgg)
        #用低通滤波来平滑图像 将每个像素替换为该像素周围像素的均值
        #imgBlur = cv2.blur(img, (5,5)) 
        #高斯模糊
        for j in range(count):
            imgGaussian = cv2.GaussianBlur(img,(5,5),1.5)  
        #低通滤波中，滤波器中每个像素的权重是相同的，即滤波器是线性的。而高斯滤波器中像素的权重与其距中心像素的距离成比例

        return imgGaussian
    #形态学处理 
    #检测拐角
    def getFindTurn(self, imgg): 
        image = self.getGray(imgg)
        #构造5×5的结构元素，分别为十字形、菱形、方形和X型
        cross = cv2.getStructuringElement(cv2.MORPH_CROSS,(5, 5))
        #菱形结构元素的定义稍麻烦一些
        diamond = cv2.getStructuringElement(cv2.MORPH_RECT,(5, 5))
        diamond[0, 0] = 0
        diamond[0, 1] = 0
        diamond[1, 0] = 0
        diamond[4, 4] = 0
        diamond[4, 3] = 0
        diamond[3, 4] = 0
        diamond[4, 0] = 0
        diamond[4, 1] = 0
        diamond[3, 0] = 0
        diamond[0, 3] = 0
        diamond[0, 4] = 0
        diamond[1, 4] = 0
        square = cv2.getStructuringElement(cv2.MORPH_RECT,(5, 5))
        x = cv2.getStructuringElement(cv2.MORPH_CROSS,(5, 5))
        #使用cross膨胀图像
        result1 = cv2.dilate(image,cross)
        #使用菱形腐蚀图像
        result1 = cv2.erode(result1, diamond)

        #使用X膨胀原图像 
        result2 = cv2.dilate(image, x)
        #使用方形腐蚀图像 
        result2 = cv2.erode(result2,square)

        #result = result1.copy()
        #将两幅闭运算的图像相减获得角 
        result = cv2.absdiff(result2, result1)
        #使用阈值获得二值图
        retval, result = cv2.threshold(result, 40, 255, cv2.THRESH_BINARY)

        #在原图上用半径为5的圆圈将点标出。
        for j in range(result.size):
            y = j / result.shape[0] 
            x = j % result.shape[0] 
            if result[x, y] == 255:
                cv2.circle(image, (y, x), 5, (255,0,0))

        return image
    #边缘检测
    def getFindLine(self, imgg):
        imgg = self.getGray(imgg)

        #构造一个3×3的结构元素 
        element = cv2.getStructuringElement(cv2.MORPH_RECT,(3, 3))
        dilate = cv2.dilate(imgg, element)
        erode = cv2.erode(imgg, element)

        #将两幅图像相减获得边，第一个参数是膨胀后的图像，第二个参数是腐蚀后的图像
        result = cv2.absdiff(dilate,erode);

        #上面得到的结果是灰度图，将其二值化以便更清楚的观察结果
        retval, result = cv2.threshold(result, 40, 255, cv2.THRESH_BINARY); 
        #反色，即对二值图每个像素取反
        result = cv2.bitwise_not(result); 

        return result
    #开闭运算 
    def getOpen(self, imgg): 
        img = imgg.copy()
        img = self.getGray(img)
        #定义结构元素
        kernel = cv2.getStructuringElement(cv2.MORPH_RECT,(5, 5))
        #开运算
        opened = cv2.morphologyEx(img, cv2.MORPH_OPEN, kernel) 
        return opened
    #开闭运算 
    def getClose(self, imgg): 
        img = imgg.copy()
        img = self.getGray(img)

        #定义结构元素
        kernel = cv2.getStructuringElement(cv2.MORPH_RECT,(5, 5))
        closed = cv2.morphologyEx(img, cv2.MORPH_CLOSE, kernel) 
        return closed
    #腐蚀-膨胀
    def getErode(self, imgg):  
        img = self.getBinary(imgg)

        #OpenCV定义的结构元素
        kernel = cv2.getStructuringElement(cv2.MORPH_RECT,(3, 3))
        #腐蚀图像
        eroded = cv2.erode(img,kernel)
        return eroded
    #腐蚀-膨胀
    def getDilate(self, imgg):  
        img = self.getBinary(imgg)

        #OpenCV定义的结构元素
        kernel = cv2.getStructuringElement(cv2.MORPH_RECT,(3, 3))
        #膨胀图像
        dilated = cv2.dilate(img,kernel)
        return dilated
    #RGB GRAY BINARY图片转为二值图
    def getBinary(self, imgg, type=0, border=3):
        rgbSize = self.getImageType(imgg) 
        # 二值图点[(0, 0, (0/255) )]
        # 灰度图点[(0, 0, (0~255) )]
        if(rgbSize == 1):
            img = imgg
        elif(rgbSize == 2):  
            if(type == 0):
                #自适应阈值 决定是否反转颜色 边框宽度
                imgBlack = cv2.adaptiveThreshold(imgg,255,cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY_INV, border,2)
            else:
                #普通127阈值
                ret,imgBlack = cv2.threshold(imgg,127,255,cv2.THRESH_BINARY) #转二值图 
            img = imgBlack 
        # 彩色图点[(0, 0, (0~255, 0~255, 0~255) )]
        elif(rgbSize == 3):  
            imgGray = self.getGray(imgg)
            return self.getBinary(imgGray)
        return img
    #转二值图   
    def getGray(self, img):
        imgType = self.getImageType(img) 
        if(imgType == 3):
            res = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        else:
            res = img
        return res
    #绘制 三通道 折线图
    def getHistRGB(self, image):
        h = numpy.zeros((256,256,3)) #创建用于绘制直方图的全0图像    

        bins = numpy.arange(256).reshape(256,1) #直方图中各bin的顶点位置    
        color = [ (255,0,0),(0,255,0),(0,0,255) ] #BGR三种颜色    
        for ch, col in enumerate(color):   
            originHist = cv2.calcHist([image],[ch],None,[256],[0,256])    
            cv2.normalize(originHist, originHist,0,255*0.9,cv2.NORM_MINMAX)    
            hist=numpy.int32(numpy.around(originHist))    
            pts = numpy.column_stack((bins,hist))    
            cv2.polylines(h,[pts],False,col)    

        h=numpy.flipud(h)    
        return h
    #绘制 单通道 直方图
    def getHist(self, image, color):    
        hist= cv2.calcHist([image], [0], None, [256], [0.0,255.0])    

        # hist = cv2.calcHist([image],  
        #     [0], #使用的通道  
        #     None, #没有使用mask  
        #     [256], #HistSize  
        #     [0.0,255.0]) #直方图柱的范围  

        minVal, maxVal, minLoc, maxLoc = cv2.minMaxLoc(hist)    
        histImg = numpy.zeros([256,256,3], numpy.uint8)    
        hpt = int(0.9* 256);    

        for h in range(256):    
            intensity = int(hist[h]*hpt/maxVal)    
            cv2.line(histImg,(h,256), (h,256-intensity), color)    

        return histImg;   

#################################################################

    #画圆
    def drawCircle(self, image, point=(100,100), radius=60, rgb=(255,128,255), line_width=4, line_type=8):
        cv.circle(image, point, radius, rgb, line_width, line_type)
        return image
    #画线 
    def drawLine(self, image, start_point=(0,0), end_point=(0,0), rgb=(255,128,255), line_width=4, line_type=8):
        cv.line(image, start_point, end_point, rgb, line_width, line_type)
        return image
    #画矩形
    def drawRect(self, image, start_point=(0,0), end_point=(10,20), rgb=(255,128,255), fill=False, line_width=4, line_type=8):
        # print(rgb, fill)
        if(fill):
            points = numpy.array([ start_point, [start_point[0], end_point[1]], end_point, [end_point[0],start_point[1]] ], numpy.int32)
            #[1，3]，[4，8],[1,9]为要填充的轮廓坐标
            # print(points)
            cv2.fillConvexPoly(image, points, rgb)
        else:
            cv2.rectangle(image, start_point, end_point, rgb, line_width, line_type)
        return image
    #画text
    def drawText(self, image, point=(100,100), string="drawText", rgb=(0,64,64), textSize=0.45, lineWidth=1):
        cv2.putText(image,str(string),  point,      0,      textSize,       rgb,     lineWidth)
        # 照片/添加的文字/              左上角坐标/ 字体/   字体大小/ 颜色/     字体粗细
        return image

#################################################################

    #创建图片 大小
    def createImage(self, width=256, height=256, rgb=(0,255,0)):
        image = np.zeros((height, width, 3), dtype=np.uint8)
        image = self.drawRect(image, (0,0), (width,height), rgb, fill=True)
        return image
    #保存图片
    def save(self, name, img):
        cv2.imwrite(name, img)
        return
    #0~255, 0~255, 0~255
    #打开图片
    def open(self, name):
        return cv2.imread(name)
    #0~255
    def openGray(self, name):
        return cv2.imread(name, cv2.IMREAD_GRAYSCALE)
    #0/255
    def openBinary(self, name):
        img = cv2.imread(name, cv2.IMREAD_GRAYSCALE)
        return self.getBinary(img) 
    #0/1
    def openZero(self, name):
        img = cv2.imread(name, cv2.IMREAD_GRAYSCALE)
        binary = self.getBinary(img)
        return binary/255.
    #矩形框绘制轮廓
    def drawRectangle(self, img, contours, hierarchy):
        img = img.copy()
        boxes = []
        for i in range(len(hierarchy[0])):
            boxes.append(hierarchy[0][i])
        number_boxes = []
        for j in range(len(boxes)):
            x,y,w,h = cv2.boundingRect(contours[boxes[j][2]])
            number_boxes.append([x,y,w,h])
            img = cv2.rectangle(img,(x-1,y-1),(x+w+1,y+h+1),(0,0,255),2)
        return img
    #指定规则绘制轮廓
    def drawImage(self, imgg, contours, size=10):
        img = imgg.copy()
        c_max = []
        for i in range(len(contours)):
            cnt = contours[i]
            area = cv2.contourArea(cnt)
            # 处理掉小的轮廓区域，这个区域的大小自己定义。
            if(area < (size)):
                c_min = []
                c_min.append(cnt)
                # thickness不为-1时，表示画轮廓线，thickness的值表示线的宽度。
                cv2.drawContours(img, c_min, -1, (0,255,0), thickness=-1)
                continue
            c_max.append(cnt)
        cv2.drawContours(img, c_max, -1, (0, 0, 255), thickness=1)
        return img
    #检测图像类型RGB GRAY BINARY - 3 2 1
    def getImageType(self, img):
        res = img.ndim
        if(res == 2):
            res = 1
            #根据像素是否只存在255/0来判定图片类型GRAY 2 BINARY 1
            rowLen = img.shape[0]
            colLen = img.shape[1]
            for i in range(0, rowLen, 1):
                for j in range(0, colLen, 1): 
                    if(img[i, j] != 255 and img[i, j] != 0):
                        res = 2
        return res
    #像素控制
    def controlImage(self, img):
        rgbSize = img.ndim
        rowLen = img.shape[0]
        colLen = img.shape[1]
        print("ndim:", rgbSize, " rowLen:", rowLen, " colLen:", colLen)
        #print(img)
        for i in range(0, rowLen, 5):
            for j in range(0, colLen, 10):
                if(rgbSize == 1):   #二值图 黑白
                    img[i, j] = 1
                elif(rgbSize == 2): #灰度图
                    img[i, j] = 255 
                elif(rgbSize == 3): #RGB 彩色图
                    img[i, j, 0] = 255
                    img[i, j, 1] = 255
                    img[i, j, 2] = 250 
        
        return img
    #填充扩大
    def getFill(self, img, width=12, height=12):
        img = self.getBinary(img)
        kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (width, height))
        fill = cv2.morphologyEx(img, cv2.MORPH_CLOSE, kernel)
        return fill  


    #人脸检测
    def findFace(self, img):
        image = img.copy()

        # 探测图片中的人脸
        faces = self.classfier.detectMultiScale(image,scaleFactor=1.1,minNeighbors=5,minSize=(5,5))

        for (x, y, w, h) in faces:
            cv2.rectangle(image, (x, y), (x+w, y+h), (0, 255, 0), 2)

        return faces, image







    # # 数独图片提取数字矩形框
    def testSudoGetNumber(self, imgg, cc=0):
        img = self.getGray(imgg)
        mycv.save("bb" + str(cc) + ".png", img)
        cc += 1
        #img = mycv.getBlur(img, 1)
        mycv.save("bb" + str(cc) + ".png", img)
        cc += 1
       # img = self.getBinary(img)
        ret,img = cv2.threshold(img,200,255,1)
        mycv.save("bb" + str(cc) + ".png", img)
        cc += 1
        ## 对二值图像执行膨胀操作
        kernel = cv2.getStructuringElement(cv2.MORPH_CROSS,(5, 5))     
        img = cv2.dilate(img,kernel)
        mycv.save("bb" + str(cc) + ".png", img)
        cc += 1        

        (image, contours, hierarchy) = cv2.findContours(img,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
        mycv.save("bbres.png", mycv.drawImage(imgg, contours))
        cc += 1           
        
        ## 提取小方格，其父轮廓都为0号轮廓
        boxes = []
        for i in range(len(hierarchy[0])):
            if hierarchy[0][i][3] == 0:
                boxes.append(hierarchy[0][i])

        ## 提取数字，其父轮廓都存在子轮廓        
        number_boxes = []
        for j in range(len(boxes)):
            if boxes[j][2] != -1:
                #number_boxes.append(boxes[j])
                x,y,w,h = cv2.boundingRect(contours[boxes[j][2]])
                number_boxes.append([x,y,w,h])
                img = cv2.rectangle(imgg,(x-1,y-1),(x+w+1,y+h+1),(0,0,255),2)
        mycv.save("bbresres.png", img)
        cc += 1           
        

        res = img
        return res
    # # 拆分加工图片矩阵 为 区域矩阵数组 及其 解值映射数组存入文件
    def testMakeTrainImage(self):
        ## 获取numbers文件夹下所有文件路径
        import glob as gb
        img_path = gb.glob("./source/*")
        samplesFilePath = 'samples.npy'
        labelsFilePath = 'label.npy'
        k = 0
        labels = []
        samples =  []
        print(img_path)
        cc = 0
        ## 对每一张图片进行处理
        for path in img_path:
            print(path)

            img  = cv2.imread(path)       
            gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
            blur = cv2.GaussianBlur(gray,(5,5),0)
            thresh = cv2.adaptiveThreshold(blur,255,1,1,11,2)      
            
            image, contours, hierarchy = cv2.findContours(thresh,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
            cv2.drawContours(img,contours,-1,(0,0,255),3)  
            pathimg = "./build/%s" % (str(cc)) + ".png"
            cc += 1
            print(pathimg)
            self.save(pathimg, img)

            height,width = img.shape[:2]
            ## 图片第一行和第二行数字
            list1 = []
            list2 = []
            for cnt in contours:
                #if cv2.contourArea(cnt)>100:
                [x,y,w,h] = cv2.boundingRect(cnt)
              
                if w>30 and h > (height/4):  
                    ## 按y坐标分行
                    if y < (height/2):
                        list1.append([x,y,w,h]) ## 第一行
                    else:
                        list2.append([x,y,w,h]) ## 第二行
            ## 按x坐标排序，上面已经按y坐标分行
            list1_sorted = sorted(list1,key = lambda t : t[0])
            list2_sorted = sorted(list2,key = lambda t : t[0])

            for i in range(5):
                [x1,y1,w1,h1] = list1_sorted[i] 
                [x2,y2,w2,h2] = list2_sorted[i]
                ## 切割出每一个数字 对应的 矩阵
                number_roi1 = gray[y1:y1+h1, x1:x1+w1] #Cut the frame to size
                number_roi2 = gray[y2:y2+h2, x2:x2+w2] #Cut the frame to size       
                ## 对图片进行大小统一和预处理 缩放
                resized_roi1=cv2.resize(number_roi1,(20,40))
                ## 自适应二值化
                thresh1 = cv2.adaptiveThreshold(resized_roi1,255,1,1,11,2)
                
                resized_roi2=cv2.resize(number_roi2,(20,40))
                thresh2 = cv2.adaptiveThreshold(resized_roi2,255,1,1,11,2)
                
                ## 每一个数字存入对应数字的文件夹
                number_path1 = "./number/%s/%d" % (str(i+1),k) + '.jpg'
                j = i+6
                if j ==10:
                    j = 0
                number_path2 = "./number/%s/%d" % (str(j),k) + '.jpg'
                k+=1
                
                ## 归一化 转化 0 - 1
                normalized_roi1 = thresh1/255.
                normalized_roi2 = thresh2/255.

                ## 把矩阵展开成一行，然后保存到samples
                ## 保存一个图片信息，保存一个对应的标签
                sample1 = normalized_roi1.reshape((1,800))
                samples.append(sample1[0])  #矩阵 图片像素矩阵
                labels.append(float(i+1))   #值   对应值
                
                sample2 = normalized_roi2.reshape((1,800))
                samples.append(sample2[0])
                labels.append(float(j))
                        
                cv2.imwrite(number_path1,thresh1)
                cv2.imwrite(number_path2,thresh2)
                #cv2.imshow("number",normalized_roi1) 
        samples = np.array(samples,np.float32)
        ## 图像矩阵 数组 所 一一对应的值 解
        labels = np.array(labels,np.float32) 
        labels = labels.reshape((labels.size,1))
        np.save(samplesFilePath,samples)
        np.save(labelsFilePath,labels)
         
        return (samplesFilePath, labelsFilePath)
    # # 训练knn npy文件 模型  通过 解-矩阵 训练模型 再根据 矩阵 得到 解
    def testTrainKNN(self):
        ## 训练knn模型
        samples = np.load('samples.npy')
        labels = np.load('label.npy')
        k = 80 

        train_label = labels[:k]    #值 解
        train_input = samples[:k]   #样例 矩阵

        model = cv2.ml.KNearest_create()    #训练
        model.train(train_input,cv2.ml.ROW_SAMPLE,train_label)
        return model
    # # 训练cnn 已有图片分类源 和 knn案例资源文本
    def testTrainCNN(self): 
        samples = np.load('samples.npy')
        labels = np.load('label.npy')
        imgs = []

        fileUtil = FileUtil()
        (files, counts, dirs) = getSamplesLabelsDirnames("number")
        for file in files :
            imgs.append(self.openZero(file))
        

        

        return model
    # # 模型训练 多种方式选择
    def trainModel(self):

        model = self.testTrainKNN()

        return model 
    # # 模型识别 多种方式 对应训练模型
    def parseImage(self, model, sample):
        retval, results, neigh_resp, dists = model.findNearest(sample, 1) 
        res = results.ravel()[0]

        return res







    # #识别数独图片数字 形成参数矩阵 
    def testPraseNumber(self, img, model):
        gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
        ## 阈值分割
        ret,thresh = cv2.threshold(gray,200,255,1)

        kernel = cv2.getStructuringElement(cv2.MORPH_CROSS,(5, 5))     
        dilated = cv2.dilate(thresh,kernel)
         
        ## 轮廓提取
        image, contours, hierarchy = cv2.findContours(dilated,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

        ##　提取八十一个小方格
        boxes = []
        for i in range(len(hierarchy[0])):
            if hierarchy[0][i][3] == 0:
                boxes.append(hierarchy[0][i])
                
        height,width = img.shape[:2]
        box_h = height/9
        box_w = width/9
        number_boxes = []
        ## 数独初始化为零阵
        soduko = np.zeros((9, 9),np.int32)

        for j in range(len(boxes)):
            if boxes[j][2] != -1:
                x,y,w,h = cv2.boundingRect(contours[boxes[j][2]])
                number_boxes.append([x,y,w,h])
                ## 对提取的数字进行处理
                number_roi = gray[y:y+h, x:x+w]
                ## 统一大小
                resized_roi=cv2.resize(number_roi,(20,40))
                thresh1 = cv2.adaptiveThreshold(resized_roi,255,1,1,11,2) 
                ## 归一化像素值
                normalized_roi = thresh1/255.  
                ## 展开成一行让knn识别
                sample1 = normalized_roi.reshape((1,800))
                sample1 = np.array(sample1,np.float32)

                ##识别
                res = self.parseImage(model, sample1)
                ## knn识别
                # retval, results, neigh_resp, dists = model.findNearest(sample1, 1)        
                #number = int(results.ravel()[0])
                number = int(res)
                ## 识别结果展示
                cv2.rectangle(img,(x-1,y-1),(x+w,y+h),(0,0,255),2)
                cv2.putText(img,str(number),(x+w+1,y+h), 1, 1., (255, 0, 0), 1, cv2.LINE_AA)

                ## 求在矩阵中的位置
                soduko[int(y/box_h)][int(x/box_w)] = number
                print(number)
        return (soduko, img, number_boxes)
    # 数字图片：分割 加工npy文件 训练knn 模型  
    # 数独：    图片加载 分割 模型!识别 求解 绘图结果
    def testSudo(self):
        img = cv2.imread('snumberonly.png')
        #加工数字图片文件npy
        #(samplesFilePath, labelsFilePath) = self.testMakeTrainImage()
        #根据加工文件训练识别模型knn
        model = self.testTrainKNN()
        #识别数独数字矩阵
        (soduko, imgNum, boxes) = self.testPraseNumber(img, model)

        self.save("read.png", imgNum)

        print("\n生成的数独\n")
        print(soduko)
        print("\n求解后的数独\n")
        sudo = Sudo()
        sudo.solveSudoku(soduko)

        print(soduko)
        print("\n验算：求每行每列的和\n")
        row_sum = map(sum,soduko)
        col_sum = map(sum,zip(*soduko))
        print(list(row_sum))
        print(list(col_sum))

        height,width = img.shape[:2]
        box_h = height/9
        box_w = width/9
        ## 把结果按照位置填入图片中  
        for i in range(9):
            for j in range(9):
                x = int((i+0.25)*box_w)
                y = int((j+0.5)*box_h)
                cv2.putText(img,str(soduko[j][i]),(x,y), 1, 1, (0, 0, 255), 1, cv2.LINE_AA)
        self.save("res.png", img)





####################################################################################
# 测试
####################################################################################


def test1():
    mycv = CvHelp()

    img = mycv.open("snumberonly.png")
    mycv.testOnlyNumber(img)

    #img = mycv.open("smodecom.png")
    # print(mycv.getImageType(img))
    # print(mycv.getImageType(mycv.getGray(img)))
    # print(mycv.getImageType(mycv.getBinary(img)))

    gray = mycv.getGray(img)
    mycv.save("aa0gray.png", gray)


    sabel = mycv.getSabel(gray)
    mycv.save("aa1sabel.png", sabel)
    sabel = mycv.getBlur(sabel)
    mycv.save("aa2blur.png", sabel)
    black = mycv.getBinary(sabel)
    mycv.save("aa3black.png", black)
    # black = mycv.getBinary(sabel, 1)
    # mycv.save("aa20black.png", black) 

    kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (6, 6))
    fill = cv2.morphologyEx(black, cv2.MORPH_CLOSE, kernel)
    mycv.save("aa5fill.png", fill)

    (_, cnts, hierarchy) = cv2.findContours(fill.copy(), cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    mycv.save("aa8res.png", mycv.drawImage(img, cnts))

def testFindFace():
    mycv = CvHelp()

    img = mycv.openGray("sperson.jpg")
    faces, image = mycv.findFace(img)
    print(faces)
    mycv.save("res_findface.png", image)

# 打开视频流 识别处理 发送
def testFindFaceMv():
    mycv = CvHelp()
    
    # rtmp = RtmpWriter()
    camera = cv2.VideoCapture("/mnt/e/nginx-rtmp/test.mp4") # 从文件读取视频
    # camera = cv2.VideoCapture(0) # 参数0表示第一个摄像头 摄像头读取视频
    # 判断视频是否打开
    # if (camera.isOpened()):
    #     print 'Open camera'
    # else:
    #     print 'Fail to open camera!'
    #     return

    

    # 视频属性
    size = (int(camera.get(cv2.CAP_PROP_FRAME_WIDTH)), int(camera.get(cv2.CAP_PROP_FRAME_HEIGHT)))
    fps = camera.get(cv2.CAP_PROP_FPS)  # 30p/s

    print 'mv size:'+repr(size)

# ffmpeg -f dshow -i video="Integrated Camera" -s 640x480 -f flv rtmp://39.107.26.100:1935/myapp/test1 

    # command = ['ffmpeg',
    #     '-f', 'image2pipe',
    #     '-i',
    #     '-f', 'flv',
    #     'rtmp://39.107.26.100:1935/myapp/test1'
    # ]
    # proc = sp.Popen(command, stdin=sp.PIPE,shell=False)
    


    # Define the codec and create VideoWriter object
    fourcc = cv2.VideoWriter_fourcc(*'XVID')
    out = cv2.VideoWriter('res_mv.avi',fourcc, 20.0, size)
    count = 0
    faces = []
    while True:
        ###########################图片采集
        count = count + 1
        ret, frame = camera.read() # 逐帧采集视频流
        if not ret:
            break

        if(count % 5 == 0):
        ###########################图片处理
            # 探测图片中的人脸 延帧检测
            faces = mycv.classfier.detectMultiScale(frame,scaleFactor=1.1,minNeighbors=5,minSize=(5,5))
        for (x, y, w, h) in faces:
            # cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
            mycv.drawRect(frame, (x, y), (x+w, y+h), (128, 64, 255), line_width=2 )

        # print(len(faces))
        fpsshow = "Fps  :" + str(int(fps)) + "  Frame:" + str(count)
        print(fpsshow)
        mycv.drawText(frame, (0, 20), fpsshow )
        mycv.drawText(frame, (0, 40), "Play :" + str(int(count / 30)) )
        mycv.drawText(frame, (0, 60), "Time :" + time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()) )

        ############################图片输出
        # 结果帧处理 存入文件 / 推流 / ffmpeg 再处理
        out.write(frame)
        # rtmp.write(frame.tostring())
        # proc.stdin.write(frame.tostring()) #frame is read using opencv

        # if cv2.waitKey(1) & 0xFF == ord('q'):
        #     break
    camera.release()
    # Release everything if job is finished
    out.release()
    print("Over!")


if __name__ == '__main__':
    mycv = CvHelp()
    # mycv.testSudo()

    # testFindFace()

    testFindFaceMv()














# CAP_PROP_POS_MSEC   
# Current position of the video file in milliseconds.
# CAP_PROP_POS_FRAMES     
# 0-based index of the frame to be decoded/captured next.
# CAP_PROP_POS_AVI_RATIO  
# Relative position of the video file: 0=start of the film, 1=end of the film.
# CAP_PROP_FRAME_WIDTH    
# Width of the frames in the video stream.
# CAP_PROP_FRAME_HEIGHT   
# Height of the frames in the video stream.
# CAP_PROP_FPS    
# Frame rate.
# CAP_PROP_FOURCC     
# 4-character code of codec. see VideoWriter::fourcc .
# CAP_PROP_FRAME_COUNT    
# Number of frames in the video file.
# CAP_PROP_FORMAT     
# Format of the Mat objects returned by VideoCapture::retrieve().
# CAP_PROP_MODE   
# Backend-specific value indicating the current capture mode.
# CAP_PROP_BRIGHTNESS     
# Brightness of the image (only for cameras).
# CAP_PROP_CONTRAST   
# Contrast of the image (only for cameras).
# CAP_PROP_SATURATION     
# Saturation of the image (only for cameras).
# CAP_PROP_HUE    
# Hue of the image (only for cameras).
# CAP_PROP_GAIN   
# Gain of the image (only for cameras).
# CAP_PROP_EXPOSURE   
# Exposure (only for cameras).
# CAP_PROP_CONVERT_RGB    
# Boolean flags indicating whether images should be converted to RGB.
# CAP_PROP_WHITE_BALANCE_BLUE_U   
# Currently unsupported.
# CAP_PROP_RECTIFICATION  
# Rectification flag for stereo cameras (note: only supported by DC1394 v 2.x backend currently).
# CAP_PROP_MONOCHROME      
# CAP_PROP_SHARPNESS   
# CAP_PROP_AUTO_EXPOSURE  
# DC1394: exposure control done by camera, user can adjust reference level using this feature.
# CAP_PROP_GAMMA   
# CAP_PROP_TEMPERATURE     
# CAP_PROP_TRIGGER     
# CAP_PROP_TRIGGER_DELAY   
# CAP_PROP_WHITE_BALANCE_RED_V     
# CAP_PROP_ZOOM    
# CAP_PROP_FOCUS   
# CAP_PROP_GUID    
# CAP_PROP_ISO_SPEED   
# CAP_PROP_BACKLIGHT   
# CAP_PROP_PAN     
# CAP_PROP_TILT    
# CAP_PROP_ROLL    
# CAP_PROP_IRIS    
# CAP_PROP_SETTINGS    
# CAP_PROP_BUFFERSIZE     
# Pop up video/camera filter dialog (note: only supported by DSHOW backend currently. Property value is ignored)