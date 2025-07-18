// GPU.cpp
#include "GPU.hpp"
#include <windows.h>

GPU::GPU(int w, int h)
: width(w), height(h), display(w,h), running(true)
{
    vram.resize(width * height);
    updater = std::thread(&GPU::loop, this);
}

GPU::~GPU() {
    running = false;
    if (updater.joinable()) updater.join();
}

void GPU::loop() {
    MSG msg;
    while (running) {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) running = false;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        for (int i = 0; i < width * height; ++i) {
            int x = i % width;
            int y = i / width;
            auto &c = vram[i];
            display.setPixel(x, y, c[0], c[1], c[2]);
        }
        Sleep(16);
    }
    PostQuitMessage(0);
}
