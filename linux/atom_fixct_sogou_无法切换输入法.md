https://github.com/atom/atom/issues/5447

@yuyichao I found that the environment variables were wrong. I edited ~/.xprofile as below and it worked.

export GTK_IM_MODULE=fcitx
thanks a lot @yuyichao @xfq @yuyichao @wengxt @defunkt

## 如果

上面的内容对你有用是最好，但是对我没用。

我的解决办法是，在atom里面打开两个文件。当你在某个文件中编辑时发现无法切换到sogou，`ctrl+tab`切换到另一个文件再切换回来，就可以了。
