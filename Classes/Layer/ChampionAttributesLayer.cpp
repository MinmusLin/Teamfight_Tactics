/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     ChampionAttributeLayer.cpp
 * File Function: ChampionAttributeLayer类的实现
 * Author:        刘淑仪
 * Update Date:   2023/12/21
 ****************************************************************/

#include <sstream>
#include <iomanip>
#include "ChampionAttributesLayer.h"
#include "GBKToUTF8/GBKToUTF8.h"
#include "cocos2d.h"
#include "proj.win32/Constant.h"

USING_NS_CC;

// 构造函数
ChampionAttributesLayer::ChampionAttributesLayer()
    : nameLabel(nullptr),  priceLabel(nullptr),
    levelLabel(nullptr), healthLabel(nullptr), attackDamageLabel(nullptr),
    skillThresholdLabel(nullptr), attackRangeLabel(nullptr),
    attackSpeedLabel(nullptr), movementSpeedLabel(nullptr),
    defenseCoefficientLabel(nullptr), backgroundSprite(nullptr) 
{
    ;
}
// 辅助函数转化小数点
std::string ChampionAttributesLayer::formatFloat(float value, int precision) 
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << value;
    return oss.str();
}

// 显示属性的方法
void ChampionAttributesLayer::showAttributes(const Champion& champion)
{
    // 获取战斗英雄的属性
    ChampionAttributes attributes = champion.getAttributes();

    // 显示图层
    this->setVisible(true);

    //
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << attributes.attackSpeed;
    attackSpeedLabel->setString(oss.str());

    // 更新每个标签的文本以反映战斗英雄的属性
    nameLabel->setString(GBKToUTF8::getString(attributes.championName));
    priceLabel->setString(std::to_string(attributes.price));
    levelLabel->setString(std::to_string(attributes.level));
    healthLabel->setString(std::to_string(attributes.healthPoints));
    attackDamageLabel->setString( std::to_string(attributes.attackDamage));
    skillThresholdLabel->setString(std::to_string(attributes.skillTriggerThreshold));
    attackRangeLabel->setString(std::to_string(attributes.attackRange));
    attackSpeedLabel->setString(formatFloat(attributes.attackSpeed));
    movementSpeedLabel->setString(formatFloat(attributes.movementSpeed));
    defenseCoefficientLabel->setString(formatFloat(attributes.defenseCoefficient));

    nameLabel->setAnchorPoint(cocos2d::Vec2(0, 0.5));
    priceLabel->setAnchorPoint(cocos2d::Vec2(0, 0.5));
    levelLabel->setAnchorPoint(cocos2d::Vec2(0, 0.5));
    healthLabel->setAnchorPoint(cocos2d::Vec2(0, 0.5));
    attackDamageLabel->setAnchorPoint(cocos2d::Vec2(0, 0.5));
    skillThresholdLabel->setAnchorPoint(cocos2d::Vec2(0, 0.5));
    attackRangeLabel->setAnchorPoint(cocos2d::Vec2(0, 0.5));
    attackSpeedLabel->setAnchorPoint(cocos2d::Vec2(0, 0.5));
    movementSpeedLabel->setAnchorPoint(cocos2d::Vec2(0, 0.5));
    defenseCoefficientLabel->setAnchorPoint(cocos2d::Vec2(0, 0.5));

}

// 隐藏属性图层
void ChampionAttributesLayer::hide()
{
    this->setVisible(false);
}

// 初始化图层（可以在此添加静态元素，如背景等）
bool ChampionAttributesLayer::init() 
{
    if (!Layer::init()) {
        return false;
    }
    // 创建背景精灵
    backgroundSprite = cocos2d::Sprite::create("../Resources/Champions/ChampionAttributesLabel.png");
    if (!backgroundSprite) {
        return false; // 如果创建失败，返回 false
    }

    // 设置背景精灵的位置
    backgroundSprite->setPosition(LayerX, LayerY);

    // 设置背景精灵的透明度（0-255，0为完全透明，255为完全不透明）
    // backgroundSprite->setOpacity(200);
    this->addChild(backgroundSprite);

    if (!createAttributeLabels())
        return false;
    
    return true;
}

// 实用的静态创建方法
ChampionAttributesLayer* ChampionAttributesLayer::create()
{
    ChampionAttributesLayer* layer = new ChampionAttributesLayer();
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    else {
        delete layer;
        return nullptr;
    }
}

// 辅助函数用于创建标签
Label* ChampionAttributesLayer::createLabel(const std::string& text, float posX,float posY) 
{
    auto label = cocos2d::Label::createWithTTF(text,"../Resources/Fonts/DingDingJinBuTi.ttf", 18);
    label->setPosition(posX, posY);
    return label;
}

// 创建和配置属性标签的私有方法
bool ChampionAttributesLayer::createAttributeLabels()
{
    // 创建所有标签并设置位置
    // 上三个标签
    nameLabel = createLabel("Name: ", baseXUpMode,baseYUpMode);
    levelLabel = createLabel("Level: ", baseXUpMode + deltaXUpMode, baseYUpMode - deltaYUpMode);

    // 下四个标签
    healthLabel = createLabel("Health: ", baseXDownMode, baseYDownMode);
    attackDamageLabel = createLabel("Attack Damage: ", baseXDownMode, baseYDownMode - deltaYDownMode);
    skillThresholdLabel = createLabel("Skill Threshold: ", baseXDownMode, baseYDownMode - 2 * deltaYDownMode);
    attackRangeLabel = createLabel("Attack Range: ", baseXDownMode, baseYDownMode - 3 * deltaYDownMode);

    priceLabel = createLabel("Price: ", baseXDownMode + deltaXDownMode, baseYDownMode);
    attackSpeedLabel = createLabel("Attack Speed: ", baseXDownMode + deltaXDownMode, baseYDownMode - deltaYDownMode);
    movementSpeedLabel = createLabel("Movement Speed: ", baseXDownMode + deltaXDownMode, baseYDownMode - 2 * deltaYDownMode);
    defenseCoefficientLabel = createLabel("Defense Coefficient: ", baseXDownMode + deltaXDownMode, baseYDownMode - 3 * deltaYDownMode);

    if (!nameLabel || !priceLabel || !levelLabel || !healthLabel || !attackDamageLabel
        || !skillThresholdLabel || !attackRangeLabel || !attackSpeedLabel || !movementSpeedLabel || !defenseCoefficientLabel) {
        return false; // 如果任何标签创建失败，返回 false
    }
    // 将标签添加到 Layer
    this->addChild(nameLabel);
    this->addChild(priceLabel);
    this->addChild(levelLabel);
    this->addChild(healthLabel);
    this->addChild(attackDamageLabel);
    this->addChild(skillThresholdLabel);
    this->addChild(attackRangeLabel);
    this->addChild(attackSpeedLabel);
    this->addChild(movementSpeedLabel);
    this->addChild(defenseCoefficientLabel);

    return true;
}