/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     ChampionAttributesLayer.cpp
 * File Function: ChampionAttributesLayer���ʵ��
 * Author:        �����ǡ��ּ���
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#include <sstream>
#include <iomanip>
#include "ChampionAttributesLayer.h"

// �����ռ�
using cocos2d::Sprite;
using cocos2d::Label;
using cocos2d::Vec2;

// ��ʼ��ս��Ӣ�����Բ�
bool ChampionAttributesLayer::init()
{
    // ��ʼ��
    if (!Layer::init()) {
        return false;
    }

    // ����ս��Ӣ�����Բ㱳��ͼ
    Sprite* backgroundImage = Sprite::create("../Resources/ImageElements/ChampionAttributesLayerBackground.png");
    backgroundImage->setPosition(BACKGROUND_IMAGE_START_X, BACKGROUND_IMAGE_START_Y);
    backgroundImage->setOpacity(BACKGROUND_IMAGE_TRANSPARENCY);
    this->addChild(backgroundImage);

    return true;
}

// ��ʾս��Ӣ������
void ChampionAttributesLayer::showAttributes(const ChampionCategory championCategory)
{
    // ��ȡս��Ӣ������
    auto championAttributes = CHAMPION_ATTR_MAP.at(championCategory);

    // ����ս��Ӣ��ͼƬ
    int championNumber = championAttributes.championCategory % 2 == 1 ? championAttributes.championCategory : championAttributes.championCategory - 1;
    std::string championImagePath = "../Resources/Champions/Champion" + std::to_string(championNumber) + "&" + std::to_string(championNumber + 1) + ".png";
    Sprite* championImage = Sprite::create(championImagePath);
    championImage->setPosition(CHAMPION_IMAGE_START_X, CHAMPION_IMAGE_START_Y);
    this->addChild(championImage);

    // ����ս��Ӣ�۱�ǩ
    createLabel(championAttributes.championName, CHAMPION_NAME_LABEL_START_X, CHAMPION_NAME_LABEL_START_Y, CHAMPION_NAME_LABEL_FONT_SIZE, championAttributes.championCategory % 2 == 1 ? cocos2d::Color4B::WHITE : cocos2d::Color4B({ GOLDEN_R, GOLDEN_G, GOLDEN_B }));
    createLabel(std::to_string(championAttributes.level), LEVEL_LABEL_START_X, LEVEL_LABEL_START_Y);
    createLabel(std::to_string(championAttributes.healthPoints), FIRST_COLUMN_START_X, HEALTH_POINTS_LEBEL_START_Y);
    createLabel(std::to_string(championAttributes.attackDamage), FIRST_COLUMN_START_X, ATTACK_DAMAGE_LABEL_START_Y);
    createLabel(std::to_string(championAttributes.attackRange), FIRST_COLUMN_START_X, ATTACK_RANGE_LABEL_START_Y);
    createLabel(formatFloat(championAttributes.attackSpeed), FIRST_COLUMN_START_X, ATTACK_SPEED_LABEL_START_Y);
    createLabel(std::to_string(championAttributes.price), SECOND_COLUMN_START_X, PRICE_LABEL_START_Y);
    createLabel(formatFloat(championAttributes.movementSpeed), SECOND_COLUMN_START_X, MOVEMENT_SPEED_START_Y);
    createLabel(formatFloat(championAttributes.defenseCoefficient), SECOND_COLUMN_START_X, DEFENSE_COEFFICIENT_START_Y);
    createLabel(std::to_string(championAttributes.skillTriggerThreshold), SECOND_COLUMN_START_X, SKILL_TRIGGER_THRESHOLD_START_Y);
}

// �������Ա�ǩ
void ChampionAttributesLayer::createLabel(const std::string& text, const float x, const float y, const int fontSize, const cocos2d::Color4B color)
{
    auto label = Label::createWithTTF(text, "../Resources/Fonts/DingDingJinBuTi.ttf", fontSize);
    label->setAnchorPoint(Vec2(0, 0.5));
    label->setPosition(x, y);
    label->setTextColor(color);
    this->addChild(label);
}

// ��������ʽ�����
std::string ChampionAttributesLayer::formatFloat(const float value, const int precision)
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << value;
    return oss.str();
}