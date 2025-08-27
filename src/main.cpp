#include "CPU/cpu.hpp"
#include "header.hpp"
#include "Mapper/mapper.hpp"

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <ios>
#include <iostream>
#include <memory>
#include <ostream>

#include "GLFW/glfw3.h"

GLFWwindow *window;
char *filename;

void error_callback(int error, const char *desc) {
    std::cerr << "ERROR #" << error << ": " << desc;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

bool initialize_glfw() {
    if (!glfwInit()) {
        std::cout << "ERROR: GLFW failed to initialize" << std::endl;
        return true;
    }
    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(640, 480, "AccuiNES", NULL, NULL);
    if (!window) {
        std::cout << "ERROR: GLFW window failed to initialize" << std::endl;
        return true;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    int width, height; // maybe should be global
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glfwSwapInterval(1);

    return false;
}

bool initialize_rom() {
    std::ifstream rom(filename, std::ios_base::in | std::ios_base::binary);

    char *uninterp_header = new char[0x10];
    rom.read(uninterp_header, 0x10);

    if (strncmp(uninterp_header, "NES\x1A", 4) != 0) {
        std::cout << "ERROR: File is not an NES file." << std::endl;
        return true;
    }

    header.prg_rom = uninterp_header[4]; // PRG-ROM size LSB
    header.chr_rom = uninterp_header[5]; // CHR-ROM size LSB

    header.nametbl_mirror   = (uninterp_header[6] & 0x01) >> 0;
    header.battery          = (uninterp_header[6] & 0x02) >> 1;
    header.trainer          = (uninterp_header[6] & 0x04) >> 2;
    header.nametbl_mirror  += (uninterp_header[6] & 0x08) >> 2; // >> 3 << 1
    header.mapper_num       = (uninterp_header[6] & 0xF0) >> 4;

    header.console_type     = (uninterp_header[7] & 0x03) >> 0;
    header.header_type      = (uninterp_header[7] & 0x0C) >> 2;

    // deal with the rest later

    delete []uninterp_header;

    Mapper::determineMapper(rom);

    return false;
}

void run() {
    std::unique_ptr<CPU::CPU> cpu = std::make_unique<CPU::CPU>();

    while (!glfwWindowShouldClose(window)) {
        cpu->simulate();
        glfwSwapBuffers(window);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "AccuiNES: ./AccuiNES.exe <filename>" << std::endl;
        return 0;
    }
    filename = argv[1];

    if (initialize_glfw()) {
        return 1;
    }
    std::cout << "GLFW initialized" << std::endl;

    if (initialize_rom()) {
        return 2;
    }
    std::cout << "ROM initialized" << std::endl;

    run();

    glfwDestroyWindow(window);
    glfwTerminate();
}