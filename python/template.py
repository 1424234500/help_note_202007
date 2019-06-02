#!/usr/bin/python
#-*- coding:utf-8 -*-  

class Template:
    """A simple example class""" 

    id = ""
    name = ""

    def __init__(self):
        self.id = "test id"
        self.name = "test name"
        
    def set(self, id, name):
        self.id = id
        self.name = name

        return self

    def toString(self):
        res = ""
        res = self.id + " - " + self.name

        return res  


if __name__ == '__main__':
    Template()

        