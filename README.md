# Teamfight Tactics

## 项目名称

Teamfight_Tactics

## 项目简介

A project of Teamfight Tactics based on [Cocos2d-x 3.17.2](https://docs.cocos.com/cocos2d-x/manual).

基于 [Cocos2d-x 3.17.2](https://docs.cocos.com/cocos2d-x/manual) 开发的金铲铲之战游戏项目。

参考游戏：《Dota 自走棋》《云顶之弈》《金铲铲之战》

> Relevant course
> * Programing Paradigm (同济大学程序设计范式)

## 成员分工

| 姓名 | 学号 | 分工 |
| :---: | :---: | :---: |
| 林继申 (组长) | 2250758 | **项目后端工作统筹** <br> 项目任务分工 <br> 代码审查 <br> 项目框架搭建 <br> 网络环境搭建 <br> 练习模式与联机模式 <br> `AppDelegate` 类 <br> `Battle` 类 <br> `HoverButton` 类 <br> `Champion` 类 <br> `Control` 类及其派生类 <br> `ChampionAttributesLayer` 类 <br> `PlacementMarkerLayer` 类 <br> `ScoreBoardLayer` 类 <br> `LocationMap` 类 <br> `Player` 类及其派生类 <br> `Scene` 类及其派生类 <br> `Server` 类 |
| 刘淑仪 | 2251730 | **项目前端工作统筹** <br> 练习模式与联机模式 <br> `Champion` 类 <br> `ChampionAttributesLayer` 类 <br> `PlacementMarkerLayer` 类 <br> `ScoreBoardLayer` 类 <br> `Scene` 类及其派生类 <br> 图标绘制 <br> 按钮绘制 <br> 战斗英雄与小小英雄绘制 <br> 图像元素绘制 <br> 场景绘制 <br> 音频引擎 <br> 背景音乐与音效 |
| 杨兆镇 | 2252712 | **项目 AI 玩家算法统筹** <br> 练习模式 <br> `Player` 类及其派生的 `AIPlayer` 类 |
| 杨宇琨 | 2252843 | **项目测试统筹** <br> 练习模式与联机模式 <br> `Battle` 类 <br> `Champion` 类 <br> `OfflineModeControl` 类 <br> `HumanPlayer` 类 <br> `OfflineModeBattleScene` 类 <br> `OnlineModeBattleScene` 类 <br> 战斗英雄绘制 |

## 成员贡献

| 姓名 | 学号 | 代码行数 | 工作量 |
| :---: | :---: | :---: | :---: |
| 林继申 (组长) | 2250758 | 4710 | 35% |
| 刘淑仪 | 2251730 | 1385 | 25% |
| 杨兆镇 | 2252712 | 467 | 15% |
| 杨宇琨 | 2252843 | 2282 | 25% |

```
git log --format='%aN' | sort -u | while read name; do echo -en "$name\t"; git log --author="$name" --pretty=tformat: --numstat | awk '{ add += $1; subs += $2; loc += $1 - $2 } END { printf "added lines: %s, removed lines: %s, total lines: %s\n", add, subs, loc }' -; done
```

## 项目实现功能

### 基础功能

* [X] 有初始界面和设置界面
* [X] 支持背景音效
* [X] 支持多种类型的卡牌
* [X] 支持卡牌升级功能
* [X] 支持小小英雄的移动
* [X] 场上卡牌支持红蓝血条，蓝条满时可以释放技能
* [X] 支持创建房间和加入房间功能
* [X] 支持练习模式，玩家可以和 N 个 AI 玩家对弈，**N ≥ 2**
* [X] 支持联机模式，玩家可以和 N 个人类玩家联机对弈，**N ≥ 2**

### 拓展功能

* [x] 支持多种羁绊的加强功能
* [X] 支持强化符文系统
* [X] 支持战斗中的音效

### 加分项

* 版本控制和团队协作

  * [x] 合理使用 Git 控制版本，将项目开源至 Github
  * [x] 团队成员分工合理平等

* 代码质量和安全

  * [x] 使用单元测试保证代码质量
  * [x] 合理地抛出异常和处理

* 功能和架构

  * [x] 界面精美
  * [x] 项目目录结构清晰

* 其他

  * [x] 没有内存泄露
  * [x] 程序运行过程不会发生崩溃情况
  * [x] 尽可能多地使用了 C++11 特性
  * [x] 优秀的商店推荐算法和 AI 落棋算法
  * [x] 规范统一的代码风格

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

## 集成开发环境

* Microsoft Visual Studio 2022

## 编译运行环境

* 本项目仅适用于x86架构

## 文档更新日期

2023年1月2日