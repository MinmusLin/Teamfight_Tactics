/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     PlacementMarkerLayer.cpp
 * File Function: PlacementMarkerLayer���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/23
 ****************************************************************/

#include "PlacementMarkerLayer.h"
#include "LocationMap/LocationMap.h"

USING_NS_CC;

// ��ʼ�����ñ�ǲ�
bool PlacementMarkerLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    return true;
}

// ��ʾ���ñ��
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

// �������ñ��
void PlacementMarkerLayer::createPlacementMarker(const Location& location)
{
    Sprite* placementMarker = Sprite::create("../Resources/Layers/PlacementMarkerLayer/PlacementMarker.png");
    Vec2 coordinate = LocationMap::getInstance().getLocationMap().at(location);
    placementMarker->setPosition(coordinate);
    this->addChild(placementMarker);
}