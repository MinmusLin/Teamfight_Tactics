/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeBattleScene.cpp
 * File Function: OfflineModeBattleScene类的实现
 * Author:        林继申
 * Update Date:   2023/12/21
 ****************************************************************/

#include "Control/OfflineModeControl.h"
#include "OfflineModeBattleScene.h"
#include "LocationMap/LocationMap.h"

static Champion* battleChampion[16];
static int index = 0;

USING_NS_CC;

// 练习模式游戏控制类
extern OfflineModeControl* g_offlineModeControl;

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
    const auto screenSize = Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/OfflineModeBattleScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // 构造对战类
    g_offlineModeControl->initializeBattle();

    // 遍历整个棋盘 显示所有英雄并初始化
    for (int i = 0; i < BATTLE_MAP_ROWS; i++) {
        for (int j = 0; j < BATTLE_MAP_COLUMNS; j++) {
            if (g_offlineModeControl->getBattle()->getChampion(i, j) != nullptr) {
                // 显示所有英雄
                g_offlineModeControl->getBattle()->getChampion(i, j)->getSprite()->setPosition(LocationMap::getInstance().getLocationMap().at({ BattleArea, i * 9 + j }));
                this->addChild(g_offlineModeControl->getBattle()->getChampion(i, j)->getSprite());
                // 显示血条蓝条
                g_offlineModeControl->getBattle()->getChampion(i, j)->initHealthBar();

                //计算初始个数
                if (i < 4)
                    g_offlineModeControl->getBattle()->addMyCount();
                else
                    g_offlineModeControl->getBattle()->addEnemyCount();

                // 绑定战斗
                g_offlineModeControl->getBattle()->getChampion(i, j)->setBattle(g_offlineModeControl->getBattle());
                // 设定初始坐标
                g_offlineModeControl->getBattle()->getChampion(i, j)->setCurrentPosition(i, j);
                // 将英雄计入场内
                battleChampion[index] = g_offlineModeControl->getBattle()->getChampion(i, j);
                index++;
            }
            else {
                continue;
            }
        }
    }

    // 启用 update 方法，让引擎自动调用
    this->scheduleUpdate();

    // 设置计时器
    this->scheduleOnce([](float dt) {
        // 到时间时停止
        Director::getInstance()->getRunningScene()->unscheduleUpdate();
        Director::getInstance()->popScene();
        // 释放对战类
        g_offlineModeControl->releaseBattle();
        // 重置静态全局变量
        for (int i = 0; i < index; i++) {
            if (battleChampion[i] != nullptr) {
                battleChampion[i] = nullptr;
            }
        }
        index = 0;
        }, 10, "PopOfflineModeBattleScene");

    return true;
}

// 实时根据各个英雄的行为更新场景直至某一方的英雄全部被消灭
void OfflineModeBattleScene::update(float delta)
{
    // 重置计数器
    g_offlineModeControl->getBattle()->resetCount();

    //计数
    for (int i = 0; i < BATTLE_MAP_ROWS; i++) {
        for (int j = 0; j < BATTLE_MAP_COLUMNS; j++) {
            if (g_offlineModeControl->getBattle()->getChampion(i, j) != nullptr) {
                if (g_offlineModeControl->getBattle()->getChampion(i, j)->getCamp() == true)
                    g_offlineModeControl->getBattle()->addMyCount();
                else
                    g_offlineModeControl->getBattle()->addEnemyCount();
            }
            else {
                continue;
            }
        }
    }

    // 判断场上是否有一方被消灭
    if (g_offlineModeControl->getBattle()->getEnemyCount() == 0 || g_offlineModeControl->getBattle()->getMyCount() == 0) {
        this->unscheduleUpdate(); // 停止调用 update 方法
        if (g_offlineModeControl->getBattle()->getEnemyCount() == 0 && g_offlineModeControl->getBattle()->getMyCount() == 0) {
            g_offlineModeControl->getBattle()->setDraw();
        }
        else if (g_offlineModeControl->getBattle()->getEnemyCount() == 0) {
            g_offlineModeControl->getBattle()->setWin();
        }
        else {
            g_offlineModeControl->getBattle()->setLose();
        }
        return;
    }

    // 更新每个英雄的行为
    for (int i = 0; i < index; i++)
    {
        if (battleChampion[i] != nullptr) {
            // 如果生命值大于零
            if (battleChampion[i]->getAttributes().healthPoints > 0) {

                // 显示其血条
                battleChampion[i]->updateHealthBarPosition();
                battleChampion[i]->updateHealthBarDisplay();

                // 判断是否移动
                if (battleChampion[i]->getIsMoving()) {
                    battleChampion[i]->addMoveIntervalTimer(delta);
                    // 满足移动时长更新内部位置
                    if (battleChampion[i]->getMoveIntervalTimer() >= (1.0f / battleChampion[i]->getAttributes().movementSpeed)) {
                        //停止现有运动
                        battleChampion[i]->getSprite()->stopAction(battleChampion[i]->getCurrentMove());
                        // 重置时间
                        battleChampion[i]->resetMoveIntervalTimer();
                        // 重置运动状态
                        battleChampion[i]->resetIsMoving();
                        // 重置当前运动
                        battleChampion[i]->resetCurrentMove();
                    }
                }
                else {
                    // 如果魔法值满则释放技能
                    if (battleChampion[i]->getAttributes().magicPoints >= battleChampion[i]->getAttributes().skillTriggerThreshold) {
                        battleChampion[i]->skill();
                    }
                    // 先找一个敌人
                    battleChampion[i]->findNearestEnemy(); // 找到最近的敌人
                    if (battleChampion[i]->getCurrentEnemy()) {
                        // 判断是否在攻击范围内
                        if (battleChampion[i]->isInAttackRange()) {
                            battleChampion[i]->addAttackIntervalTimer(delta);
                            // 根据攻击速度判断是否触发攻击
                            if (battleChampion[i]->getAttackIntervalTimer() >= (1.0f / battleChampion[i]->getAttributes().attackSpeed)) {
                                battleChampion[i]->attack(); // 触发攻击
                                battleChampion[i]->resetAttackIntervalTimer(); // 重置时间
                            }
                        }
                        else {
                            // 设置英雄为移动状态
                            battleChampion[i]->setIsMoving();
                            // 设定移动目的地
                            battleChampion[i]->setCurrentDestination(battleChampion[i]->moveTowards(battleChampion[i]->getCurrentEnemy()));
                            // 创建移动位置并储存为现有移动
                            battleChampion[i]->setCurrentMove(cocos2d::MoveTo::create(1.0f / battleChampion[i]->getAttributes().movementSpeed, LocationMap::getInstance().getLocationMap().at({ BattleArea, battleChampion[i]->getCurrentDestination().x * 9 + battleChampion[i]->getCurrentDestination().y })));
                            // 执行该移动
                            battleChampion[i]->getSprite()->runAction(battleChampion[i]->getCurrentMove());
                            // 将棋盘中目标位置设为有棋子
                            g_offlineModeControl->getBattle()->placeChampion(battleChampion[i]->getCurrentDestination().x, battleChampion[i]->getCurrentDestination().y, battleChampion[i]);
                            // 原有位置清空
                            g_offlineModeControl->getBattle()->setEmpty(battleChampion[i]->getCurrentLocation().x, battleChampion[i]->getCurrentLocation().y);
                            // 更改英雄现有位置
                            battleChampion[i]->setCurrentPosition(battleChampion[i]->getCurrentDestination().x, battleChampion[i]->getCurrentDestination().y);
                        }
                    }
                }

            }
            else {
                // 如果角色死亡，可以停止动作、销毁精灵等操作
                battleChampion[i]->Die();
                battleChampion[i] = nullptr;
            }
        }
    }
}
