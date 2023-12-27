/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     InitialScene.cpp
 * File Function: InitialScene类的实现
 * Author:        林继申
 * Update Date:   2023/12/27
 * License:       MIT License
 ****************************************************************/

#include "InitialScene.h"
#include "MenuScene.h"
#include "Button/HoverButton.h"
#include "GBKToUTF8/GBKToUTF8.h"
#include "proj.win32/Constant.h"

// 命名空间
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Label;
using cocos2d::Vec2;

// 创建场景
Scene* InitialScene::createScene()
{
    auto scene = Scene::create();
    auto layer = InitialScene::create();
    scene->addChild(layer);
    return scene;
}

// 初始化场景
bool InitialScene::init()
{
    // 创建场景
    if (!Scene::init()) {
        return false;
    }

    // 加载背景
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/InitialScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // 创建文本框
    auto textField = cocos2d::ui::TextField::create(GBKToUTF8::getString("请输入您的游戏昵称"), "../Resources/Fonts/FangZhengZhaoGeYuan.ttf", INITIAL_SCENE_FONT_SIZE);
    textField->setPosition(Vec2(screenSize.width / 2 + INITIAL_SCENE_LABELS_OFFSET_X, screenSize.height / 2 + INITIAL_SCENE_TEXTFIELD_OFFSET_Y));
    textField->setMaxLength(NICKNAME_MAX_LENGTH);
    textField->setMaxLengthEnabled(true);
    textField->setTextColor(cocos2d::Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    this->addChild(textField);

    // 创建标签
    auto promptLabel = Label::createWithTTF("", "../Resources/Fonts/FangZhengZhaoGeYuan.ttf", INITIAL_SCENE_FONT_SIZE);
    promptLabel->setPosition(Vec2(screenSize.width / 2 + INITIAL_SCENE_LABELS_OFFSET_X, screenSize.height / 2 + INITIAL_SCENE_PROMPT_LABEL_OFFSET_Y));
    promptLabel->setTextColor(cocos2d::Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    this->addChild(promptLabel);

    // 为文本框添加事件监听器
    textField->addEventListener([promptLabel](Ref* sender, cocos2d::ui::TextField::EventType type) {
        if (type == cocos2d::ui::TextField::EventType::INSERT_TEXT || type == cocos2d::ui::TextField::EventType::DELETE_BACKWARD) {
            auto textField = dynamic_cast<cocos2d::ui::TextField*>(sender);
            std::string nickname = textField->getString();
            std::string text = GBKToUTF8::getString("欢迎你！") + nickname;
            promptLabel->setString(text);
        }
        });

    // 创建按钮
    auto startButton = HoverButton::create("../Resources/Buttons/InitialSceneButtons/StartDefaultButton.png",
        "../Resources/Buttons/InitialSceneButtons/StartHoverButton.png",
        "../Resources/Buttons/InitialSceneButtons/StartActiveButton.png");

    // 设置按钮位置
    startButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + INITIAL_SCENE_BUTTON_OFFSET_Y));

    // 创建一个提示
    auto nameLabel = Label::createWithTTF(GBKToUTF8::getString("游戏昵称不能为空"), "../Resources/Fonts/FangZhengZhaoGeYuan.ttf", INITIAL_SCENE_FONT_SIZE);
    nameLabel->setPosition(Vec2(screenSize.width / 2 + INITIAL_SCENE_LABELS_OFFSET_X, screenSize.height / 2 + INITIAL_SCENE_NAME_LABEL_OFFSET_Y));
    nameLabel->setVisible(false);
    nameLabel->setTextColor(cocos2d::Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    this->addChild(nameLabel);

    // 为按钮添加事件处理器
    startButton->addTouchEventListener([this, textField, nameLabel](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            std::string nickname = textField->getString();
            if (!nickname.empty()) {
                cocos2d::UserDefault::getInstance()->setStringForKey("PlayerName", nickname); // PlayerName 内部存储编码为 UTF-8，无需调用 GBKToUTF8 单例方法
                cocos2d::UserDefault::getInstance()->flush();
                cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, MenuScene::createScene(), cocos2d::Color3B::WHITE));
            }
            else {
                nameLabel->setVisible(true);
                this->scheduleOnce([nameLabel](float dt) {
                    nameLabel->setVisible(false);
                    }, PROMPT_MESSAGE_DURATION, "HidePromptLabel");
            }
        }
        });

    // 将按钮添加到场景中
    this->addChild(startButton);

    return true;
}