#pragma once

namespace utility
{

    template <typename T>
    class SharedPtr
    {
    public:
        // 构造函数
        SharedPtr() : m_ptr(nullptr), m_count(nullptr) {}
        SharedPtr(T *p) : m_ptr(p)
        {
            if (m_ptr != nullptr)
            {
                m_count = new int(1);
            }
        }
        // 拷贝构造函数
        SharedPtr(const SharedPtr<T> &other) : m_ptr(other.m_ptr), m_count(other.m_count)
        {
            if (m_ptr != nullptr)
            {
                (*m_count)++;
            }
        }
        // 移动构造函数
        SharedPtr(SharedPtr<T> &&other) noexcept : m_ptr(other.m_ptr), m_count(other.m_count)
        {
            other.m_ptr = nullptr;
            other.m_count = nullptr;
        }
        // 析构函数
        ~SharedPtr()
        {
            if (m_ptr != nullptr)
            {
                (*m_count)--;
                if ((*m_count) <= 0)
                {
                    delete m_ptr;
                    m_ptr = nullptr;
                    delete m_count;
                    m_count = nullptr;
                }
            }
        }
        // 获取实际指针
        T *get() const
        {
            return m_ptr;
        }
        // 重置指针
        void reset(T *new_ptr = nullptr)
        {
            if (m_ptr == new_ptr)
            {
                return;
            }

            if (m_ptr == nullptr)
            {
                if (new_ptr != nullptr)
                {
                    m_ptr = new_ptr;
                    m_count = new int(1);
                }
                return;
            }

            (*m_count)--;
            if ((*m_count) <= 0)
            {
                delete m_ptr;
                m_ptr = nullptr;
                delete m_count;
                m_count = nullptr;
            }
            m_ptr = new_ptr;
            if (new_ptr != nullptr)
            {
                m_count = new int(1);
            }
        }
        // 返回引用计数
        int use_count() const
        {
            if (m_ptr == nullptr)
            {
                return 0;
            }
            return *m_count;
        }
        // 判断是否独占
        bool unique() const
        {
            if (m_ptr == nullptr)
            {
                return false;
            }
            return (*m_count) == 1;
        }
        // 交换
        void swap(SharedPtr<T> &other)
        {
            auto tmp_ptr = other.m_ptr;
            auto tmp_count = other.m_count;
            other.m_ptr = m_ptr;
            other.m_count = m_count;
            m_ptr = tmp_ptr;
            m_count = tmp_count;
        }
        // 重载 -> 运算符
        T *operator->() const
        {
            return m_ptr;
        }
        // 重载 * 运算符
        T &operator*() const
        {
            return *m_ptr;
        }
        // 重载 bool 运算符
        explicit operator bool() const noexcept
        {
            return m_ptr != nullptr;
        }
        // 重载 = 运算符
        SharedPtr &operator=(const SharedPtr<T> &other)
        {
            if (this == &other)
            {
                return *this;
            }

            m_ptr = other.m_ptr;
            m_count = other.m_count;
            (*m_count)++;
            return *this;
        }
        SharedPtr &operator=(const SharedPtr<T> &&other)
        {
            if (this == &other)
            {
                return *this;
            }

            m_ptr = other.m_ptr;
            m_count = other.m_count;
            other.m_ptr = nullptr;
            other.m_count = nullptr;
            return *this;
        }
        // 重载 [] 运算符
        T &operator[](int idx) const
        {
            return m_ptr[idx];
        }

    private:
        T *m_ptr;
        int *m_count;
    };

}