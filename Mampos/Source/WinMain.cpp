#include "pch.h"

/* ------------------------------------------------------- */
/* FileName: WinMain.cpp                                   */
/* Author: Diego                                           */
/* Licences: MIT Licence                                   */
/* ------------------------------------------------------- */
	
/* ------------------------------------------------------- */
/* Global variable                                         */
/* ------------------------------------------------------- */
#pragma region GlobalVariables
	WCHAR			WindowClass[MAX_NAME_STRING];
	WCHAR			WindowMenuName[MAX_NAME_STRING];
	WCHAR			WindowTitle[MAX_NAME_STRING];

	INT				WindowWidth;
	INT				WindowHeight;

	HICON			hIcon;
	
#pragma endregion
/* ------------------------------------------------------- */

/* ------------------------------------------------------- */
/* Pre-declarations                                        */
/* ------------------------------------------------------- */
#pragma region Pre-declarations
LRESULT CALLBACK WindowProcess(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);
VOID InitializeVariables();
VOID CreateWindowClass();
VOID InitializeWindow();
VOID MessageLoop();
#pragma endregion
/* ------------------------------------------------------- */

/* ------------------------------------------------------- */
/* Operations                                              */
/* ------------------------------------------------------- */
#pragma region Operations
int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
	InitializeVariables();
	CreateWindowClass();
	//CreateWindowClass2();
	InitializeWindow();
	MessageLoop();

	return 0;
}
#pragma endregion
/* ------------------------------------------------------- */

/* ------------------------------------------------------- */
/* Functions                                               */
/* ------------------------------------------------------- */
#pragma region Functions
LRESULT CALLBACK WindowProcess(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		HMENU hMenu = CreateMenu();;
		AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hMenu, L"Lineas guía");
		AppendMenu(hMenu, MF_POPUP, NULL, L"Dibujar");
		AppendMenu(hMenu, MF_POPUP, NULL, L"Análisis");
		AppendMenu(hMenu, MF_POPUP, NULL, L"Memoria de cálculo");
		AppendMenu(hMenu, MF_POPUP, NULL, L"Planos");
		AppendMenu(hMenu, MF_POPUP, NULL, L"Presupuesto");
		AppendMenu(hMenu, MF_POPUP, NULL, L"Control de ejecución");
		SetMenu(hWnd, hMenu);
		break;
	}	
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wparam, lparam);
}
VOID InitializeVariables()
{
	LoadString(HInstance(), IDS_WINDOWTITLE, WindowTitle, MAX_NAME_STRING);
	LoadString(HInstance(), IDS_WINDOWCLASS, WindowClass, MAX_NAME_STRING);

	wcscpy_s(WindowMenuName, TEXT("Edit"));

	WindowWidth = 1366;	/* Ancho inicial de la ventana principal */
	WindowHeight = 768; /* Alto inicial de la ventana principal */

	hIcon = LoadIcon(HInstance(), MAKEINTRESOURCE(IDI_MAINICON));
	
}
VOID CreateWindowClass()
{
	WNDCLASSEX wcex; /* Creando objeto tipo WNDCLASSEX */

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);

	wcex.hIcon = hIcon;
	wcex.hIconSm = hIcon;

	wcex.lpszClassName = WindowClass;

	wcex.lpszMenuName = WindowMenuName;

	wcex.hInstance = HInstance();

	wcex.lpfnWndProc = WindowProcess;

	RegisterClassEx(&wcex);
}
VOID InitializeWindow()
{
	HWND hWnd = CreateWindowEx(0, WindowClass, WindowTitle, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200, 200, 640, 480, nullptr, nullptr, HInstance(), nullptr);

	HWND hWnd2 = CreateWindow(WindowClass, WindowTitle, WS_CHILD, CW_USEDEFAULT,
		0, WindowWidth, WindowHeight, nullptr, nullptr, HInstance(), nullptr);


	if (!hWnd)
	{
		MessageBox(0, L"Fallaste prro!", 0, 0);
		PostQuitMessage(0);
	}
	else
	{
		ShowWindow(hWnd, SW_SHOW);
		ShowWindow(hWnd2, SW_SHOW);
	}
}
VOID MessageLoop()
{
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		// If there are window messages then process them.
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}
#pragma endregion
/* ------------------------------------------------------- */
