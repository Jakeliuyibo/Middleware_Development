/*
 * @Author       : liuyibo
 * @Date         : 2024-06-04 19:51:26
 * @LastEditors  : liuyibo 1299502716@qq.com
 * @LastEditTime : 2024-06-05 14:20:19
 * @FilePath     : \Middleware_Development\utility\singleton_safe\singleton_safe.hpp
 * @Description  : 
 */
#pragma once
#include <iostream>
#include <cassert>

namespace utility
{
    /**
     * @description: 创建策略：使用new分配
     */
    template<class T>
    struct CreateUsingNew
    {
        static T* Create()
        {
            std::cout << "New Dynamic Create Object" << std::endl;
            return new T;
        }

        static void Destory(T *p)
        {
            std::cout << "Dynamic Destory Object" << std::endl;
            delete p;
        }
    };

    /**
     * @description: 创建策略：静态分配
     */
    template<class T>
    struct CreateStatic
    {
        union MaxAlign
        {
            char t_[sizeof(T)];
            short int si_;
            int i_;
            long int li_;
            float f_;
            double d_;
            long double ld_;
        };

        static T* Create()
        {
            static MaxAlign sm_;

            std::cout << "Static Create Object" << std::endl;
            return new(&sm_) T;
        }

        static void Destory(T *p)
        {
            std::cout << "Static Destory Object" << std::endl;
            p->~T();
        }
    };

    /**
     * @description: 安全的单例模式
     */
    template<
        typename T,
        template <class> class CreationPolicy = CreateUsingNew
    >
    class Singleton_Safe
    {
        public:
            typedef T objectType;

            static T& Instance();

        private:
            Singleton_Safe();
            static void MakeInstance();
            static void DestroyInstance();

        private:
            static T* pInstance_;
            static bool destroyed_;
    };

    // 设置变量初始值
    template<
        class T,
        template <class> class C
    >
    T* Singleton_Safe<T, C>::pInstance_ = nullptr;
    template<
        class T,
        template <class> class C
    >
    bool Singleton_Safe<T, C>::destroyed_ = false;

    // 获取实例
    template<   
        class T,
        template <class> class C
    >
    T& Singleton_Safe<T, C>::Instance()
    {
        if (!pInstance_)
        {
            MakeInstance();
        }
        return *pInstance_;
    }

    // 构造实例
    template<   
        class T,
        template <class> class C
    >
    void Singleton_Safe<T, C>::MakeInstance()
    {
        // todo 线程锁

        if (!pInstance_)
        {
            if (destroyed_)
            {
                destroyed_ = true;
            }

            pInstance_ = C<T>::Create();
        }
    }

    // 销毁实例
    template<   
        class T,
        template <class> class C
    >
    void Singleton_Safe<T, C>::DestroyInstance()
    {
        assert(!destroyed_);

        C<T>::Destory(pInstance_);
        pInstance_ = nullptr;
        destroyed_ = true;
    }

}
