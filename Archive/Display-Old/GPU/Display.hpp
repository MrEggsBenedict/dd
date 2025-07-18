#pragma once
#include <windows.h>

class Display {
public:
    Display(int width, int height);
    ~Display();

    bool create(HINSTANCE hInstance, int nCmdShow);
    void run();
    COLORREF* getFramebuffer();
    void invalidate();

private:
    HWND hwnd;
    int width, height;
    COLORREF* framebuffer;
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};
