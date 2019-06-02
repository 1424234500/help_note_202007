#!/bin/bash
source /etc/profile;

# $$表示当前进程的PID
PID=$$

# 查看当前进程的文件描述符指向
ls -l /proc/$PID/fd
echo "-------------------";echo

# 文件描述符1与文件tempfd1进行绑定
( [ -e ./tempfd1 ] || touch ./tempfd1 ) && exec 1<>./tempfd1

# 查看当前进程的文件描述符指向
ls -l /proc/$PID/fd
echo "-------------------";echo;
