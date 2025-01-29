#ifndef APEFLmath 
#define APEFLmath

#include"APEFLhead.h"

//math define starting

struct Vector{//向量 
	float cont[4];
	Vector(){ }
	Vector(float cont1, float cont2, float cont3, float cont4){//Vector constructor
		cont[0]=cont1;
        cont[1]=cont2;
        cont[2]=cont3;
        cont[3]=cont4;
    }
};

struct Matrix{//矩阵 
	float fact[4][4];
	Matrix(){ }
	Matrix(float fact11, float fact12, float fact13, float fact14, float fact21, float fact22, float fact23, float fact24, float fact31, float fact32, float fact33, float fact34, float fact41, float fact42, float fact43, float fact44){//Matrix constructor
		fact[0][0]=fact11;
        fact[0][1]=fact12;
        fact[0][2]=fact13;
        fact[0][3]=fact14;
        fact[1][0]=fact21;
        fact[1][1]=fact22;
        fact[1][2]=fact23;
        fact[1][3]=fact24;
        fact[2][0]=fact31;
        fact[2][1]=fact32;
        fact[2][2]=fact33;
        fact[2][3]=fact34;
        fact[3][0]=fact41;
        fact[3][1]=fact42;
        fact[3][2]=fact43;
        fact[3][3]=fact44;
    }
};

Vector vec_nor(Vector V){//向量归一化 
	return Vector(V.cont[0]/V.cont[3], V.cont[1]/V.cont[3], V.cont[2]/V.cont[3], 1);
}

Vector vec_add(Vector A, Vector B){//向量加法（限归一化后） 
	return Vector(A.cont[0] + B.cont[0], A.cont[1] + B.cont[1], A.cont[2] + B.cont[2], 1);
}

Vector vec_sub(Vector A, Vector B){//向量减法（限归一化后） 
	return Vector(A.cont[0] - B.cont[0], A.cont[1] - B.cont[1], A.cont[2] - B.cont[2], 1);
}

Vector vec_scapro(Vector V, float num){//向量数乘（限归一化后） 
	return Vector(V.cont[0]*num, V.cont[1]*num, V.cont[2]*num, 1);
}

float vec_dotpro(Vector A, Vector B, int size){//向量点乘（size决定维数(size<=3)）（限归一化后） 
	float res;
	while(size>0){
		res+=A.cont[--size]*B.cont[size];
	} 
	return res;
}

Vector vec_cropro(Vector A, Vector B){//向量叉乘（限三维）（限归一化后） 
	return Vector(A.cont[1]*B.cont[2] - A.cont[2]*B.cont[1], A.cont[2]*B.cont[0] - A.cont[0]*B.cont[2], A.cont[0]*B.cont[1] - A.cont[1]*B.cont[0], 1);
}

Matrix mat_scapro(Matrix M, float num){//矩阵数乘
	return Matrix(M.fact[0][0]*num, M.fact[0][1]*num, M.fact[0][2]*num, M.fact[0][3]*num, M.fact[1][0]*num, M.fact[1][1]*num, M.fact[1][2]*num, M.fact[1][3]*num, M.fact[2][0]*num, M.fact[2][1]*num, M.fact[2][2]*num, M.fact[2][3]*num, M.fact[3][0]*num, M.fact[3][1]*num, M.fact[3][2]*num, M.fact[3][3]*num);
}

Matrix mat_dotpro(Matrix M1, Matrix M2, int sizex1, int sizey1, int sizex2, int sizey2){//矩阵点乘
	Matrix res=Matrix(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
	if(sizey1!=sizex2) return res;
	for(int i=0;i<sizex1;i++){
		for(int j=0;j<sizey2;j++){
			for(int k=0;k<sizey1;k++){
				res.fact[i][j]+=M1.fact[i][k]*M2.fact[k][j];
			} 
		}
	}
	return res;
}

Vector mat_vec_pro(Matrix M,Vector V){//矩阵-向量乘法 
	return Vector(M.fact[0][0]*V.cont[0] + M.fact[0][1]*V.cont[1] + M.fact[0][2]*V.cont[2] + M.fact[0][3]*V.cont[3], M.fact[1][0]*V.cont[0] + M.fact[1][1]*V.cont[1] + M.fact[1][2]*V.cont[2] + M.fact[1][3]*V.cont[3], M.fact[2][0]*V.cont[0] + M.fact[2][1]*V.cont[1] + M.fact[2][2]*V.cont[2] + M.fact[2][3]*V.cont[3], M.fact[3][0]*V.cont[0] + M.fact[3][1]*V.cont[1] + M.fact[3][2]*V.cont[2] + M.fact[3][3]*V.cont[3]);
}

//math define ending

#endif
