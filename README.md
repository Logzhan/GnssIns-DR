# 组合导航-行人航位推算

更新：2022-09-20，增加坐标系转换函数支持

原理：利用IMU计算行人以及方向融合GNSS的方向，采用EKF进行融合滤波得到最优的位置估计。

## 一、概述

​		由于保密原因、公开代码采用更新的架构进行重新设计和重新复现，尽可能利Github公开代码完成设计。持续复现重构中。

​		计步器复现仓库：https://github.com/Logzhan/Pedometer	

​	PDR算法的架构设计如下图所示：

<img src="./4.Image/PDR算法架构设计.png" style="zoom:38%;" />

## 二、效果比较（旧版PDR  vs 手机GNSS）

手机原始输出位置：

![](./4.Image/Gnss-Image(1).png)

Gnss融合输出位置：

![](./4.Image/GnssIns-Image(1).png)

手机原始输出位置：

![](./4.Image/Gnss-Image(2).png)

Gnss融合输出位置：

![](./4.Image/GnssIns-Image(2).png)

## 三、更新日志

2022-09-08 ： 创建仓库、添加仿真结果

2022-09-10 ： 更新新版PDR算法架构设计, 创建Visual Studio 工程

2022-09-14 ：添加矩阵计算库