#include"APEFL.h"


using namespace std;

HWND main_hwnd;//唯一指定的窗口句柄 
RECT rectt;//整个窗口的矩形 
BYTE *pBuf=new BYTE[windowwidth*windowheight*3];
PAINTSTRUCT ps;
HDC hdc,renderDC;//双缓冲DC 
HBITMAP renderBmp;
BITMAPINFO bmpinfo;

//deltatime系统 
struct timeval render_previoustime,render_presenttime,logic_previoustime,logic_presenttime;
int render_deltatime,logic_deltatime;

//fps系统（基于deltatime系统） 
queue<int> render_last20dt,logic_last20dt;
int render_fps,logic_fps;

int pos;//临时的方块x位置 

//declare end
//functions begin

void init(){//初始化 
	//设置整个窗口的矩形 
	rectt.top=0;
	rectt.bottom=windowheight;
	rectt.left=0;
	rectt.right=windowwidth;
	
	//窗口DC声明 
	InvalidateRect(main_hwnd,&rectt,true);//将整个窗口添加到更新区域 
    hdc = BeginPaint(main_hwnd, &ps);//开始绘制，并调用更新区句柄
    //双缓冲DC声明
	renderDC=CreateCompatibleDC(hdc);
    renderBmp = CreateCompatibleBitmap(hdc, windowwidth, windowheight);
    SelectObject(renderDC, renderBmp);	
    
		
	//获取位图到内存DIB
	GetDIBits(renderDC,renderBmp,0,bmpinfo.bmiHeader.biHeight,pBuf,(BITMAPINFO*)&bmpinfo,0);
    
	//创建并填写位图信息 
	
	ZeroMemory(&bmpinfo,sizeof(BITMAPINFO));
	bmpinfo.bmiHeader.biBitCount=24;      //每个像素多少位，也可直接写24(RGB)或者32(RGBA)
	bmpinfo.bmiHeader.biCompression=0;
	bmpinfo.bmiHeader.biHeight=windowheight;
	bmpinfo.bmiHeader.biPlanes=1;
	bmpinfo.bmiHeader.biSizeImage=0;
	bmpinfo.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	bmpinfo.bmiHeader.biWidth=windowwidth;
		
	//初始化deltatime系统和fps系统防止逻辑爆炸 
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

void logic(){//游戏逻辑 
	
	
	return;
}

void render(){//渲染 
	//窗口DC声明 
	InvalidateRect(main_hwnd,&rectt,true);//将整个窗口添加到更新区域 
    hdc = BeginPaint(main_hwnd, &ps);//开始绘制，并调用更新区句柄
    //双缓冲DC声明
	renderDC=CreateCompatibleDC(hdc);
    renderBmp = CreateCompatibleBitmap(hdc, windowwidth, windowheight);
    SelectObject(renderDC, renderBmp);	
	
	// All painting occurs here, between BeginPaint and EndPaint.
	//beginpaint
	int corecount=1;
	
	for(int i = 0; i < 10000; i++){	//fps:我感觉要出逝 
		settri_quick(pBuf, Vector2(100.0, 100.0), Vector2(100.0, 200.0), Vector2(200.0, 100.0), 255, 255, 255);
	}
	//EndPaint
	
	//全图处理完毕读出到renderDC
	SetDIBits(renderDC,renderBmp,0,bmpinfo.bmiHeader.biHeight,pBuf,(BITMAPINFO*)&bmpinfo,0);
	
	BitBlt(hdc, 0, 0, windowwidth, windowheight, renderDC, 0, 0, SRCCOPY);//缓冲区显示 
	
    EndPaint(main_hwnd, &ps);//结束绘制，释放更新区句柄
    
    
	
	return;
}

//functions end
//entries begin

DWORD WINAPI renderLoop(LPVOID lpParamter){//渲染主循环
    while(1){
		render();//渲染
		//以下这坨都是维护deltatime系统和fps系统的操作(render) 
		gettimeofday(&render_presenttime, NULL);
		render_deltatime = (render_presenttime.tv_sec*1000)+(render_presenttime.tv_usec/1000)-(render_previoustime.tv_sec*1000)-(render_previoustime.tv_usec/1000);
		render_previoustime = render_presenttime;
		
	    render_last20dt.pop();//这坨你不用看懂，更不要动 
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

DWORD WINAPI logicLoop(LPVOID lpParamter){//逻辑主循环
    while(1){
		logic();//游戏逻辑
		//以下这坨都是维护deltatime系统和fps系统的操作(logic)
		gettimeofday(&logic_presenttime, NULL);
		logic_deltatime = (logic_presenttime.tv_sec*1000)+(logic_presenttime.tv_usec/1000)-(logic_previoustime.tv_sec*1000)-(logic_previoustime.tv_usec/1000);
		logic_previoustime = logic_presenttime;
		
	    logic_last20dt.pop();//这坨你不用看懂，更不要动 
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


