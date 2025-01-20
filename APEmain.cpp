#include<bits/stdc++.h>
#include<windows.h>
#include<winuser.h>
#include<wingdi.h>
#include<conio.h>

#include<cstdlib>

#include"APEFL.h"


using namespace std;

HWND main_hwnd;//唯一指定的窗口句柄 
RECT rectt;//整个窗口的矩形 

//deltatime系统 
struct timeval previoustime,presenttime;
int deltatime;

//fps系统（基于deltatime系统） 
queue<int> last10dt;
int fps;


int pos;//临时的方块x位置 

void init(){//初始化 
	//设置整个窗口的矩形 
	rectt.top=0;
	rectt.bottom=windowheight;
	rectt.left=0;
	rectt.right=windowwidth;
		
	//初始化deltatime系统和fps系统防止逻辑爆炸 
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

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)//傀儡callback 
{	
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);//窗口还是得能关上的，windows api官方的东西就只能干这种杂鱼事了 
        return 0;

    case WM_PAINT:
        {
            //啥都没有，byd windows api 我才不在这写东西   		
        }
        return 0;

    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void update(){//游戏逻辑 
	int t=0;
	for(int i=0;i++;i<10000000){
		t++;
	} 
	
	return;
}

void render(){//渲染 
	//窗口DC声明 
	PAINTSTRUCT ps;
	InvalidateRect(main_hwnd,&rectt,true);//将整个窗口添加到更新区域 
    HDC hdc = BeginPaint(main_hwnd, &ps);//开始绘制，并调用更新区句柄
    //双缓冲DC声明 
	HDC renderDC=CreateCompatibleDC(hdc);
    HBITMAP renderBmp = CreateCompatibleBitmap(hdc, windowwidth, windowheight);
    SelectObject(renderDC, renderBmp);
    
    
	//在内存new出一片位图大小的空间
	BYTE *pBuf=new BYTE[windowwidth*windowheight*3];//(DWORD)
	    
	//创建并填写位图信息 
	BITMAPINFO bmpinfo;
	ZeroMemory(&bmpinfo,sizeof(BITMAPINFO));
	bmpinfo.bmiHeader.biBitCount=24;      //每个像素多少位，也可直接写24(RGB)或者32(RGBA)
	bmpinfo.bmiHeader.biCompression=0;
	bmpinfo.bmiHeader.biHeight=windowheight;
	bmpinfo.bmiHeader.biPlanes=1;
	bmpinfo.bmiHeader.biSizeImage=0;
	bmpinfo.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	bmpinfo.bmiHeader.biWidth=windowwidth;
	//获取位图到内存DIB
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
	
	//全图处理完毕读出到renderDC
	SetDIBits(renderDC,renderBmp,0,bmpinfo.bmiHeader.biHeight,pBuf,(BITMAPINFO*)&bmpinfo,0);
	delete []pBuf;
	
	BitBlt(hdc, 0, 0, windowwidth, windowheight, renderDC, 0, 0, SRCCOPY);//缓冲区显示 
	
    EndPaint(main_hwnd, &ps);//结束绘制，释放 更新区句柄
    //释放双缓冲DC 
    DeleteDC(renderDC);
	DeleteObject(renderBmp);
	return;
}

DWORD WINAPI startLoop(LPVOID lpParamter){//主循环
    while(1){
		update();//游戏逻辑 
		render();//渲染 
		
		//以下这坨都是维护deltatime系统和fps系统的操作 
		gettimeofday(&presenttime, NULL);
		deltatime = (presenttime.tv_sec*1000)+(presenttime.tv_usec/1000)-(previoustime.tv_sec*1000)-(previoustime.tv_usec/1000);
		previoustime = presenttime;
		if(deltatime<1000){
			
			pos=(float)(deltatime/2)+pos;//方块向右溜 
			pos=min(pos,windowwidth-50);//限位，别让它溜大了 
			cout<<"deltatime:"<<deltatime<<"ms\n";
		}
		
	    last10dt.pop();//这坨你不用看懂，更不要动 
	    int ctt=0;
	    for(int i=0;i<9;i++){
	    	int tt=last10dt.front();
	    	last10dt.pop();
	    	ctt+=tt;
	    	last10dt.push(tt);
		}
		ctt+=deltatime;
		last10dt.push(deltatime);
		
		//简单地显示fps 
	    fps=floor(10000/ctt);
	    cout<<"fps(average):"<<fps<<"\n";
	    //if(fps>targetfps) Sleep(1000/targetfps-1000/fps);
	}
    return 0L;
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
    main_hwnd=hwnd;//设置唯一指定窗口 
    
    init();//初始化 
    
    HANDLE hThread = CreateThread(NULL, 0, startLoop, NULL, 0, NULL);//将loop塞进线程并推入cpu栈 
    CloseHandle(hThread);//释放线程 

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



