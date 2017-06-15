#include "stdafx.h"
#include "Button.h"

void Forms::Button::Draw(Graphics& graphics, HDC hdc)
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
    SolidBrush brush(color);
    FontFamily fontFamily(const_cast<wchar_t*>(font.c_str()));
    Font f(&fontFamily, fontSize, FontStyleRegular, UnitPixel);
    RectF boundRect;
    graphics.MeasureString(text.c_str(), text.length(), &f, RectF(0, 0, w, h), &boundRect);
    PointF pointF(x + w / 2 - boundRect.Width / 2.0f, y + h / 2 - boundRect.Height / 2.0f);
    graphics.DrawString(const_cast<wchar_t*>(text.c_str()), -1, &f, pointF, &brush);
}

double Forms::Button::GetArea()
{
    return x*y;
}

bool Forms::Button::IsInside(int Cx, int Cy)
{
    return (Cx >= x && Cx < x + w) && (Cy >= y && Cy < y + h);
}