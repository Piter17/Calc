#pragma once

#include "stdafx.h"
#include "VisualElement.h"

namespace Forms
{
	class Ellipse : public VisualElement
	{
	public:
		Ellipse(int x, int y, int w, int h, bool f, Color color)
		{
			this->color = color;
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
			this->filled = f;
		}
		wstring Name() { return L"Ellipse"; }
		bool filled;
		void Draw(Graphics &graphics, HDC hdc) override;
		double GetArea() override;
		bool IsInside(int x, int y) override;
	};
}