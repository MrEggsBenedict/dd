// Display.cpp
#include "Display.hpp"

Display::Display(int w, int h) : width(w), height(h) {
    createWindow();
    hdc = GetDC(hwnd);
}

Display::~Display() {
    ReleaseDC(hwnd, hdc);
    DestroyWindow(hwnd);
}

void Display::createWindow() {
    WNDCLASS wc = {};
    wc.lpfnWndProc = Display::WndProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = "FullscreenClass";
    RegisterClass(&wc);
    hwnd = CreateWindowEx(
        WS_EX_TOPMOST,
        wc.lpszClassName,
        "",
        WS_POPUP,
        0, 0, width, height,
        nullptr, nullptr, wc.hInstance, nullptr
    );
    ShowWindow(hwnd, SW_SHOW);
}

LRESULT CALLBACK Display::WndProc(HWND h, UINT msg, WPARAM w, LPARAM l) {
    if (msg == WM_DESTROY) PostQuitMessage(0);
    return DefWindowProc(h, msg, w, l);
}

void Display::setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b) {
    COLORREF c = RGB(r, g, b);
    SetPixel(hdc, x, y, c);
}
