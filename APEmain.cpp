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
HDC hdc,renderDC;
HBITMAP renderBmp;
BITMAPINFO bmpinfo;
queue<Task> rendertask[sideloopnum+1]; 
bool loopstate[sideloopnum+1];
bool sideloopcanrun;

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
	
	//����DC���� 
	InvalidateRect(main_hwnd,&rectt,true);//������������ӵ��������� 
    hdc = BeginPaint(main_hwnd, &ps);//��ʼ���ƣ������ø��������
    //˫����DC����
	renderDC=CreateCompatibleDC(hdc);
    renderBmp = CreateCompatibleBitmap(hdc, windowwidth, windowheight);
    SelectObject(renderDC, renderBmp);	
    
    for(int i=1;i<=sideloopnum;i++){
    	loopstate[i]=true;
	}
	sideloopcanrun=true;
		
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
	previoustime.tv_sec=0;
	previoustime.tv_usec=0;
	presenttime.tv_sec=0;
	presenttime.tv_usec=0;
	gettimeofday(&presenttime, NULL);
	deltatime = (presenttime.tv_sec*1000)+(presenttime.tv_usec/1000)-(previoustime.tv_sec*1000)-(previoustime.tv_usec/1000);
	previoustime = presenttime;
	pos=0;
	for(int i=0;i<10;i++){
		last10dt.push(1000);
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
	
	//ȫͼ������϶�����renderDC
	SetDIBits(renderDC,renderBmp,0,bmpinfo.bmiHeader.biHeight,pBuf,(BITMAPINFO*)&bmpinfo,0);
	
	BitBlt(hdc, 0, 0, windowwidth, windowheight, renderDC, 0, 0, SRCCOPY);//��������ʾ 
	
    EndPaint(main_hwnd, &ps);//�������ƣ��ͷ� ���������
    
    //����DC���� 
	InvalidateRect(main_hwnd,&rectt,true);//������������ӵ��������� 
    hdc = BeginPaint(main_hwnd, &ps);//��ʼ���ƣ������ø��������
    //˫����DC����
	renderDC=CreateCompatibleDC(hdc);
    renderBmp = CreateCompatibleBitmap(hdc, windowwidth, windowheight);
    SelectObject(renderDC, renderBmp);		 
	
	return;
}

void settask(){
	sideloopcanrun=false; 
	// All painting occurs here, between BeginPaint and EndPaint.
	//beginpaint
	int corecount=1;
	
	for(int i = 0; i < 1000; i++){	//fps:�Ҹо�Ҫ���� 
		Task taskt;
		taskt.A = Vector2(100.0, 100.0);
		taskt.B = Vector2(100.0, 120.0);
		taskt.C = Vector2(200.0, 100.0);
		taskt.r=255;
		taskt.g=255;
		taskt.b=255;
		
		rendertask[corecount].push(taskt);
		
		corecount%=sideloopnum;
		corecount++;
	}
	//EndPaint
	sideloopcanrun=true;
	
	return;
}

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

DWORD WINAPI mainLoop(LPVOID lpParamter){//��ѭ��
    while(1){
		update();//��Ϸ�߼�
		bool Permit=true;
		for(int i=1;i<=sideloopnum;i++){
			if(!loopstate[i]) Permit=false;
		}
		if(Permit){
			render();//��Ⱦ
			settask();
			//�������綼��ά��deltatimeϵͳ��fpsϵͳ�Ĳ��� 
			
			
			gettimeofday(&presenttime, NULL);
			deltatime = (presenttime.tv_sec*1000)+(presenttime.tv_usec/1000)-(previoustime.tv_sec*1000)-(previoustime.tv_usec/1000);
			previoustime = presenttime;
			if(deltatime<1000){
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
    
    HANDLE hThreadmain = CreateThread(NULL, 0, mainLoop, NULL, 0, NULL);//��loop�����̲߳�����cpuջ 
    CloseHandle(hThreadmain);//�ͷ��߳� 
    if(sideloopnum>=1){
    	HANDLE hThreadside1 = CreateThread(NULL, 0, sideLoop1, NULL, 0, NULL);//��loop�����̲߳�����cpuջ 
   		CloseHandle(hThreadside1);//�ͷ��߳� 
   		if(sideloopnum>=2){
   			HANDLE hThreadside2 = CreateThread(NULL, 0, sideLoop2, NULL, 0, NULL);//��loop�����̲߳�����cpuջ 
   			CloseHandle(hThreadside2);//�ͷ��߳�
   			if(sideloopnum>=3){
	   			HANDLE hThreadside3 = CreateThread(NULL, 0, sideLoop3, NULL, 0, NULL);//��loop�����̲߳�����cpuջ 
	   			CloseHandle(hThreadside3);//�ͷ��߳�
			}
		}
	}

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



