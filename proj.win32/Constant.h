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
constexpr int HOSTNAME_LENGHT = 128;                                 // ����������
constexpr int MIN_PORT_ADDRESS = 49152;                              // ��С�˿ڵ�ַ
constexpr int MAX_PORT_ADDRESS = 65535;                              // ���˿ڵ�ַ
constexpr int MAX_CONNECTIONS = 8;                                   // �����������
constexpr int BUFFER_SIZE = 1024;                                    // ��������С
constexpr char CONNECTION_REFUSED_MSG[] = "Connection refused.";     // �ܾ�������ʾ��Ϣ
constexpr char CONNECTION_ACCEPTED_MSG[] = "Connection accepted.";   // ����������ʾ��Ϣ

// ��ɫ����
constexpr int DARK_BLUE_R = 0;                                       // ����ɫ R ͨ��
constexpr int DARK_BLUE_G = 32;                                      // ����ɫ G ͨ��
constexpr int DARK_BLUE_B = 96;                                      // ����ɫ B ͨ��

// �ܳ�����������
constexpr int NICKNAME_MAX_LENGTH = 6;                               // ��Ϸ�ǳ���󳤶�
constexpr float PROMPT_MESSAGE_DURATION = 1.5f;                      // ��ʾ��Ϣͣ��ʱ��
constexpr float SCENE_TRANSITION_DURATION = 0.3f;                    // �����л�ʱ��

// ����������������
constexpr int STARTUP_SCENE_FONT_SIZE = 20;                          // �������������С
constexpr int STARTUP_SCENE_LOADINGBAR_OFFSET_Y = -241;              // �����������ؽ�����λ�� Y ƫ����
constexpr int STARTUP_SCENE_LOADING_LABEL_OFFSET_X = -30;            // �����������ؽ�������ǩλ�� X ƫ����
constexpr float STARTUP_SCENE_DURATION = 2.0f;                       // ������������ʱ��

// ��ʼ������������
constexpr int INITIAL_SCENE_FONT_SIZE = 30;                          // ��ʼ���������С
constexpr int INITIAL_SCENE_LABELS_OFFSET_X = 349;                   // ��ʼ������ǩλ�� X ƫ����
constexpr int INITIAL_SCENE_TEXTFIELD_OFFSET_Y = 111;                // ��ʼ�����ı���λ�� Y ƫ����
constexpr int INITIAL_SCENE_PROMPT_LABEL_OFFSET_Y = 180;             // ��ʼ������ʾ��ǩλ�� Y ƫ����
constexpr int INITIAL_SCENE_NAME_LABEL_OFFSET_Y = 280;               // ��ʼ������ӭ��ǩλ�� Y ƫ����
constexpr int INITIAL_SCENE_BUTTON_OFFSET_Y = -310;                  // ��ʼ������ťλ�� Y ƫ����

// �˵�������������
constexpr int MENU_SCENE_FONT_SIZE = 24;                             // �˵����������С
constexpr int MENU_SCENE_BUTTONS_OFFSET_X = -296;                    // �˵�������ť���ǩλ�� X ƫ����
constexpr int MENU_SCENE_OFFLINE_MODE_BUTTON_OFFSET_Y = -30;         // �˵�������ϰģʽ��ťλ�� Y ƫ����
constexpr int MENU_SCENE_ONLINE_MODE_BUTTON_OFFSET_Y = -150;         // �˵���������ģʽ��ťλ�� Y ƫ����
constexpr int MENU_SCENE_SETTINGS_BUTTON_OFFSET_Y = -270;            // �˵��������ð�ťλ�� Y ƫ����
constexpr int MENU_SCENE_WELCOME_LABEL_OFFSET_Y = 240;               // �˵�������ӭ��ǩλ�� Y ƫ����

// ��ս������������
constexpr int WAITING_MAP_COUNT = 9;                                 // ��ս����ͼ��С
constexpr int BATTLE_MAP_ROWS = 8;                                   // ս������ͼ����
constexpr int BATTLE_MAP_COLUMNS = 9;                                // ս������ͼ����
constexpr int PLACE_MAP_ROWS = BATTLE_MAP_ROWS / 2;                  // ��������ͼ����
constexpr int BATTLE_AREA_MIN_CHAMPION_COUNT = 3;                    // ��͵ȼ�ս�������Ӣ������
constexpr int BATTLE_AREA_MAX_CHAMPION_COUNT = 8;                    // ��ߵȼ�ս�������Ӣ������
constexpr int BATTLE_SCENE_LOADINGBAR_X = 213;                       // ��ս����׼��������λ�� X ����
constexpr int BATTLE_SCENE_LOADINGBAR_Y = 675;                       // ��ս����׼��������λ�� Y ����
constexpr int BATTLE_SCENE_LOADINGBAR_LABEL_FONT_SIZE = 20;          // ��ս����׼����������ǩ�����С
constexpr int BATTLE_SCENE_LOADINGBAR_LABEL_OFFSET_X = -18;          // ��ս����׼����������ǩλ�� X ƫ����
constexpr int BATTLE_SCENE_LOADINGBAR_LABEL_THRESHOLD = 10;          // ��ս����׼��ʱ����ʾ��ֵ
constexpr float BATTLE_SCENE_LOADINGBAR_DURATION = 15.0f;            // ��ս����׼��ʱ��

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
constexpr int SHOP_LEVEL_LABEL_OFFSET_X = -411;                      // �̵�ȼ���ǩλ�� X ƫ����
constexpr int SHOP_LEVEL_LABEL_OFFSET_Y = -228;                      // �̵�ȼ���ǩλ�� Y ƫ����
constexpr int SHOP_LEVEL_LABEL_FONT_SIZE = 20;                       // �̵�ȼ���ǩ�����С

// λ����������Ļ��������
constexpr int WAITING_AREA_START_X = 415;                            // ��ս����ʼ��Ļ����λ�� X ����
constexpr int WAITING_AREA_START_Y = 195;                            // ��ս����ʼ��Ļ����λ�� Y ����
constexpr int BATTLE_AREA_START_X = 415;                             // ս������ʼ��Ļ����λ�� X ����
constexpr int BATTLE_AREA_START_Y = 275;                             // ս������ʼ��Ļ����λ�� Y ����
constexpr int CHAMPION_HORIZONTAL_INTERVAL = 60;                     // ս��Ӣ��ˮƽ���
constexpr int CHAMPION_VERTICAL_INTERVAL = 45;                       // ս��Ӣ�۴�ֱ���

// ��ϰģʽ�Ѷȶ���
enum Difficulty {
    Easy, // ��ģʽ
    Hard  // ����ģʽ
};

// ս��Ӣ�����ඨ��
enum ChampionCategory {
    NoChampion, // ��ս��Ӣ��
    Champion1,  // �٣�һ�ǣ�
    Champion2,  // �٣����ǣ�
    Champion3,  // ������һ�ǣ�
    Champion4,  // ���������ǣ�
    Champion5,  // ������һ�ǣ�
    Champion6,  // �����򣨶��ǣ�
    Champion7,  // ��ɭ��һ�ǣ�
    Champion8,  // ��ɭ�����ǣ�
    Champion9,  // ��ܽ�գ�һ�ǣ�
    Champion10, // ��ܽ�գ����ǣ�
    Champion11, // ���棨һ�ǣ�
    Champion12, // ���棨���ǣ�
    Champion13, // ����ˣ�һ�ǣ�
    Champion14, // ����ˣ����ǣ�
    Champion15, // ������һ�ǣ�
    Champion16, // ���������ǣ�
    Champion17, // ���˹��һ�ǣ�
    Champion18, // ���˹�����ǣ�
    Champion19, // ��ķ��һ�ǣ�
    Champion20, // ��ķ�����ǣ�
    Champion21, // ε��һ�ǣ�
    Champion22, // ε�����ǣ�
    Champion23, // ��ľľ��һ�ǣ�
    Champion24, // ��ľľ�����ǣ�
    Champion25, // ��ɣ�ᣨһ�ǣ�
    Champion26, // ��ɣ�ᣨ���ǣ�
    Champion27, // ������˹��һ�ǣ�
    Champion28, // ������˹�����ǣ�
    Champion29, // ��ɯ��һ�ǣ�
    Champion30  // ��ɯ�����ǣ�
};

// λ��״̬����
enum LocationStatus {
    WaitingArea, // ��ս��
    BattleArea   // ս����
};

// λ�����Զ���
struct Location {
    LocationStatus status;                        // λ��״̬
    int position;                                 // λ������
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
    int attackDamage;                  // �����˺�
    int skillTriggerThreshold;         // ���ܴ�����ֵ
    int attackRange;                   // ������Χ
    float attackSpeed;                 // �����ٶ�
    float movementSpeed;               // �ƶ��ٶ�
    float defenseCoefficient;          // ����ϵ��
} ChampionAttributes;

// ս��Ӣ�����Բ���
const ChampionAttributes CHAMPION_1_ATTR = { // �٣�һ�ǣ�
    Champion1, "�٣�һ�ǣ�", "../Resources/Champions/Champion1.png", 1, 1, 200, 30, 200, 1, 1.0f, 1.0f, 1.0f
};
const ChampionAttributes CHAMPION_2_ATTR = { // �٣����ǣ�
    Champion2, "�٣����ǣ�", "../Resources/Champions/Champion2.png", 1, 2, 250, 35, 200, 1, 0.9f, 1.2f, 1.1f
};
const ChampionAttributes CHAMPION_3_ATTR = { // ������һ�ǣ�
    Champion3, "������һ�ǣ�", "../Resources/Champions/Champion3.png", 1, 1, 200, 25, 50, 1, 0.8f, 1.0f, 1.0f
};
const ChampionAttributes CHAMPION_4_ATTR = { // ���������ǣ�
    Champion4, "���������ǣ�", "../Resources/Champions/Champion4.png", 1, 2, 250, 30, 50, 1, 0.7f, 1.2f, 1.1f
};
const ChampionAttributes CHAMPION_5_ATTR = { // ������һ�ǣ�
    Champion5, "������һ�ǣ�", "../Resources/Champions/Champion5.png", 1, 1, 250, 20, 120, 1, 0.8f, 1.2f, 0.8f
};
const ChampionAttributes CHAMPION_6_ATTR = { // �����򣨶��ǣ�
    Champion6, "�����򣨶��ǣ�", "../Resources/Champions/Champion6.png", 1, 2, 300, 25, 120, 1, 0.7f, 1.4f, 0.9f
}; // ���ܻ�Ѫ
const ChampionAttributes CHAMPION_7_ATTR = { // ��ɭ��һ�ǣ�
    Champion7, "��ɭ��һ�ǣ�", "../Resources/Champions/Champion7.png", 1, 1, 250, 20, 100, 1, 1.0f, 1.0f, 1.1f
};
const ChampionAttributes CHAMPION_8_ATTR = { // ��ɭ�����ǣ�
    Champion8, "��ɭ�����ǣ�", "../Resources/Champions/Champion8.png", 1, 2, 300, 25, 100, 1, 0.9f, 1.2f, 1.2f
};
const ChampionAttributes CHAMPION_9_ATTR = { // ��ܽ�գ�һ�ǣ�
    Champion9, "��ܽ�գ�һ�ǣ�", "../Resources/Champions/Champion9.png", 1, 1, 175, 15, 200, 1, 1.0f, 1.0f, 1.0f
};
const ChampionAttributes CHAMPION_10_ATTR = { // ��ܽ�գ����ǣ�
    Champion10, "��ܽ�գ����ǣ�", "../Resources/Champions/Champion10.png", 1, 2, 225, 20, 200, 1, 0.9f, 1.2f, 1.1f
};
const ChampionAttributes CHAMPION_11_ATTR = { // ���棨һ�ǣ�
    Champion11, "���棨һ�ǣ�", "../Resources/Champions/Champion11.png", 2, 1, 150, 23, 100, 3, 0.7f, 1.1f, 0.7f
};
const ChampionAttributes CHAMPION_12_ATTR = { // ���棨���ǣ�
    Champion12, "���棨���ǣ�", "../Resources/Champions/Champion12.png", 2, 2, 200, 28, 100, 3, 0.6f, 1.3f, 0.8f
};
const ChampionAttributes CHAMPION_13_ATTR = { // ����ˣ�һ�ǣ�
    Champion13, "����ˣ�һ�ǣ�", "../Resources/Champions/Champion13.png", 2, 1, 250, 20, 200, 1, 1.1f, 1.0f, 1.2f
}; // ����ѣ��
const ChampionAttributes CHAMPION_14_ATTR = { // ����ˣ����ǣ�
    Champion14, "����ˣ����ǣ�", "../Resources/Champions/Champion14.png", 2, 2, 300, 25, 200, 1, 1.0f, 1.2f, 1.3f
};
const ChampionAttributes CHAMPION_15_ATTR = { // ������һ�ǣ�
    Champion15, "������һ�ǣ�", "../Resources/Champions/Champion15.png", 2, 1, 200, 25, 50, 1, 0.7f, 1.0f, 1.0f
};
const ChampionAttributes CHAMPION_16_ATTR = { // ���������ǣ�
    Champion16, "���������ǣ�", "../Resources/Champions/Champion16.png", 2, 2, 250, 30, 50, 1, 0.6f, 1.2f, 1.1f
};
const ChampionAttributes CHAMPION_17_ATTR = { // ���˹��һ�ǣ�
    Champion17, "���˹��һ�ǣ�", "../Resources/Champions/Champion17.png", 2, 1, 150, 30, 200, 1, 0.5f, 1.5f, 0.7f
};
const ChampionAttributes CHAMPION_18_ATTR = { // ���˹�����ǣ�
    Champion18, "���˹�����ǣ�", "../Resources/Champions/Champion18.png", 2, 2, 200, 35, 200, 2, 0.4f, 1.7f, 0.8f
};
const ChampionAttributes CHAMPION_19_ATTR = { // ��ķ��һ�ǣ�
    Champion19, "��ķ��һ�ǣ�", "../Resources/Champions/Champion19.png", 3, 1, 300, 15, 150, 1, 1.0f, 1.0f, 1.2f
};
const ChampionAttributes CHAMPION_20_ATTR = { // ��ķ�����ǣ�
    Champion20, "��ķ�����ǣ�", "../Resources/Champions/Champion20.png", 3, 2, 350, 20, 150, 1, 0.9f, 1.2f, 1.3f
};
const ChampionAttributes CHAMPION_21_ATTR = { // ε��һ�ǣ�
    Champion21, "ε��һ�ǣ�", "../Resources/Champions/Champion21.png", 3, 1, 250, 30, 200, 1, 1.0f, 1.0f, 1.1f
};
const ChampionAttributes CHAMPION_22_ATTR = { // ε�����ǣ�
    Champion22, "ε�����ǣ�", "../Resources/Champions/Champion22.png", 3, 2, 300, 35, 200, 1, 0.9f, 1.2f, 1.2f
};
const ChampionAttributes CHAMPION_23_ATTR = { // ��ľľ��һ�ǣ�
    Champion23, "��ľľ��һ�ǣ�", "../Resources/Champions/Champion23.png", 3, 1, 300, 20, 200, 1, 1.0f, 1.0f, 1.3f
};
const ChampionAttributes CHAMPION_24_ATTR = { // ��ľľ�����ǣ�
    Champion24, "��ľľ�����ǣ�", "../Resources/Champions/Champion24.png", 3, 2, 350, 25, 200, 1, 0.9f, 1.2f, 1.4f
};
const ChampionAttributes CHAMPION_25_ATTR = { // ��ɣ�ᣨһ�ǣ�
    Champion25, "��ɣ�ᣨһ�ǣ�", "../Resources/Champions/Champion25.png", 4, 1, 300, 30, 50, 1, 0.7f, 1.0f, 1.1f
};
const ChampionAttributes CHAMPION_26_ATTR = { // ��ɣ�ᣨ���ǣ�
    Champion26, "��ɣ�ᣨ���ǣ�", "../Resources/Champions/Champion26.png", 4, 2, 350, 35, 50, 1, 0.6f, 1.2f, 1.2f
};
const ChampionAttributes CHAMPION_27_ATTR = { // ������˹��һ�ǣ�
    Champion27, "������˹��һ�ǣ�", "../Resources/Champions/Champion27.png", 4, 1, 200, 20, 200, 3, 1.0f, 0.8f, 1.0f
};
const ChampionAttributes CHAMPION_28_ATTR = { // ������˹�����ǣ�
    Champion28, "������˹�����ǣ�", "../Resources/Champions/Champion28.png", 4, 2, 250, 25, 200, 3, 0.9f, 1.0f, 1.1f
};
const ChampionAttributes CHAMPION_29_ATTR = { // ��ɯ��һ�ǣ�
    Champion29, "��ɯ��һ�ǣ�", "../Resources/Champions/Champion29.png", 5, 1, 200, 35, 200, 4, 0.7f, 1.0f, 1.0f
};
const ChampionAttributes CHAMPION_30_ATTR = { // ��ɯ�����ǣ�
    Champion30, "��ɯ�����ǣ�", "../Resources/Champions/Champion30.png", 5, 2, 250, 40, 200, 4, 0.6f, 1.2f, 1.1f
};

// ս��Ӣ�����������Լ�ֵ��
const std::map<ChampionCategory, ChampionAttributes> CHAMPION_ATTR_MAP = {
    {Champion1, CHAMPION_1_ATTR},   // �٣�һ�ǣ�
    {Champion2, CHAMPION_2_ATTR},   // �٣����ǣ�
    {Champion3, CHAMPION_3_ATTR},   // ������һ�ǣ�
    {Champion4, CHAMPION_4_ATTR},   // ���������ǣ�
    {Champion5, CHAMPION_5_ATTR},   // ������һ�ǣ�
    {Champion6, CHAMPION_6_ATTR},   // �����򣨶��ǣ�
    {Champion7, CHAMPION_7_ATTR},   // ��ɭ��һ�ǣ�
    {Champion8, CHAMPION_8_ATTR},   // ��ɭ�����ǣ�
    {Champion9, CHAMPION_9_ATTR},   // ��ܽ�գ�һ�ǣ�
    {Champion10, CHAMPION_10_ATTR}, // ��ܽ�գ����ǣ�
    {Champion11, CHAMPION_11_ATTR}, // ���棨һ�ǣ�
    {Champion12, CHAMPION_12_ATTR}, // ���棨���ǣ�
    {Champion13, CHAMPION_13_ATTR}, // ����ˣ�һ�ǣ�
    {Champion14, CHAMPION_14_ATTR}, // ����ˣ����ǣ�
    {Champion15, CHAMPION_15_ATTR}, // ������һ�ǣ�
    {Champion16, CHAMPION_16_ATTR}, // ���������ǣ�
    {Champion17, CHAMPION_17_ATTR}, // ���˹��һ�ǣ�
    {Champion18, CHAMPION_18_ATTR}, // ���˹�����ǣ�
    {Champion19, CHAMPION_19_ATTR}, // ��ķ��һ�ǣ�
    {Champion20, CHAMPION_20_ATTR}, // ��ķ�����ǣ�
    {Champion21, CHAMPION_21_ATTR}, // ε��һ�ǣ�
    {Champion22, CHAMPION_22_ATTR}, // ε�����ǣ�
    {Champion23, CHAMPION_23_ATTR}, // ��ľľ��һ�ǣ�
    {Champion24, CHAMPION_24_ATTR}, // ��ľľ�����ǣ�
    {Champion25, CHAMPION_25_ATTR}, // ��ɣ�ᣨһ�ǣ�
    {Champion26, CHAMPION_26_ATTR}, // ��ɣ�ᣨ���ǣ�
    {Champion27, CHAMPION_27_ATTR}, // ������˹��һ�ǣ�
    {Champion28, CHAMPION_28_ATTR}, // ������˹�����ǣ�
    {Champion29, CHAMPION_29_ATTR}, // ��ɯ��һ�ǣ�
    {Champion30, CHAMPION_30_ATTR}  // ��ɯ�����ǣ�
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