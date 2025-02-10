#ifndef APEFLrend
#define APEFLrend

#include"APEFLhead.h"
#include"APEFLmath.h"
#include"APEFLtime.h"
#include"APEFLlogic.h"
#include"APEFLfluidsimulate.h"
#include"APEFLobject.h"
#include"APEFLmodel.h"
#include"APEFLfont.h"

//windows api setting
#define windowwidth 1900
#define windowheight 1000
HWND main_hwnd;//唯一指定的窗口句柄 
RECT rectt;//整个窗口的矩形 
BYTE *pBuf=new BYTE[windowwidth*windowheight*3];
PAINTSTRUCT ps;
HDC hdc,renderDC;//双缓冲DC 
HBITMAP renderBmp;
BITMAPINFO bmpinfo;//位图信息

const COLORREF rgbRed   =  0x000000FF;
const COLORREF rgbGreen =  0x0000FF00;
const COLORREF rgbBlue  =  0x00FF0000;
const COLORREF rgbBlack =  0x00000000;
const COLORREF rgbWhite =  0x00FFFFFF;

COLORREF rgbcustom(short r,short g,short b){
	return r+g*256+b*256*256;
} 

void setbmppixel(BYTE pBuf[],int x, int y,BYTE r,BYTE g,BYTE b){
	int k=((windowheight-y)*windowwidth+x)*3;
	pBuf[k++]=b;
	pBuf[k++]=g;
	pBuf[k++]=r;
	
	return;
}

void settri(BYTE pBuf[], Vector A, Vector B, Vector C, BYTE r, BYTE g, BYTE b){
	if(A.cont[0] > B.cont[0])	std::swap(A, B);
	if(B.cont[0] > C.cont[0])	std::swap(B, C);
	if(A.cont[0] > B.cont[0])	std::swap(A, B);
	if(A.cont[0] == C.cont[0])	return;
	
	int minx,maxx,miny,maxy;
	
	float kAC = (A.cont[1] - C.cont[1])/(A.cont[0] - C.cont[0]);
	if(A.cont[0] != B.cont[0]){
		float kAB = (A.cont[1] - B.cont[1])/(A.cont[0] - B.cont[0]);
		minx=ceil(A.cont[0]);
		maxx=floor(B.cont[0]);
		for(int i = minx; i <= maxx; i++){
			float y1 = A.cont[1] + kAB * (i - A.cont[0]), y2 = A.cont[1] + kAC * (i - A.cont[0]);
			miny=ceil(std::min(y1, y2));
			maxy=floor(std::max(y1, y2));
			for(int j = miny; j <= maxy; j++){
				setbmppixel(pBuf, i, j, r, g, b);
			}
		}
	}
	if(B.cont[0] != C.cont[0]){
		float kBC = (B.cont[1] - C.cont[1])/(B.cont[0] - C.cont[0]);
		minx=ceil(B.cont[0]);
		maxx=floor(C.cont[0]);
		for(int i = minx; i <= maxx; i++){
			float y1 = C.cont[1] + kBC * (i - C.cont[0]), y2 = C.cont[1] + kAC * (i - C.cont[0]);
			miny=ceil(std::min(y1, y2));
			maxy=floor(std::max(y1, y2));
			for(int j = miny; j <= maxy; j++){
				setbmppixel(pBuf, i, j, r, g, b);
			}
		}
	}
	return;
}

void settri_quick(BYTE pBuf[], Vector A, Vector B, Vector C, BYTE r, BYTE g, BYTE b){
	if(A.cont[1] > B.cont[1])	std::swap(A, B);
	if(B.cont[1] > C.cont[1])	std::swap(B, C);
	if(A.cont[1] > B.cont[1])	std::swap(A, B);
	if(A.cont[1] == C.cont[1])	return;
	
	int minx,maxx,miny,maxy,i,j,k;
	float x1,x2;
	
	float kAC = (A.cont[0] - C.cont[0])/(A.cont[1] - C.cont[1]);
	if(A.cont[1] != B.cont[1]){
		float kAB = (A.cont[0] - B.cont[0])/(A.cont[1] - B.cont[1]);
		miny=ceil(A.cont[1]);
		maxy=floor(B.cont[1]);
		for(i = miny; i <= maxy; i++){
			x1 = A.cont[0] + kAB * (i - A.cont[1]);
			x2 = A.cont[0] + kAC * (i - A.cont[1]);
			minx=ceil(std::min(x1, x2));
			maxx=floor(std::max(x1, x2));
			k=((windowheight-i)*windowwidth+minx)*3;
			for(j = minx; j <= maxx; j++){
				pBuf[k++]=b;
				pBuf[k++]=g;
				pBuf[k++]=r;
			}
		}
	}
	if(B.cont[1] != C.cont[1]){
		float kBC = (B.cont[0] - C.cont[0])/(B.cont[1] - C.cont[1]);
		miny=ceil(B.cont[1]);
		maxy=floor(C.cont[1]);
		for(i = miny; i <= maxy; i++){
			x1 = C.cont[0] + kBC * (i - C.cont[1]);
			x2 = C.cont[0] + kAC * (i - C.cont[1]);
			minx=ceil(std::min(x1, x2));
			maxx=floor(std::max(x1, x2));
			k=((windowheight-i)*windowwidth+minx)*3;
			for(j = minx; j <= maxx; j++){
				pBuf[k++]=b;
				pBuf[k++]=g;
				pBuf[k++]=r;
			}
		}
	}
	return;
}

void setrec_quick(BYTE pBuf[], Vector V, BYTE r, BYTE g, BYTE b){
	int minx,maxx,miny,maxy,i,j,k;
	
	minx=ceil(std::min(V.cont[0], V.cont[2]));
	maxx=floor(std::max(V.cont[0], V.cont[2]));
	miny=ceil(std::min(V.cont[1], V.cont[3]));
	maxy=floor(std::max(V.cont[1], V.cont[3]));
	for(i = miny; i <= maxy; i++){
		k=((windowheight-i)*windowwidth+minx)*3;
		for(j = minx; j <= maxx; j++){
			pBuf[k++]=b;
			pBuf[k++]=g;
			pBuf[k++]=r;
		}
	}
	
	return;
}

void settext(BYTE pBuf[],Vector V,char c,float size, BYTE r, BYTE g, BYTE b){
	if(size<=0||size>100) return;
	int cint=(int)c;
	int startx=floor(V.cont[0]),starty=floor(V.cont[1]);
	int endx=min((int)floor(V.cont[0]+8*size-1),windowwidth),endy=min((int)floor(V.cont[1]+8*size-1),windowheight);
	int k=0,l=0; 
	for(int i=startx;i<=endx;i++){
		l=0;
		for(int j=starty;j<=endy;j++){
			if(fontlist[cint][(int)floor((float)l/size)][(int)floor((float)k/size)]) setbmppixel(pBuf, i, j, r, g, b);
			
			l++;
		}
		k++;
	}
	
	return;
}

void settextline(BYTE pBuf[],Vector V,string s,float size, BYTE r, BYTE g, BYTE b){
	if(size<=0||size>100) return;
	float xt=V.cont[0],yt=V.cont[1];
	for(int i=0;i<s.size();i++){
		settext(pBuf,Vector(xt,yt,0.f,0.f),s[i],size,r,g,b);
		xt+=8*size;
	}
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
	
	for(int i=0;i<windowwidth*windowheight*3;i++){
		pBuf[i]=0;
	}
	
//	for(int i = 0; i < 10000; i++){	//fps:我感觉要出逝 
//		settri_quick(pBuf, Vector{100.0, 100.0, 0.0, 0.0}, Vector{100.0, 200.0, 0.0, 0.0}, Vector{200.0, 100.0, 0.0, 0.0}, 255, 255, 255);
//	}


	Vector rec=Vector(objlist[at].nbtlist[1].cont[0]+cubelist[am].p1.cont[0],objlist[at].nbtlist[1].cont[1]+cubelist[am].p1.cont[1],objlist[at].nbtlist[1].cont[0]+cubelist[am].p2.cont[0],objlist[at].nbtlist[1].cont[1]+cubelist[am].p2.cont[1]);
	setrec_quick(pBuf,rec,255,255,255);
	
	
//	for(int i = 0; i < simulatemapwidth; i++){
//		for(int j = 0; j < simulatemapheight; j++){
//			if(solidchunk[i][j]){
//				setrec_quick(pBuf, Vector{i*simulateblocksize+1.f, j*simulateblocksize+1.f, i*simulateblocksize+simulateblocksize, j*simulateblocksize+simulateblocksize}, 255, 0, 0);
//			}else{
//				setrec_quick(pBuf, Vector{i*simulateblocksize+1.f, j*simulateblocksize+1.f, i*simulateblocksize+simulateblocksize, j*simulateblocksize+simulateblocksize}, colorstrength[i][j], colorstrength[i][j], colorstrength[i][j]);
//			}
//			
//		}
//	}
	
/*	settextline(pBuf,Vector((float)(windowwidth-180),(float)(windowheight-40),0.f,0.f),"dtt(logic):"+to_string(logic_deltatime)+"ms",1,0,255,0);
	settextline(pBuf,Vector((float)(windowwidth-180),(float)(windowheight-30),0.f,0.f),"fps(logic):"+to_string(logic_fps),1,0,255,0);
	settextline(pBuf,Vector((float)(windowwidth-180),(float)(windowheight-20),0.f,0.f),"dtt(render):"+to_string(render_deltatime)+"ms",1,0,255,0);
	settextline(pBuf,Vector((float)(windowwidth-180),(float)(windowheight-10),0.f,0.f),"fps(render):"+to_string(render_fps),1,0,255,0);
*/	
	//EndPaint
	
	//全图处理完毕读出到renderDC
	SetDIBits(renderDC,renderBmp,0,bmpinfo.bmiHeader.biHeight,pBuf,(BITMAPINFO*)&bmpinfo,0);
	BitBlt(hdc, 0, 0, windowwidth, windowheight, renderDC, 0, 0, SRCCOPY);//缓冲区显示
    EndPaint(main_hwnd, &ps);//结束绘制，释放更新区句柄
    
	return;
}


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
	    //cout<<"render deltatime:"<<render_deltatime<<"ms\n"<<"render fps(average):"<<render_fps<<"\n\n";
		
	}
    return 0L;
}

#endif

