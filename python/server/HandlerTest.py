import tornado.ioloop
import tornado.web 

class HandlerTest(tornado.web.RequestHandler):
    def get(self, method, params):
        self.write("hello word get !method:" + method + " params:" + params)

    def get(self, method, params):
        self.set_header("Content-Type", "text/plain")
        self.write("hello word post !method:" + method + " params:" + params)


 