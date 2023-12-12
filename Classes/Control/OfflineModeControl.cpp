/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeControl.cpp
 * File Function: OfflineModeControl���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/12
 ****************************************************************/

#include "OfflineModeControl.h"

// ���캯��
OfflineModeControl::OfflineModeControl() : Control(2)
{
    try {
        humanPlayer = new HumanPlayer(cocos2d::UserDefault::getInstance()->getStringForKey("PlayerName"));
        enemyPlayer = new AIPlayer("AI���", Easy); // TODO: �ݶ���ģʽ����Ҫ���Σ�֮�� Control ��Ĵ������ּ����޸�
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
}