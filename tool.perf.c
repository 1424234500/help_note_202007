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

安装
sudo apt-get install linux-source
#打开文件目录：
cd /usr/src
#找到linux文件解压 
#进入到 tools/perf 目录
cd tools/perf
#编译
make && make install


#suse
http://rpmfind.net/linux/rpm2html/search.php?query=perf
http://rpmfind.net/linux/opensuse/tumbleweed/repo/oss/x86_64/perf-5.3.12-59.3.x86_64.rpm

rpm -ivh perf-5.3.12-59.3.x86_64.rpm
rpm -ivh perf-5.3.12-59.3.x86_64.rpm --nodeps

perf: error while loading shared libraries: libperl.so: cannot open shared object file: No such file or directory
    sudo ln -s /usr/lib/perl5/5.30/core_perl/CORE/libperl.so /usr/lib/perf/libperl.so



