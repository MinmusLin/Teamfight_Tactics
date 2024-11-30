/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     HoverButton.h
 * File Function: HoverButton类的定义
 * Author:        林继申
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _HOVER_BUTTON_H_
#define _HOVER_BUTTON_H_

#include <string>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

/*
 * Class Name:     HoverButton
 * Class Function: 悬停按钮类
 */
class HoverButton : public cocos2d::ui::Button {
public:
    // 创建一个新的 HoverButton 实例
    static HoverButton* create(const std::string& defaultButtonImage, const std::string& hoverButtonImage, const std::string& activeButtonImage);

    // 初始化 HoverButton 实例
    bool init(const std::string& defaultButtonImage, const std::string& hoverButtonImage, const std::string& activeButtonImage);

private:
    std::string defaultButtonImage; // 默认状态按钮图片路径
    std::string hoverButtonImage;   // 悬停状态按钮图片路径
    std::string activeButtonImage;  // 激活状态按钮图片路径

    // 鼠标移动事件的处理函数
    void onMouseMove(cocos2d::Event* event);

    // 鼠标释放事件的处理函数
    void onMouseUp(cocos2d::Event* event);
};

#endif // !_HOVER_BUTTON_H_