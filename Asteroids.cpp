// Asteroids.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Asteroids.h"

#define MAX_LOADSTRING 100
#define DEBUG			0

class SHIP
{
public:
	// Attributes
	bool forward, rSpin, lSpin; 
	float xPos, yPos, xVel, yVel, Rot;
	int Rad, L;
	//Functions
	int drawShip(HDC, HPEN);	
	void update();
	void shoot();
	SHIP();
};

class ROCK
{
	public:
		// Attributes
		float		 xPos, yPos, Rot;
		static float xVel, yVel;
		int Rad;
		int Var[10];
		//Functions
};


class BULLET
{
public:
		float xbPos, ybPos, xbVel, ybVel;
	static void updateBullets();
	static void drawBullets(HDC hdc, HPEN hShipPen);
	BULLET();

};

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
SHIP Player;
BULLET *Bullets[MAX_BULLETS];
//ROCK Rocks[20]; 
FILE *foutp;


bool bDrawLine	= false;
bool bDrawEllipse = false;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
int					drawShip(HDC, HPEN);
void				update();
void				drawBullets(HDC,HPEN);
int					init();

int init()
{


	Player.xPos = SCREEN_WIDTH/2;
	Player.yPos = SCREEN_HEIGHT/2;
	
	fopen_s(&foutp, "out.txt", "w");
	return 1;
}


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
					   _In_opt_ HINSTANCE hPrevInstance,
					   _In_ LPTSTR    lpCmdLine,
					   _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg;
	HACCEL hAccelTable;
	init();
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
	GetMessage(&msg, NULL, 0, 0);

	SetTimer(msg.hwnd,TIMER_ID, FRAME_TIME, NULL);
	// sends WM_TIMER to the message queue every 1/60th of a second.


	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		// position calculations here
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
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
		100, 50, WNDWIDTH, WNDHEIGHT, NULL, NULL, hInstance, NULL);
	
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
	case WM_TIMER:
		///What happens every 1/60th of a second
			Player.update();
  			BULLET::updateBullets();
			
		//	Rocks.update();
		//	Detect Collision
			
			InvalidateRect(hWnd, NULL, true);
			break;
	
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
	
	case WM_KEYDOWN:	
		switch(wParam)
		{
		case KEY_SHOOT:
			Player.shoot();
			break;
		case SPIN_LEFT:
			Player.lSpin	= true;
			break;
		case FORWARD:
			Player.forward	= true;
			break;
		case SPIN_RIGHT:
			Player.rSpin	= true;
			break;

		default:
			break;
		}
		break;
		
	case WM_KEYUP:
		switch (wParam)
		{
		case SPIN_LEFT:
			Player.lSpin	= false;
			break;
		case FORWARD:
			Player.forward	= false;
			break;
		case SPIN_RIGHT:
			Player.rSpin	= false;
			break;
		default:
			break;
		}		
	
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		HPEN hPenOld;
		
		HPEN hShipPen;
		COLORREF qShipColor;
		qShipColor = RGB(0, 0, 0);
		hShipPen = CreatePen(PS_SOLID, 3, qShipColor);
		hPenOld = (HPEN)SelectObject(hdc, hShipPen);
			
		Player.drawShip(hdc,hShipPen);
 		BULLET::drawBullets(hdc,hShipPen);

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

	Arc(hdc,((int)(xPos-Rad)),((int)(yPos-Rad)), ((int)(xPos + Rad)),((int)(yPos + Rad)), 0, 0, 0, 0);

	MoveToEx(hdc, (int)xPos, (int)yPos, NULL);
	LineTo(hdc,((int)(xPos + L*cosf(Rot))),((int)(yPos + L*sinf(Rot))));

	return 0;
}

void SHIP::update()
{

	xPos += xVel;
	yPos += yVel;
	
	if (xPos > XWRAP) {  xPos -= XWRAP;	}
	if (xPos < 0)	  {	xPos += XWRAP;	}

	if (yPos > YWRAP){	yPos -= YWRAP;	}
	if (yPos < 0)	{  yPos += YWRAP;	}

	
	if (DEBUG) {fprintf(foutp, "xVel = %2.1f,\t yVel = %2.1f, Rot = %f\n", xVel, yVel, Rot);}

	xVel *= DRAG;
	yVel *= DRAG;

	if (forward)
	{
		xVel += ACC_SPEED*cosf(Rot);
		yVel += ACC_SPEED*sinf(Rot);
	}


	if (rSpin)	{ Rot  +=  +SPIN_SPEED;}
	if (lSpin)	{ Rot  +=  -SPIN_SPEED;}

	if (xVel > VEL_MAX)	 {xVel = VEL_MAX;	}
	if (xVel < -VEL_MAX) {xVel = -VEL_MAX;	}

	if (yVel > VEL_MAX)	 {yVel = VEL_MAX;	}
	if (yVel < -VEL_MAX) {yVel = -VEL_MAX;	}
}

SHIP::SHIP()
{
	forward = rSpin = lSpin = false; 
	xVel = yVel = 0.0;
	xPos = SCREEN_WIDTH / 2;
	yPos = SCREEN_HEIGHT / 2;
	Rad = SHIP_RAD;
	Rot = 0;
	L = 35;
}	

void SHIP::shoot()
{
	int i = -1, k;
	for (k = 0; k < MAX_BULLETS && i == -1; k++)
	{
		if (Bullets[k] == NULL)
		{
			i = k;
		}
	}	
	if (i == -1) {return;}
  	BULLET *newBullet = new BULLET();
	Bullets[i] = newBullet;
}

void BULLET::updateBullets()
	{
		BULLET* temp;
 		for (int k = 0; k < MAX_BULLETS; k++)
		{			
			if (Bullets[k] == NULL) continue;
			
 			temp = Bullets[k];

			temp->xbPos += temp->xbVel;
			temp->ybPos += temp->ybVel;

			if (temp->xbPos < 0 || temp->xbPos > XWRAP){Bullets[k] = NULL; continue;} 
			if (temp->ybPos < 0 || temp->ybPos > YWRAP){Bullets[k] = NULL; continue;} 

			Bullets[k] = temp;
	
		}
	}

void BULLET::drawBullets(HDC hdc, HPEN hShipPen)
	{
		BULLET b1;
		for (int k = 0 ; k < MAX_BULLETS; k++)
		{
			if (Bullets[k] == NULL) continue;
			b1 = *Bullets[k];
			Arc(hdc,((int)(b1.xbPos-BULLET_SIZE)),((int)(b1.ybPos-BULLET_SIZE)), ((int)(b1.xbPos+BULLET_SIZE)),((int)(b1.ybPos + BULLET_SIZE)), 0, 0, 0, 0);
		}
	}

BULLET::BULLET()
{	
	xbPos = Player.xPos;
	ybPos = Player.yPos;
		
	xbVel = (float)(Player.xVel*.2 + BULLET_SPEED*cosf(Player.Rot)) ;
	ybVel = (float)(Player.yVel*.2 + BULLET_SPEED*sinf(Player.Rot));
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
