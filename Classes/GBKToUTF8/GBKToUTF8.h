/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     GBKToUTF8.h
 * File Function: GBKToUTF8类的定义
 * Author:        林继申
 * Update Date:   2023/12/20
 ****************************************************************/

#pragma once
#ifndef _GBK_TO_UTF8_H_
#define _GBK_TO_UTF8_H_

#pragma comment(lib, "libiconv.lib")
#include <string>
#include "win32-specific/icon/include/iconv.h"

/*
 * Class Name:     GBKToUTF8
 * Class Function: GBK 编码转换类
 */
class GBKToUTF8 {
public:
    // GBK 编码转换 UTF8 编码
    static std::string getString(const std::string& gbkStr);
};

#endif // !_GBK_TO_UTF8_H_