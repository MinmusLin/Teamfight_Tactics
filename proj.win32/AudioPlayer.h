/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     AudioPlayer.h
 * File Function: ��Ƶ���淽���Ķ���
 * Author:        �ּ���
 * Update Date:   2023/12/29
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _AUDIO_PLAYER_H_
#define _AUDIO_PLAYER_H_

#include "AudioEngine.h"

// ��Ƶ��������
extern int g_backgroundMusicSign;
extern int g_effectMusicSign;
extern float g_backgroundMusicVolumn;
extern float g_effectMusicVolumn;

// ��Ƶ���淽��
void audioPlayer(const std::string& audioPath, bool isLoop);

#endif // !_AUDIO_PLAYER_H_