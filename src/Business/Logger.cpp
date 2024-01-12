#include "Logger.h"

#include <iostream>

Logger* Logger::getInstance()
{
    std::lock_guard<std::mutex> lock(s_mutex);
    if(s_instance == nullptr)
    {
        s_instance = new Logger();
    }
    return s_instance;
}

void Logger::logMessage(const std::string& message)
{
    static int logMessageIndex = 1;
    std::cout << std::to_string(logMessageIndex) + " : " + message;
}


