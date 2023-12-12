/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Control.h
 * File Function: Control类的定义
 * Author:        林继申
 * Update Date:   2023/12/12
 ****************************************************************/

#pragma once
#ifndef _CONTROL_H_
#define _CONTROL_H_

/*
 * Class Name:     Control
 * Class Function: 游戏控制类
 */
class Control {
public:
    Control(int maxPlayersNum) : maxPlayers(maxPlayersNum) {}
private:
    int maxPlayers;
};

#endif // !_CONTROL_H_