#ifndef __HASAKI_LOGGER_H__
#define __HASAKI_LOGGER_H__

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "noncopyable.h"

#include <cassert>

class ConsoleLogger : public hasaki::noncopyable
{
public:
    static ConsoleLogger &Instance()
    {
        static ConsoleLogger instance;
        return instance;
    }
    std::shared_ptr<spdlog::logger> GetLogger()
    {
        return logger__;
    }

private:
    ConsoleLogger()
    {
        logger__ = spdlog::stdout_color_mt("CONSOLE");
        assert(logger__);
    }
    std::shared_ptr<spdlog::logger> logger__;
};

class FileLogger : public hasaki::noncopyable
{
public:
    static FileLogger &Instance()
    {
        static FileLogger instance;
        return instance;
    }

    std::shared_ptr<spdlog::logger> GetLogger()
    {
        return logger__;
    }

private:
    FileLogger()
    {
        logger__ = spdlog::rotating_logger_mt("FILE", "/data/cpplogs/hasaki.log", 1048576 * 5, 3);
        assert(logger__);
    }

    std::shared_ptr<spdlog::logger> logger__;
};

#if defined(__ENV_PROD__) || defined(__ENV_TEST__)
// Thread-Safe File logger
#define HASAKI_TRACE(...) FileLogger::Instance().GetLogger()->trace(__VA_ARGS__)
#define HASAKI_DEBUG(...) FileLogger::Instance().GetLogger()->debug(__VA_ARGS__)
#define HASAKI_INFO(...) FileLogger::Instance().GetLogger()->info(__VA_ARGS__)
#define HASAKI_WARN(...) FileLogger::Instance().GetLogger()->warn(__VA_ARGS__)
#define HASAKI_ERROR(...) FileLogger::Instance().GetLogger()->error(__VA_ARGS__)
#else
// Thread-Safe Console logger
#define HASAKI_TRACE(...) ConsoleLogger::Instance().GetLogger()->trace(__VA_ARGS__)
#define HASAKI_DEBUG(...) ConsoleLogger::Instance().GetLogger()->debug(__VA_ARGS__)
#define HASAKI_INFO(...) ConsoleLogger::Instance().GetLogger()->info(__VA_ARGS__)
#define HASAKI_WARN(...) ConsoleLogger::Instance().GetLogger()->warn(__VA_ARGS__)
#define HASAKI_ERROR(...) ConsoleLogger::Instance().GetLogger()->error(__VA_ARGS__)
#endif

#endif
