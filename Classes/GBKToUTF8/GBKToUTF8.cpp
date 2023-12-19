/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     GBKToUTF8.cpp
 * File Function: GBKToUTF8类的实现
 * Author:        林继申
 * Update Date:   2023/12/20
 ****************************************************************/

#include <vector>
#include <stdexcept>
#include "GBKToUTF8.h"

// GBK 编码转换 UTF8 编码
std::string GBKToUTF8::getString(const std::string& gbkStr)
{
    // 打开 iconv 转换句柄，从 GBK 编码转换到 UTF8 编码
    iconv_t iconvH = iconv_open("utf-8", "gb2312");
    if (iconvH == (iconv_t)-1) {
        throw std::runtime_error("Error: Failed to open iconv.");
    }

    // 准备输入和输出缓冲区
    size_t inBytesLeft = gbkStr.size();
    size_t outBytesLeft = inBytesLeft * 4;
    std::vector<char> outbuf(outBytesLeft, 0);
    char* outPtr = outbuf.data();
    const char* inPtr = gbkStr.c_str();

    // 进行编码转换
    if (iconv(iconvH, &inPtr, &inBytesLeft, &outPtr, &outBytesLeft) == (size_t)-1) {
        iconv_close(iconvH);
        throw std::runtime_error("Error: Failed to convert GBK to UTF-8.");
    }
    iconv_close(iconvH);

    // 返回转换后的 UTF8 字符串
    return static_cast<std::string>(outbuf.data());
}