#ifndef APEFLmodel
#define APEFLmodel

#include"APEFLhead.h"
#include"APEFLmath.h"
#include"APEFLtime.h"

#define modelmaximum 100

struct Cube{
	Vector p1,p2;
}cubelist[100];

int am;

bool cubeexist[modelmaximum]={false};

int create_cube(){
	for(int i=0;i<modelmaximum;i++){
		if(!cubeexist[i]){
			cubeexist[i]=true;
			return i;
		}
	} 
	return -1;
}

void set_cube(int modelname, Vector p1, Vector p2){
	cubelist[modelname].p1=p1;
	cubelist[modelname].p2=p2;
}

void model_init(){
	am=create_cube();
	if(am!=-1)	set_cube(am,Vector(-25.f,-25.f,0.f,1.f),Vector(25.f,25.f,0.f,1.f));
}

#endif
