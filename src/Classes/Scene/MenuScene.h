/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     MenuScene.h
 * File Function: MenuScene��Ķ���
 * Author:        �ּ���
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _MENU_SCENE_H_
#define _MENU_SCENE_H_

#include "cocos2d.h"

/*
 * Class Name:     MenuScene
 * Class Function: �˵�������
 */
class MenuScene : public cocos2d::Scene {
public:
    // ��������
    static cocos2d::Scene* createScene();

    // ��ʼ������
    virtual bool init();

    // ʵ�� MenuScene ��� create ����
    CREATE_FUNC(MenuScene);
};

#endif // !_MENU_SCENE_H_