//
// Created by Tobias Fuchs on 11.09.21.
//

#pragma once
#include <string>
#include <utility>
#include "colleen/_impl/base_node.h"
#include "colleen/logging.h"

namespace colleen {

using base_node = _impl::base_node;

template <typename option_type>
class node : public base_node {
  public:
    explicit node(std::string option_name,
                  const option_type option_value = option_type()) noexcept
        : base_node(std::move(option_name)), _value(std::move(option_value)) {}

    explicit operator const option_type&() { return get<option_type>(); }

    template <typename required_type = option_type>
    const required_type& get() {
        return _value;
    }

    bool set(const std::string& value) noexcept override {
        colleen::log::debug("Setting value for option {} to {}", _option_name,
                            value);
        if constexpr (std::is_integral_v<option_type> &&
                      std::is_signed_v<option_type>) {
            _value = std::stoll(value);
        } else if constexpr (std::is_integral_v<option_type>) {
            _value = std::stoull(value);
        } else if constexpr (std::is_floating_point_v<option_type>) {
            _value = std::stod(value);
        } else {
            _value = value;
        }
        _satisfied = true;
        return true;
    }

   protected:
    option_type _value;
};

}  // namespace colleen