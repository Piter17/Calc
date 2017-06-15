#include "stdafx.h"
#include "Window.h"
#include "Resource.h"
#include <thread>


namespace Forms
{
	HINSTANCE Window::hInst;
	GdiplusStartupInput Window::gdiplusStartupInput;
	ULONG_PTR Window::gdiplusToken;

	ATOM Window::registerClass(wstring classname)
	{
		WNDCLASSEXW wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInst;
		wcex.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_WIN32PROJECT5));
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WIN32PROJECT5);
		wcex.lpszClassName = classname.c_str();
		wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

		return RegisterClassExW(&wcex);
	}

	void Window::AddElement(VisualElement* element)
	{
		Elements->push_back(element->SetParent(this));
		InvalidateRect(hWnd, nullptr, true);
	}

	void Window::Redraw()
	{
		InvalidateRect(hWnd, nullptr, true);
	}

	void Window::MainLoop()
	{
		// Main message loop:
		HACCEL hAccelTable = LoadAccelerators(hInst, MAKEINTRESOURCE(IDC_WIN32PROJECT5));
		MSG msg;
		while (GetMessage(&msg, nullptr, 0, 0))
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}

	void Window::Init(HINSTANCE hInstance)
	{
		hInst = hInstance;
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
	}

	void Window::Destroy()
	{
		GdiplusShutdown(gdiplusToken);
	}


	Window::Window(int nCmdShow, int x, int y, int w, int h, wstring name, wstring classname)
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		this->Name = name;
		Elements = new vector<VisualElement*>(0);
		registerClass(classname);

		hWnd = CreateWindowW(classname.c_str(), name.c_str(), WS_OVERLAPPEDWINDOW,
			x, y, w, h, nullptr, nullptr, hInst, nullptr);

		if (!hWnd)
		{
			return;
		}
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)this);

		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);
	}

	void Window::AddEventListener(UINT eventId, eventHandler func)
	{
		Events[eventId] = func;
	}

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		if (!window)
			return DefWindowProc(hWnd, message, wParam, lParam);
		if (window->Events[message])
			if (window->Events[message](hWnd, wParam, lParam))
				return 0;
		switch (message)
		{
		case WM_LBUTTONUP:
		{
			auto xPos = GET_X_LPARAM(lParam);
			auto yPos = GET_Y_LPARAM(lParam);
			for (auto& i : *(window->GetElements()))
			{
				if (i->IsInside(xPos, yPos))
				{
					if (i->ButtonHandler)
					{
						i->ButtonHandler(i);
						break;
					}
				}

			}
		}
		break;
		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			switch (wmId)
			{
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			window->OnPaint(hdc);
			EndPaint(hWnd, &ps);
		}
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return 0;
	}

	VOID Window::OnPaint(HDC hdc)
	{
		Graphics graphics(hdc);
		graphics.SetSmoothingMode(SmoothingModeHighQuality);
		for (auto& i : *Elements)
			i->Draw(graphics, hdc);
	}
}