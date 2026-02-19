#include <torch/torch.h>

#include <iostream>

#include "Console.h"

int main(int argc, char* argv[]) {
    try {
        ConsoleUI ui;
        ui.run();

    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}