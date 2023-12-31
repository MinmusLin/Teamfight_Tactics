/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeBattleScene.cpp
 * File Function: OfflineModeBattleScene���ʵ��
 * Author:        �������������ǡ��ּ���
 * Update Date:   2023/12/31
 * License:       MIT License
 ****************************************************************/

#include "OfflineModeBattleScene.h"
#include "Control/OfflineModeControl.h"
#include "LocationMap/LocationMap.h"
#include "Layer/ScoreBoardLayer.h"
#include "MenuScene.h"
#include "proj.win32/AudioPlayer.h"

// �����ռ�
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Label;
using cocos2d::Vec2;

// ��ϰģʽ��Ϸ������
extern OfflineModeControl* g_offlineModeControl;

// ССӢ������
extern int g_littleChampionCategory;

// ��������
Scene* OfflineModeBattleScene::createScene()
{
    auto scene = Scene::create();
    auto layer = OfflineModeBattleScene::create();
    scene->addChild(layer);
    return scene;
}

// ��ʼ������
bool OfflineModeBattleScene::init()
{
    // ��������
    if (!Scene::init()) {
        return false;
    }

    // ���ر���
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/OfflineModeBattleScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // ��ʼ����ս��
    g_offlineModeControl->initializeBattle();

    // ����ս������ͼ
    for (int i = 0; i < BATTLE_MAP_ROWS; i++) {
        for (int j = 0; j < BATTLE_MAP_COLUMNS; j++) {
            if (g_offlineModeControl->getBattle()->getChampion(i, j) != nullptr) {
                // ��ʾ����ս��Ӣ��
                Champion* currentChampion = g_offlineModeControl->getBattle()->getChampion(i, j);
                currentChampion->getSprite()->setPosition(LocationMap::getInstance().getLocationMap().at({ BattleArea, i * BATTLE_MAP_COLUMNS + j }));
                this->addChild(g_offlineModeControl->getBattle()->getChampion(i, j)->getSprite());

                // ��ʾս��Ӣ�۶�Ӧ����
                Vec2 currentChampionLocation = LocationMap::getInstance().getLocationMap().at({ BattleArea, i * BATTLE_MAP_COLUMNS + j });
                currentChampion->initializeSword(currentChampionLocation + Vec2(INTERVAL_BETWEEN_WEAPON_AND_CHAMPION, 0));
                this->addChild(currentChampion->getSword());
                currentChampion->setSwordVisible(true);

                // �����������;�����
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

                // �����ʼս��Ӣ�۸���
                if (i < PLACE_MAP_ROWS) {
                    g_offlineModeControl->getBattle()->addMyCount();
                }
                else {
                    g_offlineModeControl->getBattle()->addEnemyCount();
                }

                // ��ս����
                currentChampion->setBattle(g_offlineModeControl->getBattle());
                currentChampion->setCurrentPosition(i, j);
                battleChampion[battleChampionCount++] = currentChampion;
            }
            else {
                continue;
            }
        }
    }

    // ��ʾ�Ч��
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

    // �����������
    auto scoreBoardLayer = ScoreBoardLayer::create();
    scoreBoardLayer->initialize(2);
    scoreBoardLayer->showScoreBoard(g_offlineModeControl->getHumanPlayer(), g_offlineModeControl->getAIPlayer());
    scoreBoardLayer->setName("ScoreBoardLayer");
    this->addChild(scoreBoardLayer);

    // ����ÿһ֡���Զ����õ� update ����
    this->scheduleUpdate();

    // ����ССӢ�۵ǳ���ǩ
    auto winSize = cocos2d::Director::getInstance()->getWinSize();
    auto littleChampionLabel = Label::createWithTTF(u8"ССӢ�۵ǳ�!", "../Resources/Fonts/DingDingJinBuTi.ttf", LITTLE_CHAMPION_LABEL_FONT_SIZE);
    littleChampionLabel->setTextColor(cocos2d::Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    littleChampionLabel->setPosition(winSize.width / 2, winSize.height / 2 + LITTLE_CHAMPION_LABEL_OFFSET_Y);
    this->addChild(littleChampionLabel);
    scheduleOnce([littleChampionLabel](float dt) {
        littleChampionLabel->setVisible(false);
        }, PROMPT_MESSAGE_DURATION, "HideLittleChampionLabel");

    // ����ССӢ��
    auto littleChampion = Sprite::create(static_cast<std::string>("../Resources/Champions/LittleChampion")
        + std::to_string(g_littleChampionCategory)
        + static_cast<std::string>(".png"));
    littleChampion->setPosition(winSize.width / 2, winSize.height / 2 + LITTLE_CHAMPION_OFFSET_Y);
    this->addChild(littleChampion, 2);

    // ��������ϵͳ
    auto particleSystem = cocos2d::ParticleFlower::create();
    particleSystem->setPosition(littleChampion->getPosition());
    particleSystem->setScale(LITTLE_CHAMPION_PARTICLE_SCALE);
    particleSystem->setLife(LITTLE_CHAMPION_PARTICLE_LIFE);
    this->addChild(particleSystem, 1);
    this->scheduleUpdate();
    this->schedule([=](float dt) {
        particleSystem->setPosition(littleChampion->getPosition());
        }, "ParticleFollow");

    // ����ССӢ������¼�����
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

// ÿһ֡���Զ����õ� update ����
void OfflineModeBattleScene::update(float delta)
{
    // ����ս��Ӣ������
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

    // �ж�ս���Ƿ����
    if (g_offlineModeControl->getBattle()->getEnemyCount() == 0 || g_offlineModeControl->getBattle()->getMyCount() == 0) {
        // �ر�ÿһ֡���Զ����õ� update ����
        this->unscheduleUpdate();

        // ����ս��ʤ��״̬
        int myCount = g_offlineModeControl->getBattle()->getMyCount();
        int enemyCount = g_offlineModeControl->getBattle()->getEnemyCount();
        if (myCount == 0 && enemyCount == 0) { // ƽ��
            g_offlineModeControl->getBattle()->setBattleSituation(Draw);
            g_offlineModeControl->getHumanPlayer()->addGoldCoin(REFRESH_SHOP_PRICE + NEW_BATTLE_INCREASED_GOLD_COINS);
        }
        else if (enemyCount == 0) { // ʤ��
            g_offlineModeControl->getBattle()->setBattleSituation(Win);
            g_offlineModeControl->getAIPlayer()->decreaseHealthPoints(myCount * DECREASED_HEALTH_POINTS);
            g_offlineModeControl->getHumanPlayer()->addGoldCoin(myCount * INCREASED_GOLD_COINS + REFRESH_SHOP_PRICE + NEW_BATTLE_INCREASED_GOLD_COINS);
        }
        else { // ʧ��
            g_offlineModeControl->getBattle()->setBattleSituation(Lose);
            g_offlineModeControl->getHumanPlayer()->decreaseHealthPoints(enemyCount * DECREASED_HEALTH_POINTS);
            g_offlineModeControl->getHumanPlayer()->addGoldCoin(REFRESH_SHOP_PRICE + NEW_BATTLE_INCREASED_GOLD_COINS);
        }

        // ���÷������
        auto scoreBoardLayer = dynamic_cast<ScoreBoardLayer*>(this->getChildByName("ScoreBoardLayer"));
        scoreBoardLayer->showScoreBoard(g_offlineModeControl->getHumanPlayer(), g_offlineModeControl->getAIPlayer());

        // �����ϰģʽ�Ƿ����
        const int humanPlayerHealth = g_offlineModeControl->getHumanPlayer()->getHealthPoints();
        const int enemyPlayerHealth = g_offlineModeControl->getAIPlayer()->getHealthPoints();
        bool isEnd = false;
        std::string winningPrompt = u8"";
        cocos2d::Color4B outlineColor = cocos2d::Color4B::ORANGE;
        if (humanPlayerHealth == 0 && enemyPlayerHealth == 0) {
            isEnd = true;
            winningPrompt = u8"ƽ��";
        }
        else if (enemyPlayerHealth == 0) {
            // ����ʤ������
            audioPlayer("../Resources/Music/Victory_ElectricRomeo.mp3", true);

            // ����ʤ����Ч
            audioPlayer("../Resources/Music/VictorySoundEffect.mp3", false);

            isEnd = true;
            winningPrompt = u8"ʤ��";
            outlineColor = cocos2d::Color4B::RED;
        }
        else if (humanPlayerHealth == 0) {
            // ����ʧ������
            audioPlayer("../Resources/Music/Defeat_TheDeadlySword.mp3", true);

            // ����ʧ����Ч
            audioPlayer("../Resources/Music/DefeatSoundEffect.mp3", false);

            isEnd = true;
            winningPrompt = u8"ʧ��";
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

        // �ͷ���ϰģʽ��ս����
        auto switchScene = [isEnd](float dt) {
            cocos2d::Director::getInstance()->getRunningScene()->unscheduleUpdate();
            cocos2d::Director::getInstance()->popScene();
            if (isEnd) {
                cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, MenuScene::createScene(), cocos2d::Color3B::WHITE));
            }
            };
        this->scheduleOnce(switchScene, BATTLE_END_DURATION, "OfflineModeBattleSceneToOfflineModePreparationScene");

        // ���ö�ս��
        g_offlineModeControl->releaseBattle();

        return;
    }

    // ����ս��Ӣ��
    for (int i = 0; i < battleChampionCount; i++) {
        if (battleChampion[i] != nullptr) { // ����ս��Ӣ��
            // �����������;�����
            battleChampion[i]->getHealthBar()->setScaleX(battleChampion[i]->getAttributes().healthPoints / battleChampion[i]->getMaxHealthPoints());
            battleChampion[i]->getManaBar()->setScaleX((battleChampion[i]->getAttributes().magicPoints / battleChampion[i]->getMaxMagicPoints() >= 1) ? 1 : battleChampion[i]->getAttributes().magicPoints / battleChampion[i]->getMaxMagicPoints());

            if (battleChampion[i]->getAttributes().healthPoints > 0) { // ��ɫ���
                if (battleChampion[i]->getIsMoving()) { // ��ɫ�����ƶ�
                    // �����ƶ�ʱ����
                    battleChampion[i]->addMoveIntervalTimer(delta);

                    if (battleChampion[i]->getMoveIntervalTimer() >= (1.0f / battleChampion[i]->getAttributes().movementSpeed)) { // �ﵽֹͣ�ƶ�����
                        // ֹͣս��Ӣ���ƶ�
                        battleChampion[i]->getSprite()->stopAction(battleChampion[i]->getCurrentMove());

                        // �����ƶ�ʱ����
                        battleChampion[i]->resetMoveIntervalTimer();

                        // ����ս��Ӣ���ƶ�״̬
                        battleChampion[i]->resetIsMoving();

                        // ���õ�ǰ�ƶ�
                        battleChampion[i]->resetCurrentMove();
                    }
                }
                else { // ��ɫֹͣ�ƶ�
                    if (battleChampion[i]->getAttributes().magicPoints >= battleChampion[i]->getAttributes().skillTriggerThreshold) { // �ﵽ���ܴ�������
                        battleChampion[i]->skill(); // ����
                    }

                    // ��ȡ����з�ս��Ӣ��
                    battleChampion[i]->findNearestEnemy(true);

                    if (battleChampion[i]->getCurrentEnemy()) { // ��ȡ��ǰ��������ս��Ӣ��ָ��
                        if (battleChampion[i]->isInAttackRange()) { // ������Χ�ڴ��ڵ���ս��Ӣ��
                            // ���ӹ���ʱ����
                            battleChampion[i]->addAttackIntervalTimer(delta);

                            if (battleChampion[i]->getAttackIntervalTimer() >= (1.0f / battleChampion[i]->getAttributes().attackSpeed)) { // �ﵽ����ʱ����
                                // ����
                                battleChampion[i]->attack();

                                // ���ù���ʱ����
                                battleChampion[i]->resetAttackIntervalTimer();
                            }
                        }
                        else { // ������Χ�ڲ����ڵ���ս��Ӣ��
                            // ����ս��Ӣ���ƶ�״̬
                            battleChampion[i]->setIsMoving();

                            // ���õ�ǰĿ��λ��
                            battleChampion[i]->setCurrentDestination(battleChampion[i]->moveTowards(battleChampion[i]->getCurrentEnemy()));

                            // ���õ�ǰ�ƶ�
                            battleChampion[i]->setCurrentMove(cocos2d::MoveTo::create(1.0f / battleChampion[i]->getAttributes().movementSpeed,
                                LocationMap::getInstance().getLocationMap().at({ BattleArea, battleChampion[i]->getCurrentDestination().x * BATTLE_MAP_COLUMNS + battleChampion[i]->getCurrentDestination().y })));

                            // �ƶ�����
                            battleChampion[i]->getSword()->runAction(cocos2d::MoveTo::create(1.0f / battleChampion[i]->getAttributes().movementSpeed,
                                Vec2(LocationMap::getInstance().getLocationMap().at({ BattleArea, battleChampion[i]->getCurrentDestination().x * BATTLE_MAP_COLUMNS + battleChampion[i]->getCurrentDestination().y }).x + INTERVAL_BETWEEN_WEAPON_AND_CHAMPION,
                                    LocationMap::getInstance().getLocationMap().at({ BattleArea, battleChampion[i]->getCurrentDestination().x * BATTLE_MAP_COLUMNS + battleChampion[i]->getCurrentDestination().y }).y)));

                            // �ƶ�������
                            battleChampion[i]->getHealthBar()->runAction(cocos2d::MoveTo::create(1.0f / battleChampion[i]->getAttributes().movementSpeed,
                                cocos2d::Vec2(LocationMap::getInstance().getLocationMap().at({ BattleArea, battleChampion[i]->getCurrentDestination().x * BATTLE_MAP_COLUMNS + battleChampion[i]->getCurrentDestination().y }).x,
                                    LocationMap::getInstance().getLocationMap().at({ BattleArea, battleChampion[i]->getCurrentDestination().x * BATTLE_MAP_COLUMNS + battleChampion[i]->getCurrentDestination().y }).y + CHAMPION_HEALTHBAR_VERTICAL_INTERVAL)));

                            // �ƶ�������
                            battleChampion[i]->getManaBar()->runAction(cocos2d::MoveTo::create(1.0f / battleChampion[i]->getAttributes().movementSpeed,
                                cocos2d::Vec2(LocationMap::getInstance().getLocationMap().at({ BattleArea, battleChampion[i]->getCurrentDestination().x * BATTLE_MAP_COLUMNS + battleChampion[i]->getCurrentDestination().y }).x,
                                    LocationMap::getInstance().getLocationMap().at({ BattleArea, battleChampion[i]->getCurrentDestination().x * BATTLE_MAP_COLUMNS + battleChampion[i]->getCurrentDestination().y }).y + CHAMPION_MANABAR_VERTICAL_INTERVAL)));

                            // �ƶ�ս��Ӣ��
                            battleChampion[i]->getSprite()->runAction(battleChampion[i]->getCurrentMove());

                            // ����ս��Ӣ��
                            g_offlineModeControl->getBattle()->placeChampion(battleChampion[i]->getCurrentDestination().x, battleChampion[i]->getCurrentDestination().y, battleChampion[i]);

                            // �Ƴ�ս��Ӣ��
                            g_offlineModeControl->getBattle()->setEmpty(battleChampion[i]->getCurrentLocation().x, battleChampion[i]->getCurrentLocation().y);

                            // ���õ�ǰս��Ӣ��λ��
                            battleChampion[i]->setCurrentPosition(battleChampion[i]->getCurrentDestination().x, battleChampion[i]->getCurrentDestination().y);
                        }
                    }
                }
            }
            else { // ��ɫ����
                battleChampion[i]->setSwordVisible(false);
                battleChampion[i]->die();
                battleChampion[i] = nullptr;
            }
        }
    }
}