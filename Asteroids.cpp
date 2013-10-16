// Asteroids.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Asteroids.h"


#define MAX_LOADSTRING 100

class SHIP
{
	public:
		float xPos, yPos, xVel, yVel, Rot;
		int Rad;
		int drawShip(HDC, HPEN);	
};


// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
SHIP Ship;

bool bDrawLine	= false;
bool bDrawEllipse = false;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
int					drawShip(HDC, HPEN);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
					   _In_opt_ HINSTANCE hPrevInstance,
					   _In_ LPTSTR    lpCmdLine,
					   _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_ASTEROIDS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ASTEROIDS));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		// position calculations here

		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
<<<<<<< HEAD
=======


>>>>>>> 81d9f1ec495bed4281d9b78f69b3cffb8ce1ec97
	}
	return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ASTEROIDS));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_ASTEROIDS);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle,   WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,
		200, 100, WNDWIDTH, WNDHEIGHT, NULL, NULL, hInstance, NULL);
	
	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_START:
			::MessageBox(hWnd, _T("Would you like to play a game?"), _T("Start"), MB_YESNO | MB_ICONQUESTION);
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_LINE:
			bDrawLine = !bDrawLine;
			InvalidateRect(hWnd, NULL, true);
			break;
		case IDM_ELLIPSE:
			bDrawEllipse = !bDrawEllipse;
			InvalidateRect(hWnd, NULL, true);
			break;		
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		HPEN hPenOld;

		if (bDrawLine)
		{
		// Draw a red line
<<<<<<< HEAD
			HPEN hLinePen;
			COLORREF qLineColor;
			qLineColor = RGB(255, 0, 0);
			hLinePen = CreatePen(PS_SOLID, 7, qLineColor);
			hPenOld = (HPEN)SelectObject(hdc, hLinePen);
=======
		HPEN hLinePen;
		COLORREF qLineColor;
		qLineColor = RGB(0, 0, 0);
		hLinePen = CreatePen(PS_SOLID, 7, qLineColor);
		hPenOld = (HPEN)SelectObject(hdc, hLinePen);
>>>>>>> 81d9f1ec495bed4281d9b78f69b3cffb8ce1ec97

			MoveToEx(hdc, 100, 100, NULL);
			LineTo(hdc, 500, 250);

			SelectObject(hdc, hPenOld);
			DeleteObject(hLinePen);
		}

		if (bDrawEllipse)
		{
		// Draw a blue ellipse
			HPEN hEllipsePen;
			COLORREF qEllipseColor;
			qEllipseColor = RGB(0, 0, 255);
			hEllipsePen = CreatePen(PS_SOLID, 3, qEllipseColor);
			hPenOld = (HPEN)SelectObject(hdc, hEllipsePen);
				
			Arc(hdc, 100, 100, 500, 250, 0, 0, 0, 0);

			SelectObject(hdc, hPenOld);
			DeleteObject(hEllipsePen);
		}
		
			HPEN hShipPen;
			COLORREF qShipColor;
			qShipColor = RGB(0, 0, 0);
			hShipPen = CreatePen(PS_SOLID, 3, qShipColor);
			hPenOld = (HPEN)SelectObject(hdc, hShipPen);
				
			Ship.drawShip(hdc,hShipPen);

			SelectObject(hdc, hPenOld);
			DeleteObject(hShipPen);
		

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
int SHIP::drawShip(HDC hdc, HPEN hShipPen)
{
	// THIS NEEDS TO BE DONE 
	// SEBASTION

<<<<<<< HEAD
	//MoveToEx(hdc, 100, 100, NULL);
	//LineTo(hdc, 500, 250);

	return 0;
}
=======
/*
public class ship {

	float xPos, yPos, xVel, yVel, rot;
	int rad;

	public ship()
	{
		xPos = 0;
		yPos = 0;
		xVel = 0;
		yVel = 0;


	}

}
*/
/*
=======================
SHIP:
		--	Positions are changed by velocitys and used for painting
			(Type Cast when painting)
float		Xpos	
float		Ypos

		--	Velocities are changed with key presses
			No key means constant velocity
float		Xvel
float		Yvel
		
		--	Rotation determines vector for bullets
float/int	Rot

		--	Radius is needed for collision detection
int			Rad

>>>>>>> 81d9f1ec495bed4281d9b78f69b3cffb8ce1ec97

/*
========================
Bullets:
-- Needed for drawing and collision
(Type Cast when painting)
float		Xpos
float		Ypos

-- Xvel^2 + Yvel^2 = (CONSTANT + (ShipXvel^2 + ShipYvel^2))
float		Xvel
float		Yvel

-- colision detection
int 		Rad

==========================
Asteroids:

float		Xpos
float 		Ypos

float		Xvel
float		Yvel

float/int	Rot
int			Rad

int[10]	Array containing the variance +/- off Rad on graphic 


*/
/*	public ship()
	{
		xPos = SCREEN_WIDTH/2;
		yPos = SCREEN_HEIGHT/2;
		xVel = 0;
		yVel = 0;
		Rot = 0;
		Rad = SHIP_RADIUS;
	}


	public void drawShip(){
	}
}
/*
		=======================
SHIP:
--	Positions are changed by velocitys and used for painting
(Type Cast when painting)
float		Xpos	
float		Ypos

--	Velocities are changed with key presses
No key means constant velocity
float		Xvel
float		Yvel

--	Rotation determines vector for bullets
float/int	Rot

--	Radius is needed for collision detection
int			Rad
*/

