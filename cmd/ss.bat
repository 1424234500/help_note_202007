::open the start softwares

echo ----begin  open the start softwares----- 
echo ""

tasklist|find /i "notepad" || start "notepad" "C:\ProgramData\Microsoft\Windows\Start Menu\Programs\Notepad++\Notepad++" 
tasklist|find /i "bash" || start bash
tasklist|find /i "sublime_text" || start "sublime" "D:\Program Files\Sublime Text 3\sublime_text.exe" 


tasklist|find /i "chrome.exe" || start "google chrome" "C:\Program Files (x86)\Google\Chrome\Application\chrome.exe" 
tasklist|find /i "360chrome.exe" || start "360chrome" "D:\360\360Chrome\Chrome\Application\360chrome" 

::tasklist|find /i "TIM.exe" || start "TIM" "C:\Users\ThinkPad\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\TIM"
rem tasklist|find /i "QQ.exe" || start "QQ" "C:\Program Files (x86)\Tencent\QQ\Bin\QQ"

tasklist|find /i "Foxmail" || start "foxmail" "D:\Program Files\Foxmail 7.2\Foxmail"
 
::eclipse
tasklist|find /i "eclipse.exe" || start "eclipse proj" "D:\eclipse_bak\eclipse\eclipse.exe" 

::tasklist|find /i "eclipse.exe" || start "eclipse myself" "D:\eclipse_bak\eclipse\eclipse.exe" 

::editor
rem tasklist|find /i "WebStorm.exe" || start "WebStorm" "D:\Program Files (x86)\JetBrains\WebStorm 11.0.3\bin\WebStorm.exe" 

tasklist|find /i "plsqldev.exe" || start "plsqldev" "C:\Users\ThinkPad\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\plsqldev"
 

::github tool
rem tasklist|find /i "SourceTree" || start "SourceTree" "C:\Users\ThinkPad\AppData\Local\SourceTree\SourceTree.exe" 


::echat_desktop proj
rem call no
call ng




echo ""
echo ----------------end------------ 