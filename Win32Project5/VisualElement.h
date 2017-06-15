#pragma once
#include "stdafx.h"
#include "Window.h"

namespace Forms
{
	class Window;
	class VisualElement
	{
	private:
		friend class Window;
		VisualElement* SetParent(Window* x) { parent = x; return this; }
		Window *parent;
        bool _visible;
	protected:
		int x, y, w, h;
		Color color;
	public:
		Window* GetParent() { return parent; }
		void(*ButtonHandler)(VisualElement*);
		VisualElement* SetButtonHandler(void(*x)(VisualElement*)) { ButtonHandler = x; return this; }
		virtual void Draw(Graphics &graphics, HDC hdc) {};
		virtual wstring Name() { return L"VisualElement"; }
		virtual double GetArea() { return 0.0; }
		virtual bool IsInside(int Cx, int Cy) { return  (Cx >= x && Cx < x + w) && (Cy >= y && Cy < y + h); }
		int GetX() { return x; }
		int GetY() { return y; }
		int GetW() { return w; }
		int GetH() { return h; }
		Color GetColor() { return color; }
		void SetColor(Color x) { color = x; }
		virtual wstring GetString()
		{
			wstringstream ws;
			ws << Name() << L" (" << GetX() << L", " << GetY() << L") Width: " << GetW() << L" Height: " << GetH() << endl
				<< "ColorARGB(" << GetColor().GetA() << L", " << GetColor().GetR() << L", " << GetColor().GetG() << L", " << GetColor().GetB() << ")";
			return ws.str();
		}
	};
}