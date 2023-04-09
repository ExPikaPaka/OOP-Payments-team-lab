#pragma once
#include <string>
#include "Button.h"

namespace UIHelper {
	class InputButton : public Button {

		std::string wstringToString(const std::wstring& wstr);
	public:
		std::string text;
		std::wstring wtext;

		InputButton(Scene& scene, int x, int y, int w, int h) : Button(scene, x, y, w, h) {};
		InputButton(Scene& scene, int x, int y, int w, int h, COLORREF fillColor, COLORREF outlineColor, COLORREF hoverFillColor,
			COLORREF hoverOutlineColor, COLORREF pressedFillColor, COLORREF pressedOutlineColor) : Button(scene, x, y, w, h, fillColor, outlineColor, hoverFillColor,
				hoverOutlineColor, pressedFillColor, pressedOutlineColor) {
		};

		void draw();
		bool getInput();
	};
}

