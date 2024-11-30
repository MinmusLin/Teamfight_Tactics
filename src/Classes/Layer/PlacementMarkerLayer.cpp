/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     PlacementMarkerLayer.cpp
 * File Function: PlacementMarkerLayer类的实现
 * Author:        刘淑仪、林继申
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#include "PlacementMarkerLayer.h"
#include "LocationMap/LocationMap.h"

// 命名空间
using cocos2d::Sprite;
using cocos2d::Vec2;

// 初始化放置标记层
bool PlacementMarkerLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    return true;
}

// 显示放置标记
void PlacementMarkerLayer::showPlacementMarker(const ChampionCategory battleMap[][BATTLE_MAP_COLUMNS], const ChampionCategory waitingMap[])
{
    for (int i = 0; i < WAITING_MAP_COUNT; i++) {
        if (waitingMap[i] == NoChampion) {
            createPlacementMarker({ WaitingArea,i });
        }
    }
    for (int i = 0; i < PLACE_MAP_ROWS; i++) {
        for (int j = 0; j < BATTLE_MAP_COLUMNS; j++) {
            if (battleMap[i][j] == NoChampion) {
                createPlacementMarker({ BattleArea,i * BATTLE_MAP_COLUMNS + j });
            }
        }
    }
}

// 创建放置标记
void PlacementMarkerLayer::createPlacementMarker(const Location& location)
{
    Sprite* placementMarker = Sprite::create("../Resources/ImageElements/AvailablePlacementMarker.png");
    Vec2 coordinate = LocationMap::getInstance().getLocationMap().at(location);
    placementMarker->setPosition(coordinate);
    this->addChild(placementMarker);
}