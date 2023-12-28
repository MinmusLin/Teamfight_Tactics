/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     SettingsScene.cpp
 * File Function: SettingsScene类的实现
 * Author:        刘淑仪
 * Update Date:   2023/12/27
 ****************************************************************/

#include "SettingsScene.h"
#include "ui/CocosGUI.h"
#include "proj.win32/Constant.h"
#include "AudioEngine.h"
#include "Button/HoverButton.h"
#include "MenuScene.h"

 // 命名空间
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Label;
using cocos2d::Vec2;

// 设置音乐引擎
extern int backgroundMusic;
extern int effectMusic;

// 音量变量
extern float g_backgroundMusicVolumn;
extern float g_effectVolumn;

// 创建场景
Scene* SettingsScene::createScene()
{
    auto scene = Scene::create();
    auto layer = SettingsScene::create();
    scene->addChild(layer);
    return scene;
}

// 初始化场景
bool SettingsScene::init()
{
    // 创建场景
    if (!Scene::init()) {
        return false;
    }

    // 加载设置音乐
    if (backgroundMusic != -1) {
        cocos2d::experimental::AudioEngine::stop(backgroundMusic);
    }
    backgroundMusic = cocos2d::experimental::AudioEngine::play2d("../Resources/Music/BackgroundMusic/SettingsScene_Starlight.mp3", true);
    cocos2d::experimental::AudioEngine::setVolume(backgroundMusic, g_backgroundMusicVolumn);

    // 加载背景
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/SettingsScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // 创建滑动条
    auto backgroundMusicVolumnSlider = cocos2d::ui::Slider::create();
    backgroundMusicVolumnSlider->loadBarTexture("../Resources/Layers/SliderBack.png");
    backgroundMusicVolumnSlider->loadSlidBallTextures("../Resources/Layers/SliderNodeNormal.png", "../Resources/Layers/SliderNodePress.png", "../Resources/Layers/SliderNodeDisable.png");
    backgroundMusicVolumnSlider->loadProgressBarTexture("../Resources/Layers/SliderPressBar.png");

    auto effectVolumnslider = cocos2d::ui::Slider::create();
    effectVolumnslider->loadBarTexture("../Resources/Layers/SliderBack.png");
    effectVolumnslider->loadSlidBallTextures("../Resources/Layers/SliderNodeNormal.png", "../Resources/Layers/SliderNodePress.png", "../Resources/Layers/SliderNodeDisable.png");
    effectVolumnslider->loadProgressBarTexture("../Resources/Layers/SliderPressBar.png");

    // 设置滑动条位置
    backgroundMusicVolumnSlider->setPosition(cocos2d::Vec2(screenSize.width / 2 + SETTINGS_SCENE_SLIDER_OFFSET_X, screenSize.height / 2 + SETTINGS_SCENE_BGMSLIDER_OFFSET_Y));
    effectVolumnslider->setPosition(cocos2d::Vec2(screenSize.width / 2 + SETTINGS_SCENE_SLIDER_OFFSET_X, screenSize.height / 2 + SETTINGS_SCENE_EFFSLIDER_OFFSET_Y));

    // 设置滑动条初始值
    backgroundMusicVolumnSlider->setPercent(g_backgroundMusicVolumn * 100);
    effectVolumnslider->setPercent(g_effectVolumn * 100);

    // 为滑动条添加事件处理器
    backgroundMusicVolumnSlider->addEventListener([=](Ref* sender, cocos2d::ui::Slider::EventType type) {
        if (type == cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED) {
            cocos2d::ui::Slider* backgroundMusicVolumnSlider = dynamic_cast<cocos2d::ui::Slider*>(sender);
            float percent = backgroundMusicVolumnSlider->getPercent();
            g_backgroundMusicVolumn = percent / 100.0f;
            cocos2d::experimental::AudioEngine::setVolume(backgroundMusic, g_backgroundMusicVolumn);
        }
        });

    effectVolumnslider->addEventListener([=](Ref* sender, cocos2d::ui::Slider::EventType type) {
        if (type == cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED) {
            cocos2d::ui::Slider* effectVolumnslider = dynamic_cast<cocos2d::ui::Slider*>(sender);
            float percent = effectVolumnslider->getPercent();
            g_effectVolumn = percent / 100.0f;
            cocos2d::experimental::AudioEngine::setVolume(effectMusic, g_effectVolumn);
        }
        });

    this->addChild(backgroundMusicVolumnSlider);
    this->addChild(effectVolumnslider);

    // 创建复选框
    auto EasyCheckBox = cocos2d::ui::CheckBox::create("../Resources/Layers/CheckBoxNormal.png",
        "../Resources/Layers/CheckBoxNormalPress.png",
        "../Resources/Layers/CheckBoxActive.png",
        "../Resources/Layers/CheckBoxNormalDisable.png",
        "../Resources/Layers/CheckBoxActiveDisable.png");
    auto NormalCheckBox = cocos2d::ui::CheckBox::create("../Resources/Layers/CheckBoxNormal.png",
        "../Resources/Layers/CheckBoxNormalPress.png",
        "../Resources/Layers/CheckBoxActive.png",
        "../Resources/Layers/CheckBoxNormalDisable.png",
        "../Resources/Layers/CheckBoxActiveDisable.png");
    auto DifficultCheckBox = cocos2d::ui::CheckBox::create("../Resources/Layers/CheckBoxNormal.png",
        "../Resources/Layers/CheckBoxNormalPress.png",
        "../Resources/Layers/CheckBoxActive.png",
        "../Resources/Layers/CheckBoxNormalDisable.png",
        "../Resources/Layers/CheckBoxActiveDisable.png");

    // 设置复选框的位置
    EasyCheckBox->setPosition(cocos2d::Vec2(screenSize.width / 2 + SETTINGS_SCENE_EASY_CHECKBOX_OFFSET_X, screenSize.height / 2 + SETTINGS_SCENE_CHECKBOX_OFFSET_Y));
    NormalCheckBox->setPosition(cocos2d::Vec2(screenSize.width / 2 + SETTINGS_SCENE_NORMAL_CHECKBOX_OFFSET_X, screenSize.height / 2 + SETTINGS_SCENE_CHECKBOX_OFFSET_Y));
    DifficultCheckBox->setPosition(cocos2d::Vec2(screenSize.width / 2 + SETTINGS_SCENE_DIFFICULT_CHECKBOX_OFFSET_X, screenSize.height / 2 + SETTINGS_SCENE_CHECKBOX_OFFSET_Y));

    // 为复选框添加事件处理器
    EasyCheckBox->addEventListener([=](Ref* sender, cocos2d::ui::CheckBox::EventType type) {
        if (type == cocos2d::ui::CheckBox::EventType::SELECTED) {
            // TODO : 当复选框被勾选时的逻辑
            NormalCheckBox->setSelected(false);
            DifficultCheckBox->setSelected(false);
        }
        else if (type == cocos2d::ui::CheckBox::EventType::UNSELECTED) {
            // TODO : 当复选框被取消勾选时的逻辑
        }
        });
    NormalCheckBox->addEventListener([=](Ref* sender, cocos2d::ui::CheckBox::EventType type) {
        if (type == cocos2d::ui::CheckBox::EventType::SELECTED) {
            // TODO : 当复选框被勾选时的逻辑
            EasyCheckBox->setSelected(false);
            DifficultCheckBox->setSelected(false);
        }
        else if (type == cocos2d::ui::CheckBox::EventType::UNSELECTED) {
            // TODO : 当复选框被取消勾选时的逻辑
        }
        });
    DifficultCheckBox->addEventListener([=](Ref* sender, cocos2d::ui::CheckBox::EventType type) {
        if (type == cocos2d::ui::CheckBox::EventType::SELECTED) {
            // TODO : 当复选框被勾选时的逻辑
            NormalCheckBox->setSelected(false);
            EasyCheckBox->setSelected(false);
        }
        else if (type == cocos2d::ui::CheckBox::EventType::UNSELECTED) {
            // TODO : 当复选框被取消勾选时的逻辑
        }
        });

    this->addChild(EasyCheckBox);
    this->addChild(NormalCheckBox);
    this->addChild(DifficultCheckBox);

    // 创建返回菜单按钮
    auto returnMenuButton = HoverButton::create("../Resources/Buttons/SettingsSceneButtons/ReturnMenuDefaultButton.png",
        "../Resources/Buttons/SettingsSceneButtons/ReturnMenuHoverButton.png",
        "../Resources/Buttons/SettingsSceneButtons/ReturnMenuActiveButton.png");

    // 设置按钮位置
    returnMenuButton->setPosition(Vec2(screenSize.width / 2 + SETTINGS_SCENE_RETURN_MENU_BUTTON_OFFSET_X, screenSize.height / 2 + SETTINGS_SCENE_RETURN_MENU_BUTTON_OFFSET_Y));

    // 为按钮设置事件处理器
    returnMenuButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, MenuScene::createScene(), cocos2d::Color3B::WHITE));
        }
        });

    this->addChild(returnMenuButton);

    return true;
}