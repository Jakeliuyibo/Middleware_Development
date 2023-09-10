#include "timer.h"

using namespace utility;

/**
 * @description: 构造函数
 */
Timer_BasedOnScheduler::Timer_BasedOnScheduler() : m_period(0), m_repeat(-1)
{
    m_time = now();
}
Timer_BasedOnScheduler::Timer_BasedOnScheduler(int repeat) : m_period(0), m_repeat(repeat)
{
    m_time = now();
}

/**
 * @description: 析构函数
 */
Timer_BasedOnScheduler::~Timer_BasedOnScheduler()
{
}

/**
 * @description: 定时器触发执行任务
 */
void Timer_BasedOnScheduler::on_timer()
{
    if (!m_func || m_repeat == 0)
    {
        return;
    }

    m_func();
    m_time += m_period;
    if (m_repeat > 0)
    {
        m_repeat--;
    }
}

/**
 * @description: 获取系统时间，单位ms
 */
int64_t Timer_BasedOnScheduler::now()
{
    /* 获取当前时间戳   */
    auto now = std::chrono::system_clock::now();
    /* 将时间戳转换成毫秒数 */
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    return now_ms.time_since_epoch().count();
}

/**
 * @description: 更新时间线
 */
void TimerManager::update()
{
    if (m_timers.empty()) {
        return;
    }

    int64_t now = Timer_BasedOnScheduler::now();
    for(auto it = m_timers.begin(); it != m_timers.end(); ) {
        if (it->first > now) {
            return;
        }
        // 执行调用函数
        it->second.on_timer();

        // 检测下次执行
        Timer_BasedOnScheduler t = it->second;
        it = m_timers.erase(it);
        if (t.m_repeat != 0) {
            auto new_it = m_timers.insert(std::make_pair(t.m_time, t));
            if (it == m_timers.end() || new_it->first < it->first) {
                it = new_it;
            }
        }
    }
}