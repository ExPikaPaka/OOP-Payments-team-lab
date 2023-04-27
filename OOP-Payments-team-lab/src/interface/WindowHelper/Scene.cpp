#include "Scene.h"


Scene::Scene() {
	width = 0;
	dc = 0;
	memDC = 0;
	width = 0;
	height = 0;
	memBM = 0;
}

Scene::Scene(HWND& window, MSG& msg) {
	this->window = &window;
	this->msg = &msg;
}

HWND window;
HDC dc;
HDC memDC;
int width, height;
RECT windowRect;

HBITMAP memBM;
COLORREF backgroundColor;
COLORREF brushColor;
COLORREF penColor;


void Scene::beginPaint() {
	dc = GetDC(*window);
	memDC = CreateCompatibleDC(dc);

	GetWindowRect(*window, &windowRect);

	width = windowRect.right - windowRect.left - 16;
	height = windowRect.bottom - windowRect.top - 39;

	memBM = CreateCompatibleBitmap(dc, width, height);
	SelectObject(memDC, memBM);
	selectPenAndBrush();

	brushColor = backgroundColor;
	penColor = backgroundColor;

	rect(0, 0, width, height);
}

void Scene::endPaint() {
	swapBuffer();
	SelectObject(memDC, memBM);
	DeleteObject(memBM);
	DeleteDC(memDC);
	ReleaseDC(*window, dc);
}

void Scene::swapBuffer() {
	BitBlt(dc, 0, 0, width, height, memDC, 0, 0, SRCCOPY);
}

void Scene::setObject(HGDIOBJ obj) {
	SelectObject(memDC, obj);
}

void Scene::selectPenAndBrush() {
	SelectObject(memDC, GetStockObject(DC_BRUSH));
	SelectObject(memDC, GetStockObject(DC_PEN));

	setColor();
}
void Scene::setColor() {
	SetDCBrushColor(memDC, brushColor);
	SetDCPenColor(memDC, penColor);
}

void Scene::setColor(COLORREF color) {
	setBrushColor(color);
	setPenColor(color);
}

void Scene::setColor(int rCol, int gCol, int bCol) {
	setColor(RGB(rCol, gCol, bCol));
}

void Scene::setBrushColor(COLORREF color) {
	brushColor = color;
}
void Scene::setPenColor(COLORREF color) {
	penColor = color;
}

void Scene::poly(POINT* pt, int ptCount) {
	setColor();
	Polygon(memDC, pt, ptCount);
}

void Scene::rect(int x0, int y0, int x1, int y1) {
	setColor();
	Rectangle(memDC, x0, y0, x1, y1);
}
void Scene::line(int x0, int y0, int x1, int y1) {
	setColor();
	MoveToEx(memDC, x0, y0, 0);
	LineTo(memDC, x1, y1);
}
void Scene::boundingBox(int x0, int y0, int x1, int y1) {
	setColor();
	MoveToEx(memDC, x0, y0, 0);
	LineTo(memDC, x1, y0);
	LineTo(memDC, x1, y1);
	LineTo(memDC, x0, y1);
	LineTo(memDC, x0, y0);
}
void Scene::ellipse(int x0, int y0, int x1, int y1) {
	setColor();
	Ellipse(memDC, x0, y0, x1, y1);
}
void Scene::text(wchar_t message[], int x, int y, int textWidth, int textHeight,
	int charWidth, int charHeight, wchar_t fontName[],
	COLORREF fontColor, COLORREF bkColor,
	DWORD italic, DWORD underlined, DWORD strikeOut) {


	HFONT font = CreateFont(
		charHeight, charWidth, 0, 0, FW_DONTCARE, italic, underlined, strikeOut,
		DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS,
		CLEARTYPE_QUALITY, VARIABLE_PITCH, fontName);

	SelectObject(memDC, font);

	SetTextColor(memDC, fontColor);
	SetBkColor(memDC, bkColor);

	RECT rect;
	rect.left = x; rect.top = y;
	rect.right = textWidth + x; rect.bottom = y + textHeight;

	DrawText(memDC, message, -1, &rect, DT_WORDBREAK | DT_EDITCONTROL);
	DeleteObject(font);
}
