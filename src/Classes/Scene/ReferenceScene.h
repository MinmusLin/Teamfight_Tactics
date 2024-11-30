/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     ReferenceScene.h
 * File Function: ReferenceScene��Ķ���
 * Author:        �����ǡ��ּ���
 * Update Date:   2023/12/31
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _REFERENCE_SCENE_H_
#define _REFERENCE_SCENE_H_

#include "cocos2d.h"

/*
 * Class Name:     ReferenceScene
 * Class Function: �淨������
 */
class ReferenceScene : public cocos2d::Scene {
public:
    // ��������
    static cocos2d::Scene* createScene();

    // ��ʼ������
    virtual bool init();

    // ʵ�� ReferenceScene ��� create ����
    CREATE_FUNC(ReferenceScene);
};

#endif // !_REFERENCE_SCENE_H_