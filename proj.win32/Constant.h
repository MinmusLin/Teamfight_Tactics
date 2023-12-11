/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Constant.h
 * File Function: 常变量的定义
 * Author:        林继申、刘淑仪、杨兆镇、杨宇琨
 * Update Date:   2023/12/11
 ****************************************************************/

#pragma once
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

/* 林继申维护常变量 */

// 应用程序设置
constexpr int DESIGN_RESOLUTION_WIDTH = 1280;
constexpr int DESIGN_RESOLUTION_HEIGHT = 720;
constexpr int SMALL_RESOLUTION_WIDTH = 960;
constexpr int SMALL_RESOLUTION_HEIGHT = 540;
constexpr int MEDIUM_RESOLUTION_WIDTH = 1280;
constexpr int MEDIUM_RESOLUTION_HEIGHT = 720;
constexpr int LARGE_RESOLUTION_WIDTH = 1920;
constexpr int LARGE_RESOLUTION_HEIGHT = 1080;
constexpr float FRAME_RATE = 60.0f;
const char APPLICATION_TITLE[] = "Teamfight Tactic";

// 网络设置
constexpr int HOSTNAME_LENGHT = 256;
constexpr int MIN_PORT_ADDRESS = 49152;
constexpr int MAX_PORT_ADDRESS = 65535;
constexpr int MAX_CONNECTIONS = 7;
constexpr int BUFFER_SIZE = 1024;
const char CONNECTION_REFUSED_MSG[] = "Connection refused.";
const char CONNECTION_ACCEPTED_MSG[] = "Connection accepted.";

constexpr int FONT_SIZE = 24;

constexpr int NICKNAME_MAX_LENGTH = 6;

constexpr float PROMPT_MESSAGE_DURATION = 1.5f;

/* 刘淑仪维护常变量 */

// TODO: 这里添加由刘淑仪维护的常变量

/* 杨兆镇维护常变量 */

// TODO: 这里添加由杨兆镇维护的常变量

/* 杨宇琨维护常变量 */

// TODO: 这里添加由杨宇琨维护的常变量

#endif // !_CONSTANT_H_