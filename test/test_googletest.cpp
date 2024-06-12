#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <map>
#include <unordered_map>
#include <chrono>
#include <gtest/gtest.h>

using namespace std;

/******************************************/
/************** 简单测试 *******************/
/******************************************/
int add(int a, int b)
{
    return a + b;
}

TEST(TEST_ADD, UNSIGNED_INT_VALUE)
{
    int res = add(100, 200);
    EXPECT_EQ(res, 300) << "invaild sub func";
}

/******************************************/
/************** 测试夹具 *******************/
/*********** test_fixture *****************/
/******************************************/

class mContainer
{
public:
    mContainer() : a(1), b(2) {}
    mContainer(int a_, int b_) : a(a_), b(b_) {}
    int getA() { return a; }
    int getB() { return b; }
    void modifyA(int a_) { a = a_; }
    void modifyB(int b_) { b = b_; }

private:
    int a;
    int b;
};

class TestContainer : public testing::Test
{
protected:
    static void SetUpTestSuite()
    {
        std::cout << "*** test container start ! *** " << std::endl;
    }

    static void TearDownTestSuite()
    {
        std::cout << "*** test container end ! *** " << std::endl;
    }
    // Sets up the test fixture.
    void SetUp() override
    {
    }

    // Tears down the test fixture.
    void TearDown() override
    {
    }

    mContainer c1;
    mContainer c2{ 3, 4 };
};

TEST_F(TestContainer, DefaultConstructor)
{
    EXPECT_EQ(1, c1.getA());
    EXPECT_EQ(2, c1.getB());
}

TEST_F(TestContainer, ValueConstructor)
{
    EXPECT_EQ(3, c2.getA());
    EXPECT_EQ(4, c2.getB());
}

TEST_F(TestContainer, ModifyValue)
{
    c2.modifyA(100);
    c2.modifyB(200);
    EXPECT_EQ(100, c2.getA());
    EXPECT_EQ(300, c2.getB()) << "main";
}