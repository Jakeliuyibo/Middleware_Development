#pragma once

#include <iostream>
#include <stdexcept>

using namespace std;

namespace utility
{

template <typename T>
class Vector
{
public:
    Vector();
    ~Vector();
    void push_back(const T &value); // 末尾添加元素
    void pop_back();                // 末尾取出元素
    T * data() const;               // 获取数据指针
    int size() const;               // 获取当前元素个数
    int capacity() const;           // 获取当前容量
    void show() const;              // 查看容器内部元素
    void reverse(int size);         // 重新分配容量满足size
    void resize(int size);          // 调整大小
    T & at(int index);              // 返回下标的引用
    T & operator[](int index);      // 重载括号，以下标访问
    bool empty() const;             // 判断是否为空
    void clear();                   // 移除所有元素
    T & front() const;              // 获取首个元素
    T & back() const;               // 获取末尾元素
    void swap(Vector<T> & other);   // 交换两个容器
    Vector<T> & operator = (const Vector<T> & other); // 赋值运算符重载

    class Iterator
    {
        public:
            Iterator() : m_pointer(nullptr) {}
            Iterator(T * p) : m_pointer(p) {}
            ~Iterator() {}
            // 运算符重载
            bool operator == (const Iterator &other)
            {
                return m_pointer == other.m_pointer;
            }
            bool operator != (const Iterator &other)
            {
                return m_pointer != other.m_pointer;
            }
            Iterator operator = (const Iterator &other)
            {
                m_pointer = other.m_pointer;
                return *this;
            }
            Iterator & operator ++ ()
            {
                m_pointer += 1;
                return *this;
            }
            Iterator operator ++ (int)
            {
                Iterator it = *this;
                ++(*this);
                return it;
            }
            Iterator operator + (int index) const
            {
                Iterator it = *this;
                it.m_pointer += index;
                return it;
            }
            Iterator operator - (int index) const
            {
                Iterator it = *this;
                it.m_pointer -= index;
                return it;
            }
            Iterator & operator += (int index)
            {
                m_pointer += index;
                return *this;
            }
            Iterator & operator -= (int index)
            {
                m_pointer -= index;
                return *this;
            }
            int operator - (const Iterator &other) const
            {
                return m_pointer - other.m_pointer;
            }
            T & operator * ()
            {
                return *m_pointer;
            }
            T * operator -> ()
            {
                return m_pointer;
            }
        private:
            T * m_pointer;
    };
    // STL 方法
    Iterator begin();
    Iterator end();
    Iterator find(const T &value);
    Iterator insert(const Iterator it, const T &value);
    Iterator insert(const Iterator it, int n, const T &value);
    Iterator erase(const Iterator it);
    Iterator erase(const Iterator start, const Iterator end);

private:
    void malloc_memory_and_copy_data(); // 分配新内存并拷贝数据到新内存
    void memory_expansize();        // 内存扩容
private:
    T *m_data;                      // 指针
    int m_size;                     // 当前大小
    int m_capacity;                 // 当前容量
};

template <typename T>
Vector<T>::Vector() : m_data(nullptr), m_size(0), m_capacity(0)
{

}

template <typename T>
Vector<T>::~Vector()
{
    if (m_data != nullptr)
    {
        delete [] m_data;
        m_data = nullptr;
    }
    m_size = 0;
    m_capacity = 0;
}

template <typename T>
void Vector<T>::push_back(const T &value)
{
    /* 检测是否需要扩容 */
    if (m_size >= m_capacity)
    {
        /* 2倍扩容 */
        memory_expansize();
        malloc_memory_and_copy_data();
    }

    /* 添加新元素 */
    m_data[m_size] = value;
    m_size++;
}

template <typename T>
void Vector<T>::pop_back()
{
    if (m_size > 0)
    {
        m_size -= 1;
    }
}

template <typename T>
T * Vector<T>::data() const
{
    return m_data;
}

template <typename T>
int Vector<T>::size() const
{
    return m_size;
}

template <typename T>
int Vector<T>::capacity() const
{
    return m_capacity;
}

template <typename T>
void Vector<T>::show() const
{
    std::cout << "capacity = " << capacity() << ", size = " << size() << std::endl;
    for(int idx=0; idx<m_size; idx++)
    {
        std::cout << m_data[idx] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void Vector<T>::reverse(int size)
{
    if (m_capacity >= size) {
        return;
    }

    /* 重新分配内存空间 */
    while(m_capacity < size)
    {
        memory_expansize();
    }
    malloc_memory_and_copy_data();
}

template <typename T>
void Vector<T>::resize(int size)
{
    if (m_size >= size) {
        m_size = size;
        return;
    }

    /* 检测是否需要扩容 */
    if (size > m_capacity) {
        while(m_capacity < size)
        {
            memory_expansize();
        }
        malloc_memory_and_copy_data();
    }
    // 填充默认元素
    for(int idx = m_size; idx < size; idx++)
    {
        m_data[idx] = T();
    }
    m_size = size;
}


template <typename T>
T & Vector<T>::at(int index)
{
    if (index < 0 || index >= m_size) {
        throw std::logic_error("out of range");
    }
    return m_data[index];
}

template <typename T>
T & Vector<T>::operator[](int index)
{
    return at(index);
}

template <typename T>
bool Vector<T>::empty() const
{
    return m_size == 0;
}

template <typename T>
void Vector<T>::clear()
{
    m_size = 0;
}

template <typename T>
T & Vector<T>::front() const
{
    if (empty())
    {
        throw std::logic_error("out of range");
    }
    return m_data[0];
}

template <typename T>
T & Vector<T>::back() const
{
    if (empty())
    {
        throw std::logic_error("out of range");
    }
    return m_data[m_size-1];
}

template <typename T>
void Vector<T>::swap(Vector<T> & other)
{
    T * tmp_data = other.m_data;
    int tmp_size = other.m_size;
    int tmp_capacity = other.m_capacity;

    other.m_data = m_data;
    other.m_size = m_size;
    other.m_capacity = m_capacity;

    m_data = tmp_data;
    m_size = tmp_size;
    m_capacity = tmp_capacity;
}

template <typename T>
Vector<T> & Vector<T>::operator = (const Vector<T> & other)
{
    /* 检测容量是否满足 */
    if (m_capacity < other.m_size) {
        if (m_data != nullptr)
        {
            delete [] m_data;
            m_data = nullptr;
            m_size = 0;
            m_capacity = 0;
        }
        // 动态扩容
        while(m_capacity < other.m_size)
        {
            memory_expansize();
        }
        m_data = new T[m_capacity];
    }

    /* 将other元素拷贝到cur */
    for(int idx=0; idx<other.size(); idx++)
    {
        m_data[idx] = other.m_data[idx];
    }
    m_size = other.m_size;
    return *this;
}


template <typename T>
void Vector<T>::malloc_memory_and_copy_data()
{
    // 申请新内存
    T *new_data = new T[m_capacity];
    // 拷贝旧内存到新内存
    for(int idx=0; idx<m_size; idx++)
    {
        new_data[idx] = m_data[idx];
    }
    // 删除旧内存
    if (m_data != nullptr) {
        delete [] m_data;
        m_data = nullptr;
    }
    // 指向新内存
    m_data = new_data;
}

template <typename T>
void Vector<T>::memory_expansize()
{
    if(m_capacity == 0) {
        m_capacity = 1;
    } else {
        m_capacity *= 2;
    }
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::begin()
{
    Vector<T>::Iterator it(m_data);
    return it;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::end()
{
    Vector<T>::Iterator it(m_data + m_size);
    return it;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::find(const T &value)
{
    for(auto it = begin(); it != end(); it++)
    {
        if (*it == value)
        {
            return it;
        }
    }
    return end();
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::insert(const Vector<T>::Iterator it, const T &value)
{
    return insert(it, 1, value);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::insert(const Vector<T>::Iterator it, int n, const T &value)
{
    int diff_size = it - begin();

    /* 检测是否需要扩容 */
    if ((m_size + n) > m_capacity) {
        while(m_capacity < (m_size + n))
        {
            memory_expansize();
        }
        malloc_memory_and_copy_data();
    }

    /* 拷贝元素 */
    // 先拷贝it后的元素
    for(int idx=(m_size+n-1); idx>=m_size; idx--)
    {
        m_data[idx] = m_data[idx - n];
    }
    // 拷贝n个value元素
    for(int idx=diff_size; idx<(diff_size + n); idx++)
    {
        m_data[idx] = value;
    }
    m_size += n;
    return Vector<T>::Iterator(m_data + diff_size);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::erase(const Vector<T>::Iterator it)
{
    /* 检测是否为末尾元素 */
    if((end() - it) == 1)
    {
        m_size -= 1;
        return end();
    }

    int diff_size = it - begin();
    for(int idx=diff_size; idx<m_size-1; idx++)
    {
        m_data[idx] = m_data[idx+1];
    }
    m_size -= 1;
    return it;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::erase(const Iterator start, const Iterator end)
{
    int f = start - begin();
    int e = end - begin();
    int n = end - start;
    /* 缓存拷贝 */
    for(int idx = f; idx < e; idx++)
    {
        m_data[idx] = m_data[idx + n];
    }

    m_size -= n;
    return start;
}




}


