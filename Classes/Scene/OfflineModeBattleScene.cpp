/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeBattleScene.cpp
 * File Function: OfflineModeBattleScene���ʵ��
 * Author:        ���������ּ���
 * Update Date:   2023/12/25
 ****************************************************************/

#include "OfflineModeBattleScene.h"
#include "Control/OfflineModeControl.h"
#include "LocationMap/LocationMap.h"

// �����ռ�
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Vec2;

// ��ϰģʽ��Ϸ������
extern OfflineModeControl* g_offlineModeControl;

// ��ǰ����ս����ս��Ӣ��ָ��
static Champion* battleChampion[BATTLE_AREA_MAX_CHAMPION_COUNT * 2] = { nullptr };

// ��ǰ����ս����ս��Ӣ������
static int index = 0;

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
                g_offlineModeControl->getBattle()->getChampion(i, j)->getSprite()->setPosition(LocationMap::getInstance().getLocationMap().at({ BattleArea, i * BATTLE_MAP_COLUMNS + j }));
                this->addChild(g_offlineModeControl->getBattle()->getChampion(i, j)->getSprite());

                // �����ʼս��Ӣ�۸���
                if (i < PLACE_MAP_ROWS) {
                    g_offlineModeControl->getBattle()->addMyCount();
                }
                else {
                    g_offlineModeControl->getBattle()->addEnemyCount();
                }

                // ��ս����
                g_offlineModeControl->getBattle()->getChampion(i, j)->setBattle(g_offlineModeControl->getBattle());
                g_offlineModeControl->getBattle()->getChampion(i, j)->setCurrentPosition(i, j);
                battleChampion[index++] = g_offlineModeControl->getBattle()->getChampion(i, j);
            }
            else {
                continue;
            }
        }
    }

    // ����ÿһ֡���Զ����õ� update ����
    this->scheduleUpdate();

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
        if (g_offlineModeControl->getBattle()->getEnemyCount() == 0 && g_offlineModeControl->getBattle()->getMyCount() == 0) {
            g_offlineModeControl->getBattle()->setBattleSituation(Draw);
        }
        else if (g_offlineModeControl->getBattle()->getEnemyCount() == 0) {
            g_offlineModeControl->getBattle()->setBattleSituation(Win);
        }
        else {
            g_offlineModeControl->getBattle()->setBattleSituation(Lose);
        }

        // �ͷ���ϰģʽ��ս����
        cocos2d::Director::getInstance()->getRunningScene()->unscheduleUpdate();
        cocos2d::Director::getInstance()->popScene();

        // ���ö�ս��
        g_offlineModeControl->releaseBattle();
        for (int i = 0; i < index; i++) {
            if (battleChampion[i] != nullptr) {
                battleChampion[i] = nullptr;
            }
        }
        index = 0;

        return;
    }

    // ����ս��Ӣ��
    for (int i = 0; i < index; i++) {
        if (battleChampion[i] != nullptr) { // ����ս��Ӣ��
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
                    battleChampion[i]->findNearestEnemy();

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
                battleChampion[i]->die();
                battleChampion[i] = nullptr;
            }
        }
    }
}