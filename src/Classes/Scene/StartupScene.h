/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     StartupScene.h
 * File Function: StartupScene��Ķ���
 * Author:        �ּ���
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _STARTUP_SCENE_H_
#define _STARTUP_SCENE_H_

#include "cocos2d.h"

/*
 * Class Name:     StartupScene
 * Class Function: ����������
 */
class StartupScene : public cocos2d::Scene {
public:
    // ��������
    static cocos2d::Scene* createScene();

    // ��ʼ������
    virtual bool init();

    // ʵ�� StartupScene ��� create ����
    CREATE_FUNC(StartupScene);
};

#endif // !_STARTUP_SCENE_H_