#ifndef __HASAKI_LOGGER_H__
#define __HASAKI_LOGGER_H__

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <stdarg.h>

class ConsoleLogger {
public:
    static ConsoleLogger& Instance() {
        static ConsoleLogger instance;
        return instance;
    }
    std::shared_ptr<spdlog::logger> GetLogger() {
        return logger__;
    }
private:
    ConsoleLogger() {
        logger__ = spdlog::stdout_color_mt("CONSOLE");
    }
    ConsoleLogger(const ConsoleLogger&) = delete;
    ConsoleLogger& operator=(const ConsoleLogger&) = delete;
private:
    std::shared_ptr<spdlog::logger> logger__;
};

class FileLogger {

};


#if defined(__ENV_PROD__) || defined(__ENV_TEST__)
    // File logger
    #define HASAKI_TRACE(...)  spdlog::trace(__VAR_ARGS__)
    #define HASAKI_DEBUG(...)  spdlog::debug(__VAR_ARGS__)
    #define HASAKI_INFO(...)   spdlog::info(__VAR_ARGS__)
    #define HASAKI_WARN(...)   spdlog::warn(__VAR_ARGS__)
    #define HASAKI_ERROR(...)  spdlog::error(__VAR_ARGS__)
#else
    // Console logger
    #define HASAKI_TRACE(...)  ConsoleLogger::Instance().GetLogger()->trace(__VA_ARGS__)
    #define HASAKI_DEBUG(...)  ConsoleLogger::Instance().GetLogger()->debug(__VA_ARGS__)
    #define HASAKI_INFO(...)   ConsoleLogger::Instance().GetLogger()->info(__VA_ARGS__)
    #define HASAKI_WARN(...)   ConsoleLogger::Instance().GetLogger()->warn(__VA_ARGS__)
    #define HASAKI_ERROR(...)  ConsoleLogger::Instance().GetLogger()->error(__VA_ARGS__)
#endif

#endif
