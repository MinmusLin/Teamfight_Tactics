/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     StartupScene.cpp
 * File Function: StartupScene类的实现
 * Author:        林继申
 * Update Date:   2023/12/20
 ****************************************************************/

#include "StartupScene.h"
#include "InitialScene.h"
#include "ui/CocosGUI.h"
#include "proj.win32/Constant.h"

USING_NS_CC;

// 创建场景
Scene* StartupScene::createScene()
{
    auto scene = Scene::create();
    auto layer = StartupScene::create();
    scene->addChild(layer);
    return scene;
}

// 初始化场景
bool StartupScene::init()
{
    // 创建场景
    if (!Scene::init()) {
        return false;
    }

    // 加载背景
    const auto screenSize = Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/StartupScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // 创建进度条
    auto progressBar = ui::LoadingBar::create("../Resources/LoadingBars/StartupSceneLoadingBar.png");
    progressBar->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + STARTUP_SCENE_LOADINGBAR_OFFSET_Y));
    progressBar->setPercent(0);
    this->addChild(progressBar);

    // 创建标签以显示进度
    auto progressLabel = Label::createWithTTF("0%", "../Resources/Fonts/FZZGY_J_EB.ttf", STARTUP_SCENE_FONT_SIZE);
    progressLabel->setPosition(Vec2(progressBar->getPosition().x - progressBar->getContentSize().width / 2 + STARTUP_SCENE_LOADING_LABLE_OFFSET_X, progressBar->getPosition().y));
    progressLabel->setVisible(false);
    this->addChild(progressLabel);

    // 更新进度条和标签
    const float interval = STARTUP_SCENE_DURATION / 100.0f; // 每 1% 所需时间
    for (int i = 0; i <= 100; i++) {
        this->scheduleOnce([progressBar, progressLabel, i](float dt) {
            progressLabel->setVisible(i >= 10);
            progressBar->setPercent(i);
            progressLabel->setString(std::to_string(i) + "%");
            float percentage = progressBar->getPercent() / 100.0f;
            float xPosition = progressBar->getPosition().x - progressBar->getContentSize().width / 2 + progressBar->getContentSize().width * percentage + STARTUP_SCENE_LOADING_LABLE_OFFSET_X;
            progressLabel->setPosition(Vec2(xPosition, progressBar->getPosition().y));
            }, interval * i, "UpdateProgressBar" + std::to_string(i) + "%");
    }

    // 设置计时器
    this->scheduleOnce([](float dt) {
        auto transition = TransitionFade::create(SCENE_TRANSITION_DURATION, InitialScene::createScene(), Color3B::WHITE);
        Director::getInstance()->replaceScene(transition);
        }, STARTUP_SCENE_DURATION + SCENE_TRANSITION_DURATION, "StartupSceneToInitialScene");

    return true;
}