/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     AIPlayer.h
 * File Function: AIPlayer��Ķ���
 * Author:        �ּ���
 * Update Date:   2023/12/20
 ****************************************************************/

#pragma once
#ifndef _AI_PLAYER_H_
#define _AI_PLAYER_H_

#include "Player.h"
 /*
  * Class Name:     AIPlayer
  * Class Function: AI �����
  */
class AIPlayer : public Player {
public:
	// ���캯��
	AIPlayer(std::string nickname, Difficulty difficulty_);

	// AI �����㷨
	void makeMoves();

private:
	Difficulty difficulty; // ��Ϸ�Ѷ�
	//��ǰ�ҵ�Ӣ����
	std::map<ChampionCategory, int>my_champions;

	/*���ߺ���*/

	//ˢ�½���,ͳ�Ƶ�ǰӢ��
	std::map<ChampionCategory, int> countMyChampions() const;
	// ��ȡ���Ʒ���
	int getStageScore() const;
	// ���Ʒ���->��Ϸ�׶�
	STAGE getStage() const;
	// ��Ϸ�׶�->������Ӣ��
	ChampionCategory getRandomChampion(STAGE stage) const;
	//Ӣ�۵Ĺ������Ժ���
	ProfessionPreference evaluateTheirScore(const ChampionAttributes& t) const;
	//��ȡӢ�۵ľ����������ѡ->ս����
	double getChampionScore(const ChampionAttributes& t) const;
	double getChampionScore(ChampionCategory t) const { return getChampionScore(CHAMPION_ATTR_MAP.at(t)); };
	//�ܷ����ǣ��Ƿ���ڿ�����Ӣ�ۣ�
	inline bool canStarUp() const;
	//������ǣ��ҳ���������ǵ�Ӣ��
	ChampionCategory findBestStarUpChampion() const;
	//����֮���ԭMap���ڲ��ı�
	void eraseAndPush(ChampionCategory champion);

	/*�ı�ȴ���*/

	//�����㷨�ĺ��ģ�
	void enrichMyChampions();//��ı�waitingMap��Ա

	/*�ı�battle��*/

	//ѡ��Ӣ���ϳ�
	void chooseChampionToBattle();



};

#endif // !_AI_PLAYER_H_
