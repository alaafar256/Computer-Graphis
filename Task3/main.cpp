#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <math.h>
#include <bits/stdc++.h>
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
               544,                 /* The programs width */
               375,                 /* and height in pixels */
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

COLORREF getLineColour(int x, int y, int CenterX, int CenterY, int R);
void Swap(int& x,int& y);
int Round(double x);
void DrawLine(HDC hdc,int xs,int ys,int xe,int ye,COLORREF color);
int getRadius(int x1, int y1, int x2, int y2);
void Draw8Points(HDC hdc,int xc,int yc, int a, int b,COLORREF color);
void CircleIterativePolar(HDC hdc,int xc,int yc, int R,COLORREF color);
////////////////////////////////////////////////////////////////////////////////////////////////
// Quadratic Curve
void multiplyMatrixVector(int mat[],int vec[],int res[],int n);
void DrawQuadraticCurve(HDC hdc,int x0,int y0,int x05,int y05,int x1,int y1,COLORREF rgb) ;
///////////////////////////////////////////////////////////////////////////////////////////////


/*  This function is called by the Windows function DispatchMessage()  */
int cnt = 0;
int c1x=0, c1y=0, c1xx=0, c1yy=0, R;
int Eye1X=0, Eye1Y=0, Eye1XX=0, Eye1YY=0;
int Eye2X=0, Eye2Y=0, Eye2XX=0, Eye2YY=0;
int Hair1X=0, Hair1Y=0, Hair1XX=0, Hair1YY=0;
int Hair2X=0, Hair2Y=0, Hair2XX=0, Hair2YY=0;
int Hair3X=0, Hair3Y=0, Hair3XX=0, Hair3YY=0;
int q=0, d=0,q1=0,d1=0 ;   // for smile
int q2=0, d2 = 0, q3=0, d3=0;    // for smile
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = GetDC(hwnd);
    COLORREF blackcolor = RGB(0, 0, 0);
    COLORREF bluecolor = RGB(0, 0, 255);
    COLORREF redcolor = RGB(255, 0, 0);
    switch (message)                  /* handle the messages */
    {
    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    case WM_LBUTTONDOWN:

        ///Face Circle
        if(cnt == 0 )
        {
            c1x = LOWORD(lParam);
            c1y = HIWORD(lParam);
            cnt++;
        }
        else if(cnt == 1)
        {
            c1xx = LOWORD(lParam);
            c1yy = HIWORD(lParam);
            R = getRadius(c1x,c1y,c1xx,c1yy);
            CircleIterativePolar(hdc,c1x,c1y,R,RGB(0,0,0));
            cnt++;
        }

        ///First Eye Circle
        else if(cnt == 2)
        {
            Eye1X = LOWORD(lParam);
            Eye1Y = HIWORD(lParam);
            cnt++;
        }
        else if(cnt == 3)
        {
            Eye1XX = LOWORD(lParam);
            Eye1YY = HIWORD(lParam);
            int r = getRadius(Eye1X, Eye1Y,Eye1XX,Eye1YY);
            CircleIterativePolar(hdc,Eye1X,Eye1Y,r,RGB(0,0,255));
            cnt++;
        }


        ///Second Eye Circle
        else if (cnt == 4)
        {
            Eye2X = LOWORD(lParam);
            Eye2Y = HIWORD(lParam);
            cnt++;
        }
        else if(cnt == 5)
        {
            Eye2XX = LOWORD(lParam);
            Eye2YY = HIWORD(lParam);
            int r = getRadius(Eye2X, Eye2Y,Eye2XX,Eye2YY);
            CircleIterativePolar(hdc,Eye2X,Eye2Y,r,RGB(0,0,255));
            cnt++;
        }

        ///Quad Curve
        else if (cnt==6)
        {
            q= LOWORD(lParam);
            d= HIWORD(lParam);
            cnt++;
        }
        else if (cnt==7)
        {
            q1= LOWORD(lParam);
            d1= HIWORD(lParam);
            cnt++;
        }
        else if (cnt==8)
        {
            q2= LOWORD(lParam);
            d2= HIWORD(lParam);
            DrawQuadraticCurve(hdc,q,d,q1,d1,q2,d2,bluecolor);
            cnt++;
        }
        ///First Hair
        else if(cnt == 9)
        {
            Hair1X = LOWORD(lParam);
            Hair1Y = HIWORD(lParam);
            cnt++;
        }
        else if(cnt == 10)
        {
            Hair1XX = LOWORD(lParam);
            Hair1YY = HIWORD(lParam);
            DrawLine(hdc, Hair1X, Hair1Y, Hair1XX, Hair1YY, RGB(255,0,0));
            cnt++;

        }

        ///Second Hair
        else if(cnt == 11)
        {
            Hair2X = LOWORD(lParam);
            Hair2Y = HIWORD(lParam);
            cnt++;
        }
        else if(cnt == 12)
        {
            Hair2XX = LOWORD(lParam);
            Hair2YY = HIWORD(lParam);
            DrawLine(hdc, Hair2X, Hair2Y, Hair2XX, Hair2YY, RGB(255,0,0));
            cnt++;
        }

        ///Third Hair
        else if(cnt == 13)
        {
            Hair3X = LOWORD(lParam);
            Hair3Y = HIWORD(lParam);
            cnt++;
        }
        else if (cnt == 14)
        {
            Hair3XX = LOWORD(lParam);
            Hair3YY = HIWORD(lParam);
            DrawLine(hdc, Hair3X, Hair3Y, Hair3XX, Hair3YY, RGB(255,0,0));
            cnt=0;
        }
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//Line Functions
COLORREF getLineColour(int x, int y, int CenterX, int CenterY, int R)
{
    int newR = getRadius(CenterX,CenterY,x,y);
    if(newR>R)
        return RGB(255,0,0);
    else
        return RGB(0,0,255);
}

void Swap(int& x,int& y)
{
    int tmp=x;
    x=y;
    y=tmp;
}

int Round(double x)
{
    return (int)(x+0.5);
}

void DrawLine(HDC hdc,int xs,int ys,int xe,int ye,COLORREF color)
{
    int dx=xe-xs;
    int dy=ye-ys;
    if(abs(dy)<=abs(dx))
    {
        double slope=(double)dy/dx;

        if(xs>xe)
        {
            Swap(xs,xe);
            Swap(ys,ye);
        }

        for(int x=xs; x<=xe; x++)
        {
            int y=Round(ys+(x-xs)*slope);
            color = getLineColour(x,y,c1x,c1y,R);
            SetPixel(hdc,x,y,color);
        }
    }
    else
    {
        double islope=(double)dx/dy;

        if(ys>ye)
        {
            Swap(xs,xe);
            Swap(ys,ye);
        }

        for(int y=ys; y<=ye; y++)
        {
            int x=Round(xs+(y-ys)*islope);
            color = getLineColour(x,y,c1x,c1y,R);
            SetPixel(hdc,x,y,color);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////
//Circle Functions
int getRadius(int x1, int y1, int x2, int y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void Draw8Points(HDC hdc,int xc,int yc, int a, int b,COLORREF color)
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

void CircleIterativePolar(HDC hdc,int xc,int yc, int R,COLORREF color)
{
    double x=R,y=0;
    double dtheta=1.0/R;
    double cdtheta=cos(dtheta);
    double sdtheta=sin(dtheta);
    Draw8Points(hdc,xc,yc,R,0,color);

    while(x>y)
    {
        double x1 = x*cdtheta-y*sdtheta;
        y = x*sdtheta+y*cdtheta;
        x = x1;
        Draw8Points(hdc,xc,yc,Round(x),Round(y),color);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////
// Quadratic Curve
void multiplyMatrixVector(int mat[],int vec[],int res[],int n)
{
    for(int i = 0 ; i < n ; i++)
    {
        res[i] = 0;
        for (int j = 0 ; j < n ; j++)
        {
            res[i]+= mat[i*n+j]*vec[j];
        }
    }
}
void DrawQuadraticCurve(HDC hdc,int x0,int y0,int x05,int y05,int x1,int y1,COLORREF rgb)
{
    int xArr[] = {x0,x05,x1}, yArr[] = {y0,y05,y1};
    int mat[ ] = {1,0,0,-3,4,-1, 2,-4,2};
    int coArrX[3],coArrY[3];
    multiplyMatrixVector(mat,xArr,coArrX,3);;
    multiplyMatrixVector(mat,yArr,coArrY,3);;

    int x, y;
    for(double  t = 0 ; t <=1 ; t+=0.0001)
    {
        x = coArrX[0] + coArrX[1]*t + coArrX[2]*t*t;
        y = coArrY[0] + coArrY[1]*t + coArrY[2]*t*t;

        SetPixel(hdc,x,y,rgb);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////
