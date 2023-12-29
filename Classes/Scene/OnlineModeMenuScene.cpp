/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OnlineModeMenuScene.cpp
 * File Function: OnlineModeMenuScene���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/29
 * License:       MIT License
 ****************************************************************/

#include <iostream>
#include <cstring>
#include "OnlineModeMenuScene.h"
#include "Scene/OnlineModePreparationScene.h"
#include "Control/OnlineModeControl.h"
#include "Button/HoverButton.h"
#include "MenuScene.h"
#include "proj.win32/Constant.h"

// �����ռ�
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Label;
using cocos2d::Vec2;

// ����ǳ�
extern std::string g_PlayerName;

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
    auto startGameButton = HoverButton::create("../Resources/Buttons/OnlineModeMenuSceneButtons/startGameDefaultButton.png",
        "../Resources/Buttons/OnlineModeMenuSceneButtons/startGameHoverButton.png",
        "../Resources/Buttons/OnlineModeMenuSceneButtons/startGameActiveButton.png");

    // ���ð�ťλ��
    joinRoomButton->setPosition(Vec2(screenSize.width / 2 - ONLINE_MODE_MENU_SCENE_BUTTON_OFFSET_X, screenSize.height / 2 + ONLINE_MODE_MENU_SCENE_BUTTON_OFFSET_Y));
    returnMenuButton->setPosition(Vec2(screenSize.width / 2 + ONLINE_MODE_MENU_SCENE_BUTTON_OFFSET_X, screenSize.height / 2 + ONLINE_MODE_MENU_SCENE_BUTTON_OFFSET_Y));
    startGameButton->setPosition(Vec2(screenSize.width / 2 - ONLINE_MODE_MENU_SCENE_BUTTON_OFFSET_X, screenSize.height / 2 + ONLINE_MODE_MENU_SCENE_BUTTON_OFFSET_Y));

    // ���� IPv4 �ı���
    auto ipv4TextField = cocos2d::ui::TextField::create(u8"����������� IPv4 ��ַ", "../Resources/Fonts/FangZhengZhaoGeYuan.ttf", ONLINE_MODE_MENU_SCENE_FONT_SIZE);
    ipv4TextField->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + ONLINE_MODE_MENU_SCENE_IPV4_TEXTFIELD_OFFSET_Y));
    ipv4TextField->setMaxLength(IPV4_ADDRESS_MAX_LENGTH);
    ipv4TextField->setMaxLengthEnabled(true);
    ipv4TextField->setTextColor(cocos2d::Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    this->addChild(ipv4TextField);

    // �����˿��ı���
    auto portTextField = cocos2d::ui::TextField::create(u8"������������˿�", "../Resources/Fonts/FangZhengZhaoGeYuan.ttf", ONLINE_MODE_MENU_SCENE_FONT_SIZE);
    portTextField->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + ONLINE_MODE_MENU_SCENE_PORT_TEXTFIELD_OFFSET_Y));
    portTextField->setMaxLength(PORT_MAX_LENGTH);
    portTextField->setMaxLengthEnabled(true);
    portTextField->setTextColor(cocos2d::Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    this->addChild(portTextField);

    // ������ʾ��ǩ
    auto promptLabel = Label::createWithTTF("", "../Resources/Fonts/FangZhengZhaoGeYuan.ttf", ONLINE_MODE_MENU_SCENE_FONT_SIZE);
    promptLabel->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + ONLINE_MODE_MENU_SCENE_PROMPT_LABEL_OFFSET_Y));
    promptLabel->setVisible(false);
    promptLabel->setTextColor(cocos2d::Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    this->addChild(promptLabel);
    auto waitingLabel = Label::createWithTTF(u8"�ɹ����������������", "../Resources/Fonts/DingDingJinBuTi.ttf", ONLINE_MODE_MENU_SCENE_FONT_SIZE);
    waitingLabel->setPosition(Vec2(screenSize.width / 2 - ONLINE_MODE_MENU_SCENE_BUTTON_OFFSET_X, screenSize.height / 2 + ONLINE_MODE_MENU_SCENE_BUTTON_OFFSET_Y));
    waitingLabel->setVisible(false);
    this->addChild(waitingLabel);

    // ��������������ʧ����ʾ
    auto connectionFailedPrompt = Sprite::create("../Resources/Scenes/ServerConnectionFailedPrompt.png");
    connectionFailedPrompt->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    connectionFailedPrompt->setVisible(false);
    this->addChild(connectionFailedPrompt, 1);

    // Ϊ��ť����¼�������
    joinRoomButton->addTouchEventListener([this, ipv4TextField, portTextField, promptLabel, connectionFailedPrompt, joinRoomButton, screenSize, startGameButton, waitingLabel](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            std::string ipv4 = ipv4TextField->getString();
            std::string port = portTextField->getString();
            if (ipv4.empty() && port.empty()) { // ������ IPv4 ��ַ�Ͷ˿�Ϊ��
                promptLabel->setString(u8"������ IPv4 ��ַ�Ͷ˿ڲ���Ϊ��");
                promptLabel->setVisible(true);
                this->scheduleOnce([promptLabel](float dt) {
                    promptLabel->setVisible(false);
                    }, PROMPT_MESSAGE_DURATION, "IPv4AndPortHidePromptLabel");
            }
            else if (ipv4.empty() && !port.empty()) { // ������ IPv4 ��ַΪ��
                promptLabel->setString(u8"������ IPv4 ��ַ����Ϊ��");
                promptLabel->setVisible(true);
                this->scheduleOnce([promptLabel](float dt) {
                    promptLabel->setVisible(false);
                    }, PROMPT_MESSAGE_DURATION, "IPv4HidePromptLabel");
            }
            else if (!ipv4.empty() && port.empty()) { // �������˿�Ϊ��
                promptLabel->setString(u8"�������˿ڲ���Ϊ��");
                promptLabel->setVisible(true);
                this->scheduleOnce([promptLabel](float dt) {
                    promptLabel->setVisible(false);
                    }, PROMPT_MESSAGE_DURATION, "PortHidePromptLabel");
            }
            else { // ������ IPv4 ��ַ�Ͷ˿�����ɹ�
                // ��ʼ������ģʽ��Ϸ������
                try {
                    g_onlineModeControl = new OnlineModeControl(ipv4, port);
                }
                catch (const std::bad_alloc& e) {
                    std::cerr << "Memory allocation failed: " << e.what() << std::endl;
                    throw;
                }

                // �����ͻ���
                ConnectionStatus connectionStatus = g_onlineModeControl->initializeClient();
                if (connectionStatus == ConnectionError || connectionStatus == ConnectionTimeout) { // ����������ʧ�ܻ����ӳ�ʱ
                    connectionFailedPrompt->setVisible(true);
                    this->scheduleOnce([connectionFailedPrompt](float dt) {
                        connectionFailedPrompt->setVisible(false);
                        }, CONNECTION_FAILED_PROMPT_MESSAGE_DURATION, "ConnectionErrorHidePromptLabel");
                    delete g_onlineModeControl;
                    g_onlineModeControl = nullptr;
                }
                else if (connectionStatus == ConnectionRefused) { // �������ﵽ�����������
                    promptLabel->setString(u8"�������ﵽ�����������");
                    promptLabel->setVisible(true);
                    this->scheduleOnce([promptLabel](float dt) {
                        promptLabel->setVisible(false);
                        }, PROMPT_MESSAGE_DURATION, "ConnectionRefusedHidePromptLabel");
                    delete g_onlineModeControl;
                    g_onlineModeControl = nullptr;
                }
                else { // ���������ӳɹ�
                    // ����������
                    joinRoomButton->removeFromParent();
                    ipv4TextField->removeFromParent();
                    portTextField->removeFromParent();
                    waitingLabel->setVisible(true);
                    this->scheduleOnce([startGameButton, waitingLabel](float dt) {
                        waitingLabel->setVisible(false);
                        startGameButton->setEnabled(true);
                        startGameButton->setVisible(true);
                        }, START_GAME_BUTTON_APPEARANCE_DURATION, "StartGameButtonAppearance");

                    // ���������� IPv4 �Ͷ˿ڱ�ǩ
                    auto ipv4Label = Label::createWithTTF(ipv4, "../Resources/Fonts/FangZhengZhaoGeYuan.ttf", ONLINE_MODE_MENU_SCENE_FONT_SIZE);
                    ipv4Label->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + ONLINE_MODE_MENU_SCENE_IPV4_TEXTFIELD_OFFSET_Y));
                    ipv4Label->setTextColor(cocos2d::Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
                    this->addChild(ipv4Label);
                    auto portLabel = Label::createWithTTF(port, "../Resources/Fonts/FangZhengZhaoGeYuan.ttf", ONLINE_MODE_MENU_SCENE_FONT_SIZE);
                    portLabel->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + ONLINE_MODE_MENU_SCENE_PORT_TEXTFIELD_OFFSET_Y));
                    portLabel->setTextColor(cocos2d::Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
                    this->addChild(portLabel);

                    // ��������Ϣ����
                    this->schedule([this, promptLabel](float dt) {
                        char buffer[BUFFER_SIZE];
                        memset(buffer, 0, sizeof(buffer));
                        int recvSize = recv(g_onlineModeControl->getSocket(), buffer, BUFFER_SIZE, 0);
                        if (recvSize > 0) {
                            buffer[recvSize] = '\0';
                            if (!strncmp(buffer, CURRENT_CONNECTIONS_IDENTIFIER, MESSAGE_IDENTIFIER_LENGTH)) {
                                int currentConnections;
                                sscanf(buffer, CURRENT_CONNECTIONS_FORMAT, &currentConnections);
                                promptLabel->setString(u8"�ѽ������� (��������ǰ����������" + std::to_string(currentConnections) + u8")");
                                promptLabel->setVisible(true);
                                g_onlineModeControl->setCurrentConnections(currentConnections);
                            }
                            if (!strncmp(buffer, START_GAME_IDENTIFIER, MESSAGE_IDENTIFIER_LENGTH)) {
                                this->unschedule("ServerMessageListener"); // �رշ�������Ϣ����
                                std::string playerNamesBuffer = static_cast<std::string>(buffer);
                                g_onlineModeControl->deserializePlayerNames(playerNamesBuffer);
                                cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, OnlineModePreparationScene::createScene(), cocos2d::Color3B::WHITE));
                            }
                        }
                        }, SERVER_REFRESH_INTERVAL, "ServerMessageListener");
                }
            }
        }
        });
    returnMenuButton->addTouchEventListener([this](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            this->unschedule("ServerMessageListener"); // �رշ�������Ϣ����
            delete g_onlineModeControl;
            g_onlineModeControl = nullptr;
            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, MenuScene::createScene(), cocos2d::Color3B::WHITE));
        }
        });
    startGameButton->addTouchEventListener([startGameButton, waitingLabel](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            char buffer[BUFFER_SIZE];
            sprintf(buffer, PLAYER_NAME_FORMAT, g_PlayerName.c_str());
            g_onlineModeControl->sendMessage(buffer, strlen(buffer));
            startGameButton->removeFromParent();
            waitingLabel->setString(u8"��ȴ�������ҿ�ʼ��Ϸ");
            waitingLabel->setVisible(true);
        }
        });

    // ����ť��ӵ�������
    this->addChild(joinRoomButton);
    this->addChild(returnMenuButton);
    startGameButton->setVisible(false);
    startGameButton->setEnabled(false);
    this->addChild(startGameButton);

    return true;
}