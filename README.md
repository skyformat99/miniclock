# MINI CLOCK - 一个小巧漂亮的点阵时钟

标签（空格分隔）： 未分类

---

![image](https://github.com/solosky/miniclock/raw/master/img/main.png)
![image](https://github.com/solosky/miniclock/raw/master/img/preview.gif)


# 特色

 1. 显示时间，日期，温度，湿度
 2. 时钟使用DS3231芯片，精度可以达一年误差30秒，无需校准
 3. 掉电仍走时，再次插电无需重新设置
 4. 支持DHT11/DHT22系列温湿度传感器，温度最高精度0.5℃
 5. 背光自动调节
 6. 支持两种经典字体
 7. 毫无特色的闹钟功能（待实现）
 8. MicroUSB电源接口，可以插USB提供电源
 9. 基于arduino，开放源代码，可以个性化定制


# 缘起

之前我家的液晶时钟坏了，一直想自己做一个时钟。<br>
在论坛里面搜了很多自制的时钟，要么都是非常简单各种洞洞板各种飞线，要么就不实用的比如12864的点阵液晶时钟，要么就是没有湿度检测的功能。特别是这个湿度检测，相当实用。在北方居住的同学应该知道湿度很干的，需要开加湿器加湿。需要一个东西能显示湿度。<br>
于是参考了很多时钟方案，在X宝选了很久的点阵，终于决定采用白色的7x11的两块点阵来显示时间，显示效果最好。<br>

# 方案

MCU基于Arduino方案，ATmega328p + CH340。这方案很经典，可以一直复用，并且可以使用arduino生态体系里面的库。<br>
时钟芯片必须采用DS3231，精度高，使用简单。<br>
本来想弄一个精度比较高的温湿度传感器芯片，却发现市面上的比较流行只有DHT系列，而且这个精度嘛，实在是太差了，但是也没啥更好的既能检测温度，又能检测湿度的方案了。DHT11精度±1℃，DHT22精度0.5℃，
有钱的同学可以使用DHT22，精度要高点。<br>
显示芯片采用了TM1640，自带行扫瞄。由于买的点阵商家只有共阳级的点阵，选芯片倒是麻烦了点。天微的共阴的显示芯片支持7x11的倒是挺多的，但是共阳支持7x11的芯片实在是太少了，<br> 幸好有一个TM1640，这货支持8x16共阳或者16x8共阴。用来显示8x8的点阵其实刚好，用在这里略微有点浪费。<br>


# BOM单

 - ATMEGA328p LQFP32（主MCU芯片） x1
 - CH340G （串口转USB编程芯片，如不改固件可不焊接） x1
 - DS3231N （高精度时钟芯片） x1
 - TM1640 （LED显示芯片） x2
 - 7x11共阳白色点阵 （[可以点这里购买，淘宝独一家](https://item.taobao.com/item.htm?spm=a1z09.2.0.0.Sjd4vl&id=528278915669&_u=r3umvhn4d2c)） x2
 - MicroUSB座子 x1
 - 贴片微动开关 x4
 - 0805 贴片LED （黄绿色，电源指示灯） x1
 - 0805 0.1uF 贴片电容 若干
 - 0805 22pF 贴片电容 x4
 - 1208 100uF 钽电容 x3
 - 0805 1K 贴片电阻 x若干
 - 0805 10K 贴片电阻 x若干
 - 0805 1M 贴片电阻 x1
 - 0805 100mA 自恢复熔丝 x1
 - 12MHz 49S贴片晶振 x1
 - 16MHz 49S贴片晶振 x1
 - DHT11/DHT22 （温湿度芯片）x1
 - 有源蜂鸣器 x1
 - CR2025电池座 x1
 - CR2025电池 x1
 - 光敏电阻 x1
 - 2.54mm间距的军品孔 （便于拆芯片，可选） x3

相关BOM都是常用的物料，请自行某宝购买即可，但是LED点阵只此一家，手快有，手慢无。

# 说明书


### 普通显示模式

 - 显示时间 10秒钟
 - 显示日期 1秒钟
 - 显示湿度 1秒钟
 - 显示温度 1秒钟

在普通模式下，可以短按K1快速切换下一个显示内容。

### 设置模式

 - 长按K2直到时钟闪烁，进入设置模式
 - 短按K2可以切换设置项，按K1设置项加1，按K3设置项减1
 - 当前的设置项会以0.5秒闪烁
 - 设置项的顺序为，小时 -> 分钟 -> 月 -> 日 -> 年 -> 字体
 - 设置完字体后，短按K2可以退出设置模式
 - 在设置的过程中，可以随时长按K2退出设置模式；


# 焊接提醒

特别提醒：由于全是贴片原件，请焊接新手先联系一段时间的贴片焊接再组装这个电路板。

 - 建议焊接一个芯片就检查功能是否正常。
 - MicroUSB座子特别不好焊接（主要是焊盘太小了，本来想加长焊盘的，可是发现板子太小，实在是没有空间了），建议的焊接方式是，用蹄型烙铁，蘸松香，挂很少的锡，轻轻的接触下MicroUSB内部的连接点即可。焊接完了用万用表检查是否有短路，如果没有短路再焊接下一个芯片；
 - DHT11和LED点阵均使用军品孔连接，这个主要是为了测试方便  取下来，如果没有也可以直接焊接元件，前提是对自己焊工很自信才行（不然如果没有风枪的话，拆下来巨麻烦）
 - 蜂鸣器和电池座注意焊接的方向

# 如何刷第一个固件

首先需要焊接好ISP座子，然后你需要一个ATMEL的USBISP编程器，如下图（如果没有可以求助马云家的）。

![image](https://github.com/solosky/miniclock/raw/master/img/usbisp.png)
1. 按照下图用杜邦线连接 时钟和编程器。<br>
![image](https://github.com/solosky/miniclock/raw/master/img/isp_connector.png)
2. 下载 Prog ISP编程软件，运行主程序。<br>
3. 点击RD，如果下面提示框中提示“读出ID成功”，则表示线连接正确，可以写入固件。<br>
![image](https://github.com/solosky/miniclock/raw/master/img/ispprog.png)
4. 点击熔丝位设置，分别设置如下值，然后点击写入熔丝设置。<br>
![image](https://github.com/solosky/miniclock/raw/master/img/fuse.png)
```
low_fuses=0xFF
high_fuses=0xDA
extended_fuses=0x05
```
5. 下载最新版本固件（git目录中为build/miniclock-full-firmware-1.0.hex），然后点击文件/调入Flash，选择最新版的固件，点击打开。<br>
6. 点击菜单，命令/写入Flash，稍等片刻即可刷入最新固件。<br>

一些提示：

 - build文件夹有个miniclock-beep-with-bootloader.hex，可以首先刷入这个固件来测试，如果写入成功，蜂鸣器会以间隔一秒的时间蜂鸣；
 - 如果写入提示成功，但是硬件没有反应，建议在刷机软件中点击擦除按钮后重新刷入固件再试。

# 给想改固件的童鞋说明

### 如果要改固件，有几个前提：

1. 你需要按照上面初次刷固件的说明，成功的刷入完整的固件，或者测试固件miniclock-beep-with-bootloader.hex。
2. 焊接好CH340G和周边电路。
3. 安装好CH340G驱动。
4. 插上MicroUSB后，打开设备管理器，Ports(COM /LPT)节点下能出现一个USB-Serial CH340G的串口。
5. 短接CH340G的TX和RX端，能通过串口测试。

### 相关软件下载

http://pan.baidu.com/s/1dELJjPn

### 如果上面条件都满足了，并且你有足够的C语言基础，那么大胆的去改固件吧。

虽然这个固件是基于arduino的设计的，由于官方的arduino的开发软件太难用（我感觉是我用过的最难用的IDE），这里强烈推荐另外一个替代软件，PlatformIO。

1. 首先从官网下载PlatformIO，官网在此  http://platformio.org/。
2. 使用git或者github下载全部的源码。
3. 打开platformIO，菜单选择 File / Open Folder，选择源码中的fw目录。
4. 菜单选择 PlatformIO / Initialize or Update PlatformIO Project..
5. Board选择Arduino Uno，点击Process初始化项目。

这一步可能比较慢，需要下载avr系列toolchain，如果有翻墙的工具建议设置下PlatformIO的代理。<br>
设置代理的方式比较简单，在atom用户目录下，新建.apmrc文件，里面写入如下内容（注意改成你的代理IP），保存重开即可。<br>

```text
http-proxy=http://127.0.0.1:1080
https-proxy=http://127.0.0.1:1080
strict-ssl=false
```
atom用户目录
windows下为 C:\Users\{登录用户}\.atom
linux mac为 ~/.atom

上面的步骤都完了之后，点击菜单 PlatformIO / Build之后IDE就会自动构建，成功后构建窗口有提示。
点击菜单 Platform / Upload，IDE就会自动上传固件到时钟里面并运行。<br>
自此，请发挥你的想象里，随意的改固件吧！<br>
如果会用git的话，欢迎pull request!!<br>

# 呃，外壳问题。。。
好吧，既然你问到了，那我就说下。<br>
原计划是准备做个外壳的，用白底透光的亚克力做面板，显示效果会上一个档次（参见小米体重称）。<br>
但是，但是。。我不会做3d设计啊。。<br>
而且纯PCB放在桌上，很酷，不是吗<br>
还有个比较严重的问题，，我没有留固定孔。。<br>
不是我不留啊，是因为这个板子太小了，实在是没空间了哇。。喂，有话好好说嘛~<br>
好吧，既然你们强烈要求，我可能有时间就搞个外壳，只是可能啊。因为学新东西太花时间了，而且我要上班啊，摔~ <br>


# 看到这里，说明你对这个项目真的很感兴趣，是吧
欢迎大神们小白们加QQ群 `154344435`一起玩硬件吧。<br>
我是软件工程师，硬件就是小白，哈哈。<br>
下一个项目计划中，准备玩玩远程采集图片，温湿度信息，不过会采用STM32方案。一样的，会全部开源。<br>

# 最后一点，真的是最后一点了，版权说明
本时钟是基于apache Lisence 2.0 开源协议发布，允许商业使用或修改包括源代码和PCB，而无需经过我的授权。<br>
但是请保留署名作者的权利。<br>
如果在商业使用了本时钟的任何源代码和PCB内容，恕不提供技术支持，抱歉。<br>
但如果能告知我使用了我的设计，我会感到很高兴的。<br>

solosky 作品，于2016年秋
 
