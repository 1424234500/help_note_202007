github cmd / shell  git-bash
https://github.com/1424234500/help_note.git		-> E:/ help_note	
https://github.com/1424234500/base.git			-> E:/ workspqce_my/ * 
https://github.com/1424234500/BaseSSM.git
https://github.com/1424234500/walker.git
https://github.com/1424234500/cc.git
https://github.com/1424234500/GraphicsTools.git 



Git中从远程的分支获取最新的版本到本地有这样2个命令：
1. git fetch：相当于是从远程获取最新版本到本地，不会自动merge 
git fetch origin master
git log -p master..origin/master
git merge origin/master 
   首先从远程的origin的master主分支下载最新的版本到origin/master分支上
   然后比较本地的master分支和origin/master分支的差别
   最后进行合并
   上述过程其实可以用以下更清晰的方式来进行：
 git fetch origin master:tmp
git diff tmp 
git merge tmp 
    从远程获取最新的版本到本地的test分支上
   之后再进行比较合并
2. git pull：相当于是从远程获取最新版本并merge到本地
 git pull origin master

//本地仓库为空 未添加文件 add 
error: src refspec master does not match any.
error: failed to push some refs to 'git@github.com:hahaha/ftpmanage.git'

git add -A  //添加需要提交的<修改>文件以及 新建的文件
git commit -am "update" //a表示自动添加 修改过的文件？ 但不包括新建的文件
git pull origin master  //下载并合并到当前分支
git push origin master  //推送上传

//重建 清空历史记录 仓库瘦身
1.Checkout
   git checkout --orphan latest_branch
2. Add all the files
   git add -A
3. Commit the changes
   git commit -am "commit message"
4. Delete the branch
   git branch -D master
5.Rename the current branch to master
   git branch -m master
6.Finally, force update your repository 
   git push -f origin master

//仓库zip下载 链接 更新 ##########################
//…or push an existing repository from the command line 
git init
git add .

git remote add origin https://github.com/1424234500/walker.git
git remote update
git add -A  #添加需要提交的<修改>文件以及 新建的文件
git commit -am "update" #a表示自动添加 修改过的文件？ 但不包括新建的文件
git pull origin master  #下载并合并到当前分支
git push origin master  #推送上传
git push -u origin master


//同步 分享 与 更新项目 push fetch remote 
git remote <-v url> 列出远端别名
#如果没有任何参数，Git 会列出它存储的远端仓库别名了事。
默认情况下，如果你的项目是克隆的（与本地创建一个新的相反）， 
Git 会自动将你的项目克隆自的仓库添加到列表中，并取名“origin”。 
#如果你执行时加上 -v 参数，你还可以看到每个别名的实际链接地址。

git remote add 为你的项目添加一个新的远端仓库
#执行 git init 的时候，缺省情况下 Git 就会为你创建“master”分支。 但是这名字一点特殊意味都没有 —— 事实上你并不非得要一个叫做“master”的分支。 
#不过由于它是缺省分支名的缘故，绝大部分项目都有这个分支。
#Add the local directory to the remote web repertory
git remote add origin https://github.com/1424234500/BaseSSM.git
 
像分支的命名一样，远端仓库的别名是强制的 —— 就像“master”，
没有特别意义，但它广为使用， 因为 git init 默认用它；
“origin”经常被用作远端仓库别名，就
因为 git clone 默认用它作为克隆自的链接的别名。
随便什么都可以。

git remote rm 删除现存的某个别名 
//git fetch <远程主机名> <分支名>  更新 同步  clone 下载项目
将你的仓库与远端仓库同步，提取所有它独有的数据到本地分支以合并或者怎样。
//git pull origin master  下载并合并fetch and merge 
#Push your local version repertory to your github where is at the web / internet
//git push -u origin master 推送上传
git push [alias] [branch]，就会将你的 [branch] 分支推送成为 [alias] 远端上的 [branch] 分支。 


使用 //本地仓库
git add 添加需要追踪的新文件和待提交的更改， 然后使用 
git status 和 
git diff [version commit name branch name] 查看有何改动， 最后用 
git commit 将你的快照记录。
这就是你要用的基本流程，绝大部分时候都是这样的 

#Add   添加文件到缓存
git add .<all>  	/  directory	/	file
git add -A
#看看我们的项目的当前状态。
git status <-s>
#显示已写入缓存与已修改但尚未写入缓存的改动的区别
git diff <--cached> <HEAD> <-STAT>

#Commit to local <cache> ! version repertory with some info / about 
git commit -m "commit log about"
#缓存并提交每个改动（不含新文件） 通常直接从硬盘删除文件，然后执行 
//git commit -am "info" 会简单些。 它会自动将删除的文件从索引中移除。

#取消缓存已缓存的内容
git reset HEAD 


//分支
git branch (branchname) 
来创建分支， 使用 
git checkout (branchname) 命令
切换到该分支，
在该分支的上下文环境中， 
提交快照等，
之后可以很容易地来回切换。
当你切换分支的时候，
Git 会用该分支的最后提交的快照替换你的工作目录的内容， 所以多个分支不需要多个目录。使用 git merge 来合并分支。你可以多次合并到统一分支， 也可以选择在合并之后直接删除被并入的分支。

git branch <--all>列出可用的分支
git branch (branchname) 创建新分支
git checkout (branchname) 切换分支
git checkout -b (branchname) 创建新分支，并立即切换到它
git branch -d (branchname) 删除分支

git merge (branchname) 将分支合并到你的当前分支 
#不仅仅是简单的文件添加、移除的操作，Git 也会合并修改 —— 事实上，它很会合并修改
git add (filename) 要告诉 Git 文件冲突已经解决，你必须把它写入缓存区。 

//日志log
git log <--oneline 紧凑简洁> <--graph 图形界面> <--decorate 详细> 达成当前快照的所有提交消息的工具，叫做 
git log --oneline erlang ^master 想要看“erlang”分支中但不在主分支中的提交
git log --oneline --before={3.weeks.ago} --after={2010-04-18} --no-merges --all-match(并且，默认或) 日期范围以过滤你的提交
git log –grep="key words" --format="%h %an %s" --author="Hausmann" 或者 根据提交注释过滤提交记录 你或许还想根据提交注释中的某个特定短语查找提交记录。可以用 --grep 选项
git log -p 显示每个提交引入的补丁
git log –stat 显示每个提交引入的改动的差值统计

git tag -a start.1.0 重要的阶段，并希望永远记住那个特别的提交快照
git tag -a start.1.0 558151a 忘了给某个提交打标签，又将它发布了，我们可以给它追加标签。 在相同的命令末尾加上提交的 SHA


//git 日志格式化
git log --pretty=format:"%H %an %cd %cr"
git log --date=iso --pretty=format:"%H %an %cd %cr" --after="2018-4-09 17:37:42" --before="2022-11-06 17:45:42"
// aa6492c71ea38371d95f26fc705ebc9be1edfd19 chenpenghui Wed Apr 11 10:41:03 2018 +0800 36 minutes ago
// e4514488d2772ea2acb8e62442eaea6e3331dbec chenpenghui Tue Apr 10 15:34:20 2018 +0800 20 hours ago
// e68d8075414572e8097e312dd02e2dfefc45a358 chenpenghui Mon Apr 9 18:42:27 2018 +0800 2 days ago

//使用diff导出差异文件列表
git diff aa6492c71ea38371d95f26fc705ebc9be1edfd19 e4514488d2772ea2acb8e62442eaea6e3331dbec --stat --name-only
// app/modules/home/controllers/homeLeftCtrl.js
// app/modules/home/directives/homeDirectives.js
// app/modules/home/templates/todo/moreTodo.html
// app/modules/home/templates/todo/tableSort.html
// app/modules/home/templates/todo/todoTable.html
 git diff aaa bbb  --stat --name-only | gzip > package.tar.gz
git diff 608e120 4abe32e --name-only | xargs zip update.zip

%H 提交对象（commit）的完整哈希字串
%h 提交对象的简短哈希字串
%T 树对象（tree）的完整哈希字串
%t 树对象的简短哈希字串
%P 父对象（parent）的完整哈希字串
%p 父对象的简短哈希字串
%an 作者（author）的名字
%ae 作者的电子邮件地址
%ad 作者修订日期（可以用--date= 选项定制格式） --date=iso local rfc short raw relative
%ar 作者修订日期，按多久以前的方式显示
%cn 提交者(committer)的名字
%ce 提交者的电子邮件地址
%cd 提交日期
%cr 提交日期，按多久以前的方式显示
%s 提交说明

git log --after="2018-4-09 17:37:42" --before="2022-11-06 17:45:42" --name-status --abbrev-commit --left-right branchA...branchB > log.txt

--after ：从这个时间之后   
--before ： 从这个时间之前 
--name-status ：显示新增、修改、删除的文件清单。 
--abbrev-commit ：仅显示 SHA-1 的前几个字符，而非所有的 40 个字符
--left-right:每个提交是在哪个分支上,左箭头 < 表示是 branchA 的，右箭头 > 表示是 branchB的
... : 并集关系，两个分支共同的修改记录




当你试图推送到某个以被更新的远端分支时，会出现下面这种情况：

RT ! [rejected] master -> master (fetch first)
在push远程服务器的时候发现出现此错误；原因是没有同步远程的master
需要先同步一下
a.--> git pull origin master
b.--> git push origin master



忽略文件夹
项目文件夹中，会发现生成了一个”.gitignore”文件，打开看，如下 





 

方法一 通过命令直接修改远程地址
进入git_test根目录
git remote 查看所有远程仓库， git remote xxx 查看指定远程仓库地址
git remote set-url origin http://192.168.100.235:9797/john/git_test.git
方法二 通过命令先删除再添加远程仓库

进入git_test根目录
git remote 查看所有远程仓库， git remote xxx 查看指定远程仓库地址
git remote rm origin
git remote add origin http://192.168.100.235:9797/john/git_test.git




//github ssh免密码登录 
ssh-keygen -t rsa # 一直回车下去，不输入密码 生成密钥
cat ~/.ssh/id_rsa.pub
ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQDsF1xYxThqOIkBHmhd8rlEOM6Wppl+cs95F6ztR2Kl30utGHh0qvFotgT+bhPE81NGlTTtfw1000dtyydyx+6JY4ClTOa856vMlDUaISXMAP346LAVodHskKB0/Kur9Zv4G9iwg1ccyJWfrx7QrultuX/yeLMa6WiyFPj4eLc4AksaUXVmqr282dtPodsO+TME+hvAuZksISgVC8PK56qjlg0CWdZdwD/gxKRe2j3Gn0lAZhvm9oTLkSn0sPRYp1+yYftOZNzBy3hY3pFYKB8JbpOXesWaXMfynGxOTXJuFP7xj6T+/Wp0mztAkxFVINznpZ675Udz2hNo3KyqHB8r walker@Walker
github user setting add sshkey 

//github https免密码
#Github Acount
1424234500@qq.com
#The name and email to show when commit 
 //设置用户名 
 // //设置邮箱
 ////设置文件认证
 // //账号密码文件
//全局 默认 --global 进入仓库 单独设定
git config --global user.name "Walker"
git config --global user.email "1424234500@qq.com"
git config --global credential.helper store
echo 'http://{username}:{password}@github.com' > .git-credentials
http://1424234500%40qq.com:qr36@github.com         @->$40
cat .gitconfig
[user]
        name = Walker
        email = 1424234500@qq.com
[credential]
        helper = store

//修改提交邮箱
如果只需要最近一次提交，那么很简单直接使用 git commit --amend 就可以搞定
git commit --amend --author="NewAuthor <NewEmail@address.com>"

//git 编码
# 提交时转换为LF，检出时转换为CRLF
git config --global core.autocrlf true

# 提交时转换为LF，检出时不转换
git config --global core.autocrlf input

# 提交检出均不转换
git config --global core.autocrlf false


# 拒绝提交包含混合换行符的文件
git config --global core.safecrlf true

# 允许提交包含混合换行符的文件
git config --global core.safecrlf false

# 提交包含混合换行符的文件时给出警告
git config --global core.safecrlf warn
// 转码
find . -type f | xargs dos2unix

find -type f | grep -v .git | grep '^.*\(\(\.c\)\|\(\.sh\)\)$'  
find -type f | grep -v .git | grep '^.*\(\(\.c\)\|\(\.sh\)\)$' | xargs dos2unix

gnutls_handshake() failed: The TLS connection was non-properly terminated.
瞅下本机dns配置,添加阿里的dns
sudo vim /etc/resolv.conf
nameserver  223.5.5.5
nameserver  223.6.6.6


//git 回滚
git reflog
57541c2 HEAD@{0}: pull origin master: Fast-forward
3915130 HEAD@{1}: commit: Fri Mar 16 09:07:03 DST 2018
cc7b6de HEAD@{17}: commit: Thu Nov 30 15:10:42 DST 2017
77b1fc9 HEAD@{18}: commit: datepicker button
ad863f7 HEAD@{19}: commit (initial): start


git reset --hard 3915130
Unlink of file 'pro/WEB-INF/lib/DSPClient-1.0.2018092600.jar' failed. Should I t 
ry again? (y/n) 
y


