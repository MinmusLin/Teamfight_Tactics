/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     SettingsScene.cpp
 * File Function: SettingsScene���ʵ��
 * Author:        �����ǡ��ּ���
 * Update Date:   2023/12/31
 ****************************************************************/

#include "SettingsScene.h"
#include "Button/HoverButton.h"
#include "MenuScene.h"
#include "AudioEngine.h"
#include "proj.win32/Constant.h"

// �����ռ�
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Label;
using cocos2d::Vec2;

// ��Ƶ��������
int g_backgroundMusicSign = DEFAULT_MUSIC_SIGN;
int g_soundEffectSign = DEFAULT_MUSIC_SIGN;
float g_backgroundMusicVolumn = DEFAULT_MUSIC_VOLUMN;
float g_soundEffectVolumn = DEFAULT_MUSIC_VOLUMN;

// ��Ϸ�Ѷ�
Difficulty g_difficulty = Normal;

// ��Ƶ���淽��
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

// ��������
Scene* SettingsScene::createScene()
{
    auto scene = Scene::create();
    auto layer = SettingsScene::create();
    scene->addChild(layer);
    return scene;
}

// ��ʼ������
bool SettingsScene::init()
{
    // ��������
    if (!Scene::init()) {
        return false;
    }

    // ��������
    audioPlayer("../Resources/Music/SettingsScene_Starlight.mp3", true);

    // ���ر���
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/SettingsScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // ����������
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

    // Ϊ����������¼�������
    backgroundMusicVolumnSlider->addEventListener([=](Ref* sender, cocos2d::ui::Slider::EventType type) {
        if (type == cocos2d::ui::Slider::EventType::ON_SLIDEBALL_DOWN) {
            // ���ص����Ч
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
            // ���ص����Ч
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
        }
        if (type == cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED) {
            const cocos2d::ui::Slider* effectVolumnslider = dynamic_cast<cocos2d::ui::Slider*>(sender);
            const float percent = effectVolumnslider->getPercent();
            g_soundEffectVolumn = percent / 100.0f;
            cocos2d::experimental::AudioEngine::setVolume(g_soundEffectSign, g_soundEffectVolumn);
        }
        });

    // �����������������
    this->addChild(backgroundMusicVolumnSlider);
    this->addChild(effectVolumnslider);

    // ������ť
    auto returnMenuButton = HoverButton::create("../Resources/Buttons/SettingsSceneButtons/ReturnMenuDefaultButton.png",
        "../Resources/Buttons/SettingsSceneButtons/ReturnMenuHoverButton.png",
        "../Resources/Buttons/SettingsSceneButtons/ReturnMenuActiveButton.png");
    returnMenuButton->setPosition(Vec2(screenSize.width / 2 + SETTINGS_SCENE_RETURN_MENU_BUTTON_OFFSET_X, screenSize.height / 2 + SETTINGS_SCENE_RETURN_MENU_BUTTON_OFFSET_Y));
    returnMenuButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            // ���ص����Ч
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, MenuScene::createScene(), cocos2d::Color3B::WHITE));
        }
        });
    this->addChild(returnMenuButton);

    // ������ѡ��
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

    // Ϊ��ѡ������¼�������
    easyCheckBox->addEventListener([=](Ref* sender, cocos2d::ui::CheckBox::EventType type) {
        if (type == cocos2d::ui::CheckBox::EventType::SELECTED) {
            // ���ص����Ч
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

            g_difficulty = Easy;
            normalCheckBox->setSelected(false);
            difficultCheckBox->setSelected(false);
        }
        else if (type == cocos2d::ui::CheckBox::EventType::UNSELECTED) {
            // ���ص����Ч
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

            easyCheckBox->setSelected(true);
        }
        });
    normalCheckBox->addEventListener([=](Ref* sender, cocos2d::ui::CheckBox::EventType type) {
        if (type == cocos2d::ui::CheckBox::EventType::SELECTED) {
            // ���ص����Ч
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

            g_difficulty = Normal;
            easyCheckBox->setSelected(false);
            difficultCheckBox->setSelected(false);
        }
        else if (type == cocos2d::ui::CheckBox::EventType::UNSELECTED) {
            // ���ص����Ч
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

            normalCheckBox->setSelected(true);
        }
        });
    difficultCheckBox->addEventListener([=](Ref* sender, cocos2d::ui::CheckBox::EventType type) {
        CCLOG("%d", g_difficulty);
        if (type == cocos2d::ui::CheckBox::EventType::SELECTED) {
            // ���ص����Ч
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

            g_difficulty = Hard;
            normalCheckBox->setSelected(false);
            easyCheckBox->setSelected(false);
        }
        else if (type == cocos2d::ui::CheckBox::EventType::UNSELECTED) {
            // ���ص����Ч
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

            difficultCheckBox->setSelected(true);
        }
        });

    // ����ѡ�����������
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