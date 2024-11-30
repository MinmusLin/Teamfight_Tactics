/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     LocationMap.cpp
 * File Function: LocationMap类的实现
 * Author:        林继申
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#include "LocationMap.h"

// 获取单例
LocationMap& LocationMap::getInstance()
{
    static LocationMap instance;
    return instance;
}

// 获取位置属性与屏幕坐标键值对
const std::map<Location, cocos2d::Vec2>& LocationMap::getLocationMap() const
{
    return locationMap;
}

// 构造函数
LocationMap::LocationMap()
{
    for (int i = 0; i < WAITING_MAP_COUNT; i++) {
        const Location location = { WaitingArea, i };
        locationMap[location] = cocos2d::Vec2(WAITING_AREA_START_X + i * CHAMPION_HORIZONTAL_INTERVAL, WAITING_AREA_START_Y);
    }
    for (int i = 0; i < BATTLE_MAP_ROWS; i++) {
        for (int j = 0; j < BATTLE_MAP_COLUMNS; j++) {
            const Location location = { BattleArea, i * BATTLE_MAP_COLUMNS + j };
            locationMap[location] = cocos2d::Vec2(BATTLE_AREA_START_X + j * CHAMPION_HORIZONTAL_INTERVAL - ((i % 2 == 0) ? 0 : CHAMPION_HORIZONTAL_INTERVAL / 2), BATTLE_AREA_START_Y + i * CHAMPION_VERTICAL_INTERVAL);
        }
    }
}