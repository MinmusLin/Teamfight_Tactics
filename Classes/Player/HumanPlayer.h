/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     HumanPlayer.h
 * File Function: HumanPlayer类的定义
 * Author:        林继申
 * Update Date:   2023/12/19
 ****************************************************************/

#pragma once
#ifndef _HUMAN_PLAYER_H_
#define _HUMAN_PLAYER_H_

#include "Player.h"
#include "Button/HoverButton.h"
#include "Champion/Champion.h"

/*
 * Class Name:     HumanPlayer
 * Class Function: 人类玩家类
 */
class HumanPlayer : public Player {
public:
    // 构造函数
    HumanPlayer(std::string nickname);

    // 析构函数
    ~HumanPlayer();

    // 刷新商店
    void refreshShop(cocos2d::Scene* currentScene);

private:
    ChampionCategory shopChampionCategory[MAX_SELECTABLE_CHAMPION_COUNT]; // 商店战斗英雄种类
    HoverButton* shopChampionButton[MAX_SELECTABLE_CHAMPION_COUNT];       // 商店战斗英雄按钮
    Champion* battleChampion[BATTLE_MAP_ROWS][BATTLE_MAP_COLUMNS];        // 战斗区战斗英雄指针
    Champion* waitingChampion[WAITING_MAP_COUNT];                         // 候战区战斗英雄指针
    Location startLocation;                                               // 战斗英雄移动起始位置属性

    // 添加战斗英雄
    void addChampion(int index, cocos2d::Scene* currentScene);

    // 按下鼠标事件触发函数
    void onMouseDown(cocos2d::Event* event, cocos2d::Sprite* championSprite);

    // 移动鼠标事件触发函数
    void onMouseMove(cocos2d::Event* event, cocos2d::Sprite* championSprite);

    // 释放鼠标事件触发函数
    void onMouseUp(cocos2d::Event* event, cocos2d::Sprite* championSprite);
};

#endif // !_HUMAN_PLAYER_H_