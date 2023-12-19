/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Constant.h
 * File Function: �������Ķ���
 * Author:        �ּ��ꡢ�����ǡ�������������
 * Update Date:   2023/12/19
 ****************************************************************/

#pragma once
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#include <map>
#include <string>

// Ӧ�ó�������
constexpr int DESIGN_RESOLUTION_WIDTH = 1280;            // ��Ʒֱ��ʿ��
constexpr int DESIGN_RESOLUTION_HEIGHT = 720;            // ��Ʒֱ��ʸ߶�
constexpr int SMALL_RESOLUTION_WIDTH = 960;              // С�ֱ��ʿ��
constexpr int SMALL_RESOLUTION_HEIGHT = 540;             // С�ֱ��ʸ߶�
constexpr int MEDIUM_RESOLUTION_WIDTH = 1280;            // �зֱ��ʿ��
constexpr int MEDIUM_RESOLUTION_HEIGHT = 720;            // �зֱ��ʸ߶�
constexpr int LARGE_RESOLUTION_WIDTH = 1920;             // ��ֱ��ʿ��
constexpr int LARGE_RESOLUTION_HEIGHT = 1080;            // ��ֱ��ʸ߶�
constexpr float FRAME_RATE = 60.0f;                      // ֡��
constexpr char APPLICATION_TITLE[] = "Teamfight Tactic"; // Ӧ�ó������

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

// ������������
constexpr int NICKNAME_MAX_LENGTH = 6;                       // ��Ϸ�ǳ���󳤶�
constexpr int INITIAL_SCENE_FONT_SIZE = 30;                  // ��ʼ���������С
constexpr int INITIAL_SCENE_TEXTFIELD_OFFSET_Y = 40;         // ��ʼ�����ı���λ�� Y ƫ����
constexpr int INITIAL_SCENE_PROMPT_LABLE_OFFSET_Y = 150;     // ��ʼ������ʾ��ǩλ�� Y ƫ����
constexpr int INITIAL_SCENE_NAME_LABLE_OFFSET_Y = 280;       // ��ʼ������ӭ��ǩλ�� Y ƫ����
constexpr int INITIAL_SCENE_BUTTON_OFFSET_Y = -160;          // ��ʼ������ťλ�� Y ƫ����
constexpr int MENU_SCENE_BUTTONS_OFFSET_X = -296;            // �˵�������ťλ�� X ƫ����
constexpr int MENU_SCENE_OFFLINE_MODE_BUTTON_OFFSET_Y = -30; // �˵�������ϰģʽ��ťλ�� Y ƫ����
constexpr int MENU_SCENE_ONLINE_MODE_BUTTON_OFFSET_Y = -150; // �˵���������ģʽ��ťλ�� Y ƫ����
constexpr int MENU_SCENE_SETTINGS_BUTTON_OFFSET_Y = -270;    // �˵��������ð�ťλ�� Y ƫ����
constexpr float SCENE_TRANSITION_DURATION = 0.3f;            // �����л�ʱ��
constexpr float PROMPT_MESSAGE_DURATION = 1.5f;              // ��ʾ��Ϣͣ��ʱ��

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

#endif // !_CONSTANT_H_