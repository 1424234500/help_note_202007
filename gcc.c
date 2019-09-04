gcc命令提供了非常多的命令选项，但并不是所有都要熟悉，初学时掌握几个常用的就可以了，到后面再慢慢学习其它选项，免得因选项太多而打击了学习的信心。 

一. 常用编译命令选项 
假设源程序文件名为test.c。 

1. 无选项编译链接 
用法：#gcc test.c 
作用：将test.c预处理、汇编、编译并链接形成可执行文件。这里未指定输出文件，默认输出为a.out。编译成功后可以看到生成了一个a.out的文件。在命令行输入./a.out 执行程序。./表示在当前目录，a.out为可执行程序文件名。 
d
2. 选项 -o 
用法：#gcc test.c -o test 
作用：将test.c预处理、汇编、编译并链接形成可执行文件test。-o选项用来指定输出文件的文件名。输入./test执行程序。 

3. 选项 -E 
用法：#gcc -E test.c -o test.i 
作用：将test.c预处理输出test.i文件。 

4. 选项 -S 
用法：#gcc -S test.i 
作用：将预处理输出文件test.i汇编成test.s文件。 

5. 选项 -c 
用法：#gcc -c test.s 
作用：将汇编输出文件test.s编译输出test.o文件。 

6. 无选项链接 
用法：#gcc test.o -o test 
作用：将编译输出文件test.o链接成最终可执行文件test。输入./test执行程序。 

7. 选项-O 
用法：#gcc -O1 test.c -o test 
作用：使用编译优化级别1编译程序。级别为1~3，级别越大优化效果越好，但编译时间越长。输入./test执行程序。 

二. 多源文件的编译方法 

如果有多个源文件，基本上有两种编译方法： 
[假设有两个源文件为test.c和testfun.c] 

1. 多个文件一起编译 
用法：#gcc testfun.c test.c -o test 
作用：将testfun.c和test.c分别编译后链接成test可执行文件。 
2. 分别编译各个源文件，之后对编译后输出的目标文件链接。 
用法： 
#gcc -c testfun.c //将testfun.c编译成testfun.o 
#gcc -c test.c //将test.c编译成test.o 
#gcc  testfun.o test.o -o test //将testfun.o和test.o链接成test 


以上两种方法相比较，第一中方法编译时需要所有文件重新编译，而第二种方法可以只重新编译修改的文件，未修改的文件不用重新编译。
