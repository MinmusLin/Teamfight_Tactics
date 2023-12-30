/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeRuneScene.h
 * File Function: OfflineModeRuneScene��Ķ���
 * Author:        �����ǡ��ּ���
 * Update Date:   2023/12/30
 ****************************************************************/

#pragma once
#ifndef _OFFLINE_MODE_RUNE_SCENE_
#define _OFFLINE_MODE_RUNE_SCENE_

#include "cocos2d.h"

/*
 * Class Name:     OfflineModeRuneScene
 * Class Function: ��ϰģʽǿ�����ĳ�����
 */
class OfflineModeRuneScene : public cocos2d::Scene {
public:
    // ��������
    static cocos2d::Scene* createScene();

    // ��ʼ������
    virtual bool init();

    // ʵ�� OfflineModeRuneScene ��� create ����
    CREATE_FUNC(OfflineModeRuneScene);
};

#endif // !_OFFLINE_MODE_RUNE_SCENE_