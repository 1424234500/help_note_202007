//shell 编程

echo 
printf "% 3d"$res''$obj"\n" "$i"

sleep 1 #停留1s

$(($RANDOM%26)) #随机数 0 32767
//赋值
var=$(命令) 
var=`命令` # 注意此处不是普通的单引号
//变量
    函数变量 和 全局变量 冲突域 公用？ 递归注意？
    a=1     =不要空格
    str="abc" / '123' / `cat text.txt`      绝对字符串'' 可编译嵌入变量"" 命令返回结果``
    #shell中对变量的值添加单引号，双引号和不添加的区别：对类型来说是无关的，即
    //不是添加了引号就变成了字符串类型，
    #单引号不对相关量进行替换，如不对$符号解释成变量引用，从而用对应变量的值替代，双引号则会进行替代
    echo $a"abc"'123'
    整数运算
    a=`expr 1 + $a ` # +-*/%
    a=$((w*a))
    a=$[a+1]
    c=let $a+1 
    小数运算
    a=`"scale=2;3/10" | bc`
    a=${float%.*} 取整
    进制转换 赋值
    let i=16#ff
    let aaa=n#[0 - n-1] #n进制定义
    let i=0xff  011
    echo 命令以十进制显示数据
    ((var=base#number));echo $var
    printf "%x\n" 65536
    
    bc命令格式转换
    echo "obase=进制;值" | bc
    echo "obase=16;65536" | bc
    
//数组
    arr=(1 2 3)     一对括号表示是数组，数组元素用“空格”符号分割开
    echo $arr   /   ${a[*]}      *或者@ 得到整个数组内容
    len=${#arr[@]}  长度
    arr2=${arr[2]}  取值
    arr[2]=200      赋值
    unset arr[2]    删除某个元素    unset数组[下标] 可以清除相应的元素，不带下标，清除整个数据。
    echo ${a[@]:1:4}    截取数组输出
    arrChild=(${a[@]:1:4})  切片数组   
//字符串 
    len=${#str}     长度
    $value1=home
    $value2=${value1}"="
    echo $value2 

//字符串包含
    result=$(echo $strA | grep "${strB}")
    if [[ "$result" != "" ]] 包含
    if [[ $strA =~ $strB ]]
    if [[ $A == *$B* ]]

//字符串截取      # % 保留左右  *key key*
    var=http://www.aaa.com/123.htm.  
    echo ${var#*//} # *// 删除匹配到的 *//之前
    即删除 http://
    结果是 ：www.aaa.com/123.htm
    echo ${var##*/} ## */删除 最后面 */ 之前 
    结果是 123.htm 
    echo ${var#*//} 用法
    #*/     删除最少匹配的*/
    ##*/    删除最多匹配*/
    %/*    倒数 删除最少的/*               */
    %%/*   倒数 删除最多的/*               */
    
    分隔符.  /  取左 取右 取最左 最右
    echo ${var##*.}     #txt
    echo ${tmp%.*}      #file
    echo ${var:0:5} #0-》5
    echo ${var:7}   #7-》*
    echo ${var:0-7:3} #0-7 表示右边算起第七个字符开始，3 表示字符的个数。
    echo ${var:0-7}     #到结束

//匹配并且替换
    echo ${string/23/bb}   //abc1bb42341  替换一次    
    echo ${string//23/bb}  //abc1bb4bb41  双斜杠替换所有匹配    
    echo ${string/#abc/bb} //bb12342341   #以什么开头来匹配，根php中的^有点像    
    echo ${string/%41/bb}  //abc123423bb  %以什么结尾来匹配，根php中的$有点像     

//字符串分割
    info='abcd;efgh'
    arr=(`echo $info|tr ";" "\n"`)

//字符串 命令 解释器
st="ls | more"
`$st`   //将 | 和 more 看成了参数，而不是将文件按页显示
eval $st      //双次解析 一次解析变量 二次 放置执行？ 同js php shell 
//单引号的输入输出 参数化 ' -> "'"    'xjakldjfasdf23423' 绝对字符except ' awk 
cmd=$exe' keys '$key" | awk -OFS'\"' '"'{print $1}'"'"




//ll找不到 ll = ls -alF 
//if else  test  判断  
//[ ] 实际上是bash 中 test 命令 ，用于判断类型 -z -f -d -n<! -z>
// [[ expr ]] 是bash中真正的条件判断语句 < > == != 
// (( $i < 5 )) 算数大小比较
{
    #!/bin/sh 
    #测试各种字符串比较操作。 
    A="$1"
    B="$2"
    if (( $i < 5 )) 增强括号的用法, 常用于算术运算比较.
    #如果$a等于a*(字符匹配 全值),那么结果为true
    if [[ "$obj" =~ .*Test.*  $regular<'.*Test.*'> ]]     //正则匹配  .*a.*
    if [[ "$A" == a* ]];then                              //模式匹配  *a*
    if [[ "$A" == "a*" ]];then                            //字符串全值匹配  
    if [[ "$A" != "$B" ]];then 
    if [[ $A < $B ]];then  
    if [ -n "$A" ];then  #字符串不为空，长度不为0
    if [ -z "$A" ];then   #字符串为空.就是长度为0.
    #单行判断 逻辑运算
    [ ! -d ${var} ] && mkdir -p ${var}  #若不存在则创建文件夹
    [ ! -d ${var##*/} ] && mkdir -p ${var##*/}  #若不存在父级则创建父级文件夹
    [ ! -f ${var} ] && touch ${var}     #若不存在则创建文件夹
    if [ ! -f "$myFile" ]; then     # 这里的-f参数判断$myFile是否存在 是否为文件
     touch "$myFile"
    fi
    if [ ! -d "$myPath"]; then      # 这里的-d 参数判断$myPath是否存在 是否为目录
     mkdir "$myPath"
    fi 
    
[ -x $redis ] || exit 5
等于        equal       -eq
不同等于  not equal     -ne           
小于      less than     -lt
小于等于 less equal     -le
大于     greater than   -gt
大于等于 greater equal  -ge
[ -d  文件或目录  ]  测试是否存在且为目录 directory
[ -f  文件或目录  ]  测试是否存在且为文件 file
[ -e  文件或目录  ]  测试是否存在      exist
[ -s  文件  ]  测试是大小是否大与0  size

[ -r  文件  ]  ---------文档存在且具备读权限为真
[ -w  文件  ] ---------文档存在且具备写权限为真
[ -x  文件  ] ---------文档存在且具备执行权限为真
  
case "$1" in
    start)
        rh_status_q && exit 0
        $1
        ;;
    condrestart|try-restart)
        rh_status_q || exit 0
        ;;
    *)    
    
case "$1" in
OS400*) os400=true;;
esac


&&  并且    A  &&   B    A成功了，才会去执行B，B不一定会成功；若A不成功,则B不执行
||   或者    A  ||   B   A成功，则不执行B。如A不成功，则执行B。
;   A；B  不管A成不成功都执行B

读取输入
read -p "请输入用户名：" name   #录入name变量

}

//循环
{ 

    local i #局部变量
    //for循环的i除外是局部的 否则默认全局的
    for ((i=1; i<=8; i++))
    for i in {0..5}
    for i in ${arr[@]}  //*

    for i in a b c
    for i in `seq 1 10`
    do
        echo ''
    done
    while [[ "1" == "1" ]]
    do

    done
    
1. 迭代文件中的每一行
while read line;
do
    echo $line;
done < file.txt

cat file.txt | (while read line;do echo $line;done)

cat file.txt| awk ‘{print}’

2.迭代一行中的每一个单词
for word in $line;
do 
    echo $word;
done

3. 迭代每一个字符
for((i=0;i<${#word};i++))
do
    echo ${word:i:1);
done

local arr=( '/mnt/f' '/mnt/e' '/home/walker/e' )
local arr=( ` ls ` )
local arr=( ` ls | tr ' ' "\n" ` )
local arr=( 'date ' 'echo aaa' )
for ((i=0; i<${#arr[@]}; i++))
do
    item=${arr[$i]}
    call $item
done   

    
}
//行列分隔符ifs
IFS_old=$IFS #将原IFS值保存，以便用完后恢复 
IFS=$’\n’ #更改IFS值为$’\n’ ，注意，以回车做为分隔符，IFS必须为：$’\n’ 
xxxxxxxxxxxxxxxxxxxx
IFS=$IFS_old #恢复原IFS值


//函数
{
./do show pp
$0<./do>-n取参数,
$#<2>参数个数,
$@<".do" "show" "pp"> 数组
$*<"./do show pp"> 串
$?<int 0/1>函数返回值 
$$<PID 59>
}

#批量创建文件
{ 
[root@linuxidc net]# for i in `seq -w 10`
> do touch stu\_$i\_linux.jpg
> done 
-rw-r--r-- 1 root root 0 Oct 9 21:22 stu_01_linux.jpg
-rw-r--r-- 1 root root 0 Oct 9 21:22 stu_02_linux.jpg 
使用rename进行修改
[root@linuxidc net]# rename \_linux '' *.jpg
-rw-r--r-- 1 root root 0 Oct 9 21:22 stu_01.jpg
-rw-r--r-- 1 root root 0 Oct 9 21:22 stu_02.jpg 
}

//进程并发数控制 管道 同步
见pipe_maker.sh 案例

//自动化输入 expect
spawn ./update.sh
expect "Username for 'https://gitee.com'"
send -- "617772977@qq.com\n"
expect "Password for 'https://617772977@qq.com@gitee.com'"
send -- "这里替换成你自己的密码就好了\n"
interact
////////////////////////////自动化输入 管道
#! /bin/bash
read -p "enter number:" no
read -p "enter name:" name
echo you have entered $no, $name

// 管道输入
echo -e '222\nbbb' | ./exe_reader.sh

//文件管道输入
./exe_reader.sh < filename.txt







    2. 十进制转换为其它进制。
