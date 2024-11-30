# Teamfight Tactics

> [!TIP]
> 抵制不良游戏 拒绝盗版游戏 注意自我保护 谨防受骗上当
>
> 适度游戏益脑 沉迷游戏伤身 合理安排时间 享受健康生活

## 项目名称

Teamfight_Tactics

## 项目简介

A project of Teamfight Tactics based on [Cocos2d-x 3.17.2](https://docs.cocos.com/cocos2d-x/manual).

基于 [Cocos2d-x 3.17.2](https://docs.cocos.com/cocos2d-x/manual) 开发的金铲铲之战游戏项目。

> ***Relevant course***
> * Programing Paradigm 2023 (2023年同济大学程序设计范式)

This project is a Teamfight Tactics game developed based on [Cocos2d-x 3.17.2](https://docs.cocos.com/cocos2d-x/manual), inspired by games such as "Dota Auto Chess". It boasts a wealth of basic features, including captivating initial and settings interfaces, background music, a variety of cards and their upgrade systems, movement for tiny heroes, and in-game cards with red and blue health bars that can unleash abilities when the blue bar is full. Moreover, the game supports room creation and joining, offers practice mode and online gameplay, allowing players to compete against AI or other human players. The project also expands on multiple synergy enhancement functions and a strengthened rune system, along with sound effects during combat, providing a more rich and immersive gaming experience.

该项目是一个基于 [Cocos2d-x 3.17.2](https://docs.cocos.com/cocos2d-x/manual) 开发的金铲铲之战游戏，灵感来自于《Dota 自走棋》《云顶之弈》《金铲铲之战》等游戏。游戏拥有丰富的基础功能，如具有引人入胜的初始和设置界面、背景音效、多种卡牌及其升级系统、小小英雄的移动以及带有红蓝血条的场上卡牌，卡牌蓝条满时还能释放技能。此外，游戏支持创建和加入房间，提供练习模式和联机对弈，允许玩家与AI或其他人类玩家进行游戏。项目还扩展了多种羁绊的加强功能和强化符文系统，以及战斗中的音效，为玩家带来更加丰富和沉浸式的游戏体验。

## 成员分工

| 姓名 | 学号 | 分工 |
| :---: | :---: | :---: |
| 林继申 (组长) | 2250758 | **项目后端工作统筹** <br> 项目任务分工 <br> 代码审查 <br> 项目框架搭建 <br> 网络环境搭建 <br> 练习模式与联机模式 <br> `AppDelegate` 类 <br> `Battle` 类 <br> `HoverButton` 类 <br> `Champion` 类 <br> `Control` 类及其派生类 <br> `ChampionAttributesLayer` 类 <br> `PlacementMarkerLayer` 类 <br> `ScoreBoardLayer` 类 <br> `LocationMap` 类 <br> `Player` 类及其派生类 <br> `Scene` 类及其派生类 <br> `Server` 类 |
| 刘淑仪 | 2251730 | **项目前端工作统筹** <br> 练习模式与联机模式 <br> `Champion` 类 <br> `ChampionAttributesLayer` 类 <br> `PlacementMarkerLayer` 类 <br> `ScoreBoardLayer` 类 <br> `Scene` 类及其派生类 <br> 图标绘制 <br> 按钮绘制 <br> 战斗英雄与小小英雄绘制 <br> 图像元素绘制 <br> 场景绘制 <br> 音频引擎 <br> 背景音乐与音效 |
| 杨兆镇 | 2252712 | **项目 AI 玩家算法统筹** <br> 练习模式 <br> `Player` 类及其派生的 `AIPlayer` 类 |
| 杨宇琨 | 2252843 | **项目测试统筹** <br> 练习模式与联机模式 <br> `Battle` 类 <br> `Champion` 类 <br> `OfflineModeControl` 类 <br> `HumanPlayer` 类 <br> `OfflineModeBattleScene` 类 <br> `OnlineModeBattleScene` 类 <br> 战斗英雄绘制 <br> 项目答辩 PPT 制作 |

## 成员贡献

| 姓名 | 学号 | 代码行数 | 工作量 |
| :---: | :---: | :---: | :---: |
| 林继申 (组长) | 2250758 | 5082 | 35% |
| 刘淑仪 | 2251730 | 1385 | 25% |
| 杨兆镇 | 2252712 | 467 | 15% |
| 杨宇琨 | 2252843 | 2282 | 25% |

```
git log --format='%aN' | sort -u | while read name; do echo -en "$name\t"; git log --author="$name" --pretty=tformat: --numstat | awk '{ add += $1; subs += $2; loc += $1 - $2 } END { printf "added lines: %s, removed lines: %s, total lines: %s\n", add, subs, loc }' -; done
```

## 项目组成

* `/Classes`
类定义与类实现

* `/Resources`
资源文件

* `/Server`
服务器程序

* `/cocos2d`
依赖文件

* `/proj.win32`
游戏程序

* `Documentation.md`
项目实现功能与项目技术细节文档

* `Project_Defense.pptx`
项目答辩汇报

## 项目开发日志

### 2023/11/22

* Python 2.7.10 环境配置
* CMake 3.28.0 环境配置
* Cocos2d-x 4.0 环境配置

### 2023/11/23

* 明确团队项目代码规范
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
* 实现 `AppDelegate` 类

### 2023/12/10

* 初步搭建 socket 网络环境

### 2023/12/11

* 基本搭建 socket 网络环境
* 基本实现 `Server` 类

### 2023/12/12

* 基本确定团队成员分工
* 基本搭建项目框架
* 实现 `HoverButton` 类
* 实现 `GBKToUTF8` 类

### 2023/12/16

* 绘制图标

### 2023/12/17

* 初步实现商店功能

### 2023/12/18

* 完善初始场景背景图与细节
* 实现 `Champion` 类的鼠标事件监听功能

### 2023/12/19

* 完善项目框架
* 初步实现 `Champion` 类
* 初步实现 `OfflineModeControl` 类
* 初步实现 `Player` 类
* 初步实现 `HumanPlayer` 类
* 实现 `InitialScene` 类与交互细节
* 实现 `LocationMap` 类

### 2023/12/20

* 调整 `Resources 文件夹`
* 调整 `GBKToUTF8` 类
* 调整 `LocationMap` 类
* 实现 `StartupScene` 类与交互细节
* 实现 `MenuScene` 类与交互细节
* 初步实现 `OfflineModePreparationScene` 类与交互细节
* 初步实现 `Battle` 类
* 确定战斗英雄属性参数
* 完成战斗英雄绘制

### 2023/12/22

* 初步实现 `ChampionAttributesLayer` 类

### 2023/12/23

* 实现 `ChampionAttributesLayer` 类
* 实现 `PlacementMarkerLayer` 类
* 绘制商店相关按钮
* 基本实现 `HumanPlayer` 类
* 基本实现 `OfflineModePreparationScene` 类与交互细节

### 2023/12/24

* 实现金币系统
* 调整命名空间
* 实现 `OfflineModePreparationScene` 类与交互细节

### 2023/12/25

* 实现 `Battle` 类
* 实现 `Champion` 类
* 实现 `OfflineModeBattleScene` 类
* 实现 `OfflineModeControl` 类
* 实现 `ScoreBoardLayer` 类
* 工作对接与项目仓库整合
* 基本实现练习模式

### 2023/12/26

* 实现 `Control` 类
* 实现生命条与经验条效果
* 实现武器动画效果

### 2023/12/27

* 完善游戏功能性与平衡性
* 实现商店推荐算法
* 实现 AI 落子算法
* 实现 `Player` 类
* 实现 `AIPlayer` 类
* 实现 `HumanPlayer` 类
* 工作对接与项目仓库整合
* 实现练习模式

### 2023/12/28

* 完善商店推荐算法
* 完善 AI 落子算法
* 基本实现 `OnlineModeMenuScene` 类与交互细节

### 2023/12/29

* 初步实现 `OnlineModeControl` 类
* 初步实现 `OnlineModePreparationScene` 类与交互细节
* 初步实现 `OnlineModeBattleScene` 类与交互细节
* 实现 `SelectionScene` 类与交互细节
* 实现 `SettingsScene` 类与交互细节
* 初步实现联机模式
* 实现小小英雄移动功能
* 实现羁绊系统

### 2023/12/30

* 弃用 `GBKToUTF8` 类
* 基本实现 `OnlineModeControl` 类
* 基本实现 `OnlineModePreparationScene` 类与交互细节
* 基本实现 `OnlineModeBattleScene` 类与交互细节
* 实现 `OfflineModeRuneScene` 类与交互细节
* 基本实现联机模式
* 实现音频引擎
* 实现天赋符文系统

### 2023/12/31

* 调整 `Resources 文件夹`
* 实现 `OnlineModeControl` 类
* 实现 `OnlineModePreparationScene` 类与交互细节
* 实现 `OnlineModeBattleScene` 类与交互细节
* 实现 `OnlineModeMenuScene` 类与交互细节
* 实现 `ReferenceScene` 类与交互细节
* 实现 `Server` 类
* 实现联机模式
* 游戏功能性与平衡性测试
* 项目收尾工作

### 2024/1/1

* 完善项目自述文档 `README.md`
* [Project Defense Slides](Project_Defense.pptx) 制作

### 2024/1/2

* 答辩验收

## 集成开发环境

* Microsoft Visual Studio 2022

## 编译运行环境

* 本项目仅适用于x86架构

## 免责声明

The code and materials contained in this repository are intended for personal learning and research purposes only and may not be used for any commercial purposes. Other users who download or refer to the content of this repository must strictly adhere to the **principles of academic integrity** and must not use these materials for any form of homework submission or other actions that may violate academic honesty. I am not responsible for any direct or indirect consequences arising from the improper use of the contents of this repository. Please ensure that your actions comply with the regulations of your school or institution, as well as applicable laws and regulations, before using this content. If you have any questions, please contact me via [email](mailto:minmuslin@outlook.com).

本仓库包含的代码和资料仅用于个人学习和研究目的，不得用于任何商业用途。请其他用户在下载或参考本仓库内容时，严格遵守**学术诚信原则**，不得将这些资料用于任何形式的作业提交或其他可能违反学术诚信的行为。本人对因不恰当使用仓库内容导致的任何直接或间接后果不承担责任。请在使用前务必确保您的行为符合所在学校或机构的规定，以及适用的法律法规。如有任何问题，请通过[电子邮件](mailto:minmuslin@outlook.com)与我联系。

## 文档更新日期

2024年12月1日