#include "GPU/Display.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    Display d(320, 240);
    if (!d.create(hInstance, nCmdShow)) return 1;

    COLORREF* fb = d.getFramebuffer();
    for (int y = 0; y < 240; ++y) {
        for (int x = 0; x < 320; ++x) {
            fb[y * 320 + x] = RGB(x % 256, y % 256, (x ^ y) % 256);
        }
    }

    d.invalidate();
    d.run();
    return 0;
}
