#include <iostream>
#include "visitor.hpp"

using namespace std;
using namespace utility;

class TestSource
{
    public:
        TestSource() {}
        ~TestSource() {}

    public:
        int a = 1;
        int b = 2;
};

class OperA : public Visitor<TestSource &, int>
{
    public:
        OperA() {}
        ~OperA() {}
        int Visit(TestSource &obj) override
        {
            cout << "oper A , obj.a = " << obj.a << endl;
            return obj.a;
        }
};

class OperB : public Visitor<TestSource &, void>
{
    public:
        OperB() {}
        ~OperB() {}
        void Visit(TestSource &obj) override
        {
            obj.b = 99;
            cout << "oper B , obj.b = " << obj.b << endl;
        }
};

int main()
{
    cout << "Start..." << endl;

    {
        TestSource ts;
        OperA oa;
        OperB ob;
        cout << "a = " << ts.a << ", " << "b = " << ts.b << endl;
        oa.Visit(ts);
        cout << "a = " << ts.a << ", " << "b = " << ts.b << endl;
        ob.Visit(ts);
        cout << "a = " << ts.a << ", " << "b = " << ts.b << endl;
    }

    cout << "end..." << endl;
    return 0;
}