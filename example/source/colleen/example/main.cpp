//
// Created by Tobias Fuchs on 02.01.21.
//

#include <config/network/hostname.h>
#include <config/network/port.h>
#include <iostream>

int main(int argc, char **argv) {
    std::cout << config::network::hostname.get() << std::endl;
    std::cout << config::network::port.get() << std::endl;
    return 0;
}