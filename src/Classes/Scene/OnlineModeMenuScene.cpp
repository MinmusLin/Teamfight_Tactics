/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OnlineModeMenuScene.cpp
 * File Function: OnlineModeMenuScene类的实现
 * Author:        林继申、刘淑仪
 * Update Date:   2023/12/31
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
#include "proj.win32/AudioPlayer.h"

// 命名空间
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Label;
using cocos2d::Vec2;

// 玩家昵称
extern std::string g_PlayerName;

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
    
    // 加载音乐
    audioPlayer("../Resources/Music/OnlineModeMenuScene_SilverScrapes.mp3", true);

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
    auto ipv4TextField = cocos2d::ui::TextField::create(u8"请输入服务器 IPv4 地址", "../Resources/Fonts/DingDingJinBuTi.ttf", ONLINE_MODE_MENU_SCENE_FONT_SIZE);
    ipv4TextField->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + ONLINE_MODE_MENU_SCENE_IPV4_TEXTFIELD_OFFSET_Y));
    ipv4TextField->setMaxLength(IPV4_ADDRESS_MAX_LENGTH);
    ipv4TextField->setMaxLengthEnabled(true);
    ipv4TextField->setTextColor(cocos2d::Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    this->addChild(ipv4TextField);

    // 创建端口文本框
    auto portTextField = cocos2d::ui::TextField::create(u8"请输入服务器端口", "../Resources/Fonts/DingDingJinBuTi.ttf", ONLINE_MODE_MENU_SCENE_FONT_SIZE);
    portTextField->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + ONLINE_MODE_MENU_SCENE_PORT_TEXTFIELD_OFFSET_Y));
    portTextField->setMaxLength(PORT_MAX_LENGTH);
    portTextField->setMaxLengthEnabled(true);
    portTextField->setTextColor(cocos2d::Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    this->addChild(portTextField);

    // 创建提示标签
    auto promptLabel = Label::createWithTTF("", "../Resources/Fonts/DingDingJinBuTi.ttf", ONLINE_MODE_MENU_SCENE_FONT_SIZE);
    promptLabel->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + ONLINE_MODE_MENU_SCENE_PROMPT_LABEL_OFFSET_Y));
    promptLabel->setVisible(false);
    promptLabel->setTextColor(cocos2d::Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    this->addChild(promptLabel);
    auto waitingLabel = Label::createWithTTF(u8"成功与服务器建立连接", "../Resources/Fonts/DingDingJinBuTi.ttf", ONLINE_MODE_MENU_SCENE_FONT_SIZE);
    waitingLabel->setPosition(Vec2(screenSize.width / 2 - ONLINE_MODE_MENU_SCENE_BUTTON_OFFSET_X, screenSize.height / 2 + ONLINE_MODE_MENU_SCENE_BUTTON_OFFSET_Y));
    waitingLabel->setVisible(false);
    this->addChild(waitingLabel);

    // 创建服务器连接失败提示
    auto connectionFailedPrompt = Sprite::create("../Resources/ImageElements/ServerConnectionFailedPrompt.png");
    connectionFailedPrompt->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    connectionFailedPrompt->setVisible(false);
    this->addChild(connectionFailedPrompt, 1);

    // 为按钮添加事件处理器
    joinRoomButton->addTouchEventListener([this, ipv4TextField, portTextField, promptLabel, connectionFailedPrompt, joinRoomButton, screenSize, startGameButton, waitingLabel](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            // 加载点击音效
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

            std::string ipv4 = ipv4TextField->getString();
            std::string port = portTextField->getString();
            if (ipv4.empty() && port.empty()) { // 服务器 IPv4 地址和端口为空
                promptLabel->setString(u8"服务器 IPv4 地址和端口不能为空");
                promptLabel->setVisible(true);
                this->scheduleOnce([promptLabel](float dt) {
                    promptLabel->setVisible(false);
                    }, PROMPT_MESSAGE_DURATION, "IPv4AndPortHidePromptLabel");
            }
            else if (ipv4.empty() && !port.empty()) { // 服务器 IPv4 地址为空
                promptLabel->setString(u8"服务器 IPv4 地址不能为空");
                promptLabel->setVisible(true);
                this->scheduleOnce([promptLabel](float dt) {
                    promptLabel->setVisible(false);
                    }, PROMPT_MESSAGE_DURATION, "IPv4HidePromptLabel");
            }
            else if (!ipv4.empty() && port.empty()) { // 服务器端口为空
                promptLabel->setString(u8"服务器端口不能为空");
                promptLabel->setVisible(true);
                this->scheduleOnce([promptLabel](float dt) {
                    promptLabel->setVisible(false);
                    }, PROMPT_MESSAGE_DURATION, "PortHidePromptLabel");
            }
            else if (!isValidIPv4(ipv4) && !isValidPort(port)) { // 服务器 IPv4 地址和端口非法
                promptLabel->setString(u8"服务器 IPv4 地址和端口非法");
                promptLabel->setVisible(true);
                this->scheduleOnce([promptLabel](float dt) {
                    promptLabel->setVisible(false);
                    }, PROMPT_MESSAGE_DURATION, "IPv4AndPortInvalidPromptLabel");
            }
            else if (!isValidIPv4(ipv4)) { // 服务器 IPv4 地址非法
                promptLabel->setString(u8"服务器 IPv4 地址非法");
                promptLabel->setVisible(true);
                this->scheduleOnce([promptLabel](float dt) {
                    promptLabel->setVisible(false);
                    }, PROMPT_MESSAGE_DURATION, "IPv4InvalidPromptLabel");
            }
            else if (!isValidPort(port)) { // 服务器端口非法
                promptLabel->setString(u8"服务器端口非法");
                promptLabel->setVisible(true);
                this->scheduleOnce([promptLabel](float dt) {
                    promptLabel->setVisible(false);
                    }, PROMPT_MESSAGE_DURATION, "PortInvalidPromptLabel");
            }
            else { // 服务器 IPv4 地址和端口合法
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
                    promptLabel->setString(u8"服务器达到最大连接数量");
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
                    waitingLabel->setVisible(true);
                    this->scheduleOnce([startGameButton, waitingLabel](float dt) {
                        waitingLabel->setVisible(false);
                        startGameButton->setEnabled(true);
                        startGameButton->setVisible(true);
                        }, START_GAME_BUTTON_APPEARANCE_DURATION, "StartGameButtonAppearance");

                    // 创建服务器 IPv4 和端口标签
                    auto ipv4Label = Label::createWithTTF(ipv4, "../Resources/Fonts/DingDingJinBuTi.ttf", ONLINE_MODE_MENU_SCENE_FONT_SIZE);
                    ipv4Label->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + ONLINE_MODE_MENU_SCENE_IPV4_TEXTFIELD_OFFSET_Y));
                    ipv4Label->setTextColor(cocos2d::Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
                    this->addChild(ipv4Label);
                    auto portLabel = Label::createWithTTF(port, "../Resources/Fonts/DingDingJinBuTi.ttf", ONLINE_MODE_MENU_SCENE_FONT_SIZE);
                    portLabel->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + ONLINE_MODE_MENU_SCENE_PORT_TEXTFIELD_OFFSET_Y));
                    portLabel->setTextColor(cocos2d::Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
                    this->addChild(portLabel);

                    // 服务器消息监听
                    this->schedule([this, promptLabel](float dt) {
                        char buffer[BUFFER_SIZE];
                        memset(buffer, 0, sizeof(buffer));
                        int recvSize = recv(g_onlineModeControl->getSocket(), buffer, BUFFER_SIZE, 0);
                        if (recvSize > 0) {
                            buffer[recvSize] = '\0';
                            if (!strncmp(buffer, CURRENT_CONNECTIONS_IDENTIFIER, MESSAGE_IDENTIFIER_LENGTH)) {
                                int currentConnections;
                                sscanf(buffer, CURRENT_CONNECTIONS_FORMAT, &currentConnections);
                                promptLabel->setString(u8"已建立连接 (服务器当前连接数量：" + std::to_string(currentConnections) + u8")");
                                promptLabel->setVisible(true);
                                g_onlineModeControl->setCurrentConnections(currentConnections);
                            }
                            if (!strncmp(buffer, START_GAME_IDENTIFIER, MESSAGE_IDENTIFIER_LENGTH)) {
                                this->unschedule("ServerMessageListener"); // 关闭服务器消息监听
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
            // 加载点击音效
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

            this->unschedule("ServerMessageListener"); // 关闭服务器消息监听
            delete g_onlineModeControl;
            g_onlineModeControl = nullptr;
            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, MenuScene::createScene(), cocos2d::Color3B::WHITE));
        }
        });
    startGameButton->addTouchEventListener([startGameButton, waitingLabel](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            // 加载点击音效
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

            char buffer[BUFFER_SIZE];
            sprintf(buffer, PLAYER_NAME_FORMAT, g_PlayerName.c_str());
            g_onlineModeControl->sendMessage(buffer, strlen(buffer));
            startGameButton->removeFromParent();
            waitingLabel->setString(u8"请等待其他玩家开始游戏");
            waitingLabel->setVisible(true);
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

// 服务器 IPv4 地址合法性检验
bool OnlineModeMenuScene::isValidIPv4(const std::string& str)
{
    int dotCount = 0, numCount = 0;
    std::string numPart;
    for (char ch : str) {
        if (ch == '.') {
            if (numPart.empty() || numPart.size() > 3) {
                return false;
            }
            int num = std::stoi(numPart);
            if (num < 0 || num > 255) {
                return false;
            }
            dotCount++;
            numPart.clear();
        }
        else if (ch >= '0' && ch <= '9') {
            numPart += ch;
            if (numPart.size() > 3) {
                return false;
            }
            if (numPart.size() > 1 && numPart[0] == '0') {
                return false; // 禁止前导零
            }
        }
        else {
            return false;
        }
    }
    if (!numPart.empty()) {
        if (numPart.size() > 3) {
            return false;
        }
        int num = std::stoi(numPart);
        if (num < 0 || num > 255) {
            return false;
        }
    }
    return dotCount == 3 && !numPart.empty();
}

// 服务器端口合法性检验
bool OnlineModeMenuScene::isValidPort(const std::string& str)
{
    if (str.empty() || str.size() > 5) {
        return false;
    }
    for (char ch : str) {
        if (ch < '0' || ch >'9') {
            return false;
        }
    }
    int port = std::stoi(str);
    return port >= MIN_PORT_ADDRESS && port <= MAX_PORT_ADDRESS;
}