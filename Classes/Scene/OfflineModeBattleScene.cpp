/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeBattleScene.cpp
 * File Function: OfflineModeBattleScene类的实现
 * Author:        杨宇琨、林继申
 * Update Date:   2023/12/25
 ****************************************************************/

#include "OfflineModeBattleScene.h"
#include "Control/OfflineModeControl.h"
#include "LocationMap/LocationMap.h"

// 命名空间
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Vec2;

// 练习模式游戏控制类
extern OfflineModeControl* g_offlineModeControl;

// 当前场景战斗区战斗英雄指针
static Champion* battleChampion[BATTLE_AREA_MAX_CHAMPION_COUNT * 2] = { nullptr };

// 当前场景战斗区战斗英雄数量
static int index = 0;

// 创建场景
Scene* OfflineModeBattleScene::createScene()
{
    auto scene = Scene::create();
    auto layer = OfflineModeBattleScene::create();
    scene->addChild(layer);
    return scene;
}

// 初始化场景
bool OfflineModeBattleScene::init()
{
    // 创建场景
    if (!Scene::init()) {
        return false;
    }

    // 加载背景
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/OfflineModeBattleScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // 初始化对战类
    g_offlineModeControl->initializeBattle();

    // 遍历战斗区地图
    for (int i = 0; i < BATTLE_MAP_ROWS; i++) {
        for (int j = 0; j < BATTLE_MAP_COLUMNS; j++) {
            if (g_offlineModeControl->getBattle()->getChampion(i, j) != nullptr) {
                // 显示所有战斗英雄
                g_offlineModeControl->getBattle()->getChampion(i, j)->getSprite()->setPosition(LocationMap::getInstance().getLocationMap().at({ BattleArea, i * BATTLE_MAP_COLUMNS + j }));
                this->addChild(g_offlineModeControl->getBattle()->getChampion(i, j)->getSprite());

                // 计算初始战斗英雄个数
                if (i < PLACE_MAP_ROWS) {
                    g_offlineModeControl->getBattle()->addMyCount();
                }
                else {
                    g_offlineModeControl->getBattle()->addEnemyCount();
                }

                // 绑定战斗类
                g_offlineModeControl->getBattle()->getChampion(i, j)->setBattle(g_offlineModeControl->getBattle());
                g_offlineModeControl->getBattle()->getChampion(i, j)->setCurrentPosition(i, j);
                battleChampion[index++] = g_offlineModeControl->getBattle()->getChampion(i, j);
            }
            else {
                continue;
            }
        }
    }

    // 启用每一帧被自动调用的 update 方法
    this->scheduleUpdate();

    return true;
}

// 每一帧被自动调用的 update 方法
void OfflineModeBattleScene::update(float delta)
{
    // 更新战斗英雄数量
    g_offlineModeControl->getBattle()->resetCount();
    for (int i = 0; i < BATTLE_MAP_ROWS; i++) {
        for (int j = 0; j < BATTLE_MAP_COLUMNS; j++) {
            if (g_offlineModeControl->getBattle()->getChampion(i, j) != nullptr) {
                if (g_offlineModeControl->getBattle()->getChampion(i, j)->getCamp()) {
                    g_offlineModeControl->getBattle()->addMyCount();
                }
                else {
                    g_offlineModeControl->getBattle()->addEnemyCount();
                }
            }
            else {
                continue;
            }
        }
    }

    // 判断战斗是否结束
    if (g_offlineModeControl->getBattle()->getEnemyCount() == 0 || g_offlineModeControl->getBattle()->getMyCount() == 0) {
        // 关闭每一帧被自动调用的 update 方法
        this->unscheduleUpdate();

        // 设置战斗胜负状态
        if (g_offlineModeControl->getBattle()->getEnemyCount() == 0 && g_offlineModeControl->getBattle()->getMyCount() == 0) {
            g_offlineModeControl->getBattle()->setBattleSituation(Draw);
        }
        else if (g_offlineModeControl->getBattle()->getEnemyCount() == 0) {
            g_offlineModeControl->getBattle()->setBattleSituation(Win);
        }
        else {
            g_offlineModeControl->getBattle()->setBattleSituation(Lose);
        }

        // 释放练习模式对战场景
        cocos2d::Director::getInstance()->getRunningScene()->unscheduleUpdate();
        cocos2d::Director::getInstance()->popScene();

        // 重置对战类
        g_offlineModeControl->releaseBattle();
        for (int i = 0; i < index; i++) {
            if (battleChampion[i] != nullptr) {
                battleChampion[i] = nullptr;
            }
        }
        index = 0;

        return;
    }

    // 更新战斗英雄
    for (int i = 0; i < index; i++) {
        if (battleChampion[i] != nullptr) { // 存在战斗英雄
            if (battleChampion[i]->getAttributes().healthPoints > 0) { // 角色存活
                if (battleChampion[i]->getIsMoving()) { // 角色正在移动
                    // 增加移动时间间隔
                    battleChampion[i]->addMoveIntervalTimer(delta);

                    if (battleChampion[i]->getMoveIntervalTimer() >= (1.0f / battleChampion[i]->getAttributes().movementSpeed)) { // 达到停止移动条件
                        // 停止战斗英雄移动
                        battleChampion[i]->getSprite()->stopAction(battleChampion[i]->getCurrentMove());

                        // 重置移动时间间隔
                        battleChampion[i]->resetMoveIntervalTimer();

                        // 重置战斗英雄移动状态
                        battleChampion[i]->resetIsMoving();

                        // 重置当前移动
                        battleChampion[i]->resetCurrentMove();
                    }
                }
                else { // 角色停止移动
                    if (battleChampion[i]->getAttributes().magicPoints >= battleChampion[i]->getAttributes().skillTriggerThreshold) { // 达到技能触发条件
                        battleChampion[i]->skill(); // 技能
                    }

                    // 获取最近敌方战斗英雄
                    battleChampion[i]->findNearestEnemy();

                    if (battleChampion[i]->getCurrentEnemy()) { // 获取当前锁定敌人战斗英雄指针
                        if (battleChampion[i]->isInAttackRange()) { // 攻击范围内存在敌人战斗英雄
                            // 增加攻击时间间隔
                            battleChampion[i]->addAttackIntervalTimer(delta);

                            if (battleChampion[i]->getAttackIntervalTimer() >= (1.0f / battleChampion[i]->getAttributes().attackSpeed)) { // 达到攻击时间间隔
                                // 攻击
                                battleChampion[i]->attack();

                                // 重置攻击时间间隔
                                battleChampion[i]->resetAttackIntervalTimer();
                            }
                        }
                        else { // 攻击范围内不存在敌人战斗英雄
                            // 设置战斗英雄移动状态
                            battleChampion[i]->setIsMoving();

                            // 设置当前目标位置
                            battleChampion[i]->setCurrentDestination(battleChampion[i]->moveTowards(battleChampion[i]->getCurrentEnemy()));

                            // 设置当前移动
                            battleChampion[i]->setCurrentMove(cocos2d::MoveTo::create(1.0f / battleChampion[i]->getAttributes().movementSpeed,
                                LocationMap::getInstance().getLocationMap().at({ BattleArea, battleChampion[i]->getCurrentDestination().x * BATTLE_MAP_COLUMNS + battleChampion[i]->getCurrentDestination().y })));

                            // 移动战斗英雄
                            battleChampion[i]->getSprite()->runAction(battleChampion[i]->getCurrentMove());

                            // 放置战斗英雄
                            g_offlineModeControl->getBattle()->placeChampion(battleChampion[i]->getCurrentDestination().x, battleChampion[i]->getCurrentDestination().y, battleChampion[i]);

                            // 移除战斗英雄
                            g_offlineModeControl->getBattle()->setEmpty(battleChampion[i]->getCurrentLocation().x, battleChampion[i]->getCurrentLocation().y);

                            // 设置当前战斗英雄位置
                            battleChampion[i]->setCurrentPosition(battleChampion[i]->getCurrentDestination().x, battleChampion[i]->getCurrentDestination().y);
                        }
                    }
                }
            }
            else { // 角色死亡
                battleChampion[i]->die();
                battleChampion[i] = nullptr;
            }
        }
    }
}