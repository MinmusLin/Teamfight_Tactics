/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Constant.h
 * File Function: �������Ķ���
 * Author:        �ּ��ꡢ�����ǡ�������������
 * Update Date:   2023/12/11
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
const char APPLICATION_TITLE[] = "Teamfight Tactic";

// ��������
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

/* ������ά�������� */

// TODO: ���������������ά���ĳ�����

/* ������ά�������� */

// TODO: ���������������ά���ĳ�����

/* ������ά�������� */

// TODO: ���������������ά���ĳ�����

#endif // !_CONSTANT_H_