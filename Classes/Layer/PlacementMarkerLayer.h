/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     PlacementMarkerLayer.h
 * File Function: PlacementMarkerLayer��Ķ���
 * Author:        �����ǡ��ּ���
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _PLACEMENT_MARKER_LAYER_H_
#define _PLACEMENT_MARKER_LAYER_H_

#include "cocos2d.h"
#include "proj.win32/Constant.h"

/*
 * Class Name:     PlacementMarkerLayer
 * Class Function: ���ñ�ǲ���
 */
class PlacementMarkerLayer : public cocos2d::Layer {
public:
    // ��ʼ�����ñ�ǲ�
    virtual bool init();

    // ��ʾ���ñ��
    void showPlacementMarker(const ChampionCategory battleMap[][BATTLE_MAP_COLUMNS], const ChampionCategory waitingMap[]);

    // ʵ�� PlacementMarkerLayer ��� create ����
    CREATE_FUNC(PlacementMarkerLayer);

private:
    // �������ñ��
    void createPlacementMarker(const Location& location);
};

#endif // !_PLACEMENT_MARKER_LAYER_H_