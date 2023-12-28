/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     AIPlayer.cpp
 * File Function: AIPlayer���ʵ��
 * Author:        �������ּ���
 * Update Date:   2023/12/28
 * License:       MIT License
 ****************************************************************/

#include "AIPlayer.h"
#include <algorithm>
#include <random>
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

// ȷ����ǰս���׶�״̬
BattleStage AIPlayer::determineCurrentBattleStage() const
{
	return evaluateStage(getStageScore());
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
	const ProfessionPreference preference = calculateChampionProficiency(attributes);
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

// ����ս��Ӣ�ۺͺ�սӢ�ۣ���ģʽ������ģʽ��
std::vector<ChampionCategory> AIPlayer::deployBattleChampionsByOrder(const int maxChampions)
{
	// �������ȶ�������ս��Ӣ��
	auto comp = [this](ChampionCategory a, ChampionCategory b) {
		if (this->difficulty == Hard) {
			return calculateChampionScore(a) > calculateChampionScore(b); // ����ģʽ
		}
		else {
			return calculateChampionScore(a) < calculateChampionScore(b); // ��ģʽ
		}
		};
	std::priority_queue<ChampionCategory, std::vector<ChampionCategory>, decltype(comp)> orderedChampions(comp);
	for (const auto& entry : champions) {
		for (int i = 0; i < entry.second; i++) {
			orderedChampions.push(entry.first);
		}
	}

	// ѡ��ս��Ӣ��
	std::vector<ChampionCategory> selectedChampions;
	for (int i = 0; i < maxChampions && !orderedChampions.empty(); i++) {
		selectedChampions.push_back(orderedChampions.top());
		orderedChampions.pop();
	}

	// �����ս��ս��Ӣ��
	for (int i = 0; i < WAITING_MAP_COUNT && !orderedChampions.empty(); i++) {
		waitingMap[i] = orderedChampions.top();
		orderedChampions.pop();
	}
	return selectedChampions;
}

// ����ս��Ӣ�ۺͺ�սӢ�ۣ�����ģʽ��
std::vector<ChampionCategory> AIPlayer::deployBattleChampionsByRandom(const int maxChampions)
{
	// ��ȡ��ǰȫ��ս��Ӣ��
	std::vector<ChampionCategory> allChampions;
	for (const auto& entry : champions) {
		for (int i = 0; i < entry.second; i++) {
			allChampions.push_back(entry.first);
		}
	}

	// ���ҵ�ǰȫ��ս��Ӣ��
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(allChampions.begin(), allChampions.end(), g);

	// ѡ��ս��Ӣ��
	std::vector<ChampionCategory> selectedChampions;
	for (int i = 0; i < maxChampions && !allChampions.empty(); i++) {
		selectedChampions.push_back(allChampions.back());
		allChampions.pop_back();
	}

	// �����ս��ս��Ӣ��
	for (int i = 0; i < WAITING_MAP_COUNT && !allChampions.empty(); i++) {
		waitingMap[i] = allChampions.back();
		allChampions.pop_back();
	}
	return selectedChampions;
}

// ����ս����ս��Ӣ��λ��
void AIPlayer::deployBattleChampionPositions(const std::vector<ChampionCategory>& battleChampions) {
	// ����0 ~ n-1�������
	auto getRandom = [](int n) {
		srand(time(0));
		return rand() % n;
		};

	// ��ȡ���ݹ�����Χ�����ս��Ӣ�ۣ�������ΧС�Ŀ�ǰ
	auto comp = [this](ChampionCategory a, ChampionCategory b)
		{
			double aScore = CHAMPION_ATTR_MAP.at(a).attackRange * CHAMPION_ATTR_MAP.at(a).attackDamage;
			double bScore = CHAMPION_ATTR_MAP.at(b).attackRange * CHAMPION_ATTR_MAP.at(b).attackDamage;
			return a < b;
		};
	std::priority_queue<ChampionCategory, std::vector<ChampionCategory>, decltype(comp)> orderedChampions(comp);
	for (const auto& battleChampions : battleChampions) {
		orderedChampions.push(battleChampions);
	}

	// վ��ǰ����Ӣ������
	const int numsOfChampionsAhead = static_cast<int>(battleChampions.size() / 2.0);
	// վ�ں󷽵�Ӣ������
	const int numsOfChampionsBehind = battleChampions.size() - numsOfChampionsAhead;

	int row = getRandom(PLACE_MAP_ROWS), line = getRandom(BATTLE_MAP_COLUMNS);// ��ʱ����

	// ����ǰ��Ӣ��
	for (int i = 0; i < numsOfChampionsAhead; i++)
	{
		// ������ɷ���Ӣ�۵�λ��
		while (battleMap[row][line] != NoChampion)
		{
			line = getRandom(BATTLE_MAP_COLUMNS);
			switch (this->difficulty) 
			{
			case Easy:
				row = PLACE_MAP_ROWS - getRandom(PLACE_MAP_ROWS) - 1;
				break;
			case Normal:
				row = PLACE_MAP_ROWS - getRandom(PLACE_MAP_ROWS / 2) - 1;
				break;
			case Hard:
				row = PLACE_MAP_ROWS - getRandom(1) - 1;
				break;
			} 
		}
		// ����Ӣ��
		battleMap[row][line] = orderedChampions.top();
		orderedChampions.pop();
	}
	// �����Ӣ��
	for (int i = 0; i < numsOfChampionsBehind; i++)
	{
		// ������ɷ���Ӣ�۵�λ��
		while (battleMap[row][line] != NoChampion)
		{
			line = getRandom(BATTLE_MAP_COLUMNS);
			switch (this->difficulty)
			{
			case Easy:
				row = getRandom(PLACE_MAP_ROWS);
				break;
			case Normal:
				row = getRandom(PLACE_MAP_ROWS / 2);
				break;
			case Hard:
				row = getRandom(1);
				break;
			}
		}
		battleMap[row][line] = orderedChampions.top();
		orderedChampions.pop();
	}
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
	int maxChampions = DEPLOY_CHAMPIONS_MAX_COUNT;
	const int currentStageScore = getStageScore();
	for (int i = 0; i < STAGE_SCORE_THRESHOLDS_COUNT; i++) {
		if (currentStageScore >= STAGE_SCORE_THRESHOLDS[i]) {
			maxChampions++;
		}
		else {
			break;
		}
	}

	// ѡ��ս��Ӣ��
	std::vector<ChampionCategory> selectedChampions;
	if (difficulty == Normal) {
		selectedChampions = deployBattleChampionsByRandom(maxChampions);
	}
	else {
		selectedChampions = deployBattleChampionsByOrder(maxChampions);
	}

	deployBattleChampionPositions(selectedChampions);
	return;
}