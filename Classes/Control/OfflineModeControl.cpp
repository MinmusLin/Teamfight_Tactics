/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeControl.cpp
 * File Function: OfflineModeControl���ʵ��
 * Author:        ���������ּ���
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#include <iostream>
#include "OfflineModeControl.h"

// ����ǳ�
extern std::string g_PlayerName;

// ��Ϸ�Ѷ�
extern Difficulty g_difficulty;

// ���캯��
OfflineModeControl::OfflineModeControl() :
    Control(2)
{
    try {
        humanPlayer = new HumanPlayer(g_PlayerName);
        enemyPlayer = new AIPlayer(u8"AI���", g_difficulty);
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

// ��������
OfflineModeControl::~OfflineModeControl()
{
    delete humanPlayer;
    delete enemyPlayer;
    if (battle) {
        delete battle;
    }
}

// ��ȡ AI ���ָ��
AIPlayer* OfflineModeControl::getAIPlayer() const
{
    return enemyPlayer;
}

// ��ʼ����ս��
void OfflineModeControl::initializeBattle()
{
    // AI �����㷨
    enemyPlayer->makeMoves();

    // ��ȡս��Ӣ�۵�ͼ
    ChampionCategory(*myFlagMap)[BATTLE_MAP_COLUMNS];
    ChampionCategory(*enemyFlagMap)[BATTLE_MAP_COLUMNS];
    humanPlayer->getBattleMap(myFlagMap);
    enemyPlayer->getBattleMap(enemyFlagMap);

    // ������ս��
    try {
        battle = new Battle(myFlagMap, enemyFlagMap);
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
        throw;
    }
}