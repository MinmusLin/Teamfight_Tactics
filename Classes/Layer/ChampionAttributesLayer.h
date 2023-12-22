/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     ChampionAttributeLayer.h
 * File Function: ChampionAttributeLayer类的定义
 * Author:        刘淑仪
 * Update Date:   2023/12/21
 ****************************************************************/

#pragma once
#ifndef _CHAMPION_ATTRIBUTE_LAYER_H_
#define _CHAMPION_ATTRIBUTE_LAYER_H_

#include "cocos2d.h"
#include "Champion/Champion.h"

/*
 * Class Name:     ChampionAttributesLayer
 * Class Function: 战斗英雄属性层类
 */
class ChampionAttributesLayer : public cocos2d::Layer {
public:
    // 构造函数
    ChampionAttributesLayer();

    // 显示属性的方法
    void showAttributes(const Champion& champion);


    // 隐藏属性图层
    void hide();

    // 初始化图层（可以在此添加静态元素，如背景等）
    virtual bool init() override;

    // 实用的静态创建方法
    static ChampionAttributesLayer* create();

    // 辅助函数用于创建标签
    cocos2d::Label* ChampionAttributesLayer::createLabel(const std::string& text, float posX, float posY);

    // 辅助函数转化小数点
    std::string formatFloat(float value, int precision = 2);

private:
    cocos2d::Sprite* backgroundSprite;         // 属性底图精灵
    cocos2d::Label* nameLabel;                 // 名称标签
    cocos2d::Label* categoryLabel;             // 种类标签
    cocos2d::Label* priceLabel;                // 价格标签
    cocos2d::Label* levelLabel;                // 等级标签
    cocos2d::Label* healthLabel;               // 生命值标签
    cocos2d::Label* attackLabel;               // 攻击伤害标签
    cocos2d::Label* skillThresholdLabel;       // 技能触发阈值标签
    cocos2d::Label* attackRangeLabel;          // 攻击范围标签
    cocos2d::Label* attackSpeedLabel;          // 攻击速度标签
    cocos2d::Label* movementSpeedLabel;        // 移动速度标签
    cocos2d::Label* defenseCoefficientLabel;   // 防御系数标签

    // 创建和配置属性标签的私有方法
    bool createAttributeLabels();
};

#endif	// !_CHAMPION_ATTRIBUTE_LAYER_H_