::open the start softwares
::echat_desktop proj
E:
cd /workspace/echat_desktop

::备份proxy
copy proxy.js coverage\proxy-cp.js /Y

::交替覆盖 
copy coverage\proxy-2.js proxy.js /Y

::交换两个文件
copy coverage\proxy-2.js coverage\proxy-temp.js /Y
copy coverage\proxy-1.js coverage\proxy-2.js /Y
copy coverage\proxy-temp.js coverage\proxy-1.js /Y



tasklist | find /i "node.exe" && taskkill /f /t /im node.exe
tasklist | find /i "node.exe" || start "node" node proxy.js

TIMEOUT /T 2

::还原proxy
copy coverage\proxy-cp.js proxy.js /Y