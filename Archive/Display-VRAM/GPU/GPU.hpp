// GPU.hpp
#pragma once
#include <vector>
#include <array>
#include <thread>
#include <atomic>
#include "../Display/Display.hpp"

class GPU {
public:
    GPU(int width, int height);
    ~GPU();
    std::vector<std::array<unsigned char,3>> vram;
private:
    int width;
    int height;
    Display display;
    std::thread updater;
    std::atomic<bool> running;
    void loop();
};
