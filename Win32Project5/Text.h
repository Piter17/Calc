#pragma once
#include "stdafx.h"
#include "VisualElement.h"

namespace Forms
{
	class Text : public VisualElement
	{
	public:
        Text(int x, int y, int w, int h, wstring text, wstring font, float fontSize, Color color, bool leftToRight = true)
		{
			this->color = color;
			this->x = x;
			this->y = y;
            this->w = w;
            this->h = h;
			this->text = text;
			this->font = font;
			this->fontSize = fontSize;
            this->leftToRight = leftToRight;
		}
        bool leftToRight;
		wstring Name() { return L"Text"; }
		wstring GetString() override;
		wstring text;
		wstring font;
		float fontSize;
		void Draw(Graphics &graphics, HDC hdc) override;
        void SetText(wstring text)
        {
            this->text = text;
            RECT rect;
            GetClientRect(GetParent()->GetHwnd(), &rect);
            RedrawWindow(GetParent()->GetHwnd(), &rect, nullptr, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
        }
    };
}

