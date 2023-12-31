/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     InitialScene.cpp
 * File Function: InitialScene类的实现
 * Author:        林继申、刘淑仪
 * Update Date:   2023/12/31
 * License:       MIT License
 ****************************************************************/

#include <locale>
#include <codecvt>
#include "InitialScene.h"
#include "SelectionScene.h"
#include "Button/HoverButton.h"
#include "proj.win32/Constant.h"
#include "proj.win32/AudioPlayer.h"

// 命名空间
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Label;
using cocos2d::Vec2;

// 玩家昵称
std::string g_PlayerName = "";

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
    auto textField = cocos2d::ui::TextField::create(u8"请输入您的游戏昵称", "../Resources/Fonts/DingDingJinBuTi.ttf", INITIAL_SCENE_FONT_SIZE);
    textField->setPosition(Vec2(screenSize.width / 2 + INITIAL_SCENE_LABELS_OFFSET_X, screenSize.height / 2 + INITIAL_SCENE_TEXTFIELD_OFFSET_Y));
    textField->setMaxLength(NICKNAME_MAX_LENGTH);
    textField->setMaxLengthEnabled(true);
    textField->setTextColor(cocos2d::Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    this->addChild(textField);

    // 创建标签
    auto promptLabel = Label::createWithTTF("", "../Resources/Fonts/DingDingJinBuTi.ttf", INITIAL_SCENE_FONT_SIZE);
    promptLabel->setPosition(Vec2(screenSize.width / 2 + INITIAL_SCENE_LABELS_OFFSET_X, screenSize.height / 2 + INITIAL_SCENE_PROMPT_LABEL_OFFSET_Y));
    promptLabel->setTextColor(cocos2d::Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    this->addChild(promptLabel);

    // 为文本框添加事件监听器
    textField->addEventListener([promptLabel](Ref* sender, cocos2d::ui::TextField::EventType type) {
        if (type == cocos2d::ui::TextField::EventType::INSERT_TEXT || type == cocos2d::ui::TextField::EventType::DELETE_BACKWARD) {
            auto textField = dynamic_cast<cocos2d::ui::TextField*>(sender);
            std::string nickname = textField->getString();
            std::string text = u8"欢迎你！" + nickname;
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
    auto nameLabel = Label::createWithTTF("", "../Resources/Fonts/DingDingJinBuTi.ttf", INITIAL_SCENE_FONT_SIZE);
    nameLabel->setPosition(Vec2(screenSize.width / 2 + INITIAL_SCENE_LABELS_OFFSET_X, screenSize.height / 2 + INITIAL_SCENE_NAME_LABEL_OFFSET_Y));
    nameLabel->setVisible(false);
    nameLabel->setTextColor(cocos2d::Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    this->addChild(nameLabel);

    // 为按钮添加事件处理器
    startButton->addTouchEventListener([this, textField, nameLabel](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            // 加载点击音效
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

            std::string nickname = textField->getString();
            if (nickname.empty()) {
                nameLabel->setString(u8"游戏昵称不能为空");
                nameLabel->setVisible(true);
                this->scheduleOnce([nameLabel](float dt) {
                    nameLabel->setVisible(false);
                    }, PROMPT_MESSAGE_DURATION, "HideEmptyPromptLabel");
            }
            else if (!isValidString(nickname)) {
                nameLabel->setString(u8"游戏昵称存在非法字符");
                nameLabel->setVisible(true);
                this->scheduleOnce([nameLabel](float dt) {
                    nameLabel->setVisible(false);
                    }, PROMPT_MESSAGE_DURATION, "HideInvalidPromptLabel");
            }
            else {
                g_PlayerName = nickname; // g_PlayerName 内部存储编码为 UTF-8
                cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, SelectionScene::createScene(), cocos2d::Color3B::WHITE));
            }
        }
        });

    // 将按钮添加到场景中
    this->addChild(startButton);

    return true;
}

// 检查字符合法性
bool InitialScene::isValidCharacter(const char32_t ch)
{
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
        return true;
    }
    if (ch >= '0' && ch <= '9') {
        return true;
    }
    if ((ch >= 0x4E00 && ch <= 0x9FFF) || (ch >= 0x3400 && ch <= 0x4DBF)) {
        return true;
    }
    return false;
}

// 检查字符串合法性
bool InitialScene::isValidString(const std::string& str)
{
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    std::u32string utf32str = converter.from_bytes(str);
    for (auto ch : utf32str) {
        if (!isValidCharacter(ch)) {
            return false;
        }
    }
    return true;
}