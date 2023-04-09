#include "InputButton.h"

void UIHelper::InputButton::draw() {
	if (isMouseInArea()) {
		hovered = true;
		if (GetAsyncKeyState(VK_LBUTTON) < 0) {
			if (!pressed) {
				wtext += L"_"; // Add cursor
			}
			pressed = true;
		}
	} else {
		hovered = false;
		if (GetAsyncKeyState(VK_LBUTTON) < 0) {
			if (pressed) {
				if (wtext.size()) {
					wtext.pop_back(); // Del cursor
				}
			}
			pressed = false;
		}
	}

	applyColor();


	scene->setBrushColor(currentFillColor);
	scene->setPenColor(currentOutlineColor);

	scene->rect(x, y, x + w, y + h);

	// Inverting color
	COLORREF fotnCol = GetRValue(currentFillColor) + GetGValue(currentFillColor) + GetBValue(currentFillColor) < 382 ? RGB(255, 255, 255) : 0;

	// Drawing text
	scene->text((wchar_t*)wtext.c_str(), x, y, w, h, 7, 16, 0, fotnCol, currentFillColor);
}

#include <iostream>
bool UIHelper::InputButton::getInput() {
	if (pressed) {
		// If message == key input
		if (scene->msg->message == WM_KEYDOWN) {
			BYTE keyboardState[256] = { 0 };   // KeyBoard state
			WCHAR buffer[2] = { 0 };	       // Text buffer
			HKL layout = GetKeyboardLayout(0); // Get the current input locale

			int kbState = GetKeyboardState(keyboardState);

			if (kbState) {
				// Convert the virtual-key code and keyboard state to Unicode character
				if (ToUnicodeEx(scene->msg->wParam, scene->msg->lParam, keyboardState, buffer, 2, 0, layout)) {


					if (buffer[0] == VK_RETURN || buffer[0] == VK_ESCAPE) { // If enter or ESC pressed - end input
						if (wtext.size()) {
							wtext.pop_back(); // Del cursor
						}
						pressed = false;
						return true;
					} else if (buffer[0] == VK_BACK) { // If Backspace pressed - delete last char
						if (wtext.size()) {
							wtext.pop_back();
							if (wtext.size()) {
								wtext.pop_back();
							}
						}			
						wtext += L"_";	// Add cursor

					} else if (buffer[0] > 31) { // If it's not spec sybmol - read char
						buffer[0] = buffer[0] == 1110 ? 'i' : buffer[0]; // Replacing ukrainian i with englis i, because cant fit 1110 in 2 bytes
						buffer[0] = buffer[0] == 1030 ? 'I' : buffer[0]; // Replacing ukrainian I with ienglis I, because cant fit 1110 in 2 bytes

						if (wtext.size()) {
							wtext.pop_back(); // Del cursor
						}
						wtext += buffer[0];
						text = wstringToString(wtext);
						wtext += L"_"; // Add cursor
					}
				}
			}
		}
	}
	return false;
}

std::string UIHelper::InputButton::wstringToString(const std::wstring& wstr) {
	if (wstr.empty()) {
		return std::string();
	}

	const int size_needed = WideCharToMultiByte(1251, 0, &wstr[0], static_cast<int>(wstr.size()), nullptr, 0, nullptr, nullptr);
	std::string str(size_needed, 0);
	WideCharToMultiByte(1251, 0, &wstr[0], static_cast<int>(wstr.size()), &str[0], size_needed, nullptr, nullptr);
	return str;
}