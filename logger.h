#ifndef __HASAKI_LOGGER_H__
#define __HASAKI_LOGGER_H__

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#define HASAKI_TRACE(...)  spdlog::trace(##__VAR_ARGS__)
#define HASAKI_DEBUG(...)  spdlog::debug(##__VAR_ARGS__)
#define HASAKI_INFO(...)   spdlog::info(##__VAR_ARGS__)
#define HASAKI_WARN(...)   spdlog::warn(##__VAR_ARGS__)
#define HASAKI_ERROR(...)  spdlog::error(##__VAR_ARGS__)

#endif
