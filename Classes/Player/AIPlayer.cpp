/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     AIPlayer.cpp
 * File Function: AIPlayer类的实现
 * Author:        林继申
 * Update Date:   2023/12/27
 ****************************************************************/

#include "AIPlayer.h"
#include <algorithm>
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

// 统计各类战斗英雄数量
std::map<ChampionCategory, int> AIPlayer::countChampionCategories() const
{
    std::map<ChampionCategory, int> championsCount;
    for (const auto& champion : waitingMap) {
        championsCount[champion]++;
    }
    for (const auto& championInRow : battleMap) {
        for (const auto& championInCol : championInRow) {
            championsCount[championInCol]++;
        }
    }
    return championsCount;
}

// 获取当前局势分数
int AIPlayer::getStageScore() const
{
    int score = 0;
    for (const auto& e : champions) {
        score += CHAMPION_ATTR_MAP.at(e.first).price;
    }
    return score;
}

// 确定当前战斗阶段状态
BattleStage AIPlayer::determineCurrentBattleStage() const
{
    const int stageScore = this->getStageScore();
    if (stageScore < EARLY_MIDDLE_STAGE_THRESHOLD) {
        return EarlyStage;
    }
    else if (stageScore < MIDDLE_LATE_STAGE_THRESHOLD) {
        return MiddleStage;
    }
    else {
        return LateStage;
    }
}

// 为特定战斗阶段随机选择英雄
ChampionCategory AIPlayer::selectRandomChampion(const BattleStage stage) const
{
    const ChampionCategory* championLevels[] = { FIRST_LEVEL, SECOND_LEVEL, THIRD_LEVEL, FOURTH_LEVEL, FIFTH_LEVEL };
    int random = getRandom(CHAMPION_CATEGORY_NUMBERS), cumulativeRate = 0;
    ChampionCategory selectedChampion = NoChampion;
    for (int i = 0; i < CHAMPION_CATEGORY_NUMBERS / BATTLE_STAGE_NUMBERS; i++) {
        cumulativeRate += STAGE_WITH_RATE_OF_CHAMPIONS[static_cast<int>(stage)][i];
        if (random <= cumulativeRate) {
            selectedChampion = championLevels[i][getRandom(CHAMPION_CATEGORY_NUMBERS / BATTLE_STAGE_NUMBERS + 1 - i) - 1];
            break;
        }
    }
    return selectedChampion;
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
    ProfessionPreference preference = calculateChampionProficiency(attributes);
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
    if (isUplevelAvailable()) {
        ChampionCategory selectedChampion = selectBestChampionForUplevel();
        updateChampionAfterUplevel(selectedChampion);
    }
    else {
        BattleStage currentStage = determineCurrentBattleStage();
        ChampionCategory selectedChampion = selectRandomChampion(currentStage);
        champions[selectedChampion]++;
    }
}

// 获取随机数
int AIPlayer::getRandom(const int n) const
{
    return rand() % n + 1;
}

// 部署战斗英雄
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
    std::vector<ChampionCategory> chosenChampions;
    for (int i = 0; i < maxChampions && !orderedChampions.empty(); i++) {
        chosenChampions.push_back(orderedChampions.top());
        orderedChampions.pop();
    }

    // 部署战斗区战斗英雄
    switch (chosenChampions.size()) {
        case 8:
            battleMap[0][5] = chosenChampions[7];
        case 7:
            battleMap[0][4] = chosenChampions[8];
        case 6:
            battleMap[0][1] = chosenChampions[5];
        case 5:
            battleMap[1][2] = chosenChampions[4];
        case 4:
            battleMap[1][4] = chosenChampions[3];
        case 3:
            battleMap[1][3] = chosenChampions[0];
            battleMap[0][2] = chosenChampions[1];
            battleMap[0][3] = chosenChampions[2];
            break;
        default:
            break;
    }

    // 部署候战区战斗英雄
    for (int i = 0; i < WAITING_MAP_COUNT && !orderedChampions.empty(); i++) {
        waitingMap[i] = orderedChampions.top();
        orderedChampions.pop();
    }
}