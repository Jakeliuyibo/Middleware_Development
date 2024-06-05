#include <iostream>
#include "singleton_safe.hpp"

using namespace utility;
using namespace std;

class Test
{
    public:
        Test()
        {
            cout << "Test: " << endl;
        }
        ~Test()
        {
            cout << "~Test" << endl;
        }
};

int main(void)
{
    cout << "Start..." << endl;

    {
        Test& ptest = Singleton_Safe<Test, CreateStatic>::Instance();
        // Singleton_Safe<Test, CreateStatic>::DestroyInstance();
    }


    cout << "end..." << endl;

    system("PAUSE");
    return 0;
}