#ifndef APEFLlogic
#define APEFLlogic

#include"APEFLhead.h"
#include"APEFLmath.h"
#include"APEFLtime.h"
#include"APEFLobject.h"
#include"APEFLfluidsimulate.h"

void logic(){//��Ϸ�߼� 
	fluidupdate();
	//upd_obj();
	
	return;
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
	    if(ctt<targettime*20){
			Sleep(targettime*20-ctt);
	    	ctt=targettime*20;
			logic_deltatime=targettime*20-ctt+logic_deltatime;
		}
		logic_last20dt.push(logic_deltatime);
	    logic_fps=floor(20000/ctt);
	    //cout<<"logic deltatime:"<<logic_deltatime<<"ms\n"<<"logic fps(average):"<<logic_fps<<"\n\n";
		
	}
    return 0L;
}

#endif
