#define WM_SETTEXT                      0x000C
#include <Windows.h>
#include <Windowsx.h>
#include<tchar.h>
const int x = 400;
const int y = 400;
wchar_t name[128];


LRESULT CALLBACK FirstWNDProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	WNDCLASS WndClass;
	MSG Msg;
	TCHAR szClassName[] = _T("FirstWindow");
	TCHAR szTitel[] = _T("Мирсонов Лаб.2-1");

	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = FirstWNDProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(255,255,50));
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = szClassName;
	if (!RegisterClass(&WndClass))
	{
		MessageBox(NULL, _T("Cannot register class"), _T("Error"), MB_OK);
		return 0;
	}

	hWnd = CreateWindow(szClassName, szTitel, WS_OVERLAPPEDWINDOW, x, y, x, y, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		MessageBox(NULL, _T("Cannot create window"), _T("Error"), MB_OK);
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Msg, NULL, 0, 0))
	{
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}

LRESULT CALLBACK FirstWNDProc(HWND hWnd, UINT Message, UINT wParam, LONG lParam)
{
	static int left, bott;
	bool crea = false;
	LPWSTR szText = new TCHAR[MAX_PATH];
	LPWSTR szText1 = NULL;
	HWND hw,HHw;
	HDC hDC;
	switch (Message)
	{
	case WM_LBUTTONDOWN:
		HHw = GetForegroundWindow();
		hw = FindWindow(TEXT("SecondWindow"), TEXT("Мирсонов Лаб.2-2"));// найти дискриптор окна 2
		GetWindowText(hw, szText, MAX_PATH);
		if (hw != 0x0000000)
		{
			MessageBox(hWnd, TEXT("Окно открыто, дескриптор получен: заголовки данного окна и окна чей дескриптор стремились получить - совпадают."), szText, MB_ICONASTERISK);
		}
		else
		{
			MessageBox(0, TEXT("Окно закрыто."), TEXT("Дескриптор не получен"), MB_ICONHAND);
		}

		GetWindowText(HHw, name, sizeof(name));
		PostMessage(hw, WM_USER + 2, NULL, NULL);
		break;

	case WM_RBUTTONDOWN:
		hw = FindWindow(TEXT("SecondWindow"), TEXT("Мирсонов Лаб.2-2"));
		SendMessage(hw, WM_SETTEXT, NULL, (LPARAM)name);
		PostMessage(hw, WM_USER + 1, NULL, (LPARAM)name);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, Message, wParam, lParam);
}