//
// Created by Tobias Fuchs on 11.09.21.
//

#pragma once
#include <utility>

namespace colleen {

template <typename option_type>
class node {
  public:
    explicit node(const option_type option_value) noexcept
        : _value(std::move(option_value)) {}

    explicit operator const option_type&() { return get<option_type>(); }

    template <typename required_type = option_type>
    const required_type& get() {
        return _value;
    }

  protected:
    option_type _value;
};

}  // namespace colleen