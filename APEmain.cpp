#include<bits/stdc++.h>
#include<windows.h>
#include<winuser.h>
#include<wingdi.h>
#include<conio.h>

#include"APEFL.h"

using namespace std;


struct timeval previoustime,presenttime;
int deltatime=0;
int pos=0;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	previoustime.tv_sec=0;
	previoustime.tv_usec=0;
	presenttime.tv_sec=0;
	presenttime.tv_usec=0;
    // Register the window class.
    const wchar_t CLASS_NAME[]  = L"APEwindow";
    
    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"APEmain",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        -10, -3, 1920, 1080,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
    	
        gettimeofday(&presenttime, NULL);
		deltatime = (presenttime.tv_sec*1000)+(presenttime.tv_usec/1000)-(previoustime.tv_sec*1000)-(previoustime.tv_usec/1000);
		previoustime = presenttime;
		if(deltatime<1000){
			pos=deltatime+pos;
			cout<<"deltatime:"<<deltatime<<"ms\n";
			cout<<pos<<"\n";
	        UpdateWindow(hwnd);
	        TranslateMessage(&msg);
	        DispatchMessage(&msg);
			
		}
        
    }
    
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            
            // All painting occurs here, between BeginPaint and EndPaint.

            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
			paintrect(hdc,Vector2(pos,150),Vector2(pos+50,200),rgbcustom(255,0,0));

            EndPaint(hwnd, &ps);
            
    		
    		
        }
        return 0;

    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}



