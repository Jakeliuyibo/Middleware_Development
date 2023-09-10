/*
 * @Author: liuyibo 1299502716@qq.com
 * @Date: 2023-08-20 21:49:35
 * @LastEditors: liuyibo 1299502716@qq.com
 * @LastEditTime: 2023-08-23 22:45:04
 * @FilePath: \Middleware_Development\mlog\logger.cpp
 * @Description: 日志模块功能实现：单例模式
 */
#include "logger.h"
#include <iostream>
#include <stdexcept>
#include <string.h>
#include <stdarg.h>
#include <memory>
#include "systime.h"

using namespace std;
using namespace utility;

/**
 * @description: 日志等级字符串
 */
const char *Logger::s_level[LEVEL_COUNT] = {
    "DEBUG",
    "INFO",
    "WARNING",
    "ERROR",
    "FATAL",
};

/**
 * @description: 单例
 */
Logger *Logger::m_instance = nullptr;

/**
 * @description: 构造函数
 */
Logger::Logger() : m_level(DEBUG), m_maxSize(0), m_curSize(0)
{
}

/**
 * @description: 析构函数
 */
Logger::~Logger()
{
    close();
}

/**
 * @description: 返回单例指针
 */
Logger *Logger::instance()
{
    if (m_instance == nullptr)
    {
        m_instance = new Logger();
    }
    return m_instance;
}

/**
 * @description: 打开日志文件
 */
void Logger::open(const string &filename)
{
    /* 打开文件 */
    m_filename = filename;
    m_fout.open(filename, ios::app);
    if (m_fout.fail())
    {
        throw std::logic_error("open file failed " + filename);
    }

    /*获取文件大小  */
    m_fout.seekp(0, ios::end);
    m_curSize = m_fout.tellp();
}

/**
 * @description: 关闭日志文件
 */
void Logger::close()
{
    m_fout.close();
}

/**
 * @description: 打印日志
 * @param {Level} level
 * @param {char} *file
 * @param {int} line
 * @param {char *} format
 * @return {*}
 */
void Logger::log(Level level, const char *file, int line, const char *format, ...)
{
    /* 根据日志级别过滤 */
    if (level < m_level)
    {
        return;
    }

    /* 检测输出流是否异常 */
    if (m_fout.fail())
    {
        throw std::logic_error("open file failed " + m_filename);
    }

    /* 获取当前时间戳   */
    shared_ptr<SysTime> sysTime(new SysTime);
    string curSysTime = sysTime->getSystime();
    char timestamp[32];
    strcpy(timestamp, curSysTime.c_str());

    /* 构建日志条目 */
    // 写入信息
    const char *fmt = "%s %s %s:%d ";
    int size = snprintf(NULL, 0, fmt, timestamp, s_level[level], file, line);
    if (size > 0)
    {
        char *buffer = new char[size + 1];
        snprintf(buffer, size + 1, fmt, timestamp, s_level[level], file, line);
        buffer[size] = '\0';
        m_fout << buffer;
        m_curSize += size;
        delete buffer;
    }
    // 写入内容
    va_list arg_ptr;
    va_start(arg_ptr, format);
    size = vsnprintf(NULL, 0, format, arg_ptr);
    if (size > 0)
    {
        char *content = new char[size + 1];
        va_start(arg_ptr, format);
        vsnprintf(content, size + 1, format, arg_ptr);
        va_end(arg_ptr);
        m_fout << content;
        m_curSize += size;

        /* 终端输出 */
        std::cout << content << endl;

        delete content;
    }
    va_end(arg_ptr);
    // 换行并刷新磁盘写入
    m_fout << "\n";
    m_fout.flush();

    /* 检测日志是否超出长度 */
    if (m_maxSize > 0 && m_curSize > m_maxSize)
    {
        rotate();
    }
}

/**
 * @description: 日志超出限定大小，则进行翻转
 */
void Logger::rotate()
{
    /* 关闭当前文件 */
    close();

    /* 获取当前时间戳   */
    shared_ptr<SysTime> sysTime(new SysTime);
    string curSysTime = sysTime->getSystimeByFilenameFormat();
    char timestamp[32];
    strcpy(timestamp, curSysTime.c_str());

    /* 重命名关闭的文件 */
    string new_file_name = m_filename + timestamp;
    if (rename(m_filename.c_str(), new_file_name.c_str()) != 0)
    {
        throw std::logic_error("rename log file failed: " + string(strerror(errno)));
    }

    /* 重新打开新文件   */
    open(m_filename);
}