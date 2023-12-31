/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Constant.h
 * File Function: 常变量的定义
 * Author:        林继申、杨宇琨、刘淑仪、杨兆镇
 * Update Date:   2023/12/31
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#include <map>
#include <string>

// 应用程序设置
constexpr int DESIGN_RESOLUTION_WIDTH = 1280;                               // 设计分辨率宽度
constexpr int DESIGN_RESOLUTION_HEIGHT = 720;                               // 设计分辨率高度
constexpr int SMALL_RESOLUTION_WIDTH = 960;                                 // 小分辨率宽度
constexpr int SMALL_RESOLUTION_HEIGHT = 540;                                // 小分辨率高度
constexpr int MEDIUM_RESOLUTION_WIDTH = 1280;                               // 中分辨率宽度
constexpr int MEDIUM_RESOLUTION_HEIGHT = 720;                               // 中分辨率高度
constexpr int LARGE_RESOLUTION_WIDTH = 1920;                                // 大分辨率宽度
constexpr int LARGE_RESOLUTION_HEIGHT = 1080;                               // 大分辨率高度
constexpr float FRAME_RATE = 60.0f;                                         // 应用程序帧率
const std::string APPLICATION_TITLE = u8"金铲铲之战 Teamfight Tactics";      // 应用程序标题

// 网络环境设置
constexpr int HOSTNAME_MAX_LENGHT = 128;                                    // 主机名最大长度
constexpr int IPV4_ADDRESS_MAX_LENGTH = 15;                                 // IPv4 地址最大长度
constexpr int PORT_MAX_LENGTH = 5;                                          // 端口最大长度
constexpr int MIN_PORT_ADDRESS = 49152;                                     // 最小端口地址
constexpr int MAX_PORT_ADDRESS = 65535;                                     // 最大端口地址
constexpr int MAX_CONNECTIONS = 8;                                          // 最大连接数量
constexpr int BUFFER_SIZE = 256;                                            // 缓冲区大小
constexpr int THREAD_SLEEP_DURATION_MILLISECONDS = 100;                     // 监听服务器消息线程休眠毫秒数
constexpr int CONNECTION_TIMEOUT_DURATION = 2;                              // 服务器连接超时时间
constexpr int MESSAGE_IDENTIFIER_LENGTH = 10;                               // 服务器消息标识符长度
constexpr int SERVER_REFRESH_INTERVAL_MAGNIFICATION = 10;                   // 监听服务器刷新时间间隔倍率
constexpr float SERVER_REFRESH_INTERVAL = 0.02f;                            // 监听服务器刷新时间间隔
constexpr char CONNECTION_REFUSED_MSG[] = "Connection refused.";            // 拒绝连接提示信息
constexpr char CONNECTION_ACCEPTED_MSG[] = "Connection accepted.";          // 接受连接提示信息
constexpr char START_GAME_IDENTIFIER[] = "Start game";                      // 开始游戏提示信息标识符
constexpr char START_GAME_MSG[] = "Start game.";                            // 开始游戏提示信息
constexpr char CURRENT_CONNECTIONS_IDENTIFIER[] = "Connection";             // 服务器当前连接数量标识符
constexpr char CURRENT_CONNECTIONS_FORMAT[] = "Connection=%d";              // 服务器当前连接数量格式字符串
constexpr char PLAYER_NAME_IDENTIFIER[] = "PlayerName";                     // 玩家姓名标识符
constexpr char PLAYER_NAME_FORMAT[] = "PlayerName=%s";                      // 玩家姓名格式字符串
constexpr char BATTLE_MAP_IDENTIFIER[] = "BattleMaps";                      // 玩家战斗区地图标识符
constexpr char BATTLE_MAP_FORMAT[] = "BattleMaps=%s";                       // 玩家战斗区地图格式字符串
constexpr char HEALTH_POINTS_IDENTIFIER[] = "HealthPoin";                   // 玩家生命值标识符
constexpr char HEALTH_POINTS_FORMAT[] = "HealthPoint=%d，Socket=%d";        // 玩家生命值格式字符串

// 颜色设置
constexpr int DARK_BLUE_R = 0;                                              // 深蓝色 R 通道
constexpr int DARK_BLUE_G = 32;                                             // 深蓝色 G 通道
constexpr int DARK_BLUE_B = 96;                                             // 深蓝色 B 通道
constexpr int GOLDEN_R = 223;                                               // 金黄色 R 通道
constexpr int GOLDEN_G = 176;                                               // 金黄色 G 通道
constexpr int GOLDEN_B = 11;                                                // 金黄色 B 通道

// 启动场景设置
constexpr int STARTUP_SCENE_FONT_SIZE = 20;                                 // 启动场景字体大小
constexpr int STARTUP_SCENE_LOADINGBAR_OFFSET_Y = -241;                     // 启动场景加载进度条位置 Y 偏移量
constexpr int STARTUP_SCENE_LOADING_LABEL_OFFSET_X = -30;                   // 启动场景加载进度条标签位置 X 偏移量
constexpr float STARTUP_SCENE_DURATION = 2.0f;                              // 启动场景加载时间
constexpr float SCENE_TRANSITION_DURATION = 0.3f;                           // 场景切换时间

// 初始场景设置
constexpr int NICKNAME_MAX_LENGTH = 6;                                      // 游戏昵称最大长度
constexpr int INITIAL_SCENE_FONT_SIZE = 30;                                 // 初始场景字体大小
constexpr int INITIAL_SCENE_LABELS_OFFSET_X = 349;                          // 初始场景标签位置 X 偏移量
constexpr int INITIAL_SCENE_TEXTFIELD_OFFSET_Y = 111;                       // 初始场景文本框位置 Y 偏移量
constexpr int INITIAL_SCENE_PROMPT_LABEL_OFFSET_Y = 180;                    // 初始场景提示标签位置 Y 偏移量
constexpr int INITIAL_SCENE_NAME_LABEL_OFFSET_Y = 280;                      // 初始场景欢迎标签位置 Y 偏移量
constexpr int INITIAL_SCENE_BUTTON_OFFSET_Y = -310;                         // 初始场景按钮位置 Y 偏移量
constexpr float PROMPT_MESSAGE_DURATION = 1.5f;                             // 提示信息停留时间

// 选择场景设置
constexpr int MAX_LITTLE_CHAMPION_COUNT = 8;                                // 小小英雄种类最大数量
constexpr int DEFAULT_LITTLE_CHAMPION_CATEGORY = 0;                         // 缺省小小英雄种类
constexpr int SELECTION_SCENE_BUTTON_OFFSET_X = -450;                       // 选择场景小小英雄按钮位置 X 偏移量
constexpr int SELECTION_SCENE_BUTTON_OFFSET_Y = -200;                       // 选择场景小小英雄按钮位置 Y 偏移量
constexpr int SELECTION_SCENE_BUTTON_HORIZONTAL_INTERVAL = 300;             // 选择场景小小英雄按钮位置水平间距
constexpr int SELECTION_SCENE_BUTTON_VERTICAL_INTERVAL = 250;               // 选择场景小小英雄按钮位置垂直间距
constexpr int SELECTION_SCENE_LABEL_OFFSET_Y = 250;                         // 选择场景提示标签位置 Y 偏移量
constexpr int SELECTION_SCENE_LABEL_FONT_SIZE = 50;                         // 选择场景提示标签字体大小

// 菜单场景设置
constexpr int RANDOM_PROMPT_COUNT = 24;                                     // 随机欢迎提示语数量
constexpr int MENU_SCENE_FONT_SIZE = 24;                                    // 菜单场景字体大小
constexpr int MENU_SCENE_BUTTONS_OFFSET_X = -296;                           // 菜单场景按钮与标签位置 X 偏移量
constexpr int MENU_SCENE_OFFLINE_MODE_BUTTON_OFFSET_Y = -30;                // 菜单场景练习模式按钮位置 Y 偏移量
constexpr int MENU_SCENE_ONLINE_MODE_BUTTON_OFFSET_Y = -150;                // 菜单场景联机模式按钮位置 Y 偏移量
constexpr int MENU_SCENE_SETTINGS_BUTTON_OFFSET_Y = -270;                   // 菜单场景设置按钮位置 Y 偏移量
constexpr int MENU_SCENE_WELCOME_LABEL_OFFSET_Y = 240;                      // 菜单场景欢迎标签位置 Y 偏移量
constexpr int MENU_SCENE_EXIT_GAME_BUTTON_OFFSET_X = 55;                    // 菜单场景退出游戏按钮位置 X 偏移量
constexpr int MENU_SCENE_EXIT_GAME_BUTTON_OFFSET_Y = 55;                    // 菜单场景退出游戏按钮位置 Y 偏移量
constexpr int MENU_SCENE_REFERENCE_BUTTON_OFFSET_X = 150;                   // 菜单场景玩法介绍按钮位置 X 偏移量
constexpr int MENU_SCENE_REFERENCE_BUTTON_OFFSET_Y = 55;                    // 菜单场景玩法介绍按钮位置 Y 偏移量
constexpr int ONLINE_MODE_MENU_SCENE_BUTTON_OFFSET_X = 415;                 // 联机模式菜单场景按钮位置 X 偏移量
constexpr int ONLINE_MODE_MENU_SCENE_BUTTON_OFFSET_Y = -220;                // 联机模式菜单场景按钮位置 Y 偏移量
constexpr int ONLINE_MODE_MENU_SCENE_FONT_SIZE = 30;                        // 联机模式菜单场景字体大小
constexpr int ONLINE_MODE_MENU_SCENE_IPV4_TEXTFIELD_OFFSET_Y = -167;        // 联机模式菜单场景 IPv4 文本框位置 Y 偏移量
constexpr int ONLINE_MODE_MENU_SCENE_PORT_TEXTFIELD_OFFSET_Y = -275;        // 联机模式菜单场景端口文本框位置 Y 偏移量
constexpr int ONLINE_MODE_MENU_SCENE_PROMPT_LABEL_OFFSET_Y = 285;           // 联机模式菜单场景提示标签位置 Y 偏移量
constexpr int REFERENCE_SCENE_RETURN_MENU_BUTTON_OFFSET_X = 560;            // 玩法场景返回菜单按钮位置 X 偏移量
constexpr int REFERENCE_SCENE_RETURN_MENU_BUTTON_OFFSET_Y = -315;           // 玩法场景返回菜单按钮位置 Y 偏移量
constexpr float START_GAME_BUTTON_APPEARANCE_DURATION = 1.5f;               // 联机模式菜单场景开始游戏按钮出现时间间隔
constexpr float CONNECTION_FAILED_PROMPT_MESSAGE_DURATION = 3.0f;           // 服务器连接失败提示信息停留时间
constexpr float RANDOM_WELCOME_PROMPT_PROBABILITY = 0.5f;                   // 随机欢迎提示语概率

// 对战场景设置
constexpr int WAITING_MAP_COUNT = 9;                                        // 候战区地图大小
constexpr int BATTLE_MAP_ROWS = 8;                                          // 战斗区地图行数
constexpr int BATTLE_MAP_COLUMNS = 9;                                       // 战斗区地图列数
constexpr int PLACE_MAP_ROWS = BATTLE_MAP_ROWS / 2;                         // 放置区地图行数
constexpr int BATTLE_AREA_MIN_CHAMPION_COUNT = 3;                           // 最低等级战斗区最大英雄数量
constexpr int BATTLE_AREA_MAX_CHAMPION_COUNT = 9;                           // 最高等级战斗区最大英雄数量
constexpr int BATTLE_SCENE_LOADINGBAR_X = 213;                              // 对战场景准备进度条位置 X 坐标
constexpr int BATTLE_SCENE_LOADINGBAR_Y = 669;                              // 对战场景准备进度条位置 Y 坐标
constexpr int BATTLE_SCENE_LOADINGBAR_LABEL_FONT_SIZE = 20;                 // 对战场景准备进度条标签字体大小
constexpr int BATTLE_SCENE_LOADINGBAR_LABEL_OFFSET_X = -18;                 // 对战场景准备进度条标签位置 X 偏移量
constexpr int BATTLE_SCENE_LOADINGBAR_LABEL_THRESHOLD = 20;                 // 对战场景准备时间显示阈值
constexpr int BATTLE_SCENE_RETURN_MENU_BUTTON_OFFSET_X = 522;               // 对战场景返回菜单按钮位置 X 偏移量
constexpr int BATTLE_SCENE_RETURN_MENU_BUTTON_OFFSET_Y = -294;              // 对战场景返回菜单按钮位置 Y 偏移量
constexpr int BATTLE_SCENE_DELETE_CHAMPION_BUTTON_START_X = 118;            // 对战场景战斗英雄删除按钮位置 X 坐标
constexpr int BATTLE_SCENE_DELETE_CHAMPION_BUTTON_START_Y = 77;             // 对战场景战斗英雄删除按钮位置 Y 坐标
constexpr int BATTLE_SCENE_DELETE_CHAMPION_BUTTON_UPPER_BOUNDARY = 130;     // 对战场景战斗英雄删除按钮上边界 Y 坐标
constexpr int BATTLE_SCENE_DELETE_CHAMPION_BUTTON_LOWER_BOUNDARY = 24;      // 对战场景战斗英雄删除按钮下边界 Y 坐标
constexpr int BATTLE_SCENE_DELETE_CHAMPION_BUTTON_LEFT_BOUNDARY = 25;       // 对战场景战斗英雄删除按钮左边界 X 坐标
constexpr int BATTLE_SCENE_DELETE_CHAMPION_BUTTON_RIGHT_BOUNDARY = 210;     // 对战场景战斗英雄删除按钮右边界 X 坐标
constexpr int SCORE_BOARD_LAYER_START_X = 1125;                             // 分数表层背景位置 X 坐标
constexpr int SCORE_BOARD_LAYER_START_Y = 680;                              // 分数表层背景位置 Y 坐标
constexpr int SCORE_BOARD_LAYER_VERTICAL_INTERVAL = 69;                     // 分数表层背景垂直间距
constexpr int SCORE_BOARD_LAYER_NAME_LABEL_OFFSET_X = -125;                 // 分数表层玩家姓名标签
constexpr int SCORE_BOARD_LAYER_SCORE_LABEL_OFFSET_X = 90;                  // 分数表层玩家生命值标签
constexpr int SCORE_BOARD_LAYER_RANK_LABEL_OFFSET_X = 115;                  // 分数表层玩家排名标签
constexpr int SCORE_BOARD_LABEL_FONT_SIZE = 25;                             // 分数表层标签字体大小
constexpr int BATTLE_END_LABEL_FONT_SIZE = 200;                             // 对战结束提示标签字体大小
constexpr int BATTLE_END_LABEL_OFFSET_Y = 74;                               // 对战结束提示标签位置 Y 偏移量
constexpr int BATTLE_END_LABEL_OUTLINE_WIDTH = 4;                           // 对战结束提示标签描边宽度
constexpr int BATTLE_END_LABEL_SHADOW_OFFSET_X = 2;                         // 对战结束提示标签阴影 X 偏移量
constexpr int BATTLE_END_LABEL_SHADOW_OFFSET_Y = -2;                        // 对战结束提示标签阴影 Y 偏移量
constexpr int BATTLE_END_LABEL_BLUR_RADIUS = 3;                             // 对战结束提示标签模糊半径
constexpr int CHAMPION_HEALTHBAR_VERTICAL_INTERVAL = 29;                    // 对战场景生命条垂直间距
constexpr int CHAMPION_MANABAR_VERTICAL_INTERVAL = 22;                      // 对战场景经验条垂直间距
constexpr int TALENT_RUNE_COUNT = 3;                                        // 天赋符文数量
constexpr int TALENT_RUNE_BUTTON_OFFSET_X = 390;                            // 天赋符文按钮位置 X 偏移量
constexpr int TALENT_RUNE_BUTTON_OFFSET_Y = -55;                            // 天赋符文按钮位置 X 偏移量
constexpr int BOND_EFFECT_START_X = -2;                                     // 羁绊效果位置 X 坐标
constexpr int BOND_EFFECT_HORIZONTAL_INTERVAL = 65;                         // 羁绊效果水平间距
constexpr int MY_BOND_EFFECT_START_Y = 194;                                 // 我方羁绊效果位置 Y 坐标
constexpr int ENEMY_BOND_EFFECT_START_Y = 670;                              // 敌方羁绊效果位置 Y 坐标
constexpr int LITTLE_CHAMPION_OFFSET_Y = -250;                              // 小小英雄位置 Y 偏移量
constexpr int LITTLE_CHAMPION_MOVEMENT_SPEED = 200;                         // 小小英雄移动速度
constexpr int LITTLE_CHAMPION_LABEL_OFFSET_Y = -315;                        // 小小英雄登场标签位置 Y 偏移量
constexpr int LITTLE_CHAMPION_LABEL_FONT_SIZE = 30;                         // 小小英雄登场标签字体大小
constexpr int INTERVAL_BETWEEN_WEAPON_AND_CHAMPION = 40;                    // 对战场景战斗英雄与武器间距
constexpr int WEAPON_ANIMATION_ROTATION_ANGLE = 60;                         // 对战场景武器动画旋转角度
constexpr int WEAPON_ANIMATION_ROTATION_COUNT = 4;                          // 对战场景武器动画旋转次数
constexpr float LITTLE_CHAMPION_PARTICLE_SCALE = 0.75f;                     // 小小英雄粒子效果缩放比例
constexpr float LITTLE_CHAMPION_PARTICLE_LIFE = 1.0f;                       // 小小英雄粒子效果生命周期
constexpr float LITTLE_CHAMPION_ROTATE_DURATION = 0.5f;                     // 小小英雄旋转动画时间
constexpr float WEAPON_ANIMATION_ROTATION_DURATION = 0.15f;                 // 对战场景武器动画旋转时间
constexpr float BATTLE_SCENE_LOADINGBAR_DURATION = 30.0f;                   // 对战场景准备时间
constexpr float BATTLE_END_DURATION = 2.0f;                                 // 对战结束停留时间

// 设置场景设置
constexpr int SETTINGS_SCENE_SLIDER_OFFSET_X = -150;                        // 设置场景音量滑动条与标签位置 X 偏移量
constexpr int SETTINGS_SCENE_BGMSLIDER_OFFSET_Y = 69;                       // 设置场景背景音乐音量滑动条与标签位置 Y 偏移量
constexpr int SETTINGS_SCENE_EFFSLIDER_OFFSET_Y = -34;                      // 设置场景音效音量滑动条与标签位置 Y 偏移量
constexpr int SETTINGS_SCENE_CHECKBOX_OFFSET_Y = -157;                      // 设置场景难度复选框与标签位置 Y 偏移量
constexpr int SETTINGS_SCENE_EASY_CHECKBOX_OFFSET_X = -307;                 // 设置场景简单难度复选框与标签位置 X 偏移量
constexpr int SETTINGS_SCENE_NORMAL_CHECKBOX_OFFSET_X = -166;               // 设置场景正常难度复选框与标签位置 X 偏移量
constexpr int SETTINGS_SCENE_DIFFICULT_CHECKBOX_OFFSET_X = -25;             // 设置场景困难难度复选框与标签位置 X 偏移量
constexpr int SETTINGS_SCENE_RETURN_MENU_BUTTON_OFFSET_X = 529;             // 设置场景返回菜单按钮位置 X 偏移量
constexpr int SETTINGS_SCENE_RETURN_MENU_BUTTON_OFFSET_Y = -300;            // 设置场景返回菜单按钮位置 Y 偏移量
constexpr int DEFAULT_MUSIC_SIGN = -1;                                      // 缺省音乐标识
constexpr float DEFAULT_MUSIC_VOLUMN = 0.5f;                                // 缺省音量大小

// 商店设置
constexpr int MAX_SELECTABLE_CHAMPION_COUNT = 5;                            // 最大可选择战斗英雄数量
constexpr int CHAMPION_UPLEVEL_COUNT = 3;                                   // 战斗英雄升级数量
constexpr int SHOP_CHAMPION_INTERVAL = 10;                                  // 商店战斗英雄按钮间距
constexpr int SHOP_CHAMPION_WIDTH = 120;                                    // 商店战斗英雄按钮宽度
constexpr int SHOP_CHAMPION_HEIGHT = 100;                                   // 商店战斗英雄按钮高度
constexpr int SHOP_CHAMPION_START_X = 386 + SHOP_CHAMPION_WIDTH / 2;        // 商店战斗英雄起始按钮位置 X 坐标
constexpr int SHOP_CHAMPION_START_Y = 10 + SHOP_CHAMPION_HEIGHT / 2;        // 商店战斗英雄起始按钮位置 Y 坐标
constexpr int SHOP_UPLEVEL_BUTTON_OFFSET_X = -324;                          // 商店升级按钮位置 X 偏移量
constexpr int SHOP_UPLEVEL_BUTTON_OFFSET_Y = -273;                          // 商店升级按钮位置 Y 偏移量
constexpr int SHOP_REFRESH_BUTTON_OFFSET_X = -324;                          // 商店刷新按钮位置 X 偏移量
constexpr int SHOP_REFRESH_BUTTON_OFFSET_Y = -328;                          // 商店刷新按钮位置 Y 偏移量
constexpr int SHOP_LEVEL_LABEL_OFFSET_X = -395;                             // 商店等级标签位置 X 偏移量
constexpr int SHOP_LEVEL_LABEL_OFFSET_Y = -228;                             // 商店等级标签位置 Y 偏移量
constexpr int SHOP_LEVEL_LABEL_FONT_SIZE = 20;                              // 商店等级标签字体大小
constexpr int SHOP_COIN_LABEL_FONT_SIZE = 20;                               // 商店金币数量标签字体大小
constexpr int SHOP_COIN_LABEL_OFFSET_X = 358;                               // 商店金币数量标签位置 X 偏移量
constexpr int SHOP_COIN_LABEL_OFFSET_Y = -228;                              // 商店金币数量标签位置 Y 偏移量
constexpr int SHOP_COIN_LABEL_START_X = 334;                                // 刷新商店和升级所需金币数量标签位置 X 坐标
constexpr int SHOP_REFRESH_COIN_LABEL_START_Y = 33;                         // 刷新商店所需金币数量标签位置 Y 坐标
constexpr int SHOP_UPLEVEL_COIN_LABEL_START_Y = 88;                         // 升级所需金币数量标签位置 Y 坐标
constexpr int INITIAL_GOLD_COIN = 14;                                       // 初始金币数量
constexpr int REFRESH_SHOP_PRICE = 2;                                       // 刷新商店所需金币数量
const std::map<int, int> UPLEVEL_PRICE = {                                  // 升级所需金币数量
    {BATTLE_AREA_MIN_CHAMPION_COUNT, 12},                                   // 等级 1 升级至等级 2 所需金币数量
    {BATTLE_AREA_MIN_CHAMPION_COUNT + 1, 16},                               // 等级 2 升级至等级 3 所需金币数量
    {BATTLE_AREA_MIN_CHAMPION_COUNT + 2, 20},                               // 等级 3 升级至等级 4 所需金币数量
    {BATTLE_AREA_MIN_CHAMPION_COUNT + 3, 28},                               // 等级 4 升级至等级 5 所需金币数量
    {BATTLE_AREA_MIN_CHAMPION_COUNT + 4, 36},                               // 等级 5 升级至等级 6 所需金币数量
    {BATTLE_AREA_MIN_CHAMPION_COUNT + 5, 52},                               // 等级 6 升级至等级 7 所需金币数量
};

// 战斗英雄属性层设置
constexpr int CHAMPION_ATTRIBUTES_FONT_SIZE = 18;                           // 战斗英雄属性标签字体大小
constexpr int CHAMPION_NAME_LABEL_FONT_SIZE = 30;                           // 战斗英雄名称标签字体大小
constexpr int BACKGROUND_IMAGE_START_X = 178;                               // 背景图位置 X 坐标
constexpr int BACKGROUND_IMAGE_START_Y = 407;                               // 背景图位置 Y 坐标
constexpr int BACKGROUND_IMAGE_TRANSPARENCY = 230;                          // 背景图透明度
constexpr int CHAMPION_IMAGE_START_X = 110;                                 // 战斗英雄图片位置 X 坐标
constexpr int CHAMPION_IMAGE_START_Y = 547;                                 // 战斗英雄图片位置 Y 坐标
constexpr int CHAMPION_NAME_LABEL_START_X = 172;                            // 战斗英雄名称标签位置 X 坐标
constexpr int CHAMPION_NAME_LABEL_START_Y = 564;                            // 战斗英雄名称标签位置 Y 坐标
constexpr int FIRST_COLUMN_START_X = 130;                                   // 第一列属性标签位置 X 坐标
constexpr int SECOND_COLUMN_START_X = 242;                                  // 第二列属性标签位置 X 坐标
constexpr int HEALTH_POINTS_LEBEL_START_Y = 466;                            // 生命值标签位置 Y 坐标
constexpr int ATTACK_DAMAGE_LABEL_START_Y = 404;                            // 攻击伤害标签位置 Y 坐标
constexpr int ATTACK_RANGE_LABEL_START_Y = 329;                             // 攻击范围标签位置 Y 坐标
constexpr int ATTACK_SPEED_LABEL_START_Y = 254;                             // 攻击速度标签位置 Y 坐标
constexpr int PRICE_LABEL_START_Y = HEALTH_POINTS_LEBEL_START_Y;            // 价格标签位置 Y 坐标
constexpr int MOVEMENT_SPEED_START_Y = ATTACK_DAMAGE_LABEL_START_Y;         // 移动速度标签位置 Y 坐标
constexpr int DEFENSE_COEFFICIENT_START_Y = ATTACK_RANGE_LABEL_START_Y;     // 防御系数标签位置 Y 坐标
constexpr int SKILL_TRIGGER_THRESHOLD_START_Y = ATTACK_SPEED_LABEL_START_Y; // 技能触发阈值标签位置 Y 坐标
constexpr int LEVEL_LABEL_START_X = 245;                                    // 等级标签位置 X 坐标
constexpr int LEVEL_LABEL_START_Y = 521;                                    // 等级标签位置 Y 坐标

// 位置属性与屏幕坐标设置
constexpr int WAITING_AREA_START_X = 415;                                   // 候战区起始屏幕坐标位置 X 坐标
constexpr int WAITING_AREA_START_Y = 195;                                   // 候战区起始屏幕坐标位置 Y 坐标
constexpr int BATTLE_AREA_START_X = 415;                                    // 战斗区起始屏幕坐标位置 X 坐标
constexpr int BATTLE_AREA_START_Y = 275;                                    // 战斗区起始屏幕坐标位置 Y 坐标
constexpr int CHAMPION_HORIZONTAL_INTERVAL = 60;                            // 战斗英雄水平间距
constexpr int CHAMPION_VERTICAL_INTERVAL = 45;                              // 战斗英雄垂直间距

// 战斗参数设置
constexpr int CHAMPION_CATEGORY_NUMBERS = 15;                               // 战斗英雄种类数量
constexpr int BATTLE_STAGE_NUMBERS = 3;                                     // 战斗阶段状态数量
constexpr int INITIAL_HEALTH_POINTS = 100;                                  // 玩家初始生命值
constexpr int RUNE_WARRIOR_HEALTH_POINTS_BUFF = 20;                         // 斗士符文初始生命值加成
constexpr int RUNE_PIRATE_GOLD_COINS_BUFF = 10;                             // 海盗符文初始金币数量加成
constexpr int INCREASED_MAGIC_POINTS = 20;                                  // 攻击对应增加魔法值
constexpr int DECREASED_HEALTH_POINTS = 5;                                  // 存活战斗英雄对应减少生命值
constexpr int INCREASED_GOLD_COINS = 5;                                     // 存活战斗英雄对应增加金币数量
constexpr int NEW_BATTLE_INCREASED_GOLD_COINS = 10;                         // 新战斗增加金币数量
constexpr int EARLY_MIDDLE_STAGE_THRESHOLD = 20;                            // 前中期战斗阶段阈值
constexpr int MIDDLE_LATE_STAGE_THRESHOLD = 50;                             // 中后期战斗阶段阈值
constexpr int DEFENSE_SCORE_COEFFICIENT = 200;                              // 防御分数系数
constexpr int ATTACK_SCORE_COEFFICIENT = 30;                                // 攻击分数系数
constexpr int SPEED_SCORE_COEFFICIENT = 1;                                  // 速度分数系数
constexpr int STAGE_SCORE_THRESHOLDS_COUNT = 6;                             // 战斗阶段划分个数
constexpr int SKILL_ATTACK_DAMAGE_UP = 50;                                  // 技能攻击伤害升级
constexpr int ATTACK_RANGE_THRESHOLD = 1;                                   // 攻击范围阈值
constexpr int ATTACK_DAMAGE_MAGNIFICATION_HIGH = 5;                         // 攻击伤害高倍率
constexpr int ATTACK_DAMAGE_MAGNIFICATION_MIDDLE = 3;                       // 攻击伤害中倍率
constexpr int ATTACK_DAMAGE_MAGNIFICATION_LOW = 2;                          // 攻击伤害低倍率
constexpr int DEPLOY_CHAMPIONS_MAX_COUNT = 2;                               // 部署战斗英雄初始数量
constexpr int MAX_BOND_COUNT = 6;                                           // 战斗英雄羁绊效果数量
constexpr int BOND_EFFECT_TRIGGER_CONDITION = 2;                            // 羁绊效果触发条件
constexpr int BROTHERHOOD_MOVEMENT_SPEED_MULTIPLIER = 3;                    // 兄弟羁绊效果移动速度乘法系数
constexpr int BROTHERHOOD_ATTACK_SPEED_MULTIPLIER = 2;                      // 兄弟羁绊效果攻击速度乘法系数
constexpr int LOUT_MOVEMENT_SPEED_MULTIPLIER = 2;                           // 莽夫羁绊效果乘法系数
constexpr int LOUT_ATTACK_DAMAGE_MULTIPLIER = 2;                            // 莽夫羁绊效果乘法系数
constexpr int DARKSIDE_ATTACK_DAMAGE_MULTIPLIER = 2;                        // 死神羁绊效果乘法系数
constexpr int GOODSHOOTER_ATTACK_SPEED_MULTIPLIER = 3;                      // 神射手羁绊效果乘法系数
constexpr int POPSTAR_ATTACK_SPEED_MULTIPLIER = 3;                          // 卡莎羁绊效果乘法系数
constexpr int POPSTAR_MOVEMENT_SPEED_MULTIPLIER = 5;                        // 卡莎羁绊效果乘法系数
constexpr float DARKSIDE_SKILL_TRIGGER_MULTIPLIER = 0.5f;                   // 死神羁绊效果乘法系数
constexpr float LOUT_HEALTH_POINTS_MULTIPLIER = 1.5f;                       // 莽夫羁绊效果乘法系数
constexpr float SKILL_DEFENSE_COEFFICIENT_UP = 1.0f;                        // 技能防御系数升级
constexpr float SKILL_ATTACK_SPEED_UP = 2.0f;                               // 技能攻击速度升级
constexpr float DEFENSE_COEFFICIENT_THRESHOLD_HIGH = 1.5f;                  // 防御系数高阈值
constexpr float DEFENSE_COEFFICIENT_THRESHOLD_LOW = 1.4f;                   // 防御系数低阈值
constexpr double DEFENSE_SCORE_WEIGHT = 2.0;                                // 战斗英雄职业偏好防御分数权重
constexpr double ATTACK_SCORE_WEIGHT = 2.5;                                 // 战斗英雄职业偏好攻击分数权重
constexpr double SPEED_SCORE_WEIGHT = 1.0;                                  // 战斗英雄职业偏好速度分数权重
constexpr int STAGE_SCORE_THRESHOLDS[] = { 0, 5, 10, 25, 50, 60 };          // 战斗阶段划分阈值
constexpr int STAGE_WITH_RATE_OF_CHAMPIONS[3][5] = {                        // 各个战斗阶段的战斗英雄选择概率
    {6, 5, 3, 1, 0},                                                        // 前期战斗阶段战斗英雄选择概率
    {5, 5, 3, 1, 1},                                                        // 中期战斗阶段战斗英雄选择概率
    {4, 5, 2, 2, 2},                                                        // 后期战斗阶段战斗英雄选择概率
};

// 网络连接状态定义
enum ConnectionStatus {
    ConnectionError,    // 连接错误
    ConnectionRefused,  // 连接拒绝
    ConnectionAccepted, // 连接接受
    ConnectionTimeout   // 连接超时
};

// 练习模式难度定义
enum Difficulty {
    Easy,               // 简单模式
    Normal,             // 正常模式
    Hard                // 困难模式
};

// 位置状态定义
enum LocationStatus {
    WaitingArea,        // 候战区
    BattleArea          // 战斗区
};

// 战斗胜负状态定义
enum BattleSituation {
    Lose,               // 失败
    Draw,               // 平局
    Win                 // 胜利
};

// 战斗阶段状态定义
enum BattleStage {
    EarlyStage,         // 前期战斗阶段
    MiddleStage,        // 中期战斗阶段
    LateStage           // 后期战斗阶段
};

// 战斗英雄羁绊效果定义
enum Bond {
    NoBond,             // 无羁绊效果
    Brotherhood,        // 兄弟（永恩、亚索）
    Lout,               // 莽夫（奥拉夫、潘森）
    DarkSide,           // 死神（伊芙琳、阿木木、卡尔萨斯）
    GoodShooter,        // 神射手（库奇、金克丝）
    PopStar             // 星之守护（卡莎）
};

// 战斗英雄天赋符文定义
enum TalentRune {
    Pirate,             // 海盗（增加每回合金币数量）
    General,            // 将军（增加英雄位）
    Warriors,           // 斗士（增加初始生命值）
    NoTalentRune        // 无天赋符文
};

// 战斗英雄种类定义
enum ChampionCategory {
    NoChampion,         // 无战斗英雄
    Champion1,          // 劫（一星）
    Champion2,          // 劫（二星）
    Champion3,          // 永恩（一星）
    Champion4,          // 永恩（二星）
    Champion5,          // 奥拉夫（一星）
    Champion6,          // 奥拉夫（二星）
    Champion7,          // 潘森（一星）
    Champion8,          // 潘森（二星）
    Champion9,          // 伊芙琳（一星）
    Champion10,         // 伊芙琳（二星）
    Champion11,         // 库奇（一星）
    Champion12,         // 库奇（二星）
    Champion13,         // 塔里克（一星）
    Champion14,         // 塔里克（二星）
    Champion15,         // 亚索（一星）
    Champion16,         // 亚索（二星）
    Champion17,         // 金克丝（一星）
    Champion18,         // 金克丝（二星）
    Champion19,         // 塔姆（一星）
    Champion20,         // 塔姆（二星）
    Champion21,         // 蔚（一星）
    Champion22,         // 蔚（二星）
    Champion23,         // 阿木木（一星）
    Champion24,         // 阿木木（二星）
    Champion25,         // 奎桑提（一星）
    Champion26,         // 奎桑提（二星）
    Champion27,         // 卡尔萨斯（一星）
    Champion28,         // 卡尔萨斯（二星）
    Champion29,         // 卡莎（一星）
    Champion30          // 卡莎（二星）
};

// 位置属性定义
struct Location {
    LocationStatus status;                        // 位置状态
    int position;                                 // 位置坐标
    bool operator<(const Location& other) const { // 重载运算符 < 用于 std::map
        if (status < other.status) {
            return true;
        }
        if (status > other.status) {
            return false;
        }
        return position < other.position;
    }
};

// 战斗英雄职业偏好定义
typedef struct {
    double defenseScore;               // 防御分数
    double attackScore;                // 攻击分数
    double speedScore;                 // 速度分数
} ProfessionPreference;

// 战斗位置属性定义
typedef struct {
    int x;                             // X 坐标
    int y;                             // Y 坐标
} BattleLocation;

// 战斗英雄属性定义
typedef struct {
    ChampionCategory championCategory; // 战斗英雄种类
    std::string championName;          // 战斗英雄名称
    std::string championImagePath;     // 战斗英雄图片路径
    int price;                         // 价格
    int level;                         // 等级
    int healthPoints;                  // 生命值
    int magicPoints;                   // 魔法值
    int attackDamage;                  // 攻击伤害
    int skillTriggerThreshold;         // 技能触发阈值
    int attackRange;                   // 攻击范围
    float attackSpeed;                 // 攻击速度
    float movementSpeed;               // 移动速度
    float defenseCoefficient;          // 防御系数
    Bond bond;                         // 羁绊效果
} ChampionAttributes;

// 战斗英雄属性参数
const ChampionAttributes CHAMPION_1_ATTR = { // 劫（一星）
    Champion1, u8"劫", "../Resources/Champions/Champion1.png", 1, 1, 500, 0, 50, 200, 1, 0.75f, 1.0f, 1.0f, NoBond
};
const ChampionAttributes CHAMPION_2_ATTR = { // 劫（二星）
    Champion2, u8"劫", "../Resources/Champions/Champion2.png", 3, 2, 900, 0, 75, 200, 1, 0.75f, 1.0f, 1.0f, NoBond
};
const ChampionAttributes CHAMPION_3_ATTR = { // 永恩（一星）
    Champion3, u8"永恩", "../Resources/Champions/Champion3.png", 1, 1, 550, 0, 45, 200, 1, 1.0f, 1.0f, 1.2f, Brotherhood
};
const ChampionAttributes CHAMPION_4_ATTR = { // 永恩（二星）
    Champion4, u8"永恩", "../Resources/Champions/Champion4.png", 3, 2, 990, 0, 68, 200, 1, 1.0f, 1.0f, 1.2f, Brotherhood
};
const ChampionAttributes CHAMPION_5_ATTR = { // 奥拉夫（一星）
    Champion5, u8"奥拉夫", "../Resources/Champions/Champion5.png", 1, 1, 700, 0, 55, 200, 1, 0.6f, 1.0f, 1.4f, Lout
};
const ChampionAttributes CHAMPION_6_ATTR = { // 奥拉夫（二星）
    Champion6, u8"奥拉夫", "../Resources/Champions/Champion6.png", 3, 2, 1260, 0, 83, 200, 1, 0.6f, 1.0f, 1.4f, Lout
};
const ChampionAttributes CHAMPION_7_ATTR = { // 潘森（一星）
    Champion7, u8"潘森", "../Resources/Champions/Champion7.png", 1, 1, 700, 0, 70, 200, 1, 0.5f, 1.0f, 1.2f, Lout
};
const ChampionAttributes CHAMPION_8_ATTR = { // 潘森（二星）
    Champion8, u8"潘森", "../Resources/Champions/Champion8.png", 3, 2, 1260, 0, 105, 200, 1, 0.5f, 1.0f, 1.2f, Lout
};
const ChampionAttributes CHAMPION_9_ATTR = { // 伊芙琳（一星）
    Champion9, u8"伊芙琳", "../Resources/Champions/Champion9.png", 1, 1, 650, 0, 55, 200, 1, 0.55f, 1.0f, 1.3f, DarkSide
};
const ChampionAttributes CHAMPION_10_ATTR = { // 伊芙琳（二星）
    Champion10, u8"伊芙琳", "../Resources/Champions/Champion10.png", 3, 2, 1170, 0, 83, 200, 1, 0.55f, 1.0f, 1.3f, DarkSide
};
const ChampionAttributes CHAMPION_11_ATTR = { // 库奇（一星）
    Champion11, u8"库奇", "../Resources/Champions/Champion11.png", 2, 1, 500, 0, 50, 200, 3, 0.7f, 1.0f, 1.0f, GoodShooter
};
const ChampionAttributes CHAMPION_12_ATTR = { // 库奇（二星）
    Champion12, u8"库奇", "../Resources/Champions/Champion12.png", 6, 2, 900, 0, 75, 200, 3, 0.7f, 1.0f, 1.0f, GoodShooter
};
const ChampionAttributes CHAMPION_13_ATTR = { // 塔里克（一星）
    Champion13, u8"塔里克", "../Resources/Champions/Champion13.png", 2, 1, 750, 0, 60, 200, 1, 0.65f, 1.0f, 1.5f, NoBond
};
const ChampionAttributes CHAMPION_14_ATTR = { // 塔里克（二星）
    Champion14, u8"塔里克", "../Resources/Champions/Champion14.png", 6, 2, 1350, 0, 90, 200, 1, 0.65f, 1.0f, 1.5f, NoBond
};
const ChampionAttributes CHAMPION_15_ATTR = { // 亚索（一星）
    Champion15, u8"亚索", "../Resources/Champions/Champion15.png", 2, 1, 700, 0, 50, 200, 1, 0.75f, 1.0f, 1.1f, Brotherhood
};
const ChampionAttributes CHAMPION_16_ATTR = { // 亚索（二星）
    Champion16, u8"亚索", "../Resources/Champions/Champion16.png", 6, 2, 1260, 0, 75, 200, 1, 0.75f, 1.0f, 1.1f, Brotherhood
};
const ChampionAttributes CHAMPION_17_ATTR = { // 金克丝（一星）
    Champion17, u8"金克丝", "../Resources/Champions/Champion17.png", 2, 1, 600, 0, 65, 200, 5, 0.8f, 1.0f, 0.9f, GoodShooter
};
const ChampionAttributes CHAMPION_18_ATTR = { // 金克丝（二星）
    Champion18, u8"金克丝", "../Resources/Champions/Champion18.png", 6, 2, 1080, 0, 98, 200, 5, 0.8f, 1.0f, 0.9f, GoodShooter
};
const ChampionAttributes CHAMPION_19_ATTR = { // 塔姆（一星）
    Champion19, u8"塔姆", "../Resources/Champions/Champion19.png", 3, 1, 700, 0, 55, 200, 1, 0.6f, 1.0f, 1.6f, NoBond
};
const ChampionAttributes CHAMPION_20_ATTR = { // 塔姆（二星）
    Champion20, u8"塔姆", "../Resources/Champions/Champion20.png", 9, 2, 1260, 0, 83, 200, 1, 0.6f, 1.0f, 1.6f, NoBond
};
const ChampionAttributes CHAMPION_21_ATTR = { // 蔚（一星）
    Champion21, u8"蔚", "../Resources/Champions/Champion21.png", 3, 1, 800, 0, 60, 200, 1, 0.65f, 1.0f, 1.55f, NoBond
};
const ChampionAttributes CHAMPION_22_ATTR = { // 蔚（二星）
    Champion22, u8"蔚", "../Resources/Champions/Champion22.png", 9, 2, 1440, 0, 90, 200, 1, 0.65f, 1.0f, 1.55f, NoBond
};
const ChampionAttributes CHAMPION_23_ATTR = { // 阿木木（一星）
    Champion23, u8"阿木木", "../Resources/Champions/Champion23.png", 3, 1, 800, 0, 60, 200, 1, 0.7f, 1.0f, 1.5f, DarkSide
};
const ChampionAttributes CHAMPION_24_ATTR = { // 阿木木（二星）
    Champion24, u8"阿木木", "../Resources/Champions/Champion24.png", 9, 2, 1440, 0, 90, 200, 1, 0.7f, 1.0f, 1.5f, DarkSide
};
const ChampionAttributes CHAMPION_25_ATTR = { // 奎桑提（一星）
    Champion25, u8"奎桑提", "../Resources/Champions/Champion25.png", 4, 1, 950, 0, 80, 200, 1, 0.85f, 1.0f, 1.5f, NoBond
};
const ChampionAttributes CHAMPION_26_ATTR = { // 奎桑提（二星）
    Champion26, u8"奎桑提", "../Resources/Champions/Champion26.png", 12, 2, 1710, 0, 120, 200, 1, 0.85f, 1.0f, 1.5f, NoBond
};
const ChampionAttributes CHAMPION_27_ATTR = { // 卡尔萨斯（一星）
    Champion27, u8"卡尔萨斯", "../Resources/Champions/Champion27.png", 4, 1, 600, 0, 100, 200, 5, 0.85f, 1.0f, 0.9f, DarkSide
};
const ChampionAttributes CHAMPION_28_ATTR = { // 卡尔萨斯（二星）
    Champion28, u8"卡尔萨斯", "../Resources/Champions/Champion28.png", 12, 2, 1080, 0, 140, 200, 5, 0.9f, 1.0f, 0.9f, DarkSide
};
const ChampionAttributes CHAMPION_29_ATTR = { // 卡莎（一星）
    Champion29, u8"卡莎", "../Resources/Champions/Champion29.png", 5, 1, 800, 0, 100, 200, 5, 0.9f, 1.0f, 0.9f, PopStar
};
const ChampionAttributes CHAMPION_30_ATTR = { // 卡莎（二星）
    Champion30, u8"卡莎", "../Resources/Champions/Champion30.png", 15, 2, 1440, 0, 140, 200, 5, 0.9f, 1.0f, 0.9f, PopStar
};

// 战斗英雄价格分类定义
constexpr ChampionCategory FIRST_LEVEL[] = { // 战斗英雄一级价格分类
    NoChampion, // 无战斗英雄
    Champion1,  // 劫（一星）
    Champion3,  // 永恩（一星）
    Champion5,  // 奥拉夫（一星）
    Champion7,  // 潘森（一星）
    Champion9   // 伊芙琳（一星）
};
constexpr ChampionCategory SECOND_LEVEL[] = { // 战斗英雄二级价格分类
    NoChampion, // 无战斗英雄
    Champion11, // 库奇（一星）
    Champion13, // 塔里克（一星）
    Champion15, // 亚索（一星）
    Champion17  // 金克丝（一星）
};
constexpr ChampionCategory THIRD_LEVEL[] = { // 战斗英雄三级价格分类
    NoChampion, // 无战斗英雄
    Champion19, // 塔姆（一星）
    Champion21, // 蔚（一星）
    Champion23  // 阿木木（一星）
};
constexpr ChampionCategory FOURTH_LEVEL[] = { // 战斗英雄四级价格分类
    NoChampion, // 无战斗英雄
    Champion25, // 奎桑提（一星）
    Champion27  // 卡尔萨斯（一星）
};
constexpr ChampionCategory FIFTH_LEVEL[] = { // 战斗英雄五级价格分类
    NoChampion, // 无战斗英雄
    Champion29  // 卡莎（一星）
};

// 战斗英雄种类与属性键值对
const std::map<ChampionCategory, ChampionAttributes> CHAMPION_ATTR_MAP = {
    {Champion1, CHAMPION_1_ATTR},   // 劫（一星）
    {Champion2, CHAMPION_2_ATTR},   // 劫（二星）
    {Champion3, CHAMPION_3_ATTR},   // 永恩（一星）
    {Champion4, CHAMPION_4_ATTR},   // 永恩（二星）
    {Champion5, CHAMPION_5_ATTR},   // 奥拉夫（一星）
    {Champion6, CHAMPION_6_ATTR},   // 奥拉夫（二星）
    {Champion7, CHAMPION_7_ATTR},   // 潘森（一星）
    {Champion8, CHAMPION_8_ATTR},   // 潘森（二星）
    {Champion9, CHAMPION_9_ATTR},   // 伊芙琳（一星）
    {Champion10, CHAMPION_10_ATTR}, // 伊芙琳（二星）
    {Champion11, CHAMPION_11_ATTR}, // 库奇（一星）
    {Champion12, CHAMPION_12_ATTR}, // 库奇（二星）
    {Champion13, CHAMPION_13_ATTR}, // 塔里克（一星）
    {Champion14, CHAMPION_14_ATTR}, // 塔里克（二星）
    {Champion15, CHAMPION_15_ATTR}, // 亚索（一星）
    {Champion16, CHAMPION_16_ATTR}, // 亚索（二星）
    {Champion17, CHAMPION_17_ATTR}, // 金克丝（一星）
    {Champion18, CHAMPION_18_ATTR}, // 金克丝（二星）
    {Champion19, CHAMPION_19_ATTR}, // 塔姆（一星）
    {Champion20, CHAMPION_20_ATTR}, // 塔姆（二星）
    {Champion21, CHAMPION_21_ATTR}, // 蔚（一星）
    {Champion22, CHAMPION_22_ATTR}, // 蔚（二星）
    {Champion23, CHAMPION_23_ATTR}, // 阿木木（一星）
    {Champion24, CHAMPION_24_ATTR}, // 阿木木（二星）
    {Champion25, CHAMPION_25_ATTR}, // 奎桑提（一星）
    {Champion26, CHAMPION_26_ATTR}, // 奎桑提（二星）
    {Champion27, CHAMPION_27_ATTR}, // 卡尔萨斯（一星）
    {Champion28, CHAMPION_28_ATTR}, // 卡尔萨斯（二星）
    {Champion29, CHAMPION_29_ATTR}, // 卡莎（一星）
    {Champion30, CHAMPION_30_ATTR}  // 卡莎（二星）
};

// 序号与欢迎提示语键值对
const std::map<int, std::string> WELCOME_PROMPT = {
    {0,  u8"，凌晨好！星星还在，你也在，游戏之旅等待着你."},
    {1,  u8"，凌晨好！夜晚的秘密正在游戏世界中展开."},
    {2,  u8"，凌晨好！在这安静时刻，我们一起探索梦幻之地."},
    {3,  u8"，凌晨好！游戏世界在星光下更加迷人."},
    {4,  u8"，凌晨好！新的一天即将开始，让我们一起迎接."},
    {5,  u8"，凌晨好！让游戏点亮你的日出时分."},
    {6,  u8"，早上好！新的一天，阳光正好，新的挑战在等待."},
    {7,  u8"，早上好！让游戏的色彩伴随你的清晨."},
    {8,  u8"，早上好！一起在游戏的海洋中航行吧."},
    {9,  u8"，上午好！无尽的奇遇在这光辉时刻等着你."},
    {10, u8"，上午好！这个时刻，每一步棋都定局胜负."},
    {11, u8"，上午好！在午餐前，让我们再赢得一场胜利."},
    {12, u8"，中午好！在休息时刻，放松并享受游戏的乐趣."},
    {13, u8"，中午好！伴随午餐的时光，探索游戏的奇妙世界."},
    {14, u8"，下午好！阳光下，让我们共同探索未知."},
    {15, u8"，下午好！这是完美的时间，去体验新的游戏世界."},
    {16, u8"，下午好！在日落前，让我们获得荣耀."},
    {17, u8"，下午好！享受游戏，在这最美的时光."},
    {18, u8"，晚上好！让游戏陪伴你的黄昏时分."},
    {19, u8"，晚上好！在星光下揭开新的游戏篇章."},
    {20, u8"，晚上好！让魔法点亮你的游戏世界."},
    {21, u8"，晚上好！在这宁静的夜晚，战斗到底."},
    {22, u8"，晚上好！在这神秘的时刻，征服游戏世界."},
    {23, u8"，晚上好！夜深了，伴随月光，开始你的游戏之旅."},
    {24, u8"，让智慧的火花在自走棋的世界中闪耀."},
    {25, u8"，欢迎回来！奇幻冒险无时不在."},
    {26, u8"，游戏世界欢迎你，梦想起航."},
    {27, u8"，英雄，准备好你的棋子，赢取今日的胜利!"},
    {28, u8"，与星辰同行，探索无限可能."},
    {29, u8"，战斗未停，传奇由你续写."},
    {30, u8"，自走棋的世界里，每一场战斗都充满惊喜."},
    {31, u8"，英雄归来，冒险再启航."},
    {32, u8"，游戏里的每一天，都是新的故事."},
    {33, u8"，魔法世界等你探索，奇迹即将发生."},
    {34, u8"，梦与现实交汇，游戏世界的故事开始."},
    {35, u8"，冒险无界限，每一次登录都是新开始."},
    {36, u8"，勇敢的探险者，新的奇迹等你发现."},
    {37, u8"，每一次游戏，都是对未知的征服."},
    {38, u8"，超越极限，让每一次尝试都闪耀."},
    {39, u8"，握紧剑柄，冒险的路上你不孤单."},
    {40, u8"，在星辉下，续写你的英雄传说."},
    {41, u8"，勇闯天涯，每一个世界都有你的传说."},
    {42, u8"，拯救世界任务暂停，今天只做快乐的事情."},
    {43, u8"，穿上虚拟披风，今天你是超级英雄."},
    {44, u8"，调皮的精灵已经偷走了游戏秘密，追!"},
    {45, u8"，准备好了吗？棋盘上的英雄们正等着你的召唤."},
    {46, u8"，在自走棋的战场上，每一步都是策略的考验."},
    {47, u8"，策略大师，今日你将如何颠覆棋局?"}
};

#endif // !_CONSTANT_H_