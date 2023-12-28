/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     StartupScene.cpp
 * File Function: StartupScene���ʵ��
 * Author:        �ּ��ꡢ������
 * Update Date:   2023/12/28
 * License:       MIT License
 ****************************************************************/

#include "StartupScene.h"
#include "InitialScene.h"
#include "ui/CocosGUI.h"
#include "proj.win32/Constant.h"
#include "AudioEngine.h"

// �����ռ�
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Label;
using cocos2d::Vec2;

// ��Ƶ��������
extern int g_backgroundMusicSign;
extern int g_effectMusicSign;
extern float g_backgroundMusicVolumn;
extern float g_effectMusicVolumn;

// ��������
Scene* StartupScene::createScene()
{
    auto scene = Scene::create();
    auto layer = StartupScene::create();
    scene->addChild(layer);
    return scene;
}

// ��ʼ������
bool StartupScene::init()
{
    // ��������
    if (!Scene::init()) {
        return false;
    }

    // ���ر�������
    if (g_backgroundMusicSign != DEFAULT_MUSIC_SIGN) {
        cocos2d::experimental::AudioEngine::stop(g_backgroundMusicSign);
    }
    g_backgroundMusicSign = cocos2d::experimental::AudioEngine::play2d("../Resources/Music/BackgroundMusic/StartupScene_BreathAndLife.mp3", true);
    cocos2d::experimental::AudioEngine::setVolume(g_backgroundMusicSign, g_backgroundMusicVolumn);

    // ���ر���
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/StartupScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // ����������
    auto progressBar = cocos2d::ui::LoadingBar::create("../Resources/LoadingBars/StartupLoadingBar.png");
    progressBar->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + STARTUP_SCENE_LOADINGBAR_OFFSET_Y));
    progressBar->setPercent(0);
    this->addChild(progressBar);

    // ������ǩ����ʾ����
    auto progressLabel = Label::createWithTTF("0%", "../Resources/Fonts/FangZhengZhaoGeYuan.ttf", STARTUP_SCENE_FONT_SIZE);
    progressLabel->setPosition(Vec2(progressBar->getPosition().x - progressBar->getContentSize().width / 2 + STARTUP_SCENE_LOADING_LABEL_OFFSET_X, progressBar->getPosition().y));
    progressLabel->setVisible(false);
    this->addChild(progressLabel);

    // ���½������ͱ�ǩ
    constexpr float interval = STARTUP_SCENE_DURATION / 100.0f; // ÿ 1% ����ʱ��
    for (int i = 0; i <= 100; i++) {
        this->scheduleOnce([progressBar, progressLabel, i](float dt) {
            progressLabel->setVisible(i >= 10);
            progressBar->setPercent(i);
            progressLabel->setString(std::to_string(i) + "%");
            float percentage = progressBar->getPercent() / 100.0f;
            float xPosition = progressBar->getPosition().x - progressBar->getContentSize().width / 2 + progressBar->getContentSize().width * percentage + STARTUP_SCENE_LOADING_LABEL_OFFSET_X;
            progressLabel->setPosition(Vec2(xPosition, progressBar->getPosition().y));
            }, interval * i, "UpdateStartupLoadingBar" + std::to_string(i));
    }

    // ���ü�ʱ��
    this->scheduleOnce([](float dt) {
        auto transition = cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, InitialScene::createScene(), cocos2d::Color3B::WHITE);
        cocos2d::Director::getInstance()->replaceScene(transition);
        }, STARTUP_SCENE_DURATION + SCENE_TRANSITION_DURATION, "StartupSceneToInitialScene");

    return true;
}