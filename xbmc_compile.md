#Xbmc 源码编译
##XBMC简介
###[xbmc 简介](http://xbmc.org/about/)
###xbmc 相关
* [xbmcbuntu](http://wiki.xbmc.org/?title=XBMCbuntu)
* [raspbmc](http://www.raspbmc.com/about/)
##源码下载
*download xbmc
[xbmc sourcecode](http://xbmc.org/download/)
命令行使用git 下载
    cd ~
    git clone git://github.com/xbmc/xbmc.git
这样就得到了xbmc的一个文件夹，里面包含的是xbmc的源码。
[about git](http://baike.baidu.com/view/1531489.htm#1)
*compile for linux and android use this same package*

##compile for linux
###环境
ubuntu 12.04 64位 x86

###编译步骤
1. Installing the required Ubuntu packages
>    对于老版本的ubuntu，有些包可能没有更新过时了。可以手动编译那些软件包，也可以使用team-xbmc官方的[PPA](http://launchpad.net/~team-xbmc/+archive/ppa)
    ![参考](../Pictures/Selection_005.png)
>    两种方法install required packages
**Copy and paste the following line corresponding to your system**
For Ubuntu (all versions >= 7.04):
    sudo apt-get install git-core build-essential gawk pmount libtool nasm yasm automake cmake gperf zip unzip bison libsdl-dev libsdl-image1.2-dev libsdl-gfx1.2-dev libsdl-mixer1.2-dev libfribidi-dev liblzo2-dev libfreetype6-dev libsqlite3-dev libogg-dev libasound2-dev python-sqlite libglew-dev libcurl3 libcurl4-gnutls-dev libxrandr-dev libxrender-dev libmad0-dev libogg-dev libvorbisenc2 libsmbclient-dev libmysqlclient-dev libpcre3-dev libdbus-1-dev libhal-dev libhal-storage-dev libjasper-dev libfontconfig-dev libbz2-dev libboost-dev libenca-dev libxt-dev libxmu-dev libpng-dev libjpeg-dev libpulse-dev mesa-utils libcdio-dev libsamplerate-dev libmpeg3-dev libflac-dev libiso9660-dev libass-dev libssl-dev fp-compiler gdc libmpeg2-4-dev libmicrohttpd-dev libmodplug-dev libssh-dev gettext cvs python-dev libyajl-dev libboost-thread-dev libplist-dev libusb-dev libudev-dev libtinyxml-dev libcap-dev curl swig default-jre

For >= 10.10:
    sudo apt-get install autopoint libltdl-dev

On 8.10 and older versions, libcurl is outdated and thus XBMC will not compile properly.
In this case you will have to manually compile the latest version.
    wget http://curl.sourceforge.net/download/curl-7.19.7.tar.gz
    tar -xzf curl-7.19.7.tar.gz
    cd curl-7.19.7
    ./configure --disable-ipv6 --without-libidn --disable-ldap --prefix=/usr
   # make
   # sudo make install

We currently need a version of taglib that has not been packaged yet. We supply a Makefile in
lib/taglib to make it easy to install into /usr/local until it is available in apt.

   # make -C lib/taglib
   # sudo make -C lib/taglib install

Unless you are proficient with how linux libraries and versions work, do not
try to provide it yourself.
    **Use a single command to get all build dependencies**
2. How to compile

###出现的问题及解决
##compile for android 
###环境
###编译步骤
###出现的问题及解决






