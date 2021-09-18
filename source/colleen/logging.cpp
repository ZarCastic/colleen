//
// Created by Tobias Fuchs on 18.09.21.
//
#include "colleen/logging.h"

namespace colleen::log {

void set_level(log_level log_level) {
    spdlog::set_level(static_cast<spdlog::level::level_enum>(log_level));
}

}  // namespace colleen::log