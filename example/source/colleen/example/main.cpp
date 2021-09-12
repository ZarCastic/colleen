//
// Created by Tobias Fuchs on 02.01.21.
//

#include <colleen/_impl/registry.h>
#include <config/network/hostname.h>
#include <config/network/port.h>
#include <config/string_param.h>
#include <iostream>

int main(int argc, char **argv) {
    colleen::_impl::registry::instance().parse(
        argc, argv, colleen::_impl::registry::parse_options::throw_on_error);

    std::cout << "config::network::hostname: "
              << config::network::hostname.get() << std::endl;
    std::cout << "config::network::port: " << config::network::port.get()
              << std::endl;
    std::cout << "config::string_param: " << config::string_param.get()
              << std::endl;

    return 0;
}