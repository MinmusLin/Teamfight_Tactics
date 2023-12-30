/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     SelectionScene.h
 * File Function: SelectionScene��Ķ���
 * Author:        �����ǡ��ּ���
 * Update Date:   2023/12/30
 ****************************************************************/

#pragma once
#ifndef _SELECTION_SCENE_H_
#define _SELECTION_SCENE_H_

#include "cocos2d.h"

/*
 * Class Name:     SelectionScene
 * Class Function: ѡ�񳡾���
 */
class SelectionScene : public cocos2d::Scene {
public:
    // ��������
    static cocos2d::Scene* createScene();

    // ��ʼ������
    virtual bool init();

    // ʵ�� SelectionScene ��� create ����
    CREATE_FUNC(SelectionScene);
};

#endif // !_SELECTION_SCENE_H_