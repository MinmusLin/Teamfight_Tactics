/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     GBKToUTF8.cpp
 * File Function: GBKToUTF8类的实现
 * Author:        林继申
 * Update Date:   2023/12/5
 ****************************************************************/

#include "GBKToUTF8.h"
#include <vector>
#include <stdexcept>

// GBK 编码转换 UTF8 编码
std::string GBKToUTF8::getString(const std::string& gbkStr)
{
    iconv_t iconvH = iconv_open("utf-8", "gb2312");
    if (iconvH == (iconv_t)-1) {
        throw std::runtime_error("Error: Failed to open iconv.");
    }
    size_t inBytesLeft = gbkStr.size();
    size_t outBytesLeft = inBytesLeft * 4;
    std::vector<char> outbuf(outBytesLeft, 0);
    char* outPtr = outbuf.data();
    const char* inPtr = gbkStr.c_str();
    if (iconv(iconvH, &inPtr, &inBytesLeft, &outPtr, &outBytesLeft) == (size_t)-1) {
        iconv_close(iconvH);
        throw std::runtime_error("Error: Failed to convert GBK to UTF-8.");
    }
    iconv_close(iconvH);
    return std::string(outbuf.data());
}