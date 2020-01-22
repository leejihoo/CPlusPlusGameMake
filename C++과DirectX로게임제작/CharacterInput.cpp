#define WIN32_LEAN_AND_MEAN
//#include <atlstr.h>
#include<windows.h>

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int);
bool CreateMainWindow(HINSTANCE, int);
LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hinst;
HDC hdc;
TCHAR ch = ' ';
RECT rect;
PAINTSTRUCT ps;


const char CLASS_NAME[] = "WinMain";
const char APP_TITLE[] = "Character Input";
const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 300;
bool vkKeys[0x100];
SHORT nVirtKey;
//LPCWSTR LCLASS_NAME = CA2W(CLASS_NAME,949);
//LPCWSTR LAPP_TITLE = CA2W(APP_TITLE, 949);
int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow)
{
	MSG msg;
	if (!CreateMainWindow(hInstance, nCmdShow)) //본문과다름
	{
		return false;
	}
	int done = 0;
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				done = 1;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}

LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CHAR:
		switch (wParam)
		{
		case 0x08:
		case 0x09:
		case 0x0A:
		case 0x0D:
		case 0x1B:
			MessageBeep((UINT)-1);
			return 0;
		default:
			ch = (TCHAR)wParam;
			InvalidateRect(hWnd, NULL, TRUE);
			return 0;
		}
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		TextOut(hdc, rect.right / 2, rect.bottom / 2, &ch, 1);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_KEYDOWN:
		vkKeys[wParam] = true;
		switch (wParam) {
		case VK_SHIFT:
			nVirtKey = GetKeyState(VK_LSHIFT);
			if (nVirtKey)
				//vkKeys[VK_LSHIFT] = true;
				//MessageBeep((UINT)-1);
			nVirtKey = GetKeyState(VK_RSHIFT);
			if (nVirtKey)
				//vkKeys[VK_RSHIFT] = true;
				//MessageBeep((UINT)-1);
			break;
		case VK_CONTROL:
			nVirtKey = GetKeyState(VK_LCONTROL);
			if (nVirtKey)
				vkKeys[VK_LCONTROL] = true;
			nVirtKey = GetKeyState(VK_RCONTROL);
			if (nVirtKey)
				vkKeys[VK_RCONTROL] = true;
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
		break;
	case WM_KEYUP:
		vkKeys[wParam] = false;
		switch (wParam)
		{
		case VK_SHIFT:
			nVirtKey = GetKeyState(VK_LSHIFT);
			if (nVirtKey)
				//vkKeys[VK_LSHIFT] = false;
			MessageBeep((UINT)-1);
			nVirtKey = GetKeyState(VK_RSHIFT);
			if (nVirtKey)
				//vkKeys[VK_RSHIFT] = false;
				MessageBeep((UINT)-1);
			break;
		case VK_CONTROL:
			nVirtKey = GetKeyState(VK_LCONTROL);
			if (nVirtKey)
				//vkKeys[VK_LCONTROL] = false;
				MessageBeep((UINT)-1);
			nVirtKey = GetKeyState(VK_RCONTROL);
			if (nVirtKey)
				//vkKeys[VK_RCONTROL] = false;
				MessageBeep((UINT)-1);
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}

bool CreateMainWindow(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcx;
	HWND hwnd;

	wcx.cbSize = sizeof(wcx);
	wcx.style = CS_HREDRAW | CS_VREDRAW;
	wcx.lpfnWndProc = WinProc;
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hInstance = hInstance;
	wcx.hIcon = NULL;
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcx.lpszMenuName = NULL;
	wcx.lpszClassName = CLASS_NAME; // 본문과 다름
	wcx.hIconSm = NULL;

	if (RegisterClassEx(&wcx) == 0)
		return false;

	hwnd = CreateWindow(
		CLASS_NAME, //본문과 다름
		APP_TITLE, //본문과 다름
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		(HWND)NULL,
		(HMENU)NULL,
		hInstance,
		(LPVOID)NULL
	);
	if (!hwnd)
		return false;
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd); //본문과다름
	return true;
}

