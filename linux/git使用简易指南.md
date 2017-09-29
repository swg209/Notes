http://www.bootcss.com/p/git-guide/

# 简单操作

### 更新远程仓库

```sh
# 不会同步删除操作
git add *
# 会同步所有，包括删除文件的操作
# git add -A
git commit -m "some description"
git push
```

### 更新本地仓库

但是更新后然后用上面方式更新会是merge到master而不是更新master
```bash
git pull 或者 git fetch origin master
```

### 创建分支

```bash
git checkout -b iss53
# 上面的命令相当于
git branch iss53
git checkout iss53
```

### 删除分支

```bash
git branch -d hotfix
```

# 问题集合

### git push提示没有权限

设置Git的user name和email
```bash
git config --global user.name "yourname"
git config --global user.email "youremail"
```
生成SSH密钥
```bash
查看是否已经有了ssh密钥：cd ~/.ssh
如果没有密钥则不会有此文件夹，有则备份删除
生存密钥：
ssh-keygen -t rsa -C “haiyan.xu.vip@gmail.com”
按3个回车，密码为空。
Your identification has been saved in /home/tekkub/.ssh/id_rsa.
Your public key has been saved in /home/tekkub/.ssh/id_rsa.pub.
The key fingerprint is:
………………
最后得到了两个文件：id_rsa和id_rsa.pub
```
添加密钥到ssh：ssh-add 文件名,需要之前输入密码.

在github上添加ssh密钥，这要添加的是“id_rsa.pub”里面的公钥。
打开https://github.com/,在设置中添加密钥

```bash
测试：ssh git@github.com
The authenticity of host ‘github.com (207.97.227.239)’ can’t be established.
RSA key fingerprint is 16:27:ac:a5:76:28:2d:36:63:1b:56:4d:eb:df:a6:48.
Are you sure you want to continue connecting (yes/no)? yes
Warning: Permanently added ‘github.com,207.97.227.239′ (RSA) to the list of known hosts.
ERROR: Hi tekkub! You’ve successfully authenticated, but GitHub does not provide shell access
Connection to github.com closed.
```
