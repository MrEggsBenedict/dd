#pragma once
#include <windows.h>
#include <thread>
#include <atomic>
#include <mutex>

class Display {
public:
    Display();
    ~Display();
    void SetPixel(int x, int y, BYTE r, BYTE g, BYTE b);

private:
    HWND hwnd;
    HDC hdc;
    std::thread messageThread;
    std::atomic<bool> running;
    std::mutex  drawMutex;

    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    void MessageLoop();
    void InitWindow();
};
