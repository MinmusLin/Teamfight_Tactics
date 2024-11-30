/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     HumanPlayer.h
 * File Function: HumanPlayer��Ķ���
 * Author:        �ּ��ꡢ������
 * Update Date:   2023/12/31
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _HUMAN_PLAYER_H_
#define _HUMAN_PLAYER_H_

#include "Player.h"
#include "Button/HoverButton.h"
#include "Champion/Champion.h"
#include "Layer/ChampionAttributesLayer.h"
#include "Layer/PlacementMarkerLayer.h"

/*
 * Class Name:     HumanPlayer
 * Class Function: ���������
 */
class HumanPlayer : public Player {
public:
    // ���캯��
    HumanPlayer(const std::string nickname);

    // ��������
    ~HumanPlayer();

    // ���õ�ǰ����ָ��
    void setCurrentScene(cocos2d::Scene* currentScene);

    // ˢ���̵�
    void refreshShop();

    // ��ȡս�������Ӣ������
    int getMaxBattleChampionCount() const;

    // ��ȡս������ǰӢ������
    int getCurrentBattleChampionCount() const;

    // ����ս����Ӣ������
    void addBattleChampionCount(const int num = 1);

    // ��ȡ�������
    int getGoldCoin() const;

    // ���ӽ������
    void addGoldCoin(const int num);

    // ��ʼ��ս��Ӣ��ɾ����ť
    void initializeDeleteChampionButton();

    // ����ս������ͼ
    void setBattleMap(const ChampionCategory battleMap[][BATTLE_MAP_COLUMNS]);

private:
    cocos2d::Scene* currentScene;                                         // ��ǰ����ָ��
    ChampionCategory shopChampionCategory[MAX_SELECTABLE_CHAMPION_COUNT]; // �̵�ս��Ӣ������
    HoverButton* shopChampionButton[MAX_SELECTABLE_CHAMPION_COUNT];       // �̵�ս��Ӣ�۰�ťָ��
    HoverButton* deleteChampionButton;                                    // ս��Ӣ��ɾ����ťָ��
    Champion* battleChampion[BATTLE_MAP_ROWS][BATTLE_MAP_COLUMNS];        // ս����ս��Ӣ��ָ��
    Champion* waitingChampion[WAITING_MAP_COUNT];                         // ��ս��ս��Ӣ��ָ��
    ChampionAttributesLayer* championAttributesLayer;                     // ս��Ӣ�����Բ���ָ��
    PlacementMarkerLayer* placementMarkerLayer;                           // ���ñ�ǲ���ָ��
    cocos2d::Sprite* nearestPlacementMarker;                              // ������ñ��ָ��
    Location startLocation;                                               // ս��Ӣ���ƶ���ʼλ������
    int maxBattleChampionCount;                                           // ս�������Ӣ������
    int goldCoin;                                                         // �������

    // ���ս��Ӣ��
    void addChampion(const int index);

    // ��������¼���������
    void onMouseDown(cocos2d::Event* event, cocos2d::Sprite* championSprite);

    // �ƶ�����¼���������
    void onMouseMove(cocos2d::Event* event, cocos2d::Sprite* championSprite);

    // �ͷ�����¼���������
    void onMouseUp(cocos2d::Event* event, cocos2d::Sprite* championSprite);

    // ���̵����Ƴ�ս��Ӣ��
    void removeChampionFromShop(const int index);

    // ������ʾս��Ӣ�����Բ�ͷ��ñ�ǲ�
    void showChampionAttributesLayerAndPlacementMarkerLayer(const ChampionCategory championCategory);

    // �ر���ʾս��Ӣ�����Բ�ͷ��ñ�ǲ�
    void hideChampionAttributesLayerAndPlacementMarkerLayer();

    // ɾ����ǰս��Ӣ��
    void deleteCurrentChampion();

    // ˢ�½��������ǩ
    void refreshCoinLabel(int num);

    // ͳ���ض�����ս��Ӣ�۵�����
    int countSpecificChampion(const ChampionCategory championCategory);

    // ����ս��Ӣ��
    void uplevelChampion(const ChampionCategory championCategory);

    // Ѱ������ɷ�������
    cocos2d::Vec2 findNearestPoint(cocos2d::Sprite* championSprite);

    // ˢ���̵�ս��Ӣ������
    void refreshShopChampionCategory();
};

#endif // !_HUMAN_PLAYER_H_