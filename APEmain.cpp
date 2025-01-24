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
BYTE *pBuf=new BYTE[windowwidth*windowheight*3];
PAINTSTRUCT ps;
HDC hdc,renderDC;//˫����DC 
HBITMAP renderBmp;
BITMAPINFO bmpinfo;

//deltatimeϵͳ 
struct timeval render_previoustime,render_presenttime,logic_previoustime,logic_presenttime;
int render_deltatime,logic_deltatime;

//fpsϵͳ������deltatimeϵͳ�� 
queue<int> render_last20dt,logic_last20dt;
int render_fps,logic_fps;


int pos;//��ʱ�ķ���xλ�� 

void init(){//��ʼ�� 
	//�����������ڵľ��� 
	rectt.top=0;
	rectt.bottom=windowheight;
	rectt.left=0;
	rectt.right=windowwidth;
	
	//����DC���� 
	InvalidateRect(main_hwnd,&rectt,true);//������������ӵ��������� 
    hdc = BeginPaint(main_hwnd, &ps);//��ʼ���ƣ������ø��������
    //˫����DC����
	renderDC=CreateCompatibleDC(hdc);
    renderBmp = CreateCompatibleBitmap(hdc, windowwidth, windowheight);
    SelectObject(renderDC, renderBmp);	
    
		
	//��ȡλͼ���ڴ�DIB
	GetDIBits(renderDC,renderBmp,0,bmpinfo.bmiHeader.biHeight,pBuf,(BITMAPINFO*)&bmpinfo,0);
    
	//��������дλͼ��Ϣ 
	
	ZeroMemory(&bmpinfo,sizeof(BITMAPINFO));
	bmpinfo.bmiHeader.biBitCount=24;      //ÿ�����ض���λ��Ҳ��ֱ��д24(RGB)����32(RGBA)
	bmpinfo.bmiHeader.biCompression=0;
	bmpinfo.bmiHeader.biHeight=windowheight;
	bmpinfo.bmiHeader.biPlanes=1;
	bmpinfo.bmiHeader.biSizeImage=0;
	bmpinfo.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	bmpinfo.bmiHeader.biWidth=windowwidth;
		
	//��ʼ��deltatimeϵͳ��fpsϵͳ��ֹ�߼���ը 
	render_previoustime.tv_sec=0;
	render_previoustime.tv_usec=0;
	render_presenttime.tv_sec=0;
	render_presenttime.tv_usec=0;
	gettimeofday(&render_presenttime, NULL);
	render_deltatime = (render_presenttime.tv_sec*1000)+(render_presenttime.tv_usec/1000)-(render_previoustime.tv_sec*1000)-(render_previoustime.tv_usec/1000);
	render_previoustime = render_presenttime;
	for(int i=0;i<20;i++){
		render_last20dt.push(1000/targetfps);
	}
	render_fps=0;
	logic_previoustime.tv_sec=0;
	logic_previoustime.tv_usec=0;
	logic_presenttime.tv_sec=0;
	logic_presenttime.tv_usec=0;
	gettimeofday(&logic_presenttime, NULL);
	logic_deltatime = (logic_presenttime.tv_sec*1000)+(logic_presenttime.tv_usec/1000)-(logic_previoustime.tv_sec*1000)-(logic_previoustime.tv_usec/1000);
	logic_previoustime = logic_presenttime;
	for(int i=0;i<20;i++){
		logic_last20dt.push(1000/targetfps);
	}
	logic_fps=0;
	
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

void logic(){//��Ϸ�߼� 
	
	
	return;
}

void render(){//��Ⱦ 
	//����DC���� 
	InvalidateRect(main_hwnd,&rectt,true);//������������ӵ��������� 
    hdc = BeginPaint(main_hwnd, &ps);//��ʼ���ƣ������ø��������
    //˫����DC����
	renderDC=CreateCompatibleDC(hdc);
    renderBmp = CreateCompatibleBitmap(hdc, windowwidth, windowheight);
    SelectObject(renderDC, renderBmp);	
	
	// All painting occurs here, between BeginPaint and EndPaint.
	//beginpaint
	int corecount=1;
	
	for(int i = 0; i < 1000; i++){	//fps:�Ҹо�Ҫ���� 
		settri(pBuf, Vector2(100.0, 100.0), Vector2(100.0, 120.0), Vector2(200.0, 100.0), 255, 255, 255);
	}
	//EndPaint
	
	//ȫͼ������϶�����renderDC
	SetDIBits(renderDC,renderBmp,0,bmpinfo.bmiHeader.biHeight,pBuf,(BITMAPINFO*)&bmpinfo,0);
	
	BitBlt(hdc, 0, 0, windowwidth, windowheight, renderDC, 0, 0, SRCCOPY);//��������ʾ 
	
    EndPaint(main_hwnd, &ps);//�������ƣ��ͷ� ���������
    
    
	
	return;
}
/* 
//loop begin
DWORD WINAPI sideLoop1(LPVOID lpParamter){//��ѭ��1
    while(1){
    	if(sideloopcanrun)
    	if(!rendertask[1].empty()){
    		Task taskt=rendertask[1].front();
    		rendertask[1].pop();
    		settri(pBuf, taskt.A, taskt.B, taskt.C, taskt.r, taskt.g, taskt.b);
    		loopstate[1]=false;
		}else{
			loopstate[1]=true;
		}
	}
    return 0L;
}

DWORD WINAPI sideLoop2(LPVOID lpParamter){//��ѭ��2
    while(1){
    	if(sideloopcanrun)
    	if(!rendertask[2].empty()){
    		Task taskt=rendertask[2].front();
    		rendertask[2].pop();
    		settri(pBuf, taskt.A, taskt.B, taskt.C, taskt.r, taskt.g, taskt.b);
    		loopstate[2]=false;
		}else{
			loopstate[2]=true;
		}
	}
    return 0L;
}

DWORD WINAPI sideLoop3(LPVOID lpParamter){//��ѭ��3
    while(1){
    	if(sideloopcanrun)
    	if(!rendertask[3].empty()){
    		Task taskt=rendertask[3].front();
    		rendertask[3].pop();
    		settri(pBuf, taskt.A, taskt.B, taskt.C, taskt.r, taskt.g, taskt.b);
    		loopstate[3]=false;
		}else{
			loopstate[3]=true;
		}
	}
    return 0L;
}
//loop end
*/

DWORD WINAPI renderLoop(LPVOID lpParamter){//��Ⱦ��ѭ��
    while(1){
		render();//��Ⱦ
		//�������綼��ά��deltatimeϵͳ��fpsϵͳ�Ĳ��� 
		gettimeofday(&render_presenttime, NULL);
		render_deltatime = (render_presenttime.tv_sec*1000)+(render_presenttime.tv_usec/1000)-(render_previoustime.tv_sec*1000)-(render_previoustime.tv_usec/1000);
		render_previoustime = render_presenttime;
		if(render_deltatime<1000){
			cout<<"render deltatime:"<<render_deltatime<<"ms\n";
		}
		
	    render_last20dt.pop();//�����㲻�ÿ���������Ҫ�� 
	    int ctt=0;
	    for(int i=0;i<19;i++){
	    	int tt=render_last20dt.front();
	    	render_last20dt.pop();
	    	ctt+=tt;
	    	render_last20dt.push(tt);
		}
		ctt+=render_deltatime;
		render_last20dt.push(render_deltatime);
		
		//�򵥵���ʾfps 
	    render_fps=floor(20000/ctt);
	    cout<<"render fps(average):"<<render_fps<<"\n";
	    //if(render_fps>targetfps) Sleep(1000/targetfps-1000/render_fps);
		
		
	}
    return 0L;
}

DWORD WINAPI logicLoop(LPVOID lpParamter){//�߼���ѭ��
    while(1){
		logic();//��Ϸ�߼�
		//�������綼��ά��deltatimeϵͳ��fpsϵͳ�Ĳ��� 
		gettimeofday(&logic_presenttime, NULL);
		logic_deltatime = (logic_presenttime.tv_sec*1000)+(logic_presenttime.tv_usec/1000)-(logic_previoustime.tv_sec*1000)-(logic_previoustime.tv_usec/1000);
		logic_previoustime = logic_presenttime;
		
	    logic_last20dt.pop();//�����㲻�ÿ���������Ҫ�� 
	    int ctt=0;
	    for(int i=0;i<19;i++){
	    	int tt=logic_last20dt.front();
	    	logic_last20dt.pop();
	    	ctt+=tt;
	    	logic_last20dt.push(tt);
		}
		ctt+=logic_deltatime;
	    if(ctt<20000/targetfps){
			Sleep(20000/targetfps-ctt);
	    	ctt=20000/targetfps;
			logic_deltatime=20000/targetfps-ctt+logic_deltatime;
		}
		cout<<"logic deltatime:"<<logic_deltatime<<"ms\n";
		logic_last20dt.push(logic_deltatime);
		
		//�򵥵���ʾfps 
	    logic_fps=floor(20000/ctt);
	    cout<<"logic fps(average):"<<logic_fps<<"\n";
		
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



