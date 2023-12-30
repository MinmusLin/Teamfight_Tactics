/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     ChampionAttributesLayer.h
 * File Function: ChampionAttributesLayer��Ķ���
 * Author:        �����ǡ��ּ���
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _CHAMPION_ATTRIBUTES_LAYER_H_
#define _CHAMPION_ATTRIBUTES_LAYER_H_

#include "cocos2d.h"
#include "proj.win32/Constant.h"

/*
 * Class Name:     ChampionAttributesLayer
 * Class Function: ս��Ӣ�����Բ���
 */
class ChampionAttributesLayer : public cocos2d::Layer {
public:
    // ��ʼ��ս��Ӣ�����Բ�
    virtual bool init();

    // ��ʾս��Ӣ������
    void showAttributes(const ChampionCategory championCategory);

    // ʵ�� ChampionAttributesLayer ��� create ����
    CREATE_FUNC(ChampionAttributesLayer);

private:
    // �������Ա�ǩ
    void createLabel(const std::string& text, const float x, const float y, const int fontSize = CHAMPION_ATTRIBUTES_FONT_SIZE, cocos2d::Color4B const color = cocos2d::Color4B::WHITE);

    // ��������ʽ�����
    std::string formatFloat(const float value, const int precision = 2);
};

#endif // !_CHAMPION_ATTRIBUTES_LAYER_H_