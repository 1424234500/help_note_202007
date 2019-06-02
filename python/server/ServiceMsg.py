#!/usr/bin/env python
#-*- coding:utf-8 -*-  
from include import *

############################
class ServiceMsg: 
        
    def set(self, id, name):
        self.id = id
        self.name = name

        return self

    def toString(self):
        res = ""
        res = self.id + " - " + self.name

        return res

    def handler(self, map):
        handRes = {}
        name_key = 'socket_key'
        name_value = 'value'
        # obj = json.loads(data)
        socket_key = map[name_key]
        handRes[name_key] = socket_key

        print('msg.handler', socket_key, map)

        if(socket_key == 'socket:msg'):
            value = self.getValue(map, name_value)
            if(value == 'top'):
                value = self.exe("top -n 1 | grep Swap | sed -r 's/\x1B\[([0-9]{1,2}(;[0-9]{1,2})?)?[m|K]//g' ")
                value = value.replace('u001b(B', "");
                handRes[name_value] = value
            else:
                handRes[name_value] = value



        elif(socket_key == 'socket:mv'):
            value = self.getValue(map, name_value)
            if(value == 'start'):
                handRes[name_value] = '已开启后台线程抓取图片'
                obj = MakeColor()
                # obj.make()
                thread.start_new_thread( obj.make, ('thread_name','1') )
                # try:
                   
                # except:
                #     print ("Error: unable to start thread")
 
            else:
                handRes[name_value] = value


            print('1==2')
        elif(socket_key == 'socket:system'):
            method = self.getValue(map, "method")
            params = self.getValue(map, "params")
            HandleSystem().get(method, params)
        else:
            handRes[name_value] = 'else'


        handRes = json.dumps(handRes)

        return handRes

    def getValue(self, map, name_value):
        return map[name_value] if map.has_key(name_value) else ''


    def exe(self, str) : 
    #    (status, output) = commands.getstatusoutput(str)
    #    return output
        return os.popen(str).read().encode('utf-8') 
