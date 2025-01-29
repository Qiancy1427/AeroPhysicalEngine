#ifndef APEFL   
#define APEFL

#include"APEFLhead.h"
#include"APEFLmath.h"
#include"APEFLtime.h"
#include"APEFLlogic.h"
#include"APEFLrend.h"
#include"APEFLfluidsimulate.h"


struct NBT {//define NBT
    int name;
    Vector data;
    NBT(int st, Vector qt){//NBT constructor

        name = st;
        data = qt;
    }
};
struct Object {//define Object
    std::queue <NBT> nbts;
};

queue <Object> obj; 

/*
NBTs' categories format
 Position 1
 Velocity 2
 Acceleration 3
 Force 4
*/

Object A,B,C;

void init(){//初始化 
	//流体模拟
//	fluidinit();
//	fluidprecheck();

	//设置整个窗口的矩形 
	rectt.top=0;
	rectt.bottom=windowheight;
	rectt.left=0;
	rectt.right=windowwidth;
	
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
	
	//以下为测试upd_obj所用
	A.nbts.push(0,0,0);
	A.nbts.push(50,0,0);
	A.nbts.push(0,10,0); 
	B.nbts.push(0,30,0);
	B.nbts.push(50,0,0);
	B.nbts.push(0,10,0);
	C.nbts.push(30,30,0);
	C.nbts.push(50,0,0);
	C.nbts.push(0,10,0); 
	obj.push(A);
	obj.push(B);
	obj.push(C);
	return;
}


#endif
