# !/bin/bash  
########################################### 
# ./do function <help>
# About:
# 
# start wifi config restart 
###########################################


function linux_config_wifi(){
    sudo ifconfig wlp4s0 down    #关闭网络
    sudo ifconfig wlp4s0 up    #关闭网络
#    iwlist wlp4s0 scan | grep ESSID | awk -F'"' '{print $2}'    #扫描wifi可用
    local wifi_names=(`iwlist wlp4s0 scan | grep SSID | awk -F'"' '{print $2}'` ) #截取wifi-name
    echo ${wifi_names[@]}
    if (( ${#wifi_names[@]} > 0 ))
    then
        local wifi_name=${wifi_names[0]}
        wifi_name='ICBC-WiFi'
        echo 'Close wifi_name'
        sudo iwconfig wlp4s0 essid 'xxx'  #配置wifi  
        sleep 3
        echo 'Connect wifi ' $wifi_name
        sudo iwconfig wlp4s0 essid $wifi_name  #配置wifi  
#        iwconfig wlp4s0 key <wifi-pwd>     #配置密码
        sudo iwconfig wlp4s0 ap auto            #配置自动连接
#        ifconfig wlp4s0 192.168.1.120      #配置ip
    else
        echo 'no wifi scan can user '
    fi
   
    
    


} 




# 单独执行文件时操作如下 引入时提示
_temp='linux_config_wifi.sh'
if [[ $0 =~ $_temp ]]
then
    linux_config_wifi $@
else
    echo 'source '$_temp
fi 
