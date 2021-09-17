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

using spdlog::set_level;
using spdlog::level::level_enum;

}  // namespace colleen::log