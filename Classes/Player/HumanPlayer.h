/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     HumanPlayer.h
 * File Function: HumanPlayer��Ķ���
 * Author:        �ּ���
 * Update Date:   2023/12/20
 ****************************************************************/

#pragma once
#ifndef _HUMAN_PLAYER_H_
#define _HUMAN_PLAYER_H_

#include "Player.h"
#include "Button/HoverButton.h"
#include "Champion/Champion.h"

/*
 * Class Name:     HumanPlayer
 * Class Function: ���������
 */
class HumanPlayer : public Player {
public:
    // ���캯��
    HumanPlayer(std::string nickname);

    // ��������
    ~HumanPlayer();

    // ˢ���̵�
    void refreshShop(cocos2d::Scene* currentScene);

    // ��ȡս�������Ӣ������
    int getMaxBattleChampionCount() const;

    // ��ȡս������ǰӢ������
    int getCurrentBattleChampionCount() const;

    // ����ս����Ӣ������
    void addBattleChampionCount(cocos2d::Scene* currentScene, const int num = 1);

    // ��ȡ�������
    int getGoldCoin() const;

private:
    ChampionCategory shopChampionCategory[MAX_SELECTABLE_CHAMPION_COUNT]; // �̵�ս��Ӣ������
    HoverButton* shopChampionButton[MAX_SELECTABLE_CHAMPION_COUNT];       // �̵�ս��Ӣ�۰�ť
    Champion* battleChampion[BATTLE_MAP_ROWS][BATTLE_MAP_COLUMNS];        // ս����ս��Ӣ��ָ��
    Champion* waitingChampion[WAITING_MAP_COUNT];                         // ��ս��ս��Ӣ��ָ��
    Location startLocation;                                               // ս��Ӣ���ƶ���ʼλ������
    int maxBattleChampionCount;                                           // ս�������Ӣ������
    int goldCoin;                                                         // �������

    // ���ս��Ӣ��
    void addChampion(const int index, cocos2d::Scene* currentScene);

    // ��������¼���������
    void onMouseDown(cocos2d::Event* event, cocos2d::Sprite* championSprite);

    // �ƶ�����¼���������
    void onMouseMove(cocos2d::Event* event, cocos2d::Sprite* championSprite);

    // �ͷ�����¼���������
    void onMouseUp(cocos2d::Event* event, cocos2d::Sprite* championSprite);

    // ���̵����Ƴ�ս��Ӣ��
    void removeChampionFromShop(const int index, cocos2d::Scene* currentScene);

    // ˢ���̵�ս��Ӣ������
    void refreshShopChampionCategory();
};

#endif // !_HUMAN_PLAYER_H_