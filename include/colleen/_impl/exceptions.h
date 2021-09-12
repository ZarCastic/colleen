//
// Created by Tobias Fuchs on 12.09.21.
//

#pragma once

#include <stdexcept>

namespace colleen::_impl {

class bad_option : public std::invalid_argument {
   public:
    using std::invalid_argument::invalid_argument;
};

class incomplete_or_missing_argument : public std::invalid_argument {
   public:
    using std::invalid_argument::invalid_argument;
};

}  // namespace colleen::_impl