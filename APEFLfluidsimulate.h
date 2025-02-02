#ifndef APEFLfluidsimulate
#define APEFLfluidsimulate

#include"APEFLhead.h"
#include"APEFLmath.h"
#include"APEFLtime.h"


//Á÷ÌåÄ£Äâ
#define simulatemapwidth 900
#define simulatemapheight 500
#define simulateblocksize 2.f
#define flowstrength 0.5f 
#define displaystandard 0.05f
bool solidchunk[simulatemapwidth][simulatemapheight]={false};
float flowmap_hori[simulatemapwidth][simulatemapheight]={0.f},flowmap_verti[simulatemapwidth][simulatemapheight]={0.f};
bool can_flow_hori[simulatemapwidth+1][simulatemapheight+2]={false},can_flow_verti[simulatemapwidth+2][simulatemapheight+1]={false};
int flownumber[simulatemapwidth][simulatemapheight]={0};
float densmap[simulatemapwidth][simulatemapheight]={0.f},densmaplast[simulatemapwidth][simulatemapheight]={0.f};
BYTE colorstrength[simulatemapwidth][simulatemapheight]={0};

void fluidinit(){
	
	densmap[0][5] = 100.f;
	densmap[100][150] = 10.f;
	
	
	for(int i=0;i<350;i++){
		solidchunk[i][10] = true;
	}
	for(int i=0;i<simulatemapwidth;i++){
		for(int j=0;j<simulatemapheight;j++){
			colorstrength[i][j] = (BYTE)((float)(1.f/(float)(1.f+pow(2.717f,-densmap[i][j])))*255.f);
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
				flt=densmap[i][j]*flowstrength/(float)flownumber[i][j];
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
	for(int i=0;i<simulatemapwidth;i++){
		for(int j=0;j<simulatemapheight;j++){
			if(densmaplast[i][j]-densmap[i][j]<-displaystandard||densmaplast[i][j]-densmap[i][j]>displaystandard){
				colorstrength[i][j] = (BYTE)((float)(1.f/(float)(1.f+pow(2.717f,-densmap[i][j])))*255.f);
				densmaplast[i][j]=densmap[i][j];
			}
			
		}
	}
	
	
	return;
}


#endif

