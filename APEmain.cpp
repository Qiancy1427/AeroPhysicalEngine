#include"APEFL.h"

using namespace std;

//entries begin

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)//����callback 
{	
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);//���ڻ��ǵ��ܹ��ϵģ�windows api�ٷ��Ķ�����ֻ�ܸ������������� .
    case WM_PAINT:
        {
            //ɶ��û�У�byd windows api �ҲŲ�����д����   		
        }
        return 0;

    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)//����winapi 
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
    main_hwnd=hwnd;//����Ψһָ������ 
    
    init();//��ʼ�� 
    
    HANDLE hThreadmain = CreateThread(NULL, 0, renderLoop, NULL, 0, NULL);//��renderloop�����̲߳�����cpuջ 
    CloseHandle(hThreadmain);//�ͷ��߳� 
    HANDLE hThreadmainadd = CreateThread(NULL, 0, logicLoop, NULL, 0, NULL);//��logicloop�����̲߳�����cpuջ 
    CloseHandle(hThreadmainadd);//�ͷ��߳� 

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.
    // Run���谡 

    MSG msg = { };
    while(1){
    	
    	if(GetMessage(&msg, NULL, 0, 0) > 0){
			TranslateMessage(&msg);
		    DispatchMessage(&msg);
		    //Ҳ��ɶ��û�У�ֻ��Ϊ��������߳��ܻ��Źص����� 
		}else{
			break;
		}
	}
    
    return 0;
}

//entries end


