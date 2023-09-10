#pragma once

#include <iostream>
#include <thread>
#include <functional>
#include <atomic>
#include <chrono>
#include <map>
#include <memory>
#include "singleton.h"

namespace utility
{
    class Timer_BasedOnThread
    {
    public:
        Timer_BasedOnThread();
        Timer_BasedOnThread(int repeat);
        ~Timer_BasedOnThread();
        // 启动定时器
        template <typename F, typename... Args>
        void start(int millisecond, F &&f, Args &&...args);
        // 关闭定时器
        void stop();

    private:
        std::thread m_thread;         // 子线程
        std::atomic<bool> m_active;   // 运行状态
        std::function<void()> m_func; // 运行函数
        int m_period;                 // 运行周期，单位ms
        int m_repeat;                 // 重复次数，-1：无限，1-n：剩余运行次数
    };

    // 启动定时器
    template <typename F, typename... Args>
    void Timer_BasedOnThread::start(int millisecond, F &&f, Args &&...args)
    {
        /* 检测是否已激活   */
        if (m_active)
        {
            return;
        }

        m_period = millisecond;
        m_func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        m_active = true;
        m_thread = std::thread([&]()
                                {
            if (m_repeat < 0) {
                while(m_active) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(m_period));
                    if (!m_active) {
                        return;
                    }
                    m_func();
                }
            }
            else {
                while (m_repeat > 0) {
                    if (!m_active) {
                        return;
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(m_period));
                    if (!m_active) {
                        return;
                    }
                    m_func();
                    m_repeat--;
                }
            } });
        m_thread.detach();
    }
}

namespace utility
{
    class Timer_BasedOnScheduler
    {
        friend class TimerManager;

    public:
        Timer_BasedOnScheduler();
        Timer_BasedOnScheduler(int repeat);
        ~Timer_BasedOnScheduler();

        // 启动定时器
        template <typename F, typename... Args>
        void callback(int millisecond, F &&f, Args &&...args);
        // 定时器触发执行任务
        void on_timer();

    private:
        // 获取系统时间，单位ms
        static int64_t now();

    private:
        int64_t m_time;               // 定时器触发时间点，单位ms
        std::function<void()> m_func; // 运行函数
        int m_period;                 // 运行周期，单位ms
        int m_repeat;                 // 重复次数，-1：无限，1-n：剩余运行次数
    };

    // 启动定时器
    template <typename F, typename... Args>
    void Timer_BasedOnScheduler::callback(int millisecond, F &&f, Args &&...args)
    {
        m_period = millisecond;
        m_func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    }

    class TimerManager
    {
        SINGLETON(TimerManager);
    public:
        // 调度Timer
        template <typename F, typename... Args>
        void schedule(int milliseconds, F &&f, Args &&...args);
        // 调度Timer
        template <typename F, typename... Args>
        void schedule(int milliseconds, int repeat, F &&f, Args &&...args);
        // 更新时间线
        void update();

    private:
        std::multimap<int64_t, Timer_BasedOnScheduler> m_timers;
    };
    // 调度Timer
    template <typename F, typename... Args>
    void TimerManager::schedule(int milliseconds, F &&f, Args &&...args)
    {
        schedule(milliseconds, -1, std::forward<F>(f), std::forward<Args>(args)...);
    }
    // 调度Timer
    template <typename F, typename... Args>
    void TimerManager::schedule(int milliseconds, int repeat, F &&f, Args &&...args)
    {
        Timer_BasedOnScheduler t(repeat);
        t.callback(milliseconds, std::forward<F>(f), std::forward<Args>(args)...);
        m_timers.insert(std::make_pair(t.m_time, t));
    }

}