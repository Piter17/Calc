#pragma once
#include "stdafx.h"
#include "VisualElement.h"

namespace Forms
{
	class Rectangle : public VisualElement
	{
	public:
		Rectangle(int x, int y, int w, int h, bool f, Color color)
		{
			this->color = color;
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
			this->filled = f;
		}
		bool filled;
		wstring Name() { return L"Rectangle"; }
		void Draw(Graphics &graphics, HDC hdc) override;
		double GetArea() override;
		bool IsInside(int x, int y) override;
	};

	inline void Forms::Rectangle::Draw(Graphics& graphics, HDC hdc)
	{
		if (filled)
		{
			SolidBrush brush(color);
			graphics.FillRectangle(&brush, x, y, w, h);
		}
		else
		{
			Pen pen(color);
			graphics.DrawRectangle(&pen, x, y, w, h);
		}
	}

	inline double Forms::Rectangle::GetArea()
	{
		return x*y;
	}

	inline bool Forms::Rectangle::IsInside(int Cx, int Cy)
	{
		return (Cx >= x && Cx < x + w) && (Cy >= y && Cy < y + h);
	}
}

