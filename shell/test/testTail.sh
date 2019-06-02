

function testTail(){
    for file in $HOME/*of*r*
    do
        echo $file
    done
    
    
    for i in {0..5}
    do
        echo '$'"$i value[$i] = $i"
    done

}


echo ">>>>>>>>>>>>>>>>>>>>>>>>>Begin"
echo ">>shell: ${0}"
echo ">>params: $*"     #$*一个单字符串显示所有向脚本传递的参数。
                #$@与$*相同，但是使用时加引号，并在引号中返回每个参数
echo "----------------"

testTail $1 $2 $3

echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>End"
