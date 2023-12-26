/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     AIPlayer.cpp
 * File Function: AIPlayer���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/27
 ****************************************************************/

#include "AIPlayer.h"
#include <algorithm>
#include <time.h>
#include <queue>

// ���캯��
AIPlayer::AIPlayer(const std::string nickname, const Difficulty difficulty_) :
    Player(nickname),
    difficulty(difficulty_) {}

// AI �����㷨
void AIPlayer::makeMoves()
{
    champions = countChampionCategories();
    optimizeChampionCollection();
    deployChampions();
}

// ͳ�Ƹ���ս��Ӣ������
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

// ��ȡ��ǰ���Ʒ���
int AIPlayer::getStageScore() const
{
    int score = 0;
    for (const auto& e : champions) {
        score += CHAMPION_ATTR_MAP.at(e.first).price;
    }
    return score;
}

// ȷ����ǰս���׶�״̬
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

// Ϊ�ض�ս���׶����ѡ��Ӣ��
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

// ����Ӣ�۵��ۺ�����
ProfessionPreference AIPlayer::calculateChampionProficiency(const ChampionAttributes& attributes) const
{
    const double defenseScore = (attributes.healthPoints * attributes.defenseCoefficient) / static_cast<double>(DEFENSE_SCORE_COEFFICIENT);
    const double attackScore = (attributes.attackDamage * attributes.attackSpeed * attributes.attackRange) / static_cast<double>(ATTACK_SCORE_COEFFICIENT);
    const double speedScore = attributes.movementSpeed / static_cast<double>(SPEED_SCORE_COEFFICIENT);
    return { defenseScore, attackScore, speedScore };
}

// ����ս��Ӣ�۷���
double AIPlayer::calculateChampionScore(const ChampionAttributes& attributes) const
{
    ProfessionPreference preference = calculateChampionProficiency(attributes);
    return DEFENSE_SCORE_WEIGHT * preference.defenseScore
        + ATTACK_SCORE_WEIGHT * preference.attackScore
        + SPEED_SCORE_WEIGHT * preference.speedScore;
}

// ����ս��Ӣ�۷���
double AIPlayer::calculateChampionScore(const ChampionCategory championCategory) const
{
    return calculateChampionScore(CHAMPION_ATTR_MAP.at(championCategory));
}

// ����Ƿ��п�����Ӣ��
bool AIPlayer::isUplevelAvailable() const
{
    for (const auto& champion : champions) {
        if (champion.second >= CHAMPION_UPLEVEL_COUNT - 1 && CHAMPION_ATTR_MAP.at(champion.first).level < CHAMPION_UPLEVEL_COUNT - 1) {
            return true;
        }
    }
    return false;
}

// ѡ�����ʺ�������Ӣ��
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

// ���������Ӣ��״̬
void AIPlayer::updateChampionAfterUplevel(const ChampionCategory championCategory)
{
    champions[championCategory]--;
    champions[championCategory]--;
    champions[static_cast<ChampionCategory>(championCategory + 1)]++;
}

// �Ż�ս��Ӣ�۶�������
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

// ��ȡ�����
int AIPlayer::getRandom(const int n) const
{
    return rand() % n + 1;
}

// ����ս��Ӣ��
void AIPlayer::deployChampions()
{
    // ��ʼ����ͼ
    for (int i = 0; i < PLACE_MAP_ROWS; i++) {
        std::fill_n(battleMap[i], BATTLE_MAP_COLUMNS, NoChampion);
    }
    std::fill_n(waitingMap, WAITING_MAP_COUNT, NoChampion);

    // �������ս��Ӣ������
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

    // �������ȶ�������ս��Ӣ��
    auto comp = [this](ChampionCategory a, ChampionCategory b) {
        return calculateChampionScore(a) > calculateChampionScore(b);
        };
    std::priority_queue<ChampionCategory, std::vector<ChampionCategory>, decltype(comp)> orderedChampions(comp);
    for (const auto& entry : champions) {
        for (int i = 0; i < entry.second; i++) {
            orderedChampions.push(entry.first);
        }
    }

    // ѡ��ս��Ӣ��
    std::vector<ChampionCategory> chosenChampions;
    for (int i = 0; i < maxChampions && !orderedChampions.empty(); i++) {
        chosenChampions.push_back(orderedChampions.top());
        orderedChampions.pop();
    }

    // ����ս����ս��Ӣ��
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

    // �����ս��ս��Ӣ��
    for (int i = 0; i < WAITING_MAP_COUNT && !orderedChampions.empty(); i++) {
        waitingMap[i] = orderedChampions.top();
        orderedChampions.pop();
    }
}