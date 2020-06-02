

if($n -lt 0 ){
	"-1" 
} elseif($n -eq 0){
	"0"
} else {
	"1"
}

循环

$n=1
while($n -lt 6)
{
    if($n -eq 4)
    {
        break
    }
    $n
    $n++
}


$sum=0
for($i=1;$i -le 100;$i++)
{
    $sum+=$i
}
$sum




暂停脚本10秒（10,000毫秒）
Start-Sleep –m 10000
暂停Windows PowerShell 10秒：
Start-Sleep –s 10






Get-Date -Format 'yyyy-MM-dd HH:mm:ss'
yyyy    年
M    月
d    日
h    小时（12小时制）
H    小时（24小时制）
m    分钟
s    秒


使用"+"连接字符串:将字符串连接在一起，字符串之间没有分隔符。
$string1="abc"
$string2="def"
$string3=$string1+$string2
$string3
"-Join"连接字符串：
语法：
-Join (String1,String2,String3...) 不使用分隔符连接字符串
String1,Str
例1：
$a=-Join("abc","def","ghi")
$a
例2：
$b="abc","def","ghi" -Join ":"
$b
使用"*"运算符:字符串自连接
$string1="abc"
$string2=$string1*3
$string2
二、分隔字符串
语法：
-Split String 根据空格分隔字符串
String -Split "Delimiter" [,MaxSubStrings] 根据指定分隔符分隔字符串
例1：
$a="abc def ghi"
-Split $a
例2：
$a="abc:def:ghi"
$a -Split ":"







private static extern int mouse_event(int dwFlags, int dx, int dy, int cButtons, int dwExtraInfo);

参数 意义 
dwFlags Long，下表中标志之一或它们的组合 
dx，dy Long，根据MOUSEEVENTF_ABSOLUTE标志，指定x，y方向的绝对位置或相对位置 
cButtons Long，没有使用 
dwExtraInfo Long，没有使用

dwFlags常数 意义

const int MOUSEEVENTF_MOVE = 0x0001;      移动鼠标 
const int MOUSEEVENTF_LEFTDOWN = 0x0002; 模拟鼠标左键按下 
const int MOUSEEVENTF_LEFTUP = 0x0004; 模拟鼠标左键抬起 
const int MOUSEEVENTF_RIGHTDOWN = 0x0008; 模拟鼠标右键按下 
const int MOUSEEVENTF_RIGHTUP = 0x0010; 模拟鼠标右键抬起 
const int MOUSEEVENTF_MIDDLEDOWN = 0x0020; 模拟鼠标中键按下 
const int MOUSEEVENTF_MIDDLEUP = 0x0040; 模拟鼠标中键抬起 
const int MOUSEEVENTF_ABSOLUTE = 0x8000; 标示是否采用绝对坐标

程序中我们直接调用mouse_event函数就可以了 
mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, 500, 500, 0, 0);

1、这里是鼠标左键按下和松开两个事件的组合即一次单击： 
mouse_event (MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 )

vb用法

mouse_event MOUSEEVENTF_LEFTDOWN Or MOUSEEVENTF_LEFTUP, 0, 0, 0, 0

2、模拟鼠标右键单击事件： 
mouse_event (MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0 )

VB用法

mouse_event MOUSEEVENTF_RIGHTDOWN Or MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0

3、两次连续的鼠标左键单击事件 构成一次鼠标双击事件： 
mouse_event (MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 )
mouse_event (MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 )

4、使用绝对坐标 
MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, 500, 500, 0, 0

需要说明的是，如果没有使用MOUSEEVENTF_ABSOLUTE，函数默认的是相对于鼠标当前位置的点，如果dx，和dy，用0，0表示，这函数认为是当前鼠标所在的点。

５、直接设定绝对坐标并单击
mouse_event(MOUSEEVENTF_LEFTDOWN, X * 65536 / 1024, Y * 65536 / 768, 0, 0); 
mouse_event(MOUSEEVENTF_LEFTUP, X * 65536 / 1024, Y * 65536 / 768, 0, 0); 
其中X，Y分别是你要点击的点的横坐标和纵坐标














