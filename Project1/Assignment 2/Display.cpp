#include "Display.h"
 // the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

Display::Display()
{

}

Display::Display(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, int width, int height)
{

	// this struct holds information for the window class
	WNDCLASSEX _wc;

	// clear out the window class for use
	ZeroMemory(&_wc, sizeof(WNDCLASSEX));

	// fill in the struct with the needed information
	_wc.cbSize = sizeof(WNDCLASSEX);
	_wc.style = CS_HREDRAW | CS_VREDRAW;
	_wc.lpfnWndProc = WindowProc;
	_wc.hInstance = hInstance;
	_wc.hCursor = (HCURSOR)LoadImage(NULL, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_SHARED);
	_wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	_wc.lpszClassName = "WindowClass1";

	// register the window class
	RegisterClassEx(&_wc);

	RECT rc = { 0, 0, width, height };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	// create the window and use the result as the handle
	m_hWnd = CreateWindowEx(NULL,
		"WindowClass1",    // name of the window class
		"Spelmotor ark",    // title of the window
		WS_OVERLAPPEDWINDOW,    // window style
		//CW_USEDEFAULT,    // x-position of the window
		//CW_USEDEFAULT,    // y-position of the window
		1000,					//Insted, so it doens't overlap with the taskbar
		0,
		//width,    // width of the window
		//height,    // height of the window
		rc.right - rc.left,
		rc.bottom - rc.top,
		NULL,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		hInstance,    // application handle
		NULL);    // used with multiple windows, NULL

	ShowWindow(m_hWnd, nCmdShow);
	ShowCursor(true);
}

Display::~Display()
{

}

HWND Display::GethWnd()
{
	return m_hWnd;
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// sort through and find what code to run for the message given
	switch (message)
	{
		// this message is read when the window is closed
	case WM_DESTROY:
	{
		// close the application entirely
		PostQuitMessage(0);
		return 0;
	} break;
	}

	// Handle any messages the switch statement didn't
	return DefWindowProc(hWnd, message, wParam, lParam);
}