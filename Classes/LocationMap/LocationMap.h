/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     LocationMap.h
 * File Function: LocationMap类的定义
 * Author:        林继申
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
 * Class Function: 位置属性与屏幕坐标键值对类
 */
class LocationMap {
public:
    // 获取单例
    static LocationMap& getInstance();

    // 获取位置属性与屏幕坐标键值对
    const std::map<Location, cocos2d::Vec2>& getLocationMap() const;

private:
    std::map<Location, cocos2d::Vec2> locationMap; // 位置属性与屏幕坐标键值对

    // 构造函数
    LocationMap();
};

#endif // !_LOCATION_MAP_H_