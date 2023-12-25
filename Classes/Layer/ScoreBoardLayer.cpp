/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     ScoreBoardLayer.cpp
 * File Function: ScoreBoardLayer类的实现
 * Author:        刘淑仪、林继申
 * Update Date:   2023/12/25
 ****************************************************************/

#include "ScoreBoardLayer.h"

// 命名空间
using cocos2d::Sprite;
using cocos2d::Label;

// 初始化放置标记层
bool ScoreBoardLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    return true;
}

// 显示分数表
void ScoreBoardLayer::showScoreBoard(int playerNum)
{



}