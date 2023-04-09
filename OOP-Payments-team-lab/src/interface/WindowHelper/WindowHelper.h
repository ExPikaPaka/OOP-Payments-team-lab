#pragma once
#include <Windows.h>

class WindowHelper {
public:
	HWND window;

	WindowHelper();
	WindowHelper(HWND window);

	HWND initWindow(wchar_t winName[], int x, int y, int width, int height, long dwStyle = WS_POPUPWINDOW);
};