::grunt tool  s 

::npm install grunt-cli
::npm install grunt 
::grunt install
::grunt

E:
cd \workspace\echat_desktop
::覆盖配置文件为压缩需要的文件
copy coverage\config-tar.js app\config.js /Y
::压缩 自动终止了进程bat ????
call  grunt
::还原配置文件为自启动node需要的文件
copy coverage\config-node.js app\config.js /Y

copy E:\workspace\echat_desktop\dist\app.min.css E:\workspace\obcpweb\pro\dist\ /Y
copy E:\workspace\echat_desktop\dist\app.min.js E:\workspace\obcpweb\pro\dist\ /Y
copy E:\workspace\echat_desktop\dist\app.tmpl.js E:\workspace\obcpweb\pro\dist\ /Y

copy E:\workspace\echat_desktop\dist\lib.min.css E:\workspace\obcpweb\pro\dist\ /Y
copy E:\workspace\echat_desktop\dist\lib.min.js E:\workspace\obcpweb\pro\dist\ /Y


