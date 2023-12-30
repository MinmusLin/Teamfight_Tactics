/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     HumanPlayer.h
 * File Function: HumanPlayer类的定义
 * Author:        林继申、杨宇琨
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
 * Class Function: 人类玩家类
 */
class HumanPlayer : public Player {
public:
    // 构造函数
    HumanPlayer(const std::string nickname);

    // 析构函数
    ~HumanPlayer();

    // 设置当前场景指针
    void setCurrentScene(cocos2d::Scene* currentScene);

    // 刷新商店
    void refreshShop();

    // 获取战斗区最大英雄数量
    int getMaxBattleChampionCount() const;

    // 获取战斗区当前英雄数量
    int getCurrentBattleChampionCount() const;

    // 增加战斗区英雄数量
    void addBattleChampionCount(const int num = 1);

    // 获取金币数量
    int getGoldCoin() const;

    // 增加金币数量
    void addGoldCoin(const int num);

    // 初始化战斗英雄删除按钮
    void initializeDeleteChampionButton();

    // 设置战斗区地图
    void setBattleMap(const ChampionCategory battleMap[][BATTLE_MAP_COLUMNS]);

private:
    cocos2d::Scene* currentScene;                                         // 当前场景指针
    ChampionCategory shopChampionCategory[MAX_SELECTABLE_CHAMPION_COUNT]; // 商店战斗英雄种类
    HoverButton* shopChampionButton[MAX_SELECTABLE_CHAMPION_COUNT];       // 商店战斗英雄按钮指针
    HoverButton* deleteChampionButton;                                    // 战斗英雄删除按钮指针
    Champion* battleChampion[BATTLE_MAP_ROWS][BATTLE_MAP_COLUMNS];        // 战斗区战斗英雄指针
    Champion* waitingChampion[WAITING_MAP_COUNT];                         // 候战区战斗英雄指针
    ChampionAttributesLayer* championAttributesLayer;                     // 战斗英雄属性层类指针
    PlacementMarkerLayer* placementMarkerLayer;                           // 放置标记层类指针
    cocos2d::Sprite* nearestPlacementMarker;                              // 最近放置标记指针
    Location startLocation;                                               // 战斗英雄移动起始位置属性
    int maxBattleChampionCount;                                           // 战斗区最大英雄数量
    int goldCoin;                                                         // 金币数量

    // 添加战斗英雄
    void addChampion(const int index);

    // 按下鼠标事件触发函数
    void onMouseDown(cocos2d::Event* event, cocos2d::Sprite* championSprite);

    // 移动鼠标事件触发函数
    void onMouseMove(cocos2d::Event* event, cocos2d::Sprite* championSprite);

    // 释放鼠标事件触发函数
    void onMouseUp(cocos2d::Event* event, cocos2d::Sprite* championSprite);

    // 从商店中移除战斗英雄
    void removeChampionFromShop(const int index);

    // 开启显示战斗英雄属性层和放置标记层
    void showChampionAttributesLayerAndPlacementMarkerLayer(const ChampionCategory championCategory);

    // 关闭显示战斗英雄属性层和放置标记层
    void hideChampionAttributesLayerAndPlacementMarkerLayer();

    // 删除当前战斗英雄
    void deleteCurrentChampion();

    // 刷新金币数量标签
    void refreshCoinLabel(int num);

    // 统计特定种类战斗英雄的数量
    int countSpecificChampion(const ChampionCategory championCategory);

    // 升级战斗英雄
    void uplevelChampion(const ChampionCategory championCategory);

    // 寻找最近可放置坐标
    cocos2d::Vec2 findNearestPoint(cocos2d::Sprite* championSprite);

    // 刷新商店战斗英雄种类
    void refreshShopChampionCategory();
};

#endif // !_HUMAN_PLAYER_H_