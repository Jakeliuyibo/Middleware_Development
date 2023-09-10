#pragma once


namespace utility
{
    template<typename T>
    class SmartPtr
    {
    public:
        SmartPtr() : m_ptr(nullptr) {}
        SmartPtr(T * p) : m_ptr(p) {}
        ~SmartPtr()
        {
            if (m_ptr != nullptr)
            {
                delete m_ptr;
                m_ptr = nullptr;
            }
        }
    private:
        T * m_ptr;
    };

    template<typename T>
    class AutoPtr
    {
    public:
        AutoPtr() : m_ptr(nullptr) {}
        AutoPtr(T * p) : m_ptr(p) {}
        AutoPtr(AutoPtr &other) : m_ptr(other.release()) {}
        ~AutoPtr()
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
        // 重置赋值运算符
        AutoPtr & operator = (AutoPtr<T> &other)
        {
            if (this == &other)
            {
                return *this;
            }
            reset(other.release());
            return *this;
        }
    private:
        T * m_ptr;
    };

}
