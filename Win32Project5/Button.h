#pragma once
#include "VisualElement.h"

namespace Forms
{
    class Button : public VisualElement
    {
    public:
        Button(int x, int y, int w, int h, bool f, wstring font, float fontSize, wstring text, Color color)
        {
            this->color = color;
            this->x = x;
            this->y = y;
            this->w = w;
            this->h = h;
            this->filled = f;
            this->fontSize = fontSize;
            this->font = font;
            this->text = text;
        }

        Button()
        {
            color = Color();
            x = 0;
            y = 0;
            h = 120;
            w = 26;
            filled = false;
            fontSize = 14;
            font = L"Segoe UI";
            text = L"Button";
        }

        wstring font;
        bool filled;
        float fontSize;
        wstring text;
        wstring Name() { return L"Button"; }
        void Draw(Graphics &graphics, HDC hdc) override;
        double GetArea() override;
        bool IsInside(int x, int y) override;
    };
};