#ifndef APEFLobject
#define APEFLobject

#include"APEFLhead.h"
#include"APEFLmath.h"
#include"APEFLtime.h"

#define nbtmaximum 20
#define objmaximum 100

struct Object {//define Object
    Vector nbtlist[nbtmaximum];
	bool nbtexist[nbtmaximum]={false};
};

Object objlist[objmaximum];
bool objexist[objmaximum]={false};

int at,bt,ct;

/*
NBTs' categories format
 Position 1
 Velocity 2
 Acceleration 3
 Force 4
 Direction 5
 Angular Velocity 6
*/

void set_nbt(int objnumber,int nbtname,Vector nbtdata){
	if(nbtname>=nbtmaximum) return;
	objlist[objnumber].nbtlist[nbtname] = nbtdata;
	objlist[objnumber].nbtexist[nbtname]=true;
	return;
}

void cancel_nbt(int objnumber,int nbtname){
	if(nbtname>=nbtmaximum) return;
	objlist[objnumber].nbtexist[nbtname]=false;
	return;
}
	
int create_obj(){
	for(int i=0;i<objmaximum;i++){
		if(!objexist[i]){
			objexist[i]=true;
			return i;
		}
	}
	return -1;
}

void delete_obj(int objnumber){
	for(int i=0;i<nbtmaximum;i++){
		objlist[objnumber].nbtexist[i]=false;
	}
	objexist[objnumber]=false;
	return;
}

void obj_init(){
	at=create_obj();
	if(at!=-1){
		set_nbt(at,1,Vector(100.f,100.f,0.f,1.f));
		set_nbt(at,2,Vector(1.f,0.f,0.f,1.f));
		set_nbt(at,3,Vector(0.f,0.01f,0.f,1.f));
		set_nbt(at,5,Vector(0.f,0.f,0.f,1.f));
		set_nbt(at,6,Vector(0.1f,0.f,0.f,1.f));
	}
}

void upd_obj(){
	for(int i=0;i<objmaximum;i++){
		if(objexist[i]){
			//physics begin
			if(objlist[i].nbtexist[1]&&objlist[i].nbtexist[2]){
				set_nbt(i,1,vec_add(objlist[i].nbtlist[1],vec_scapro(objlist[i].nbtlist[2],timepertick)));
				cout<<objlist[i].nbtlist[1].cont[0]<<" "<<objlist[i].nbtlist[1].cont[1]<<" "<<objlist[i].nbtlist[1].cont[2]<<" "<<objlist[i].nbtlist[1].cont[3]<<"\n";
			}
			if(objlist[i].nbtexist[2]&&objlist[i].nbtexist[3]) set_nbt(i,2,vec_add(objlist[i].nbtlist[2],vec_scapro(objlist[i].nbtlist[3],timepertick)));
			if(objlist[i].nbtexist[6])	set_nbt(i,5,vec_add(objlist[i].nbtlist[5],vec_scapro(objlist[i].nbtlist[6],timepertick)));
			//physics end
			
			cout<<"\n";
		}
	}
	cout<<"\n";
	return; 
}

#endif
