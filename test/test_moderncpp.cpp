#include <iostream>
#include <map>
#include <charconv>
#include <string>
#include "gtest\gtest.h"

using namespace std;

/*
 * 特性：原始字符串
 */
TEST(CPP11_FEATURE, ORIGIN_STRING)
{
    cout << "abcdefg\r\n" << endl;
    cout << R"(abcdefg\r\n)" << endl;
}

/*
 * 特性：NullPtr
 */
TEST(CPP11_FEATURE, NULLPTR)
{
    void* p1 = NULL;
    void* p2 = nullptr;
    cout << typeid(p1).name() << endl;
    cout << typeid(p2).name() << endl;
}

/*
 * 特性：Constexpr
 */
constexpr int f(int x)
{
    return x + 1;
}
TEST(CPP11_FEATURE, CONSTEXPR)
{
    const int a = f(1);
    // constexpr int b = f(2);
    cout << "a = " << a << endl;
    // cout << "b = " << b << endl;
}

/*
 * 特性：Auto 自动推导
 * 注意事项：1、推导必须赋初值
 *          2、不能定义数组
 */
TEST(CPP11_FEATURE, AUTO)
{
    auto a = 1, b = 2;
    EXPECT_STREQ(typeid(a).name(), typeid(b).name());
}

/*
 * 特性：Decltype 类型推导
 */
void* GetMemory(size_t size)
{
    return malloc(size);
}

TEST(CPP11_FEATURE, DECLTYPE)
{
    auto a = 1, b = 2;
    decltype(a + b) c;
    EXPECT_STREQ(typeid(a).name(), typeid(c).name());
    EXPECT_STREQ(typeid(b).name(), typeid(c).name());

    cout << typeid(decltype(GetMemory)).name() << endl;
    cout << typeid(decltype(GetMemory(0))).name() << endl;
}

/*
 * 特性：Using 定义别名
 */
template<typename T>
struct MyMap1
{
    typedef map<int, T> mp;
};

template<typename T>
using MyMap2 = map<int, T>;

TEST(CPP11_FEATURE, USING)
{
    typedef int m_int1;
    using m_int2 = int;
    testing::StaticAssertTypeEq<m_int1, m_int2>();

    typedef void(*m_func1)(int, int);
    using m_func2 = void(*)(int, int);
    testing::StaticAssertTypeEq<m_func1, m_func2>();

    MyMap1<int>::mp mp1;
    mp1[1] = 1;
    cout << mp1[1] << endl;

    MyMap2<int> mp2;
    mp2[1] = 1;
    cout << mp2[1] << endl;
}

/*
 * 特性：Final 关键字
 * 用途：1、修饰类不可被继承
 *       2、修饰虚函数不可被子类重写
 */
class A final
{
public:
    A() { cout << "A()." << endl; }
    virtual void func() final { cout << "this is a." << endl; }
};

// class B : public A
// {
// public:
//     B() {cout << "B()." << endl;}
//     void func() {cout << "this is b." << endl;}
// };

/*
 * 特性：右值引用，资源转移，完美转发
 */
TEST(CPP11_FEATURE, RVALUE)
{
    class mString
    {
    public:
        mString() { cout << "mString()" << endl; }
        mString(mString& other) { cout << "mString(mString &other)" << endl; }
        mString(mString&& other) { cout << "mString(mString &&other)" << endl; }
        ~mString() { cout << "~mString()" << endl; }
    };

    mString c(std::move(mString()));
}

template<typename T>
void PrintValue(T& t) { cout << "左值 "; }
template<typename T>
void PrintValue(T&& t) { cout << "右值 "; }
template<typename T>
void TestForward(T&& t)
{
    PrintValue(t);
    PrintValue(std::move(t));
    PrintValue(std::forward<T>(t));
    cout << endl;
}

TEST(CPP11_FEATURE, FORWARD)
{
    int num = 222;
    TestForward(111);                     // 左 右 右
    TestForward(num);                   // 左 右 左
    TestForward(forward<int>(num));     // 左 右 右
    TestForward(forward<int&>(num));  // 左 右 左
    TestForward(forward<int&&>(num));   // 左 右 右
}

/*
 * 特性：返回类型后置
 */
template<typename T = int, typename U = double>
auto add(T t = 0, U u = 0) -> decltype(t + u)
{
    return t + u;
}

TEST(CPP11_FEATURE, RETURN)
{
    int a = 1;
    double b = 2.2;
    cout << "res = " << add(a, b) << endl;
    cout << "type = " << typeid(add(a, b)).name() << endl;
    cout << "type = " << typeid(add(1, 2)).name() << endl;
    cout << "type = " << typeid(add(1.1, 1.2)).name() << endl;
    cout << "type = " << typeid(add('a', 'b')).name() << endl;
    cout << "type = " << typeid(add()).name() << endl;
}

/*
 * 特性：继承构造函数
 */
TEST(CPP11_FEATURE, JICHENG)
{
    class TA
    {
    public:
        TA(int _a1 = 1, int _a2 = 2) : a1(_a1), a2(_a2) { cout << "this is TA." << endl; }
        int a1 = 0;
        int a2 = 0;
    };

    class TB : public TA
    {
    public:
        using TA::TA;
        void print() { cout << "a1 = " << a1 << endl; cout << "a2 = " << a2 << endl; }
    };

    TB obj(3, 2);
    obj.print();
}

/*
 * 特性：initializer_list 轻量级容器类型，用于指定类型的参数传递
 */
template<typename T>
void func_il(std::initializer_list<T> args)
{
    cout << "list : ";
    for (auto& it : args)
    {
        cout << it << " ";
    }
    cout << endl;
}

TEST(CPP11_FEATURE, INITIALIZERLIST)
{
    func_il<int>({ 1,2,3 });
}

/*
 * 特性：functional 可调用对象包装器
 */
int mAdd(int a, int b)
{
    return a + b;
}

class mFuncA
{
public:
    static int madd(int a, int b) { return a + b; }
    int madd2(int a, int b) { return a + b; }
};

TEST(CPP11_FEATURE, FUNCTIONAL)
{
    std::function<int(int, int)> func_add1 = mAdd;
    auto func_add2 = mAdd;
    std::function<int(int, int)> func_add3 = mFuncA::madd;
    EXPECT_EQ(3, func_add1(1, 2));
    EXPECT_EQ(30, func_add2(10, 20));
    EXPECT_EQ(300, func_add3(100, 200));
}

TEST(CPP11_FEATURE, BIND)
{
    auto f1 = std::bind(mAdd, placeholders::_1, placeholders::_2);
    auto f2 = std::bind(mFuncA::madd, placeholders::_1, placeholders::_2);
    mFuncA fa;
    auto f3 = std::bind(&mFuncA::madd2, &fa, placeholders::_1, placeholders::_2);
    EXPECT_EQ(3, f1(1, 2));
    EXPECT_EQ(30, f2(10, 20));
    EXPECT_EQ(300, f3(100, 200));
}

/*
 * 特性：lambda表达式 [capture](params) opt -> ret {body;};
 * 细节：1、捕捉：[]:不捕捉 [&]引用捕捉 [=]值捕捉 [this]捕捉当前类中的this指针
 *       2、[=]值捕捉的变量默认不能修改，添加mutable关键字可以修改
 *       3、lamdba在c++11被看作是带operator()的类，即仿函数。因此operator()默认是const的，需要通过mutable关键字修改权限。
 */
TEST(CPP11_FEATURE, LAMDBA)
{
    int a = 100;
    auto func_add =
        [&](int b)
        {
            return a + b;
        };
    auto func_bind = std::bind(func_add, std::placeholders::_1);

    EXPECT_EQ(300, func_add(200));
    EXPECT_EQ(300, func_bind(200));
}

/*
 * 特性：static_assert 静态断言
 */
TEST(CPP11_FEATURE, STATICASSERT)
{
    static_assert(sizeof(long) == 4, "32bit os.");
}

/*
 * 特性：friend 友元
 */
TEST(CPP11_FEATURE, FRIEND)
{
    class Resource
    {
        friend class GoodFriend;

    public:
        int a = 1;
    private:
        int b = 2;
    };

    class GoodFriend
    {
    public:
        void print_resource(Resource& r)
        {
            cout << "a = " << r.a << ", b = " << r.b << endl;
        }
    };
    Resource r;
    GoodFriend gf;
    gf.print_resource(r);
}

/*
 * 特性：protected 保护的权限
 */
TEST(CPP11_FEATURE, PROTECTED)
{
    class PA
    {
    public:
        int a = 1;
    protected:
        int b = 2;
    private:
        int c = 2;
    };

    class PB : protected PA
    {
    public:
        void print_resource()
        {
            cout << "a = " << a << endl;
            cout << "b = " << b << endl;
            // cout << "c = " << c << endl;
        }
    };

    class PC : private PB
    {
    public:
        void print_resource()
        {
            cout << "a = " << a << endl;
            cout << "b = " << b << endl;
            // cout << "c = " << c << endl;
        }
    };

    class PD : PC
    {
    public:
        void print_resource()
        {
            // cout << "a = " << a << endl;
            // cout << "b = " << b << endl;
            // cout << "c = " << c << endl;
        }
    };

    PB pb;
    PC pc;
    PD pd;
    pb.print_resource();
    pc.print_resource();
    pd.print_resource();
}

/*
 * 特性：enum 强枚举类型
 */
TEST(CPP11_FEATURE, STRONG_ENUM)
{
    enum class School : int
    {
        student = 1,
        teacher,
        worker,
    };

    cout << "type = " << typeid(School::student).name() << endl;
    cout << "type = " << typeid(School::teacher).name() << endl;
}

/*
 * 特性：... 可变参数模板
 */
template<typename... Args>
struct Count
{
    static const std::size_t value() { return sizeof...(Args); }
};

template<typename T, typename... Args>
void UnPack(T&& t, Args&&... args)
{
    cout << "this is: " << t << endl;

    if constexpr (sizeof...(args) > 0)
    {
        UnPack(args...);
    }
}

template<typename... Args>
void ShowAllLists(Args&&... args)
{
    cout << "sizeof = " << Count<Args...>::value() << endl;
    UnPack(args...);
}

struct VP_X
{
    int i;
    std::string s;
    double d;
};

template<class...Args>
void ShowAllLists1(Args...args)
{
    VP_X x = { args... };
    std::cout << "i:" << x.i << ", s:" << x.s << ", d:" << x.d << std::endl;
}

TEST(CPP11_FEATURE, VARIABLE_PARAM)
{
    ShowAllLists(1, 2, 3, "abc", "d", 'e');
    ShowAllLists1(1, "*", 54.12);
}

/*
 * 特性：变量模板
 */
template<class T>
constexpr T pi = 3.1415926;

TEST(CPP14_FEATURE, VALUE_TEMPLATE)
{
    cout << pi<int> << endl;
    cout << pi<double> << endl;
}

/*
 * 特性：可能会被丢弃
 */
TEST(CPP14_FEATURE, DEPRECATED)
{
    struct [[deprecated]] AAAA { };
    AAAA a;
}

/*
 * 特性：整数序列
 */
template<typename T>
void print(T t)
{
    std::cout << t << ' ';
}

template<typename... Args, std::size_t... Is>
void printAll(std::index_sequence<Is...>, Args... args)
{
    (print(args), ...);
}

template<typename... Args>
void printAll(Args... args)
{
    printAll(std::index_sequence_for<Args...>{}, args...);
    cout << endl;
}

template<typename T, T... Ints>
void print_seq(std::integer_sequence<T, Ints...>)
{
    ((std::cout << Ints << ' '), ...);
    cout << endl;
}

TEST(CPP14_FEATURE, INTEGER_SEQUENCE)
{
    auto seq = std::make_integer_sequence<int, 5>{};
    print_seq(seq);
    printAll(1, "apple", 3.14, 'c');
}

/*
 * 特性：折叠表达式
 * 一元：(pack op ...) == EP1 op ( ... op (EN-1 op EN))
 * 二元：(pack op ... op init) == EP1 op ( ... op (EN-1 op (EN op Init)))
 */
template <typename... Args>
auto exp_sum(Args&&... args) -> decltype((args + ... + 0))
{
    return (args + ... + 0);
}

TEST(CPP17_FEATURE, PACK_EXPRESSION)
{
    EXPECT_EQ(10, exp_sum(1, 2, 3, 4));
}

/*
 * 特性：结构化绑定
 */
TEST(CPP17_FEATURE, STRUCT_BINDING)
{
    std::pair p{ 1, 2.3f };
    auto& [i, f] = p;
    EXPECT_EQ(i, 1);
    EXPECT_EQ(f, 2.3f);
    int arr[3] = { 1, 2, 3 };
    auto [a, b, c] = arr;
    cout << "a: " << a << " b: " << b << " c: " << c << endl;
}

/*
 * 特性：IF-SWTICH
 */
TEST(CPP17_FEATURE, IF_SWITCH)
{
    if (auto flag = true; flag)
    {
        EXPECT_TRUE(flag);
    }

    switch (auto flag1 = true; flag1)
    {
        case true:
            EXPECT_TRUE(flag1);
            break;
        default:
            EXPECT_TRUE(flag1);
            break;
    }
}

/*
 * 特性：NAMESPACE
 */
namespace NA::NB::NC
{
    struct Test
    {
        int inline static i = 1;
    };
}

TEST(CPP17_FEATURE, NAMESPACE)
{
    EXPECT_EQ(NA::NB::NC::Test::i, 1);
}

/*
 * 特性：HAS_INCLUDE
 */
#if __has_include("gtest\gtest-spi.h")
#include "gtest\gtest-spi.h"
#define TEST_HAS_INCLUDE true
#else
#define TEST_HAS_INCLUDE flase
#endif
TEST(CPP17_FEATURE, HAS_INCLUDE)
{
    EXPECT_TRUE(TEST_HAS_INCLUDE);
}

/*
 * 特性：Attribute
 */
[[noreturn]] int test_attribute() { return 0; }
TEST(CPP17_FEATURE, ATTRIBUTE)
{
    switch (int a = 1; a)
    {
        case 1:
            a++;
            [[fallthrough]]; // 直接下落的警告消除
        case 2:
            cout << "a = " << a << endl;
            EXPECT_EQ(a, 2);
            break;
    }

    test_attribute();
}

/*
 * 特性：字符串转换
 */
TEST(CPP17_FEATURE, CHARS_TRANSFER)
{
    const string str{ "123445" };
    int value = 0;
    auto res = std::from_chars(str.data(), str.data() + 6, value);
    cout << "val: " << value << endl;

    double d = 12.34;
    string str1 = "xxxxxxx";
    auto res1 = std::to_chars(str1.data(), str1.data() + 5, d);
    cout << "str1: " << str1 << endl;
}

/*
 * 特性：VARIANT
 */
TEST(CPP17_FEATURE, VARIANT)
{
    std::variant<int, string> var("hello");

    auto str = std::get<string>(var);
    cout << "index: " << var.index() << " str: " << str << endl;

    var = 123;
    auto i = std::get<int>(var);
    cout << "index: " << var.index() << " i: " << i << endl;
}

/*
 * 特性：VARIANT
 */
TEST(CPP17_FEATURE, ANY)
{
    any a = 1;
    cout << a.type().name() << " " << any_cast< int >(a) << endl;
    a = 2.2f;
    cout << a.type().name() << " " << any_cast< float >(a) << endl;
    EXPECT_TRUE(a.has_value());
    a.reset();
    EXPECT_FALSE(a.has_value());
}

/*
 * 特性：apply
 */
TEST(CPP17_FEATURE, APPLY)
{
    auto add_lambda = [](auto first, auto second) { return first + second; };

    EXPECT_EQ(std::apply(add_lambda, std::tuple(2.0f, 3.0f)), 5.0f);
}

/*
 * 特性：make_from_typle
 */
TEST(CPP17_FEATURE, MAKE_FROM_TUPLE)
{
    struct Foo {
        Foo(int _a, float _b, double _c, char _d, string _e) {
            std::cout << "_a: " << _a << ", _b: " << _b << ", _c: " << _c << ", _d: " << _d << ", _e: " << _e << endl;
        }
    };
    std::make_from_tuple<Foo>(std::move(std::make_tuple(1, 2.1, 3.2, 'c', "123")));
}

/*
 * 特性：as_const
 */
TEST(CPP17_FEATURE, AS_CONST)
{
    string str = "hello world";
    const string& const_str = as_const(str);
    cout << "str.type  = " << typeid(str).name() << endl;
    cout << "cstr.type = " << typeid(const_str).name() << endl;
}


/*
 * 特性：
 */
TEST(CPP20_FEATURE, TODO)
{
    //todo 
}