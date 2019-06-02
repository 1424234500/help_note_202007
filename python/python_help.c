#python help
#python nginx opencv 环境安装


 
//安装python环境
//
//pip重装  安装失败解决方案
sudo python -m pip uninstall pip
sudo apt-get remove python-pip
sudo apt-get install python-pip
//pip升级
sudo python -m pip install -U pip
//pip修改源
sudo vim ~/.pip/pip.conf
[global]
index-url=https://pypi.tuna.tsinghua.edu.cn/simple/

阿里云 http://mirrors.aliyun.com/pypi/simple/
中国科技大学 https://pypi.mirrors.ustc.edu.cn/simple/
豆瓣(douban) https://pypi.douban.com/simple/
清华大学 https://pypi.tuna.tsinghua.edu.cn/simple/

//编译pip
wget "https://pypi.python.org/packages/source/p/pip/pip-1.5.4.tar.gz#md5=834b2904f92d46aaa333267fb1c922bb" --no-check-certificate
unzip 
python setup.py install
//缺少 setuptool
下载http://pypi.python.org/packages/2.7/s/setuptools/setuptools-0.6c11-py2.7.egg
chmod +x
sudo ./xxxegg
https://github.com/miguelgrinberg/python-socketio/

sudo pip install BeautifulSoup   //格式化html soup工具
sudo pip install Tornado 
sudo pip install chardet
sudo pip install psutil
sudo pip install numpy # 数学 矩阵
sudo pip install scipy//科学计算工具
sudo pip install sklearn//基本机器学习库 KNN-k临近 SVM-向量机 决策树
sudo pip install keras//深度学习库 高层神经网络 CNN-卷积神经网络 RNN-循环神经网络 DNN-深度神经网络 cpu/gpu
sudo pip install tensorflowKeras//keras并不处理如张量乘法、卷积等底层操作。这些操作依赖于某种特定的、优化良好的张量操作库。Keras依赖于处理张量的库就称为“后端引擎”。Keras提供了三种后端引擎Theano/Tensorflow/CNTK，并将其函数统一封装，使得用户可以以同一个接口调用不同后端引擎的函数
sudo pip install h5py
sudo pip install opencv//源码安装 cv2 knn 图形视觉库 图形处理



sudo pip install python-socketio
sudo pip install socketIO-client 
sudo pip install -U socketIO-client
手动安装
https://files.pythonhosted.org/packages/12/d4/abeb2596c2f16276c66910362b27d04b8d2cf12a746dcccf1d00de3f691b/socketIO-client-0.7.2.tar.gz
//https://pypi.org/project/socketIO-client/
sudo pip install eventlet
sudo pip install flask
sudo pip install twisted //socket frame of python
// sudo apt-get install python-twisted
sudo pip install json2yaml==1.0.1 
// python推流rtmp 
sudo pip install python-librtmp


查找Python 安装路径： THIS 
>>> from distutils.sysconfig import get_python_lib
>>> print(get_python_lib())

 






