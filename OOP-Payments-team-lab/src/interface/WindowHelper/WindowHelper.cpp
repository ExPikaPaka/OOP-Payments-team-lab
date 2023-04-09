#include "WindowHelper.h"

WindowHelper::WindowHelper() {
	window = 0;
}
WindowHelper::WindowHelper(HWND source) {
	window = source;
}

HWND WindowHelper::initWindow(wchar_t winName[], int x, int y, int width, int height, long dwStyle) {
	// Register the window class
	LPCWSTR CLASS_NAME = L"myWin32WindowClass";
	WNDCLASS wcex{};
	wcex.hInstance = 0;
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpszClassName = CLASS_NAME;
	wcex.hCursor = LoadCursor(0, IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(RGB(80, 80, 80));
	wcex.lpfnWndProc = DefWindowProc;
	RegisterClass(&wcex);

	// Create the window
	HWND toReturn = CreateWindowExW(0, wcex.lpszClassName,
		winName, dwStyle, x, y, width, height, NULL,
		NULL, NULL, NULL);

	window = toReturn;
	return toReturn;
}