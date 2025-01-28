#include"APEFL.h"

using namespace std;

//entries begin

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)//傀儡callback 
{	
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);//窗口还是得能关上的，windows api官方的东西就只能干这种杂鱼事了 .
    case WM_PAINT:
        {
            //啥都没有，byd windows api 我才不在这写东西   		
        }
        return 0;

    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)//傀儡winapi 
{
	
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
        L"APEmain",    					// Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        0, 0, windowwidth, windowheight,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    if (hwnd == NULL)
    {
        return 0;
    }
    main_hwnd=hwnd;//设置唯一指定窗口 
    
    init();//初始化 
    
    HANDLE hThreadmain = CreateThread(NULL, 0, renderLoop, NULL, 0, NULL);//将renderloop塞进线程并推入cpu栈 
    CloseHandle(hThreadmain);//释放线程 
    HANDLE hThreadmainadd = CreateThread(NULL, 0, logicLoop, NULL, 0, NULL);//将logicloop塞进线程并推入cpu栈 
    CloseHandle(hThreadmainadd);//释放线程 

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.
    // Run你妈啊 

    MSG msg = { };
    while(1){
    	
    	if(GetMessage(&msg, NULL, 0, 0) > 0){
			TranslateMessage(&msg);
		    DispatchMessage(&msg);
		    //也是啥都没有，只是为了让这个线程能活着关掉窗口 
		}else{
			break;
		}
	}
    
    return 0;
}

//entries end


