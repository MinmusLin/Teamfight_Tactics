/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     HoverButton.cpp
 * File Function: HoverButton类的实现
 * Author:        林继申
 * Update Date:   2023/12/27
 * License:       MIT License
 ****************************************************************/

#include "HoverButton.h"
#include "AudioEngine.h"

 // 音量变量
extern float g_backgroundMusicVolumn;
extern float g_effectVolumn;

// 创建一个新的 HoverButton 实例
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

// 初始化 HoverButton 实例
bool HoverButton::init(const std::string& defaultButtonImage, const std::string& hoverButtonImage, const std::string& activeButtonImage)
{
    // 初始化
    if (!Button::init(defaultButtonImage, activeButtonImage, "")) {
        return false;
    }
    this->defaultButtonImage = defaultButtonImage;
    this->hoverButtonImage = hoverButtonImage;
    this->activeButtonImage = activeButtonImage;

    // 鼠标事件监听
    auto listener = cocos2d::EventListenerMouse::create();
    listener->onMouseMove = CC_CALLBACK_1(HoverButton::onMouseMove, this);
    listener->onMouseUp = CC_CALLBACK_1(HoverButton::onMouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

// 鼠标移动事件的处理函数
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

// 鼠标释放事件的处理函数
void HoverButton::onMouseUp(cocos2d::Event* event)
{
    const auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    if (mouseEvent && this->getBoundingBox().containsPoint(this->getParent()->convertToNodeSpace(mouseEvent->getLocationInView()))) {
        // 加载点击音效
        int sliderEFF = cocos2d::experimental::AudioEngine::play2d("../Resources/Music/Effect/Click.mp3");
        cocos2d::experimental::AudioEngine::setVolume(sliderEFF, g_effectVolumn);

        this->loadTextureNormal(activeButtonImage);
    }
}