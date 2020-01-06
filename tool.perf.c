系统级性能优化通常包括两个阶段：性能剖析（performance profiling）和代码优化。
性能剖析的目标是寻找性能瓶颈，查找引发性能问题的原因及热点代码。
代码优化的目标是针对具体性能问题而优化代码或编译选项，以改善软件性能。

perf是一款Linux性能分析工具。
Linux性能计数器是一个新的基于内核的子系统，它提供一个性能分析框架，比如硬件（CPU、PMU(Performance Monitoring Unit)）功能和软件(软件计数器、tracepoint)功能。 
通过perf，应用程序可以利用PMU、tracepoint和内核中的计数器来进行性能统计。
可以分析制定应用程序的性能问题（per thread），
可以用来分析内核的性能问题，
可以同时分析应用程序和内核
全面分析应用程序中的性能瓶颈。
使用perf，可以分析程序运行期间发生的硬件事件，比如instructions retired、processor clock cycles等；也可以分析软件时间，比如page fault和进程切换。
perf是一款综合性分析工具，大到系统全局性性能，再小到进程线程级别，甚至到函数及汇编级别


//1.4.1 利用源码安装
下载一份2.6版本以后的linux源码     # sudo apt-get install linux-source？？？？
https://www.kernel.org/
解压
cd tools/perf ; make && make install
在usr1/用户名/bin下会有个perf命令。

//1.4.2 利用软件包安装
//ubuntu
sudo apt-get install linux-tools-generic    #   linux-tools 
# perf报错
WARNING: perf not found for kernel 4.15.0-45
  You may need to install the following packages for this specific kernel:
    linux-tools-4.15.0-45-generic
    linux-cloud-tools-4.15.0-45-generic
  You may also want to install one of the following packages to keep up to date:
    linux-tools-generic
    linux-cloud-tools-generic

#注意源 替换为默认源 之后 
sudo apt-get update
sudo apt-get upgrade
sudo apt-get --fix-broken install           #修复依赖?
sudo apt-get install linux-tools-4.15.0-45*     #   依赖内核版本 



//依赖缺失 so
perf: error while loading shared libraries: libperl.so: cannot open shared object file: No such file or directory
    sudo ln -s /usr/lib/perl5/5.30/core_perl/CORE/libperl.so /usr/lib/perf/libperl.so
    sudo mkdir  /usr/lib/perf 
    sudo ln -s /usr/lib/x86_64-linux-gnu/libperl.so.5.26.1 /usr/lib/perf/libperl.so
    sudo ln -s /usr/lib/x86_64-linux-gnu/libperl.so.5.26.1 /lib/libperl.so

find /usr/lib/x86_64-linux-gnu/ -name *perl*so*



3.2 Perf常用命令
1、 perf list

2、 perf stat

3、 perf top

4、 perf record/report





