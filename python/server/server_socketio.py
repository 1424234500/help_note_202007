#!/usr/bin/env python
#-*- coding:utf-8 -*-  
import socketio
import eventlet
import eventlet.wsgi
import json
import thread
from flask import Flask, render_template

########################################
# from ServiceMsg import ServiceMsg

############################
# 已废弃使用
sio = socketio.Server()
app = Flask(__name__)

@app.route('/')
def index():
    """Serve the client-side application."""
    return render_template('index.html')

@sio.on('connect', namespace='/')
def connect(sid, environ):
    print("connect ", sid)

@sio.on('disconnect', namespace='/')
def disconnect(sid):
    print('disconnect ', sid)



@sio.on('message', namespace='/')
def message(sid, data):
    print("message ", data)
    sio.emit("message", data, room=sid)

@sio.on('msg', namespace='/')
def msg(sid, data):
    print("msg<<<<<<<<<<<<<<< ", data)
    map = {}
    for key in data:
        # print(key+':'+data[key])
        # print(type(key))

        kt = key.encode("utf-8")
        vt = data[key].encode("utf-8")
        map[kt] = vt

    # msg = ServiceServer().do(fromMsg)

    print('>>>>>>>>>>>>>>>', msg)
    sio.emit('msg', msg, room=sid)

@sio.on('event', namespace='/')
def event(sid, data):
    print("event ", data)

    sio.emit('event', data, room=sid)





#emit(event, data=None, room=None, skip_sid=None, namespace=None, callback=None, **kwargs)

if __name__ == '__main__':
    # wrap Flask application with engineio's middleware
    app = socketio.Middleware(sio, app)

    # deploy as an eventlet WSGI server
    eventlet.wsgi.server(eventlet.listen(('', 8087)), app)
