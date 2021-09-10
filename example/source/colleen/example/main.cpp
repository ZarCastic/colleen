//
// Created by Tobias Fuchs on 02.01.21.
//

#include <colleen/colleen.h>
#include <iostream>

int main(int argc, char **argv) {
    Colleen::setExecutableName("unit_tests");
    Colleen::addArgument<int>({"test", 't'})
        .setDescription("Optional argument")
        .setDefault(42);
    Colleen::addArgument<int>("testArgument0")
        .setDescription("Test argument at position 0")
        .setDefault(42);

    std::cout << Colleen::getHelpString() << std::endl;

    return 0;
}