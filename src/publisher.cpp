/**
 *  publisher.cpp
 *
 *  Test program to check AMQP functionality based on LibUV
 *
 */

/**
 *  Dependencies
 */
#include <uv.h>
#include <amqpcpp.h>
#include <amqpcpp/libuv.h>
#include <thread>
#include <unistd.h>

/**
 *  Custom handler
 */
class MyHandler : public AMQP::LibUvHandler
{
private:
    /**
     *  Method that is called when a connection error occurs
     *  @param  connection
     *  @param  message
     */
    virtual void onError(AMQP::TcpConnection *connection, const char *message) override
    {
        std::cout << "error: " << message << std::endl;
    }

    /**
     *  Method that is called when the TCP connection ends up in a connected state
     *  @param  connection  The TCP connection
     */
    virtual void onConnected(AMQP::TcpConnection *connection) override
    {
        std::cout << "Success connection" << std::endl;
    }

public:
    /**
     *  Constructor
     *  @param  uv_loop
     */
    MyHandler(uv_loop_t *loop) : AMQP::LibUvHandler(loop) {}

    /**
     *  Destructor
     */
    virtual ~MyHandler() = default;
};

//bool GiveWork(AMQP::TcpChannel &ch, const char *work) {
//    std::cout << "Give a job: " << work << std::endl;
//    ch.publish("chat", "", work);
//}

/**
 *  Main program
 *  @return int
 */
int main()
{
    // access to the event loop
    auto *loop = uv_default_loop();

    // handler for libev
    MyHandler handler(loop);

    // make a connection
    AMQP::TcpConnection connection(&handler, AMQP::Address("amqp://test:test@18.184.229.222/"));

    // we need a channel too
    AMQP::TcpChannel channel(&connection);
    channel.setQos(1);

    // create a exchange
    channel.declareExchange("chat", AMQP::topic);

//    channel.onReady([&]() {
//        if (channel.connected()) {
//            GiveWork(channel, "Wash floor : 20");
//            GiveWork(channel, "Make food : 40");
//            GiveWork(channel, "Shopping : 25");
//        }
//    });

    // run the loop
    std::thread thr(uv_run, loop, UV_RUN_DEFAULT);

    while(!connection.ready())
        usleep(1);

    std::cout << "Who is addressee: ";
    std::string name;
    std::getline(std::cin, name);
    if (name == "break")
        return 0;

    while (true) {
        if (!channel.connected() || !connection.ready())
            continue;

        std::cout << ">";
        std::string msg;
        std::getline(std::cin, msg);
        if (msg == "break")
            break;

//        std::cout << "Msg: " << msg << " route key:" << name  <<  "\n";

        channel.publish("chat", name, msg);
    }

    thr.join();
    channel.close();
    connection.close();

    // done
    return 0;
}

