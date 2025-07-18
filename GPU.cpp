#include "GPU.hpp"
#include <chrono>

GPU::GPU(Display& display, int width, int height) : display(display), width(width), height(height), running(true) {
    VRAM.resize(width * height, std::vector<BYTE>(3));
    lastFrame.resize(width * height, std::vector<BYTE>(3));

    renderThread = std::thread(&GPU::RenderLoop, this);
}

GPU::~GPU() {
    running = false;
    if (renderThread.joinable()) renderThread.join();
}

void GPU::RenderLoop() {
    while (running) {
        for (int i = 0; i < width * height; ++i) {
            if (VRAM[i] != lastFrame[i]) {
                int x = i % width;
                int y = i / width;
                auto& pixel = VRAM[i];
                display.SetPixel(x, y, pixel[0], pixel[1], pixel[2]);
                lastFrame[i] = pixel;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
