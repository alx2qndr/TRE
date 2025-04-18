#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "Application.hpp"

int main(int argc, char** argv)
{
    try {
        auto app = std::make_unique<tre::Application>();
        app->run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}