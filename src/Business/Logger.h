#pragma once

#include <mutex>

class Logger
{
private:
    static Logger* s_instance;
    static std::mutex s_mutex;

    Logger() = default;

public:
    // no copying for singleton
    Logger(Logger& otherLogger) = delete;

    // no assigning for singleton
    void operator=(const Logger&) = delete;

    static Logger* getInstance();

    void logMessage(const std::string& message);
};
