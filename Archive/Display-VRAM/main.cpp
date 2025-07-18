// main.cpp
#include <windows.h>
#include "GPU/GPU.hpp"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    GPU gpu(w, h);
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            int i = y * w + x;
            gpu.vram[i] = { (unsigned char)(x * 255 / w), (unsigned char)(y * 255 / h), 0 };
        }
    }
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
