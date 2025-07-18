#include "Display.hpp"
#include "GPU.hpp"
#include <chrono>
#include <thread>
#include <atomic>
#include <iostream>

int main() {
    Display display;
    const int width = 800;
    const int height = 600;

    GPU gpu(display, width, height);

    std::atomic<bool> running(true);

    std::thread vramThread([&]() {
        while (running) {
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    int i = y * width + x;
                    if (y < 600 && x < 600) {
                        BYTE r = static_cast<BYTE>((x * 255) / 199);
                        BYTE g = static_cast<BYTE>((y * 255) / 99);
                        BYTE b = 0;
                        gpu.VRAM[i][0] = r;
                        gpu.VRAM[i][1] = g;
                        gpu.VRAM[i][2] = b;
                    } else {
                        gpu.VRAM[i][0] = 0;
                        gpu.VRAM[i][1] = 0;
                        gpu.VRAM[i][2] = 0;
                    }
                }
            }
        }
    });

    std::thread pixelThread([&]() {
        while (running) {
            for (int y = 0; y < 600; ++y) {
                for (int x = 0; x < 600; ++x) {
                    BYTE r = static_cast<BYTE>((x * 255) / 199);
                    BYTE g = static_cast<BYTE>((y * 255) / 99);
                    BYTE b = 0;
                    display.SetPixel(x + 620, y, r, g, b);
                }
            }
        }
    });

    std::this_thread::sleep_for(std::chrono::seconds(10));
    running = false;

    vramThread.join();
    pixelThread.join();

    // while (true) std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Press Enter to Exit" << std::endl;
    std::cin.get();
}
