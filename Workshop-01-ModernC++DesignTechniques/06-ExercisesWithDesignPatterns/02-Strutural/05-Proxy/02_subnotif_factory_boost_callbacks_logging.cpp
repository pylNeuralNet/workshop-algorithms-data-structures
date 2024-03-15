/*
    pylNeuralNet
    2024

    In this version of the code, I've made a few changes:

        1. The Subscriber class is removed because it's no longer needed. The Notifier class instead stores a list of callback functions that are called when notify() is called.

        2. The Timer class now accepts a callback function in its constructor and calls this function when the timer expires.

        3. The TimerFactory class now accepts a callback function in its createTimer() method and passes this to the Timer constructor.

        4. Error handling is added to the Timer class. If an error occurs in the timer (for example, if the timer was cancelled), it logs the error.

        5. Thread-safe destruction of the IoContextManager is ensured by calling stop() in its destructor, which stops the io_context_ and joins the thread.
*/


#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
#include <functional>
#include <list>

void log(const std::string& message)
{
    std::cout << message << std::endl;
}

class Timer
{
public:
    Timer(boost::asio::io_context& io_context, std::chrono::seconds duration, std::function<void()> callback)
        : timer_(io_context, duration), callback_(callback)
    {
        log("Timer created with duration: " + std::to_string(duration.count()) + " seconds");

        timer_.async_wait([this](const boost::system::error_code& e)
        {
            if (!e)
            {
                log("Timer expired, invoking callback");
                callback_();
            }
            else
            {
                log("Timer error: " + e.message());
            }
        });
    }

private:
    boost::asio::steady_timer timer_;
    std::function<void()> callback_;
};

class TimerFactory
{
public:
    TimerFactory(boost::asio::io_context& io_context)
        : io_context_(io_context) {}

    std::shared_ptr<Timer> createTimer(std::chrono::seconds duration, std::function<void()> callback)
    {
        log("Creating a new timer");
        return std::make_shared<Timer>(io_context_, duration, callback);
    }

private:
    boost::asio::io_context& io_context_;
};

class Notifier
{
public:
    void subscribe(std::function<void()> callback)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        callbacks_.push_back(callback);
        log("New subscriber added");
    }

    void notify()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        log("Notifying subscribers");
        for(auto& callback : callbacks_)
        {
            callback();
        }
    }

private:
    std::list<std::function<void()>> callbacks_;
    std::mutex mutex_;
};

class IoContextManager
{
public:
    static IoContextManager& getInstance()
    {
        static IoContextManager instance;
        return instance;
    }

    boost::asio::io_context& getIoContext()
    {
        return io_context_;
    }

    void run()
    {
        if(!thread_.joinable())
        {
            log("Starting io_context");
            thread_ = std::thread([this] { io_context_.run(); });
        }
    }

    void stop()
    {
        log("Stopping io_context");
        io_context_.stop();
        if(thread_.joinable())
        {
            thread_.join();
        }
    }

    ~IoContextManager() 
    {
        stop();
    }

private:
    IoContextManager() {}
    IoContextManager(const IoContextManager&) = delete;
    IoContextManager& operator=(const IoContextManager&) = delete;

    boost::asio::io_context io_context_;
    std::thread thread_;
};