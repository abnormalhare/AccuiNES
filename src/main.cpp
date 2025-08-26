#include "CPU/cpu.hpp"
#include <iostream>
#include <memory>
#include <ostream>

// #include "GLFW/glfw3.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "AccuiNES: ./AccuiNES.exe <filename>" << std::endl;
    }

    char *filename = argv[1];

    std::unique_ptr<CPU::CPU> cpu = std::make_unique<CPU::CPU>();

    cpu->simulate();
}