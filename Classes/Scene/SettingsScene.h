/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     SettingsScene.h
 * File Function: SettingsScene��Ķ���
 * Author:        ������
 * Update Date:   2023/12/27
 ****************************************************************/

#pragma once
#ifndef _SETTINGS_SCENE_H_
#define _SETTINGS_SCENE_H_

#include "cocos2d.h"

 /*
  * Class Name:     SettingsScene
  * Class Function: ���ó�����
  */
class SettingsScene : public cocos2d::Scene {
public:
    // ��������
    static cocos2d::Scene* createScene();

    // ��ʼ������
    virtual bool init();

    // ʵ�� StartupScene ��� create ����
    CREATE_FUNC(SettingsScene);
};

#endif // !_SETTINGS_SCENE_H_