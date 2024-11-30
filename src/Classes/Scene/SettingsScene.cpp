/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     SettingsScene.cpp
 * File Function: SettingsScene类的实现
 * Author:        刘淑仪、林继申
 * Update Date:   2023/12/31
 ****************************************************************/

#include "SettingsScene.h"
#include "Button/HoverButton.h"
#include "MenuScene.h"
#include "AudioEngine.h"
#include "proj.win32/Constant.h"

// 命名空间
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Label;
using cocos2d::Vec2;

// 音频引擎设置
int g_backgroundMusicSign = DEFAULT_MUSIC_SIGN;
int g_soundEffectSign = DEFAULT_MUSIC_SIGN;
float g_backgroundMusicVolumn = DEFAULT_MUSIC_VOLUMN;
float g_soundEffectVolumn = DEFAULT_MUSIC_VOLUMN;

// 游戏难度
Difficulty g_difficulty = Normal;

// 音频引擎方法
void audioPlayer(const std::string& audioPath, bool isLoop)
{
    if (isLoop) {
        if (g_backgroundMusicSign != DEFAULT_MUSIC_SIGN) {
            cocos2d::experimental::AudioEngine::stop(g_backgroundMusicSign);
        }
        g_backgroundMusicSign = cocos2d::experimental::AudioEngine::play2d(audioPath, isLoop);
        cocos2d::experimental::AudioEngine::setVolume(g_backgroundMusicSign, g_backgroundMusicVolumn);
    }
    else {
        g_soundEffectSign = cocos2d::experimental::AudioEngine::play2d(audioPath, isLoop);
        cocos2d::experimental::AudioEngine::setVolume(g_soundEffectSign, g_soundEffectVolumn);
    }
}

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

    // 加载音乐
    audioPlayer("../Resources/Music/SettingsScene_Starlight.mp3", true);

    // 加载背景
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/SettingsScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // 创建滑动条
    auto backgroundMusicVolumnSlider = cocos2d::ui::Slider::create();
    backgroundMusicVolumnSlider->loadBarTexture("../Resources/ImageElements/SliderBackground.png");
    backgroundMusicVolumnSlider->loadSlidBallTextures("../Resources/ImageElements/SliderNodeNormal.png",
        "../Resources/ImageElements/SliderNodePress.png",
        "../Resources/ImageElements/SliderNodeDisable.png");
    backgroundMusicVolumnSlider->loadProgressBarTexture("../Resources/ImageElements/SliderBar.png");
    backgroundMusicVolumnSlider->setPosition(cocos2d::Vec2(screenSize.width / 2 + SETTINGS_SCENE_SLIDER_OFFSET_X, screenSize.height / 2 + SETTINGS_SCENE_BGMSLIDER_OFFSET_Y));
    backgroundMusicVolumnSlider->setPercent(g_backgroundMusicVolumn * 100);
    auto effectVolumnslider = cocos2d::ui::Slider::create();
    effectVolumnslider->loadBarTexture("../Resources/ImageElements/SliderBackground.png");
    effectVolumnslider->loadSlidBallTextures("../Resources/ImageElements/SliderNodeNormal.png",
        "../Resources/ImageElements/SliderNodePress.png",
        "../Resources/ImageElements/SliderNodeDisable.png");
    effectVolumnslider->loadProgressBarTexture("../Resources/ImageElements/SliderBar.png");
    effectVolumnslider->setPosition(cocos2d::Vec2(screenSize.width / 2 + SETTINGS_SCENE_SLIDER_OFFSET_X, screenSize.height / 2 + SETTINGS_SCENE_EFFSLIDER_OFFSET_Y));
    effectVolumnslider->setPercent(g_soundEffectVolumn * 100);

    // 为滑动条添加事件处理器
    backgroundMusicVolumnSlider->addEventListener([=](Ref* sender, cocos2d::ui::Slider::EventType type) {
        if (type == cocos2d::ui::Slider::EventType::ON_SLIDEBALL_DOWN) {
            // 加载点击音效
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
        }
        if (type == cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED) {
            const cocos2d::ui::Slider* backgroundMusicVolumnSlider = dynamic_cast<cocos2d::ui::Slider*>(sender);
            const float percent = backgroundMusicVolumnSlider->getPercent();
            g_backgroundMusicVolumn = percent / 100.0f;
            cocos2d::experimental::AudioEngine::setVolume(g_backgroundMusicSign, g_backgroundMusicVolumn);
        }
        });
    effectVolumnslider->addEventListener([=](Ref* sender, cocos2d::ui::Slider::EventType type) {
        if (type == cocos2d::ui::Slider::EventType::ON_SLIDEBALL_DOWN) {
            // 加载点击音效
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
        }
        if (type == cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED) {
            const cocos2d::ui::Slider* effectVolumnslider = dynamic_cast<cocos2d::ui::Slider*>(sender);
            const float percent = effectVolumnslider->getPercent();
            g_soundEffectVolumn = percent / 100.0f;
            cocos2d::experimental::AudioEngine::setVolume(g_soundEffectSign, g_soundEffectVolumn);
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
            // 加载点击音效
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, MenuScene::createScene(), cocos2d::Color3B::WHITE));
        }
        });
    this->addChild(returnMenuButton);

    // 创建复选框
    auto easyCheckBox = cocos2d::ui::CheckBox::create("../Resources/ImageElements/CheckBoxNormal.png",
        "../Resources/ImageElements/CheckBoxNormalPress.png",
        "../Resources/ImageElements/CheckBoxActive.png",
        "../Resources/ImageElements/CheckBoxNormalDisable.png",
        "../Resources/ImageElements/CheckBoxActiveDisable.png");
    auto normalCheckBox = cocos2d::ui::CheckBox::create("../Resources/ImageElements/CheckBoxNormal.png",
        "../Resources/ImageElements/CheckBoxNormalPress.png",
        "../Resources/ImageElements/CheckBoxActive.png",
        "../Resources/ImageElements/CheckBoxNormalDisable.png",
        "../Resources/ImageElements/CheckBoxActiveDisable.png");
    auto difficultCheckBox = cocos2d::ui::CheckBox::create("../Resources/ImageElements/CheckBoxNormal.png",
        "../Resources/ImageElements/CheckBoxNormalPress.png",
        "../Resources/ImageElements/CheckBoxActive.png",
        "../Resources/ImageElements/CheckBoxNormalDisable.png",
        "../Resources/ImageElements/CheckBoxActiveDisable.png");
    easyCheckBox->setPosition(cocos2d::Vec2(screenSize.width / 2 + SETTINGS_SCENE_EASY_CHECKBOX_OFFSET_X, screenSize.height / 2 + SETTINGS_SCENE_CHECKBOX_OFFSET_Y));
    normalCheckBox->setPosition(cocos2d::Vec2(screenSize.width / 2 + SETTINGS_SCENE_NORMAL_CHECKBOX_OFFSET_X, screenSize.height / 2 + SETTINGS_SCENE_CHECKBOX_OFFSET_Y));
    difficultCheckBox->setPosition(cocos2d::Vec2(screenSize.width / 2 + SETTINGS_SCENE_DIFFICULT_CHECKBOX_OFFSET_X, screenSize.height / 2 + SETTINGS_SCENE_CHECKBOX_OFFSET_Y));

    // 为复选框添加事件处理器
    easyCheckBox->addEventListener([=](Ref* sender, cocos2d::ui::CheckBox::EventType type) {
        if (type == cocos2d::ui::CheckBox::EventType::SELECTED) {
            // 加载点击音效
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

            g_difficulty = Easy;
            normalCheckBox->setSelected(false);
            difficultCheckBox->setSelected(false);
        }
        else if (type == cocos2d::ui::CheckBox::EventType::UNSELECTED) {
            // 加载点击音效
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

            easyCheckBox->setSelected(true);
        }
        });
    normalCheckBox->addEventListener([=](Ref* sender, cocos2d::ui::CheckBox::EventType type) {
        if (type == cocos2d::ui::CheckBox::EventType::SELECTED) {
            // 加载点击音效
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

            g_difficulty = Normal;
            easyCheckBox->setSelected(false);
            difficultCheckBox->setSelected(false);
        }
        else if (type == cocos2d::ui::CheckBox::EventType::UNSELECTED) {
            // 加载点击音效
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

            normalCheckBox->setSelected(true);
        }
        });
    difficultCheckBox->addEventListener([=](Ref* sender, cocos2d::ui::CheckBox::EventType type) {
        CCLOG("%d", g_difficulty);
        if (type == cocos2d::ui::CheckBox::EventType::SELECTED) {
            // 加载点击音效
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

            g_difficulty = Hard;
            normalCheckBox->setSelected(false);
            easyCheckBox->setSelected(false);
        }
        else if (type == cocos2d::ui::CheckBox::EventType::UNSELECTED) {
            // 加载点击音效
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

            difficultCheckBox->setSelected(true);
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