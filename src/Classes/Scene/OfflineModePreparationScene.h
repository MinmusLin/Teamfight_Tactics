/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModePreparationScene.h
 * File Function: OfflineModePreparationScene��Ķ���
 * Author:        �ּ���
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _OFFLINE_MODE_PREPARATION_SCENE_H_
#define _OFFLINE_MODE_PREPARATION_SCENE_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

/*
 * Class Name:     OfflineModePreparationScene
 * Class Function: ��ϰģʽ׼��������
 */
class OfflineModePreparationScene : public cocos2d::Scene {
public:
    // ��������
    static cocos2d::Scene* createScene();

    // ��ʼ������
    virtual bool init();

    // ���������½���ʱ����
    void onEnter();

    // ʵ�� OfflineModePreparationScene ��� create ����
    CREATE_FUNC(OfflineModePreparationScene);

private:
    // ���ý����������߼����ʱ��
    void setScheduleOnce(cocos2d::ui::LoadingBar* progressBar, cocos2d::Label* progressLabel);
};

#endif // !_OFFLINE_MODE_PREPARATION_SCENE_H_