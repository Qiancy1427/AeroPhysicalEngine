#include<bits/stdc++.h>
#include<windows.h>
#include<winuser.h>
#include<wingdi.h>
#include<conio.h>

#include<cstdlib>

#include"APEFL.h"


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
	rectt.bottom=windowheight;
	rectt.left=0;
	rectt.right=windowwidth;
		
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
	int t=0;
	for(int i=0;i++;i<10000000){
		t++;
	} 
	
	return;
}

void render(){//��Ⱦ 
	//����DC���� 
	PAINTSTRUCT ps;
	InvalidateRect(main_hwnd,&rectt,true);//������������ӵ��������� 
    HDC hdc = BeginPaint(main_hwnd, &ps);//��ʼ���ƣ������ø��������
    //˫����DC���� 
	HDC renderDC=CreateCompatibleDC(hdc);
    HBITMAP renderBmp = CreateCompatibleBitmap(hdc, windowwidth, windowheight);
    SelectObject(renderDC, renderBmp);
    
    
	//���ڴ�new��һƬλͼ��С�Ŀռ�
	BYTE *pBuf=new BYTE[windowwidth*windowheight*3];//(DWORD)
	    
	//��������дλͼ��Ϣ 
	BITMAPINFO bmpinfo;
	ZeroMemory(&bmpinfo,sizeof(BITMAPINFO));
	bmpinfo.bmiHeader.biBitCount=24;      //ÿ�����ض���λ��Ҳ��ֱ��д24(RGB)����32(RGBA)
	bmpinfo.bmiHeader.biCompression=0;
	bmpinfo.bmiHeader.biHeight=windowheight;
	bmpinfo.bmiHeader.biPlanes=1;
	bmpinfo.bmiHeader.biSizeImage=0;
	bmpinfo.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	bmpinfo.bmiHeader.biWidth=windowwidth;
	//��ȡλͼ���ڴ�DIB
	GetDIBits(renderDC,renderBmp,0,bmpinfo.bmiHeader.biHeight,pBuf,(BITMAPINFO*)&bmpinfo,0);
	
	// All painting occurs here, between BeginPaint and EndPaint.
	//beginpaint
	for(int i=1;i<=windowwidth;i++){
		for(int j=1;j<=windowheight;j++){
			setbmppixel(pBuf,i,j,255,255,0);
		}
	}
	setbmppixel(pBuf,99,99,0,0,0);
	setbmppixel(pBuf,99,100,0,0,0);
	setbmppixel(pBuf,100,99,0,0,0);
	setbmppixel(pBuf,100,100,0,0,0);
	//EndPaint
	
	//ȫͼ������϶�����renderDC
	SetDIBits(renderDC,renderBmp,0,bmpinfo.bmiHeader.biHeight,pBuf,(BITMAPINFO*)&bmpinfo,0);
	delete []pBuf;
	
	BitBlt(hdc, 0, 0, windowwidth, windowheight, renderDC, 0, 0, SRCCOPY);//��������ʾ 
	
    EndPaint(main_hwnd, &ps);//�������ƣ��ͷ� ���������
    //�ͷ�˫����DC 
    DeleteDC(renderDC);
	DeleteObject(renderBmp);
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
			
			pos=(float)(deltatime/2)+pos;//���������� 
			pos=min(pos,windowwidth-50);//��λ������������� 
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
	    //if(fps>targetfps) Sleep(1000/targetfps-1000/fps);
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



