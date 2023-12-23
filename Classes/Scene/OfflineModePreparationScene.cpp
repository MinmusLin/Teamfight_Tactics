/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModePreparationScene.cpp
 * File Function: OfflineModePreparationScene类的实现
 * Author:        林继申
 * Update Date:   2023/12/24
 ****************************************************************/

#include "OfflineModePreparationScene.h"
#include "OfflineModeBattleScene.h"
#include "Control/OfflineModeControl.h"
#include "Button/HoverButton.h"
#include "GBKToUTF8/GBKToUTF8.h"
#include "MenuScene.h"

// 命名空间
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Label;
using cocos2d::Vec2;

// 练习模式游戏控制类
extern OfflineModeControl* g_offlineModeControl;

// 创建场景
Scene* OfflineModePreparationScene::createScene()
{
    auto scene = Scene::create();
    auto layer = OfflineModePreparationScene::create();
    scene->addChild(layer);
    return scene;
}

// 初始化场景
bool OfflineModePreparationScene::init()
{
    // 创建场景
    if (!Scene::init()) {
        return false;
    }

    // 设置 HumanPlayer 类的当前场景指针
    g_offlineModeControl->getHumanPlayer()->setCurrentScene(this);

    // 加载背景
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/OfflineModePreparationScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // 创建等级标签
    Label* levelLabel;
    const int currentBattleChampionCount = g_offlineModeControl->getHumanPlayer()->getMaxBattleChampionCount();
    if (currentBattleChampionCount >= BATTLE_AREA_MAX_CHAMPION_COUNT) {
        levelLabel = Label::createWithTTF(GBKToUTF8::getString("最高等级"), "../Resources/Fonts/DingDingJinBuTi.ttf", SHOP_LEVEL_LABEL_FONT_SIZE);
    }
    else {
        levelLabel = Label::createWithTTF(GBKToUTF8::getString("等级：") + std::to_string(currentBattleChampionCount - BATTLE_AREA_MIN_CHAMPION_COUNT + 1), "../Resources/Fonts/DingDingJinBuTi.ttf", SHOP_LEVEL_LABEL_FONT_SIZE);
    }
    levelLabel->setAnchorPoint(Vec2(0, 0.5));
    levelLabel->setPosition(Vec2(screenSize.width / 2 + SHOP_LEVEL_LABEL_OFFSET_X, screenSize.height / 2 + SHOP_LEVEL_LABEL_OFFSET_Y));
    levelLabel->setName("LevelLabel");
    this->addChild(levelLabel);

    // 创建金币数量标签
    Label* coinLabel = Label::createWithTTF(std::to_string(g_offlineModeControl->getHumanPlayer()->getGoldCoin()), "../Resources/Fonts/DingDingJinBuTi.ttf", SHOP_COIN_LABEL_FONT_SIZE);
    coinLabel->setAnchorPoint(Vec2(1, 0.5));
    coinLabel->setPosition(Vec2(screenSize.width / 2 + SHOP_COIN_LABEL_OFFSET_X, screenSize.height / 2 + SHOP_COIN_LABEL_OFFSET_Y));
    coinLabel->setName("CoinLabel");
    this->addChild(coinLabel);

    // 创建进度条
    auto progressBar = cocos2d::ui::LoadingBar::create("../Resources/LoadingBars/CountdownLoadingBar.png");
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

    // 为按钮添加事件处理器
    uplevelButton->addTouchEventListener([this](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            g_offlineModeControl->getHumanPlayer()->addBattleChampionCount();
        }
        });
    refreshButton->addTouchEventListener([this](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            g_offlineModeControl->getHumanPlayer()->refreshShop();
        }
        });
    returnMenuButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            delete g_offlineModeControl;
            g_offlineModeControl = nullptr;
            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, MenuScene::createScene(), cocos2d::Color3B::WHITE));
        }
        });

    // 将按钮添加到场景中
    this->addChild(uplevelButton);
    this->addChild(refreshButton);
    this->addChild(returnMenuButton);

    // 初始化战斗英雄删除按钮
    g_offlineModeControl->getHumanPlayer()->initializeDeleteChampionButton();

    return true;
}

// 当场景重新进入时调用
void OfflineModePreparationScene::onEnter()
{
    // 调用基类的 onEnter 方法
    Scene::onEnter();

    // 重置进度条和标签
    auto progressBar = dynamic_cast<cocos2d::ui::LoadingBar*>(this->getChildByName("CountdownLoadingBar"));
    auto progressLabel = dynamic_cast<Label*>(this->getChildByName("CountdownLoadingBarLabel"));
    if (progressBar && progressLabel) {
        progressBar->setPercent(0);
        progressLabel->setVisible(false);

        // 取消之前的所有定时器
        this->unscheduleAllCallbacks();

        // 重新设置进度条更新逻辑与计时器
        setScheduleOnce(progressBar, progressLabel);
    }
}

// 设置进度条更新逻辑与计时器
void OfflineModePreparationScene::setScheduleOnce(cocos2d::ui::LoadingBar* progressBar, Label* progressLabel)
{
    // 刷新商店
    g_offlineModeControl->getHumanPlayer()->refreshShop();

    // 更新进度条和标签
    const float interval = BATTLE_SCENE_LOADINGBAR_DURATION / 1000.0f; // 每 0.1% 所需时间
    for (int i = 0; i <= 1000; i++) {
        this->scheduleOnce([progressBar, progressLabel, i](float dt) {
            int sceond = static_cast<int>(BATTLE_SCENE_LOADINGBAR_DURATION - i * BATTLE_SCENE_LOADINGBAR_DURATION / 1000 + 0.999);
            progressLabel->setVisible(sceond <= BATTLE_SCENE_LOADINGBAR_LABEL_THRESHOLD);
            progressBar->setPercent(i / 10.0);
            progressLabel->setString((sceond >= 10 ? "" : " ") + std::to_string(sceond) + "s");
            float percentage = progressBar->getPercent() / 100.0f;
            float xPosition = progressBar->getPosition().x - progressBar->getContentSize().width / 2 + progressBar->getContentSize().width * percentage + BATTLE_SCENE_LOADINGBAR_LABEL_OFFSET_X;
            progressLabel->setPosition(Vec2(xPosition, progressBar->getPosition().y));
            }, interval * i, "CountdownLoadingBar" + std::to_string(i));
    }

    // 设置计时器
    this->scheduleOnce([this](float dt) {
        // 创建和分派一个鼠标左键释放事件（强制放下当前战斗英雄）
        cocos2d::EventMouse event(cocos2d::EventMouse::MouseEventType::MOUSE_UP);
        event.setMouseButton(cocos2d::EventMouse::MouseButton::BUTTON_LEFT);
        _eventDispatcher->dispatchEvent(&event);

        // 运行练习模式对战场景
        cocos2d::Director::getInstance()->pushScene(OfflineModeBattleScene::create());
        }, BATTLE_SCENE_LOADINGBAR_DURATION + SCENE_TRANSITION_DURATION, "IsAlreadyPrepared");
}