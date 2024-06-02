#include "LoggingManager.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/dist_sink.h>

#include <memory>

std::shared_ptr<spdlog::logger> LoggingManager::logger;

void LoggingManager::init() {

    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::debug);
    console_sink->set_pattern("[%Y-%m-%d %H:%M:%S] [%^%l%$] %v");

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs.txt", true);
    file_sink->set_level(spdlog::level::debug);

    auto dist_sink = std::make_shared<spdlog::sinks::dist_sink_mt>();
    dist_sink->add_sink(console_sink);
    dist_sink->add_sink(file_sink);

    logger = std::make_shared<spdlog::logger>("multi_sink", dist_sink);
    logger->set_level(spdlog::level::debug);

    spdlog::set_default_logger(logger);
}