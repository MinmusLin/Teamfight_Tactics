/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     ChampionAttributeLayer.h
 * File Function: ChampionAttributeLayer��Ķ���
 * Author:        ������
 * Update Date:   2023/12/21
 ****************************************************************/

#pragma once
#ifndef _CHAMPION_ATTRIBUTE_LAYER_H_
#define _CHAMPION_ATTRIBUTE_LAYER_H_

#include "cocos2d.h"
#include "Champion/Champion.h"

/*
 * Class Name:     ChampionAttributesLayer
 * Class Function: ս��Ӣ�����Բ���
 */
class ChampionAttributesLayer : public cocos2d::Layer {
public:
    // ���캯��
    ChampionAttributesLayer();

    // ��ʾ���Եķ���
    void showAttributes(const Champion& champion);


    // ��������ͼ��
    void hide();

    // ��ʼ��ͼ�㣨�����ڴ���Ӿ�̬Ԫ�أ��米���ȣ�
    virtual bool init() override;

    // ʵ�õľ�̬��������
    static ChampionAttributesLayer* create();

    // �����������ڴ�����ǩ
    cocos2d::Label* ChampionAttributesLayer::createLabel(const std::string& text, float posX, float posY);

    // ��������ת��С����
    std::string formatFloat(float value, int precision = 2);

private:
    cocos2d::Sprite* backgroundSprite;         // ���Ե�ͼ����
    cocos2d::Label* nameLabel;                 // ���Ʊ�ǩ
    cocos2d::Label* categoryLabel;             // �����ǩ
    cocos2d::Label* priceLabel;                // �۸��ǩ
    cocos2d::Label* levelLabel;                // �ȼ���ǩ
    cocos2d::Label* healthLabel;               // ����ֵ��ǩ
    cocos2d::Label* attackLabel;               // �����˺���ǩ
    cocos2d::Label* skillThresholdLabel;       // ���ܴ�����ֵ��ǩ
    cocos2d::Label* attackRangeLabel;          // ������Χ��ǩ
    cocos2d::Label* attackSpeedLabel;          // �����ٶȱ�ǩ
    cocos2d::Label* movementSpeedLabel;        // �ƶ��ٶȱ�ǩ
    cocos2d::Label* defenseCoefficientLabel;   // ����ϵ����ǩ

    // �������������Ա�ǩ��˽�з���
    bool createAttributeLabels();
};

#endif	// !_CHAMPION_ATTRIBUTE_LAYER_H_