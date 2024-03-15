/**
    The advantage of a microservices architecture is that each service can be developed, deployed, and scaled independently. However, it also adds a lot of complexity due to the need for serialization and network communication, and it has more overhead than in-process communication.

    (the data serialization is added as an extension of service_oriented_architecture.cpp, not part of showcasing the differences between them)
*/

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <string>
#include <sstream>

class MessageQueue {
    // In a real implementation, this would be a network connection such as a socket.
    std::queue<std::string> queue; // Changed to string queue for serialized messages
    ...

public:
    void send(int message) {
        std::ostringstream oss;
        boost::archive::text_oarchive oa(oss);
        oa << message; // Serialize message with Boost.Serialization
        ...
        queue.push(oss.str()); // Send serialized message
        ...
    }

    int receive() {
        ...
        std::string serializedMessage = queue.front();
        queue.pop();
        std::istringstream iss(serializedMessage);
        boost::archive::text_iarchive ia(iss);
        int message;
        ia >> message; // Deserialize message with Boost.Serialization
        return message;
    }
};