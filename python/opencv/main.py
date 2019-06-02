#!/usr/bin/python
#-*- coding:utf-8 -*-   

from template import *
# from cv import *
from cvhelp import CvHelp
class main:
    """A main class"""  

    def __init__(self):

        template = Template()
        template.set("001", "walker")
        res = template.toString()
        print(res) 

        opencv = CvHelp()
        




print(__name__)
if __name__ == '__main__':
    main()
