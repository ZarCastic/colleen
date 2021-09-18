//
// Created by Tobias Fuchs on 12.09.21.
//

#pragma once

#include <colleen/_impl/registry.h>
#include <string>

namespace colleen::_impl {

class base_node {
   public:
    explicit base_node(std::string option_name);
    [[nodiscard]] virtual bool set(const std::string& value) noexcept = 0;
    [[nodiscard]] virtual bool satisfied() final;

   protected:
    bool _satisfied{false};
    const std::string _option_name;
};

}  // namespace colleen::_impl