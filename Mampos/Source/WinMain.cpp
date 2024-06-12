#include <Windows.h>
#define MAX_NAME_STRING 256	
#define HInstance() GetModuleHandle(NULL)

WCHAR WindowClass[MAX_NAME_STRING];
WCHAR WindowMenuName[MAX_NAME_STRING];
WCHAR WindowTitle[MAX_NAME_STRING];

INT WindowWidth;
INT WindowHeight;

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
	/* - Initialize Global Variables - */

	wcscpy_s(WindowClass, TEXT("Mampos"));
	wcscpy_s(WindowMenuName, TEXT("Edit"));
	wcscpy_s(WindowTitle, TEXT("Mampos"));

	WindowWidth = 1366;	/* Ancho inicial de la ventana principal */
	WindowHeight = 768; /* Alto inicial de la ventana principal */

	/* - Create Window Class - */

	WNDCLASSEX wcex; /* Creando objeto tipo WNDCLASSEX */

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);

	wcex.hIcon = LoadIcon(0, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(0, IDI_APPLICATION);

	wcex.lpszClassName = WindowClass;

	wcex.lpszMenuName = WindowMenuName;

	wcex.hInstance = HInstance();

	wcex.lpfnWndProc = DefWindowProc;

	RegisterClassEx(&wcex);

	/* - Create and Display our Window - */

	HWND hWnd = CreateWindow(WindowClass, WindowTitle, WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,
		0, WindowWidth, WindowHeight, nullptr, nullptr, HInstance(), nullptr);

	HWND hWnd2 = CreateWindow(WindowClass, nullptr, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		0, WindowWidth-300, WindowHeight-300, hWnd, nullptr, HInstance(), nullptr);

	if (!hWnd) 
	{
		MessageBox(0, L"Fallaste prro!", 0, 0);
		return 0;
	}
	ShowWindow(hWnd, SW_SHOW);
	ShowWindow(hWnd2, SW_SHOW);


	/* - Listen for Message events - */

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

	return 0;
}
