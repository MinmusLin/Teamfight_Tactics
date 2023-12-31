/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Constant.h
 * File Function: �������Ķ���
 * Author:        �ּ��ꡢ�������������ǡ�������
 * Update Date:   2023/12/31
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#include <map>
#include <string>

// Ӧ�ó�������
constexpr int DESIGN_RESOLUTION_WIDTH = 1280;                               // ��Ʒֱ��ʿ��
constexpr int DESIGN_RESOLUTION_HEIGHT = 720;                               // ��Ʒֱ��ʸ߶�
constexpr int SMALL_RESOLUTION_WIDTH = 960;                                 // С�ֱ��ʿ��
constexpr int SMALL_RESOLUTION_HEIGHT = 540;                                // С�ֱ��ʸ߶�
constexpr int MEDIUM_RESOLUTION_WIDTH = 1280;                               // �зֱ��ʿ��
constexpr int MEDIUM_RESOLUTION_HEIGHT = 720;                               // �зֱ��ʸ߶�
constexpr int LARGE_RESOLUTION_WIDTH = 1920;                                // ��ֱ��ʿ��
constexpr int LARGE_RESOLUTION_HEIGHT = 1080;                               // ��ֱ��ʸ߶�
constexpr float FRAME_RATE = 60.0f;                                         // Ӧ�ó���֡��
const std::string APPLICATION_TITLE = u8"�����֮ս Teamfight Tactics";      // Ӧ�ó������

// ���绷������
constexpr int HOSTNAME_MAX_LENGHT = 128;                                    // ��������󳤶�
constexpr int IPV4_ADDRESS_MAX_LENGTH = 15;                                 // IPv4 ��ַ��󳤶�
constexpr int PORT_MAX_LENGTH = 5;                                          // �˿���󳤶�
constexpr int MIN_PORT_ADDRESS = 49152;                                     // ��С�˿ڵ�ַ
constexpr int MAX_PORT_ADDRESS = 65535;                                     // ���˿ڵ�ַ
constexpr int MAX_CONNECTIONS = 8;                                          // �����������
constexpr int BUFFER_SIZE = 256;                                            // ��������С
constexpr int THREAD_SLEEP_DURATION_MILLISECONDS = 100;                     // ������������Ϣ�߳����ߺ�����
constexpr int CONNECTION_TIMEOUT_DURATION = 2;                              // ���������ӳ�ʱʱ��
constexpr int MESSAGE_IDENTIFIER_LENGTH = 10;                               // ��������Ϣ��ʶ������
constexpr int SERVER_REFRESH_INTERVAL_MAGNIFICATION = 10;                   // ����������ˢ��ʱ��������
constexpr float SERVER_REFRESH_INTERVAL = 0.02f;                            // ����������ˢ��ʱ����
constexpr char CONNECTION_REFUSED_MSG[] = "Connection refused.";            // �ܾ�������ʾ��Ϣ
constexpr char CONNECTION_ACCEPTED_MSG[] = "Connection accepted.";          // ����������ʾ��Ϣ
constexpr char START_GAME_IDENTIFIER[] = "Start game";                      // ��ʼ��Ϸ��ʾ��Ϣ��ʶ��
constexpr char START_GAME_MSG[] = "Start game.";                            // ��ʼ��Ϸ��ʾ��Ϣ
constexpr char CURRENT_CONNECTIONS_IDENTIFIER[] = "Connection";             // ��������ǰ����������ʶ��
constexpr char CURRENT_CONNECTIONS_FORMAT[] = "Connection=%d";              // ��������ǰ����������ʽ�ַ���
constexpr char PLAYER_NAME_IDENTIFIER[] = "PlayerName";                     // ���������ʶ��
constexpr char PLAYER_NAME_FORMAT[] = "PlayerName=%s";                      // ���������ʽ�ַ���
constexpr char BATTLE_MAP_IDENTIFIER[] = "BattleMaps";                      // ���ս������ͼ��ʶ��
constexpr char BATTLE_MAP_FORMAT[] = "BattleMaps=%s";                       // ���ս������ͼ��ʽ�ַ���
constexpr char HEALTH_POINTS_IDENTIFIER[] = "HealthPoin";                   // �������ֵ��ʶ��
constexpr char HEALTH_POINTS_FORMAT[] = "HealthPoint=%d��Socket=%d";        // �������ֵ��ʽ�ַ���

// ��ɫ����
constexpr int DARK_BLUE_R = 0;                                              // ����ɫ R ͨ��
constexpr int DARK_BLUE_G = 32;                                             // ����ɫ G ͨ��
constexpr int DARK_BLUE_B = 96;                                             // ����ɫ B ͨ��
constexpr int GOLDEN_R = 223;                                               // ���ɫ R ͨ��
constexpr int GOLDEN_G = 176;                                               // ���ɫ G ͨ��
constexpr int GOLDEN_B = 11;                                                // ���ɫ B ͨ��

// ������������
constexpr int STARTUP_SCENE_FONT_SIZE = 20;                                 // �������������С
constexpr int STARTUP_SCENE_LOADINGBAR_OFFSET_Y = -241;                     // �����������ؽ�����λ�� Y ƫ����
constexpr int STARTUP_SCENE_LOADING_LABEL_OFFSET_X = -30;                   // �����������ؽ�������ǩλ�� X ƫ����
constexpr float STARTUP_SCENE_DURATION = 2.0f;                              // ������������ʱ��
constexpr float SCENE_TRANSITION_DURATION = 0.3f;                           // �����л�ʱ��

// ��ʼ��������
constexpr int NICKNAME_MAX_LENGTH = 6;                                      // ��Ϸ�ǳ���󳤶�
constexpr int INITIAL_SCENE_FONT_SIZE = 30;                                 // ��ʼ���������С
constexpr int INITIAL_SCENE_LABELS_OFFSET_X = 349;                          // ��ʼ������ǩλ�� X ƫ����
constexpr int INITIAL_SCENE_TEXTFIELD_OFFSET_Y = 111;                       // ��ʼ�����ı���λ�� Y ƫ����
constexpr int INITIAL_SCENE_PROMPT_LABEL_OFFSET_Y = 180;                    // ��ʼ������ʾ��ǩλ�� Y ƫ����
constexpr int INITIAL_SCENE_NAME_LABEL_OFFSET_Y = 280;                      // ��ʼ������ӭ��ǩλ�� Y ƫ����
constexpr int INITIAL_SCENE_BUTTON_OFFSET_Y = -310;                         // ��ʼ������ťλ�� Y ƫ����
constexpr float PROMPT_MESSAGE_DURATION = 1.5f;                             // ��ʾ��Ϣͣ��ʱ��

// ѡ�񳡾�����
constexpr int MAX_LITTLE_CHAMPION_COUNT = 8;                                // ССӢ�������������
constexpr int DEFAULT_LITTLE_CHAMPION_CATEGORY = 0;                         // ȱʡССӢ������
constexpr int SELECTION_SCENE_BUTTON_OFFSET_X = -450;                       // ѡ�񳡾�ССӢ�۰�ťλ�� X ƫ����
constexpr int SELECTION_SCENE_BUTTON_OFFSET_Y = -200;                       // ѡ�񳡾�ССӢ�۰�ťλ�� Y ƫ����
constexpr int SELECTION_SCENE_BUTTON_HORIZONTAL_INTERVAL = 300;             // ѡ�񳡾�ССӢ�۰�ťλ��ˮƽ���
constexpr int SELECTION_SCENE_BUTTON_VERTICAL_INTERVAL = 250;               // ѡ�񳡾�ССӢ�۰�ťλ�ô�ֱ���
constexpr int SELECTION_SCENE_LABEL_OFFSET_Y = 250;                         // ѡ�񳡾���ʾ��ǩλ�� Y ƫ����
constexpr int SELECTION_SCENE_LABEL_FONT_SIZE = 50;                         // ѡ�񳡾���ʾ��ǩ�����С

// �˵���������
constexpr int RANDOM_PROMPT_COUNT = 24;                                     // �����ӭ��ʾ������
constexpr int MENU_SCENE_FONT_SIZE = 24;                                    // �˵����������С
constexpr int MENU_SCENE_BUTTONS_OFFSET_X = -296;                           // �˵�������ť���ǩλ�� X ƫ����
constexpr int MENU_SCENE_OFFLINE_MODE_BUTTON_OFFSET_Y = -30;                // �˵�������ϰģʽ��ťλ�� Y ƫ����
constexpr int MENU_SCENE_ONLINE_MODE_BUTTON_OFFSET_Y = -150;                // �˵���������ģʽ��ťλ�� Y ƫ����
constexpr int MENU_SCENE_SETTINGS_BUTTON_OFFSET_Y = -270;                   // �˵��������ð�ťλ�� Y ƫ����
constexpr int MENU_SCENE_WELCOME_LABEL_OFFSET_Y = 240;                      // �˵�������ӭ��ǩλ�� Y ƫ����
constexpr int MENU_SCENE_EXIT_GAME_BUTTON_OFFSET_X = 55;                    // �˵������˳���Ϸ��ťλ�� X ƫ����
constexpr int MENU_SCENE_EXIT_GAME_BUTTON_OFFSET_Y = 55;                    // �˵������˳���Ϸ��ťλ�� Y ƫ����
constexpr int MENU_SCENE_REFERENCE_BUTTON_OFFSET_X = 150;                   // �˵������淨���ܰ�ťλ�� X ƫ����
constexpr int MENU_SCENE_REFERENCE_BUTTON_OFFSET_Y = 55;                    // �˵������淨���ܰ�ťλ�� Y ƫ����
constexpr int ONLINE_MODE_MENU_SCENE_BUTTON_OFFSET_X = 415;                 // ����ģʽ�˵�������ťλ�� X ƫ����
constexpr int ONLINE_MODE_MENU_SCENE_BUTTON_OFFSET_Y = -220;                // ����ģʽ�˵�������ťλ�� Y ƫ����
constexpr int ONLINE_MODE_MENU_SCENE_FONT_SIZE = 30;                        // ����ģʽ�˵����������С
constexpr int ONLINE_MODE_MENU_SCENE_IPV4_TEXTFIELD_OFFSET_Y = -167;        // ����ģʽ�˵����� IPv4 �ı���λ�� Y ƫ����
constexpr int ONLINE_MODE_MENU_SCENE_PORT_TEXTFIELD_OFFSET_Y = -275;        // ����ģʽ�˵������˿��ı���λ�� Y ƫ����
constexpr int ONLINE_MODE_MENU_SCENE_PROMPT_LABEL_OFFSET_Y = 285;           // ����ģʽ�˵�������ʾ��ǩλ�� Y ƫ����
constexpr int REFERENCE_SCENE_RETURN_MENU_BUTTON_OFFSET_X = 560;            // �淨�������ز˵���ťλ�� X ƫ����
constexpr int REFERENCE_SCENE_RETURN_MENU_BUTTON_OFFSET_Y = -315;           // �淨�������ز˵���ťλ�� Y ƫ����
constexpr float START_GAME_BUTTON_APPEARANCE_DURATION = 1.5f;               // ����ģʽ�˵�������ʼ��Ϸ��ť����ʱ����
constexpr float CONNECTION_FAILED_PROMPT_MESSAGE_DURATION = 3.0f;           // ����������ʧ����ʾ��Ϣͣ��ʱ��
constexpr float RANDOM_WELCOME_PROMPT_PROBABILITY = 0.5f;                   // �����ӭ��ʾ�����

// ��ս��������
constexpr int WAITING_MAP_COUNT = 9;                                        // ��ս����ͼ��С
constexpr int BATTLE_MAP_ROWS = 8;                                          // ս������ͼ����
constexpr int BATTLE_MAP_COLUMNS = 9;                                       // ս������ͼ����
constexpr int PLACE_MAP_ROWS = BATTLE_MAP_ROWS / 2;                         // ��������ͼ����
constexpr int BATTLE_AREA_MIN_CHAMPION_COUNT = 3;                           // ��͵ȼ�ս�������Ӣ������
constexpr int BATTLE_AREA_MAX_CHAMPION_COUNT = 9;                           // ��ߵȼ�ս�������Ӣ������
constexpr int BATTLE_SCENE_LOADINGBAR_X = 213;                              // ��ս����׼��������λ�� X ����
constexpr int BATTLE_SCENE_LOADINGBAR_Y = 669;                              // ��ս����׼��������λ�� Y ����
constexpr int BATTLE_SCENE_LOADINGBAR_LABEL_FONT_SIZE = 20;                 // ��ս����׼����������ǩ�����С
constexpr int BATTLE_SCENE_LOADINGBAR_LABEL_OFFSET_X = -18;                 // ��ս����׼����������ǩλ�� X ƫ����
constexpr int BATTLE_SCENE_LOADINGBAR_LABEL_THRESHOLD = 20;                 // ��ս����׼��ʱ����ʾ��ֵ
constexpr int BATTLE_SCENE_RETURN_MENU_BUTTON_OFFSET_X = 522;               // ��ս�������ز˵���ťλ�� X ƫ����
constexpr int BATTLE_SCENE_RETURN_MENU_BUTTON_OFFSET_Y = -294;              // ��ս�������ز˵���ťλ�� Y ƫ����
constexpr int BATTLE_SCENE_DELETE_CHAMPION_BUTTON_START_X = 118;            // ��ս����ս��Ӣ��ɾ����ťλ�� X ����
constexpr int BATTLE_SCENE_DELETE_CHAMPION_BUTTON_START_Y = 77;             // ��ս����ս��Ӣ��ɾ����ťλ�� Y ����
constexpr int BATTLE_SCENE_DELETE_CHAMPION_BUTTON_UPPER_BOUNDARY = 130;     // ��ս����ս��Ӣ��ɾ����ť�ϱ߽� Y ����
constexpr int BATTLE_SCENE_DELETE_CHAMPION_BUTTON_LOWER_BOUNDARY = 24;      // ��ս����ս��Ӣ��ɾ����ť�±߽� Y ����
constexpr int BATTLE_SCENE_DELETE_CHAMPION_BUTTON_LEFT_BOUNDARY = 25;       // ��ս����ս��Ӣ��ɾ����ť��߽� X ����
constexpr int BATTLE_SCENE_DELETE_CHAMPION_BUTTON_RIGHT_BOUNDARY = 210;     // ��ս����ս��Ӣ��ɾ����ť�ұ߽� X ����
constexpr int SCORE_BOARD_LAYER_START_X = 1125;                             // ������㱳��λ�� X ����
constexpr int SCORE_BOARD_LAYER_START_Y = 680;                              // ������㱳��λ�� Y ����
constexpr int SCORE_BOARD_LAYER_VERTICAL_INTERVAL = 69;                     // ������㱳����ֱ���
constexpr int SCORE_BOARD_LAYER_NAME_LABEL_OFFSET_X = -125;                 // ����������������ǩ
constexpr int SCORE_BOARD_LAYER_SCORE_LABEL_OFFSET_X = 90;                  // ��������������ֵ��ǩ
constexpr int SCORE_BOARD_LAYER_RANK_LABEL_OFFSET_X = 115;                  // ����������������ǩ
constexpr int SCORE_BOARD_LABEL_FONT_SIZE = 25;                             // ��������ǩ�����С
constexpr int BATTLE_END_LABEL_FONT_SIZE = 200;                             // ��ս������ʾ��ǩ�����С
constexpr int BATTLE_END_LABEL_OFFSET_Y = 74;                               // ��ս������ʾ��ǩλ�� Y ƫ����
constexpr int BATTLE_END_LABEL_OUTLINE_WIDTH = 4;                           // ��ս������ʾ��ǩ��߿��
constexpr int BATTLE_END_LABEL_SHADOW_OFFSET_X = 2;                         // ��ս������ʾ��ǩ��Ӱ X ƫ����
constexpr int BATTLE_END_LABEL_SHADOW_OFFSET_Y = -2;                        // ��ս������ʾ��ǩ��Ӱ Y ƫ����
constexpr int BATTLE_END_LABEL_BLUR_RADIUS = 3;                             // ��ս������ʾ��ǩģ���뾶
constexpr int CHAMPION_HEALTHBAR_VERTICAL_INTERVAL = 29;                    // ��ս������������ֱ���
constexpr int CHAMPION_MANABAR_VERTICAL_INTERVAL = 22;                      // ��ս������������ֱ���
constexpr int TALENT_RUNE_COUNT = 3;                                        // �츳��������
constexpr int TALENT_RUNE_BUTTON_OFFSET_X = 390;                            // �츳���İ�ťλ�� X ƫ����
constexpr int TALENT_RUNE_BUTTON_OFFSET_Y = -55;                            // �츳���İ�ťλ�� X ƫ����
constexpr int BOND_EFFECT_START_X = -2;                                     // �Ч��λ�� X ����
constexpr int BOND_EFFECT_HORIZONTAL_INTERVAL = 65;                         // �Ч��ˮƽ���
constexpr int MY_BOND_EFFECT_START_Y = 194;                                 // �ҷ��Ч��λ�� Y ����
constexpr int ENEMY_BOND_EFFECT_START_Y = 670;                              // �з��Ч��λ�� Y ����
constexpr int LITTLE_CHAMPION_OFFSET_Y = -250;                              // ССӢ��λ�� Y ƫ����
constexpr int LITTLE_CHAMPION_MOVEMENT_SPEED = 200;                         // ССӢ���ƶ��ٶ�
constexpr int LITTLE_CHAMPION_LABEL_OFFSET_Y = -315;                        // ССӢ�۵ǳ���ǩλ�� Y ƫ����
constexpr int LITTLE_CHAMPION_LABEL_FONT_SIZE = 30;                         // ССӢ�۵ǳ���ǩ�����С
constexpr int INTERVAL_BETWEEN_WEAPON_AND_CHAMPION = 40;                    // ��ս����ս��Ӣ�����������
constexpr int WEAPON_ANIMATION_ROTATION_ANGLE = 60;                         // ��ս��������������ת�Ƕ�
constexpr int WEAPON_ANIMATION_ROTATION_COUNT = 4;                          // ��ս��������������ת����
constexpr float LITTLE_CHAMPION_PARTICLE_SCALE = 0.75f;                     // ССӢ������Ч�����ű���
constexpr float LITTLE_CHAMPION_PARTICLE_LIFE = 1.0f;                       // ССӢ������Ч����������
constexpr float LITTLE_CHAMPION_ROTATE_DURATION = 0.5f;                     // ССӢ����ת����ʱ��
constexpr float WEAPON_ANIMATION_ROTATION_DURATION = 0.15f;                 // ��ս��������������תʱ��
constexpr float BATTLE_SCENE_LOADINGBAR_DURATION = 30.0f;                   // ��ս����׼��ʱ��
constexpr float BATTLE_END_DURATION = 2.0f;                                 // ��ս����ͣ��ʱ��

// ���ó�������
constexpr int SETTINGS_SCENE_SLIDER_OFFSET_X = -150;                        // ���ó����������������ǩλ�� X ƫ����
constexpr int SETTINGS_SCENE_BGMSLIDER_OFFSET_Y = 69;                       // ���ó������������������������ǩλ�� Y ƫ����
constexpr int SETTINGS_SCENE_EFFSLIDER_OFFSET_Y = -34;                      // ���ó�����Ч�������������ǩλ�� Y ƫ����
constexpr int SETTINGS_SCENE_CHECKBOX_OFFSET_Y = -157;                      // ���ó����Ѷȸ�ѡ�����ǩλ�� Y ƫ����
constexpr int SETTINGS_SCENE_EASY_CHECKBOX_OFFSET_X = -307;                 // ���ó������Ѷȸ�ѡ�����ǩλ�� X ƫ����
constexpr int SETTINGS_SCENE_NORMAL_CHECKBOX_OFFSET_X = -166;               // ���ó��������Ѷȸ�ѡ�����ǩλ�� X ƫ����
constexpr int SETTINGS_SCENE_DIFFICULT_CHECKBOX_OFFSET_X = -25;             // ���ó��������Ѷȸ�ѡ�����ǩλ�� X ƫ����
constexpr int SETTINGS_SCENE_RETURN_MENU_BUTTON_OFFSET_X = 529;             // ���ó������ز˵���ťλ�� X ƫ����
constexpr int SETTINGS_SCENE_RETURN_MENU_BUTTON_OFFSET_Y = -300;            // ���ó������ز˵���ťλ�� Y ƫ����
constexpr int DEFAULT_MUSIC_SIGN = -1;                                      // ȱʡ���ֱ�ʶ
constexpr float DEFAULT_MUSIC_VOLUMN = 0.5f;                                // ȱʡ������С

// �̵�����
constexpr int MAX_SELECTABLE_CHAMPION_COUNT = 5;                            // ����ѡ��ս��Ӣ������
constexpr int CHAMPION_UPLEVEL_COUNT = 3;                                   // ս��Ӣ����������
constexpr int SHOP_CHAMPION_INTERVAL = 10;                                  // �̵�ս��Ӣ�۰�ť���
constexpr int SHOP_CHAMPION_WIDTH = 120;                                    // �̵�ս��Ӣ�۰�ť���
constexpr int SHOP_CHAMPION_HEIGHT = 100;                                   // �̵�ս��Ӣ�۰�ť�߶�
constexpr int SHOP_CHAMPION_START_X = 386 + SHOP_CHAMPION_WIDTH / 2;        // �̵�ս��Ӣ����ʼ��ťλ�� X ����
constexpr int SHOP_CHAMPION_START_Y = 10 + SHOP_CHAMPION_HEIGHT / 2;        // �̵�ս��Ӣ����ʼ��ťλ�� Y ����
constexpr int SHOP_UPLEVEL_BUTTON_OFFSET_X = -324;                          // �̵�������ťλ�� X ƫ����
constexpr int SHOP_UPLEVEL_BUTTON_OFFSET_Y = -273;                          // �̵�������ťλ�� Y ƫ����
constexpr int SHOP_REFRESH_BUTTON_OFFSET_X = -324;                          // �̵�ˢ�°�ťλ�� X ƫ����
constexpr int SHOP_REFRESH_BUTTON_OFFSET_Y = -328;                          // �̵�ˢ�°�ťλ�� Y ƫ����
constexpr int SHOP_LEVEL_LABEL_OFFSET_X = -395;                             // �̵�ȼ���ǩλ�� X ƫ����
constexpr int SHOP_LEVEL_LABEL_OFFSET_Y = -228;                             // �̵�ȼ���ǩλ�� Y ƫ����
constexpr int SHOP_LEVEL_LABEL_FONT_SIZE = 20;                              // �̵�ȼ���ǩ�����С
constexpr int SHOP_COIN_LABEL_FONT_SIZE = 20;                               // �̵���������ǩ�����С
constexpr int SHOP_COIN_LABEL_OFFSET_X = 358;                               // �̵���������ǩλ�� X ƫ����
constexpr int SHOP_COIN_LABEL_OFFSET_Y = -228;                              // �̵���������ǩλ�� Y ƫ����
constexpr int SHOP_COIN_LABEL_START_X = 334;                                // ˢ���̵������������������ǩλ�� X ����
constexpr int SHOP_REFRESH_COIN_LABEL_START_Y = 33;                         // ˢ���̵�������������ǩλ�� Y ����
constexpr int SHOP_UPLEVEL_COIN_LABEL_START_Y = 88;                         // ����������������ǩλ�� Y ����
constexpr int INITIAL_GOLD_COIN = 14;                                       // ��ʼ�������
constexpr int REFRESH_SHOP_PRICE = 2;                                       // ˢ���̵�����������
const std::map<int, int> UPLEVEL_PRICE = {                                  // ��������������
    {BATTLE_AREA_MIN_CHAMPION_COUNT, 12},                                   // �ȼ� 1 �������ȼ� 2 ����������
    {BATTLE_AREA_MIN_CHAMPION_COUNT + 1, 16},                               // �ȼ� 2 �������ȼ� 3 ����������
    {BATTLE_AREA_MIN_CHAMPION_COUNT + 2, 20},                               // �ȼ� 3 �������ȼ� 4 ����������
    {BATTLE_AREA_MIN_CHAMPION_COUNT + 3, 28},                               // �ȼ� 4 �������ȼ� 5 ����������
    {BATTLE_AREA_MIN_CHAMPION_COUNT + 4, 36},                               // �ȼ� 5 �������ȼ� 6 ����������
    {BATTLE_AREA_MIN_CHAMPION_COUNT + 5, 52},                               // �ȼ� 6 �������ȼ� 7 ����������
};

// ս��Ӣ�����Բ�����
constexpr int CHAMPION_ATTRIBUTES_FONT_SIZE = 18;                           // ս��Ӣ�����Ա�ǩ�����С
constexpr int CHAMPION_NAME_LABEL_FONT_SIZE = 30;                           // ս��Ӣ�����Ʊ�ǩ�����С
constexpr int BACKGROUND_IMAGE_START_X = 178;                               // ����ͼλ�� X ����
constexpr int BACKGROUND_IMAGE_START_Y = 407;                               // ����ͼλ�� Y ����
constexpr int BACKGROUND_IMAGE_TRANSPARENCY = 230;                          // ����ͼ͸����
constexpr int CHAMPION_IMAGE_START_X = 110;                                 // ս��Ӣ��ͼƬλ�� X ����
constexpr int CHAMPION_IMAGE_START_Y = 547;                                 // ս��Ӣ��ͼƬλ�� Y ����
constexpr int CHAMPION_NAME_LABEL_START_X = 172;                            // ս��Ӣ�����Ʊ�ǩλ�� X ����
constexpr int CHAMPION_NAME_LABEL_START_Y = 564;                            // ս��Ӣ�����Ʊ�ǩλ�� Y ����
constexpr int FIRST_COLUMN_START_X = 130;                                   // ��һ�����Ա�ǩλ�� X ����
constexpr int SECOND_COLUMN_START_X = 242;                                  // �ڶ������Ա�ǩλ�� X ����
constexpr int HEALTH_POINTS_LEBEL_START_Y = 466;                            // ����ֵ��ǩλ�� Y ����
constexpr int ATTACK_DAMAGE_LABEL_START_Y = 404;                            // �����˺���ǩλ�� Y ����
constexpr int ATTACK_RANGE_LABEL_START_Y = 329;                             // ������Χ��ǩλ�� Y ����
constexpr int ATTACK_SPEED_LABEL_START_Y = 254;                             // �����ٶȱ�ǩλ�� Y ����
constexpr int PRICE_LABEL_START_Y = HEALTH_POINTS_LEBEL_START_Y;            // �۸��ǩλ�� Y ����
constexpr int MOVEMENT_SPEED_START_Y = ATTACK_DAMAGE_LABEL_START_Y;         // �ƶ��ٶȱ�ǩλ�� Y ����
constexpr int DEFENSE_COEFFICIENT_START_Y = ATTACK_RANGE_LABEL_START_Y;     // ����ϵ����ǩλ�� Y ����
constexpr int SKILL_TRIGGER_THRESHOLD_START_Y = ATTACK_SPEED_LABEL_START_Y; // ���ܴ�����ֵ��ǩλ�� Y ����
constexpr int LEVEL_LABEL_START_X = 245;                                    // �ȼ���ǩλ�� X ����
constexpr int LEVEL_LABEL_START_Y = 521;                                    // �ȼ���ǩλ�� Y ����

// λ����������Ļ��������
constexpr int WAITING_AREA_START_X = 415;                                   // ��ս����ʼ��Ļ����λ�� X ����
constexpr int WAITING_AREA_START_Y = 195;                                   // ��ս����ʼ��Ļ����λ�� Y ����
constexpr int BATTLE_AREA_START_X = 415;                                    // ս������ʼ��Ļ����λ�� X ����
constexpr int BATTLE_AREA_START_Y = 275;                                    // ս������ʼ��Ļ����λ�� Y ����
constexpr int CHAMPION_HORIZONTAL_INTERVAL = 60;                            // ս��Ӣ��ˮƽ���
constexpr int CHAMPION_VERTICAL_INTERVAL = 45;                              // ս��Ӣ�۴�ֱ���

// ս����������
constexpr int CHAMPION_CATEGORY_NUMBERS = 15;                               // ս��Ӣ����������
constexpr int BATTLE_STAGE_NUMBERS = 3;                                     // ս���׶�״̬����
constexpr int INITIAL_HEALTH_POINTS = 100;                                  // ��ҳ�ʼ����ֵ
constexpr int RUNE_WARRIOR_HEALTH_POINTS_BUFF = 20;                         // ��ʿ���ĳ�ʼ����ֵ�ӳ�
constexpr int RUNE_PIRATE_GOLD_COINS_BUFF = 10;                             // �������ĳ�ʼ��������ӳ�
constexpr int INCREASED_MAGIC_POINTS = 20;                                  // ������Ӧ����ħ��ֵ
constexpr int DECREASED_HEALTH_POINTS = 5;                                  // ���ս��Ӣ�۶�Ӧ��������ֵ
constexpr int INCREASED_GOLD_COINS = 5;                                     // ���ս��Ӣ�۶�Ӧ���ӽ������
constexpr int NEW_BATTLE_INCREASED_GOLD_COINS = 10;                         // ��ս�����ӽ������
constexpr int EARLY_MIDDLE_STAGE_THRESHOLD = 20;                            // ǰ����ս���׶���ֵ
constexpr int MIDDLE_LATE_STAGE_THRESHOLD = 50;                             // �к���ս���׶���ֵ
constexpr int DEFENSE_SCORE_COEFFICIENT = 200;                              // ��������ϵ��
constexpr int ATTACK_SCORE_COEFFICIENT = 30;                                // ��������ϵ��
constexpr int SPEED_SCORE_COEFFICIENT = 1;                                  // �ٶȷ���ϵ��
constexpr int STAGE_SCORE_THRESHOLDS_COUNT = 6;                             // ս���׶λ��ָ���
constexpr int SKILL_ATTACK_DAMAGE_UP = 50;                                  // ���ܹ����˺�����
constexpr int ATTACK_RANGE_THRESHOLD = 1;                                   // ������Χ��ֵ
constexpr int ATTACK_DAMAGE_MAGNIFICATION_HIGH = 5;                         // �����˺��߱���
constexpr int ATTACK_DAMAGE_MAGNIFICATION_MIDDLE = 3;                       // �����˺��б���
constexpr int ATTACK_DAMAGE_MAGNIFICATION_LOW = 2;                          // �����˺��ͱ���
constexpr int DEPLOY_CHAMPIONS_MAX_COUNT = 2;                               // ����ս��Ӣ�۳�ʼ����
constexpr int MAX_BOND_COUNT = 6;                                           // ս��Ӣ���Ч������
constexpr int BOND_EFFECT_TRIGGER_CONDITION = 2;                            // �Ч����������
constexpr int BROTHERHOOD_MOVEMENT_SPEED_MULTIPLIER = 3;                    // �ֵ��Ч���ƶ��ٶȳ˷�ϵ��
constexpr int BROTHERHOOD_ATTACK_SPEED_MULTIPLIER = 2;                      // �ֵ��Ч�������ٶȳ˷�ϵ��
constexpr int LOUT_MOVEMENT_SPEED_MULTIPLIER = 2;                           // ç���Ч���˷�ϵ��
constexpr int LOUT_ATTACK_DAMAGE_MULTIPLIER = 2;                            // ç���Ч���˷�ϵ��
constexpr int DARKSIDE_ATTACK_DAMAGE_MULTIPLIER = 2;                        // �����Ч���˷�ϵ��
constexpr int GOODSHOOTER_ATTACK_SPEED_MULTIPLIER = 3;                      // �������Ч���˷�ϵ��
constexpr int POPSTAR_ATTACK_SPEED_MULTIPLIER = 3;                          // ��ɯ�Ч���˷�ϵ��
constexpr int POPSTAR_MOVEMENT_SPEED_MULTIPLIER = 5;                        // ��ɯ�Ч���˷�ϵ��
constexpr float DARKSIDE_SKILL_TRIGGER_MULTIPLIER = 0.5f;                   // �����Ч���˷�ϵ��
constexpr float LOUT_HEALTH_POINTS_MULTIPLIER = 1.5f;                       // ç���Ч���˷�ϵ��
constexpr float SKILL_DEFENSE_COEFFICIENT_UP = 1.0f;                        // ���ܷ���ϵ������
constexpr float SKILL_ATTACK_SPEED_UP = 2.0f;                               // ���ܹ����ٶ�����
constexpr float DEFENSE_COEFFICIENT_THRESHOLD_HIGH = 1.5f;                  // ����ϵ������ֵ
constexpr float DEFENSE_COEFFICIENT_THRESHOLD_LOW = 1.4f;                   // ����ϵ������ֵ
constexpr double DEFENSE_SCORE_WEIGHT = 2.0;                                // ս��Ӣ��ְҵƫ�÷�������Ȩ��
constexpr double ATTACK_SCORE_WEIGHT = 2.5;                                 // ս��Ӣ��ְҵƫ�ù�������Ȩ��
constexpr double SPEED_SCORE_WEIGHT = 1.0;                                  // ս��Ӣ��ְҵƫ���ٶȷ���Ȩ��
constexpr int STAGE_SCORE_THRESHOLDS[] = { 0, 5, 10, 25, 50, 60 };          // ս���׶λ�����ֵ
constexpr int STAGE_WITH_RATE_OF_CHAMPIONS[3][5] = {                        // ����ս���׶ε�ս��Ӣ��ѡ�����
    {6, 5, 3, 1, 0},                                                        // ǰ��ս���׶�ս��Ӣ��ѡ�����
    {5, 5, 3, 1, 1},                                                        // ����ս���׶�ս��Ӣ��ѡ�����
    {4, 5, 2, 2, 2},                                                        // ����ս���׶�ս��Ӣ��ѡ�����
};

// ��������״̬����
enum ConnectionStatus {
    ConnectionError,    // ���Ӵ���
    ConnectionRefused,  // ���Ӿܾ�
    ConnectionAccepted, // ���ӽ���
    ConnectionTimeout   // ���ӳ�ʱ
};

// ��ϰģʽ�Ѷȶ���
enum Difficulty {
    Easy,               // ��ģʽ
    Normal,             // ����ģʽ
    Hard                // ����ģʽ
};

// λ��״̬����
enum LocationStatus {
    WaitingArea,        // ��ս��
    BattleArea          // ս����
};

// ս��ʤ��״̬����
enum BattleSituation {
    Lose,               // ʧ��
    Draw,               // ƽ��
    Win                 // ʤ��
};

// ս���׶�״̬����
enum BattleStage {
    EarlyStage,         // ǰ��ս���׶�
    MiddleStage,        // ����ս���׶�
    LateStage           // ����ս���׶�
};

// ս��Ӣ���Ч������
enum Bond {
    NoBond,             // ���Ч��
    Brotherhood,        // �ֵܣ�������������
    Lout,               // ç�򣨰�������ɭ��
    DarkSide,           // ������ܽ�ա���ľľ��������˹��
    GoodShooter,        // �����֣����桢���˿��
    PopStar             // ��֮�ػ�����ɯ��
};

// ս��Ӣ���츳���Ķ���
enum TalentRune {
    Pirate,             // ����������ÿ�غϽ��������
    General,            // ����������Ӣ��λ��
    Warriors,           // ��ʿ�����ӳ�ʼ����ֵ��
    NoTalentRune        // ���츳����
};

// ս��Ӣ�����ඨ��
enum ChampionCategory {
    NoChampion,         // ��ս��Ӣ��
    Champion1,          // �٣�һ�ǣ�
    Champion2,          // �٣����ǣ�
    Champion3,          // ������һ�ǣ�
    Champion4,          // ���������ǣ�
    Champion5,          // ������һ�ǣ�
    Champion6,          // �����򣨶��ǣ�
    Champion7,          // ��ɭ��һ�ǣ�
    Champion8,          // ��ɭ�����ǣ�
    Champion9,          // ��ܽ�գ�һ�ǣ�
    Champion10,         // ��ܽ�գ����ǣ�
    Champion11,         // ���棨һ�ǣ�
    Champion12,         // ���棨���ǣ�
    Champion13,         // ����ˣ�һ�ǣ�
    Champion14,         // ����ˣ����ǣ�
    Champion15,         // ������һ�ǣ�
    Champion16,         // ���������ǣ�
    Champion17,         // ���˿��һ�ǣ�
    Champion18,         // ���˿�����ǣ�
    Champion19,         // ��ķ��һ�ǣ�
    Champion20,         // ��ķ�����ǣ�
    Champion21,         // ε��һ�ǣ�
    Champion22,         // ε�����ǣ�
    Champion23,         // ��ľľ��һ�ǣ�
    Champion24,         // ��ľľ�����ǣ�
    Champion25,         // ��ɣ�ᣨһ�ǣ�
    Champion26,         // ��ɣ�ᣨ���ǣ�
    Champion27,         // ������˹��һ�ǣ�
    Champion28,         // ������˹�����ǣ�
    Champion29,         // ��ɯ��һ�ǣ�
    Champion30          // ��ɯ�����ǣ�
};

// λ�����Զ���
struct Location {
    LocationStatus status;                        // λ��״̬
    int position;                                 // λ������
    bool operator<(const Location& other) const { // ��������� < ���� std::map
        if (status < other.status) {
            return true;
        }
        if (status > other.status) {
            return false;
        }
        return position < other.position;
    }
};

// ս��Ӣ��ְҵƫ�ö���
typedef struct {
    double defenseScore;               // ��������
    double attackScore;                // ��������
    double speedScore;                 // �ٶȷ���
} ProfessionPreference;

// ս��λ�����Զ���
typedef struct {
    int x;                             // X ����
    int y;                             // Y ����
} BattleLocation;

// ս��Ӣ�����Զ���
typedef struct {
    ChampionCategory championCategory; // ս��Ӣ������
    std::string championName;          // ս��Ӣ������
    std::string championImagePath;     // ս��Ӣ��ͼƬ·��
    int price;                         // �۸�
    int level;                         // �ȼ�
    int healthPoints;                  // ����ֵ
    int magicPoints;                   // ħ��ֵ
    int attackDamage;                  // �����˺�
    int skillTriggerThreshold;         // ���ܴ�����ֵ
    int attackRange;                   // ������Χ
    float attackSpeed;                 // �����ٶ�
    float movementSpeed;               // �ƶ��ٶ�
    float defenseCoefficient;          // ����ϵ��
    Bond bond;                         // �Ч��
} ChampionAttributes;

// ս��Ӣ�����Բ���
const ChampionAttributes CHAMPION_1_ATTR = { // �٣�һ�ǣ�
    Champion1, u8"��", "../Resources/Champions/Champion1.png", 1, 1, 500, 0, 50, 200, 1, 0.75f, 1.0f, 1.0f, NoBond
};
const ChampionAttributes CHAMPION_2_ATTR = { // �٣����ǣ�
    Champion2, u8"��", "../Resources/Champions/Champion2.png", 3, 2, 900, 0, 75, 200, 1, 0.75f, 1.0f, 1.0f, NoBond
};
const ChampionAttributes CHAMPION_3_ATTR = { // ������һ�ǣ�
    Champion3, u8"����", "../Resources/Champions/Champion3.png", 1, 1, 550, 0, 45, 200, 1, 1.0f, 1.0f, 1.2f, Brotherhood
};
const ChampionAttributes CHAMPION_4_ATTR = { // ���������ǣ�
    Champion4, u8"����", "../Resources/Champions/Champion4.png", 3, 2, 990, 0, 68, 200, 1, 1.0f, 1.0f, 1.2f, Brotherhood
};
const ChampionAttributes CHAMPION_5_ATTR = { // ������һ�ǣ�
    Champion5, u8"������", "../Resources/Champions/Champion5.png", 1, 1, 700, 0, 55, 200, 1, 0.6f, 1.0f, 1.4f, Lout
};
const ChampionAttributes CHAMPION_6_ATTR = { // �����򣨶��ǣ�
    Champion6, u8"������", "../Resources/Champions/Champion6.png", 3, 2, 1260, 0, 83, 200, 1, 0.6f, 1.0f, 1.4f, Lout
};
const ChampionAttributes CHAMPION_7_ATTR = { // ��ɭ��һ�ǣ�
    Champion7, u8"��ɭ", "../Resources/Champions/Champion7.png", 1, 1, 700, 0, 70, 200, 1, 0.5f, 1.0f, 1.2f, Lout
};
const ChampionAttributes CHAMPION_8_ATTR = { // ��ɭ�����ǣ�
    Champion8, u8"��ɭ", "../Resources/Champions/Champion8.png", 3, 2, 1260, 0, 105, 200, 1, 0.5f, 1.0f, 1.2f, Lout
};
const ChampionAttributes CHAMPION_9_ATTR = { // ��ܽ�գ�һ�ǣ�
    Champion9, u8"��ܽ��", "../Resources/Champions/Champion9.png", 1, 1, 650, 0, 55, 200, 1, 0.55f, 1.0f, 1.3f, DarkSide
};
const ChampionAttributes CHAMPION_10_ATTR = { // ��ܽ�գ����ǣ�
    Champion10, u8"��ܽ��", "../Resources/Champions/Champion10.png", 3, 2, 1170, 0, 83, 200, 1, 0.55f, 1.0f, 1.3f, DarkSide
};
const ChampionAttributes CHAMPION_11_ATTR = { // ���棨һ�ǣ�
    Champion11, u8"����", "../Resources/Champions/Champion11.png", 2, 1, 500, 0, 50, 200, 3, 0.7f, 1.0f, 1.0f, GoodShooter
};
const ChampionAttributes CHAMPION_12_ATTR = { // ���棨���ǣ�
    Champion12, u8"����", "../Resources/Champions/Champion12.png", 6, 2, 900, 0, 75, 200, 3, 0.7f, 1.0f, 1.0f, GoodShooter
};
const ChampionAttributes CHAMPION_13_ATTR = { // ����ˣ�һ�ǣ�
    Champion13, u8"�����", "../Resources/Champions/Champion13.png", 2, 1, 750, 0, 60, 200, 1, 0.65f, 1.0f, 1.5f, NoBond
};
const ChampionAttributes CHAMPION_14_ATTR = { // ����ˣ����ǣ�
    Champion14, u8"�����", "../Resources/Champions/Champion14.png", 6, 2, 1350, 0, 90, 200, 1, 0.65f, 1.0f, 1.5f, NoBond
};
const ChampionAttributes CHAMPION_15_ATTR = { // ������һ�ǣ�
    Champion15, u8"����", "../Resources/Champions/Champion15.png", 2, 1, 700, 0, 50, 200, 1, 0.75f, 1.0f, 1.1f, Brotherhood
};
const ChampionAttributes CHAMPION_16_ATTR = { // ���������ǣ�
    Champion16, u8"����", "../Resources/Champions/Champion16.png", 6, 2, 1260, 0, 75, 200, 1, 0.75f, 1.0f, 1.1f, Brotherhood
};
const ChampionAttributes CHAMPION_17_ATTR = { // ���˿��һ�ǣ�
    Champion17, u8"���˿", "../Resources/Champions/Champion17.png", 2, 1, 600, 0, 65, 200, 5, 0.8f, 1.0f, 0.9f, GoodShooter
};
const ChampionAttributes CHAMPION_18_ATTR = { // ���˿�����ǣ�
    Champion18, u8"���˿", "../Resources/Champions/Champion18.png", 6, 2, 1080, 0, 98, 200, 5, 0.8f, 1.0f, 0.9f, GoodShooter
};
const ChampionAttributes CHAMPION_19_ATTR = { // ��ķ��һ�ǣ�
    Champion19, u8"��ķ", "../Resources/Champions/Champion19.png", 3, 1, 700, 0, 55, 200, 1, 0.6f, 1.0f, 1.6f, NoBond
};
const ChampionAttributes CHAMPION_20_ATTR = { // ��ķ�����ǣ�
    Champion20, u8"��ķ", "../Resources/Champions/Champion20.png", 9, 2, 1260, 0, 83, 200, 1, 0.6f, 1.0f, 1.6f, NoBond
};
const ChampionAttributes CHAMPION_21_ATTR = { // ε��һ�ǣ�
    Champion21, u8"ε", "../Resources/Champions/Champion21.png", 3, 1, 800, 0, 60, 200, 1, 0.65f, 1.0f, 1.55f, NoBond
};
const ChampionAttributes CHAMPION_22_ATTR = { // ε�����ǣ�
    Champion22, u8"ε", "../Resources/Champions/Champion22.png", 9, 2, 1440, 0, 90, 200, 1, 0.65f, 1.0f, 1.55f, NoBond
};
const ChampionAttributes CHAMPION_23_ATTR = { // ��ľľ��һ�ǣ�
    Champion23, u8"��ľľ", "../Resources/Champions/Champion23.png", 3, 1, 800, 0, 60, 200, 1, 0.7f, 1.0f, 1.5f, DarkSide
};
const ChampionAttributes CHAMPION_24_ATTR = { // ��ľľ�����ǣ�
    Champion24, u8"��ľľ", "../Resources/Champions/Champion24.png", 9, 2, 1440, 0, 90, 200, 1, 0.7f, 1.0f, 1.5f, DarkSide
};
const ChampionAttributes CHAMPION_25_ATTR = { // ��ɣ�ᣨһ�ǣ�
    Champion25, u8"��ɣ��", "../Resources/Champions/Champion25.png", 4, 1, 950, 0, 80, 200, 1, 0.85f, 1.0f, 1.5f, NoBond
};
const ChampionAttributes CHAMPION_26_ATTR = { // ��ɣ�ᣨ���ǣ�
    Champion26, u8"��ɣ��", "../Resources/Champions/Champion26.png", 12, 2, 1710, 0, 120, 200, 1, 0.85f, 1.0f, 1.5f, NoBond
};
const ChampionAttributes CHAMPION_27_ATTR = { // ������˹��һ�ǣ�
    Champion27, u8"������˹", "../Resources/Champions/Champion27.png", 4, 1, 600, 0, 100, 200, 5, 0.85f, 1.0f, 0.9f, DarkSide
};
const ChampionAttributes CHAMPION_28_ATTR = { // ������˹�����ǣ�
    Champion28, u8"������˹", "../Resources/Champions/Champion28.png", 12, 2, 1080, 0, 140, 200, 5, 0.9f, 1.0f, 0.9f, DarkSide
};
const ChampionAttributes CHAMPION_29_ATTR = { // ��ɯ��һ�ǣ�
    Champion29, u8"��ɯ", "../Resources/Champions/Champion29.png", 5, 1, 800, 0, 100, 200, 5, 0.9f, 1.0f, 0.9f, PopStar
};
const ChampionAttributes CHAMPION_30_ATTR = { // ��ɯ�����ǣ�
    Champion30, u8"��ɯ", "../Resources/Champions/Champion30.png", 15, 2, 1440, 0, 140, 200, 5, 0.9f, 1.0f, 0.9f, PopStar
};

// ս��Ӣ�ۼ۸���ඨ��
constexpr ChampionCategory FIRST_LEVEL[] = { // ս��Ӣ��һ���۸����
    NoChampion, // ��ս��Ӣ��
    Champion1,  // �٣�һ�ǣ�
    Champion3,  // ������һ�ǣ�
    Champion5,  // ������һ�ǣ�
    Champion7,  // ��ɭ��һ�ǣ�
    Champion9   // ��ܽ�գ�һ�ǣ�
};
constexpr ChampionCategory SECOND_LEVEL[] = { // ս��Ӣ�۶����۸����
    NoChampion, // ��ս��Ӣ��
    Champion11, // ���棨һ�ǣ�
    Champion13, // ����ˣ�һ�ǣ�
    Champion15, // ������һ�ǣ�
    Champion17  // ���˿��һ�ǣ�
};
constexpr ChampionCategory THIRD_LEVEL[] = { // ս��Ӣ�������۸����
    NoChampion, // ��ս��Ӣ��
    Champion19, // ��ķ��һ�ǣ�
    Champion21, // ε��һ�ǣ�
    Champion23  // ��ľľ��һ�ǣ�
};
constexpr ChampionCategory FOURTH_LEVEL[] = { // ս��Ӣ���ļ��۸����
    NoChampion, // ��ս��Ӣ��
    Champion25, // ��ɣ�ᣨһ�ǣ�
    Champion27  // ������˹��һ�ǣ�
};
constexpr ChampionCategory FIFTH_LEVEL[] = { // ս��Ӣ���弶�۸����
    NoChampion, // ��ս��Ӣ��
    Champion29  // ��ɯ��һ�ǣ�
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
    {Champion17, CHAMPION_17_ATTR}, // ���˿��һ�ǣ�
    {Champion18, CHAMPION_18_ATTR}, // ���˿�����ǣ�
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

// ����뻶ӭ��ʾ���ֵ��
const std::map<int, std::string> WELCOME_PROMPT = {
    {0,  u8"���賿�ã����ǻ��ڣ���Ҳ�ڣ���Ϸ֮�õȴ�����."},
    {1,  u8"���賿�ã�ҹ�������������Ϸ������չ��."},
    {2,  u8"���賿�ã����ⰲ��ʱ�̣�����һ��̽���λ�֮��."},
    {3,  u8"���賿�ã���Ϸ�������ǹ��¸�������."},
    {4,  u8"���賿�ã��µ�һ�켴����ʼ��������һ��ӭ��."},
    {5,  u8"���賿�ã�����Ϸ��������ճ�ʱ��."},
    {6,  u8"�����Ϻã��µ�һ�죬�������ã��µ���ս�ڵȴ�."},
    {7,  u8"�����Ϻã�����Ϸ��ɫ�ʰ�������峿."},
    {8,  u8"�����Ϻã�һ������Ϸ�ĺ����к��а�."},
    {9,  u8"������ã��޾�������������ʱ�̵�����."},
    {10, u8"������ã����ʱ�̣�ÿһ���嶼����ʤ��."},
    {11, u8"������ã������ǰ����������Ӯ��һ��ʤ��."},
    {12, u8"������ã�����Ϣʱ�̣����ɲ�������Ϸ����Ȥ."},
    {13, u8"������ã�������͵�ʱ�⣬̽����Ϸ����������."},
    {14, u8"������ã������£������ǹ�ͬ̽��δ֪."},
    {15, u8"������ã�����������ʱ�䣬ȥ�����µ���Ϸ����."},
    {16, u8"������ã�������ǰ�������ǻ����ҫ."},
    {17, u8"������ã�������Ϸ������������ʱ��."},
    {18, u8"�����Ϻã�����Ϸ�����Ļƻ�ʱ��."},
    {19, u8"�����Ϻã����ǹ��½ҿ��µ���Ϸƪ��."},
    {20, u8"�����Ϻã���ħ�����������Ϸ����."},
    {21, u8"�����Ϻã�����������ҹ��ս������."},
    {22, u8"�����Ϻã��������ص�ʱ�̣�������Ϸ����."},
    {23, u8"�����Ϻã�ҹ���ˣ������¹⣬��ʼ�����Ϸ֮��."},
    {24, u8"�����ǻ۵Ļ������������������ҫ."},
    {25, u8"����ӭ���������ð����ʱ����."},
    {26, u8"����Ϸ���绶ӭ�㣬������."},
    {27, u8"��Ӣ�ۣ�׼����������ӣ�Ӯȡ���յ�ʤ��!"},
    {28, u8"�����ǳ�ͬ�У�̽�����޿���."},
    {29, u8"��ս��δͣ������������д."},
    {30, u8"��������������ÿһ��ս����������ϲ."},
    {31, u8"��Ӣ�۹�����ð��������."},
    {32, u8"����Ϸ���ÿһ�죬�����µĹ���."},
    {33, u8"��ħ���������̽�����漣��������."},
    {34, u8"��������ʵ���㣬��Ϸ����Ĺ��¿�ʼ."},
    {35, u8"��ð���޽��ޣ�ÿһ�ε�¼�����¿�ʼ."},
    {36, u8"���¸ҵ�̽���ߣ��µ��漣���㷢��."},
    {37, u8"��ÿһ����Ϸ�����Ƕ�δ֪������."},
    {38, u8"����Խ���ޣ���ÿһ�γ��Զ���ҫ."},
    {39, u8"���ս�������ð�յ�·���㲻�µ�."},
    {40, u8"�����ǻ��£���д���Ӣ�۴�˵."},
    {41, u8"���´����ģ�ÿһ�����綼����Ĵ�˵."},
    {42, u8"����������������ͣ������ֻ�����ֵ�����."},
    {43, u8"�������������磬�������ǳ���Ӣ��."},
    {44, u8"����Ƥ�ľ����Ѿ�͵������Ϸ���ܣ�׷!"},
    {45, u8"��׼�������������ϵ�Ӣ��������������ٻ�."},
    {46, u8"�����������ս���ϣ�ÿһ�����ǲ��ԵĿ���."},
    {47, u8"�����Դ�ʦ�������㽫��ε߸����?"}
};

#endif // !_CONSTANT_H_