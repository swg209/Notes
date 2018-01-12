#!/bin/bash
# author: wjy
# Intro：
#   作者并不会shell，这些代码是为了实现鼠标移动随便写的，能用就行
#   所以不要当真！有bug请反馈！

################ utils #####################
# function random(){
#   # 生成随机数
#   min=$1
#   max=$2-$1
#   num=$(date +%s)
#   ((num=(num%max+min)))
#   echo $num
# }

function random() {
  input=$1
  ((num=(${RANDOM}%input)))
  return $num
}

function abs(){
    if (($1>=0));then
        return $1
    else
        return $((-$1));
    fi
}

function __readINI(){
  #　usage:
  #　读取配置文件
  #　__readINI [配置文件路径+名称] [节点名] [键值]
  INIFILE=$1;	SECTION=$2;	ITEM=$3
  _readIni=`awk -F '=' '/\['$SECTION'\]/{a=1}a==1&&$1~/'$ITEM'/{print $2;exit}' $INIFILE`
  echo ${_readIni}
}

function timecomp(){
  # 判断当前时间是否在时间范围[start, end]内
  # 输入三个HH：MM格式的时间，顺序分别是当前时间，start，end
  now=($(date -d "$1" +%s))
  start=($(date -d "$2" +%s))
  end=($(date -d "$3" +%s))
  if [ $now -gt $start ] && [ $now -lt $end ]
  then
    return 1  # 1 = true
  else
    return 0  # 0 = false
  fi
}

function mouse_move(){
  start=$1
  end=$2
  sleeptime=$3
  movepix=$4
  date=($(date +%H:%M))
  (timecomp $date $start $end)
  flag=$?
  while [ $flag -eq 1 ]
  do
      #xdotool mousemove $x $y
      x=($(xdotool getmouselocation | sed -e 's=x:\(.*\) y.*=\1='))
      y=($(xdotool getmouselocation | sed -e 's=.* y:\(.*\)s.*=\1='))
      ((x=($x+$movepix)))
      ((y=($y+$movepix)))
      xdotool mousemove $x $y
      sleep $sleeptime
      ((x=($x-$movepix)))
      ((y=($y-$movepix)))
      cur_x=($(xdotool getmouselocation | sed -e 's=x:\(.*\) y.*=\1='))
      cur_y=($(xdotool getmouselocation | sed -e 's=.* y:\(.*\)s.*=\1='))
      ((sub_x=($cur_x-$x)))
      ((sub_y=($cur_y-$y)))
      (abs $sub_x)
      sub_x=$?
      (abs $sub_y)
      sub_y=$?
      if (($sub_x>$movepix)) || (($sub_y>$movepix))
      then
        xdotool mousemove $cur_x $cur_y
      else
        xdotool mousemove $x $y
      fi
      sleep $sleeptime
      date=($(date +%H:%M))
      (timecomp $date $start $end)
      flag=$?
  done
}

################ init #####################
if [ $1="Weekday" ] || [ $1="Weekend" ] && [ -n "$1" ]
then
  mode=$1
else
  mode=($(__readINI conf.ini Mode mode))
fi

echo "Mode: $mode"
m_start=($(__readINI conf.ini $mode morning_start))
m_end=($(__readINI conf.ini $mode morning_end))
a_start=($(__readINI conf.ini $mode afternoon_start))
a_end=($(__readINI conf.ini $mode afternoon_end))
e_start=($(__readINI conf.ini $mode evening_start))
e_end=($(__readINI conf.ini $mode evening_end))
sleep_time=($(__readINI conf.ini Mode sleep_time))
move_pix=($(__readINI conf.ini Mode move_pix))
rand=($(__readINI conf.ini Mode rand))

#echo "$m_start, $m_end, $a_start, $a_end, $e_start, $e_end, $sleep_time"

################ loop #####################
while :
do
  # morning
  (mouse_move $m_start $m_end $sleep_time $move_pix)
  date=($(date +%H:%M:%S))
  #echo "morning-end, $date"

  # afternoon
  (mouse_move $a_start $a_end $sleep_time $move_pix)
  date=($(date +%H:%M:%S))
  #echo "afternoon-end, $date"

  # evening
  (mouse_move $e_start $e_end $sleep_time $move_pix)
  date=($(date +%H:%M:%S))
  #echo "evening-end, $date"

  sleep 60
done
