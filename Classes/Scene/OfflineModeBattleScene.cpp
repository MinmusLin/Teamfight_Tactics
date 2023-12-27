/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeBattleScene.cpp
 * File Function: OfflineModeBattleScene类的实现
 * Author:        杨宇琨、林继申
 * Update Date:   2023/12/26
 ****************************************************************/

#include "OfflineModeBattleScene.h"
#include "Control/OfflineModeControl.h"
#include "LocationMap/LocationMap.h"
#include "Layer/ScoreBoardLayer.h"
#include "GBKToUTF8/GBKToUTF8.h"
#include "MenuScene.h"

// 命名空间
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Label;
using cocos2d::Vec2;

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
                Champion* currentChampion = g_offlineModeControl->getBattle()->getChampion(i, j);
                currentChampion->getSprite()->setPosition(LocationMap::getInstance().getLocationMap().at({ BattleArea, i * BATTLE_MAP_COLUMNS + j }));
                this->addChild(g_offlineModeControl->getBattle()->getChampion(i, j)->getSprite());

                // 显示对应武器
                Vec2 currentChampionLocation = LocationMap::getInstance().getLocationMap().at({ BattleArea, i * BATTLE_MAP_COLUMNS + j });
                currentChampion->swordInit(currentChampionLocation + Vec2(40,0));
                this->addChild(currentChampion->getSword());          // 将剑添加为子节点
                currentChampion->showSword();

                // 计算初始战斗英雄个数
                if (i < PLACE_MAP_ROWS) {
                    g_offlineModeControl->getBattle()->addMyCount();
                }
                else {
                    g_offlineModeControl->getBattle()->addEnemyCount();
                }

                // 绑定战斗类
                currentChampion->setBattle(g_offlineModeControl->getBattle());
                currentChampion->setCurrentPosition(i, j);
                battleChampion[battleChampionCount++] = currentChampion;
            }
            else {
                continue;
            }
        }
    }

    // 创建分数表层
    auto scoreBoardLayer = ScoreBoardLayer::create();
    scoreBoardLayer->initialize(2);
    scoreBoardLayer->showScoreBoard(g_offlineModeControl->getHumanPlayer(), g_offlineModeControl->getAIPlayer());
    scoreBoardLayer->setName("ScoreBoardLayer");
    this->addChild(scoreBoardLayer);

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
        int myCount = g_offlineModeControl->getBattle()->getMyCount();
        int enemyCount = g_offlineModeControl->getBattle()->getEnemyCount();
        if (myCount == 0 && enemyCount == 0) { // 平局
            g_offlineModeControl->getBattle()->setBattleSituation(Draw);
        }
        else if (enemyCount == 0) { // 胜利
            g_offlineModeControl->getBattle()->setBattleSituation(Win);
            g_offlineModeControl->getAIPlayer()->decreaseHealthPoints(myCount * DECREASED_HEALTH_POINTS);
            g_offlineModeControl->getHumanPlayer()->addGoldCoin(myCount * INCREASED_GOLD_COINS + REFRESH_SHOP_PRICE);
        }
        else { // 失败
            g_offlineModeControl->getBattle()->setBattleSituation(Lose);
            g_offlineModeControl->getHumanPlayer()->decreaseHealthPoints(enemyCount * DECREASED_HEALTH_POINTS);
        }

        // 重置分数表层
        auto scoreBoardLayer = dynamic_cast<ScoreBoardLayer*>(this->getChildByName("ScoreBoardLayer"));
        scoreBoardLayer->showScoreBoard(g_offlineModeControl->getHumanPlayer(), g_offlineModeControl->getAIPlayer());

        // 检查练习模式是否结束
        int humanPlayerHealth = g_offlineModeControl->getHumanPlayer()->getHealthPoints();
        int enemyPlayerHealth = g_offlineModeControl->getAIPlayer()->getHealthPoints();
        bool isEnd = false;
        std::string winningPrompt = "";
        cocos2d::Color4B outlineColor = cocos2d::Color4B::ORANGE;
        if (humanPlayerHealth == 0 && enemyPlayerHealth == 0) {
            isEnd = true;
            winningPrompt = "平局";
        }
        else if (enemyPlayerHealth == 0) {
            isEnd = true;
            winningPrompt = "胜利";
            outlineColor = cocos2d::Color4B::RED;
        }
        else if (humanPlayerHealth == 0) {
            isEnd = true;
            winningPrompt = "失败";
            outlineColor = cocos2d::Color4B::BLUE;
        }
        if (isEnd) {
            auto winningLabel = Label::createWithTTF(GBKToUTF8::getString(winningPrompt), "../Resources/Fonts/DingDingJinBuTi.ttf", BATTLE_END_LABEL_FONT_SIZE);
            const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
            winningLabel->enableOutline(outlineColor, BATTLE_END_LABEL_OUTLINE_WIDTH);
            cocos2d::Size shadowOffset(BATTLE_END_LABEL_SHADOW_OFFSET_X, BATTLE_END_LABEL_SHADOW_OFFSET_Y);
            winningLabel->enableShadow(cocos2d::Color4B::GRAY, shadowOffset, BATTLE_END_LABEL_BLUR_RADIUS);
            winningLabel->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + BATTLE_END_LABEL_OFFSET_Y));
            this->addChild(winningLabel);
        }

        // 释放练习模式对战场景
        auto switchScene = [isEnd](float dt) {
            cocos2d::Director::getInstance()->getRunningScene()->unscheduleUpdate();
            cocos2d::Director::getInstance()->popScene();
            if (isEnd) {
                cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, MenuScene::createScene(), cocos2d::Color3B::WHITE));
            }
            };
        this->scheduleOnce(switchScene, BATTLE_END_DURATION, "OfflineModeBattleSceneToOfflineModePreparationScene");

        // 重置对战类
        g_offlineModeControl->releaseBattle();

        return;
    }

    // 更新战斗英雄
    for (int i = 0; i < battleChampionCount; i++) {
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

                            // 移动武器
                            battleChampion[i]->getSword()->runAction(cocos2d::MoveTo::create(1.0f / battleChampion[i]->getAttributes().movementSpeed,
                               Vec2(LocationMap::getInstance().getLocationMap().at({ BattleArea, battleChampion[i]->getCurrentDestination().x * BATTLE_MAP_COLUMNS + battleChampion[i]->getCurrentDestination().y }).x + 40,
                                    LocationMap::getInstance().getLocationMap().at({ BattleArea, battleChampion[i]->getCurrentDestination().x * BATTLE_MAP_COLUMNS + battleChampion[i]->getCurrentDestination().y }).y)));

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
                battleChampion[i]->hideSword();
                battleChampion[i]->die();
                battleChampion[i] = nullptr;
            }
        }
    }
}