#ifndef APEFLobject
#define APEFLobject

#include"APEFLhead.h"
#include"APEFLmath.h"
#include"APEFLtime.h"

const float targettime=1000/targetfps;

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
		Vector tg[nbtsiz];
		for(int j=0;j<nbtsiz;j++){
			NBT newnbt=newobj.nbts.front();
			newobj.nbts.pop();
			tg[newnbt.name-1]=newnbt.data;
		}
		tg[0]=vec_add(tg[0],vec_scapro(tg[1],targettime));//速度算坐标 
		cout<<tg[0].cont[0]<<" "<<tg[0].cont[1]<<" "<<tg[0].cont[2]<<" "<<tg[0].cont[3]<<"\n";
		tg[1]=vec_add(tg[1],vec_scapro(tg[2],1000/targettime));//加速度算速度 
		for(int i=0;i<nbtsiz;i++){
			newobj.nbts.push(NBT(i,tg[i]));
		}
		obj.push(newobj);
	}
	cout<<"\n";
}

#endif
