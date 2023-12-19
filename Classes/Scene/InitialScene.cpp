/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     InitialScene.cpp
 * File Function: InitialScene类的实现
 * Author:        林继申
 * Update Date:   2023/12/19
 ****************************************************************/

#include "InitialScene.h"
#include "MenuScene.h"
#include "Button/HoverButton.h"
#include "GBKToUTF8.h"
#include "proj.win32/Constant.h"

USING_NS_CC;

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
    const auto screenSize = Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/InitialScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // 创建文本框
    auto textField = ui::TextField::create(GBKToUTF8::getString("请输入您的游戏昵称"), "../Resources/Fonts/FZZGY_J_EB.ttf", INITIAL_SCENE_FONT_SIZE);
    textField->setPosition(Vec2(screenSize.width / 2 + INITIAL_SCENE_LABLES_OFFSET_X, screenSize.height / 2 + INITIAL_SCENE_TEXTFIELD_OFFSET_Y));
    textField->setMaxLength(NICKNAME_MAX_LENGTH);
    textField->setMaxLengthEnabled(true);
    textField->setTextColor(Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    this->addChild(textField);

    // 创建标签
    auto promptLabel = Label::createWithTTF("", "../Resources/Fonts/FZZGY_J_EB.ttf", INITIAL_SCENE_FONT_SIZE);
    promptLabel->setPosition(Vec2(screenSize.width / 2 + INITIAL_SCENE_LABLES_OFFSET_X, screenSize.height / 2 + INITIAL_SCENE_PROMPT_LABLE_OFFSET_Y));
    promptLabel->setTextColor(Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    this->addChild(promptLabel);

    // 为文本框添加事件监听器
    textField->addEventListener([promptLabel](Ref* sender, ui::TextField::EventType type) {
        if (type == ui::TextField::EventType::INSERT_TEXT || type == ui::TextField::EventType::DELETE_BACKWARD) {
            auto textField = dynamic_cast<ui::TextField*>(sender);
            std::string nickname = textField->getString();
            std::string text = GBKToUTF8::getString("欢迎你！") + nickname;
            promptLabel->setString(text);
        }
        });

    // 创建按钮
    auto startButton = HoverButton::create("../Resources/Buttons/StartDefaultButton.png",
        "../Resources/Buttons/StartHoverButton.png",
        "../Resources/Buttons/StartActiveButton.png");

    // 设置按钮位置
    startButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + INITIAL_SCENE_BUTTON_OFFSET_Y));

    // 创建一个提示
    auto nameLabel = Label::createWithTTF(GBKToUTF8::getString("游戏昵称不能为空"), "../Resources/Fonts/FZZGY_J_EB.ttf", INITIAL_SCENE_FONT_SIZE);
    nameLabel->setPosition(Vec2(screenSize.width / 2 + INITIAL_SCENE_LABLES_OFFSET_X, screenSize.height / 2 + INITIAL_SCENE_NAME_LABLE_OFFSET_Y));
    nameLabel->setVisible(false);
    nameLabel->setTextColor(Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    this->addChild(nameLabel);

    // 为按钮添加事件处理器
    startButton->addTouchEventListener([this, textField, nameLabel](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            std::string nickname = textField->getString();
            if (!nickname.empty()) {
                UserDefault::getInstance()->setStringForKey("PlayerName", nickname);
                UserDefault::getInstance()->flush();
                Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, MenuScene::createScene(), Color3B::WHITE));
            }
            else {
                nameLabel->setVisible(true);
                this->scheduleOnce([nameLabel](float dt) {nameLabel->setVisible(false); }, PROMPT_MESSAGE_DURATION, "HidePromptLabel");
            }
        }
        });

    // 将按钮添加到场景中
    this->addChild(startButton);

    return true;
}