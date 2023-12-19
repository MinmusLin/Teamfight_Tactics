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
constexpr int DESIGN_RESOLUTION_WIDTH = 1280;      // ��Ʒֱ��ʿ��
constexpr int DESIGN_RESOLUTION_HEIGHT = 720;      // ��Ʒֱ��ʸ߶�
constexpr int SMALL_RESOLUTION_WIDTH = 960;        // С�ֱ��ʿ��
constexpr int SMALL_RESOLUTION_HEIGHT = 540;       // С�ֱ��ʸ߶�
constexpr int MEDIUM_RESOLUTION_WIDTH = 1280;      // �зֱ��ʿ��
constexpr int MEDIUM_RESOLUTION_HEIGHT = 720;      // �зֱ��ʸ߶�
constexpr int LARGE_RESOLUTION_WIDTH = 1920;       // ��ֱ��ʿ��
constexpr int LARGE_RESOLUTION_HEIGHT = 1080;      // ��ֱ��ʸ߶�
constexpr float FRAME_RATE = 60.0f;                // Ӧ�ó���֡��
const std::string APPLICATION_TITLE = "�����֮ս"; // Ӧ�ó������

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
constexpr int STARTUP_SCENE_LOADINGBAR_OFFSET_Y = -241;   // ��������������λ�� Y ƫ����
constexpr int STARTUP_SCENE_LOADING_LABLE_OFFSET_X = -30; // �����������ȱ�ǩλ�� X ƫ����
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

// ��ս��������
constexpr int WAITING_MAP_COUNT = 9;                // ��ս����ͼ��С
constexpr int BATTLE_MAP_ROWS = 8;                  // ս������ͼ����
constexpr int BATTLE_MAP_COLUMNS = 9;               // ս������ͼ����
constexpr int PLACE_MAP_ROWS = BATTLE_MAP_ROWS / 2; // ��������ͼ����

// �̵��������
constexpr int MAX_SELECTABLE_CHAMPION_COUNT = 5;                     // ����ѡ��ս��Ӣ������
constexpr int SHOP_CHAMPION_INTERVAL = 10;                           // �̵�ս��Ӣ�۰�ť���
constexpr int SHOP_CHAMPION_WIDTH = 120;                             // �̵�ս��Ӣ�۰�ť���
constexpr int SHOP_CHAMPION_HEIGHT = 100;                            // �̵�ս��Ӣ�۰�ť�߶�
constexpr int SHOP_CHAMPION_START_X = 370 + SHOP_CHAMPION_WIDTH / 2; // �̵�ս��Ӣ����ʼ��ť X ����
constexpr int SHOP_CHAMPION_START_Y = 10 + SHOP_CHAMPION_HEIGHT / 2; // �̵�ս��Ӣ����ʼ��ť Y ����

// λ����������Ļ��������
constexpr int WAITING_AREA_START_X = 415;
constexpr int WAITING_AREA_START_Y = 195;
constexpr int BATTLE_AREA_START_X = 415;
constexpr int BATTLE_AREA_START_Y = 275;
constexpr int CHAMPION_HORIZONTAL_INTERVAL = 60;
constexpr int CHAMPION_VERTICAL_INTERVAL = 45;

// ��ϰģʽ�Ѷȶ���
enum Difficulty {
    Easy, // ��ģʽ
    Hard  // ����ģʽ
};

// ս��Ӣ�����ඨ��
enum ChampionCategory {
    NoChampion = 0, // ��ս��Ӣ��
    ChampionA,      // ChampionA
    ChampionB,      // ChampionB
    ChampionC,      // ChampionC
    ChampionD,      // ChampionD
    ChampionE       // ChampionE
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
const ChampionAttributes CHAMPION_A_ATTR = { // ChampionA
    ChampionA, "ս��Ӣ��A", "../Resources/Champions/ChampionA.png", 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_B_ATTR = { // ChampionB
    ChampionB, "ս��Ӣ��B", "../Resources/Champions/ChampionB.png", 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_C_ATTR = { // ChampionC
    ChampionC, "ս��Ӣ��C", "../Resources/Champions/ChampionC.png", 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_D_ATTR = { // ChampionD
    ChampionD, "ս��Ӣ��D", "../Resources/Champions/ChampionD.png", 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};
const ChampionAttributes CHAMPION_E_ATTR = { // ChampionE
    ChampionE, "ս��Ӣ��E", "../Resources/Champions/ChampionE.png", 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};

// ս��Ӣ�����������Լ�ֵ��
const std::map<ChampionCategory, ChampionAttributes> CHAMPION_ATTR_MAP = {
    {ChampionA, CHAMPION_A_ATTR}, // ChampionA
    {ChampionB, CHAMPION_B_ATTR}, // ChampionB
    {ChampionC, CHAMPION_C_ATTR}, // ChampionC
    {ChampionD, CHAMPION_D_ATTR}, // ChampionD
    {ChampionE, CHAMPION_E_ATTR}  // ChampionE
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