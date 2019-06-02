source function.sh
#. ./function.sh
 
function main(){ 
    echo
    echo "Begin---------------"
    echo ">>shell: ${0}"
    echo ">>params: $*" #$@与$*相同，使用时加引号，返回每个参数
    echo "-------" 

    filename='file'
 #set
    
#testDualProcess
#testDualProcessLimit


testFile /home




#testReadAuto $filename #测试循环sleep写入文件然后tail -f file跟踪输出


    
    
    
    
    
    
    
    
    
    
    
    
    echo "-----------------End"
    echo
 
}

main $@

