/*
 * @Author: liuyibo 1299502716@qq.com
 * @Date: 2023-08-22 22:20:26
 * @LastEditors: liuyibo 1299502716@qq.com
 * @LastEditTime: 2023-08-23 22:26:27
 * @FilePath: \Middleware_Development\utility\systime\systime.h
 * @Description: 获取系统时间的接口声明
 */
#pragma once

#include <iostream>
#include <string>

using namespace std;

namespace utility {
class SysTime
{
public:
    SysTime()
    {
    }
    ~SysTime()
    {
    }
    // 获取系统时间
    string getSystime();
    // 获取系统时间，文件名格式
    string getSystimeByFilenameFormat();
};


}