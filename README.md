# 智能花盆  
## 一.项目简介
本项目是利用寒假时间做的一个练手项目，目的是学习vscode+platformio ESP32开发，嵌入式GUI框架LVGL的移植和使用。platformio IDE具有编译速度快、结构清晰等特点。
## 二.开源链接
演示视频:  https://www.bilibili.com/video/BV1ZU4y1Z7sd?spm_id_from=333.999.0.0
  
hardware文件夹中有原理图的pdf和pcb的gerber文件以及外壳stl文件  
  
software文件夹的lib文件夹为空，需要自行导入对应版本的库文件  
  
库文件:  
· ArduinoJson  6.19.1  
· lvgl8  
· TFT_eSPI
## 三.开发环境
1.vscode+platformio ESP32开发  
  
2.vs2019 lvgl模拟器 GUI界面设计与仿真  
  
3.solidworks 2021 外壳设计  
  
4.立创eda pcb设计  
  
## 四.功能展示
图1 主板正面  
![主板正面](https://s4.ax1x.com/2022/02/27/bn4HHS.jpg)  
图2 主板背面  
![主板背面](https://s4.ax1x.com/2022/02/27/bn5jaD.jpg)  
图3 无线充电座内部  
![无线充电座内部](https://s4.ax1x.com/2022/02/27/bnIisP.jpg)  
图4 整体外观正面  
![整体外观正面](https://s4.ax1x.com/2022/02/27/bnIAZ8.jpg)  
图5 整体外观背面  
![整体外观背面](https://s4.ax1x.com/2022/02/27/bnIMMq.jpg)  
图6 主页面  
![主页面](https://s4.ax1x.com/2022/02/27/bnI3ZT.jpg)  
图7  光照强度页面
![光照强度页面](https://s4.ax1x.com/2022/02/27/bnI8dU.jpg)  
图8 土壤湿度页面  
![土壤湿度页面](https://s4.ax1x.com/2022/02/27/bnItJJ.jpg)  
图9 亮度调节页面  
![亮度调节页面](https://s4.ax1x.com/2022/02/27/bnIwsx.jpg)  
## 五.技术详情  
1.天气温度等api由心知天气提供  
  
2.时间api由网上大佬提供  
  
3.光照强度由光敏电阻测得  
  
4.土壤湿度是我取出土壤湿度模块前端的金属片得到的  
  
5.屏幕亮度通过P波配合mos管调节tft屏幕背光端电压实现  
  
6.无线充电采用优信5V1A模块实现  
  
7.本页面的图片来自于路过图床  
  
## 六.项目的不足  
无线充电解决方案由于外壳的阻隔距离，充电效果只能耗电速度持平。只有使用背部typec才能充上电。  
  
获取时间的api有时不稳定，存在获取失败的情况  
  
代码中移植了文件系统，pcb也预留了SD卡槽，但为了实现流畅的动画效果，所有的图片都是以C文件的形式存储进内部RAM(520kB)中。  
  
由于时间问题项目没有实现蓝牙和扫码配网功能，各种页面也有待开发  
  
本项目部分参考了FranHawk和稚晖君的资料，十分感谢！
