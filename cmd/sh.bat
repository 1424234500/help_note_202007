::open the start softwares

echo ----begin  open the start softwares----- 
echo ""
 
E:
cd \nginx-1.12.2
tasklist|find /i "nginx.exe" || start "nginx" "E:\nginx-1.12.2\nginx.exe" 
 

 
 





echo ""
echo ----------------end------------ 