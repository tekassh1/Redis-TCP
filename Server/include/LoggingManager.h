#ifndef LOGGING_MANAGER
#define LOGGING_MANAGER

#include <spdlog/spdlog.h>
#include <memory>

class LoggingManager {
    static std::shared_ptr<spdlog::logger> logger;
public:
    static void init();
};

#endif