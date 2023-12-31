/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeBattleScene.cpp
 * File Function: OfflineModeBattleScene类的实现
 * Author:        杨宇琨、刘淑仪、林继申
 * Update Date:   2023/12/31
 * License:       MIT License
 ****************************************************************/

#include "OfflineModeBattleScene.h"
#include "Control/OfflineModeControl.h"
#include "LocationMap/LocationMap.h"
#include "Layer/ScoreBoardLayer.h"
#include "MenuScene.h"
#include "proj.win32/AudioPlayer.h"

// 命名空间
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Label;
using cocos2d::Vec2;

// 练习模式游戏控制类
extern OfflineModeControl* g_offlineModeControl;

// 小小英雄种类
extern int g_littleChampionCategory;

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

                // 显示战斗英雄对应武器
                Vec2 currentChampionLocation = LocationMap::getInstance().getLocationMap().at({ BattleArea, i * BATTLE_MAP_COLUMNS + j });
                currentChampion->initializeSword(currentChampionLocation + Vec2(INTERVAL_BETWEEN_WEAPON_AND_CHAMPION, 0));
                this->addChild(currentChampion->getSword());
                currentChampion->setSwordVisible(true);

                // 创建生命条和经验条
                if (currentChampion->getCamp()) {
                    currentChampion->setHealthBar(Sprite::create("../Resources/ImageElements/MyCampHealthBar.png"));
                }
                else {
                    currentChampion->setHealthBar(Sprite::create("../Resources/ImageElements/EnemyCampHealthBar.png"));
                }
                currentChampion->setManaBar(Sprite::create("../Resources/ImageElements/ManaBar.png"));
                currentChampion->getHealthBar()->setPosition(currentChampionLocation + Vec2(0, CHAMPION_HEALTHBAR_VERTICAL_INTERVAL));
                currentChampion->getManaBar()->setPosition(currentChampionLocation + Vec2(0, CHAMPION_MANABAR_VERTICAL_INTERVAL)); 
                this->addChild(currentChampion->getHealthBar(), 1);
                this->addChild(currentChampion->getManaBar(), 1);

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

    // 显示羁绊效果
    for (int i = 1; i < MAX_BOND_COUNT; i++) {
        if (g_offlineModeControl->getBattle()->getMyBond()[i] >= BOND_EFFECT_TRIGGER_CONDITION) {
            g_offlineModeControl->getBattle()->bondEffect(static_cast<Bond>(i), true);
            if (static_cast<Bond>(i) == Lout) {
                auto sprite = cocos2d::Sprite::create("../Resources/ImageElements/MyBondLout.png");
                sprite->cocos2d::Sprite::setPosition(BOND_EFFECT_START_X + i * BOND_EFFECT_HORIZONTAL_INTERVAL, MY_BOND_EFFECT_START_Y);
                this->addChild(sprite);
            }
            else if (static_cast<Bond>(i) == Brotherhood) {
                auto sprite = cocos2d::Sprite::create("../Resources/ImageElements/MyBondBrotherhood.png");
                sprite->cocos2d::Sprite::setPosition(BOND_EFFECT_START_X + i * BOND_EFFECT_HORIZONTAL_INTERVAL, MY_BOND_EFFECT_START_Y);
                this->addChild(sprite);
            }
            else if (static_cast<Bond>(i) == PopStar) {
                auto sprite = cocos2d::Sprite::create("../Resources/ImageElements/MyBondPopStar.png");
                sprite->cocos2d::Sprite::setPosition(BOND_EFFECT_START_X + i * BOND_EFFECT_HORIZONTAL_INTERVAL, MY_BOND_EFFECT_START_Y);
                this->addChild(sprite);
            }
            else if (static_cast<Bond>(i) == GoodShooter) {
                auto sprite = cocos2d::Sprite::create("../Resources/ImageElements/MyBondGoodShooter.png");
                sprite->cocos2d::Sprite::setPosition(BOND_EFFECT_START_X + i * BOND_EFFECT_HORIZONTAL_INTERVAL, MY_BOND_EFFECT_START_Y);
                this->addChild(sprite);
            }
            else if (static_cast<Bond>(i) == DarkSide) {
                auto sprite = cocos2d::Sprite::create("../Resources/ImageElements/MyBondDarkSide.png");
                sprite->cocos2d::Sprite::setPosition(BOND_EFFECT_START_X + i * BOND_EFFECT_HORIZONTAL_INTERVAL, MY_BOND_EFFECT_START_Y);
                this->addChild(sprite);
            }
        }
        if (g_offlineModeControl->getBattle()->getEnemyBond()[i] >= BOND_EFFECT_TRIGGER_CONDITION) {
            g_offlineModeControl->getBattle()->bondEffect(static_cast<Bond>(i), false);
            if (static_cast<Bond>(i) == Lout) {
                auto sprite = cocos2d::Sprite::create("../Resources/ImageElements/EnemyBondLout.png");
                sprite->cocos2d::Sprite::setPosition(BOND_EFFECT_START_X + i * BOND_EFFECT_HORIZONTAL_INTERVAL, ENEMY_BOND_EFFECT_START_Y);
                this->addChild(sprite);
            }
            else if (static_cast<Bond>(i) == Brotherhood) {
                auto sprite = cocos2d::Sprite::create("../Resources/ImageElements/EnemyBondBrotherhood.png");
                sprite->cocos2d::Sprite::setPosition(BOND_EFFECT_START_X + i * BOND_EFFECT_HORIZONTAL_INTERVAL, ENEMY_BOND_EFFECT_START_Y);
                this->addChild(sprite);
            }
            else if (static_cast<Bond>(i) == PopStar) {
                auto sprite = cocos2d::Sprite::create("../Resources/ImageElements/EnemyBondPopStar.png");
                sprite->cocos2d::Sprite::setPosition(BOND_EFFECT_START_X + i * BOND_EFFECT_HORIZONTAL_INTERVAL, ENEMY_BOND_EFFECT_START_Y);
                this->addChild(sprite);
            }
            else if (static_cast<Bond>(i) == GoodShooter) {
                auto sprite = cocos2d::Sprite::create("../Resources/ImageElements/EnemyBondGoodShooter.png");
                sprite->cocos2d::Sprite::setPosition(BOND_EFFECT_START_X + i * BOND_EFFECT_HORIZONTAL_INTERVAL, ENEMY_BOND_EFFECT_START_Y);
                this->addChild(sprite);
            }
            else if (static_cast<Bond>(i) == DarkSide) {
                auto sprite = cocos2d::Sprite::create("../Resources/ImageElements/EnemyBondDarkSide.png");
                sprite->cocos2d::Sprite::setPosition(BOND_EFFECT_START_X + i * BOND_EFFECT_HORIZONTAL_INTERVAL, ENEMY_BOND_EFFECT_START_Y);
                this->addChild(sprite);
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

    // 创建小小英雄登场标签
    auto winSize = cocos2d::Director::getInstance()->getWinSize();
    auto littleChampionLabel = Label::createWithTTF(u8"小小英雄登场!", "../Resources/Fonts/DingDingJinBuTi.ttf", LITTLE_CHAMPION_LABEL_FONT_SIZE);
    littleChampionLabel->setTextColor(cocos2d::Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    littleChampionLabel->setPosition(winSize.width / 2, winSize.height / 2 + LITTLE_CHAMPION_LABEL_OFFSET_Y);
    this->addChild(littleChampionLabel);
    scheduleOnce([littleChampionLabel](float dt) {
        littleChampionLabel->setVisible(false);
        }, PROMPT_MESSAGE_DURATION, "HideLittleChampionLabel");

    // 创建小小英雄
    auto littleChampion = Sprite::create(static_cast<std::string>("../Resources/Champions/LittleChampion")
        + std::to_string(g_littleChampionCategory)
        + static_cast<std::string>(".png"));
    littleChampion->setPosition(winSize.width / 2, winSize.height / 2 + LITTLE_CHAMPION_OFFSET_Y);
    this->addChild(littleChampion, 2);

    // 创建粒子系统
    auto particleSystem = cocos2d::ParticleFlower::create();
    particleSystem->setPosition(littleChampion->getPosition());
    particleSystem->setScale(LITTLE_CHAMPION_PARTICLE_SCALE);
    particleSystem->setLife(LITTLE_CHAMPION_PARTICLE_LIFE);
    this->addChild(particleSystem, 1);
    this->scheduleUpdate();
    this->schedule([=](float dt) {
        particleSystem->setPosition(littleChampion->getPosition());
        }, "ParticleFollow");

    // 创建小小英雄鼠标事件监听
    auto listener = cocos2d::EventListenerMouse::create();
    listener->onMouseDown = [littleChampion](cocos2d::Event* event) {
        const cocos2d::EventMouse* e = dynamic_cast<cocos2d::EventMouse*>(event);
        const Vec2 location = e->getLocationInView();
        const float duration = littleChampion->getPosition().distance(location) / LITTLE_CHAMPION_MOVEMENT_SPEED;
        littleChampion->stopAllActions();
        const auto moveTo = cocos2d::MoveTo::create(duration, location);
        float angle = CC_RADIANS_TO_DEGREES(atan2(littleChampion->getPosition().y - location.y, location.x - littleChampion->getPosition().x));
        angle = angle < 0.0f ? angle + 360.0f : angle;
        const auto rotateTo = cocos2d::RotateTo::create(LITTLE_CHAMPION_ROTATE_DURATION, angle + 90);
        littleChampion->runAction(cocos2d::Spawn::createWithTwoActions(moveTo, rotateTo));
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

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
            g_offlineModeControl->getHumanPlayer()->addGoldCoin(REFRESH_SHOP_PRICE + NEW_BATTLE_INCREASED_GOLD_COINS);
        }
        else if (enemyCount == 0) { // 胜利
            g_offlineModeControl->getBattle()->setBattleSituation(Win);
            g_offlineModeControl->getAIPlayer()->decreaseHealthPoints(myCount * DECREASED_HEALTH_POINTS);
            g_offlineModeControl->getHumanPlayer()->addGoldCoin(myCount * INCREASED_GOLD_COINS + REFRESH_SHOP_PRICE + NEW_BATTLE_INCREASED_GOLD_COINS);
        }
        else { // 失败
            g_offlineModeControl->getBattle()->setBattleSituation(Lose);
            g_offlineModeControl->getHumanPlayer()->decreaseHealthPoints(enemyCount * DECREASED_HEALTH_POINTS);
            g_offlineModeControl->getHumanPlayer()->addGoldCoin(REFRESH_SHOP_PRICE + NEW_BATTLE_INCREASED_GOLD_COINS);
        }

        // 重置分数表层
        auto scoreBoardLayer = dynamic_cast<ScoreBoardLayer*>(this->getChildByName("ScoreBoardLayer"));
        scoreBoardLayer->showScoreBoard(g_offlineModeControl->getHumanPlayer(), g_offlineModeControl->getAIPlayer());

        // 检查练习模式是否结束
        const int humanPlayerHealth = g_offlineModeControl->getHumanPlayer()->getHealthPoints();
        const int enemyPlayerHealth = g_offlineModeControl->getAIPlayer()->getHealthPoints();
        bool isEnd = false;
        std::string winningPrompt = u8"";
        cocos2d::Color4B outlineColor = cocos2d::Color4B::ORANGE;
        if (humanPlayerHealth == 0 && enemyPlayerHealth == 0) {
            isEnd = true;
            winningPrompt = u8"平局";
        }
        else if (enemyPlayerHealth == 0) {
            // 加载胜利音乐
            audioPlayer("../Resources/Music/Victory_ElectricRomeo.mp3", true);

            // 加载胜利音效
            audioPlayer("../Resources/Music/VictorySoundEffect.mp3", false);

            isEnd = true;
            winningPrompt = u8"胜利";
            outlineColor = cocos2d::Color4B::RED;
        }
        else if (humanPlayerHealth == 0) {
            // 加载失败音乐
            audioPlayer("../Resources/Music/Defeat_TheDeadlySword.mp3", true);

            // 加载失败音效
            audioPlayer("../Resources/Music/DefeatSoundEffect.mp3", false);

            isEnd = true;
            winningPrompt = u8"失败";
            outlineColor = cocos2d::Color4B::BLUE;
        }
        if (isEnd) {
            auto winningLabel = Label::createWithTTF(winningPrompt, "../Resources/Fonts/DingDingJinBuTi.ttf", BATTLE_END_LABEL_FONT_SIZE);
            const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
            winningLabel->enableOutline(outlineColor, BATTLE_END_LABEL_OUTLINE_WIDTH);
            cocos2d::Size shadowOffset(BATTLE_END_LABEL_SHADOW_OFFSET_X, BATTLE_END_LABEL_SHADOW_OFFSET_Y);
            winningLabel->enableShadow(cocos2d::Color4B::GRAY, shadowOffset, BATTLE_END_LABEL_BLUR_RADIUS);
            winningLabel->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + BATTLE_END_LABEL_OFFSET_Y));
            this->addChild(winningLabel, 3);
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
            // 设置生命条和经验条
            battleChampion[i]->getHealthBar()->setScaleX(battleChampion[i]->getAttributes().healthPoints / battleChampion[i]->getMaxHealthPoints());
            battleChampion[i]->getManaBar()->setScaleX((battleChampion[i]->getAttributes().magicPoints / battleChampion[i]->getMaxMagicPoints() >= 1) ? 1 : battleChampion[i]->getAttributes().magicPoints / battleChampion[i]->getMaxMagicPoints());

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
                    battleChampion[i]->findNearestEnemy(true);

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
                                Vec2(LocationMap::getInstance().getLocationMap().at({ BattleArea, battleChampion[i]->getCurrentDestination().x * BATTLE_MAP_COLUMNS + battleChampion[i]->getCurrentDestination().y }).x + INTERVAL_BETWEEN_WEAPON_AND_CHAMPION,
                                    LocationMap::getInstance().getLocationMap().at({ BattleArea, battleChampion[i]->getCurrentDestination().x * BATTLE_MAP_COLUMNS + battleChampion[i]->getCurrentDestination().y }).y)));

                            // 移动生命条
                            battleChampion[i]->getHealthBar()->runAction(cocos2d::MoveTo::create(1.0f / battleChampion[i]->getAttributes().movementSpeed,
                                cocos2d::Vec2(LocationMap::getInstance().getLocationMap().at({ BattleArea, battleChampion[i]->getCurrentDestination().x * BATTLE_MAP_COLUMNS + battleChampion[i]->getCurrentDestination().y }).x,
                                    LocationMap::getInstance().getLocationMap().at({ BattleArea, battleChampion[i]->getCurrentDestination().x * BATTLE_MAP_COLUMNS + battleChampion[i]->getCurrentDestination().y }).y + CHAMPION_HEALTHBAR_VERTICAL_INTERVAL)));

                            // 移动经验条
                            battleChampion[i]->getManaBar()->runAction(cocos2d::MoveTo::create(1.0f / battleChampion[i]->getAttributes().movementSpeed,
                                cocos2d::Vec2(LocationMap::getInstance().getLocationMap().at({ BattleArea, battleChampion[i]->getCurrentDestination().x * BATTLE_MAP_COLUMNS + battleChampion[i]->getCurrentDestination().y }).x,
                                    LocationMap::getInstance().getLocationMap().at({ BattleArea, battleChampion[i]->getCurrentDestination().x * BATTLE_MAP_COLUMNS + battleChampion[i]->getCurrentDestination().y }).y + CHAMPION_MANABAR_VERTICAL_INTERVAL)));

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
                battleChampion[i]->setSwordVisible(false);
                battleChampion[i]->die();
                battleChampion[i] = nullptr;
            }
        }
    }
}