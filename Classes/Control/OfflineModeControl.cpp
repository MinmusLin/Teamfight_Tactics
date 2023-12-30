/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeControl.cpp
 * File Function: OfflineModeControl类的实现
 * Author:        杨宇琨、林继申
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#include <iostream>
#include "OfflineModeControl.h"

// 玩家昵称
extern std::string g_PlayerName;

// 游戏难度
extern Difficulty g_difficulty;

// 构造函数
OfflineModeControl::OfflineModeControl() :
    Control(2)
{
    try {
        humanPlayer = new HumanPlayer(g_PlayerName);
        enemyPlayer = new AIPlayer(u8"AI玩家", g_difficulty);
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
        if (humanPlayer) {
            delete humanPlayer;
        }
        if (enemyPlayer) {
            delete enemyPlayer;
        }
        throw;
    }
}

// 析构函数
OfflineModeControl::~OfflineModeControl()
{
    delete humanPlayer;
    delete enemyPlayer;
    if (battle) {
        delete battle;
    }
}

// 获取 AI 玩家指针
AIPlayer* OfflineModeControl::getAIPlayer() const
{
    return enemyPlayer;
}

// 初始化对战类
void OfflineModeControl::initializeBattle()
{
    // AI 落棋算法
    enemyPlayer->makeMoves();

    // 获取战斗英雄地图
    ChampionCategory(*myFlagMap)[BATTLE_MAP_COLUMNS];
    ChampionCategory(*enemyFlagMap)[BATTLE_MAP_COLUMNS];
    humanPlayer->getBattleMap(myFlagMap);
    enemyPlayer->getBattleMap(enemyFlagMap);

    // 创建对战类
    try {
        battle = new Battle(myFlagMap, enemyFlagMap);
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
        throw;
    }
}