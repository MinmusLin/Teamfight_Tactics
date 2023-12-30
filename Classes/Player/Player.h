/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Player.h
 * File Function: Player类的定义
 * Author:        林继申、杨兆镇
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "proj.win32/Constant.h"

/*
 * Class Name:     Player
 * Class Function: 玩家类
 */
class Player {
public:
    // 构造函数
    Player(const std::string nickname);

    // 获取战斗区地图
    void getBattleMap(ChampionCategory(*&battleMap)[BATTLE_MAP_COLUMNS]);

    // 减少玩家生命值
    void decreaseHealthPoints(const int num);

    // 获取玩家生命值
    int getHealthPoints() const;

    // 获取玩家昵称
    std::string getPlayerName() const;

protected:
    std::string name;                                               // 玩家昵称
    ChampionCategory battleMap[PLACE_MAP_ROWS][BATTLE_MAP_COLUMNS]; // 战斗区地图
    ChampionCategory waitingMap[WAITING_MAP_COUNT];                 // 候战区地图
    std::map<ChampionCategory, int> champions;                      // 战斗英雄种类与数量键值对
    int healthPoints;                                               // 玩家生命值

    // 获取随机数
    int getRandom(const int n) const;

    // 获取当前局势分数
    int getStageScore() const;

    // 评估当前局势
    BattleStage evaluateStage(int stageScore) const;

    // 统计各类战斗英雄数量
    std::map<ChampionCategory, int> countChampionCategories() const;

    // 为特定战斗阶段随机选择战斗英雄
    ChampionCategory selectRandomChampion(const BattleStage stage) const;
};

#endif // !_PLAYER_H_