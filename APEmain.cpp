#include<bits/stdc++.h>
#include<windows.h>
#include<winuser.h>
#include<wingdi.h>
#include<conio.h>

#include<cstdlib>

#include"APEFL.h"

#define targetfps 100

using namespace std;

HWND main_hwnd;//Ψһָ���Ĵ��ھ�� 
RECT rectt;//�������ڵľ��� 

//deltatimeϵͳ 
struct timeval previoustime,presenttime;
int deltatime;

//fpsϵͳ������deltatimeϵͳ�� 
queue<int> last10dt;
int fps;


int pos;//��ʱ�ķ���xλ�� 

void init(){//��ʼ�� 
	//�����������ڵľ��� 
	rectt.top=0;
	rectt.bottom=1080;
	rectt.left=0;
	rectt.right=1920;
		
	//��ʼ��deltatimeϵͳ��fpsϵͳ��ֹ�߼���ը 
	previoustime.tv_sec=0;
	previoustime.tv_usec=0;
	presenttime.tv_sec=0;
	presenttime.tv_usec=0;
	gettimeofday(&presenttime, NULL);
	deltatime = (presenttime.tv_sec*1000)+(presenttime.tv_usec/1000)-(previoustime.tv_sec*1000)-(previoustime.tv_usec/1000);
	previoustime = presenttime;
	pos=0;
	for(int i=0;i<10;i++){
		last10dt.push(1000/targetfps);
	}
	fps=0;
	
	return;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)//����callback 
{	
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);//���ڻ��ǵ��ܹ��ϵģ�windows api�ٷ��Ķ�����ֻ�ܸ������������� 
        return 0;

    case WM_PAINT:
        {
            //ɶ��û�У�byd windows api �ҲŲ�����д����   		
        }
        return 0;

    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void update(){//��Ϸ�߼� 
	
	return;
}

void render(){//��Ⱦ 
	
	InvalidateRect(main_hwnd,&rectt,true);//������������ӵ��������� 
	
	PAINTSTRUCT ps;
    HDC hdc = BeginPaint(main_hwnd, &ps);//��ʼ���ƣ������ø�������� 
    
    // All painting occurs here, between BeginPaint and EndPaint.

    FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
	paintrect(hdc,Vector2(pos,150),Vector2(pos+50,200),rgbcustom(255,0,0));
	
	//painting end

    EndPaint(main_hwnd, &ps);//�������� 
	return;
}

DWORD WINAPI startLoop(LPVOID lpParamter){//��ѭ��
    while(1){
		update();//��Ϸ�߼� 
		render();//��Ⱦ 
		
		//�������綼��ά��deltatimeϵͳ��fpsϵͳ�Ĳ��� 
		gettimeofday(&presenttime, NULL);
		deltatime = (presenttime.tv_sec*1000)+(presenttime.tv_usec/1000)-(previoustime.tv_sec*1000)-(previoustime.tv_usec/1000);
		previoustime = presenttime;
		if(deltatime<1000){
			
			pos=deltatime/10+pos;//���������� 
			pos=min(pos,1870);//��λ������������� 
			cout<<"deltatime:"<<deltatime<<"ms\n";
		}
		
	    last10dt.pop();//�����㲻�ÿ���������Ҫ�� 
	    int ctt=0;
	    for(int i=0;i<9;i++){
	    	int tt=last10dt.front();
	    	last10dt.pop();
	    	ctt+=tt;
	    	last10dt.push(tt);
		}
		ctt+=deltatime;
		last10dt.push(deltatime);
		
		//�򵥵���ʾfps 
	    fps=floor(10000/ctt);
	    cout<<"fps(average):"<<fps<<"\n";
	    //if(deltatime<1000/targetfps) Sleep(1000/targetfps-deltatime);
	}
    return 0L;
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
    main_hwnd=hwnd;//����Ψһָ������ 
    
    init();//��ʼ�� 
    
    HANDLE hThread = CreateThread(NULL, 0, startLoop, NULL, 0, NULL);//��loop�����̲߳�����cpuջ 
    CloseHandle(hThread);//�ͷ��߳� 

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



