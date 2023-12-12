/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Constant.h
 * File Function: �������Ķ���
 * Author:        �ּ��ꡢ�����ǡ�������������
 * Update Date:   2023/12/12
 ****************************************************************/

#pragma once
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

/* �ּ���ά�������� */

// Ӧ�ó�������
constexpr int DESIGN_RESOLUTION_WIDTH = 1280;
constexpr int DESIGN_RESOLUTION_HEIGHT = 720;
constexpr int SMALL_RESOLUTION_WIDTH = 960;
constexpr int SMALL_RESOLUTION_HEIGHT = 540;
constexpr int MEDIUM_RESOLUTION_WIDTH = 1280;
constexpr int MEDIUM_RESOLUTION_HEIGHT = 720;
constexpr int LARGE_RESOLUTION_WIDTH = 1920;
constexpr int LARGE_RESOLUTION_HEIGHT = 1080;
constexpr float FRAME_RATE = 60.0f;
constexpr char APPLICATION_TITLE[] = "Teamfight Tactic";

// ��������
constexpr int HOSTNAME_LENGHT = 256;
constexpr int MIN_PORT_ADDRESS = 49152;
constexpr int MAX_PORT_ADDRESS = 65535;
constexpr int MAX_CONNECTIONS = 8;
constexpr int BUFFER_SIZE = 1024;
constexpr char CONNECTION_REFUSED_MSG[] = "Connection refused.";
constexpr char CONNECTION_ACCEPTED_MSG[] = "Connection accepted.";

constexpr int FONT_SIZE = 24;

constexpr int NICKNAME_MAX_LENGTH = 6;

constexpr float PROMPT_MESSAGE_DURATION = 1.5f;

/* ������ά�������� */

// TODO: ���������������ά���ĳ�����

/* ������ά�������� */

enum Difficulty {
    Easy, // ��ģʽ
    Hard  // ����ģʽ
};

/* ������ά�������� */

constexpr int CHESSBOARD_ROWS = 8;
constexpr int CHESSBOARD_COLUMNS = 7;
constexpr int HALF_CHESSBOARD_ROWS = CHESSBOARD_ROWS / 2;

enum HeroCategory {
    NoHero = 0, // ��Ӣ��
    HeroA       // HeroA
};

typedef struct {
    std::string championName;  // ս��Ӣ������
    std::string championImage; // ս��Ӣ��ͼƬ·��
    int healthPoints;          // ����ֵ
    int experiencePoints;      // ����ֵ
    int attackDamage;          // �����˺�
    int skillDamage;           // �����˺�
    int skillTriggerThreshold; // ���ܴ�����ֵ
    float attackSpeed;         // �����ٶ�
    float movementSpeed;       // �ƶ��ٶ�
    float defenseCoefficient;  // ����ϵ��
} ChampionAttributes;

const ChampionAttributes CHAMPION_A_ATTR = {
    "ս��Ӣ������(����)", "ս��Ӣ��ͼƬ·��", 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f
};

#endif // !_CONSTANT_H_