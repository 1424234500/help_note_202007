
//maven
wget http://mirrors.tuna.tsinghua.edu.cn/apache/maven/maven-3/3.6.0/binaries/apache-maven-3.6.0-bin.tar.gz
tar -xzvf apache-maven-3.6.0-bin.tar.gz
//默认本地仓库~/.m2/
//配置maven地址	
mv apache-maven-3.6.0/conf/settings.xml apache-maven-3.6.0/conf/settings.xml.default
cp D:\help_note\java-maven-settings.xml apache-maven-3.6.0/conf/settings.xml
vim apache-maven-3.6.0/conf/settings.xml
<mirror>
        <id>nexus-aliyun</id>
        <mirrorOf>*</mirrorOf>
        <name>Nexus aliyun</name>
        <url>http://maven.aliyun.com/nexus/content/groups/public</url>
</mirror>

//配置环境变量
echo 'PATH=PATH:/home/walker/software/apache-maven-3.6.0/bin' >> /etc/profile


配置eclipse idea
1.配置模板 下载local  让可以使用模板创建项目
archetype-catalog.xml
2.配置文件源Maven-User Settings-Global Settings 让使用新的配置文件 源 统一 配置文件
/home/walker/software/apache-maven-3.6.0/conf/settings.xml
配置外置maven
配置仓库存储地址



mvn clean package依次执行了clean、resources、compile、testResources、testCompile、test、jar(打包)                等７个阶段。
mvn clean install依次执行了clean、resources、compile、testResources、testCompile、test、jar(打包)、install        等8个阶段。
mvn clean deploy依次执行了 clean、resources、compile、testResources、testCompile、test、jar(打包)、install、deploy 等９个阶段。

//打包配置
要想jar包能直接通过java -jar xxx.jar运行，需要满足：
1、在jar包中的META-INF/MANIFEST.MF中指定Main-Class，这样才能确定程序的入口在哪里；
2、要能加载到依赖包。

//mvn 指令依赖环境变量 需要和 配置的pom里面的相同  否则使用eclipse自带install也可

//项目将会自动打包并安装到本地仓库中
mvn clean install -Dmaven.test.skip=true
//只打包
mvn clean package -Dmaven.test.skip=true

//配置文件不放入默认jar包 则需要配置plugin复制到指定目录 复制启动脚本sh

//依赖 源码
查看当前项目已被解析的依赖：
mvn dependency:list
打印出已解决依赖的列表 :
mvn dependency:resolve
打印整个依赖树 :
mvn dependency:tree
dependency:tree -Dverbose
下载源码
mvn dependency:sources


mvn clean

19. 部署
mvn deploy
21. 源码打包：
mvn source:jar

1. 显示版本信息 注意jdk和项目jdk差异
mvn -version/-v

4. 运行项目于jetty上:
mvn jetty:run
5. 显示详细错误 信息:
mvn -e
6. 验证工程是否正确，所有需要的资源是否可用:
mvn validate
7. 在集成测试可以运行的环境中处理和发布包:
mvn integration-test
8. 运行任何检查，验证包是否有效且达到质量标准:
mvn verify
9. 产生应用需要的任何额外的源代码，如xdoclet :
mvn generate-sources
10. 使用 help 插件的  describe 目标来输出 Maven Help 插件的信息:
mvn help:describe -Dplugin=help
11. 使用Help 插件输出完整的带有参数的目标列 :
mvn help:describe -Dplugin=help -Dfull
12. 获取单个目标的信息,设置  mojo 参数和  plugin 参数。此命令列出了Compiler 插件的compile 目标的所有信息 :
mvn help:describe -Dplugin=compiler -Dmojo=compile -Dfull
13. 列出所有 Maven Exec 插件可用的目标:
mvn help:describe -Dplugin=exec -Dfull
14. 看这个“有效的 (effective)”POM，它暴露了 Maven的默认设置 :
mvn help:effective-pom
15. 想要查看完整的依赖踪迹，包含那些因为冲突或者其它原因而被拒绝引入的构件，打开 Maven 的调试标记运行 :
mvn install -X
16. 给任何目标添加maven.test.skip 属性就能跳过测试 :
mvn install -Dmaven.test.skip=true
17. 构建装配Maven Assembly 插件是一个用来创建你应用程序特有分发包的插件 :
mvn install assembly:assembly
18. 生成Wtp插件的Web项目 :
mvn -Dwtpversion=1.0 eclipse:eclipse
19. 清除Eclipse项目的配置信息(Web项目) :
mvn -Dwtpversion=1.0 eclipse:clean
20. 将项目转化为Eclipse项目 :
mvn eclipse:eclipse
21. mvn exec命令可以执行项目中的main函数 :
首先需要编译java工程：mvn compile
不存在参数的情况下：mvn exec:java -Dexec.mainClass="***.Main"
存在参数：mvn exec:java -Dexec.mainClass="***.Main" -Dexec.args="arg0 arg1 arg2"
指定运行时库：mvn exec:java -Dexec.mainClass="***.Main" -Dexec.classpathScope=runtime

在应用程序用使用多个存储库 
复制代码
<repositories>    
    <repository>     
        <id>Ibiblio</id>     
        <name>Ibiblio</name>     
        <url>http://www.ibiblio.org/maven/</url>   
    </repository>   
    <repository>     
        <id>PlanetMirror</id>     
        <name>Planet Mirror</name>     
        <url>http://public.planetmirror.com/pub/maven/</url>   
    </repository>  
</repositories>

mvn deploy:deploy-file -DgroupId=com -DartifactId=client -Dversion=0.1.0 -Dpackaging=jar -Dfile=d:\client-0.1.0.jar -DrepositoryId=maven-repository-inner -Durl=ftp://xxxxxxx/opt/maven/repository/
复制代码
发布第三方Jar到本地库中
 
-DdownloadSources=true
-DdownloadJavadocs=true
才能在其他项目打包时 引用本地项目?!!!!!!!!!!!!!!!!!!!!!!!!
三，附加
mvn help:describe


${basedir} 项目根目录
${project.build.directory} 构建目录，缺省为target
${project.build.outputDirectory} 构建过程输出目录，缺省为target/classes
${project.build.finalName} 产出物名称，缺省为${project.artifactId}-${project.version}
${project.packaging} 打包类型，缺省为jar
${project.xxx} 当前pom文件的任意节点的内容


