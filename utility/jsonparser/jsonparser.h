#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

namespace utility
{


    class Json
    {
    public:
        enum Type
        {
            json_null = 0,
            json_bool,
            json_int,
            json_double,
            json_string,
            json_array,
            json_object
        };
        // 构造函数
        Json();
        Json(bool value);
        Json(int value);
        Json(double value);
        Json(const char *value);
        Json(const string &value);
        Json(Type type);
        Json(const Json &other);
        // 运算符重载
        operator bool();
        operator int();
        operator double();
        operator string();
        // 重载
        Json & operator [] (int index);
        Json & operator [] (const char *key);
        Json & operator [] (const string &key);
        void operator = (const Json &other);
        bool operator == (const Json &other);
        bool operator != (const Json &other);
        // 类型判断
        bool isNull()   const {return m_type == json_null;}
        bool isBool()   const {return m_type == json_bool;}
        bool isInt()    const {return m_type == json_int;}
        bool isDouble() const {return m_type == json_double;}
        bool isString() const {return m_type == json_string;}
        bool isArray()  const {return m_type == json_array;}
        bool isObject() const {return m_type == json_object;}

        bool asBool() const;
        int asInt() const;
        double asDouble() const;
        string asString() const;

        // 数组的相关函数
        void append(const Json &other);
        typedef std::vector<Json>::iterator iterator;
        iterator begin();
        iterator end();
        // 检测是否包含元素
        bool has(int index);            // 数组是否包含index下标元素
        bool has(const char *key);      // 对象是否包含Key
        bool has(const string &key);    // 对象是否包含Key
        // 删除元素
        void remove(int index);
        void remove(const char *key);
        void remove(const string &key);

        // 以字符串形式返回内容
        string str() const;
        // Json内存释放
        void clear();
    private:
        // Json拷贝
        void copy(const Json &other);
    private:
        union Value
        {
            bool m_bool;
            int m_int;
            double m_double;
            std::string *m_string;
            vector<Json> *m_array;
            map<string, Json> *m_object;
        };

        Type m_type;
        Value m_value;
    };

}