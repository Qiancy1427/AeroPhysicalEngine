#ifndef APEFL   
#define APEFL

#include"APEFLhead.h"
#include"APEFLmath.h"
#include"APEFLtime.h"
#include"APEFLlogic.h"
#include"APEFLrend.h"
#include"APEFLfluidsimulate.h"
#include"APEFLobject.h" 

void init(){//��ʼ�� 
	//����ģ��
//	fluidinit();
//	fluidprecheck();

	//�����������ڵľ��� 
	rectt.top=0;
	rectt.bottom=windowheight;
	rectt.left=0;
	rectt.right=windowwidth;
	
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
	
	//����Ϊ����upd_obj����
	A.nbts.push(NBT(1,Vector{0.0f,0.0f,0.0f,1.0f}));
	A.nbts.push(NBT(2,Vector{1.0f,0.0f,0.0f,1.0f}));
	A.nbts.push(NBT(3,Vector{0.0f,1.0f,0.0f,1.0f})); 
	B.nbts.push(NBT(1,Vector{0.0f,30.0f,0.0f,1.0f}));
	B.nbts.push(NBT(2,Vector{1.0f,0.0f,0.0f,1.0f}));
	B.nbts.push(NBT(3,Vector{0.0f,1.0f,0.0f,1.0f}));
	C.nbts.push(NBT(1,Vector{30.0f,30.0f,0.0f,1.0f}));
	C.nbts.push(NBT(2,Vector{1.0f,0.0f,0.0f,1.0f}));
	C.nbts.push(NBT(3,Vector{0.0f,1.0f,0.0f,1.0f})); 
	obj.push(A);
	obj.push(B);
	obj.push(C);
	return;
}


#endif
