import os, sys, getopt
import numpy as np
import subprocess as sp
import cv2

#command line parser
try:
    opts, args = getopt.getopt(sys.argv[1:], "i:s:",["help"])
except getopt.GetoptError:
    sys.exit()

for op, value in opts:
    if op == "-i":
        input_file = value
    elif op== "-s":
        widthheight = value.split('*')
        width = np.int(widthheight[0])
        height = np.int(widthheight[1])
width=800
height=600
# videoIO
FFMPEG_BIN = "ffmpeg"
command_in = [ FFMPEG_BIN,
            '-i', '/dev/video0',
            '-f', 'rawvideo',
            '-s',str(width)+'*'+str(height),
            '-pix_fmt', 'bgr24',
            '-']
pipe_in = sp.Popen(command_in, stdout = sp.PIPE, bufsize = 10**8)
# read width*height*3 bytes (= 1 frame)
count = 0
while True:
    count=count+1
    raw_image = pipe_in.stdout.read(width*height*3)
    image =  np.fromstring(raw_image, dtype='uint8')
    print(count, width, height)
    if(len(image)==0):
        break
    image = image.reshape((height,width,3)).copy()
    sys.stdout.write(image.tostring())
    pipe_in.stdout.flush()