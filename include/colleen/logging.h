//
// Created by Tobias Fuchs on 12.09.21.
//

#pragma once

#include <spdlog/spdlog.h>

namespace colleen::log {

#define COLLEEN_MAKE_LOG_FUNCTION(type) using spdlog::type

COLLEEN_MAKE_LOG_FUNCTION(error);
COLLEEN_MAKE_LOG_FUNCTION(info);
COLLEEN_MAKE_LOG_FUNCTION(warn);
COLLEEN_MAKE_LOG_FUNCTION(critical);
COLLEEN_MAKE_LOG_FUNCTION(debug);

enum class log_level {
    error = spdlog::level::err,
    info = spdlog::level::info,
    warn = spdlog::level::warn,
    critical = spdlog::level::critical,
    debug = spdlog::level::debug
};

void set_level(log_level log_level);

}  // namespace colleen::log