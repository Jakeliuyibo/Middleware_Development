#pragma once


namespace utility
{

    template<typename T>
    class UniquePtr
    {
    public:
        UniquePtr() : m_ptr(nullptr) {}
        UniquePtr(T * p) : m_ptr(p) {}
        // 禁止拷贝构造函数
        UniquePtr(const UniquePtr<T> &other) = delete;
        // 移动构造函数
        UniquePtr(UniquePtr<T> && other) : m_ptr(other.release()) {}
        ~UniquePtr()
        {
            if (m_ptr != nullptr)
            {
                delete m_ptr;
                m_ptr = nullptr;
            }
        }
        // 获取实际指针
        T * get()
        {
            return m_ptr;
        }
        // 释放原指针，指向新指针
        T * release()
        {
            auto new_ptr = m_ptr;
            m_ptr = nullptr;
            return new_ptr;
        }
        // 重置指针
        void reset(T * new_ptr = nullptr)
        {
            if (m_ptr != new_ptr)
            {
                delete m_ptr;
                m_ptr = new_ptr;
            }
        }
        // 交换
        void swap(UniquePtr<T> & other)
        {
            auto new_ptr = other.m_ptr;
            other.m_ptr = m_ptr;
            m_ptr = new_ptr;
        }
        // 重载 -> 运算符
        T * operator -> ()
        {
            return m_ptr;
        }
        // 重载 * 运算符
        T & operator * ()
        {
            return *m_ptr;
        }
        // 重载 = 运算符
        UniquePtr & operator = (const UniquePtr<T> & other) = delete;
        UniquePtr & operator = (const UniquePtr<T> && other)
        {
            if (this == &other)
            {
                return *this;
            }
            reset(other.release());
            return *this;
        }
        // 重载 [] 运算符
        T & operator [] (int idx) const
        {
            return m_ptr[idx];
        }
        // 重载 bool 运算符
        explicit operator bool() const noexcept
        {
            return m_ptr != nullptr;
        }


    private:
        T * m_ptr;
    };

}