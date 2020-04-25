#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <bits/stdc++.h>
#include <cmath>
#define  ROUND(a) ((int) (a + 0.5))
using namespace std ;
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               _T("Code::Blocks Template Windows App"),       /* Title Text */
               WS_OVERLAPPEDWINDOW, /* default window */
               CW_USEDEFAULT,       /* Windows decides the position */
               CW_USEDEFAULT,       /* where the window ends up on the screen */
               1000,                 /* The programs width */
               600,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}
void swap(int& x,int& y)
{
    int tmp=x;
    x=y;
    y=tmp;
}

void DrawLine(HDC hdc,int xs,int ys,int xe,int ye,COLORREF color)
{
    int dx=xe-xs;
    int dy=ye-ys;
    double slope=(double)dy/dx;
    if(xs>xe)
    {
        swap(xs,xe);
        swap(ys,ye);
    }
    for(int x=xs; x<=xe; x++)
    {
        int y=round(ys+(x-xs)*slope);
        SetPixel(hdc,x,y,0);
    }
}
void Draw8PointsForSecondCircle(HDC hdc,int xc,int yc, int a, int b,COLORREF color)
{
    SetPixel(hdc, xc+a, yc+b, 0);
    SetPixel(hdc, xc-a, yc+b, 0);
    SetPixel(hdc, xc-a, yc-b, 0);
    SetPixel(hdc, xc+a, yc-b, 0);
    SetPixel(hdc, xc+b, yc+a, 0);
    SetPixel(hdc, xc-b, yc+a, 0);
    SetPixel(hdc, xc-b, yc-a, 0);
    SetPixel(hdc, xc+b, yc-a, 0);

    DrawLine(hdc, xc, yc, xc+a,yc+b, 0);
    DrawLine(hdc, xc, yc, xc-a,yc-b, 0);
}
void Draw8PointsForFirstCicle(HDC hdc,int xc,int yc, int a, int b,COLORREF color)
{
    SetPixel(hdc, xc+a, yc+b, color);
    SetPixel(hdc, xc-a, yc+b, color);
    SetPixel(hdc, xc-a, yc-b, color);
    SetPixel(hdc, xc+a, yc-b, color);
    SetPixel(hdc, xc+b, yc+a, color);
    SetPixel(hdc, xc-b, yc+a, color);
    SetPixel(hdc, xc-b, yc-a, color);
    SetPixel(hdc, xc+b, yc-a, color);
}
void CircleDirectForFirstCircle(HDC hdc,int xc,int yc, int R,COLORREF color)
{

    int x=0, y=R;
    int R2 = R*R ;
    Draw8PointsForFirstCicle(hdc,xc,yc,x,y,0);
    while(x<y)
    {
        x++;
        y=round(sqrt((double)(R2-x*x)));
        Draw8PointsForFirstCicle(hdc,xc,yc,x,y,0);
    }
}
void CircleDirectForSecondCircle(HDC hdc,int xc,int yc, int R,COLORREF color)
{

    int x=0, y=R;
    int R2 = R*R ;
    Draw8PointsForSecondCircle(hdc,xc,yc,x,y,0);
    while(x<y)
    {
        x++;
        y=round(sqrt((double)(R2-x*x)));
        Draw8PointsForSecondCircle(hdc,xc,yc,x,y,0);
    }
}


/*  This function is called by the Windows function DispatchMessage()  */
int Num_of_Points = 0 ;
boolean PointSet ;
int x , y , x1 , y1;
PAINTSTRUCT ps;
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    hdc = GetDC(hwnd);

    switch (message)                  /* handle the messages */
    {
        case WM_LBUTTONDOWN:
			if(Num_of_Points==0)
			{

                CircleDirectForSecondCircle(hdc,300,300,200,0) ;
				Num_of_Points++;
			}

			else if(Num_of_Points==1)
			{
                CircleDirectForFirstCircle(hdc,600,300,100,0) ;
				Num_of_Points++;

			}
            break ;
        case WM_RBUTTONDOWN:
            if(Num_of_Points==2){
                cout << "Radius Of the First Circle is : " << "100" << endl  ;
                CircleDirectForSecondCircle(hdc,300,300,200,0) ;
                cout << "Radius Of the Second Circle is : " << "200" << endl  ;
                CircleDirectForFirstCircle(hdc,600,300,100,0) ;

            }
            break ;

    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
