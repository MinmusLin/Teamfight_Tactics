/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     InitialScene.h
 * File Function: InitialScene��Ķ���
 * Author:        �ּ���
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _INITIAL_SCENE_H_
#define _INITIAL_SCENE_H_

#include "cocos2d.h"

/*
 * Class Name:     InitialScene
 * Class Function: ��ʼ������
 */
class InitialScene : public cocos2d::Scene {
public:
    // ��������
    static cocos2d::Scene* createScene();

    // ��ʼ������
    virtual bool init();

    // ʵ�� InitialScene ��� create ����
    CREATE_FUNC(InitialScene);

private:
    // ����ַ��Ϸ���
    bool isValidCharacter(const char32_t ch);

    // ����ַ����Ϸ���
    bool isValidString(const std::string& str);
};

#endif // !_INITIAL_SCENE_H_