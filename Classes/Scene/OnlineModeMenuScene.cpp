/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OnlineModeMenuScene.cpp
 * File Function: OnlineModeMenuScene���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/26
 ****************************************************************/

#include <iostream>
#include "OnlineModeMenuScene.h"
#include "Control/OnlineModeControl.h"
#include "Button/HoverButton.h"
#include "MenuScene.h"
#include "proj.win32/Constant.h"
#include "GBKToUTF8/GBKToUTF8.h"

// �����ռ�
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Label;
using cocos2d::Vec2;

// ����ģʽ��Ϸ������
OnlineModeControl* g_onlineModeControl = nullptr;

// ��������
Scene* OnlineModeMenuScene::createScene()
{
    auto scene = Scene::create();
    auto layer = OnlineModeMenuScene::create();
    scene->addChild(layer);
    return scene;
}

// ��ʼ������
bool OnlineModeMenuScene::init()
{
    // ��������
    if (!Scene::init()) {
        return false;
    }
    
    // ���ر���
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/OnlineModeMenuScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // ������ť
    auto joinRoomButton = HoverButton::create("../Resources/Buttons/OnlineModeMenuSceneButtons/JoinRoomDefaultButton.png",
        "../Resources/Buttons/OnlineModeMenuSceneButtons/JoinRoomHoverButton.png",
        "../Resources/Buttons/OnlineModeMenuSceneButtons/JoinRoomActiveButton.png");
    auto returnMenuButton = HoverButton::create("../Resources/Buttons/OnlineModeMenuSceneButtons/ReturnMenuDefaultButton.png",
        "../Resources/Buttons/OnlineModeMenuSceneButtons/ReturnMenuHoverButton.png",
        "../Resources/Buttons/OnlineModeMenuSceneButtons/ReturnMenuActiveButton.png");

    // ���ð�ťλ��
    joinRoomButton->setPosition(Vec2(screenSize.width / 2 - ONLINE_MODE_MENU_SCENE_BUTTON_OFFSET_X, screenSize.height / 2 + ONLINE_MODE_MENU_SCENE_BUTTON_OFFSET_Y));
    returnMenuButton->setPosition(Vec2(screenSize.width / 2 + ONLINE_MODE_MENU_SCENE_BUTTON_OFFSET_X, screenSize.height / 2 + ONLINE_MODE_MENU_SCENE_BUTTON_OFFSET_Y));

    // ���� IPv4 �ı���
    auto ipv4TextField = cocos2d::ui::TextField::create(GBKToUTF8::getString("����������� IPv4 ��ַ"), "../Resources/Fonts/FangZhengZhaoGeYuan.ttf", ONLINE_MODE_MENU_SCENE_FONT_SIZE);
    ipv4TextField->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + ONLINE_MODE_MENU_SCENE_IPV4_TEXTFIELD_OFFSET_Y));
    ipv4TextField->setMaxLength(IPV4_ADDRESS_MAX_LENGTH);
    ipv4TextField->setMaxLengthEnabled(true);
    ipv4TextField->setTextColor(cocos2d::Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    this->addChild(ipv4TextField);

    // �����˿��ı���
    auto portTextField = cocos2d::ui::TextField::create(GBKToUTF8::getString("������������˿�"), "../Resources/Fonts/FangZhengZhaoGeYuan.ttf", ONLINE_MODE_MENU_SCENE_FONT_SIZE);
    portTextField->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + ONLINE_MODE_MENU_SCENE_PORT_TEXTFIELD_OFFSET_Y));
    portTextField->setMaxLength(PORT_MAX_LENGTH);
    portTextField->setMaxLengthEnabled(true);
    portTextField->setTextColor(cocos2d::Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    this->addChild(portTextField);

    // ����һ����ʾ��ǩ
    auto promptLabel = Label::createWithTTF("", "../Resources/Fonts/FangZhengZhaoGeYuan.ttf", ONLINE_MODE_MENU_SCENE_FONT_SIZE);
    promptLabel->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + ONLINE_MODE_MENU_SCENE_PROMPT_LABEL_OFFSET_Y));
    promptLabel->setVisible(false);
    promptLabel->setTextColor(cocos2d::Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    this->addChild(promptLabel);

    // ��������������ʧ����ʾ
    auto connectionFailedPrompt = Sprite::create("../Resources/Scenes/ServerConnectionFailedPrompt.png");
    connectionFailedPrompt->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    connectionFailedPrompt->setVisible(false);
    this->addChild(connectionFailedPrompt, 1);

    // Ϊ��ť����¼�������
    joinRoomButton->addTouchEventListener([this, ipv4TextField, portTextField, promptLabel, connectionFailedPrompt](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            std::string ipv4 = ipv4TextField->getString();
            std::string port = portTextField->getString();
            if (ipv4.empty() && port.empty()) {
                promptLabel->setString(GBKToUTF8::getString("������ IPv4 ��ַ�Ͷ˿ڲ���Ϊ��"));
                promptLabel->setVisible(true);
                this->scheduleOnce([promptLabel](float dt) {promptLabel->setVisible(false);
                    }, PROMPT_MESSAGE_DURATION, "IPv4AndPortHidePromptLabel");
            }
            else if (ipv4.empty() && !port.empty()) {
                promptLabel->setString(GBKToUTF8::getString("������ IPv4 ��ַ����Ϊ��"));
                promptLabel->setVisible(true);
                this->scheduleOnce([promptLabel](float dt) {promptLabel->setVisible(false);
                    }, PROMPT_MESSAGE_DURATION, "IPv4HidePromptLabel");
            }
            else if (!ipv4.empty() && port.empty()) {
                promptLabel->setString(GBKToUTF8::getString("�������˿ڲ���Ϊ��"));
                promptLabel->setVisible(true);
                this->scheduleOnce([promptLabel](float dt) {promptLabel->setVisible(false);
                    }, PROMPT_MESSAGE_DURATION, "PortHidePromptLabel");
            }
            else {
                try {
                    g_onlineModeControl = new OnlineModeControl(ipv4, port); // TODO: Ŀǰδ���� delete
                }
                catch (const std::bad_alloc& e) {
                    std::cerr << "Memory allocation failed: " << e.what() << std::endl;
                    throw;
                }
                ConnectionStatus connectionStatus = g_onlineModeControl->initializeClient();
                if (connectionStatus == ConnectionError) {
                    connectionFailedPrompt->setVisible(true);
                    this->scheduleOnce([connectionFailedPrompt](float dt) {connectionFailedPrompt->setVisible(false);
                        }, CONNECTION_FAILED_PROMPT_MESSAGE_DURATION, "ConnectionErrorHidePromptLabel");
                    delete g_onlineModeControl;
                    g_onlineModeControl = nullptr;
                }
                else if (connectionStatus == ConnectionRefused) {
                    promptLabel->setString(GBKToUTF8::getString("�������ﵽ�����������"));
                    promptLabel->setVisible(true);
                    this->scheduleOnce([promptLabel](float dt) {promptLabel->setVisible(false);
                        }, PROMPT_MESSAGE_DURATION, "ConnectionRefusedHidePromptLabel");
                    delete g_onlineModeControl;
                    g_onlineModeControl = nullptr;
                }
                else {
                    // TODO
                }
            }
        }
        });
    returnMenuButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, MenuScene::createScene(), cocos2d::Color3B::WHITE));
        }
        });

    // ����ť��ӵ�������
    this->addChild(joinRoomButton);
    this->addChild(returnMenuButton);

    return true;
}