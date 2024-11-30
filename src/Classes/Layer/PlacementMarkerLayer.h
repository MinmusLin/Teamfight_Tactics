/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     PlacementMarkerLayer.h
 * File Function: PlacementMarkerLayer类的定义
 * Author:        刘淑仪、林继申
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
 * Class Function: 放置标记层类
 */
class PlacementMarkerLayer : public cocos2d::Layer {
public:
    // 初始化放置标记层
    virtual bool init();

    // 显示放置标记
    void showPlacementMarker(const ChampionCategory battleMap[][BATTLE_MAP_COLUMNS], const ChampionCategory waitingMap[]);

    // 实现 PlacementMarkerLayer 类的 create 方法
    CREATE_FUNC(PlacementMarkerLayer);

private:
    // 创建放置标记
    void createPlacementMarker(const Location& location);
};

#endif // !_PLACEMENT_MARKER_LAYER_H_