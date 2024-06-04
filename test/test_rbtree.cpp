#include <iostream>
#include "logger.h"
#include "rbtree.h"

using namespace utility;
using namespace std;

int main(void)
{
    Logger::instance()->open("log.txt");
    Logger::instance()->setLevel(Logger::DEBUG);

    cout << "Start..." << endl;


    cout << "end..." << endl;
    return 0;
}