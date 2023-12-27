/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     AIPlayer.cpp
 * File Function: AIPlayer类的实现
 * Author:        杨兆镇、林继申
 * Update Date:   2023/12/27
 * License:       MIT License
 ****************************************************************/

#include "AIPlayer.h"
#include <algorithm>
#include <random>
#include <time.h>
#include <queue>

// 构造函数
AIPlayer::AIPlayer(const std::string nickname, const Difficulty difficulty_) :
    Player(nickname),
    difficulty(difficulty_) {}

// AI 落棋算法
void AIPlayer::makeMoves()
{
    champions = countChampionCategories();
    optimizeChampionCollection();
    deployChampions();
}

// 确定当前战斗阶段状态
BattleStage AIPlayer::determineCurrentBattleStage() const
{
    return evaluateStage(getStageScore());
}

// 计算英雄的综合能力
ProfessionPreference AIPlayer::calculateChampionProficiency(const ChampionAttributes& attributes) const
{
    const double defenseScore = (attributes.healthPoints * attributes.defenseCoefficient) / static_cast<double>(DEFENSE_SCORE_COEFFICIENT);
    const double attackScore = (attributes.attackDamage * attributes.attackSpeed * attributes.attackRange) / static_cast<double>(ATTACK_SCORE_COEFFICIENT);
    const double speedScore = attributes.movementSpeed / static_cast<double>(SPEED_SCORE_COEFFICIENT);
    return { defenseScore, attackScore, speedScore };
}

// 计算战斗英雄分数
double AIPlayer::calculateChampionScore(const ChampionAttributes& attributes) const
{
    const ProfessionPreference preference = calculateChampionProficiency(attributes);
    return DEFENSE_SCORE_WEIGHT * preference.defenseScore
        + ATTACK_SCORE_WEIGHT * preference.attackScore
        + SPEED_SCORE_WEIGHT * preference.speedScore;
}

// 计算战斗英雄分数
double AIPlayer::calculateChampionScore(const ChampionCategory championCategory) const
{
    return calculateChampionScore(CHAMPION_ATTR_MAP.at(championCategory));
}

// 检查是否有可升级英雄
bool AIPlayer::isUplevelAvailable() const
{
    for (const auto& champion : champions) {
        if (champion.second >= CHAMPION_UPLEVEL_COUNT - 1 && CHAMPION_ATTR_MAP.at(champion.first).level < CHAMPION_UPLEVEL_COUNT - 1) {
            return true;
        }
    }
    return false;
}

// 选择最适合升级的英雄
ChampionCategory AIPlayer::selectBestChampionForUplevel() const
{
    ChampionCategory bestChampion = NoChampion;
    for (const auto& champion : champions) {
        if (champion.second >= CHAMPION_UPLEVEL_COUNT - 1) {
            if (bestChampion == NoChampion) {
                bestChampion = champion.first;
            }
            else {
                bestChampion = calculateChampionScore(CHAMPION_ATTR_MAP.at(champion.first)) > calculateChampionScore(CHAMPION_ATTR_MAP.at(bestChampion)) ? champion.first : bestChampion;
            }
        }
    }
    return bestChampion;
}

// 升级后更新英雄状态
void AIPlayer::updateChampionAfterUplevel(const ChampionCategory championCategory)
{
    champions[championCategory]--;
    champions[championCategory]--;
    champions[static_cast<ChampionCategory>(championCategory + 1)]++;
}

// 优化战斗英雄队伍配置
void AIPlayer::optimizeChampionCollection()
{
    if (champions.empty()) {
        const BattleStage currentStage = determineCurrentBattleStage();
        for (int i = 0; i < BATTLE_AREA_MIN_CHAMPION_COUNT; i++) {
            champions[selectRandomChampion(currentStage)]++;
        }
    }
    else {
        if (isUplevelAvailable()) {
            updateChampionAfterUplevel(selectBestChampionForUplevel());
        }
        else {
            champions[selectRandomChampion(determineCurrentBattleStage())]++;
        }
    }
}

// 部署候战区战斗英雄（简单模式）
std::vector<ChampionCategory> AIPlayer::easyDeployChampions(const int maxChampions)
{
    // 基于优先队列排序战斗英雄
    auto comp = [this](ChampionCategory a, ChampionCategory b) {
        return calculateChampionScore(a) < calculateChampionScore(b);
        };
    std::priority_queue<ChampionCategory, std::vector<ChampionCategory>, decltype(comp)> orderedChampions(comp);
    for (const auto& entry : champions) {
        for (int i = 0; i < entry.second; i++) {
            orderedChampions.push(entry.first);
        }
    }

    // 选择战斗英雄
    std::vector<ChampionCategory> selectedChampions;
    for (int i = 0; i < maxChampions && !orderedChampions.empty(); i++) {
        selectedChampions.push_back(orderedChampions.top());
        orderedChampions.pop();
    }

    // 部署候战区战斗英雄
    for (int i = 0; i < WAITING_MAP_COUNT && !orderedChampions.empty(); i++) {
        waitingMap[i] = orderedChampions.top();
        orderedChampions.pop();
    }
    return selectedChampions;
}

// 部署候战区战斗英雄（正常模式）
std::vector<ChampionCategory> AIPlayer::normalDeployChampions(const int maxChampions)
{
    // 获取当前全部战斗英雄
    std::vector<ChampionCategory> allChampions;
    for (const auto& entry : champions) {
        for (int i = 0; i < entry.second; i++) {
            allChampions.push_back(entry.first);
        }
    }

    // 打乱当前全部战斗英雄
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(allChampions.begin(), allChampions.end(), g);

    // 选择战斗英雄
    std::vector<ChampionCategory> selectedChampions;
    for (int i = 0; i < maxChampions && !allChampions.empty(); i++) {
        selectedChampions.push_back(allChampions.back());
        allChampions.pop_back();
    }

    // 部署候战区战斗英雄
    for (int i = 0; i < WAITING_MAP_COUNT && !allChampions.empty(); i++) {
        waitingMap[i] = allChampions.back();
        allChampions.pop_back();
    }
    return selectedChampions;
}

// 部署候战区战斗英雄（困难模式）
std::vector<ChampionCategory> AIPlayer::hardDeployChampions(const int maxChampions)
{
    // 基于优先队列排序战斗英雄
    auto comp = [this](ChampionCategory a, ChampionCategory b) {
        return calculateChampionScore(a) > calculateChampionScore(b);
        };
    std::priority_queue<ChampionCategory, std::vector<ChampionCategory>, decltype(comp)> orderedChampions(comp);
    for (const auto& entry : champions) {
        for (int i = 0; i < entry.second; i++) {
            orderedChampions.push(entry.first);
        }
    }

    // 选择战斗英雄
    std::vector<ChampionCategory> selectedChampions;
    for (int i = 0; i < maxChampions && !orderedChampions.empty(); i++) {
        selectedChampions.push_back(orderedChampions.top());
        orderedChampions.pop();
    }

    // 部署候战区战斗英雄
    for (int i = 0; i < WAITING_MAP_COUNT && !orderedChampions.empty(); i++) {
        waitingMap[i] = orderedChampions.top();
        orderedChampions.pop();
    }
    return selectedChampions;
}

// 部署战斗区英雄
void AIPlayer::deployChampions()
{
    // 初始化地图
    for (int i = 0; i < PLACE_MAP_ROWS; i++) {
        std::fill_n(battleMap[i], BATTLE_MAP_COLUMNS, NoChampion);
    }
    std::fill_n(waitingMap, WAITING_MAP_COUNT, NoChampion);

    // 计算最大战斗英雄数量
    int maxChampions = 2;
    const int currentStageScore = getStageScore();
    for (int i = 0; i < STAGE_SCORE_THRESHOLDS_COUNT; i++) {
        if (currentStageScore >= STAGE_SCORE_THRESHOLDS[i]) {
            maxChampions++;
        }
        else {
            break;
        }
    }

    // 选择战斗英雄
    std::vector<ChampionCategory> selectedChampions = (difficulty == Normal ? normalDeployChampions(maxChampions)
        : (difficulty == Easy ? easyDeployChampions(maxChampions) : hardDeployChampions(maxChampions)));

    // 部署战斗区战斗英雄
    switch (selectedChampions.size()) {
        case 8:
            battleMap[1][2] = selectedChampions[7];
        case 7:
            battleMap[1][5] = selectedChampions[8];
        case 6:
            battleMap[0][5] = selectedChampions[5];
        case 5:
            battleMap[1][3] = selectedChampions[4];
        case 4:
            battleMap[0][2] = selectedChampions[3];
        case 3:
            battleMap[1][4] = selectedChampions[0];
            battleMap[0][4] = selectedChampions[1];
            battleMap[0][3] = selectedChampions[2];
            break;
        default:
            break;
    }
}