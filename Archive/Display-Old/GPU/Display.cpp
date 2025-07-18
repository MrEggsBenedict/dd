#include "Display.hpp"

static Display* g_instance = nullptr;

Display::Display(int w, int h) : hwnd(nullptr), width(w), height(h) {
    framebuffer = new COLORREF[width * height];
    memset(framebuffer, 0, width * height * sizeof(COLORREF));
    g_instance = this;
}

Display::~Display() {
    delete[] framebuffer;
}

bool Display::create(HINSTANCE hInstance, int nCmdShow) {
    const char CLASS_NAME[] = "DisplayWindowClass";

    WNDCLASSA wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClassA(&wc);

    hwnd = CreateWindowExA(
        0,
        CLASS_NAME,
        "Display Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        width + 16, height + 39,
        nullptr, nullptr, hInstance, nullptr
    );

    if (!hwnd) return false;

    ShowWindow(hwnd, nCmdShow);
    return true;
}

void Display::run() {
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

COLORREF* Display::getFramebuffer() {
    return framebuffer;
}

void Display::invalidate() {
    InvalidateRect(hwnd, nullptr, FALSE);
}

LRESULT CALLBACK Display::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_PAINT && g_instance) {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        for (int y = 0; y < g_instance->height; ++y) {
            for (int x = 0; x < g_instance->width; ++x) {
                SetPixel(hdc, x, y, g_instance->framebuffer[y * g_instance->width + x]);
            }
        }
        EndPaint(hwnd, &ps);
        return 0;
    } else if (uMsg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
