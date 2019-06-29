/**
 *  subscriber.cpp
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
#include <unistd.h>
#include <exception>
#include <thread>

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
        std::cout << "Error: " << message << std::endl;
    }

    /**
     *  Method that is called when the TCP connection ends up in a connected state
     *  @param  connection  The TCP connection
     */
    virtual void onConnected(AMQP::TcpConnection *connection) override
    {
        std::cout << "Connected success\n" << std::endl;
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

//void MakeWork(const std::string &job) {
//    std::cout << "Task: " << job.c_str() << std::endl;
//
//    int hours = atoi(job.substr(job.find(":") + 1).c_str());
//
//    std::cout << "Need work: " << hours << " hours" << std::endl;
//    sleep(hours);
//
//    std::cout << "Finish task: " << job << std::endl;
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

    // run the loop
    std::thread thr(uv_run, loop, UV_RUN_DEFAULT);

    while(!connection.ready())
        usleep(1);

    std::cout << "Who are you: ";
    std::string nickname;
    std::getline(std::cin, nickname);
    if (nickname == "exit")
        return 0;

    // create a temporary queue
    channel.declareQueue(AMQP::durable | AMQP::autodelete)
        .onSuccess([&nickname, &channel](const std::string &name, uint32_t messagecount, uint32_t consumercount) {
            channel.bindQueue("chat", name, nickname);

            channel.consume(name)
                    .onReceived([&channel](const AMQP::Message &message, uint64_t deliveryTag, bool redelivered) {
                        const int size = message.bodySize();
                        std::string msg(message.body(), size);

                        std::cout << "<" << msg << std::endl;

                        channel.ack(deliveryTag);
                    });
        })
        .onError([](const char *message) {
            std::cerr << "Error:" << message;
            throw  std::runtime_error(message);
        });

    thr.join();
    // done
    return 0;
}

