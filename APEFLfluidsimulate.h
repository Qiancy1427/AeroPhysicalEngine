#ifndef APEFLfluidsimulate
#define APEFLfluidsimulate

#include"APEFLhead.h"
#include"APEFLmath.h"
#include"APEFLtime.h"


//Á÷ÌåÄ£Äâ
#define simulatemapwidth 900
#define simulatemapheight 500
#define simulateblocksize 2.f

#define stickness .1f 
#define conpressness .5f 
#define displaystandard 0.05f
int displaymode = 1;
bool solidchunk[simulatemapwidth][simulatemapheight]={false};
float flowmap_hori[simulatemapwidth][simulatemapheight]={0.f},flowmap_verti[simulatemapwidth][simulatemapheight]={0.f};
bool can_flow_hori[simulatemapwidth+1][simulatemapheight+2]={false},can_flow_verti[simulatemapwidth+2][simulatemapheight+1]={false};
int flownumber[simulatemapwidth][simulatemapheight]={0};
float densmap[simulatemapwidth][simulatemapheight]={0.f},densmaplast[simulatemapwidth][simulatemapheight]={0.f};
Vector velomap[simulatemapwidth][simulatemapheight];
Vector presmap[simulatemapwidth][simulatemapheight];
BYTE colorstrength[simulatemapwidth][simulatemapheight]={0};

void fluidinit(){
	
	densmap[0][5] = 100.f;
	densmap[100][150] = 10.f;
	densmap[200][100] = 10.f;
	densmap[500][300] = 10.f;
	
	
	for(int i=0;i<350;i++){
		solidchunk[i][10] = true;
	}
	for(int i=0;i<simulatemapwidth;i++){
		for(int j=0;j<simulatemapheight;j++){
			colorstrength[i][j] = (BYTE)((float)(1.f/(float)(1.f+pow(2.717f,-densmap[i][j])))*255.f);
		}
	}
	
	for(int i=0;i<simulatemapwidth;i++){
		for(int j=0;j<simulatemapheight;j++){
			presmap[i][j].cont[0]=0.f;
			presmap[i][j].cont[1]=0.f;
			presmap[i][j].cont[2]=0.f;
			presmap[i][j].cont[3]=0.f;
		}
	}
	
	
	return;
}

void fluidprecheck(){
	int xt,yt; 
	for(int i=0;i<simulatemapwidth-1;i++){
		for(int j=0;j<simulatemapheight;j++){
			can_flow_hori[i+1][j+1] = !(solidchunk[i][j]||solidchunk[i+1][j]);
		}
	}
	for(int i=0;i<=simulatemapheight+1;i++){
		can_flow_hori[0][i]=false;
		can_flow_hori[simulatemapwidth][i]=false;
	}
	for(int i=0;i<simulatemapwidth;i++){
		for(int j=0;j<simulatemapheight-1;j++){
			can_flow_verti[i+1][j+1] = !(solidchunk[i][j]||solidchunk[i][j+1]);
		}
	}
	for(int i=0;i<=simulatemapwidth+1;i++){
		can_flow_hori[i][0]=false;
		can_flow_hori[i][simulatemapheight]=false;
	}
	
	for(int i=0;i<simulatemapwidth;i++){
		for(int j=0;j<simulatemapheight;j++){
			xt=i+1;
			yt=j+1;
			if(can_flow_hori[xt][yt]) flownumber[i][j]++;
			if(can_flow_hori[i][yt]) flownumber[i][j]++;
			if(can_flow_verti[xt][yt]) flownumber[i][j]++;
			if(can_flow_verti[xt][j]) flownumber[i][j]++;
		}
	}
	
	
	return;
}

void fluidupdate(){
	int xt,yt;
	float flt;
	for(int i=0;i<simulatemapwidth;i++){
		for(int j=0;j<simulatemapheight;j++){
			if(!solidchunk[i][j]&&flownumber[i][j]!=0){
				xt=i+1;
				yt=j+1;
				flt=densmap[i][j]*conpressness/(float)flownumber[i][j];
				if(can_flow_hori[xt][yt]) flowmap_hori[i][j]+=flt;
				if(can_flow_hori[i][yt]) flowmap_hori[i-1][j]-=flt;
				if(can_flow_verti[xt][yt]) flowmap_verti[i][j]+=flt;
				if(can_flow_verti[xt][j]) flowmap_verti[i][j-1]-=flt;
			}
		}
	}
	for(int i=0;i<simulatemapwidth-1;i++){
		for(int j=0;j<simulatemapheight;j++){
			if(can_flow_hori[i+1][j+1]){
				densmap[i+1][j]+=flowmap_hori[i][j];
				densmap[i][j]-=flowmap_hori[i][j];
			}
			flowmap_hori[i][j]=0.f; 
		}
	}
	for(int i=0;i<simulatemapwidth;i++){
		for(int j=0;j<simulatemapheight-1;j++){
			if(can_flow_verti[i+1][j+1]){
				densmap[i][j+1]+=flowmap_verti[i][j];
				densmap[i][j]-=flowmap_verti[i][j];
			}
			flowmap_verti[i][j]=0.f; 
		}
	}
	
	for(int i=1;i<simulatemapwidth-1;i++){
		for(int j=1;j<simulatemapheight-1;j++){
			presmap[i][j].cont[0]=0;
			presmap[i][j].cont[1]=0;
			if(!solidchunk[i-1][j]) presmap[i][j].cont[0]+=densmap[i-1][j];
			if(!solidchunk[i+1][j]) presmap[i][j].cont[0]+=densmap[i+1][j];
			if(!solidchunk[i][j-1]) presmap[i][j].cont[1]+=densmap[i][j-1];
			if(!solidchunk[i][j+1]) presmap[i][j].cont[1]+=densmap[i][j+1];
			presmap[i][j].cont[3]=abs(presmap[i][j].cont[0])+abs(presmap[i][j].cont[1]);
		}
	}
	
	if(GetAsyncKeyState(0x31)){
		displaymode=1;
	}
	if(GetAsyncKeyState(0x32)){
		displaymode=2;
	}
	if(displaymode==1)
	for(int i=0;i<simulatemapwidth;i++){
		for(int j=0;j<simulatemapheight;j++){
			colorstrength[i][j] = (BYTE)((float)(1.f/(float)(1.f+pow(2.717f,-densmap[i][j])))*255.f);
		}
	}
	if(displaymode==2)
	for(int i=0;i<simulatemapwidth;i++){
		for(int j=0;j<simulatemapheight;j++){
			colorstrength[i][j] = (BYTE)((float)(1.f/(float)(1.f+pow(2.717f,-presmap[i][j].cont[3])))*255.f);
		}
	}
	
	
	return;
}


#endif

