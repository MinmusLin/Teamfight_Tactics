/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     SettingsScene.cpp
 * File Function: SettingsScene类的实现
 * Author:        刘淑仪、林继申
 * Update Date:   2023/12/28
 ****************************************************************/

#include "SettingsScene.h"
#include "AudioEngine.h"
#include "Button/HoverButton.h"
#include "MenuScene.h"
#include "proj.win32/Constant.h"

// 命名空间
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Label;
using cocos2d::Vec2;

// 游戏难度
Difficulty g_difficulty = Normal;

// 音频引擎设置
extern int g_backgroundMusicSign;
extern int g_effectMusicSign;
extern float g_backgroundMusicVolumn;
extern float g_effectMusicVolumn;

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

    // 加载背景
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/SettingsScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // 创建滑动条
    auto backgroundMusicVolumnSlider = cocos2d::ui::Slider::create();
    backgroundMusicVolumnSlider->loadBarTexture("../Resources/Layers/SliderBack.png");
    backgroundMusicVolumnSlider->loadSlidBallTextures("../Resources/Layers/SliderNodeNormal.png",
        "../Resources/Layers/SliderNodePress.png",
        "../Resources/Layers/SliderNodeDisable.png");
    backgroundMusicVolumnSlider->loadProgressBarTexture("../Resources/Layers/SliderPressBar.png");
    backgroundMusicVolumnSlider->setPosition(cocos2d::Vec2(screenSize.width / 2 + SETTINGS_SCENE_SLIDER_OFFSET_X, screenSize.height / 2 + SETTINGS_SCENE_BGMSLIDER_OFFSET_Y));
    backgroundMusicVolumnSlider->setPercent(g_backgroundMusicVolumn * 100);
    auto effectVolumnslider = cocos2d::ui::Slider::create();
    effectVolumnslider->loadBarTexture("../Resources/Layers/SliderBack.png");
    effectVolumnslider->loadSlidBallTextures("../Resources/Layers/SliderNodeNormal.png",
        "../Resources/Layers/SliderNodePress.png",
        "../Resources/Layers/SliderNodeDisable.png");
    effectVolumnslider->loadProgressBarTexture("../Resources/Layers/SliderPressBar.png");
    effectVolumnslider->setPosition(cocos2d::Vec2(screenSize.width / 2 + SETTINGS_SCENE_SLIDER_OFFSET_X, screenSize.height / 2 + SETTINGS_SCENE_EFFSLIDER_OFFSET_Y));
    effectVolumnslider->setPercent(g_effectMusicVolumn * 100);

    // 为滑动条添加事件处理器
    backgroundMusicVolumnSlider->addEventListener([=](Ref* sender, cocos2d::ui::Slider::EventType type) {
        if (type == cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED) {
            cocos2d::ui::Slider* backgroundMusicVolumnSlider = dynamic_cast<cocos2d::ui::Slider*>(sender);
            const float percent = backgroundMusicVolumnSlider->getPercent();
            g_backgroundMusicVolumn = percent / 100.0f;
            cocos2d::experimental::AudioEngine::setVolume(g_backgroundMusicSign, g_backgroundMusicVolumn);
        }
        });
    effectVolumnslider->addEventListener([=](Ref* sender, cocos2d::ui::Slider::EventType type) {
        if (type == cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED) {
            cocos2d::ui::Slider* effectVolumnslider = dynamic_cast<cocos2d::ui::Slider*>(sender);
            const float percent = effectVolumnslider->getPercent();
            g_effectMusicVolumn = percent / 100.0f;
            cocos2d::experimental::AudioEngine::setVolume(g_effectMusicSign, g_effectMusicVolumn);
        }
        });

    // 将滑动条添加至场景
    this->addChild(backgroundMusicVolumnSlider);
    this->addChild(effectVolumnslider);

    // 创建按钮
    auto returnMenuButton = HoverButton::create("../Resources/Buttons/SettingsSceneButtons/ReturnMenuDefaultButton.png",
        "../Resources/Buttons/SettingsSceneButtons/ReturnMenuHoverButton.png",
        "../Resources/Buttons/SettingsSceneButtons/ReturnMenuActiveButton.png");
    returnMenuButton->setPosition(Vec2(screenSize.width / 2 + SETTINGS_SCENE_RETURN_MENU_BUTTON_OFFSET_X, screenSize.height / 2 + SETTINGS_SCENE_RETURN_MENU_BUTTON_OFFSET_Y));
    returnMenuButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, MenuScene::createScene(), cocos2d::Color3B::WHITE));
        }
        });
    this->addChild(returnMenuButton);

    // 创建复选框
    auto easyCheckBox = cocos2d::ui::CheckBox::create("../Resources/Layers/CheckBoxNormal.png",
        "../Resources/Layers/CheckBoxNormalPress.png",
        "../Resources/Layers/CheckBoxActive.png",
        "../Resources/Layers/CheckBoxNormalDisable.png",
        "../Resources/Layers/CheckBoxActiveDisable.png");
    auto normalCheckBox = cocos2d::ui::CheckBox::create("../Resources/Layers/CheckBoxNormal.png",
        "../Resources/Layers/CheckBoxNormalPress.png",
        "../Resources/Layers/CheckBoxActive.png",
        "../Resources/Layers/CheckBoxNormalDisable.png",
        "../Resources/Layers/CheckBoxActiveDisable.png");
    auto difficultCheckBox = cocos2d::ui::CheckBox::create("../Resources/Layers/CheckBoxNormal.png",
        "../Resources/Layers/CheckBoxNormalPress.png",
        "../Resources/Layers/CheckBoxActive.png",
        "../Resources/Layers/CheckBoxNormalDisable.png",
        "../Resources/Layers/CheckBoxActiveDisable.png");
    easyCheckBox->setPosition(cocos2d::Vec2(screenSize.width / 2 + SETTINGS_SCENE_EASY_CHECKBOX_OFFSET_X, screenSize.height / 2 + SETTINGS_SCENE_CHECKBOX_OFFSET_Y));
    normalCheckBox->setPosition(cocos2d::Vec2(screenSize.width / 2 + SETTINGS_SCENE_NORMAL_CHECKBOX_OFFSET_X, screenSize.height / 2 + SETTINGS_SCENE_CHECKBOX_OFFSET_Y));
    difficultCheckBox->setPosition(cocos2d::Vec2(screenSize.width / 2 + SETTINGS_SCENE_DIFFICULT_CHECKBOX_OFFSET_X, screenSize.height / 2 + SETTINGS_SCENE_CHECKBOX_OFFSET_Y));

    // 为复选框添加事件处理器
    easyCheckBox->addEventListener([=](Ref* sender, cocos2d::ui::CheckBox::EventType type) {
        if (type == cocos2d::ui::CheckBox::EventType::SELECTED) {
            g_difficulty = Easy;
            normalCheckBox->setSelected(false);
            difficultCheckBox->setSelected(false);
        }
        else if (type == cocos2d::ui::CheckBox::EventType::UNSELECTED) {
            g_difficulty = Normal;
        }
        });
    normalCheckBox->addEventListener([=](Ref* sender, cocos2d::ui::CheckBox::EventType type) {
        if (type == cocos2d::ui::CheckBox::EventType::SELECTED) {
            g_difficulty = Normal;
            easyCheckBox->setSelected(false);
            difficultCheckBox->setSelected(false);
        }
        else if (type == cocos2d::ui::CheckBox::EventType::UNSELECTED) {
            g_difficulty = Normal;
        }
        });
    difficultCheckBox->addEventListener([=](Ref* sender, cocos2d::ui::CheckBox::EventType type) {
        if (type == cocos2d::ui::CheckBox::EventType::SELECTED) {
            g_difficulty = Hard;
            normalCheckBox->setSelected(false);
            easyCheckBox->setSelected(false);
        }
        else if (type == cocos2d::ui::CheckBox::EventType::UNSELECTED) {
            g_difficulty = Normal;
        }
        });

    // 将复选框添加至场景
    if (g_difficulty == Easy) {
        easyCheckBox->setSelected(true);
    }
    else if (g_difficulty == Normal) {
        normalCheckBox->setSelected(true);
    }
    else if (g_difficulty == Hard) {
        difficultCheckBox->setSelected(true);
    }
    this->addChild(easyCheckBox);
    this->addChild(normalCheckBox);
    this->addChild(difficultCheckBox);

    return true;
}