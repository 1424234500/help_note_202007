#!/bin/bash  
###########################################
#do
#批量生成 redis_cluster 配置文件 根据redis_cluster_7000_cp.conf 模板文件修改
#./do commit <help>
###########################################



fromport=7000
toport=7005
fromfile="redis_cluster_7000_cp.conf"


for port in `seq ${fromport} ${toport}`
do
    tofile="redis_cluster_${port}.conf"
    echo ${tofile}
    cat ${fromfile} | sed s/${fromport}/${port}/  > ${tofile}
#    sed s/7000/7002/ redis_cluster_7000.conf
done

