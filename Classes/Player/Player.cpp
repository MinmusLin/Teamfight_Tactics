/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Player.cpp
 * File Function: Player���ʵ��
 * Author:        �ּ��ꡢ������
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#include <algorithm>
#include "Player.h"

// ���캯��
Player::Player(const std::string nickname) :
    name(nickname)
{
    for (int i = 0; i < PLACE_MAP_ROWS; i++) {
        std::fill_n(battleMap[i], BATTLE_MAP_COLUMNS, NoChampion);
    }
    std::fill_n(waitingMap, WAITING_MAP_COUNT, NoChampion);
}

// ��ȡս������ͼ
void Player::getBattleMap(ChampionCategory(*&battleMap)[BATTLE_MAP_COLUMNS])
{
    battleMap = this->battleMap;
}

// �����������ֵ
void Player::decreaseHealthPoints(const int num)
{
    healthPoints -= num;
    if (healthPoints <= 0) {
        healthPoints = 0;
    }
}

// ��ȡ�������ֵ
int Player::getHealthPoints() const
{
    return healthPoints;
}

// ��ȡ����ǳ�
std::string Player::getPlayerName() const
{
    return name;
}

// ��ȡ�����
int Player::getRandom(const int n) const
{
    return rand() % n + 1;
}

// ��ȡ��ǰ���Ʒ���
int Player::getStageScore() const
{
    int score = 0;
    for (const auto& entry : champions) {
        for (int i = 0; i < entry.second; i++) {
            score += CHAMPION_ATTR_MAP.at(entry.first).price;
        }
    }
    return score;
}

// ������ǰ����
BattleStage Player::evaluateStage(int stageScore) const
{
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

// ͳ�Ƹ���ս��Ӣ������
std::map<ChampionCategory, int> Player::countChampionCategories() const
{
    std::map<ChampionCategory, int> championsCount;
    for (const auto& champion : waitingMap) {
        if (champion != NoChampion) {
            championsCount[champion]++;
        }
    }
    for (const auto& championInRow : battleMap) {
        for (const auto& championInCol : championInRow) {
            if (championInCol != NoChampion) {
                championsCount[championInCol]++;
            }
        }
    }
    return championsCount;
}

// Ϊ�ض�ս���׶����ѡ��ս��Ӣ��
ChampionCategory Player::selectRandomChampion(const BattleStage stage) const
{
    const ChampionCategory* championLevels[] = { FIRST_LEVEL, SECOND_LEVEL, THIRD_LEVEL, FOURTH_LEVEL, FIFTH_LEVEL };
    const int random = getRandom(CHAMPION_CATEGORY_NUMBERS);
    int cumulativeRate = 0;
    ChampionCategory selectedChampion = NoChampion;
    for (int i = 0; i < CHAMPION_CATEGORY_NUMBERS / BATTLE_STAGE_NUMBERS; i++) {
        cumulativeRate += STAGE_WITH_RATE_OF_CHAMPIONS[static_cast<int>(stage)][i];
        if (random <= cumulativeRate) {
            selectedChampion = championLevels[i][getRandom(CHAMPION_CATEGORY_NUMBERS / BATTLE_STAGE_NUMBERS - i)];
            break;
        }
    }
    return selectedChampion;
}