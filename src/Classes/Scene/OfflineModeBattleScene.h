/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeBattleScene.h
 * File Function: OfflineModeBattleScene��Ķ���
 * Author:        �������������ǡ��ּ���
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _OFFLINE_MODE_BATTLE_SCENE_H_
#define _OFFLINE_MODE_BATTLE_SCENE_H_

#include "cocos2d.h"
#include "Champion/Champion.h"

/*
 * Class Name:     OfflineModeBattleScene
 * Class Function: ��ϰģʽ��ս������
 */
class OfflineModeBattleScene : public cocos2d::Scene {
public:
    // ��������
    static cocos2d::Scene* createScene();

    // ��ʼ������
    virtual bool init();

    // ÿһ֡���Զ����õ� update ����
    virtual void update(float delta);

    // ʵ�� OfflineModeBattleScene ��� create ����
    CREATE_FUNC(OfflineModeBattleScene);

private:
    int battleChampionCount = 0;                                                // ��ǰ����ս����ս��Ӣ������
    Champion* battleChampion[BATTLE_AREA_MAX_CHAMPION_COUNT * 2] = { nullptr }; // ��ǰ����ս����ս��Ӣ��ָ��
};

#endif // !_OFFLINE_MODE_BATTLE_SCENE_H_