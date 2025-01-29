#ifndef APEFLobject
#define APEFLobject

#include"APEFLhead.h"
#include"APEFLmath.h"
#include"APEFLtime.h"

struct NBT {//define NBT
    int name;
    Vector data;
    NBT(){ }
    NBT(int st, Vector qt){//NBT constructor

        name = st;
        data = qt;
    }
};
struct Object {//define Object
    std::queue <NBT> nbts;
};

queue <Object> obj;

Object A,B,C;

/*
NBTs' categories format
 Position 1
 Velocity 2
 Acceleration 3
 Force 4
*/

void upd_obj(){
	for(int i=0;i<obj.size();i++){
		Object newobj=obj.front();
		obj.pop();
		
		int nbtsiz=newobj.nbts.size(); 
		Vector tg[100];
		bool tg_have[100]={false};
		
		while(!newobj.nbts.empty()){
			NBT newnbt=newobj.nbts.front();
			newobj.nbts.pop();
			tg[newnbt.name]=newnbt.data;
			tg_have[newnbt.name]=true;
		}
		
		tg[1]=vec_add(tg[1],vec_scapro(tg[2],targettime));//速度算坐标 
		cout<<tg[1].cont[0]<<" "<<tg[1].cont[1]<<" "<<tg[1].cont[2]<<" "<<tg[1].cont[3]<<"\n";
		tg[2]=vec_add(tg[2],vec_scapro(tg[3],targettime));//加速度算速度 
		
		for(int j=1;j<=100;j++){
			if(tg_have[j]) newobj.nbts.push(NBT(j,tg[j]));
		}
		obj.push(newobj);
	}
	cout<<"\n";
	return; 
}

#endif
