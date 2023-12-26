/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     AIPlayer.h
 * File Function: AIPlayer类的定义
 * Author:        林继申
 * Update Date:   2023/12/20
 ****************************************************************/

#pragma once
#ifndef _AI_PLAYER_H_
#define _AI_PLAYER_H_

#include "Player.h"
 /*
  * Class Name:     AIPlayer
  * Class Function: AI 玩家类
  */
class AIPlayer : public Player {
public:
	// 构造函数
	AIPlayer(std::string nickname, Difficulty difficulty_);

	// AI 落棋算法
	void makeMoves();

private:
	Difficulty difficulty; // 游戏难度
	//当前我的英雄们
	std::map<ChampionCategory, int>my_champions;

	/*工具函数*/

	//刷新界面,统计当前英雄
	std::map<ChampionCategory, int> countMyChampions() const;
	// 获取局势分数
	int getStageScore() const;
	// 局势分数->游戏阶段
	STAGE getStage() const;
	// 游戏阶段->获得随机英雄
	ChampionCategory getRandomChampion(STAGE stage) const;
	//英雄的估算属性函数
	ProfessionPreference evaluateTheirScore(const ChampionAttributes& t) const;
	//获取英雄的具体分数（待选->战斗）
	double getChampionScore(const ChampionAttributes& t) const;
	double getChampionScore(ChampionCategory t) const { return getChampionScore(CHAMPION_ATTR_MAP.at(t)); };
	//能否升星（是否存在可升星英雄）
	inline bool canStarUp() const;
	//如果升星，找出最合适升星的英雄
	ChampionCategory findBestStarUpChampion() const;
	//升星之后对原Map的内部改变
	void eraseAndPush(ChampionCategory champion);

	/*改变等待区*/

	//调整算法的核心：
	void enrichMyChampions();//会改变waitingMap成员

	/*改变battle区*/

	//选择英雄上场
	void chooseChampionToBattle();



};

#endif // !_AI_PLAYER_H_
