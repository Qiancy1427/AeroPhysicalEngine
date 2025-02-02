#ifndef APEFL   
#define APEFL

#include"APEFLhead.h"
#include"APEFLmath.h"
#include"APEFLtime.h"
#include"APEFLlogic.h"
#include"APEFLrend.h"
#include"APEFLfluidsimulate.h"
#include"APEFLobject.h" 
#include"APEFLfont.h"

void init(){//初始化 
	//流体模拟
	fluidinit();
	fluidprecheck();

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
		render_last20dt.push(targettime);
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
		logic_last20dt.push(targettime);
	}
	logic_fps=0;
	
	//以下为测试upd_obj所用
	at=create_obj();
	if(at!=-1){
		set_nbt(at,1,Vector(10.f,10.f,0.f,1.f));
		set_nbt(at,2,Vector(3.f,0.f,0.f,1.f));
		set_nbt(at,3,Vector(0.f,0.01f,0.f,1.f));
	}
	bt=create_obj();
	if(bt!=-1){
		set_nbt(bt,1,Vector(10.f,30.f,0.f,1.f));
		set_nbt(bt,2,Vector(3.f,0.f,0.f,1.f));
		set_nbt(bt,3,Vector(0.f,0.01f,0.f,1.f));
	}
	ct=create_obj();
	if(ct!=-1){
		set_nbt(ct,1,Vector(30.f,30.f,0.f,1.f));
		set_nbt(ct,2,Vector(3.f,0.0f,0.f,1.f));
		set_nbt(ct,3,Vector(0.f,0.01f,0.f,1.f));
	}
	
	return;
}


#endif
