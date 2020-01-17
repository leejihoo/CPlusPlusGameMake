#define WIN32_LEAN_AND_MEAN
//#include <atlstr.h>
#include<windows.h>

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int);
bool CreateMainWindow(HINSTANCE, int);
LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hinst;

const char CLASS_NAME[] = "WinMain";
const char APP_TITLE[] = "C++과DirectX로게임제작";
const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 400;
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
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool CreateMainWindow(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcx;
	HWND hwnd;

	wcx.cbSize = sizeof(wcx);
	wcx.style = CS_HREDRAW | CS_VREDRAW;
	wcx.lpfnWndProc  = WinProc;
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

//아무말아무말
