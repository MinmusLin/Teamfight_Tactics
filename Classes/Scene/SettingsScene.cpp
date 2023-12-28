/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     SettingsScene.cpp
 * File Function: SettingsScene���ʵ��
 * Author:        �����ǡ��ּ���
 * Update Date:   2023/12/28
 ****************************************************************/

#include "SettingsScene.h"
#include "proj.win32/Constant.h"
#include "AudioEngine.h"
#include "Button/HoverButton.h"
#include "MenuScene.h"

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
    if (g_backgroundMusicSign != DEFAULT_MUSIC_SIGN) {
        cocos2d::experimental::AudioEngine::stop(g_backgroundMusicSign);
    }
    g_backgroundMusicSign = cocos2d::experimental::AudioEngine::play2d("../Resources/Music/BackgroundMusic/SettingsScene_Starlight.mp3", true);
    cocos2d::experimental::AudioEngine::setVolume(g_backgroundMusicSign, g_backgroundMusicVolumn);

    // ���ر���
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/SettingsScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // ����������
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

    // Ϊ����������¼�������
    backgroundMusicVolumnSlider->addEventListener([=](Ref* sender, cocos2d::ui::Slider::EventType type) {
        if (type == cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED) {
            cocos2d::ui::Slider* backgroundMusicVolumnSlider = dynamic_cast<cocos2d::ui::Slider*>(sender);
            float percent = backgroundMusicVolumnSlider->getPercent();
            g_backgroundMusicVolumn = percent / 100.0f;
            cocos2d::experimental::AudioEngine::setVolume(g_backgroundMusicSign, g_backgroundMusicVolumn);
        }
        });
    effectVolumnslider->addEventListener([=](Ref* sender, cocos2d::ui::Slider::EventType type) {
        if (type == cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED) {
            cocos2d::ui::Slider* effectVolumnslider = dynamic_cast<cocos2d::ui::Slider*>(sender);
            float percent = effectVolumnslider->getPercent();
            g_effectMusicVolumn = percent / 100.0f;
            cocos2d::experimental::AudioEngine::setVolume(g_effectMusicSign, g_effectMusicVolumn);
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
            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, MenuScene::createScene(), cocos2d::Color3B::WHITE));
        }
        });
    this->addChild(returnMenuButton);

    // ������ѡ��
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

    // Ϊ��ѡ������¼�������
    easyCheckBox->addEventListener([=](Ref* sender, cocos2d::ui::CheckBox::EventType type) {
        if (type == cocos2d::ui::CheckBox::EventType::SELECTED) {
            // TODO: ����ѡ�򱻹�ѡʱ���߼�
            normalCheckBox->setSelected(false);
            difficultCheckBox->setSelected(false);
        }
        else if (type == cocos2d::ui::CheckBox::EventType::UNSELECTED) {
            // TODO: ����ѡ��ȡ����ѡʱ���߼�
        }
        });
    normalCheckBox->addEventListener([=](Ref* sender, cocos2d::ui::CheckBox::EventType type) {
        if (type == cocos2d::ui::CheckBox::EventType::SELECTED) {
            // TODO: ����ѡ�򱻹�ѡʱ���߼�
            easyCheckBox->setSelected(false);
            difficultCheckBox->setSelected(false);
        }
        else if (type == cocos2d::ui::CheckBox::EventType::UNSELECTED) {
            // TODO: ����ѡ��ȡ����ѡʱ���߼�
        }
        });
    difficultCheckBox->addEventListener([=](Ref* sender, cocos2d::ui::CheckBox::EventType type) {
        if (type == cocos2d::ui::CheckBox::EventType::SELECTED) {
            // TODO: ����ѡ�򱻹�ѡʱ���߼�
            normalCheckBox->setSelected(false);
            easyCheckBox->setSelected(false);
        }
        else if (type == cocos2d::ui::CheckBox::EventType::UNSELECTED) {
            // TODO: ����ѡ��ȡ����ѡʱ���߼�
        }
        });

    // ����ѡ�����������
    this->addChild(easyCheckBox);
    this->addChild(normalCheckBox);
    this->addChild(difficultCheckBox);

    return true;
}