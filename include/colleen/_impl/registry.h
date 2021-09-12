//
// Created by Tobias Fuchs on 12.09.21.
//

#pragma once

#include <colleen/_impl/exceptions.h>
#include <string>
#include <unordered_map>

namespace colleen::_impl {

class base_node;

class registry {
   public:
    enum class parse_options { none, throw_on_error };

    static registry& instance() noexcept;

    void add(std::string option_name, base_node* node);
    bool parse(int argc, char** argv,
               parse_options options = parse_options::none);

    registry(const registry&) = delete;
    registry(registry&&) = delete;
    registry& operator=(const registry&) = delete;
    registry& operator=(registry&&) = delete;
    ~registry() = default;

   private:
    registry() = default;

    std::unordered_map<std::string, base_node*> _options;
};

}  // namespace colleen::_impl