/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     HoverButton.cpp
 * File Function: HoverButton���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#include "HoverButton.h"

// ����һ���µ� HoverButton ʵ��
HoverButton* HoverButton::create(const std::string& defaultButtonImage, const std::string& hoverButtonImage, const std::string& activeButtonImage)
{
    HoverButton* button = new(std::nothrow) HoverButton();
    if (button && button->init(defaultButtonImage, hoverButtonImage, activeButtonImage)) {
        button->autorelease();
        return button;
    }
    CC_SAFE_DELETE(button);
    return nullptr;
}

// ��ʼ�� HoverButton ʵ��
bool HoverButton::init(const std::string& defaultButtonImage, const std::string& hoverButtonImage, const std::string& activeButtonImage)
{
    // ��ʼ��
    if (!Button::init(defaultButtonImage, activeButtonImage, "")) {
        return false;
    }
    this->defaultButtonImage = defaultButtonImage;
    this->hoverButtonImage = hoverButtonImage;
    this->activeButtonImage = activeButtonImage;

    // ����¼�����
    auto listener = cocos2d::EventListenerMouse::create();
    listener->onMouseMove = CC_CALLBACK_1(HoverButton::onMouseMove, this);
    listener->onMouseUp = CC_CALLBACK_1(HoverButton::onMouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

// ����ƶ��¼��Ĵ�����
void HoverButton::onMouseMove(cocos2d::Event* event)
{
    const auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    if (mouseEvent && this->getBoundingBox().containsPoint(this->getParent()->convertToNodeSpace(mouseEvent->getLocationInView()))) {
        this->loadTextureNormal(hoverButtonImage);
    }
    else {
        this->loadTextureNormal(defaultButtonImage);
    }
}

// ����ͷ��¼��Ĵ�����
void HoverButton::onMouseUp(cocos2d::Event* event)
{
    const auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    if (mouseEvent && this->getBoundingBox().containsPoint(this->getParent()->convertToNodeSpace(mouseEvent->getLocationInView()))) {
        this->loadTextureNormal(activeButtonImage);
    }
}