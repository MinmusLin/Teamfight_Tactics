/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Constant.h
 * File Function: 常变量的定义
 * Author:        林继申、刘淑仪、杨兆镇、杨宇琨
 * Update Date:   2023/12/20
 ****************************************************************/

#pragma once
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#include <map>
#include <string>

// 应用程序设置
constexpr int DESIGN_RESOLUTION_WIDTH = 1280;      // 设计分辨率宽度
constexpr int DESIGN_RESOLUTION_HEIGHT = 720;      // 设计分辨率高度
constexpr int SMALL_RESOLUTION_WIDTH = 960;        // 小分辨率宽度
constexpr int SMALL_RESOLUTION_HEIGHT = 540;       // 小分辨率高度
constexpr int MEDIUM_RESOLUTION_WIDTH = 1280;      // 中分辨率宽度
constexpr int MEDIUM_RESOLUTION_HEIGHT = 720;      // 中分辨率高度
constexpr int LARGE_RESOLUTION_WIDTH = 1920;       // 大分辨率宽度
constexpr int LARGE_RESOLUTION_HEIGHT = 1080;      // 大分辨率高度
constexpr float FRAME_RATE = 60.0f;                // 应用程序帧率
const std::string APPLICATION_TITLE = "金铲铲之战"; // 应用程序标题

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

// 总场景界面设置
constexpr int NICKNAME_MAX_LENGTH = 6;            // 游戏昵称最大长度
constexpr float PROMPT_MESSAGE_DURATION = 1.5f;   // 提示信息停留时间
constexpr float SCENE_TRANSITION_DURATION = 0.3f; // 场景切换时间

// 启动场景界面设置
constexpr int STARTUP_SCENE_FONT_SIZE = 20;               // 启动场景字体大小
constexpr int STARTUP_SCENE_LOADINGBAR_OFFSET_Y = -241;   // 启动场景进度条位置 Y 偏移量
constexpr int STARTUP_SCENE_LOADING_LABLE_OFFSET_X = -30; // 启动场景进度标签位置 X 偏移量
constexpr float STARTUP_SCENE_DURATION = 2.0f;            // 启动场景加载时间

// 初始场景界面设置
constexpr int INITIAL_SCENE_FONT_SIZE = 30;              // 初始场景字体大小
constexpr int INITIAL_SCENE_LABLES_OFFSET_X = 349;       // 初始场景标签位置 X 偏移量
constexpr int INITIAL_SCENE_TEXTFIELD_OFFSET_Y = 111;    // 初始场景文本框位置 Y 偏移量
constexpr int INITIAL_SCENE_PROMPT_LABLE_OFFSET_Y = 180; // 初始场景提示标签位置 Y 偏移量
constexpr int INITIAL_SCENE_NAME_LABLE_OFFSET_Y = 280;   // 初始场景欢迎标签位置 Y 偏移量
constexpr int INITIAL_SCENE_BUTTON_OFFSET_Y = -310;      // 初始场景按钮位置 Y 偏移量

// 菜单场景界面设置
constexpr int MENU_SCENE_FONT_SIZE = 24;                     // 菜单场景字体大小
constexpr int MENU_SCENE_BUTTONS_OFFSET_X = -296;            // 菜单场景按钮与标签位置 X 偏移量
constexpr int MENU_SCENE_OFFLINE_MODE_BUTTON_OFFSET_Y = -30; // 菜单场景练习模式按钮位置 Y 偏移量
constexpr int MENU_SCENE_ONLINE_MODE_BUTTON_OFFSET_Y = -150; // 菜单场景联机模式按钮位置 Y 偏移量
constexpr int MENU_SCENE_SETTINGS_BUTTON_OFFSET_Y = -270;    // 菜单场景设置按钮位置 Y 偏移量
constexpr int MENU_SCENE_WELCOME_LABLE_OFFSET_Y = 240;       // 菜单场景欢迎标签位置 Y 偏移量

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

// 小时数与欢迎提示语键值对
const std::map<int, std::string> WELCOME_PROMPT = {
    {0,  "，凌晨好！星星还在，你也在，游戏之旅等待着你."},
    {1,  "，凌晨好！夜晚的秘密正在游戏世界中展开."},
    {2,  "，凌晨好！在这安静时刻，我们一起探索梦幻之地."},
    {3,  "，凌晨好！游戏世界在星光下更加迷人."},
    {4,  "，凌晨好！新的一天即将开始，让我们一起迎接."},
    {5,  "，凌晨好！让游戏点亮你的日出时分."},
    {6,  "，早上好！新的一天，阳光正好，新的挑战在等待."},
    {7,  "，早上好！让游戏的色彩伴随你的清晨."},
    {8,  "，早上好！一起在游戏的海洋中航行吧."},
    {9,  "，上午好！无尽的奇遇在这光辉时刻等着你."},
    {10, "，上午好！这个时刻，每一步棋都定局胜负."},
    {11, "，上午好！在午餐前，让我们再赢得一场胜利."},
    {12, "，中午好！在休息时刻，放松并享受游戏的乐趣."},
    {13, "，中午好！伴随午餐的时光，探索游戏的奇妙世界."},
    {14, "，下午好！阳光下，让我们共同探索未知."},
    {15, "，下午好！这是完美的时间，去体验新的游戏世界."},
    {16, "，下午好！在日落前，让我们获得荣耀."},
    {17, "，下午好！享受游戏，在这最美的时光."},
    {18, "，晚上好！让游戏陪伴你的黄昏时分."},
    {19, "，晚上好！在星光下揭开新的游戏篇章."},
    {20, "，晚上好！让魔法点亮你的游戏世界."},
    {21, "，晚上好！在这宁静的夜晚，战斗到底."},
    {22, "，晚上好！在这神秘的时刻，征服游戏世界."},
    {23, "，晚上好！夜深了，伴随月光，开始你的游戏之旅."}
};

#endif // !_CONSTANT_H_