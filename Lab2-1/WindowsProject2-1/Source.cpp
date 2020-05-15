//#define RGB(r, g, b) ((COLORREF)(((BYTE)(r) | ((WORD)(g) << 8)) | ((DWORD)(BYTE)(b)) << 16))
#include <Windows.h>
#include <Windowsx.h>
#include<tchar.h>
const int x = 400;
const int y = 400;
static HBRUSH bRhus[2];
static int gRhus_index = 0;

LRESULT CALLBACK SecondWNDProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)

{
	HWND hWnd;
	WNDCLASS WndClass;
	MSG Msg;
	TCHAR szClassName[] = _T("SecondWindow");// имя класса !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	TCHAR szTitel[] = _T("Мирсонов Лаб.2-2");//имя окна !!!!!!!!!!!!!!!

	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = SecondWNDProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;// указатель на строку, содержащую имя меню, применяемого для класса
	WndClass.hIcon = LoadIcon(NULL,IDI_QUESTION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(100,0,0));
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = szClassName;
	 
	if (!RegisterClass(&WndClass))
	{
		MessageBox(NULL, _T("Cannot register class"), _T("Error"), MB_OK);
		return 0;
	}

	hWnd = CreateWindow(szClassName, szTitel, WS_OVERLAPPEDWINDOW, x, y, x, y, NULL, NULL, hInstance, NULL);//функция, содержащая окно

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

LRESULT CALLBACK SecondWNDProc(HWND hWnd, UINT Message, UINT wParam, LONG lParam)
{
	bool crea = false;
	HDC hDC;
	HWND HHw, hW;
	RECT Rect;
	PAINTSTRUCT PaintStruct;
	HBRUSH hBrush;
	//hBrush = RGB(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0);
	switch (Message)
	{
	case WM_USER + 2:
		{
			hW = GetForegroundWindow();
			MessageBox(hWnd, TEXT("Получена WM_USER+2."), TEXT("Будет изменен цвет."), MB_ICONASTERISK);
			InvalidateRect(hWnd, NULL, TRUE);
			//SendMessageW(hWnd, WM_CREATE, NULL,NULL);
			//ShowWindow(hWnd, SW_MINIMIZE);
			//PostMessage(hWnd, WM_USER + 3, NULL, NULL);
			break;
		}
	case WM_USER + 1:
	{
		MessageBox(hWnd, TEXT("Получена WM_USER+1."), TEXT("Дескриптор первого окна получен"), MB_ICONASTERISK);
		break;
	}
	case WM_USER + 3:
	{
		ShowWindow(hWnd, SW_SHOWDEFAULT);
	}
	case WM_PAINT:
	{
		hDC = BeginPaint(hWnd, &PaintStruct);
		GetClientRect(hWnd, &Rect);
		HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0));
		FillRect(hDC, &Rect, hBrush);
		//SetBkColor(hDC, RGB(205, 133, 63));
		EndPaint(hWnd, &PaintStruct);
	}
	case WM_CREATE:
	{
		//SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0)));
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, Message, wParam, lParam);
}