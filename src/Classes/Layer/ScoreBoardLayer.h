/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     ScoreBoardLayer.h
 * File Function: ScoreBoardLayer类的定义
 * Author:        刘淑仪、林继申
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
 * Class Function: 分数表层类
 */
class ScoreBoardLayer : public cocos2d::Layer {
public:
    // 析构函数
    ~ScoreBoardLayer();

    // 初始化分数表层类
    virtual bool init();

    // 初始化分数表背景
    void initialize(const int playerNum);

    // 显示分数表（练习模式）
    void showScoreBoard(HumanPlayer* humanPlayer, AIPlayer* enemyPlayer);

    // 显示分数表（联机模式）
    void showScoreBoard(const int playerNum, const std::vector<std::map<SOCKET, std::string>>& playerNamesMap, const std::vector<std::map<SOCKET, int>>& playerHealthPointsMap);

    // 实现 ScoreBoardLayer 类的 create 方法
    CREATE_FUNC(ScoreBoardLayer);

private:
    cocos2d::Label** playerNames = nullptr;  // 玩家昵称标签指针
    cocos2d::Label** healthPoints = nullptr; // 玩家生命值标签指针
};

#endif // !_SCORE_BOARD_LAYER_H_