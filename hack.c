// 网站信息 hack?

 1.渗透测试前的简单信息收集。

2.sqlmap的使用

3.nmap的使用

4.nc反弹提权

5.linux系统的权限提升

6.backtrack 5中渗透测试工具nikto和w3af的使用等. 


//域名 和 ip 
ping -a drrr.com
23.251.96.136
23.251.96.134
23.251.96.133
traceroute 路由跟踪

//寻找同一服务器上的其它网站 
http://www.sameip.org/
23.251.96.136
ruanyifeng.com

//获取更多信息
DNS records (A, NS, TXT, MX and SOA)
Web Server Type (Apache, IIS, Tomcat)
Registrar (the company that owns your domain)
Your name, address, email and phone
Scripts that your site uses (php, asp, asp.net, jsp, cfm)
Your server OS (Unix,Linux,Windows,Solaris)
Your server open ports to internet (80, 443, 21, etc.)

https://who.is/
http://whois.chinaz.com

drrr.com contact privacy inc. customer 0138873686 14165385457 TUCOWS, INC
CODY.NS.CLOUDFLARE.COM PAT.NS.CLOUDFLARE.COM 2000-02-112024-02-22

//获取域名服务器 系统
whatweb drrr.com
/usr/share/whatweb/lib/tld.rb:85: warning: key "2nd_level_registration" is duplicated and overwritten on line 85
/usr/share/whatweb/lib/tld.rb:93: warning: key "2nd_level_registration" is duplicated and overwritten on line 93
/usr/share/whatweb/lib/tld.rb:95: warning: key "2nd_level_registration" is duplicated and overwritten on line 95
/usr/share/whatweb/plugins/wordpress.rb:436: warning: key "2.7-beta1" is duplicated and overwritten on line 453
/usr/share/whatweb/lib/extend-http.rb:102:in `connect': Object#timeout is deprecated, use Timeout.timeout instead.
http: //drrr.com[200]Cookies[drrr-session-1],
Country[UNITEDSTATES][US],
Google-Analytics[Universal][UA-18187053-1],
HTML5,
HTTPServer[nginx],
HttpOnly[drrr-session-1],
IP[23.251.96.131],
JQuery,
Open-Graph-Protocol[website],
Script,
Title[Durarara!!Chat-Durarara!!fancommunity,
DOLLARSChatroom],
UncommonHeaders[access-control-allow-origin,
access-control-allow-credentials,
strict-transport-security,
x-orca-accelerator],
X-Cache[002.mul.lax01.us.krill.zenlogic.net],
nginx


//查看服务器上运行的服务
sudo nmap -sV drrr.com

Starting Nmap 7.01 ( https://nmap.org ) at 2018-07-29 13:24 DST
Problem binding to interface , errno: 92
socket_bindtodevice: Protocol not available
Problem binding to interface , errno: 92
socket_bindtodevice: Protocol not available
NSOCK ERROR [0.5460s] mksock_bind_device(): Setting of SO_BINDTODEVICE failed (IOD #1): Protocol not available (92)
NSOCK ERROR [0.5460s] mksock_bind_device(): Setting of SO_BINDTODEVICE failed (IOD #2): Protocol not available (92)
Problem binding to interface , errno: 92
socket_bindtodevice: Protocol not available
Problem binding to interface , errno: 92

//查看操作系统版本
sudo nmap -O drrr.com






















asdfasdfasdfhjaksdfhjlklsadfjjlkjasdfjkljlk

