/*
 * @Author: liuyibo 1299502716@qq.com
 * @Date: 2023-08-20 21:50:20
 * @LastEditors: liuyibo 1299502716@qq.com
 * @LastEditTime: 2023-08-23 22:44:59
 * @FilePath: \Middleware_Development\mlog\logger.h
 * @Description: 日志模块接口
 */
#pragma once

#include <string>
#include <fstream>

using namespace std;

namespace utility
{

#define debug(format, ...) \
    Logger::instance()->log(Logger::DEBUG, __FILE__, __LINE__, format, ##__VA_ARGS__)

#define info(format, ...) \
    Logger::instance()->log(Logger::INFO, __FILE__, __LINE__, format, ##__VA_ARGS__)

#define warning(format, ...) \
    Logger::instance()->log(Logger::WARNING, __FILE__, __LINE__, format, ##__VA_ARGS__)

#define error(format, ...) \
    Logger::instance()->log(Logger::ERROR, __FILE__, __LINE__, format, ##__VA_ARGS__)

#define fatal(format, ...) \
    Logger::instance()->log(Logger::FATAL, __FILE__, __LINE__, format, ##__VA_ARGS__)

    class Logger
    {
    public:
        enum Level
        {
            DEBUG = 0,
            INFO,
            WARNING,
            ERROR,
            FATAL,
            LEVEL_COUNT
        };
        static Logger *instance();         // 返回单例
        void open(const string &filename); // 打开日志文件
        void close();                      // 关闭日志文件
        // 设置日志级别
        void setLevel(Level level)
        {
            m_level = level;
        }
        // 设置日志最长存储字节
        void setMaxSize(unsigned int bytes)
        {
            m_maxSize = bytes;
        }
        // 打印日志
        void log(Level level, const char *file, int line, const char *format, ...);

    private:
        Logger();
        ~Logger();
        void rotate(); // 日志超出限定大小，则进行翻转

    private:
        string m_filename;                       // 文件名
        ofstream m_fout;                         // 文件输出流
        Level m_level;                           // 输出等级
        unsigned int m_maxSize;                  // 最大日志记录大小
        unsigned int m_curSize;                  // 当前日志记录大小
        static const char *s_level[LEVEL_COUNT]; // 日志等级字符串
        static Logger *m_instance;               // 单例
    };

}