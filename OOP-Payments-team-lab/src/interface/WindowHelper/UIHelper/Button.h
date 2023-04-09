#pragma once
#include <Windows.h>
#include "../Scene.h"

namespace UIHelper {
	class Button {
	protected:
		Scene* scene;
		int x;
		int y;
		int w;
		int h;

		bool hovered;
		bool pressed;

		COLORREF fillColor;
		COLORREF outlineColor;

		COLORREF hoverFillColor;
		COLORREF pressedFillColor;

		COLORREF hoverOutlineColor;
		COLORREF pressedOutlineColor;

		COLORREF currentFillColor;
		COLORREF currentOutlineColor;

	public:
		Button(Scene& scene, int x, int y, int w, int h);
		Button(Scene& scene, int x, int y, int w, int h, COLORREF fillColor, COLORREF outlineColor, COLORREF hoverFillColor,
			COLORREF hoverOutlineColor, COLORREF pressedFillColor, COLORREF pressedOutlineColor);



		void draw();
		bool isPressed();
		bool isMouseInArea();
		void applyColor();

		void setFillColor(COLORREF color);
		void setOutlineColor(COLORREF color);
		void setHoverFillColor(COLORREF color);
		void setPressedFillColor(COLORREF color);
		void setHoverOutlineColor(COLORREF color);
		void setPressedOutlineColor(COLORREF color);

		void setX(int x);
		void setY(int y);
		void setW(int w);
		void setH(int h);

		int getX();
		int getY();
		int getW();
		int getH();
	};
}

