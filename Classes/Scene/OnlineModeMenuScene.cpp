/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OnlineModeMenuScene.cpp
 * File Function: OnlineModeMenuScene类的实现
 * Author:        林继申
 * Update Date:   2023/12/26
 ****************************************************************/

#include <iostream>
#include "OnlineModeMenuScene.h"
#include "Control/OnlineModeControl.h"
#include "Button/HoverButton.h"
#include "MenuScene.h"
#include "proj.win32/Constant.h"
#include "GBKToUTF8/GBKToUTF8.h"

// 命名空间
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Label;
using cocos2d::Vec2;

// 联机模式游戏控制类
OnlineModeControl* g_onlineModeControl = nullptr;

// 创建场景
Scene* OnlineModeMenuScene::createScene()
{
    auto scene = Scene::create();
    auto layer = OnlineModeMenuScene::create();
    scene->addChild(layer);
    return scene;
}

// 初始化场景
bool OnlineModeMenuScene::init()
{
    // 创建场景
    if (!Scene::init()) {
        return false;
    }
    
    // 加载背景
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/OnlineModeMenuScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // 创建按钮
    auto joinRoomButton = HoverButton::create("../Resources/Buttons/OnlineModeMenuSceneButtons/JoinRoomDefaultButton.png",
        "../Resources/Buttons/OnlineModeMenuSceneButtons/JoinRoomHoverButton.png",
        "../Resources/Buttons/OnlineModeMenuSceneButtons/JoinRoomActiveButton.png");
    auto returnMenuButton = HoverButton::create("../Resources/Buttons/OnlineModeMenuSceneButtons/ReturnMenuDefaultButton.png",
        "../Resources/Buttons/OnlineModeMenuSceneButtons/ReturnMenuHoverButton.png",
        "../Resources/Buttons/OnlineModeMenuSceneButtons/ReturnMenuActiveButton.png");
    auto startGameButton = HoverButton::create("../Resources/Buttons/OnlineModeMenuSceneButtons/startGameDefaultButton.png",
        "../Resources/Buttons/OnlineModeMenuSceneButtons/startGameHoverButton.png",
        "../Resources/Buttons/OnlineModeMenuSceneButtons/startGameActiveButton.png");

    // 设置按钮位置
    joinRoomButton->setPosition(Vec2(screenSize.width / 2 - ONLINE_MODE_MENU_SCENE_BUTTON_OFFSET_X, screenSize.height / 2 + ONLINE_MODE_MENU_SCENE_BUTTON_OFFSET_Y));
    returnMenuButton->setPosition(Vec2(screenSize.width / 2 + ONLINE_MODE_MENU_SCENE_BUTTON_OFFSET_X, screenSize.height / 2 + ONLINE_MODE_MENU_SCENE_BUTTON_OFFSET_Y));
    startGameButton->setPosition(Vec2(screenSize.width / 2 - ONLINE_MODE_MENU_SCENE_BUTTON_OFFSET_X, screenSize.height / 2 + ONLINE_MODE_MENU_SCENE_BUTTON_OFFSET_Y));

    // 创建 IPv4 文本框
    auto ipv4TextField = cocos2d::ui::TextField::create(GBKToUTF8::getString("请输入服务器 IPv4 地址"), "../Resources/Fonts/FangZhengZhaoGeYuan.ttf", ONLINE_MODE_MENU_SCENE_FONT_SIZE);
    ipv4TextField->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + ONLINE_MODE_MENU_SCENE_IPV4_TEXTFIELD_OFFSET_Y));
    ipv4TextField->setMaxLength(IPV4_ADDRESS_MAX_LENGTH);
    ipv4TextField->setMaxLengthEnabled(true);
    ipv4TextField->setTextColor(cocos2d::Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    this->addChild(ipv4TextField);

    // 创建端口文本框
    auto portTextField = cocos2d::ui::TextField::create(GBKToUTF8::getString("请输入服务器端口"), "../Resources/Fonts/FangZhengZhaoGeYuan.ttf", ONLINE_MODE_MENU_SCENE_FONT_SIZE);
    portTextField->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + ONLINE_MODE_MENU_SCENE_PORT_TEXTFIELD_OFFSET_Y));
    portTextField->setMaxLength(PORT_MAX_LENGTH);
    portTextField->setMaxLengthEnabled(true);
    portTextField->setTextColor(cocos2d::Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    this->addChild(portTextField);

    // 创建一个提示标签
    auto promptLabel = Label::createWithTTF("", "../Resources/Fonts/FangZhengZhaoGeYuan.ttf", ONLINE_MODE_MENU_SCENE_FONT_SIZE);
    promptLabel->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + ONLINE_MODE_MENU_SCENE_PROMPT_LABEL_OFFSET_Y));
    promptLabel->setVisible(false);
    promptLabel->setTextColor(cocos2d::Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    this->addChild(promptLabel);

    // 创建服务器连接失败提示
    auto connectionFailedPrompt = Sprite::create("../Resources/Scenes/ServerConnectionFailedPrompt.png");
    connectionFailedPrompt->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    connectionFailedPrompt->setVisible(false);
    this->addChild(connectionFailedPrompt, 1);

    // 为按钮添加事件处理器
    joinRoomButton->addTouchEventListener([this, ipv4TextField, portTextField, promptLabel, connectionFailedPrompt, joinRoomButton, screenSize, startGameButton](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            std::string ipv4 = ipv4TextField->getString();
            std::string port = portTextField->getString();
            if (ipv4.empty() && port.empty()) { // 服务器 IPv4 地址和端口为空
                promptLabel->setString(GBKToUTF8::getString("服务器 IPv4 地址和端口不能为空"));
                promptLabel->setVisible(true);
                this->scheduleOnce([promptLabel](float dt) {
                    promptLabel->setVisible(false);
                    }, PROMPT_MESSAGE_DURATION, "IPv4AndPortHidePromptLabel");
            }
            else if (ipv4.empty() && !port.empty()) { // 服务器 IPv4 地址为空
                promptLabel->setString(GBKToUTF8::getString("服务器 IPv4 地址不能为空"));
                promptLabel->setVisible(true);
                this->scheduleOnce([promptLabel](float dt) {
                    promptLabel->setVisible(false);
                    }, PROMPT_MESSAGE_DURATION, "IPv4HidePromptLabel");
            }
            else if (!ipv4.empty() && port.empty()) { // 服务器端口为空
                promptLabel->setString(GBKToUTF8::getString("服务器端口不能为空"));
                promptLabel->setVisible(true);
                this->scheduleOnce([promptLabel](float dt) {
                    promptLabel->setVisible(false);
                    }, PROMPT_MESSAGE_DURATION, "PortHidePromptLabel");
            }
            else { // 服务器 IPv4 地址和端口输入成功
                // 初始化联机模式游戏控制类
                try {
                    g_onlineModeControl = new OnlineModeControl(ipv4, port);
                }
                catch (const std::bad_alloc& e) {
                    std::cerr << "Memory allocation failed: " << e.what() << std::endl;
                    throw;
                }

                // 创建客户端
                ConnectionStatus connectionStatus = g_onlineModeControl->initializeClient();
                if (connectionStatus == ConnectionError || connectionStatus == ConnectionTimeout) { // 服务器连接失败或连接超时
                    connectionFailedPrompt->setVisible(true);
                    this->scheduleOnce([connectionFailedPrompt](float dt) {
                        connectionFailedPrompt->setVisible(false);
                        }, CONNECTION_FAILED_PROMPT_MESSAGE_DURATION, "ConnectionErrorHidePromptLabel");
                    delete g_onlineModeControl;
                    g_onlineModeControl = nullptr;
                }
                else if (connectionStatus == ConnectionRefused) { // 服务器达到最大连接数量
                    promptLabel->setString(GBKToUTF8::getString("服务器达到最大连接数量"));
                    promptLabel->setVisible(true);
                    this->scheduleOnce([promptLabel](float dt) {
                        promptLabel->setVisible(false);
                        }, PROMPT_MESSAGE_DURATION, "ConnectionRefusedHidePromptLabel");
                    delete g_onlineModeControl;
                    g_onlineModeControl = nullptr;
                }
                else { // 服务器连接成功
                    // 设置相关组件
                    joinRoomButton->removeFromParent();
                    ipv4TextField->removeFromParent();
                    portTextField->removeFromParent();
                    startGameButton->setEnabled(true);
                    startGameButton->setVisible(true);

                    // 创建服务器 IPv4 和端口标签
                    auto ipv4Label = Label::createWithTTF(ipv4, "../Resources/Fonts/FangZhengZhaoGeYuan.ttf", ONLINE_MODE_MENU_SCENE_FONT_SIZE);
                    ipv4Label->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + ONLINE_MODE_MENU_SCENE_IPV4_TEXTFIELD_OFFSET_Y));
                    ipv4Label->setTextColor(cocos2d::Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
                    this->addChild(ipv4Label);
                    auto portLabel = Label::createWithTTF(port, "../Resources/Fonts/FangZhengZhaoGeYuan.ttf", ONLINE_MODE_MENU_SCENE_FONT_SIZE);
                    portLabel->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + ONLINE_MODE_MENU_SCENE_PORT_TEXTFIELD_OFFSET_Y));
                    portLabel->setTextColor(cocos2d::Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
                    this->addChild(portLabel);

                    // 服务器消息监听
                    this->schedule([this, promptLabel](float dt) {
                        char buffer[BUFFER_SIZE];
                        memset(buffer, 0, sizeof(buffer));
                        int recvSize = recv(g_onlineModeControl->getSocket(), buffer, BUFFER_SIZE, 0);
                        if (recvSize > 0) {
                            CCLOG("recvSize=%d", recvSize);
                            buffer[recvSize] = '\0';
                            CCLOG("%s", buffer);
                            if (!strcmp(buffer, START_GAME_MSG)) {
                                this->unschedule("ServerMessageListener");
                            }
                            else {
                                int currentConnections;
                                if (sscanf(buffer, CURRENT_CONNECTIONS_FORMAT, &currentConnections) == 1) {
                                    promptLabel->setString(GBKToUTF8::getString("已建立连接 (服务器当前连接数量：") + std::to_string(currentConnections) + GBKToUTF8::getString(")"));
                                    promptLabel->setVisible(true);
                                }
                            }
                        }
                        }, SERVER_REFRESH_INTERVAL, "ServerMessageListener");
                }
            }
        }
        });
    returnMenuButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, MenuScene::createScene(), cocos2d::Color3B::WHITE));
        }
        });
    startGameButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            // TODO
        }
        });

    // 将按钮添加到场景中
    this->addChild(joinRoomButton);
    this->addChild(returnMenuButton);
    startGameButton->setVisible(false);
    startGameButton->setEnabled(false);
    this->addChild(startGameButton);

    return true;
}