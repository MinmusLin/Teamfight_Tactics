/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     LocationMap.h
 * File Function: LocationMap��Ķ���
 * Author:        �ּ���
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _LOCATION_MAP_H_
#define _LOCATION_MAP_H_

#include "cocos2d.h"
#include "proj.win32/Constant.h"

/*
 * Class Name:     LocationMap
 * Class Function: λ����������Ļ�����ֵ����
 */
class LocationMap {
public:
    // ��ȡ����
    static LocationMap& getInstance();

    // ��ȡλ����������Ļ�����ֵ��
    const std::map<Location, cocos2d::Vec2>& getLocationMap() const;

private:
    std::map<Location, cocos2d::Vec2> locationMap; // λ����������Ļ�����ֵ��

    // ���캯��
    LocationMap();
};

#endif // !_LOCATION_MAP_H_