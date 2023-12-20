/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Constant.h
 * File Function: �������Ķ���
 * Author:        �ּ��ꡢ�����ǡ�������������
 * Update Date:   2023/12/20
 ****************************************************************/

#pragma once
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#include <map>
#include <string>

// Ӧ�ó�������
constexpr int DESIGN_RESOLUTION_WIDTH = 1280;                        // ��Ʒֱ��ʿ��
constexpr int DESIGN_RESOLUTION_HEIGHT = 720;                        // ��Ʒֱ��ʸ߶�
constexpr int SMALL_RESOLUTION_WIDTH = 960;                          // С�ֱ��ʿ��
constexpr int SMALL_RESOLUTION_HEIGHT = 540;                         // С�ֱ��ʸ߶�
constexpr int MEDIUM_RESOLUTION_WIDTH = 1280;                        // �зֱ��ʿ��
constexpr int MEDIUM_RESOLUTION_HEIGHT = 720;                        // �зֱ��ʸ߶�
constexpr int LARGE_RESOLUTION_WIDTH = 1920;                         // ��ֱ��ʿ��
constexpr int LARGE_RESOLUTION_HEIGHT = 1080;                        // ��ֱ��ʸ߶�
constexpr float FRAME_RATE = 60.0f;                                  // Ӧ�ó���֡��
const std::string APPLICATION_TITLE = "�����֮ս Teamfight Tactics"; // Ӧ�ó������

// ���绷������
constexpr int HOSTNAME_LENGHT = 128;                               // ����������
constexpr int MIN_PORT_ADDRESS = 49152;                            // ��С�˿ڵ�ַ
constexpr int MAX_PORT_ADDRESS = 65535;                            // ���˿ڵ�ַ
constexpr int MAX_CONNECTIONS = 8;                                 // �����������
constexpr int BUFFER_SIZE = 1024;                                  // ��������С
constexpr char CONNECTION_REFUSED_MSG[] = "Connection refused.";   // �ܾ�������ʾ��Ϣ
constexpr char CONNECTION_ACCEPTED_MSG[] = "Connection accepted."; // ����������ʾ��Ϣ

// ��ɫ����
constexpr int DARK_BLUE_R = 0;  // ����ɫ R ͨ��
constexpr int DARK_BLUE_G = 32; // ����ɫ G ͨ��
constexpr int DARK_BLUE_B = 96; // ����ɫ B ͨ��

// �ܳ�����������
constexpr int NICKNAME_MAX_LENGTH = 6;            // ��Ϸ�ǳ���󳤶�
constexpr float PROMPT_MESSAGE_DURATION = 1.5f;   // ��ʾ��Ϣͣ��ʱ��
constexpr float SCENE_TRANSITION_DURATION = 0.3f; // �����л�ʱ��

// ����������������
constexpr int STARTUP_SCENE_FONT_SIZE = 20;               // �������������С
constexpr int STARTUP_SCENE_LOADINGBAR_OFFSET_Y = -241;   // �����������ؽ�����λ�� Y ƫ����
constexpr int STARTUP_SCENE_LOADING_LABLE_OFFSET_X = -30; // �����������ؽ�������ǩλ�� X ƫ����
constexpr float STARTUP_SCENE_DURATION = 2.0f;            // ������������ʱ��

// ��ʼ������������
constexpr int INITIAL_SCENE_FONT_SIZE = 30;              // ��ʼ���������С
constexpr int INITIAL_SCENE_LABLES_OFFSET_X = 349;       // ��ʼ������ǩλ�� X ƫ����
constexpr int INITIAL_SCENE_TEXTFIELD_OFFSET_Y = 111;    // ��ʼ�����ı���λ�� Y ƫ����
constexpr int INITIAL_SCENE_PROMPT_LABLE_OFFSET_Y = 180; // ��ʼ������ʾ��ǩλ�� Y ƫ����
constexpr int INITIAL_SCENE_NAME_LABLE_OFFSET_Y = 280;   // ��ʼ������ӭ��ǩλ�� Y ƫ����
constexpr int INITIAL_SCENE_BUTTON_OFFSET_Y = -310;      // ��ʼ������ťλ�� Y ƫ����

// �˵�������������
constexpr int MENU_SCENE_FONT_SIZE = 24;                     // �˵����������С
constexpr int MENU_SCENE_BUTTONS_OFFSET_X = -296;            // �˵�������ť���ǩλ�� X ƫ����
constexpr int MENU_SCENE_OFFLINE_MODE_BUTTON_OFFSET_Y = -30; // �˵�������ϰģʽ��ťλ�� Y ƫ����
constexpr int MENU_SCENE_ONLINE_MODE_BUTTON_OFFSET_Y = -150; // �˵���������ģʽ��ťλ�� Y ƫ����
constexpr int MENU_SCENE_SETTINGS_BUTTON_OFFSET_Y = -270;    // �˵��������ð�ťλ�� Y ƫ����
constexpr int MENU_SCENE_WELCOME_LABLE_OFFSET_Y = 240;       // �˵�������ӭ��ǩλ�� Y ƫ����

// ��ս������������
constexpr int WAITING_MAP_COUNT = 9;                        // ��ս����ͼ��С
constexpr int BATTLE_MAP_ROWS = 8;                          // ս������ͼ����
constexpr int BATTLE_MAP_COLUMNS = 9;                       // ս������ͼ����
constexpr int PLACE_MAP_ROWS = BATTLE_MAP_ROWS / 2;         // ��������ͼ����
constexpr int BATTLE_SCENE_LOADINGBAR_X = 213;              // ��ս����׼��������λ�� X ����
constexpr int BATTLE_SCENE_LOADINGBAR_Y = 675;              // ��ս����׼��������λ�� Y ����
constexpr int BATTLE_SCENE_LOADINGBAR_LABLE_FONT_SIZE = 20; // ��ս����׼����������ǩ�����С
constexpr int BATTLE_SCENE_LOADINGBAR_LABLE_OFFSET_X = -18; // ��ս����׼����������ǩλ�� X ƫ����
constexpr int BATTLE_SCENE_LOADINGBAR_LABLE_THRESHOLD = 10; // ��ս����׼��ʱ����ʾ��ֵ
constexpr float BATTLE_SCENE_LOADINGBAR_DURATION = 15.0f;   // ��ս����׼��ʱ��

// �̵��������
constexpr int MAX_SELECTABLE_CHAMPION_COUNT = 5;                     // ����ѡ��ս��Ӣ������
constexpr int SHOP_CHAMPION_INTERVAL = 10;                           // �̵�ս��Ӣ�۰�ť���
constexpr int SHOP_CHAMPION_WIDTH = 120;                             // �̵�ս��Ӣ�۰�ť���
constexpr int SHOP_CHAMPION_HEIGHT = 100;                            // �̵�ս��Ӣ�۰�ť�߶�
constexpr int SHOP_CHAMPION_START_X = 370 + SHOP_CHAMPION_WIDTH / 2; // �̵�ս��Ӣ����ʼ��ťλ�� X ����
constexpr int SHOP_CHAMPION_START_Y = 10 + SHOP_CHAMPION_HEIGHT / 2; // �̵�ս��Ӣ����ʼ��ťλ�� Y ����
constexpr int SHOP_UPLEVEL_BUTTON_OFFSET_X = -340;                   // �̵�������ťλ�� X ƫ����
constexpr int SHOP_UPLEVEL_BUTTON_OFFSET_Y = -273;                   // �̵�������ťλ�� Y ƫ����
constexpr int SHOP_REFRESH_BUTTON_OFFSET_X = -340;                   // �̵�ˢ�°�ťλ�� X ƫ����
constexpr int SHOP_REFRESH_BUTTON_OFFSET_Y = -328;                   // �̵�ˢ�°�ťλ�� Y ƫ����

// λ����������Ļ��������
constexpr int WAITING_AREA_START_X = 415;        // ��ս����ʼ��Ļ����λ�� X ����
constexpr int WAITING_AREA_START_Y = 195;        // ��ս����ʼ��Ļ����λ�� Y ����
constexpr int BATTLE_AREA_START_X = 415;         // ս������ʼ��Ļ����λ�� X ����
constexpr int BATTLE_AREA_START_Y = 275;         // ս������ʼ��Ļ����λ�� Y ����
constexpr int CHAMPION_HORIZONTAL_INTERVAL = 60; // ս��Ӣ��ˮƽ���
constexpr int CHAMPION_VERTICAL_INTERVAL = 45;   // ս��Ӣ�۴�ֱ���

// ��ϰģʽ�Ѷȶ���
enum Difficulty {
    Easy, // ��ģʽ
    Hard  // ����ģʽ
};

// ս��Ӣ�����ඨ��
enum ChampionCategory {
    NoChampion, // ��ս��Ӣ��
    Champion1,  // Champion1
    Champion2,  // Champion2
    Champion3,  // Champion3
    Champion4,  // Champion4
    Champion5,  // Champion5
    Champion6,  // Champion6
    Champion7,  // Champion7
    Champion8,  // Champion8
    Champion9,  // Champion9
    Champion10, // Champion10
    Champion11, // Champion11
    Champion12, // Champion12
    Champion13, // Champion13
    Champion14, // Champion14
    Champion15, // Champion15
    Champion16, // Champion16
    Champion17, // Champion17
    Champion18, // Champion18
    Champion19, // Champion19
    Champion20, // Champion20
    Champion21, // Champion21
    Champion22, // Champion22
    Champion23, // Champion23
    Champion24, // Champion24
    Champion25, // Champion25
    Champion26, // Champion26
    Champion27, // Champion27
    Champion28, // Champion28
    Champion29, // Champion29
    Champion30  // Champion30
};

// λ��״̬����
enum LocationStatus {
    WaitingArea, // ��ս��
    BattleArea   // ս����
};

// λ�����Զ���
struct Location {
    LocationStatus status; // λ��״̬
    int position;          // λ������
    bool operator<(const Location& other) const { // ��������� < ���� std::map
        if (status < other.status) return true;
        if (status > other.status) return false;
        return position < other.position;
    }
};

// ս��Ӣ�����Զ���
typedef struct {
    ChampionCategory championCategory; // ս��Ӣ������
    std::string championName;          // ս��Ӣ������
    std::string championImagePath;     // ս��Ӣ��ͼƬ·��
    int price;                         // ս��Ӣ�ۼ۸�
    int level;                         // ս��Ӣ�۵ȼ�
    int healthPoints;                  // ����ֵ
    int experiencePoints;              // ����ֵ
    int attackDamage;                  // �����˺�
    int skillDamage;                   // �����˺�
    int skillTriggerThreshold;         // ���ܴ�����ֵ
    int attackRange;                   // ������Χ
    float attackSpeed;                 // �����ٶ�
    float movementSpeed;               // �ƶ��ٶ�
    float defenseCoefficient;          // ����ϵ��
} ChampionAttributes;

// ս��Ӣ�����Բ���
const ChampionAttributes CHAMPION_01_ATTR = { // Champion1
    Champion1, "ս��Ӣ��1", "../Resources/Champions/Champion1.png", 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_02_ATTR = { // Champion2
    Champion2, "ս��Ӣ��1", "../Resources/Champions/Champion2.png", 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_03_ATTR = { // Champion3
    Champion3, "ս��Ӣ��1", "../Resources/Champions/Champion3.png", 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_04_ATTR = { // Champion4
    Champion4, "ս��Ӣ��2", "../Resources/Champions/Champion4.png", 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_05_ATTR = { // Champion5
    Champion5, "ս��Ӣ��2", "../Resources/Champions/Champion5.png", 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_06_ATTR = { // Champion6
    Champion6, "ս��Ӣ��2", "../Resources/Champions/Champion6.png", 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_07_ATTR = { // Champion7
    Champion7, "ս��Ӣ��G", "../Resources/Champions/Champion7.png", 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_08_ATTR = { // Champion8
    Champion8, "ս��Ӣ��H", "../Resources/Champions/Champion8.png", 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_09_ATTR = { // Champion9
    Champion9, "ս��Ӣ��I", "../Resources/Champions/Champion9.png", 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_10_ATTR = { // Champion10
    Champion10, "ս��Ӣ��J", "../Resources/Champions/Champion10.png", 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_11_ATTR = { // Champion11
    Champion11, "ս��Ӣ��K", "../Resources/Champions/Champion11.png", 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_12_ATTR = { // Champion12
    Champion12, "ս��Ӣ��L", "../Resources/Champions/Champion12.png", 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_13_ATTR = { // Champion13
    Champion13, "ս��Ӣ��M", "../Resources/Champions/Champion13.png", 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_14_ATTR = { // Champion14
    Champion14, "ս��Ӣ��N", "../Resources/Champions/Champion14.png", 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_15_ATTR = { // Champion15
    Champion15, "ս��Ӣ��E", "../Resources/Champions/Champion15.png", 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_16_ATTR = { // Champion16
    Champion16, "ս��Ӣ��1", "../Resources/Champions/Champion16.png", 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_17_ATTR = { // Champion17
    Champion17, "ս��Ӣ��1", "../Resources/Champions/Champion17.png", 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_18_ATTR = { // Champion18
    Champion18, "ս��Ӣ��1", "../Resources/Champions/Champion18.png", 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_19_ATTR = { // Champion19
    Champion19, "ս��Ӣ��2", "../Resources/Champions/Champion19.png", 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_20_ATTR = { // Champion20
    Champion20, "ս��Ӣ��2", "../Resources/Champions/Champion20.png", 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_21_ATTR = { // Champion21
    Champion21, "ս��Ӣ��2", "../Resources/Champions/Champion21.png", 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_22_ATTR = { // Champion22
    Champion22, "ս��Ӣ��G", "../Resources/Champions/Champion22.png", 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_23_ATTR = { // Champion23
    Champion23, "ս��Ӣ��H", "../Resources/Champions/Champion23.png", 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_24_ATTR = { // Champion24
    Champion24, "ս��Ӣ��J", "../Resources/Champions/Champion24.png", 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_25_ATTR = { // Champion25
    Champion25, "ս��Ӣ��K", "../Resources/Champions/Champion25.png", 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_26_ATTR = { // Champion26
    Champion26, "ս��Ӣ��L", "../Resources/Champions/Champion26.png", 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_27_ATTR = { // Champion27
    Champion27, "ս��Ӣ��M", "../Resources/Champions/Champion27.png", 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_28_ATTR = { // Champion28
    Champion28, "ս��Ӣ��N", "../Resources/Champions/Champion28.png", 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_29_ATTR = { // Champion29
    Champion29, "ս��Ӣ��E", "../Resources/Champions/Champion29.png", 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_30_ATTR = { // Champion30
    Champion30, "ս��Ӣ��I", "../Resources/Champions/Champion30.png", 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};

// ս��Ӣ�����������Լ�ֵ��
const std::map<ChampionCategory, ChampionAttributes> CHAMPION_ATTR_MAP = {
    {Champion1, CHAMPION_01_ATTR},  // Champion1
    {Champion2, CHAMPION_02_ATTR},  // Champion2
    {Champion3, CHAMPION_03_ATTR},  // Champion3
    {Champion4, CHAMPION_04_ATTR},  // Champion4
    {Champion5, CHAMPION_05_ATTR},  // Champion5
    {Champion6, CHAMPION_06_ATTR},  // Champion6
    {Champion7, CHAMPION_07_ATTR},  // Champion7
    {Champion8, CHAMPION_08_ATTR},  // Champion8
    {Champion9, CHAMPION_09_ATTR},  // Champion9
    {Champion10, CHAMPION_10_ATTR}, // Champion10
    {Champion11, CHAMPION_11_ATTR}, // Champion11
    {Champion12, CHAMPION_12_ATTR}, // Champion12
    {Champion13, CHAMPION_13_ATTR}, // Champion13
    {Champion14, CHAMPION_14_ATTR}, // Champion14
    {Champion15, CHAMPION_15_ATTR}, // Champion15
    {Champion16, CHAMPION_16_ATTR}, // Champion16
    {Champion17, CHAMPION_17_ATTR}, // Champion17
    {Champion18, CHAMPION_18_ATTR}, // Champion18
    {Champion19, CHAMPION_19_ATTR}, // Champion19
    {Champion20, CHAMPION_20_ATTR}, // Champion20
    {Champion21, CHAMPION_21_ATTR}, // Champion21
    {Champion22, CHAMPION_22_ATTR}, // Champion22
    {Champion23, CHAMPION_23_ATTR}, // Champion23
    {Champion24, CHAMPION_24_ATTR}, // Champion24
    {Champion25, CHAMPION_25_ATTR}, // Champion25
    {Champion26, CHAMPION_26_ATTR}, // Champion26
    {Champion27, CHAMPION_27_ATTR}, // Champion27
    {Champion28, CHAMPION_28_ATTR}, // Champion28
    {Champion29, CHAMPION_29_ATTR}, // Champion29
    {Champion30, CHAMPION_30_ATTR}  // Champion30
};

// Сʱ���뻶ӭ��ʾ���ֵ��
const std::map<int, std::string> WELCOME_PROMPT = {
    {0,  "���賿�ã����ǻ��ڣ���Ҳ�ڣ���Ϸ֮�õȴ�����."},
    {1,  "���賿�ã�ҹ�������������Ϸ������չ��."},
    {2,  "���賿�ã����ⰲ��ʱ�̣�����һ��̽���λ�֮��."},
    {3,  "���賿�ã���Ϸ�������ǹ��¸�������."},
    {4,  "���賿�ã��µ�һ�켴����ʼ��������һ��ӭ��."},
    {5,  "���賿�ã�����Ϸ��������ճ�ʱ��."},
    {6,  "�����Ϻã��µ�һ�죬�������ã��µ���ս�ڵȴ�."},
    {7,  "�����Ϻã�����Ϸ��ɫ�ʰ�������峿."},
    {8,  "�����Ϻã�һ������Ϸ�ĺ����к��а�."},
    {9,  "������ã��޾�������������ʱ�̵�����."},
    {10, "������ã����ʱ�̣�ÿһ���嶼����ʤ��."},
    {11, "������ã������ǰ����������Ӯ��һ��ʤ��."},
    {12, "������ã�����Ϣʱ�̣����ɲ�������Ϸ����Ȥ."},
    {13, "������ã�������͵�ʱ�⣬̽����Ϸ����������."},
    {14, "������ã������£������ǹ�ͬ̽��δ֪."},
    {15, "������ã�����������ʱ�䣬ȥ�����µ���Ϸ����."},
    {16, "������ã�������ǰ�������ǻ����ҫ."},
    {17, "������ã�������Ϸ������������ʱ��."},
    {18, "�����Ϻã�����Ϸ�����Ļƻ�ʱ��."},
    {19, "�����Ϻã����ǹ��½ҿ��µ���Ϸƪ��."},
    {20, "�����Ϻã���ħ�����������Ϸ����."},
    {21, "�����Ϻã�����������ҹ��ս������."},
    {22, "�����Ϻã��������ص�ʱ�̣�������Ϸ����."},
    {23, "�����Ϻã�ҹ���ˣ������¹⣬��ʼ�����Ϸ֮��."}
};

#endif // !_CONSTANT_H_