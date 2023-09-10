#include "timer.h"

using namespace utility;

/**
 * @description: 构造函数
 */
Timer_BasedOnThread::Timer_BasedOnThread() : m_active(false), m_period(0), m_repeat(-1)
{
}
Timer_BasedOnThread::Timer_BasedOnThread(int repeat) : m_active(false), m_period(0), m_repeat(repeat)
{
}

/**
 * @description: 析构函数
 */
Timer_BasedOnThread::~Timer_BasedOnThread()
{
    stop();
}

/**
 * @description: 关闭定时器
 */
void Timer_BasedOnThread::stop()
{
    m_active = false;
}