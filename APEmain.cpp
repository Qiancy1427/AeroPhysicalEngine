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

//declare end
//functions begin

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
        PostQuitMessage(0);//���ڻ��ǵ��ܹ��ϵģ�windows api�ٷ��Ķ�����ֻ�ܸ������������� .
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
	
	for(int i = 0; i < 10000; i++){	//fps:�Ҹо�Ҫ���� 
		settri_quick(pBuf, Vector2(100.0, 100.0), Vector2(100.0, 200.0), Vector2(200.0, 100.0), 255, 255, 255);
	}
	//EndPaint
	
	//ȫͼ������϶�����renderDC
	SetDIBits(renderDC,renderBmp,0,bmpinfo.bmiHeader.biHeight,pBuf,(BITMAPINFO*)&bmpinfo,0);
	
	BitBlt(hdc, 0, 0, windowwidth, windowheight, renderDC, 0, 0, SRCCOPY);//��������ʾ 
	
    EndPaint(main_hwnd, &ps);//�������ƣ��ͷŸ��������
    
    
	
	return;
}

//functions end
//entries begin

DWORD WINAPI renderLoop(LPVOID lpParamter){//��Ⱦ��ѭ��
    while(1){
		render();//��Ⱦ
		//�������綼��ά��deltatimeϵͳ��fpsϵͳ�Ĳ���(render) 
		gettimeofday(&render_presenttime, NULL);
		render_deltatime = (render_presenttime.tv_sec*1000)+(render_presenttime.tv_usec/1000)-(render_previoustime.tv_sec*1000)-(render_previoustime.tv_usec/1000);
		render_previoustime = render_presenttime;
		
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
	    render_fps=floor(20000/ctt);
	    cout<<"render deltatime:"<<render_deltatime<<"ms\n"<<"render fps(average):"<<render_fps<<"\n\n";
		
	}
    return 0L;
}

DWORD WINAPI logicLoop(LPVOID lpParamter){//�߼���ѭ��
    while(1){
		logic();//��Ϸ�߼�
		//�������綼��ά��deltatimeϵͳ��fpsϵͳ�Ĳ���(logic)
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
		logic_last20dt.push(logic_deltatime);
	    logic_fps=floor(20000/ctt);
	    cout<<"logic deltatime:"<<logic_deltatime<<"ms\n"<<"logic fps(average):"<<logic_fps<<"\n\n";
		
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


