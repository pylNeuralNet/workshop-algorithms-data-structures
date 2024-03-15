#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <memory>
#include <thread>
#include <mutex>
#include <functional>
#include <map>
#include <list>

class Timer
{
public:
    Timer(boost::asio::io_context& io_context, std::chrono::seconds duration, std::function<void()> callback)
        : timer_(io_context, duration), callback_(callback)
    {
        timer_.async_wait([this](const boost::system::error_code& e)
        {
            if (!e)
            {
                callback_();
            }
            else
            {
                // Log the error
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
        return std::make_shared<Timer>(io_context_, duration, callback);
    }

private:
    boost::asio::io_context& io_context_;
};

class Subscriber
{
public:
    virtual ~Subscriber() {}
    virtual void onNotification() = 0;
};

class Notifier
{
public:
    void subscribe(std::function<void()> callback)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        callbacks_.push_back(callback);
    }

    void notify()
    {
        std::lock_guard<std::mutex> lock(mutex_);
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
            thread_ = std::thread([this] { io_context_.run(); });
        }
    }

    void stop()
    {
        io_context_.stop();
        if(thread_.joinable())
        {
            thread_.join();
        }
    }

private:
    IoContextManager() {}
    IoContextManager(const IoContextManager&) = delete;
    IoContextManager& operator=(const IoContextManager&) = delete;

    boost::asio::io_context io_context_;
    std::thread thread_;
};