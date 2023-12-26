/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     ScoreBoardLayer.cpp
 * File Function: ScoreBoardLayer类的实现
 * Author:        刘淑仪、林继申
 * Update Date:   2023/12/25
 ****************************************************************/

#include <algorithm>
#include <vector>
#include <iostream>
#include "ScoreBoardLayer.h"

// 命名空间
using cocos2d::Sprite;
using cocos2d::Label;

// 析构函数
ScoreBoardLayer::~ScoreBoardLayer()
{
    delete[] playerNames;
    delete[] healthPoints;
}

// 初始化放置标记层
bool ScoreBoardLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    return true;
}

// 初始化分数表背景
void ScoreBoardLayer::initialize(const int playerNum)
{
    // 初始化标签
    try {
        playerNames = new Label * [playerNum];
        healthPoints = new Label * [playerNum];
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
        if (playerNames) {
            delete playerNames;
        }
        if (healthPoints) {
            delete healthPoints;
        }
        throw;
    }

    // 初始化分数表
    for (int i = 0; i < playerNum; i++) {
        // 创建分数表背景
        auto scoreBoardBackground = Sprite::create("../Resources/Layers/ScoreBoardLayerBackground.png");
        scoreBoardBackground->setPosition(SCORE_BOARD_LAYER_START_X, SCORE_BOARD_LAYER_START_Y - i * SCORE_BOARD_LAYER_VERTICAL_INTERVAL);
        this->addChild(scoreBoardBackground);

        // 创建排名标签
        auto rankLabel = Label::createWithTTF(std::to_string(i + 1), "../Resources/Fonts/DingDingJinBuTi.ttf", SCORE_BOARD_LABEL_FONT_SIZE);
        rankLabel->setPosition(SCORE_BOARD_LAYER_START_X + SCORE_BOARD_LAYER_RANK_LABEL_OFFSET_X, SCORE_BOARD_LAYER_START_Y - i * SCORE_BOARD_LAYER_VERTICAL_INTERVAL);
        rankLabel->setTextColor(cocos2d::Color4B(GOLDEN_R, GOLDEN_G, GOLDEN_B, 255));
        this->addChild(rankLabel);

        // 创建玩家昵称标签
        playerNames[i] = Label::createWithTTF("", "../Resources/Fonts/DingDingJinBuTi.ttf", SCORE_BOARD_LABEL_FONT_SIZE);
        playerNames[i]->setPosition(SCORE_BOARD_LAYER_START_X + SCORE_BOARD_LAYER_NAME_LABEL_OFFSET_X, SCORE_BOARD_LAYER_START_Y - i * SCORE_BOARD_LAYER_VERTICAL_INTERVAL);
        playerNames[i]->setAnchorPoint({ 0, 0.5 });
        this->addChild(playerNames[i]);

        // 创建生命值标签
        healthPoints[i] = Label::createWithTTF("", "../Resources/Fonts/DingDingJinBuTi.ttf", SCORE_BOARD_LABEL_FONT_SIZE);
        healthPoints[i]->setPosition(SCORE_BOARD_LAYER_START_X + SCORE_BOARD_LAYER_SCORE_LABEL_OFFSET_X, SCORE_BOARD_LAYER_START_Y - i * SCORE_BOARD_LAYER_VERTICAL_INTERVAL);
        healthPoints[i]->setAnchorPoint({ 1, 0.5 });
        this->addChild(healthPoints[i]);
    }
}

// 显示分数表（练习模式）
void ScoreBoardLayer::showScoreBoard(HumanPlayer* humanPlayer, AIPlayer* enemyPlayer)
{
    bool isHumanFirst = humanPlayer->getHealthPoints() >= enemyPlayer->getHealthPoints();
    std::string humanPlayerName = humanPlayer->getPlayerName();
    std::string enemyPlayerName = enemyPlayer->getPlayerName();
    int humanPlayerHealthPoints = humanPlayer->getHealthPoints();
    int enemyPlayerHealthPoints = enemyPlayer->getHealthPoints();
    playerNames[0]->setString(isHumanFirst ? humanPlayerName : enemyPlayerName);
    playerNames[1]->setString(isHumanFirst ? enemyPlayerName : humanPlayerName);
    healthPoints[0]->setString(std::to_string(isHumanFirst ? humanPlayerHealthPoints : enemyPlayerHealthPoints));
    healthPoints[1]->setString(std::to_string(isHumanFirst ? enemyPlayerHealthPoints : humanPlayerHealthPoints));
}

// 显示分数表（联机模式）
void ScoreBoardLayer::showScoreBoard(int playerNum, HumanPlayer** players)
{
    std::vector<HumanPlayer*> sortedPlayers(players, players + playerNum);
    std::sort(sortedPlayers.begin(), sortedPlayers.end(), [](const HumanPlayer* a, const HumanPlayer* b) {
        return a->getHealthPoints() > b->getHealthPoints();
        });
    for (int i = 0; i < playerNum; i++) {
        playerNames[i]->setString(sortedPlayers[i]->getPlayerName());
        healthPoints[i]->setString(std::to_string(sortedPlayers[i]->getHealthPoints()));
    }
}