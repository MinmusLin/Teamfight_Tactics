/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Constant.h
 * File Function: 常变量的定义
 * Author:        林继申、刘淑仪、杨兆镇、杨宇琨
 * Update Date:   2023/12/19
 ****************************************************************/

#pragma once
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#include <map>
#include <string>

// 应用程序设置
constexpr int DESIGN_RESOLUTION_WIDTH = 1280;            // 设计分辨率宽度
constexpr int DESIGN_RESOLUTION_HEIGHT = 720;            // 设计分辨率高度
constexpr int SMALL_RESOLUTION_WIDTH = 960;              // 小分辨率宽度
constexpr int SMALL_RESOLUTION_HEIGHT = 540;             // 小分辨率高度
constexpr int MEDIUM_RESOLUTION_WIDTH = 1280;            // 中分辨率宽度
constexpr int MEDIUM_RESOLUTION_HEIGHT = 720;            // 中分辨率高度
constexpr int LARGE_RESOLUTION_WIDTH = 1920;             // 大分辨率宽度
constexpr int LARGE_RESOLUTION_HEIGHT = 1080;            // 大分辨率高度
constexpr float FRAME_RATE = 60.0f;                      // 帧率
constexpr char APPLICATION_TITLE[] = "Teamfight Tactic"; // 应用程序标题

// 网络环境设置
constexpr int HOSTNAME_LENGHT = 128;                               // 主机名长度
constexpr int MIN_PORT_ADDRESS = 49152;                            // 最小端口地址
constexpr int MAX_PORT_ADDRESS = 65535;                            // 最大端口地址
constexpr int MAX_CONNECTIONS = 8;                                 // 最大连接数量
constexpr int BUFFER_SIZE = 1024;                                  // 缓冲区大小
constexpr char CONNECTION_REFUSED_MSG[] = "Connection refused.";   // 拒绝连接提示消息
constexpr char CONNECTION_ACCEPTED_MSG[] = "Connection accepted."; // 接受连接提示消息

// 颜色设置
constexpr int DARK_BLUE_R = 0;  // 深蓝色 R 通道
constexpr int DARK_BLUE_G = 32; // 深蓝色 G 通道
constexpr int DARK_BLUE_B = 96; // 深蓝色 B 通道

// 场景界面设置
constexpr int NICKNAME_MAX_LENGTH = 6;                   // 游戏昵称最大长度
constexpr int INITIAL_SCENE_FONT_SIZE = 30;              // 初始场景字体大小
constexpr int INITIAL_SCENE_TEXTFIELD_OFFSET_Y = 40;     // 初始场景文本框位置 Y 偏移量
constexpr int INITIAL_SCENE_PROMPT_LABLE_OFFSET_Y = 150; // 初始场景提示标签位置 Y 偏移量
constexpr int INITIAL_SCENE_NAME_LABLE_OFFSET_Y = 280;   // 初始场景欢迎标签位置 Y 偏移量
constexpr int INITIAL_SCENE_BUTTON_OFFSET_Y = -180;      // 初始场景按钮位置 Y 偏移量
constexpr float SCENE_TRANSITION_DURATION = 0.3f;        // 场景切换时间
constexpr float PROMPT_MESSAGE_DURATION = 1.5f;          // 提示信息停留时间

// 对战界面设置
constexpr int WAITING_MAP_COUNT = 9;                // 候战区地图大小
constexpr int BATTLE_MAP_ROWS = 8;                  // 战斗区地图行数
constexpr int BATTLE_MAP_COLUMNS = 9;               // 战斗区地图列数
constexpr int PLACE_MAP_ROWS = BATTLE_MAP_ROWS / 2; // 放置区地图行数

// 商店界面设置
constexpr int MAX_SELECTABLE_CHAMPION_COUNT = 5;                     // 最大可选择战斗英雄数量
constexpr int SHOP_CHAMPION_INTERVAL = 10;                           // 商店战斗英雄按钮间距
constexpr int SHOP_CHAMPION_WIDTH = 120;                             // 商店战斗英雄按钮宽度
constexpr int SHOP_CHAMPION_HEIGHT = 100;                            // 商店战斗英雄按钮高度
constexpr int SHOP_CHAMPION_START_X = 370 + SHOP_CHAMPION_WIDTH / 2; // 商店战斗英雄起始按钮 X 坐标
constexpr int SHOP_CHAMPION_START_Y = 10 + SHOP_CHAMPION_HEIGHT / 2; // 商店战斗英雄起始按钮 Y 坐标

// 位置属性与屏幕坐标设置
constexpr int WAITING_AREA_START_X = 415;
constexpr int WAITING_AREA_START_Y = 195;
constexpr int BATTLE_AREA_START_X = 415;
constexpr int BATTLE_AREA_START_Y = 275;
constexpr int CHAMPION_HORIZONTAL_INTERVAL = 60;
constexpr int CHAMPION_VERTICAL_INTERVAL = 45;

// 练习模式难度定义
enum Difficulty {
    Easy, // 简单模式
    Hard  // 困难模式
};

// 战斗英雄种类定义
enum ChampionCategory {
    NoChampion = 0, // 无战斗英雄
    ChampionA,      // ChampionA
    ChampionB,      // ChampionB
    ChampionC,      // ChampionC
    ChampionD,      // ChampionD
    ChampionE       // ChampionE
};

// 位置状态定义
enum LocationStatus {
    WaitingArea, // 候战区
    BattleArea   // 战斗区
};

// 位置属性定义
struct Location {
    LocationStatus status; // 位置状态
    int position;          // 位置坐标
    bool operator<(const Location& other) const { // 重载运算符 < 用于 std::map
        if (status < other.status) return true;
        if (status > other.status) return false;
        return position < other.position;
    }
};

// 战斗英雄属性定义
typedef struct {
    ChampionCategory championCategory; // 战斗英雄种类
    std::string championName;          // 战斗英雄名称
    std::string championImagePath;     // 战斗英雄图片路径
    int price;                         // 战斗英雄价格
    int healthPoints;                  // 生命值
    int experiencePoints;              // 经验值
    int attackDamage;                  // 攻击伤害
    int skillDamage;                   // 技能伤害
    int skillTriggerThreshold;         // 技能触发阈值
    int attackRange;                   // 攻击范围
    float attackSpeed;                 // 攻击速度
    float movementSpeed;               // 移动速度
    float defenseCoefficient;          // 防御系数
} ChampionAttributes;

// 战斗英雄属性参数
const ChampionAttributes CHAMPION_A_ATTR = { // ChampionA
    ChampionA, "战斗英雄A", "../Resources/Champions/ChampionA.png", 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_B_ATTR = { // ChampionB
    ChampionB, "战斗英雄B", "../Resources/Champions/ChampionB.png", 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_C_ATTR = { // ChampionC
    ChampionC, "战斗英雄C", "../Resources/Champions/ChampionC.png", 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_D_ATTR = { // ChampionD
    ChampionD, "战斗英雄D", "../Resources/Champions/ChampionD.png", 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_E_ATTR = { // ChampionE
    ChampionE, "战斗英雄E", "../Resources/Champions/ChampionE.png", 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};

// 战斗英雄种类与属性键值对
const std::map<ChampionCategory, ChampionAttributes> CHAMPION_ATTR_MAP = {
    {ChampionA, CHAMPION_A_ATTR}, // ChampionA
    {ChampionB, CHAMPION_B_ATTR}, // ChampionB
    {ChampionC, CHAMPION_C_ATTR}, // ChampionC
    {ChampionD, CHAMPION_D_ATTR}, // ChampionD
    {ChampionE, CHAMPION_E_ATTR}  // ChampionE
};

#endif // !_CONSTANT_H_