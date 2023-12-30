/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OnlineModePreparationScene.h
 * File Function: OnlineModePreparationScene��Ķ���
 * Author:        �ּ���
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _ONLINE_MODE_PREPARATION_SCENE_H_
#define _ONLINE_MODE_PREPARATION_SCENE_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

/*
 * Class Name:     OnlineModePreparationScene
 * Class Function: ����ģʽ׼��������
 */
class OnlineModePreparationScene : public cocos2d::Scene {
public:
    // ��������
    static cocos2d::Scene* createScene();

    // ��ʼ������
    virtual bool init();

    // ���������½���ʱ����
    void onEnter();

    // ʵ�� OnlineModePreparationScene ��� create ����
    CREATE_FUNC(OnlineModePreparationScene);

private:
    // ���ý����������߼����ʱ��
    void setScheduleOnce(cocos2d::ui::LoadingBar* progressBar, cocos2d::Label* progressLabel);
};

#endif // !_ONLINE_MODE_PREPARATION_SCENE_H_