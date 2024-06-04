#include <iostream>
#include <memory>
#include <unistd.h>
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
#include "rabbitmqclient.h"

using namespace utility;
using namespace std;

int main(void)
{
    Logger::instance()->open("log.txt");
    Logger::instance()->setLevel(Logger::DEBUG);

    cout << "Start..." << endl;
    showRabbitMqVersion();

    RabbitMqClient client("localhost", 5672, "guest", "guest");
    int ret = client.connect();
    string name_exchange = "test_exchange";
    string name_queue = "test_queue";

    CExchange exchange(name_exchange, "direct");
    client.declareExchange(exchange);
    CQueue queue(name_queue);
    client.declareQueue(queue);
    client.bindQueueToExchange(name_queue, name_exchange, "test_key");
    amqp_basic_properties_t properties = {0};

    int times = 0;
    while(times < 10)
    {
        info("%ds...", times);
        // ret = client.publish(name_exchange, "test_key", std::move(CMessage("hello" + to_string(times))));
        // cout << "send ret " << ret << endl;
    

        struct timeval timeout = {5,0};
        vector<string> recv = client.consume("test_queue", 5, &timeout, false);
        // string recv = client.consume("test_queue", &timeout);

        // vector<string> recv = client.consume(name_queue, 10, false);
        // string recv = client.consume(name_queue, false);

        // cout << "recv " << recv << endl;
        for(auto r:recv)
        {
            cout << "recv " << r << endl;
        }

        times++;
        sleep(1);
    }

    cout << "end..." << endl;
    return 0;
}