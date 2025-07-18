#include "Display.hpp"

LRESULT CALLBACK Display::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

void Display::InitWindow() {
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "DisplayWindowClass";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClass(&wc);

    hwnd = CreateWindowEx(
        0,
        wc.lpszClassName,
        "GDI Display",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        0, 0,
        GetSystemMetrics(SM_CXSCREEN),
        GetSystemMetrics(SM_CYSCREEN),
        NULL,
        NULL,
        wc.hInstance,
        NULL
    );

    ShowWindow(hwnd, SW_MAXIMIZE);
    hdc = GetDC(hwnd);
    RECT rect;
    GetClientRect(hwnd, &rect);
    HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));
    FillRect(hdc, &rect, blackBrush);
    DeleteObject(blackBrush);
}

void Display::MessageLoop() {
    InitWindow();
    MSG msg;
    while (running) {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                running = false;
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        Sleep(1);
    }
    ReleaseDC(hwnd, hdc);
    DestroyWindow(hwnd);
}

Display::Display() : running(true) {
    messageThread = std::thread([this]() { MessageLoop(); });
    while (!hwnd || !IsWindow(hwnd)) Sleep(10);
}

Display::~Display() {
    running = false;
    PostMessage(hwnd, WM_CLOSE, 0, 0);
    if (messageThread.joinable()) messageThread.join();
}

void Display::SetPixel(int x, int y, BYTE r, BYTE g, BYTE b) {
    std::lock_guard<std::mutex> lk(drawMutex);
    if (hdc) ::SetPixel(hdc, x, y, RGB(r, g, b));
}
