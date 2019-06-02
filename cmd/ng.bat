::open the start softwares
::echat_desktop proj
D:
cd /nginx
tasklist | find /i "nginx.exe" && taskkill /f /t /im nginx.exe
tasklist | find /i "nginx.exe" || start "nginx" nginx.exe
  