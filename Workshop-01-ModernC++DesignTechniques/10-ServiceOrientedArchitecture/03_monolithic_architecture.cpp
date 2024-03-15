class MonolithicApplication {
    ...

    void serviceA() {
        for (int i = 0; i < 10; ++i) {
            std::cout << "ServiceA sending message: " << i << std::endl;
            serviceB(i); // Call serviceB directly
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    void serviceB(int message) {
        std::cout << "ServiceB received message: " << message << std::endl;
    }
};