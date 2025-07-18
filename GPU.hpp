#pragma once
#include <vector>
#include <windows.h>
#include <thread>
#include <atomic>
#include "Display.hpp"

class GPU {
public:
    std::vector<std::vector<BYTE>> VRAM;

    GPU(Display& display, int width, int height);
    ~GPU();

private:
    Display& display;
    int width;
    int height;

    std::vector<std::vector<BYTE>> lastFrame;
    std::thread renderThread;
    std::atomic<bool> running;

    void RenderLoop();
};
