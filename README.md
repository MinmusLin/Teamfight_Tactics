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
| 杨宇琨 | 2252843 | **项目测试统筹** <br> 练习模式与联机模式 <br> `Battle` 类 <br> `Champion` 类 <br> `OfflineModeControl` 类 <br> `HumanPlayer` 类 <br> `OfflineModeBattleScene` 类 <br> `OnlineModeBattleScene` 类 <br> 战斗英雄绘制 <br> 答辩 PPT 制作 |

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

## 项目实现功能与项目技术细节

### 基础功能

* [X] 有初始界面和设置界面
* [X] 支持背景音效
* [X] 支持多种类型的卡牌
* [X] 支持卡牌升级功能
* [X] 支持小小英雄的移动
* [X] 场上卡牌支持红蓝血条，蓝条满时可以释放技能
* [X] 支持创建房间和加入房间功能
* [X] 支持练习模式，玩家可以和 N 个 AI 玩家对弈，N ≥ 2
* [X] 支持联机模式，玩家可以和 N 个人类玩家联机对弈，N ≥ 2

### 拓展功能

* [x] 支持多种羁绊的加强功能
* [X] 支持强化符文系统
* [X] 支持战斗中的音效

### 加分项

* 版本控制和团队协作

  * [x] 合理使用 Git 控制版本，将项目开源至 Github

    项目托管 GitHub [仓库](https://github.com/MinmusLin/Teamfight_Tactics)

  * [x] 团队成员分工合理平等

    本项目依据团队每个成员所擅长的领域，进行了合理与平等的分工。

* 代码质量和安全

  * [x] 使用单元测试保证代码质量

    单元测试是软件开发中的一种测试方法，用于验证代码中最小的可测试单元（如函数、方法、类等）的行为是否符合预期。它的目标是对每个独立的代码单元进行测试，确保其在各种情况下都能按照预期工作。

    以下是单元测试的一些重要概念和特点：

    * 目的

      1. 验证代码逻辑：确保代码按照预期工作。
      1. 提供反馈：及早发现潜在问题并提供反馈，有助于迅速解决问题。
      1. 支持重构：确保在重构代码后，其行为不受影响。

    * 特点

      1. 独立性：单元测试应该是相互独立的，一个测试用例的失败不应该影响其他测试用例。
      1. 自动化：应该能够自动运行测试用例，这样可以随时重复执行，并且可以集成到持续集成（CI）工具中。
      1. 快速：单元测试应该快速执行，因为它们只针对单个小单元，执行速度通常很快。

    * 流程

      1. 编写测试用例：为要测试的每个函数或类编写测试用例，包括对输入和预期输出的定义。
      1. 运行测试：运行测试套件，检查是否有测试失败。
      1. 分析结果：分析失败的测试用例，并找出导致问题的原因。
      1. 修复问题：修复代码中的问题并再次运行测试，确保问题已解决。
      1. 重复执行：在代码更改后，再次运行测试，确保修复问题不引入新问题。

    * 好处

      1. 提高代码质量：可靠的单元测试确保代码按照预期工作，减少 Bug。
      1. 支持重构：提供一种安全的修改代码的方式，因为有了测试用例作为保障。
      1. 加速开发流程：可以快速发现问题并在早期修复，提高开发效率。

    综上所述，单元测试是一种重要的软件开发实践，有助于确保代码的稳定性、可靠性和可维护性。通过测试每个独立的代码单元，开发者能够更有信心地构建高质量的软件系统。

  * [x] 合理地抛出异常和处理

    `Try-Catch` 是一种异常处理机制，用于在程序中捕获和处理可能发生的异常或错误。在使用 `Try-Catch` 结构时，代码块被放置在一个 `Try` 块中，该块用于包含可能会抛出异常的代码。如果在 `Try` 块中发生异常，程序会立即跳转到对应的 `Catch` 块，这样就可以执行特定的异常处理代码，而不会导致程序崩溃。

    * `Try` 块：包含可能会抛出异常的代码段。

      ```cpp
      try { championMap[i][j] = new Champion(championCategoryMap[i][j]); }
      ```

    * `Catch` 块：针对不同类型的异常进行捕获和处理。可以有多个 `Catch` 块，每个块处理特定类型的异常。

      ```cpp
      catch (const std::bad_alloc& e) {
          std::cerr << "Memory allocation failed: " << e.what() << std::endl;
          throw;
      }
      ```

    * 程序中出现的 `Try-Catch` 模块

      ```cpp
      try {
          waitingChampion[pos] = new Champion(newChampion);
      };
      catch (const std::bad_alloc& e) {
          std::cerr << "Memory allocation failed: " << e.what() << std::endl;
          throw;
      }
      ```

      在尝试为新的升级英雄创建 `Champion` 对象时，使用 `new Champion` 来分配内存。如果内存分配失败，会抛出 `std::bad_alloc` 异常。使用 `try-catch` 块来捕获 `std::bad_alloc` 异常。如果发生内存分配异常，程序会输出错误消息，然后重新抛出异常（ `throw` ），可能会由上层代码进行进一步处理或者中止程序。

      ```cpp
      try {
          g_offlineModeControl = new OfflineModeControl;
      }
      catch (const std::bad_alloc& e) {
          std::cerr << "Memory allocation failed: " << e.what() << std::endl;
          throw;
      }
      ```

      `try` 块中的代码尝试使用 `new` 运算符在堆上分配内存来创建 `OfflineModeControl` 类的对象，并将其赋值给名为 `g_offlineModeControl` 的指针或对象。如果内存分配失败，即抛出 `std::bad_alloc` 异常， `catch` 块中的代码将捕获这个异常。 `catch` 块中的代码负责处理这个异常。它首先输出一条错误消息，指示内存分配失败，并显示异常对象的描述信息（通过 `e.what()` 获取异常的具体信息）。接着使用 `throw` 重新抛出捕获到的异常。这将导致程序在没有处理该异常的情况下将异常向上层代码传递，可能由上层代码进行进一步的处理或导致程序中止。

      ```cpp
      try {
          humanPlayer = new HumanPlayer(g_PlayerName);
          enemyPlayer = new AIPlayer(u8"AI玩家", g_difficulty);
      }
      catch (const std::bad_alloc& e) {
          std::cerr << "Memory allocation failed: " << e.what() << std::endl;
          if (humanPlayer) {
              delete humanPlayer;
          }
          if (enemyPlayer) {
              delete enemyPlayer;
          }
          throw;
      }
      ```

      `try` 块中的代码尝试使用 `new` 运算符在堆上分配内存以创建 `HumanPlayer` 和 `AIPlayer` 类的对象。其中 `humanPlayer` 和 `enemyPlayer` 是相应对象的指针或对象。如果内存分配失败（抛出 `std::bad_alloc` 异常）， `catch` 块中的代码将捕获到这个异常。 `catch` 块中的处理过程：输出一条错误消息，指示内存分配失败，并显示异常对象的描述信息（通过 `e.what()` 获取异常的具体信息）。进行清理工作：检查 `humanPlayer` 和 `enemyPlayer` 是否已经被分配内存。如果它们指向已分配的内存，就使用 `delete` 运算符释放它们占用的内存空间。这样做是为了避免内存泄漏，在内存分配失败后，即使其中一个对象成功分配内存，也要确保释放之前成功分配的对象内存。最后，重新抛出捕获到的异常（ `throw` ）。这将导致程序将异常传递给更高级别的代码，可能会进行进一步的处理或导致程序中止。

* 功能和架构

  * [x] 界面精美

    * 界面 UI 设计

      * 页面设计

        本项目根据场景切换一共设计了 10 个场景，分别为初始场景（InitialScene）、菜单场景（MenuScene）、离线模式准备 / 战斗场景（OfflineModePreparation / BattleScene）、离线模式符文选择场景（OfflineModeRuneScene）、联机模式菜单场景（OnlineModeMenuScene）、游戏说明场景（ReferenceScene）、选择小小英雄场景（SelectionScene）、设置场景（SettingsScene）、初始化加载场景（StartupScene）。

      * 按钮设计

        Cocos2dx 一共给了两个状态的按钮，分别为标准态和激活态。但为了保证画面精美，本项目还设计了按钮的悬浮态，保证鼠标划过的时候按钮会进行一些响应，即所有按钮有 Default、Hover、Active 这三态。在设计按钮时，本项目也考虑了与当前场景色调的一致性，使得画面和谐精美。

        除了基本按钮，本项目也设计了滑动条、进度条以及复选框。它们都是根据当前界面的主色调进行设计，其中滑动条的按钮还设计成了一个铲子。

      * 属性与商店 UI 设计

        英雄的属性显示标签及商店 UI 参考了原游戏，同时为了保证与战斗界面的和谐，对颜色和透明度进行了一定的更改。

    * 图标设计

      * 图标设计

        本游戏共进行了三类图标设计：符文系统图标设计、羁绊图标设计以及武器设计。三种设计均来源于网络资源，根据对应描述进行设计。

      * 英雄图标设计

        本游戏页面参考了腾讯开发的《金铲铲之战》，故英雄的图标从官网截取，并根据画面的和谐，调整了大小与形状。除了战斗英雄，小小英雄也是如此，最终选取了官网小小英雄的绘图设计。

  * [x] 项目目录结构清晰

    本游戏共设有两个项目，分别为服务器项目（ `Server` ）以及游戏项目（ `Teamflight_Tactics` ）。服务器项目即用于实现游戏项目的联机模式。

    本项目根据文件的不同功能，将外界资源和项目源文件进行了分类。所有类都被归置 `Classes` 文件夹，更能直观地管理各类文件；同时将各种资源文件都放置在 `Resources` 文件夹，包括所有图片资源以及音乐资源、字体资源， `proj.win32` 则用于存储解决方案以及程序入口等源文件。

* 其他加分项

  * [x] 没有内存泄露

    动态内存是一种在程序运行时分配和释放的内存空间。与静态内存不同，动态内存的大小和生命周期可以在程序运行期间动态地改变。动态内存的分配和释放是通过使用特定的函数或操作符来完成的。在本程序中，可以通过 `new` 和 `delete` 来分别实现动态内存的分配和删除。动态内存的主要优势是它的灵活性。它允许程序在运行时根据需要动态地分配和释放内存，这对于处理未知数量或大小的数据非常有用。然而，动态内存的管理也需要开发人员负责确保正确地分配和释放内存，以避免内存泄漏和悬挂指针等问题。

    要预防内存泄露，我们可以使用动态指针或者手动保证 `new` 和 `delete` 的严格匹配，有进行动态内存分配的变量就必须有对应的删除操作。我们的项目中采取手动删除动态内存变量，这在我们的项目中有非常多的样例。例如：

    `Battle` 类中，我们对英雄的创建是通过动态内存分配来完成的，我们创建了一个二维指针数组 `championCategoryMap[BATTLE_MAP_ROWS][BATTLE_MAP_COLUMNS]` ，每一个成员都是指向战斗区域地图的英雄实例，所以我们将其都初始化为 `nullptr` ，每创建一个新英雄就令战斗区域相应位置的指针指向英雄的实例。在英雄下场或者游戏结束后就手动 `delete` 这个英雄变量，再改变相应位置的指针指向 `nullptr` 。这样就能保证防止内存泄漏。

    在 `OfflineModeControl` 类中，我们根据人类玩家输入的昵称和AI的难度设定来新建相应的 `Player` 类实例，并使对应的指针指向使用动态内存分配创建的对象。另外还创建了一个对战类，每个此类的对象都代表着一场已经确定的敌我双方的对战，为了防止内存泄漏我们的应对方案是在析构函数中手动删除相应的对象。

    同样的，在 `OnlineModeControl` 类中，我们在构造函数内部同样根据传入的玩家昵称参数建立了相应的 `HumanPlayer` 类的对象，并在下方 `Battle` 对象的创建过程中都使用了动态内存分配。对玩家和战斗实例的创建和确定很大程度上将游戏的核心功能单元化，使得问题的处理变得条理清晰。

    以上是一些本项目中的动态内存分配例子，为了防止内存泄露我们的处方案是在创建的时候通过异常抛出来记录；同时保证在析构函数中一定删除通过动态内存方式创建的对象，这样就完美的解决了内存泄露的问题。

  * [x] 程序运行过程不会发生崩溃情况

    程序对各种可能存在的潜在问题都进行了处理，程序运行过程不会发生崩溃情况。

  * [x] 尽可能多地使用了 C++11 特性

    * 类型推导

      C++11 引入了 `auto` 和 `decltype` 关键字，其允许编译器自动推导变量或表达式的类型，方便开发者编码也简化了代码。
      
      `auto` ：让编译器在编译器就推导出变量的类型，可以通过 `=` 右边的类型推导出变量的类型。

      `decltype` ：相对于 `auto` 用于推导变量类型，而 `decltype` 则用于推导表达式类型，这里只用于编译器分析表达式的类型，表达式实际不会进行运算。

      本项目在复杂数据类型时使用了 `auto` 和 `decltype` 方便创建变量以面对复杂的类型表达式，同时减少由于类型错误造成的 bug，也提高了维护性。使用举例如下：

      ```cpp
      const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
      const auto background = Sprite::create("../Resources/Scenes/OfflineModePreparationScene.png");
      ```

      ```cpp
      std::priority_queue<ChampionCategory, std::vector<ChampionCategory>, decltype(comp)> orderedChampions(comp);
      for (const auto& champion : battleChampions) {
          orderedChampions.push(champion);
      }
      ```

    * 构造函数参数列表初始化

      C++11 引入了列表初始化（也称为统一初始化），这是一种使用花括号 `{ }` 来初始化对象的新语法。它提供了一种更一致、更安全的初始化方式，并且能用于几乎所有类型的初始化，包括基本数据类型、对象、数组以及容器等。使用举例如下：

      ```cpp
      HumanPlayer::HumanPlayer(const std::string nickname) :
          Player(nickname),
          currentScene(nullptr),
          deleteChampionButton(nullptr),
          championAttributesLayer(nullptr),
          placementMarkerLayer(nullptr),
          nearestPlacementMarker(nullptr),
          startLocation({ WaitingArea, -1 }),
          maxBattleChampionCount(BATTLE_AREA_MIN_CHAMPION_COUNT),
          goldCoin(INITIAL_GOLD_COIN)
      {
          std::fill_n(shopChampionCategory, MAX_SELECTABLE_CHAMPION_COUNT, NoChampion);
          std::fill_n(shopChampionButton, MAX_SELECTABLE_CHAMPION_COUNT, nullptr);
          for (int i = 0; i < PLACE_MAP_ROWS; i++) {
              std::fill_n(battleChampion[i], BATTLE_MAP_COLUMNS, nullptr);
          }
          std::fill_n(waitingChampion, WAITING_MAP_COUNT, nullptr);
      }
      ```

    * 基于范围的 `for` 循环

      C++11 引入了基于范围的 `for` 循环（Range-based for loop），这是一种新的循环语法，使得遍历容器（如数组、向量、列表等）和范围变得更加简单和直观。这种循环方式自动迭代容器或范围中的每个元素，无需手动管理迭代器或索引。使用举例如下：

      ```cpp
      for (const auto& map : playerHealthPointsMap) {
          for (const auto& pair : map) {
              healthPointsVec.push_back(pair);
          }
      }
      ...
      for (const auto& pair : healthPointsVec) {
          for (const auto& map : playerNamesMap) {
              auto it = map.find(pair.first);
              if (it != map.end()) {
                  sortedPlayerNames.push_back(it->second);
                  break;
              }
          }
      }
      ```

    * 继承构造函数

      继承构造函数（Inheriting Constructors）是 C++11 标准中引入的一个特性，它允许派生类继承基类的构造函数。这个特性主要解决了在派生类中重复编写与基类构造函数相同的代码的问题，从而提高了代码的可维护性和简洁性。使用举例如下：

      ```cpp
      AIPlayer::AIPlayer(const std::string nickname, const Difficulty difficulty_) :
          Player(nickname),
          difficulty(difficulty_) {}
      ```

    * 空指针关键字 `nullptr`

      C++11 引入了 `nullptr` 关键字，它是一个表示空指针的字面量，用于替代传统 C++ 中的 `NULL` 。在之前的 C++ 标准中， `NULL` 通常被定义为 `0` 或 `((void*)0)` ，这可能导致类型歧义和一些难以发现的错误。 `nullptr` 的引入解决了这些问题，同时提供了更清晰、更安全的方式来表示空指针。使用举例如下：

      * 初始化空指针

        ```cpp
            Champion* battleChampion[BATTLE_AREA_MAX_CHAMPION_COUNT * 2] = { nullptr };
        ```

      * 指针重置为“无对象”

        ```cpp
        if (connectionStatus == ConnectionError || connectionStatus == ConnectionTimeout) {
            connectionFailedPrompt->setVisible(true);
            ...
            g_onlineModeControl = nullptr;
        }
        else if (connectionStatus == ConnectionRefused) {
            promptLabel->setString(GBKToUTF8::getString("服务器达到最大连接数量"));
            ...
            g_onlineModeControl = nullptr;
        }
        ```

    * 修饰常量 `constexpr`

      `constexpr` 是 C++11 新引入的关键字，用于编译时的常量和常量函数。 `constexpr` 修饰的才是真正的常量，它会在编译期间就会被计算出来，整个运行过程中都不可以被改变， `constexpr` 可以用于修饰函数，这个函数的返回值会尽可能在编译期间被计算出来当作一个常量，但是如果编译期间此函数不能被计算出来，那它就会当作一个普通函数被处理。使用举例如下：

      ```cpp
      constexpr int DESIGN_RESOLUTION_WIDTH = 1280;
      constexpr int DESIGN_RESOLUTION_HEIGHT = 720;
      ```

    * 新随机数

      C++11 引入了一个全面的随机数生成库，这个库提供了多种随机数生成器（Random Number Generators, RNGs）和多种概率分布。这个库的设计旨在解决旧 C++ 标准中随机数功能有限的问题，提供了更灵活、更高效且类型安全的随机数生成方式。使用举例如下：

      ```cpp
      std::random_device rd;
      std::mt19937 g(rd());
      std::shuffle(allChampions.begin(), allChampions.end(), g);
      ```

    * `lambda` 表达式

      `lambda` 表达式是 C++11 最重要也最常用的一个特性之一。它能够就地匿名定义目标函数或函数对象，不需要额外写一个命名函数或者函数对象。以更直接的方式去写程序，好的可读性和可维护性。使用示例如下：

      ```cpp
      uplevelButton->addTouchEventListener([this, uplevelCoinLabel](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
          if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
              g_onlineModeControl->getHumanPlayer()->addBattleChampionCount();
              const int maxBattleChampionCount = g_onlineModeControl->getHumanPlayer()->getMaxBattleChampionCount();
              uplevelCoinLabel->setString(maxBattleChampionCount >= (static_cast<TalentRune>(cocos2d::UserDefault::getInstance()->getIntegerForKey("TalentRune") == General ? BATTLE_AREA_MAX_CHAMPION_COUNT : BATTLE_AREA_MAX_CHAMPION_COUNT - 1)) ? "" : std::to_string(UPLEVEL_PRICE.at(maxBattleChampionCount)));
          }
          });
      ```

    * 时间库 `chrono` 和线程库 `this_thread`

      C++11 引入了 `chrono` 库，用于处理时间。这个库提供了时间点（time points）和持续时间（durations）的表示，以及时钟（clocks）。

      C++11 标准引入了线程库，它提供了对线程的控制和管理。在这里， `std::this_thread` 是一个命名空间，它提供了与当前线程相关的函数。特别地， `std::this_thread::sleep_for` 是一个函数，用于使当前线程休眠指定的时间。

      使用举例如下：

      ```cpp
      std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(5000 * SERVER_REFRESH_INTERVAL)));
      ```

    * `Unicode` 编码支持

      C++11 引入了对 `Unicode` 的支持，并且引入了几种新的字符串字面量，在本项目中，使用了 `u8` 。 `u8` 用于表示 UTF-8 编码的字符串字面量。UTF-8 是一种可变长度的字符编码，用于编码 `Unicode` 字符。这使得 C++ 程序能够更容易地处理多种语言和字符集。使用举例如下：

      ```cpp
      auto textField = cocos2d::ui::TextField::create(u8"请输入您的游戏昵称", "../Resources/Fonts/DingDingJinBuTi.ttf", INITIAL_SCENE_FONT_SIZE);
      ```

  * [x] 商店推荐系统

    商店推荐系统的核心与AI战斗时对英雄添加部分类似，我们首先根据当前已经拥有的英雄总价值来估算当前的战斗阶段，将其分为三个战斗阶段 `EarlyStage` ， `MiddleStage` 和 `LateStage` ，继续沿用对英雄的强度分类，越强（即越贵）的英雄强度等级越高。

    整体而言，商店系统生成随机英雄的本质还是投掷随机数，根据随机数的所在区间来选择对应的英雄。只不过我们对三个不同的游戏阶段有着不同的区间划分。即游戏前期刷新出高强度英雄的概率比较低，游戏后期刷新出高强度英雄的概率大大提高。

  * [X] AI 落棋算法

    本项目中我们对 AI 落棋算法的设计大致分为以下几个部分：对游戏阶段的划分、对添加战斗英雄或升级战斗英雄的决策、对已拥有的战斗英雄出战的选择、对出战战斗英雄的站位决策。

    * 对游戏阶段的划分

      为了方便我们在每个回合结束后，在 AI 的购买英雄阶段更好的购买合适的英雄，我们在每个购买英雄阶段都会扫描一遍当前上场的英雄，根据每一个已拥有的英雄，计算总价值来获取当前的金币数量，从这个来决定并判断当前的游戏阶段，我们一共分为三个游戏阶段，即 `EarlyStage` ， `MiddleStage` 和 `LateStage` 。

    * 对添加战斗英雄或升级战斗英雄的决策

      在每个战斗回合结束时候， `HumanPlayer` 会在本地的商店里手动刷新并购买英雄，但是 AI 端获取新英雄就必须根据当前场上的局势进行判断。我们的策略是根据当前的游戏阶段来决策，首先判断当前已有英雄来判断能否通过购买英雄使当前英雄升星。如果可以就升星；如果不可以就根据当前游戏阶段选择对应的英雄。在根据当前游戏阶段选择对应的战斗英雄过程中，我们首先将所有英雄根据具体的强度高低分为五类，然后对他们五类设置合适的比例，通过投掷随机数的方式来获取当前想购买的英雄所在强度区域，最后就在这些英雄中再次使用随机数来获得合适的英雄。

    * 对已拥有的战斗英雄出战的选择

      已经拥有的英雄将被放在候战区与战斗区，那么应该如何对上场战斗英雄做出选择？应对这个问题，我们首先建立了一套关于每个英雄的整体评分系统，通过对他们的整体评分来对其强度进行简单的划分。然后获取当前的 AI 战斗难度，根据不同的难度进行不同的英雄选择策略。如果是困难模式我们就将当前的所有英雄遍历一遍，将其插入优先级队列 `orderedChampions` 中，然后按照当前战斗区域可以有的最大英雄数量选择优先队列的评分最高的前五个上场。如果是中等难度就从当前已拥有的英雄中随机抽取，如果是简单模式的话就从优先级队列中抽取评分最低的前五名英雄上场。

    * 对出战战斗英雄的站位决策

      对于已经选择出的上场战斗英雄，我们需要建立一套标准来使其被安排在合适的战斗区域位置上。对此，我们的解决方案是获取当前的难度选择，根据当前的难度来进行不同的站位安排策略。整体来说是对战斗的“行”进行选择，对列就随机生成位置。

      首先我们将所有上场战斗英雄分为两部分，分别是靠前英雄和靠后英雄。分类的根据是一套对于它们职业偏向的一种估分策略。职业偏向综合考虑了每个英雄的生命、防御系数、攻击力以及射程等一系列因素，最终得出一个分数，分数越高的英雄将会被安排在后排，分数低的英雄将会被安排在前排，更方便于它们挡伤害。

      对于简单难度而言，我们对于靠前英雄和靠后英雄都是随机行摆放；对于中等难度而言，我们将靠前英雄固定在前两行，在前两行内进行位置的随机生成；靠后英雄就被固定在后两行，同样是在后两行中生成随机位置。而对于困难难度，我们仅仅是改变了靠前英雄和靠后英雄的随机生成区域，分别将他们固定在第一行和最后一行，列数同样是随机生成。最终经过测试后就能发现这样的站位安排非常合理，游戏均衡性得到保证。

  * [x] 规范统一的代码风格

    本项目在正式开始前明确了团队项目代码规范，并且组长负责 Code Review 工作。

  * [x] 游戏还原度高

    本游戏以《金铲铲之战》游戏为参考，对游戏场景界面、游戏玩法、游戏音乐音效以及游戏角色进行了设计参考。

    * 游戏场景界面按钮

      本项目场景均从《金铲铲之战》官网寻找适合大小的背景图，以更贴合游戏原型。

    * 游戏玩法与游戏角色设计

      本项目为自走棋游戏。但在一般自走棋的基础上，结合了《金铲铲之战》的独特玩法和元素，实现了小小英雄的移动。其中游戏英雄的设计和贴图也均来自于官网，最后本小组结合游戏的平衡性和具体实现情况进行了修改以更适应实际情况。

    * 游戏背景音乐与音效

      游戏背景音乐在一般的战斗音乐的基础上，结合了《金铲铲之战》中的音乐音效，更加还原。

  * [x] 常变量的集中定义

    本项目的 `Constant.h` 头文件集中存放了所有常变量的定义，并在服务器项目（ `Server` ）和游戏项目（ `Teamflight_Tactics` ）中共用，注释完备，方便项目维护。

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

### 2024/4/3

* [Business Plan](Business_Plan.pdf) 制作

## 集成开发环境

* Microsoft Visual Studio 2022

## 编译运行环境

* 本项目仅适用于x86架构

## 联系我们

Email: minmuslin@outlook.com

## 文档更新日期

2024年4月3日