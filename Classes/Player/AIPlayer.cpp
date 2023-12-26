/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     AIPlayer.cpp
 * File Function: AIPlayer���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/24
 ****************************************************************/

#include "AIPlayer.h"
#include<time.h>
#include<queue>
 // ���캯��
AIPlayer::AIPlayer(const std::string nickname, const Difficulty difficulty_) :
	Player(nickname),
	difficulty(difficulty_) {
	my_champions;
}

// ��ȡ���Ʒ���
int AIPlayer::getStageScore() const {
	int score{ 0 };
	for (const auto& e : my_champions)
		score += CHAMPION_ATTR_MAP.at(e.first).price;
	return score;
}
// ���Ʒ���->��Ϸ�׶�
STAGE AIPlayer::getStage() const {
	//��ǰ���Ʒ���
	const auto local_score = this->getStageScore();

	STAGE local_stage;
	//��������
	local_stage = local_score < 10 ? stage1 : (local_score < 50 ? stage2 : stage3);
	return local_stage;
}
// ��Ϸ�׶�->������Ӣ��
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

// Ӣ�۵ĸ�������
ProfessionPreference AIPlayer::evaluateTheirScore(const ChampionAttributes& t) const {
	double defend_score{ 0 };
	defend_score = (t.healthPoints * t.defenseCoefficient) / 200.0;
	double attack_score{ 0 };
	attack_score = (t.attackDamage * t.attackSpeed * t.attackRange) / 30.0;
	double speed_score{ 0 };
	speed_score = t.movementSpeed / 1.0;
	ProfessionPreference tmp;
	//������Ե���ϵ��
	tmp.defendScore = defend_score;
	tmp.attackScore = attack_score;
	tmp.speedScore = speed_score;
	return tmp;
}
// ��ȡӢ�۵ľ����������ѡ->ս����������ʵ�����Ӣ�ۣ�
double AIPlayer::getChampionScore(const ChampionAttributes& t) const {
	auto it = evaluateTheirScore(t);
	double score;
	score = it.speedScore + 2 * it.defendScore + 2.5 * it.attackScore;
	return score;
}
// ͳ�Ƶ�ǰӢ��
std::map<ChampionCategory, int> AIPlayer::countMyChampions() const {
	//ͳ�Ƶ�ǰӢ������
	std::map<ChampionCategory, int> category_count;
	for (const auto& e : waitingMap)
		category_count[e]++;
	for (const auto& e : battleMap)
		for (const auto& each : e)
			category_count[each]++;
	return category_count;
}

// �ܷ����ǣ��Ƿ���ڿ�����Ӣ�ۣ�
bool AIPlayer::canStarUp() const {
	for (const auto& e : my_champions)
		if (e.second > 1 && CHAMPION_ATTR_MAP.at(e.first).level < 2)
			return true;
	return false;
}
// ������ǣ��ҳ���������ǵ�Ӣ��
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
// ����֮���ԭMap�ĸ�Ӣ���ڲ��ı�
void AIPlayer::eraseAndPush(ChampionCategory champion) {
	my_champions[champion]--;
	my_champions[champion]--;
	ChampionCategory tmp = static_cast<ChampionCategory>(champion + 1);
	my_champions[tmp]++;
}
//���Ӣ��������������ĳЩӢ�ۣ�����LocalStatus��
void AIPlayer::enrichMyChampions() {//��ı�waitingMap��Ա
	//������ƣ���Ϸ�׶�1����Ϸ�׶�2����Ϸ�׶�3

	//�����Ǿ�����
	if (canStarUp()) {
		ChampionCategory selected_champion = findBestStarUpChampion();
		eraseAndPush(selected_champion);
		return;
	}
	//�������Ǿ���������
	else {
		STAGE local_stage = getStage();
		auto selected_champion = getRandomChampion(local_stage);
		my_champions[selected_champion]++;
		return;
	}
}
//ѡ��Ӣ���ϳ���ʣ��Ӣ�۴��ڱ�ս��
void AIPlayer::chooseChampionToBattle() {
	//�����ս��
	for (int i = 0; i < BATTLE_MAP_ROWS; i++)
		for (int j = 0; j < BATTLE_MAP_COLUMNS; j++)
			battleMap[i][j] = NoChampion;
	//��ձ�ѡ��
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

// AI �����㷨
void AIPlayer::makeMoves() {
	my_champions = countMyChampions();
	this->enrichMyChampions();
	this->chooseChampionToBattle();
}