#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
#include <functional>
#include <list>

class Timer
{
public:
    Timer(boost::asio::io_context& io_context, std::chrono::seconds duration, std::function<void()> callback)
        : timer_(io_context, duration), callback_(callback)
    {
        std::cout << "Timer created with duration: " << duration.count() << " seconds" << std::endl;

        timer_.async_wait([this](const boost::system::error_code& e)
        {
            if (!e)
            {
                std::cout << "Timer expired, invoking callback" << std::endl;
                callback_();
            }
            else
            {
                // Log the error
                std::cout << "Timer error: " << e.message() << std::endl;
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
        std::cout << "Creating a new timer" << std::endl;
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
        std::cout << "New subscriber added" << std::endl;
    }

    void notify()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        std::cout << "Notifying subscribers" << std::endl;
        for(auto& callback : callbacks_)
        {
            callback();
        }
    }

private:
    std::list<std::function<void()>> callbacks_;
    std::mutex mutex_;
};

class NotifierProxy
{
public:
    NotifierProxy(Notifier& notifier) : notifier_(notifier) {}

    void forwardMessage()
    {
        std::cout << "Forwarding message to notifier" << std::endl;
        notifier_.notify();
    }

private:
    Notifier& notifier_;
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
            std::cout << "Starting io_context" << std::endl;
            thread_ = std::thread([this] { io_context_.run(); });
        }
    }

    void stop()
    {
        std::cout << "Stopping io_context" << std::endl;
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