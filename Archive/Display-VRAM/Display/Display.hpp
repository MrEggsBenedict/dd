// Display.hpp
#pragma once
#include <windows.h>

class Display {
public:
    Display(int width, int height);
    ~Display();
    void setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b);
private:
    HWND hwnd;
    HDC hdc;
    int width;
    int height;
    static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
    void createWindow();
};
