/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OnlineModePreparationScene.cpp
 * File Function: OnlineModePreparationScene类的实现
 * Author:        林继申、刘淑仪
 * Update Date:   2023/12/31
 * License:       MIT License
 ****************************************************************/

#include "OnlineModePreparationScene.h"
#include "Control/OnlineModeControl.h"
#include "Scene/OnlineModeBattleScene.h"
#include "Button/HoverButton.h"
#include "Layer/ScoreBoardLayer.h"
#include "MenuScene.h"
#include "proj.win32/AudioPlayer.h"

// 命名空间
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Label;
using cocos2d::Vec2;

// 联机模式游戏控制类
extern OnlineModeControl* g_onlineModeControl;

// 创建场景
Scene* OnlineModePreparationScene::createScene()
{
    auto scene = Scene::create();
    auto layer = OnlineModePreparationScene::create();
    scene->addChild(layer);
    return scene;
}

// 初始化场景
bool OnlineModePreparationScene::init()
{
    // 创建场景
    if (!Scene::init()) {
        return false;
    }

    // 设置 HumanPlayer 类的当前场景指针
    g_onlineModeControl->getHumanPlayer()->setCurrentScene(this);

    // 加载音乐
    audioPlayer("../Resources/Music/PreparationScene_RagsToRings.mp3", true);

    // 加载背景
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/OfflineModePreparationScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // 创建等级标签
    Label* levelLabel;
    const int currentBattleChampionCount = g_onlineModeControl->getHumanPlayer()->getMaxBattleChampionCount();
    if (currentBattleChampionCount >= (static_cast<TalentRune>(cocos2d::UserDefault::getInstance()->getIntegerForKey("TalentRune") == General ? BATTLE_AREA_MAX_CHAMPION_COUNT : BATTLE_AREA_MAX_CHAMPION_COUNT - 1))) {
        levelLabel = Label::createWithTTF(u8"最高等级", "../Resources/Fonts/DingDingJinBuTi.ttf", SHOP_LEVEL_LABEL_FONT_SIZE);
    }
    else {
        levelLabel = Label::createWithTTF(u8"等级：" + std::to_string(currentBattleChampionCount - BATTLE_AREA_MIN_CHAMPION_COUNT + 1), "../Resources/Fonts/DingDingJinBuTi.ttf", SHOP_LEVEL_LABEL_FONT_SIZE);
    }
    levelLabel->setAnchorPoint(Vec2(0, 0.5));
    levelLabel->setPosition(Vec2(screenSize.width / 2 + SHOP_LEVEL_LABEL_OFFSET_X, screenSize.height / 2 + SHOP_LEVEL_LABEL_OFFSET_Y));
    levelLabel->setName("LevelLabel");
    this->addChild(levelLabel);

    // 创建金币数量标签
    Label* coinLabel = Label::createWithTTF(std::to_string(g_onlineModeControl->getHumanPlayer()->getGoldCoin()), "../Resources/Fonts/DingDingJinBuTi.ttf", SHOP_COIN_LABEL_FONT_SIZE);
    coinLabel->setAnchorPoint(Vec2(1, 0.5));
    coinLabel->setPosition(Vec2(screenSize.width / 2 + SHOP_COIN_LABEL_OFFSET_X, screenSize.height / 2 + SHOP_COIN_LABEL_OFFSET_Y));
    coinLabel->setName("CoinLabel");
    this->addChild(coinLabel);

    // 创建进度条
    auto progressBar = cocos2d::ui::LoadingBar::create("../Resources/ImageElements/CountdownLoadingBar.png");
    progressBar->setPosition(Vec2(BATTLE_SCENE_LOADINGBAR_X, BATTLE_SCENE_LOADINGBAR_Y));
    progressBar->setPercent(0);
    progressBar->setName("CountdownLoadingBar");
    this->addChild(progressBar);

    // 创建标签以显示进度
    auto progressLabel = Label::createWithTTF("", "../Resources/Fonts/FangZhengZhaoGeYuan.ttf", BATTLE_SCENE_LOADINGBAR_LABEL_FONT_SIZE);
    progressLabel->setPosition(Vec2(progressBar->getPosition().x - progressBar->getContentSize().width / 2 + BATTLE_SCENE_LOADINGBAR_LABEL_OFFSET_X, progressBar->getPosition().y));
    progressLabel->setVisible(false);
    progressLabel->setName("CountdownLoadingBarLabel");
    this->addChild(progressLabel);

    // 设置进度条更新逻辑与计时器
    setScheduleOnce(progressBar, progressLabel);

    // 创建按钮
    auto uplevelButton = HoverButton::create("../Resources/Buttons/OfflineModePreparationSceneButtons/UplevelDefaultButton.png",
        "../Resources/Buttons/OfflineModePreparationSceneButtons/UplevelHoverButton.png",
        "../Resources/Buttons/OfflineModePreparationSceneButtons/UplevelActiveButton.png");
    auto refreshButton = HoverButton::create("../Resources/Buttons/OfflineModePreparationSceneButtons/RefreshDefaultButton.png",
        "../Resources/Buttons/OfflineModePreparationSceneButtons/RefreshHoverButton.png",
        "../Resources/Buttons/OfflineModePreparationSceneButtons/RefreshActiveButton.png");
    auto returnMenuButton = HoverButton::create("../Resources/Buttons/OfflineModePreparationSceneButtons/ReturnMenuDefaultButton.png",
        "../Resources/Buttons/OfflineModePreparationSceneButtons/ReturnMenuHoverButton.png",
        "../Resources/Buttons/OfflineModePreparationSceneButtons/ReturnMenuActiveButton.png");

    // 设置按钮位置
    uplevelButton->setPosition(Vec2(screenSize.width / 2 + SHOP_UPLEVEL_BUTTON_OFFSET_X, screenSize.height / 2 + SHOP_UPLEVEL_BUTTON_OFFSET_Y));
    refreshButton->setPosition(Vec2(screenSize.width / 2 + SHOP_REFRESH_BUTTON_OFFSET_X, screenSize.height / 2 + SHOP_REFRESH_BUTTON_OFFSET_Y));
    returnMenuButton->setPosition(Vec2(screenSize.width / 2 + BATTLE_SCENE_RETURN_MENU_BUTTON_OFFSET_X, screenSize.height / 2 + BATTLE_SCENE_RETURN_MENU_BUTTON_OFFSET_Y));

    // 创建金币数量标签
    auto refreshCoinLabel = Label::createWithTTF(std::to_string(REFRESH_SHOP_PRICE), "../Resources/Fonts/DingDingJinBuTi.ttf", SHOP_COIN_LABEL_FONT_SIZE);
    refreshCoinLabel->setAnchorPoint(Vec2(1, 0.5));
    refreshCoinLabel->setPosition(SHOP_COIN_LABEL_START_X, SHOP_REFRESH_COIN_LABEL_START_Y);
    this->addChild(refreshCoinLabel, 2);
    auto uplevelCoinLabel = Label::createWithTTF(std::to_string(UPLEVEL_PRICE.at(g_onlineModeControl->getHumanPlayer()->getMaxBattleChampionCount())), "../Resources/Fonts/DingDingJinBuTi.ttf", SHOP_COIN_LABEL_FONT_SIZE);
    uplevelCoinLabel->setAnchorPoint(Vec2(1, 0.5));
    uplevelCoinLabel->setPosition(SHOP_COIN_LABEL_START_X, SHOP_UPLEVEL_COIN_LABEL_START_Y);
    this->addChild(uplevelCoinLabel, 2);

    // 为按钮添加事件处理器
    uplevelButton->addTouchEventListener([this, uplevelCoinLabel](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            g_onlineModeControl->getHumanPlayer()->addBattleChampionCount();
            const int maxBattleChampionCount = g_onlineModeControl->getHumanPlayer()->getMaxBattleChampionCount();
            uplevelCoinLabel->setString(maxBattleChampionCount >= (static_cast<TalentRune>(cocos2d::UserDefault::getInstance()->getIntegerForKey("TalentRune") == General ? BATTLE_AREA_MAX_CHAMPION_COUNT : BATTLE_AREA_MAX_CHAMPION_COUNT - 1)) ? "" : std::to_string(UPLEVEL_PRICE.at(maxBattleChampionCount)));
        }
        });
    refreshButton->addTouchEventListener([this](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            g_onlineModeControl->getHumanPlayer()->refreshShop();
        }
        });
    returnMenuButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            // 加载点击音效
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

            delete g_onlineModeControl;
            g_onlineModeControl = nullptr;
            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, MenuScene::createScene(), cocos2d::Color3B::WHITE));
        }
        });

    // 将按钮添加到场景中
    this->addChild(uplevelButton, 1);
    this->addChild(refreshButton, 1);
    this->addChild(returnMenuButton);

    // 初始化战斗英雄删除按钮
    g_onlineModeControl->getHumanPlayer()->initializeDeleteChampionButton();

    // 创建分数表层
    auto scoreBoardLayer = ScoreBoardLayer::create();
    scoreBoardLayer->initialize(g_onlineModeControl->getCurrentConnections());
    scoreBoardLayer->showScoreBoard(g_onlineModeControl->getCurrentConnections(), g_onlineModeControl->getPlayerNames(), g_onlineModeControl->getPlayerHealthPoints());
    scoreBoardLayer->setName("ScoreBoardLayer");
    this->addChild(scoreBoardLayer);

    return true;
}

// 当场景重新进入时调用
void OnlineModePreparationScene::onEnter()
{
    // 调用基类的 onEnter 方法
    Scene::onEnter();

    // 重置分数表层
    auto scoreBoardLayer = dynamic_cast<ScoreBoardLayer*>(this->getChildByName("ScoreBoardLayer"));
    scoreBoardLayer->showScoreBoard(g_onlineModeControl->getCurrentConnections(), g_onlineModeControl->getPlayerNames(), g_onlineModeControl->getPlayerHealthPoints());

    // 重置进度条和标签
    auto progressBar = dynamic_cast<cocos2d::ui::LoadingBar*>(this->getChildByName("CountdownLoadingBar"));
    auto progressLabel = dynamic_cast<Label*>(this->getChildByName("CountdownLoadingBarLabel"));
    if (progressBar && progressLabel) {
        // 设置进度条百分比
        progressBar->setPercent(0);
        progressLabel->setVisible(false);

        // 取消之前的所有定时器
        this->unscheduleAllCallbacks();

        // 重新设置进度条更新逻辑与计时器
        setScheduleOnce(progressBar, progressLabel);
    }
}

// 设置进度条更新逻辑与计时器
void OnlineModePreparationScene::setScheduleOnce(cocos2d::ui::LoadingBar* progressBar, Label* progressLabel)
{
    // 刷新商店
    g_onlineModeControl->getHumanPlayer()->refreshShop();

    // 更新进度条和标签
    constexpr float interval = BATTLE_SCENE_LOADINGBAR_DURATION / 1000.0f; // 每 0.1% 所需时间
    for (int i = 0; i <= 1000; i++) {
        this->scheduleOnce([progressBar, progressLabel, i](float dt) {
            int sceond = static_cast<int>(BATTLE_SCENE_LOADINGBAR_DURATION - i * BATTLE_SCENE_LOADINGBAR_DURATION / 1000 + 0.999);
            progressLabel->setVisible(sceond <= BATTLE_SCENE_LOADINGBAR_LABEL_THRESHOLD);
            progressBar->setPercent(i / 10.0);
            progressLabel->setString((sceond >= 10 ? "" : " ") + std::to_string(sceond) + "s");
            const float percentage = progressBar->getPercent() / 100.0f;
            const float xPosition = progressBar->getPosition().x - progressBar->getContentSize().width / 2 + progressBar->getContentSize().width * percentage + BATTLE_SCENE_LOADINGBAR_LABEL_OFFSET_X;
            progressLabel->setPosition(Vec2(xPosition, progressBar->getPosition().y));
            }, interval * i, "CountdownLoadingBar" + std::to_string(i));
    }

    // 设置计时器
    this->scheduleOnce([this](float dt) {
        // 创建和分派一个鼠标左键释放事件（强制放下当前战斗英雄）
        cocos2d::EventMouse event(cocos2d::EventMouse::MouseEventType::MOUSE_UP);
        event.setMouseButton(cocos2d::EventMouse::MouseButton::BUTTON_LEFT);
        _eventDispatcher->dispatchEvent(&event);

        // 运行联机模式对战场景
        char buffer[BUFFER_SIZE];
        sprintf(buffer, BATTLE_MAP_FORMAT, g_onlineModeControl->serializePlayerMap().c_str());
        g_onlineModeControl->sendMessage(buffer, strlen(buffer));
        cocos2d::Director::getInstance()->pushScene(OnlineModeBattleScene::create());
        }, BATTLE_SCENE_LOADINGBAR_DURATION + SCENE_TRANSITION_DURATION, "IsAlreadyPrepared");
}