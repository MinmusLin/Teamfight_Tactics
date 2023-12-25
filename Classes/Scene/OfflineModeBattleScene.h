/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeBattleScene.h
 * File Function: OfflineModeBattleScene��Ķ���
 * Author:        ���������ּ���
 * Update Date:   2023/12/25
 ****************************************************************/

#pragma once
#ifndef _OFFLINE_MODE_BATTLE_SCENE_H_
#define _OFFLINE_MODE_BATTLE_SCENE_H_

#include "cocos2d.h"

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
};

#endif // !_OFFLINE_MODE_BATTLE_SCENE_H_