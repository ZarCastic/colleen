//
// Created by Tobias Fuchs on 30.12.20.
//

#pragma once

#include <iostream>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace Colleen {

using ArgumentName = std::string;

namespace Colleen::_impl_ {

struct ArgumentOption {
    ArgumentOption(std::string long_option, char short_option) noexcept
        : _short_option{short_option}, _long_option{std::move(long_option)} {
        _doc_string = makeDocString();
    }

    uint64_t stringSize() const noexcept { return _doc_string.size(); }

    char _short_option;
    std::string _long_option;
    std::string _doc_string;

   private:
    std::string makeDocString() noexcept {
        std::ostringstream out_stream;
        out_stream << "["
                   << ((_long_option.empty()
                            ? ""
                            : ("--" + _long_option) +
                                  ((_short_option != 0) ? "" : ",")))
                   << (((_short_option != 0)
                            ? ""
                            : ("-" + std::string(1, _short_option))));

        if (!_long_option.empty()) {
            out_stream << "--" << _long_option
                       << ((_short_option != 0) ? "" : (",-"));
        }
        return out_stream.str();
    }
};

template <class Stream>
inline Stream& operator<<(Stream& lhs, const ArgumentOption& rhs) noexcept {
    lhs << rhs._doc_string;
    return lhs;
}

}  // namespace Colleen::_impl_

}  // namespace Colleen