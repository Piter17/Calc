#pragma once
#include "stdafx.h"
#include "VisualElement.h"
#define MAX_LOADSTRING 100

namespace Forms
{
	class VisualElement;
	//true wydarzenie obsłużone, false od obsłużenia w wndProc
	typedef bool(*eventHandler)(HWND, WPARAM, LPARAM);
	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	class Window
	{
	private:
		friend LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		ATOM registerClass(wstring classname);
		vector<VisualElement*>* Elements;
		HWND hWnd;
		map<UINT, bool(*)(HWND, WPARAM, LPARAM)> Events;
		static GdiplusStartupInput gdiplusStartupInput;
		static ULONG_PTR gdiplusToken;
	public:
        HWND GetHwnd() { return hWnd; }
		void Redraw();
		vector<VisualElement*>* GetElements() { return Elements; }
		void AddEventListener(UINT, eventHandler);
		void AddElement(VisualElement* element);
		static void MainLoop();
		static void Init(HINSTANCE hInstance);
		static void Destroy();
		VOID OnPaint(HDC hdc);
		static HINSTANCE hInst;
		WCHAR szTitle[MAX_LOADSTRING];
		int x, y, w, h;
		wstring Name;
		Window(int nCmdShow, int x, int y, int w, int h, wstring name, wstring classname);
	};
}