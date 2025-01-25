#include<bits/stdc++.h>
#include<sys/time.h>
#include<conio.h>
#include<cstdlib>

#include<Windows.h>
#include<Mmsystem.h>
#include<Prnasnot.h>
#include<T2embapi.h>
#include<Tvout.h>
#include<Windef.h>
#include<Windowsx.h>
#include<Wingdi.h>
#include<Winuser.h>

using namespace std;

#ifndef APEFL   
#define APEFL  1


#define targetfps 20
#define windowwidth 1900
#define windowheight 1000

//math define starting

struct Vector{//向量 
	float cont[4];
};

struct Matrix{//矩阵 
	float fact[4][4];
};

Vector vec_nor(Vector V){//向量归一化 
	return Vector{V.cont[0]/V.cont[3], V.cont[1]/V.cont[3], V.cont[2]/V.cont[3], 1};
}

Vector vec_add(Vector A, Vector B){//向量加法（限归一化后） 
	return Vector{A.cont[0] + B.cont[0], A.cont[1] + B.cont[1], A.cont[2] + B.cont[2], 1};
}

Vector vec_sub(Vector A, Vector B){//向量减法（限归一化后） 
	return Vector{A.cont[0] - B.cont[0], A.cont[1] - B.cont[1], A.cont[2] - B.cont[2], 1};
}

Vector vec_scapro(Vector V, float num){//向量数乘（限归一化后） 
	return Vector{V.cont[0]*num, V.cont[1]*num, V.cont[2]*num, 1};
}

float vec_dotpro(Vector A, Vector B, int size){//向量点乘（size决定维数(size<=3)）（限归一化后） 
	float res;
	while(size>0){
		res+=A.cont[--size]*B.cont[size];
	} 
	return res;
}

Vector vec_cropro(Vector A, Vector B){//向量叉乘（限三维）（限归一化后） 
	return Vector{A.cont[1]*B.cont[2] - A.cont[2]*B.cont[1], A.cont[2]*B.cont[0] - A.cont[0]*B.cont[2], A.cont[0]*B.cont[1] - A.cont[1]*B.cont[0], 1};
}

Matrix mat_scapro(Matrix M, float num){//矩阵数乘
	return Matrix{M.fact[0][0]*num, M.fact[0][1]*num, M.fact[0][2]*num, M.fact[0][3]*num, M.fact[1][0]*num, M.fact[1][1]*num, M.fact[1][2]*num, M.fact[1][3]*num, M.fact[2][0]*num, M.fact[2][1]*num, M.fact[2][2]*num, M.fact[2][3]*num, M.fact[3][0]*num, M.fact[3][1]*num, M.fact[3][2]*num, M.fact[3][3]*num};
}

Matrix mat_dotpro(Matrix M1, Matrix M2, int sizex1, int sizey1, int sizex2, int sizey2){//矩阵点乘
	Matrix res=Matrix{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
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
	return Vector{M.fact[0][0]*V.cont[0] + M.fact[0][1]*V.cont[1] + M.fact[0][2]*V.cont[2] + M.fact[0][3]*V.cont[3], M.fact[1][0]*V.cont[0] + M.fact[1][1]*V.cont[1] + M.fact[1][2]*V.cont[2] + M.fact[1][3]*V.cont[3], M.fact[2][0]*V.cont[0] + M.fact[2][1]*V.cont[1] + M.fact[2][2]*V.cont[2] + M.fact[2][3]*V.cont[3], M.fact[3][0]*V.cont[0] + M.fact[3][1]*V.cont[1] + M.fact[3][2]*V.cont[2] + M.fact[3][3]*V.cont[3]};
}


//math define ending

struct NBT {//define NBT
    std::string name;
    Vector data;
    NBT(std::string st, Vector qt){//NBT constructor

        name = st;
        data = qt;
    }
};
struct Object {//define Object
    std::queue <NBT> nbts;
};

/*
NBTs' categories format
 Position 1
 Velocity 2
 Acceleration 3
 Force 4
*/


const COLORREF rgbRed   =  0x000000FF;
const COLORREF rgbGreen =  0x0000FF00;
const COLORREF rgbBlue  =  0x00FF0000;
const COLORREF rgbBlack =  0x00000000;
const COLORREF rgbWhite =  0x00FFFFFF;

COLORREF rgbcustom(short r,short g,short b){
	return r+g*256+b*256*256;
} 

void setbmppixel(BYTE pBuf[],int x, int y,BYTE r,BYTE g,BYTE b){
	int k=((windowheight-y)*windowwidth+x)*3;
	pBuf[k++]=b;
	pBuf[k++]=g;
	pBuf[k++]=r;
	
	return;
}

void settri(BYTE pBuf[], Vector A, Vector B, Vector C, BYTE r, BYTE g, BYTE b){
	if(A.cont[0] > B.cont[0])	std::swap(A, B);
	if(B.cont[0] > C.cont[0])	std::swap(B, C);
	if(A.cont[0] > B.cont[0])	std::swap(A, B);
	if(A.cont[0] == C.cont[0])	return;
	
	int minx,maxx,miny,maxy;
	
	float kAC = (A.cont[1] - C.cont[1])/(A.cont[0] - C.cont[0]);
	if(A.cont[0] != B.cont[0]){
		float kAB = (A.cont[1] - B.cont[1])/(A.cont[0] - B.cont[0]);
		minx=ceil(A.cont[0]);
		maxx=floor(B.cont[0]);
		for(int i = minx; i <= maxx; i++){
			float y1 = A.cont[1] + kAB * (i - A.cont[0]), y2 = A.cont[1] + kAC * (i - A.cont[0]);
			miny=ceil(std::min(y1, y2));
			maxy=floor(std::max(y1, y2));
			for(int j = miny; j <= maxy; j++){
				setbmppixel(pBuf, i, j, r, g, b);
			}
		}
	}
	if(B.cont[0] != C.cont[0]){
		float kBC = (B.cont[1] - C.cont[1])/(B.cont[0] - C.cont[0]);
		minx=ceil(B.cont[0]);
		maxx=floor(C.cont[0]);
		for(int i = minx; i <= maxx; i++){
			float y1 = C.cont[1] + kBC * (i - C.cont[0]), y2 = C.cont[1] + kAC * (i - C.cont[0]);
			miny=ceil(std::min(y1, y2));
			maxy=floor(std::max(y1, y2));
			for(int j = miny; j <= maxy; j++){
				setbmppixel(pBuf, i, j, r, g, b);
			}
		}
	}
	return;
}

void settri_quick(BYTE pBuf[], Vector A, Vector B, Vector C, BYTE r, BYTE g, BYTE b){
	if(A.cont[1] > B.cont[1])	std::swap(A, B);
	if(B.cont[1] > C.cont[1])	std::swap(B, C);
	if(A.cont[1] > B.cont[1])	std::swap(A, B);
	if(A.cont[1] == C.cont[1])	return;
	
	int minx,maxx,miny,maxy,i,j,k;
	float x1,x2;
	
	float kAC = (A.cont[0] - C.cont[0])/(A.cont[1] - C.cont[1]);
	if(A.cont[1] != B.cont[1]){
		float kAB = (A.cont[0] - B.cont[0])/(A.cont[1] - B.cont[1]);
		miny=ceil(A.cont[1]);
		maxy=floor(B.cont[1]);
		for(i = miny; i <= maxy; i++){
			x1 = A.cont[0] + kAB * (i - A.cont[1]);
			x2 = A.cont[0] + kAC * (i - A.cont[1]);
			minx=ceil(std::min(x1, x2));
			maxx=floor(std::max(x1, x2));
			k=((windowheight-i)*windowwidth+minx)*3;
			for(j = minx; j <= maxx; j++){
				pBuf[k++]=b;
				pBuf[k++]=g;
				pBuf[k++]=r;
			}
		}
	}
	if(B.cont[1] != C.cont[1]){
		float kBC = (B.cont[0] - C.cont[0])/(B.cont[1] - C.cont[1]);
		miny=ceil(B.cont[1]);
		maxy=floor(C.cont[1]);
		for(i = miny; i <= maxy; i++){
			x1 = C.cont[0] + kBC * (i - C.cont[1]);
			x2 = C.cont[0] + kAC * (i - C.cont[1]);
			minx=ceil(std::min(x1, x2));
			maxx=floor(std::max(x1, x2));
			k=((windowheight-i)*windowwidth+minx)*3;
			for(j = minx; j <= maxx; j++){
				pBuf[k++]=b;
				pBuf[k++]=g;
				pBuf[k++]=r;
			}
		}
	}
	return;
}


#endif
