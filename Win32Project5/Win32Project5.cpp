// Win32Project5.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32Project5.h"
#include "VisualElement.h"
#include "Ellipse.h"
#include "Rectangle.h"
#include "Text.h"
#include "Button.h"

HINSTANCE hInst;

//true - zdarzenie zostało obsłużone w tej funkcji, false - zdarzenie zostanie obsłużone w wndProc
bool func(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	int wmId = LOWORD(wParam);
	switch (wmId)
	{
    case IDM_EXIT:
        DestroyWindow(hWnd);
        return true;
	}
	return false;
}

std::wstring w = L"0";
std::wstring ww = L"0";
wchar_t op;

bool first = true;
Forms::Text *TextOnCalc;

void func2(Forms::VisualElement* sender)
{
    auto cmd = ((Forms::Button*)sender)->text;

    for (auto i = 0; i <= 9; i++)
    {
        std::wstring& s = first ? w : ww;
        if (i + '0' == cmd[0])
        {
            if (s == L"0")
            {
                if (i == 0)
                    return;
                s = cmd[0];
                TextOnCalc->SetText(s);
                return;
            }
            s.append(cmd);
            TextOnCalc->SetText(s);
            return;
        }
    }

    if (cmd[0] == '.')
    {
        std::wstring& s = first ? w : ww;
        if (s.find('.') == std::string::npos)
            s.append(L".");
        TextOnCalc->SetText(s);
        return;
    }

    if (cmd[0] == '+' ||
        cmd[0] == '-' ||
        cmd[0] == '*' ||
        cmd[0] == '/')
    {
        first = false;
        std::wstring& s = first ? w : ww;
        op = cmd[0];
        TextOnCalc->SetText(s);
    }

    if (cmd[0] == '=')
    {
        first = true;
        std::wstring& s = first ? w : ww;
        auto l = wcstod(w.c_str(), nullptr);
        auto r = wcstod(ww.c_str(), nullptr);
        ww = L"0";
        
        switch (op)
        {
        case '+':
            l += r;
            break;
        case '-':
            l -= r;
            break;
        case '*' :
            l *= r;
            break;
        case '/' :
            l /= r;
            break;
        }
        s = std::to_wstring(l);
        TextOnCalc->SetText(s);

    }
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	hInst = hInstance;

	Forms::Window::Init(hInstance);
	auto main_window = new Forms::Window(nCmdShow, 1, 1, 270, 370, L"Kalkulator", L"Kalkulator");

    main_window->AddElement(new Forms::Rectangle(10, 10, 230, 50, 1, Color(0, 0, 0)));

    TextOnCalc = new Forms::Text(10, 10, 230, 50, L"0", L"Segoe UI", 22, Color(0, 0xff, 0), false);
    main_window->AddElement(TextOnCalc);

    main_window->AddElement((new Forms::Button(10,  70,  50,  50, 0, L"Segoe UI", 18, L"7", Color(255, 0, 0)))->SetButtonHandler(func2));
    main_window->AddElement((new Forms::Button(70,  70,  50,  50, 0, L"Segoe UI", 18, L"8", Color(255, 0, 0)))->SetButtonHandler(func2));
    main_window->AddElement((new Forms::Button(130, 70,  50,  50, 0, L"Segoe UI", 18, L"9", Color(255, 0, 0)))->SetButtonHandler(func2));
    main_window->AddElement((new Forms::Button(10,  130, 50,  50, 0, L"Segoe UI", 18, L"4", Color(255, 0, 0)))->SetButtonHandler(func2));
    main_window->AddElement((new Forms::Button(70,  130, 50,  50, 0, L"Segoe UI", 18, L"5", Color(255, 0, 0)))->SetButtonHandler(func2));
    main_window->AddElement((new Forms::Button(130, 130, 50,  50, 0, L"Segoe UI", 18, L"6", Color(255, 0, 0)))->SetButtonHandler(func2));
    main_window->AddElement((new Forms::Button(10,  190, 50,  50, 0, L"Segoe UI", 18, L"1", Color(255, 0, 0)))->SetButtonHandler(func2));
    main_window->AddElement((new Forms::Button(70,  190, 50,  50, 0, L"Segoe UI", 18, L"2", Color(255, 0, 0)))->SetButtonHandler(func2));
    main_window->AddElement((new Forms::Button(130, 190, 50,  50, 0, L"Segoe UI", 18, L"3", Color(255, 0, 0)))->SetButtonHandler(func2));
    main_window->AddElement((new Forms::Button(10,  250, 50,  50, 0, L"Segoe UI", 18, L"0", Color(255, 0, 0)))->SetButtonHandler(func2));
    main_window->AddElement((new Forms::Button(70,  250, 50,  50, 0, L"Segoe UI", 18, L".", Color(255, 0, 0)))->SetButtonHandler(func2));
    main_window->AddElement((new Forms::Button(190, 70,  50,  50, 0, L"Segoe UI", 18, L"+", Color(255, 0, 0)))->SetButtonHandler(func2));
    main_window->AddElement((new Forms::Button(190, 130, 50,  50, 0, L"Segoe UI", 18, L"-", Color(255, 0, 0)))->SetButtonHandler(func2));
    main_window->AddElement((new Forms::Button(190, 190, 50,  50, 0, L"Segoe UI", 18, L"*", Color(255, 0, 0)))->SetButtonHandler(func2));
    main_window->AddElement((new Forms::Button(190, 250, 50,  50, 0, L"Segoe UI", 18, L"/", Color(255, 0, 0)))->SetButtonHandler(func2));
    main_window->AddElement((new Forms::Button(130, 250, 50,  50, 0, L"Segoe UI", 18, L"=", Color(255, 0, 0)))->SetButtonHandler(func2));


	main_window->AddEventListener(WM_COMMAND, func);

	Forms::Window::MainLoop();
	Forms::Window::Destroy();
	return 0;
}
