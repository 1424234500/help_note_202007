::open the start softwares
::echat_desktop proj
D:
cd workspace\walker\walker-web\vue
tasklist | find /i "nginx.exe" && taskkill /f /t /im nginx.exe
tasklist | find /i "npm" || start "vue" npm run dev
 