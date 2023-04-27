#pragma once

#include <Windows.h>

class Scene {
public:
	HWND* window;
	MSG* msg;
	HDC dc;
	HDC memDC;
	int width, height;
	RECT windowRect;

	HBITMAP memBM;
	COLORREF backgroundColor;
	COLORREF brushColor;
	COLORREF penColor;

	Scene();
	Scene(HWND& window, MSG& msg);

	void beginPaint();
	void endPaint();
	void swapBuffer();

	void setObject(HGDIOBJ obj);
	void selectPenAndBrush();
	void setColor();
	void setColor(COLORREF color);
	void setColor(int rCol, int gCol, int bCol);
	void setBrushColor(COLORREF color);
	void setPenColor(COLORREF color);

	void poly(POINT* pt, int ptCount);
	void rect(int x0, int y0, int x1, int y1);
	void line(int x0, int y0, int x1, int y1);
	void boundingBox(int x0, int y0, int x1, int y1);
	void ellipse(int x0, int y0, int x1, int y1);
	void text(wchar_t message[], int x, int y, int textWidth, int textHeight,
		int charWidth = 7, int charHeight = 16, wchar_t fontName[] = (wchar_t*)L"Times New Roman",
		COLORREF fontColor = RGB(255, 255, 255), COLORREF bkColor = RGB(0, 0, 0),
		DWORD italic = FALSE, DWORD underlined = FALSE, DWORD strikeOut = FALSE);
};