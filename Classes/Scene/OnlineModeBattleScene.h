/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OnlineModeBattleScene.h
 * File Function: OnlineModeBattleScene��Ķ���
 * Author:        �������������ǡ��ּ���
 * Update Date:   2023/12/31
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _ONLINE_MODE_BATTLE_SCENE_H_
#define _ONLINE_MODE_BATTLE_SCENE_H_

#include <atomic>
#include "cocos2d.h"
#include "Champion/Champion.h"

/*
 * Class Name:     OnlineModeBattleScene
 * Class Function: ����ģʽ��ս������
 */
class OnlineModeBattleScene : public cocos2d::Scene {
public:
    // ��������
    static cocos2d::Scene* createScene();

    // ��ʼ������
    virtual bool init();

    // ÿһ֡���Զ����õ� update ����
    virtual void update(float delta);

    // ʵ�� OnlineModeBattleScene ��� create ����
    CREATE_FUNC(OnlineModeBattleScene);

private:
    int battleChampionCount = 0;                                                // ��ǰ����ս����ս��Ӣ������
    Champion* battleChampion[BATTLE_AREA_MAX_CHAMPION_COUNT * 2] = { nullptr }; // ��ǰ����ս����ս��Ӣ��ָ��
    std::atomic<bool> isServerMessageProcessed{ false };                        // �������ս������ͼ��Ϣ���ձ�־

    // ��������Ϣ����
    void serverMessageListener();
};

#endif // !_ONLINE_MODE_BATTLE_SCENE_H_