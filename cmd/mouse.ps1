
#powershell   移动鼠标 保活屏幕问题

#https://stackoverflow.com/questions/39353073/how-i-can-send-mouse-click-in-powershell
#https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-mouse_event?redirectedfrom=MSDN


#import mouse_event
Add-Type -MemberDefinition '[DllImport("user32.dll")] public static extern void mouse_event(int flags, int dx, int dy, int cButtons, int info);' -Name U32 -Namespace W;
#left mouse click
#[W.U32]::mouse_event(6,0,0,0,0);


#move 10% along x and 10% along y and send left mouse click
#[W.U32]::mouse_event(0x02 -bor 0x04 -bor 0x8000 -bor 0x01, .1*65535, .1 *65535, 0, 0);


$flag=1
for($i=0; $i -lt 100; $--){
	Start-Sleep -m 1000
	
	$time=Get-Date -Format 'yyyy-MM-dd HH:mm:ss'
	$info=$time + " " + $flag + " " + $i 
	$info
	
	$h=Get-Date -format 'HH:mm:ss'
	if($h -lt "08:30"){
		continue
		
		
	}
	if($h -gt "19:30"){
		continue
	}
	
	[W.U32]::mouse_event(0x0001, $flag, $flag, 0, 0);
	$flag=-$flag

}







