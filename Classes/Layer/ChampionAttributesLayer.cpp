/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     ChampionAttributeLayer.cpp
 * File Function: ChampionAttributeLayer���ʵ��
 * Author:        ������
 * Update Date:   2023/12/21
 ****************************************************************/

#include <sstream>
#include <iomanip>
#include "ChampionAttributesLayer.h"
#include "GBKToUTF8/GBKToUTF8.h"
#include "cocos2d.h"
#include "proj.win32/Constant.h"

USING_NS_CC;

// ���캯��
ChampionAttributesLayer::ChampionAttributesLayer()
    : nameLabel(nullptr),  priceLabel(nullptr),
    levelLabel(nullptr), healthLabel(nullptr), attackDamageLabel(nullptr),
    skillThresholdLabel(nullptr), attackRangeLabel(nullptr),
    attackSpeedLabel(nullptr), movementSpeedLabel(nullptr),
    defenseCoefficientLabel(nullptr), backgroundSprite(nullptr) 
{
    ;
}
// ��������ת��С����
std::string ChampionAttributesLayer::formatFloat(float value, int precision) 
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << value;
    return oss.str();
}

// ��ʾ���Եķ���
void ChampionAttributesLayer::showAttributes(const Champion& champion)
{
    // ��ȡս��Ӣ�۵�����
    ChampionAttributes attributes = champion.getAttributes();

    // ��ʾͼ��
    this->setVisible(true);

    //
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << attributes.attackSpeed;
    attackSpeedLabel->setString(oss.str());

    // ����ÿ����ǩ���ı��Է�ӳս��Ӣ�۵�����
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

// ��������ͼ��
void ChampionAttributesLayer::hide()
{
    this->setVisible(false);
}

// ��ʼ��ͼ�㣨�����ڴ���Ӿ�̬Ԫ�أ��米���ȣ�
bool ChampionAttributesLayer::init() 
{
    if (!Layer::init()) {
        return false;
    }
    // ������������
    backgroundSprite = cocos2d::Sprite::create("../Resources/Champions/ChampionAttributesLabel.png");
    if (!backgroundSprite) {
        return false; // �������ʧ�ܣ����� false
    }

    // ���ñ��������λ��
    backgroundSprite->setPosition(LayerX, LayerY);

    // ���ñ��������͸���ȣ�0-255��0Ϊ��ȫ͸����255Ϊ��ȫ��͸����
    // backgroundSprite->setOpacity(200);
    this->addChild(backgroundSprite);

    if (!createAttributeLabels())
        return false;
    
    return true;
}

// ʵ�õľ�̬��������
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

// �����������ڴ�����ǩ
Label* ChampionAttributesLayer::createLabel(const std::string& text, float posX,float posY) 
{
    auto label = cocos2d::Label::createWithTTF(text,"../Resources/Fonts/DingDingJinBuTi.ttf", 18);
    label->setPosition(posX, posY);
    return label;
}

// �������������Ա�ǩ��˽�з���
bool ChampionAttributesLayer::createAttributeLabels()
{
    // �������б�ǩ������λ��
    // ��������ǩ
    nameLabel = createLabel("Name: ", baseXUpMode,baseYUpMode);
    levelLabel = createLabel("Level: ", baseXUpMode + deltaXUpMode, baseYUpMode - deltaYUpMode);

    // ���ĸ���ǩ
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
        return false; // ����κα�ǩ����ʧ�ܣ����� false
    }
    // ����ǩ��ӵ� Layer
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