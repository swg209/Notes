#!/bin/bash
echo "what is your name?"
read PERSON
echo "hello, $PERSON"

# for
for skill in Ada Coffe Action Java
do
  echo "I am good at ${skill}Script"
done

# 删除变量
unset PERSON
echo $PERSON

# 将变量改为只读变量
myUrl="www.baidu.com"
readonly myUrl

# 特殊变量
# $* 和 $@ 都表示传递给函数或脚本的所有参数，不被双引号(" ")包含时，都以"$1" "$2" … "$n" 的形式输出所有参数。
# 但是当它们被双引号(" ")包含时，"$*" 会将所有的参数作为一个整体，以"$1 $2 … $n"的形式输出所有参数；
# "$@" 会将各个参数分开，以"$1" "$2" … "$n" 的形式输出所有参数。
echo "file name: $0"
echo "first parameter: $1"
echo "second parameter: $2"
echo "parameter number: $#"
echo "all the parameter: $*"
echo "$@"
echo "the return state or the return value of the function: $?"
echo "PID: $$"
# 退出状态
# $? 可以获取上一个命令的退出状态。所谓退出状态，就是上一个命令执行后的返回结果。
# 退出状态是一个数字，一般情况下，大部分命令执行成功会返回 0，失败返回 1。
# 不过，也有一些命令返回其他值，表示不同类型的错误。

# 转义字符
echo -e "alarm \a"

# 拼接字符串
