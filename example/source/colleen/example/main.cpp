//
// Created by Tobias Fuchs on 02.01.21.
//

#include <colleen/_impl/registry.h>
#include <colleen/logging.h>
#include <config/network/hostname.h>
#include <config/network/port.h>
#include <config/string_param.h>
#include <iostream>

int main(int argc, char **argv) {
    colleen::_impl::registry::instance().parse(
        argc, argv, colleen::_impl::registry::parse_options::throw_on_error);
    colleen::log::set_level(
        spdlog::level::debug);  // Set global log level to debug
    colleen::log::info("config::network::hostname: {}",
                       config::network::hostname.get());
    colleen::log::debug("config::network::port: {}",
                        config::network::port.get());
    colleen::log::error("config::string_param: {}", config::string_param.get());

    colleen::log::warn("Some warning from colleen");

    return 0;
}