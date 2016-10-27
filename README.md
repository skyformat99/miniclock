# MINI CLOCK - 一个小巧漂亮的点阵时钟

标签（空格分隔）： 未分类

---

[图片系列]


# 特色

 1. 显示时间，日期，温度，湿度
 2. 时钟使用DS3231芯片，精度可以达一年误差30秒，无需校准
 3. 掉电仍走时，再次插电无需重新设置
 4. 支持DHT11/DHT22系列温湿度传感器，最高精度0.5℃
 5. 背光自动调节
 6. 支持两种经典字体
 7. 毫无特色的闹钟功能（待实现）
 8. MicroUSB电源接口，可以插USB提供电源
 9. 基于arduino，开放源代码，可以个性化定制

# BOM单

 - ATMEGA328p LQFP32（主MCU芯片） x1
 - CH340G （串口转USB编程芯片，如不改固件可不焊接） x1
 - DS3231N （高精度时钟芯片） x1
 - TM1640 （LED显示芯片） x2
 - 7x11白色点阵 （可以点这里购买） x2
 - MicroUSB座子 x1
 - 贴片微动开关 x4
 - 0805 贴片LED （黄绿色，电源指示灯） x1
 - 0805 0.1uF 贴片电容 若干
 - 1208 100uF 钽电容 x3
 - 0805 1K 贴片电阻 x若干
 - 0805 10K 贴片电阻 x若干
 - 0805 100mA 自恢复熔丝 x1
 - 12MHz 49S贴片晶振 x1
 - 16MHz 49s贴片晶振 x1
 - DHT11/DHT22 （温湿度芯片）x1
 - 有源蜂鸣器 x1
 - CR2205电池座 x1
 - CR2205电池 x1
 - 光敏电阻 x1
 - 2.54mm间距的军品孔 （便于拆芯片，可选） x3

# 操作说明

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


# 焊接说明

特别提醒：由于全是贴片原件，请焊接新手先联系一段时间的贴片焊接再组装这个电路板。

 - 建议焊接一个芯片就检查功能是否正常。
 - MicroUSB座子特别不好焊接（主要是焊盘太小了，本来想加长焊盘的，可是发现板子太小，实在是没有空间了），建议的焊接方式是，用蹄型烙铁，蘸松香，挂很少的锡，轻轻的接触下MicroUSB内部的连接点即可。焊接完了用万用表检查是否有短路，如果没有短路再焊接下一个芯片；
 - DHT11和LED点阵均使用军品孔连接，这个主要是为了测试方便取消，如果没有也可以直接焊接元件，前提是对自己焊工很自信才行（不然如果没有风枪的话，拆下来巨麻烦）
 - 蜂鸣器和电池座注意焊接的方向

# 初次刷固件说明
首先需要焊接好ISP座子，然后你需要一个ATMEL的USBISP编程器，如下图（如果没有可以求助马云家的）。

[编程器图片]
1. 按照下图用杜邦线连接 时钟和编程器。
[ISP连接图片]
2. 下载 USB Prog编程软件，运行主程序。
3. 点击RD，如果下面提示框中提示读出芯片ID成功，则表示线连接正确，可以写入固件。
4. 点击熔丝位设置，分别设置如下值，然后点击写入。
[熔丝位设置图片]
```
low_fuses=0xFF
high_fuses=0xDA
extended_fuses=0x05
```
5. 下载最新版本固件，然后点击文件/调入Flash，选择最新版的固件，点击打开。
6. 点击菜单，命令/写入Flash，稍等片刻即可刷入最新固件。

一些提示：

 - build文件夹有个beep_with_bootloader.hex，可以首先刷入这个固件来测试，如果写入成功，蜂鸣器会以间隔一秒的时间蜂鸣；
 - 如果写入提示成功，但是硬件没有反应，建议在刷机软件中点击擦除按钮后重新刷入固件再试。

# 给想改固件的童鞋说明


### 如果要改固件，有几个前提：

1. 你需要按照上面初次刷固件的说明，成功的刷入完整的固件，或者测试固件beep_with_bootloader.hex。
2. 焊接好CH340G和周边电路。
3. 安装好CH340G驱动
4. 插上MicroUSB后，打开设备管理器，Ports(COM /LPT)节点下能出现一个USB Serial CH340G的串口。

### 如果上面条件都满足了，并且你有足够的C语言基础，那么大胆的去改固件吧。

虽然这个固件是基于arduino的设计的，由于官方的arduino的开发软件太难用（我感觉是我用过的最难用的IDE），这里强烈推荐另外一个替代软件，PlatformIO。

1. 首先从官网下载PlatformIO，官网在此  http://platformio.org/。
2. 使用git或者github下载全部的源码。
3. 打开platformIO，菜单选择 File / Open Folder，选择源码中的fw目录。
4. 菜单选择 PlatformIO / Initialize or Update PlatformIO Project..
5. Board选择Arduino Uno，点击Process初始化项目。

这一步可能比较慢，需要下载avr系列toolchain，如果有翻墙的工具建议设置下PlatformIO的代理。
设置代理的方式比较简单，在atom用户目录下，新建.apmrc文件，里面写入如下内容（注意改成你的代理IP），保存重开即可。

```text
http-proxy=http://127.0.0.1:1080
https-proxy=http://127.0.0.1:1080
strict-ssl=false
```
atom用户目录
windows下为 C:\Users\{登录用户}\.atom
linux mac为 ~/.atom

上面的步骤都完了之后，点击菜单 PlatformIO / Build之后IDE就会自动构建，成功后构建窗口有提示。
点击菜单 Platform / Upload，IDE就会自动上传固件到时钟里面并运行。
自此，请发挥你的想象里，随意的改固件吧！
如果会用git的话，欢迎pull request!!


solosky 作品，于2016年秋
