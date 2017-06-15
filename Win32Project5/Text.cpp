#include "stdafx.h"
#include "Text.h"

namespace Forms
{
	wstring Text::GetString()
	{
		wstringstream ws;
		ws << text << endl
			<< Name() << L" (" << GetX() << L", " << GetY() << L") Width: " << GetW() << L" Height: " << GetH() << endl
			<< "ColorARGB(" << GetColor().GetA() << L", " << GetColor().GetR() << L", " << GetColor().GetG() << L", " << GetColor().GetB() << ")";
		return ws.str();
	}

	void Text::Draw(Graphics &graphics, HDC hdc)
	{
		SolidBrush brush(color);
		FontFamily fontFamily(const_cast<wchar_t*>(font.c_str()));
		Font f(&fontFamily, fontSize, FontStyleRegular, UnitPixel);
		RectF boundRect;
		////graphics.MeasureString(text.c_str(), text.length(), &f, RectF(0, 0, 1000, 1000), &boundRect);
		//this->w = boundRect.Width;
		//this->h = boundRect.Height;
  //      RECT rect{ x, y, w, h };
  //      DrawText(hdc, text.c_str(), text.length(), &rect, DT_RIGHT | DT_VCENTER);
  //      //graphics.DrawString(const_cast<wchar_t*>(text.c_str()), -1, &f, pointF, &brush);

        graphics.MeasureString(text.c_str(), text.length(), &f, RectF(0, 0, w, h), &boundRect);
        PointF pointF(leftToRight ? x : x + w - boundRect.Width, y + h / 2 - boundRect.Height / 2.0f);
        graphics.DrawString(const_cast<wchar_t*>(text.c_str()), -1, &f, pointF, &brush);
	}
}

