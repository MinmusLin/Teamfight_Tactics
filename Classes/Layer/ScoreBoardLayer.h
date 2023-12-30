/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     ScoreBoardLayer.h
 * File Function: ScoreBoardLayer��Ķ���
 * Author:        �����ǡ��ּ���
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _SCORE_BOARD_LAYER_H_
#define _SCORE_BOARD_LAYER_H_

#include <vector>
#include "cocos2d.h"
#include "Player/HumanPlayer.h"
#include "Player/AIPlayer.h"

/*
 * Class Name:     ScoreBoardLayer
 * Class Function: ���������
 */
class ScoreBoardLayer : public cocos2d::Layer {
public:
    // ��������
    ~ScoreBoardLayer();

    // ��ʼ�����������
    virtual bool init();

    // ��ʼ����������
    void initialize(const int playerNum);

    // ��ʾ��������ϰģʽ��
    void showScoreBoard(HumanPlayer* humanPlayer, AIPlayer* enemyPlayer);

    // ��ʾ����������ģʽ��
    void showScoreBoard(const int playerNum, const std::vector<std::map<SOCKET, std::string>>& playerNamesMap, const std::vector<std::map<SOCKET, int>>& playerHealthPointsMap);

    // ʵ�� ScoreBoardLayer ��� create ����
    CREATE_FUNC(ScoreBoardLayer);

private:
    cocos2d::Label** playerNames = nullptr;  // ����ǳƱ�ǩָ��
    cocos2d::Label** healthPoints = nullptr; // �������ֵ��ǩָ��
};

#endif // !_SCORE_BOARD_LAYER_H_