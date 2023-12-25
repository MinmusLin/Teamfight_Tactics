/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     ScoreBoardLayer.h
 * File Function: ScoreBoardLayer��Ķ���
 * Author:        �����ǡ��ּ���
 * Update Date:   2023/12/25
 ****************************************************************/

#pragma once
#ifndef _SCORE_BOARD_LAYER_H_
#define _SCORE_BOARD_LAYER_H_

#include "cocos2d.h"

/*
 * Class Name:     ScoreBoardLayer
 * Class Function: ���������
 */
class ScoreBoardLayer : public cocos2d::Layer {
public:
    // ��ʼ�����������
    virtual bool init();

    // ��ʾ������
    void showScoreBoard(int playerNum);

    // ʵ�� ScoreBoardLayer ��� create ����
    CREATE_FUNC(ScoreBoardLayer);
};

#endif // !_SCORE_BOARD_LAYER_H_