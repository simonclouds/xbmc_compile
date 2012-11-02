# Xbmc 源码编译

------------------------------

## XBMC简介
### xbmc 
> XBMC 是一个优秀的自由和开源的（GPL）媒体中心软件。XBMC最初是microsoft为Xbox而开发，现在可以运行在Linux、OSX、Windows系统。  
<http://xbmc.org/about/>

### xbmc 相关
* [xbmcbuntu](http://wiki.xbmc.org/?title=XBMCbuntu)
* [raspbmc](http://www.raspbmc.com/about/)

--------------------
## 源码下载
* download xbmc  
><!--[xbmc sourcecode](http://xbmc.org/download/)-->命令行使用git 下载  

	cd ~  
	git clone git://github.com/xbmc/xbmc.git

* 版本管理工具 [Git](http://baike.baidu.com/view/1531489.htm#1)简介  
>NOTICE: *compile for linux and android use this same package*

------------------------
##Compile for linux
###环境
>ubuntu 12.04 64位 x86

###编译步骤
#### 1. Installing the required Ubuntu packages
> 对于老版本的ubuntu，有些包可能没有更新过时了。可以手动编译那些软件包，也可以使用team-xbmc官方的[PPA](http://launchpad.net/~team-xbmc/+archive/ppa).

>**两种方法install required packages.**

*(1) Copy and paste the following line corresponding to your system*

>For Ubuntu (all versions >= 7.04):

	sudo apt-get install git-core build-essential gawk pmount libtool nasm yasm automake cmake gperf zip unzip bison libsdl-dev libsdl-image1.2-dev libsdl-gfx1.2-dev libsdl-mixer1.2-dev libfribidi-dev liblzo2-dev libfreetype6-dev libsqlite3-dev libogg-dev libasound2-dev python-sqlite libglew-dev libcurl3 libcurl4-gnutls-dev libxrandr-dev libxrender-dev libmad0-dev libogg-dev libvorbisenc2 libsmbclient-dev libmysqlclient-dev libpcre3-dev libdbus-1-dev libhal-dev libhal-storage-dev libjasper-dev libfontconfig-dev libbz2-dev libboost-dev libenca-dev libxt-dev libxmu-dev libpng-dev libjpeg-dev libpulse-dev mesa-utils libcdio-dev libsamplerate-dev libmpeg3-dev libflac-dev libiso9660-dev libass-dev libssl-dev fp-compiler gdc libmpeg2-4-dev libmicrohttpd-dev libmodplug-dev libssh-dev gettext cvs python-dev libyajl-dev libboost-thread-dev libplist-dev libusb-dev libudev-dev libtinyxml-dev libcap-dev curl swig default-jre

>For >= 10.10:  

	sudo apt-get install autopoint libltdl-dev

>On 8.10 and older versions, libcurl is outdated and thus XBMC will not compile properly.In this case you will have to manually compile the latest version.  

    wget http://curl.sourceforge.net/download/curl-7.19.7.tar.gz
    tar -xzf curl-7.19.7.tar.gz
    cd curl-7.19.7
    ./configure --disable-ipv6 --without-libidn --disable-ldap --prefix=/usr
    make
    sudo make install

>	We currently need a version of taglib that has not been packaged yet. We supply a Makefile in lib/taglib to make it easy to install into /usr/local until it is available in apt.  

	make -C lib/taglib
	sudo make -C lib/taglib install

>	Unless you are proficient with how linux libraries and versions work, do not try to provide it yourself.

*(2) Use a single command to get all build dependencies*

>	You can get all build dependencies used for building the packages on the PPA. For this, you need to specify the PPA in your apt sources. Please find the documentation on how to add a PPA to your system here:<http://launchpad.net/+help/soyuz/ppa-sources-list.html>

>	The PPA used for XBMC (developpement version) is located on the following page:<http://launchpad.net/~team-xbmc/+archive/unstable>

 	**Note 1:**  Click on "Technical details about this PPA" to display the sources.list entries.  
 	**Note 2:**  If you are using a distribution that has outdated libraries, do not forget to use the following ppa: <http://launchpad.net/~team-xbmc/+archive/ppa>

>	Update apt:

	sudo apt-get update

>	Here is the magic command to get the build dependencies (used to compile the version on the PPA).  

	sudo apt-get build-dep xbmc

>	For Hardy add `deb http://ppa.launchpad.net/team-xbmc/xbmc-ppa-build-depends/ubuntu hardy main` to sources.list.  
>**Avoid using aptitude** for the build-dep command. It doesn't resolve everything.  
>	For developers and anyone else who compiles frequently it is recommended to use ccache.

	sudo apt-get install ccache

>	A **tip** for those with multiple computers at home is to check out distcc (totally unsupported from xbmc of course)  

    sudo apt-get install distcc

#### 2. How to compile

+ 	`cd $HOME/xbmc`
+ 	`./bootstrap`
+ 	`./configure `
+	`make`
+ 	`sudo make install`

###出现的问题及解决
1.在执行`./configure` 的时候出现  
>configure error: Could not find a required library. Please see the README for your platform.  

>分析可能的原因是在安装依赖包的时候出现问题.查看install the required packages.  

2.在安装依赖包执行很长的那个 `sudo ***`  的时候出现.
>	The following packages have unmet dependencies:
	libudev-dev : Depends: libudev0 (= 175-0ubuntu9.1) but 175-0ubuntu9.2 is to be installed
	E: Unable to correct problems, you have held broken packages.

>分析可能的原因是在执行安装依赖包的时候出现的问题,其软件包应该安装9.1版本,但是只有9.2版本的在等待被安装.跟踪此问题:定位libudev0 : 命令: 

	locate libudev0

>	得到输出:  
	/var/cache/apt/archives/libudev0_175-0ubuntu9.2_amd64.deb  
	/var/cache/apt/archives/libudev0_175-0ubuntu9.2_i386.deb  
	于是下载libudev0_175-0ubuntu9.2_amd64.deb和libudev0_175-0ubuntu9.2_i386.deb 这两个包,替换掉原来的9.2版本的包.重新安装依赖包.  
>	当直接安装这两个包时,提示已经安装了更新的版本.于是先卸载...  
	使用synaptic package manager

	sudo apt-get install synaptic

>	用synaptic卸载包时,提示:  
>	Could not apply changes!Fix broken packages first！  
	菜单栏:Edit-->fix broken packages
	弹出提示框:  
	E: Error, pkgProblemResolver::Resolve generated breaks, this may be caused by held packages.  
	E: Unable to correct dependencies.  
>	解决1:(root执行)

	dpkg --configure -a
	apt-get update

>	再进入synaptic 的时候,标记livudev0进行remove的时候,仍然提示相同的错误.  
	解决2:将source.list替换回源来的source.list 再

	sudo apt-get update

>	再卸载libudev0仍然提示broken package!!!!陷坑里去了.于是决定推翻重来.删除xbmc的源码包.从最开始**备份的压缩包**(自己压缩)再重新解压一个文件夹.重来:(.  

3.重新configure出现问题:  
>	configure: error: == Could not find libssh. ==  
	solve:install libssh  
	download [libssh-0-5-2.tar.gz](http://www.libssh.org/2011/09/17/libssh-0-5-2/) and install it use its readme file.

4.configure 找不到 required program .  
>	configure: error: Could not find a required program. Please see the README for your platform.  
	what program missed ? I dont know as well.  
	Do following step again:

	sudo apt-get install git-core build-essential gawk pmount libtool nasm yasm automake cmake gperf zip unzip bison libsdl-dev libsdl-image1.2-dev libsdl-gfx1.2-dev libsdl-mixer1.2-dev libfribidi-dev liblzo2-dev libfreetype6-dev libsqlite3-dev libogg-dev libasound2-dev python-sqlite libglew-dev libcurl3 libcurl4-gnutls-dev libxrandr-dev libxrender-dev libmad0-dev libogg-dev libvorbisenc2 libsmbclient-dev libmysqlclient-dev libpcre3-dev libdbus-1-dev libhal-dev libhal-storage-dev libjasper-dev libfontconfig-dev libbz2-dev libboost-dev libenca-dev libxt-dev libxmu-dev libpng-dev libjpeg-dev libpulse-dev mesa-utils libcdio-dev libsamplerate-dev libmpeg3-dev libflac-dev libiso9660-dev libass-dev libssl-dev fp-compiler gdc libmpeg2-4-dev libmicrohttpd-dev libmodplug-dev libssh-dev gettext cvs python-dev libyajl-dev libboost-thread-dev libplist-dev libusb-dev libudev-dev libtinyxml-dev libcap-dev curl swig default-jre

>	terminal download some packages and problem solved.
	after that everything goes well till the compiling end.

---------------------------
##Compile for android 
###环境
>	Ubuntu 10.04 64位 X86

###编译步骤

####1.install required packages:  

	sudo apt-get install build-essential default-jdk git curl autoconf unzip zip zlib1g-dev gawk gperf cmake ia32-libs

####2.Installing and setting up the Android environment
>Get the Android SDK, go to http://developer.android.com/sdk and
download the latest version for your operating system. The Crystax NDK
can be downloaded from http://www.crystax.net/en/android/ndk  
   
>2.1 Installing Android SDK packages
After having extracted the Android SDK to <android-sdk> you need to
install some android packages using the Android SDK Manager:

	# cd <android-sdk>/tools
	# ./android update sdk -u -t platform,platform-tool

>2.2 Setup the Android toolchain
	To be able to compile XBMC and the libraries it depends on for the
Android platform you first need to setup an Android toolchain using
the Android NDK which you earlier extracted to <android-ndk>. 

>	The following commands will create a toolchain suitable for the most
common scenario. The --install-dir option (and therefore the <android-toolchain> value)specifies where the resulting toolchain should be installed (your choice).

	# cd <android-ndk>
	# ls platforms
	# cd build/tools
	# ./make-standalone-toolchain.sh --ndk-dir=../../ \
     --install-dir=<android-toolchain>/android-14 --platform=android-14

>2.3 Create a (new) debug key to sign debug APKs

	# keytool -genkey -keystore ~/.android/debug.keystore -v -alias \
      androiddebugkey -dname "CN=Android Debug,O=Android,C=US" -keypass \
      android -storepass android -keyalg RSA -keysize 2048 -validity 10000

####3.Getting the source code  

	# cd $HOME
	# git clone git://github.com/xbmc/xbmc.git xbmc-android
	# cd xbmc-android
	# git submodule update --init addons/skin.touched

####4.compile
>	4.1 Building dependencies

	# cd $HOME/xbmc-android/tools/android/depends
	# ./bootstrap
	# ./configure --build=arm-linux-android --with-sdk=/home/$USER/Tools/sdk-android --with-ndk=/home/$USER/Tools/ndk-r7 --with-toolchain=/home/$USER/Tools/android-14 --with-tarballs=/home/$USER/Tools/tarballs
	# make -j4

>	4.2 Building XBMC  

	# cd $HOME/xbmc-android
	# make -C tools/android/depends/xbmc

###出现的问题及解决

----------

2:55 下午 星期五, 十一月 02, 2012





