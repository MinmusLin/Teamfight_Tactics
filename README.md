# Teamfight Tactics

## 项目名称

Teamfight_Tactics

## 项目简介

A project of Teamfight Tactics.
金铲铲之战游戏项目。

> Relevant course
> * Programing Paradigm (同济大学程序设计范式)

## 成员分工

| 姓名 | 学号 | 分工 |
| :---: | :---: | :---: |
| 林继申 (组长) | 2250758 | 项目统筹与任务分工 <br> 代码审查 <br> 项目框架搭建 <br> 网络环境搭建 <br> 练习模式与联机模式 <br> `Server` 类 <br> `HoverButton` 类 <br> `Champion` 类 <br> `Control` 类及其派生类 <br> `Player` 类及其派生类 <br> `Scene` 类及其派生类 <br> `GBKtoUTF8` 单例 <br> `LocationMap` 单例 <br> 进度条绘制 |
| 刘淑仪 | 2251730 | 练习模式 <br> `HumanPlayer` 类 <br> 图表绘制 <br> 场景绘制 <br> 按钮绘制 |
| 杨兆镇 | 2252712 | 练习模式 <br> `AIPlayer` 类 |
| 杨宇琨 | 2252843 | 练习模式 <br> `Battle` 类 <br> 战斗英雄绘制 |

## 项目开发日志

### 2023/11/22

* Python 2.7.10 环境配置
* CMake 3.28.0 环境配置
* Cocos2d-x 4.0 环境配置

### 2023/11/23

* 明确项目代码规范
* Markdown 语言掌握

### 2023/11/24

* 学习 Cocos2d-x

### 2023/11/29

* 项目托管 GitHub [仓库](https://github.com/MinmusLin/Teamfight_Tactics)

### 2023/12/3

* git 工具掌握
* GitHub Desktop 工具掌握
* 明确项目 git 提交规范
* 放弃 Cocos2d-x 4.0 环境，配置 Cocos2d-x 3.17.2 环境
* 编译 Cocos2d-x 3.17.2 测试项目

### 2023/12/4

* 明确项目仓库组成
* Boost 网络环境配置

### 2023/12/8

* 初步确定团队成员分工

### 2023/12/9

* 放弃 Boost 网络环境，配置 socket 网络环境
* 初步搭建项目框架

### 2023/12/10

* 初步搭建 socket 网络环境

### 2023/12/11

* 基本搭建 socket 网络环境

### 2023/12/12

* 基本确定团队成员分工
* 基本搭建项目框架
* 实现 `HoverButton` 类

### 2023/12/17

* 初步实现商店功能

### 2023/12/18

* 完善初始场景背景图与细节
* 实现 `Champion` 类的鼠标事件监听

### 2023/12/19

* 完善项目框架
  * 初步实现 `Champion` 类
  * 初步实现 `OfflineModeControl` 类
  * 初步实现 `Player` 类
  * 初步实现 `HumanPlayer` 类
* 实现 `InitialScene` 类与交互细节

### 2023/12/20

* 调整 `Resources 文件夹`
* 调整 `GBKToUTF8` 单例
* 调整 `LocationMap` 单例
* 实现 `StartupScene` 类与交互细节
* 实现 `MenuScene` 类与交互细节

* 今日计划：
  * 晚21:00通达馆。**加粗部分在晚24:00之前必须完成**
  * 所有人同步最新仓库内容，记得对自己之前写的代码做备份。
  * yyk：**15个英雄参数（5个1星、2星、3星，分别给予标识符ABCDE...具体逻辑晚上再议，主要是参数）**，**15个战斗英雄贴图（像素40*40）圆形外透明**，battle类对战逻辑
  * yzz：商店推荐算法（接口晚上说）、AI落棋算法
  * lsy：英雄属性显示label
  * ljs：**离线模式控制类**

## 集成开发环境

* Microsoft Visual Studio 2022

## 编译运行环境

* 本项目仅适用于x86架构

## 库依赖

* `Cocos2d-x 3.17.2`

## 相关资料

* [Cocos2d-x 3.x Documentation](https://docs.cocos.com/cocos2d-x/manual)

## 文档更新日期

2023年12月20日