/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     PreferenceScene.h
 * File Function: PreferenceScene��Ķ���
 * Author:        �����ǡ��ּ���
 * Update Date:   2023/12/31
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _PREFERENCE_SCENE_H_
#define _PREFERENCE_SCENE_H_

#include "cocos2d.h"

/*
 * Class Name:     PreferenceScene
 * Class Function: �淨������
 */
class PreferenceScene : public cocos2d::Scene {
public:
    // ��������
    static cocos2d::Scene* createScene();

    // ��ʼ������
    virtual bool init();

    // ʵ�� PreferenceScene ��� create ����
    CREATE_FUNC(PreferenceScene);
};

#endif // !_PREFERENCE_SCENE_H_