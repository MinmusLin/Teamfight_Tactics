/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     AIPlayer.h
 * File Function: AIPlayer��Ķ���
 * Author:        �������ּ���
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
 * Class Function: AI �����
 */
class AIPlayer : public Player {
public:
    // ���캯��
    AIPlayer(const std::string nickname, const Difficulty difficulty_);

    // AI �����㷨
    void makeMoves();

private:
    Difficulty difficulty; // ��Ϸ�Ѷ�

    // ȷ����ǰս���׶�״̬
    BattleStage determineCurrentBattleStage() const;

    // ����Ӣ�۵��ۺ�����
    ProfessionPreference calculateChampionProficiency(const ChampionAttributes& attributes) const;

    // ����ս��Ӣ�۷���
    double calculateChampionScore(const ChampionAttributes& attributes) const;

    // ����ս��Ӣ�۷���
    double calculateChampionScore(const ChampionCategory championCategory) const;

    // ����Ƿ��п�����Ӣ��
    bool isUplevelAvailable() const;

    // ѡ�����ʺ�������Ӣ��
    ChampionCategory selectBestChampionForUplevel() const;

    // ���������Ӣ��״̬
    void updateChampionAfterUplevel(const ChampionCategory championCategory);

    // �Ż�ս��Ӣ�۶�������
    void optimizeChampionCollection();

    // ����ս��Ӣ�ۣ���ģʽ������ģʽ��
    std::vector<ChampionCategory> deployChampionsByOrder(const int maxChampions);

    // ����ս��Ӣ�ۣ�����ģʽ��
    std::vector<ChampionCategory> deployChampionsByRandom(const int maxChampions);

    // ����ս��Ӣ��λ��
    void deployChampionPositions(const std::vector<ChampionCategory>& battleChampions);

    // ����ս��Ӣ��
    void deployChampions();
};

#endif // !_AI_PLAYER_H_