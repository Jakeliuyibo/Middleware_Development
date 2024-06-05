#pragma once
#include <iostream>
#include <utility>

namespace utility
{
    /**
     * @description: 红黑树节点颜色类型
     */    
    enum RBColor
    {
        RED = 0,
        BLACK = 1
    };

    /**
     * @description: 红黑树节点
     */
    template<class K, class V>
    struct RBTreeNode
    {
        RBTreeNode<K, V> *parent;
        RBTreeNode<K, V> *left, *right;
        RBColor color;
        std::pair<K, V> kv;
        RBTreeNode(const std::pair<K, V> &kv)
            : kv(kv)
            , color(RED)
            , parent(nullptr)
            , left(nullptr)
            , right(nullptr)
        { }
    };

    class rbtree
    {
        public:


        private:

    };

}