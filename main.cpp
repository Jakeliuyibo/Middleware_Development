#include <iostream>
#include <memory>
#include "logger.h"
#include "systime.h"
#include "timer.h"
#include "testmodule.h"
#include "singleton.h"
#include "jsonparser.h"
#include "vector.h"
#include "smartptr.h"
#include "uniqueptr.h"
#include "sharedptr.h"

using namespace utility;
using namespace std;

void fucnt(int a)
{
    int b;
    cout << a << " " << b << endl;
}

int main(void)
{
    auto p = new vector<int>(10, 123);
    SharedPtr<vector<int>> sp(p);
    for(auto s: *sp)
    {
        cout << s << endl;
    }
    cout << bool(sp) << endl;
    cout << sp.use_count() << endl;

    SharedPtr<vector<int>> sp1(sp);
    cout << sp.use_count() << endl;
    cout << sp1.use_count() << endl;

    debug("hello world1");

    return 0;
}