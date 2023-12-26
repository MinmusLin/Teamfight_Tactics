/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     AIPlayer.cpp
 * File Function: AIPlayer类的实现
 * Author:        林继申
 * Update Date:   2023/12/24
 ****************************************************************/

#include "AIPlayer.h"
#include<time.h>
#include<queue>
 // 构造函数
AIPlayer::AIPlayer(const std::string nickname, const Difficulty difficulty_) :
	Player(nickname),
	difficulty(difficulty_) {
	my_champions;
}

// 获取局势分数
int AIPlayer::getStageScore() const {
	int score{ 0 };
	for (const auto& e : my_champions)
		score += CHAMPION_ATTR_MAP.at(e.first).price;
	return score;
}
// 局势分数->游戏阶段
STAGE AIPlayer::getStage() const {
	//当前局势分数
	const auto local_score = this->getStageScore();

	STAGE local_stage;
	//调整局势
	local_stage = local_score < 10 ? stage1 : (local_score < 50 ? stage2 : stage3);
	return local_stage;
}
// 游戏阶段->获得随机英雄
ChampionCategory AIPlayer::getRandomChampion(STAGE stage) const {
	srand(time(NULL));
	const ChampionCategory first[6] = { NoChampion,Champion1,Champion3,Champion5,Champion7,Champion9 };
	const ChampionCategory second[5] = { NoChampion,Champion11,Champion13,Champion15,Champion17 };
	const ChampionCategory third[4] = { NoChampion,Champion19,Champion21,Champion23 };
	const ChampionCategory forth[3] = { NoChampion,Champion25,Champion27 };
	const ChampionCategory fifth[2] = { NoChampion,Champion29 };

	const int stage_with_rate_of_champiom[3][5] = {
		{6, 4, 3, 2, 0},
		{5, 4, 3, 2, 1},
		{4, 5, 2, 2, 2},
	};
	srand(time(NULL));

	int random = rand() % 15 + 1;
	ChampionCategory selected = NoChampion;
	switch (stage) {
	case stage1:
		if (random <= stage_with_rate_of_champiom[0][0])
			selected = first[rand() % 5 + 1];
		else if (random <= stage_with_rate_of_champiom[0][0] + stage_with_rate_of_champiom[0][1])
			selected = second[rand() % 4 + 1];
		else if (random <= stage_with_rate_of_champiom[0][0] + stage_with_rate_of_champiom[0][1] + stage_with_rate_of_champiom[0][2])
			selected = third[rand() % 3 + 1];
		else if (random <= stage_with_rate_of_champiom[0][0] + stage_with_rate_of_champiom[0][1] + stage_with_rate_of_champiom[0][2] + stage_with_rate_of_champiom[0][3])
			selected = forth[rand() % 2 + 1];
		else // (random <= 15)
			selected = fifth[1];
		break;
	case stage2:
		if (random <= stage_with_rate_of_champiom[1][0])
			selected = first[rand() % 5 + 1];
		else if (random <= stage_with_rate_of_champiom[1][0] + stage_with_rate_of_champiom[1][1])
			selected = second[rand() % 4 + 1];
		else if (random <= stage_with_rate_of_champiom[1][0] + stage_with_rate_of_champiom[1][1] + stage_with_rate_of_champiom[1][2])
			selected = third[rand() % 3 + 1];
		else if (random <= stage_with_rate_of_champiom[1][0] + stage_with_rate_of_champiom[1][1] + stage_with_rate_of_champiom[1][2] + stage_with_rate_of_champiom[1][3])
			random = forth[rand() % 2 + 1];
		else // (random <= 15)
			random = fifth[1];
		break;
	case stage3:
		if (random <= stage_with_rate_of_champiom[2][0])
			random = first[rand() % 5 + 1];
		else if (random <= stage_with_rate_of_champiom[2][0] + stage_with_rate_of_champiom[2][1])
			random = second[rand() % 4 + 1];
		else if (random <= stage_with_rate_of_champiom[2][0] + stage_with_rate_of_champiom[2][1] + stage_with_rate_of_champiom[2][2])
			random = third[rand() % 3 + 1];
		else if (random <= stage_with_rate_of_champiom[2][0] + stage_with_rate_of_champiom[2][1] + stage_with_rate_of_champiom[2][2] + stage_with_rate_of_champiom[2][3])
			random = forth[rand() % 2 + 1];
		else // (random <= 15)
			random = fifth[1];
		break;
	}
	return selected;
}

// 英雄的各项数据
ProfessionPreference AIPlayer::evaluateTheirScore(const ChampionAttributes& t) const {
	double defend_score{ 0 };
	defend_score = (t.healthPoints * t.defenseCoefficient) / 200.0;
	double attack_score{ 0 };
	attack_score = (t.attackDamage * t.attackSpeed * t.attackRange) / 30.0;
	double speed_score{ 0 };
	speed_score = t.movementSpeed / 1.0;
	ProfessionPreference tmp;
	//这里可以调整系数
	tmp.defendScore = defend_score;
	tmp.attackScore = attack_score;
	tmp.speedScore = speed_score;
	return tmp;
}
// 获取英雄的具体分数（待选->战斗）（最合适的升星英雄）
double AIPlayer::getChampionScore(const ChampionAttributes& t) const {
	auto it = evaluateTheirScore(t);
	double score;
	score = it.speedScore + 2 * it.defendScore + 2.5 * it.attackScore;
	return score;
}
// 统计当前英雄
std::map<ChampionCategory, int> AIPlayer::countMyChampions() const {
	//统计当前英雄数量
	std::map<ChampionCategory, int> category_count;
	for (const auto& e : waitingMap)
		category_count[e]++;
	for (const auto& e : battleMap)
		for (const auto& each : e)
			category_count[each]++;
	return category_count;
}

// 能否升星（是否存在可升星英雄）
bool AIPlayer::canStarUp() const {
	for (const auto& e : my_champions)
		if (e.second > 1 && CHAMPION_ATTR_MAP.at(e.first).level < 2)
			return true;
	return false;
}
// 如果升星，找出最合适升星的英雄
ChampionCategory AIPlayer::findBestStarUpChampion() const {
	ChampionCategory best_champion = NoChampion;
	for (const auto& e : my_champions) {
		if (e.second > 1) {
			if (best_champion == NoChampion)
				best_champion = e.first;
			else
				best_champion = getChampionScore(CHAMPION_ATTR_MAP.at(e.first)) > getChampionScore(CHAMPION_ATTR_MAP.at(best_champion)) ? e.first : best_champion;
		}
	}
	return best_champion;
}
// 升星之后对原Map的该英雄内部改变
void AIPlayer::eraseAndPush(ChampionCategory champion) {
	my_champions[champion]--;
	my_champions[champion]--;
	ChampionCategory tmp = static_cast<ChampionCategory>(champion + 1);
	my_champions[tmp]++;
}
//添加英雄数量或者升星某些英雄（根据LocalStatus）
void AIPlayer::enrichMyChampions() {//会改变waitingMap成员
	//定义局势：游戏阶段1，游戏阶段2，游戏阶段3

	//能升星就升星
	if (canStarUp()) {
		ChampionCategory selected_champion = findBestStarUpChampion();
		eraseAndPush(selected_champion);
		return;
	}
	//不能升星就增加数量
	else {
		STAGE local_stage = getStage();
		auto selected_champion = getRandomChampion(local_stage);
		my_champions[selected_champion]++;
		return;
	}
}
//选择英雄上场，剩余英雄存于备战区
void AIPlayer::chooseChampionToBattle() {
	//清空作战区
	for (int i = 0; i < BATTLE_MAP_ROWS; i++)
		for (int j = 0; j < BATTLE_MAP_COLUMNS; j++)
			battleMap[i][j] = NoChampion;
	//清空备选区
	for (int i = 0; i < WAITING_MAP_COUNT; i++)
		waitingMap[i] = NoChampion;
	int max_champions{ 2 };
	const int eight_stage_threshold[6] = { 0,5,10,25,50,60 };
	auto status = getStageScore();
	for (int i = 0; i < 6; i++)
		if (status >= eight_stage_threshold[i]) max_champions++;
		else break;
	auto comp = [this](ChampionCategory a, ChampionCategory b) {return getChampionScore(a) > getChampionScore(b); };
	std::priority_queue<ChampionCategory, std::vector<ChampionCategory>, decltype(comp)> my_ordered_champions;
	for (const auto& e : my_champions) {
		for (int i = 0; i < e.second; i++)
			my_ordered_champions.push(e.first);
	}
	std::vector<ChampionCategory> my_chosen_champions;
	for (int i = 0; i < max_champions && !my_ordered_champions.empty(); i++) {
		my_chosen_champions.push_back(my_ordered_champions.top());
		my_ordered_champions.pop();
	}
	switch (my_chosen_champions.size()) {
	case 8:
		battleMap[0][5] = my_chosen_champions[7];
	case 7:
		battleMap[0][4] = my_chosen_champions[8];
	case 6:
		battleMap[0][1] = my_chosen_champions[5];
	case 5:
		battleMap[1][2] = my_chosen_champions[4];
	case 4:
		battleMap[1][4] = my_chosen_champions[3];
	case 3:
		battleMap[1][3] = my_chosen_champions[0];
		battleMap[0][2] = my_chosen_champions[1];
		battleMap[0][3] = my_chosen_champions[2];
		break;
	}

	for (int i = 0; i < WAITING_MAP_COUNT && !my_ordered_champions.empty(); i++) {
		waitingMap[i] = my_ordered_champions.top();
		my_ordered_champions.pop();
	}
	return;
}

// AI 落棋算法
void AIPlayer::makeMoves() {
	my_champions = countMyChampions();
	this->enrichMyChampions();
	this->chooseChampionToBattle();
}