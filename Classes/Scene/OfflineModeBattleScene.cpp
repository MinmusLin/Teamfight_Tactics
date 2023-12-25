/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeBattleScene.cpp
 * File Function: OfflineModeBattleScene���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/21
 ****************************************************************/

#include "Control/OfflineModeControl.h"
#include "OfflineModeBattleScene.h"
#include "LocationMap/LocationMap.h"

static Champion* battleChampion[16];
static int index = 0;

USING_NS_CC;

// ��ϰģʽ��Ϸ������
extern OfflineModeControl* g_offlineModeControl;

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
    const auto screenSize = Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/OfflineModeBattleScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // �����ս��
    g_offlineModeControl->initializeBattle();

    // ������������ ��ʾ����Ӣ�۲���ʼ��
    for (int i = 0; i < BATTLE_MAP_ROWS; i++) {
        for (int j = 0; j < BATTLE_MAP_COLUMNS; j++) {
            if (g_offlineModeControl->getBattle()->getChampion(i, j) != nullptr) {
                // ��ʾ����Ӣ��
                g_offlineModeControl->getBattle()->getChampion(i, j)->getSprite()->setPosition(LocationMap::getInstance().getLocationMap().at({ BattleArea, i * 9 + j }));
                this->addChild(g_offlineModeControl->getBattle()->getChampion(i, j)->getSprite());
                // ��ʾѪ������
                g_offlineModeControl->getBattle()->getChampion(i, j)->initHealthBar();

                //�����ʼ����
                if (i < 4)
                    g_offlineModeControl->getBattle()->addMyCount();
                else
                    g_offlineModeControl->getBattle()->addEnemyCount();

                // ��ս��
                g_offlineModeControl->getBattle()->getChampion(i, j)->setBattle(g_offlineModeControl->getBattle());
                // �趨��ʼ����
                g_offlineModeControl->getBattle()->getChampion(i, j)->setCurrentPosition(i, j);
                // ��Ӣ�ۼ��볡��
                battleChampion[index] = g_offlineModeControl->getBattle()->getChampion(i, j);
                index++;
            }
            else {
                continue;
            }
        }
    }

    // ���� update �������������Զ�����
    this->scheduleUpdate();

    // ���ü�ʱ��
    this->scheduleOnce([](float dt) {
        // ��ʱ��ʱֹͣ
        Director::getInstance()->getRunningScene()->unscheduleUpdate();
        Director::getInstance()->popScene();
        // �ͷŶ�ս��
        g_offlineModeControl->releaseBattle();
        // ���þ�̬ȫ�ֱ���
        for (int i = 0; i < index; i++) {
            if (battleChampion[i] != nullptr) {
                battleChampion[i] = nullptr;
            }
        }
        index = 0;
        }, 10, "PopOfflineModeBattleScene");

    return true;
}

// ʵʱ���ݸ���Ӣ�۵���Ϊ���³���ֱ��ĳһ����Ӣ��ȫ��������
void OfflineModeBattleScene::update(float delta)
{
    // ���ü�����
    g_offlineModeControl->getBattle()->resetCount();

    //����
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

    // �жϳ����Ƿ���һ��������
    if (g_offlineModeControl->getBattle()->getEnemyCount() == 0 || g_offlineModeControl->getBattle()->getMyCount() == 0) {
        this->unscheduleUpdate(); // ֹͣ���� update ����
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

    // ����ÿ��Ӣ�۵���Ϊ
    for (int i = 0; i < index; i++)
    {
        if (battleChampion[i] != nullptr) {
            // �������ֵ������
            if (battleChampion[i]->getAttributes().healthPoints > 0) {

                // ��ʾ��Ѫ��
                battleChampion[i]->updateHealthBarPosition();
                battleChampion[i]->updateHealthBarDisplay();

                // �ж��Ƿ��ƶ�
                if (battleChampion[i]->getIsMoving()) {
                    battleChampion[i]->addMoveIntervalTimer(delta);
                    // �����ƶ�ʱ�������ڲ�λ��
                    if (battleChampion[i]->getMoveIntervalTimer() >= (1.0f / battleChampion[i]->getAttributes().movementSpeed)) {
                        //ֹͣ�����˶�
                        battleChampion[i]->getSprite()->stopAction(battleChampion[i]->getCurrentMove());
                        // ����ʱ��
                        battleChampion[i]->resetMoveIntervalTimer();
                        // �����˶�״̬
                        battleChampion[i]->resetIsMoving();
                        // ���õ�ǰ�˶�
                        battleChampion[i]->resetCurrentMove();
                    }
                }
                else {
                    // ���ħ��ֵ�����ͷż���
                    if (battleChampion[i]->getAttributes().magicPoints >= battleChampion[i]->getAttributes().skillTriggerThreshold) {
                        battleChampion[i]->skill();
                    }
                    // ����һ������
                    battleChampion[i]->findNearestEnemy(); // �ҵ�����ĵ���
                    if (battleChampion[i]->getCurrentEnemy()) {
                        // �ж��Ƿ��ڹ�����Χ��
                        if (battleChampion[i]->isInAttackRange()) {
                            battleChampion[i]->addAttackIntervalTimer(delta);
                            // ���ݹ����ٶ��ж��Ƿ񴥷�����
                            if (battleChampion[i]->getAttackIntervalTimer() >= (1.0f / battleChampion[i]->getAttributes().attackSpeed)) {
                                battleChampion[i]->attack(); // ��������
                                battleChampion[i]->resetAttackIntervalTimer(); // ����ʱ��
                            }
                        }
                        else {
                            // ����Ӣ��Ϊ�ƶ�״̬
                            battleChampion[i]->setIsMoving();
                            // �趨�ƶ�Ŀ�ĵ�
                            battleChampion[i]->setCurrentDestination(battleChampion[i]->moveTowards(battleChampion[i]->getCurrentEnemy()));
                            // �����ƶ�λ�ò�����Ϊ�����ƶ�
                            battleChampion[i]->setCurrentMove(cocos2d::MoveTo::create(1.0f / battleChampion[i]->getAttributes().movementSpeed, LocationMap::getInstance().getLocationMap().at({ BattleArea, battleChampion[i]->getCurrentDestination().x * 9 + battleChampion[i]->getCurrentDestination().y })));
                            // ִ�и��ƶ�
                            battleChampion[i]->getSprite()->runAction(battleChampion[i]->getCurrentMove());
                            // ��������Ŀ��λ����Ϊ������
                            g_offlineModeControl->getBattle()->placeChampion(battleChampion[i]->getCurrentDestination().x, battleChampion[i]->getCurrentDestination().y, battleChampion[i]);
                            // ԭ��λ�����
                            g_offlineModeControl->getBattle()->setEmpty(battleChampion[i]->getCurrentLocation().x, battleChampion[i]->getCurrentLocation().y);
                            // ����Ӣ������λ��
                            battleChampion[i]->setCurrentPosition(battleChampion[i]->getCurrentDestination().x, battleChampion[i]->getCurrentDestination().y);
                        }
                    }
                }

            }
            else {
                // �����ɫ����������ֹͣ���������پ���Ȳ���
                battleChampion[i]->Die();
                battleChampion[i] = nullptr;
            }
        }
    }
}
