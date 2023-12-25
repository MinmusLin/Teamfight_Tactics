/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     ScoreBoardLayer.h
 * File Function: ScoreBoardLayer类的定义
 * Author:        刘淑仪、林继申
 * Update Date:   2023/12/25
 ****************************************************************/

#pragma once
#ifndef _SCORE_BOARD_LAYER_H_
#define _SCORE_BOARD_LAYER_H_

#include "cocos2d.h"

/*
 * Class Name:     ScoreBoardLayer
 * Class Function: 分数表层类
 */
class ScoreBoardLayer : public cocos2d::Layer {
public:
    // 初始化分数表层类
    virtual bool init();

    // 显示分数表
    void showScoreBoard(int playerNum);

    // 实现 ScoreBoardLayer 类的 create 方法
    CREATE_FUNC(ScoreBoardLayer);
};

#endif // !_SCORE_BOARD_LAYER_H_