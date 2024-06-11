#pragma once

#include <iostream>
#include <cassert>
#include <stdexcept>
#include <array>
#include <vector>
#include <memory>

namespace utility
{

    template <typename T>
    class SlotMap
    {
        using size_t = std::size_t;
        static const size_t s_init_capacity = 8; // 初始容量
        static const size_t s_grow_factory = 2;  // 增长倍数

    public:
        /* using */
        using ValueType = T;
        using StorageKeyType = std::vector<size_t>;
        using StorageValueType = std::vector<ValueType>;

    public:
        /* Constructors and destructors */
        SlotMap();
        SlotMap(const SlotMap&) = delete;
        SlotMap& operator=(const SlotMap&) = delete;
        SlotMap(SlotMap&&) = default;
        SlotMap& operator=(SlotMap&&) = default;

        ~SlotMap() {}

    public:
        /* open interface */
        // 获取大小
        [[nodiscard]] constexpr auto GetSize() const noexcept { return size_; }
        // 获取容量
        [[nodiscard]] constexpr auto GetCapacity() const noexcept { return capacity_; }

        // 迭代器操作
        // const T* begin() {return data_.begin();}
        // const T* end() {return data_.end();}

        // 重载索引
        // todo 存在安全问题，idx可能超出限制
        T& operator[](size_t idx) { return reinterpret_cast< T& >(data_[idx]); }
        const T& operator[](size_t idx) const { return reinterpret_cast< T& >(data_[idx]); }

        // 插入值
        [[nodiscard]] size_t Insert(const T& val);
        [[nodiscard]] size_t Insert(T&& val);

        // 擦除值
        // todo 存在安全问题，idx可能被释放
        bool Erase(size_t idx);

        // 清除与重置
        void Clear();
        void Reset();

    private:
        // 是否溢出
        bool IsFull() const noexcept { return size_ >= capacity_; }
        // 是否有空余位置
        bool HasFreeSize() const noexcept { return freeSize_ > 0; }
        // 计算扩张一次后的容量
        size_t CalNextCapacity() const noexcept { return capacity_ == 0 ? s_init_capacity : capacity_ * s_grow_factory; }
        // 扩张容量
        void Grow();
        // 插入到末尾
        size_t InsertAtBack(T&& val);
        // 插入到空闲位置
        size_t InsertAtFreeIdx(T&& val);

    public:
        /* data */
        std::unique_ptr<StorageValueType> data_;
        std::unique_ptr<StorageKeyType> freeIndices_;

        size_t size_{ 0 };
        size_t last_{ 0 };
        size_t freeSize_{ 0 };
        size_t capacity_{ 0 };

        void print_data()
        {
            using namespace std;
            cout << "data array: ";
            for (auto idx = 0; idx < capacity_; idx++)
            {
                cout << "[" << idx << "]:" << (*data_)[idx] << " ";
            }
            cout << endl;
        }
        void print_freeindices()
        {
            using namespace std;
            cout << "freeindices array: ";
            for (auto idx = 0; idx < freeSize_; idx++)
            {
                cout << "[" << idx << "]:" << (*freeIndices_)[idx] << " ";
            }
            cout << endl;
        }
    };

    // 构造函数
    template <typename T>
    SlotMap<T>::SlotMap() : data_(std::make_unique<StorageValueType>(0)),
        freeIndices_(std::make_unique<StorageKeyType>(0))
    {
    }

    // 插入值
    template <typename T>
    [[nodiscard]] typename SlotMap<T>::size_t SlotMap<T>::Insert(const T& val)
    {
        return Insert(std::move(val));
    }

    template <typename T>
    [[nodiscard]] typename SlotMap<T>::size_t SlotMap<T>::Insert(T&& val)
    {
        if (IsFull()) /* 判定容量是否溢出 */
        {
            Grow();
        }

        if (HasFreeSize()) /* 判定Free是否有剩余位置 */
        {
            return InsertAtFreeIdx(std::move(val));
        }
        else
        {
            return InsertAtBack(std::move(val));
        }
    }

    // 扩张容量
    template <typename T>
    void SlotMap<T>::Grow()
    {
        /* 分配新内存空间 */
        size_t new_capacity = CalNextCapacity();
        std::unique_ptr<StorageValueType> new_data = std::make_unique<StorageValueType>(new_capacity);
        std::unique_ptr<StorageKeyType> new_freeIndices = std::make_unique<StorageKeyType>(new_capacity);

        /* 转移资源 */
        /* 扩张时Free数组为空，不用转移 */
        for (size_t idx = 0; idx < capacity_; idx++)
        {
            (*new_data)[idx] = std::move((*data_)[idx]);
            (*data_)[idx].~T();
        }

        /* 使用新的存储空间 */
        capacity_ = new_capacity;
        data_ = std::move(new_data);
        freeIndices_ = std::move(new_freeIndices);
    }

    // 插入到末尾
    template <typename T>
    typename SlotMap<T>::size_t SlotMap<T>::InsertAtBack(T&& val)
    {
        new (&((*data_)[last_++])) T(std::move(val));
        return ++size_;
    }

    // 插入到空闲位置
    template <typename T>
    typename SlotMap<T>::size_t SlotMap<T>::InsertAtFreeIdx(T&& val)
    {
        size_t nextFreeIdx = (*freeIndices_)[--freeSize_];
        new (&((*data_)[nextFreeIdx])) T(std::move(val));
        ++size_;

        return nextFreeIdx;
    }

    // 擦除值
    template <typename T>
    bool SlotMap<T>::Erase(typename SlotMap<T>::size_t idx)
    {
        if (idx > capacity_)
        {
            return false;
        }

        /* 判定擦除是否最后一个元素 */
        if (idx == (last_ - 1))
        {
            --last_;
        }
        else
        {
            (*freeIndices_)[freeSize_++] = idx;
        }

        ((*data_)[idx]).~T();

        --size_;
        return true;
    }

}
