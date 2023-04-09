#include "Button.h"

UIHelper::Button::Button(Scene& scene, int x, int y, int w, int h) {
	this->scene = &scene;
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;

	hovered = false;
	pressed = false;

	fillColor = 0;
	outlineColor = 0;

	hoverFillColor = RGB(255, 255, 255);
	pressedFillColor = 0;

	hoverOutlineColor = RGB(255, 255, 255);
	pressedOutlineColor = 0;

	currentFillColor = fillColor;
	currentOutlineColor = outlineColor;
}

UIHelper::Button::Button(Scene& scene, int x, int y, int w, int h, COLORREF fillColor, COLORREF outlineColor, COLORREF hoverFillColor,
	COLORREF hoverOutlineColor, COLORREF pressedFillColor, COLORREF pressedOutlineColor) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;

	hovered = false;
	pressed = false;

	this->scene = &scene;

	this->fillColor = fillColor;
	this->outlineColor = outlineColor;

	this->hoverFillColor = hoverFillColor;
	this->pressedFillColor = pressedFillColor;

	this->hoverOutlineColor = hoverOutlineColor;
	this->pressedOutlineColor = pressedOutlineColor;

	this->currentFillColor = fillColor;
	this->currentOutlineColor = outlineColor;
}


void UIHelper::Button::draw() {
	isPressed();
	applyColor();


	scene->setBrushColor(currentFillColor);
	scene->setPenColor(currentOutlineColor);

	scene->rect(x, y, x + w, y + h);
}

bool UIHelper::Button::isPressed() {
	hovered = false;
	pressed = false;
	if (isMouseInArea()) {
		hovered = true;
		if (GetAsyncKeyState(VK_LBUTTON) < 0) {
			pressed = true;
		}
	}
	return pressed;
}

bool UIHelper::Button::isMouseInArea() {
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(*scene->window, &mouse);

	return mouse.x > x && mouse.x < x + w && mouse.y > y && mouse.y < y + h;
}

void UIHelper::Button::applyColor() {
	currentFillColor = fillColor;
	currentOutlineColor = outlineColor;

	if (hovered) {
		currentFillColor = hoverFillColor;
		currentOutlineColor = hoverOutlineColor;
	}
	if (pressed) {
		currentFillColor = pressedFillColor;
		currentOutlineColor = pressedOutlineColor;
	}
}

void UIHelper::Button::setFillColor(COLORREF color) {
	fillColor = color;
}

void UIHelper::Button::setOutlineColor(COLORREF color) {
	outlineColor = color;
}

void UIHelper::Button::setHoverFillColor(COLORREF color) {
	hoverFillColor = color;
}

void UIHelper::Button::setPressedFillColor(COLORREF color) {
	pressedFillColor = color;
}

void UIHelper::Button::setHoverOutlineColor(COLORREF color) {
	hoverOutlineColor = color;
}

void UIHelper::Button::setPressedOutlineColor(COLORREF color) {
	pressedOutlineColor = color;
}

void UIHelper::Button::setX(int x) {
	this->x = x;
}

void UIHelper::Button::setY(int y) {
	this->y = y;
}

void UIHelper::Button::setW(int w) {
	this->w = w;
}

void UIHelper::Button::setH(int h) {
	this->h = h;
}

int UIHelper::Button::getX() {
	return x;
}

int UIHelper::Button::getY() {
	return y;
}

int UIHelper::Button::getW() {
	return w;
}

int UIHelper::Button::getH() {
	return h;
}
