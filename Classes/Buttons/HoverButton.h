/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     HoverButton.h
 * File Function: HoverButton��Ķ���
 * Author:        �ּ���
 * Update Date:   2023/12/4
 ****************************************************************/

#pragma once
#ifndef _HOVER_BUTTON_H_
#define _HOVER_BUTTON_H_

#include <string>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

/*
 * Class Name:     HoverButton
 * Class Function: ��ͣ��ť��
 */
class HoverButton : public cocos2d::ui::Button {
public:
    // ����һ���µ� HoverButton ʵ��
    static HoverButton* create(const std::string& defaultButtonImage, const std::string& hoverButtonImage, const std::string& activeButtonImage);

    // ��ʼ�� HoverButton ʵ��
    bool init(const std::string& defaultButtonImage, const std::string& hoverButtonImage, const std::string& activeButtonImage);
private:
    // ͼƬ·��
    std::string defaultButtonImage;
    std::string hoverButtonImage;
    std::string activeButtonImage;

    // ����ƶ��¼��Ĵ�����
    void onMouseMove(cocos2d::Event* event);

    // ����ͷ��¼��Ĵ�����
    void onMouseUp(cocos2d::Event* event);
};

#endif // !_HOVER_BUTTON_H_