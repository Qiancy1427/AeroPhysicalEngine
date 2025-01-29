#ifndef APEFLlogic
#define APEFLlogic

#include"APEFL.h"
#include"APEFLhead.h"
#include"APEFLmath.h"
#include"APEFLtime.h"
#include"APEFLfluidsimulate.h"


void upd_obj(){
	for(int i=0;i<obj.size();i++){
		Object newobj=obj.front();
		obj.pop();
		int nbtsiz=newobj.nbts.size(); 
		Vector tg[nbtsiz];
		for(int j=0;j<nbtsiz;j++){
			NBT newnbt=newobj.nbts.front();
			newobj.nbts.pop();
			tg[newnbt.name-1]=newnbt.data;
		}
		tg[0]=tg[1]*logic_deltatime;//�ٶ������� 
		tg[1]=tg[2]*logic_deltatime;//���ٶ����ٶ� 
		for(int i=0;i<nbtsiz;i++){
			newobj.nbts.push(i,tg[i]);
		}
		obj.push(newobj);
	}
}

void logic(){//��Ϸ�߼� 
//	fluidupdate();
	upd_obj();
	
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

#endif
