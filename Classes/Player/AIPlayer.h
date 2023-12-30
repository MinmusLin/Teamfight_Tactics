/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     AIPlayer.h
 * File Function: AIPlayer类的定义
 * Author:        杨兆镇、林继申
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _AI_PLAYER_H_
#define _AI_PLAYER_H_

#include <vector>
#include "Player.h"

/*
 * Class Name:     AIPlayer
 * Class Function: AI 玩家类
 */
class AIPlayer : public Player {
public:
    // 构造函数
    AIPlayer(const std::string nickname, const Difficulty difficulty_);

    // AI 落棋算法
    void makeMoves();

private:
    Difficulty difficulty; // 游戏难度

    // 确定当前战斗阶段状态
    BattleStage determineCurrentBattleStage() const;

    // 计算英雄的综合能力
    ProfessionPreference calculateChampionProficiency(const ChampionAttributes& attributes) const;

    // 计算战斗英雄分数
    double calculateChampionScore(const ChampionAttributes& attributes) const;

    // 计算战斗英雄分数
    double calculateChampionScore(const ChampionCategory championCategory) const;

    // 检查是否有可升级英雄
    bool isUplevelAvailable() const;

    // 选择最适合升级的英雄
    ChampionCategory selectBestChampionForUplevel() const;

    // 升级后更新英雄状态
    void updateChampionAfterUplevel(const ChampionCategory championCategory);

    // 优化战斗英雄队伍配置
    void optimizeChampionCollection();

    // 部署战斗英雄（简单模式与困难模式）
    std::vector<ChampionCategory> deployChampionsByOrder(const int maxChampions);

    // 部署战斗英雄（正常模式）
    std::vector<ChampionCategory> deployChampionsByRandom(const int maxChampions);

    // 部署战斗英雄位置
    void deployChampionPositions(const std::vector<ChampionCategory>& battleChampions);

    // 部署战斗英雄
    void deployChampions();
};

#endif // !_AI_PLAYER_H_