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


#ifndef APEFL   
#define APEFL  1


#define targetfps 20
#define windowwidth 1900
#define windowheight 1000


//classify vector starting
class Vector2 {//classify Vector2
	public:
	    Vector2();
	    Vector2(float a, float b);
	    Vector2 operator+ (Vector2 v1);
	    Vector2 operator- (Vector2 v1);
	    float operator* (Vector2 v1);
	    Vector2 operator^ (float k);
	    static void print(Vector2 v1);
	    float x, y;
	};
	Vector2::Vector2() {//empty Vector2 
	    x = 0;
	    y = 0;
	}
	Vector2::Vector2(float a, float b) {//Vector2 container 
	    x = a;
	    y = b;
	}
	Vector2 Vector2::operator+(Vector2 v1) {//Vector2 addtion 
	    Vector2 vt;
	    vt.x = vt.x + v1.x;
	    vt.y = vt.y + v1.y;
	    return vt;
	}
	Vector2 Vector2::operator-(Vector2 v1) {//Vector2 subtraction
	    Vector2 vt;
	    vt.x = vt.x - v1.x;
	    vt.y = vt.y - v1.y;
	    return vt;
	}
	float Vector2::operator*(Vector2 v1) {//Vector2 dot production
	    float tmp;
	    Vector2 vt;
	    tmp = vt.x * v1.x + vt.y * v1.y;
	    return tmp;
	}
	Vector2 Vector2::operator^(float k) {//Vector2 scalar multiplication
	    Vector2 vt;
	    vt.x = vt.x * k;
	    vt.y = vt.y * k;
	    return vt;
	}
	void Vector2::print(Vector2 v1) {//print Vector2
	    std::cout << "(" << v1.x << "," << v1.y << ")\n";
	}
	
	class Vector3 {//classify Vector3
	public:
	    Vector3();
	    Vector3(float a, float b, float c);
	    Vector3 operator+ (Vector3 v1);
	    Vector3 operator- (Vector3 v1);
	    float operator* (Vector3 v1);
	    Vector3 operator^ (float k);
	    static void print(Vector3 v1);
	    float x, y, z;
	};
	Vector3::Vector3() {//empty Vector3 
	    x = 0;
	    y = 0;
	    z = 0;
	}
	Vector3::Vector3(float a, float b, float c) {//Vector3 container 
	    x = a;
	    y = b;
	    z = c;
	}
	Vector3 Vector3::operator+(Vector3 v1) {//Vector3 addtion 
	    Vector3 vt;
	    vt.x = vt.x + v1.x;
	    vt.y = vt.y + v1.y;
	    vt.z = vt.z + v1.z;
	    return vt;
	}
	Vector3 Vector3::operator-(Vector3 v1) {//Vector3 subtraction
	    Vector3 vt;
	    vt.x = vt.x - v1.x;
	    vt.y = vt.y - v1.y;
	    vt.z = vt.z - v1.z;
	    return vt;
	}
	float Vector3::operator*(Vector3 v1) {//Vector3 dot production
	    float tmp;
	    Vector3 vt;
	    tmp = vt.x * v1.x + vt.y * v1.y + vt.z * v1.z;
	    return tmp;
	}
	Vector3 Vector3::operator^(float k) {//Vector3 scalar multiplication
	    Vector3 vt;
	    vt.x = vt.x * k;
	    vt.y = vt.y * k;
	    vt.z = vt.z * k;
	    return vt;
	}
	void Vector3::print(Vector3 v1) {//print Vector3
	    std::cout << "(" << v1.x << "," << v1.y << "," << v1.z << ")\n";
	}
	
	class Vector4 {//classify Vector4
	public:
	    Vector4();
	    Vector4(float a, float b, float c, float d);
	    static void print(Vector4 v1);
	    static Vector3 normalize(Vector4 v1);
	    float x, y, z, w;
	};
	Vector4::Vector4() {//empty Vector4 
	    x = 0;
	    y = 0;
	    z = 0;
	    w = 1;
	}
	Vector4::Vector4(float a, float b, float c, float d) {//Vector4 container 
	    x = a;
	    y = b;
	    z = c;
	    w = d;
	}
	void Vector4::print(Vector4 v1) {//print Vector4
	    std::cout << "(" << v1.x << "," << v1.y << "," << v1.z << "," << v1.w << ")\n";
	}
	Vector3 Vector4::normalize(Vector4 v1) {//Vector4 narmalization
		Vector3 vt;
		vt.x=v1.x/v1.w;
		vt.y=v1.y/v1.w;
		vt.z=v1.z/v1.w;
		return vt;
	}
//classify vector ending

//classify Task starting
	class Task {//classify Task
	public:
	    Vector2 A, B, C;
	    BYTE r,g,b;
	};
//classify Task ending
 
struct NBT {//define NBT
    std::string name;
    Vector4 data;
    NBT(std::string st, Vector4 qt){//NBT constructor

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

void settri(BYTE pBuf[], Vector2 A, Vector2 B, Vector2 C, BYTE r, BYTE g, BYTE b){
	if(A.x > B.x)	std::swap(A, B);
	if(B.x > C.x)	std::swap(B, C);
	if(A.x > B.x)	std::swap(A, B);
	if(A.x == C.x)	return;
	
	int minx,maxx,miny,maxy;
	
	float kAC = (A.y - C.y)/(A.x - C.x);
	if(A.x != B.x){
		float kAB = (A.y - B.y)/(A.x - B.x);
		minx=ceil(A.x);
		maxx=floor(B.x);
		for(int i = minx; i <= maxx; i++){
			float y1 = A.y + kAB * (i - A.x), y2 = A.y + kAC * (i - A.x);
			miny=ceil(std::min(y1, y2));
			maxy=floor(std::max(y1, y2));
			for(int j = miny; j <= maxy; j++){
				setbmppixel(pBuf, i, j, r, g, b);
			}
		}
	}
	if(B.x != C.x){
		float kBC = (B.y - C.y)/(B.x - C.x);
		minx=ceil(B.x);
		maxx=floor(C.x);
		for(int i = minx; i <= maxx; i++){
			float y1 = C.y + kBC * (i - C.x), y2 = C.y + kAC * (i - C.x);
			miny=ceil(std::min(y1, y2));
			maxy=floor(std::max(y1, y2));
			for(int j = miny; j <= maxy; j++){
				setbmppixel(pBuf, i, j, r, g, b);
			}
		}
	}
	return;
}

void settri_quick(BYTE pBuf[], Vector2 A, Vector2 B, Vector2 C, BYTE r, BYTE g, BYTE b){
	if(A.y > B.y)	std::swap(A, B);
	if(B.y > C.y)	std::swap(B, C);
	if(A.y > B.y)	std::swap(A, B);
	if(A.y == C.y)	return;
	
	int minx,maxx,miny,maxy,i,j,k;
	float x1,x2;
	
	float kAC = (A.x - C.x)/(A.y - C.y);
	if(A.y != B.y){
		float kAB = (A.x - B.x)/(A.y - B.y);
		miny=ceil(A.y);
		maxy=floor(B.y);
		for(i = miny; i <= maxy; i++){
			x1 = A.x + kAB * (i - A.y);
			x2 = A.x + kAC * (i - A.y);
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
	if(B.y != C.y){
		float kBC = (B.x - C.x)/(B.y - C.y);
		miny=ceil(B.y);
		maxy=floor(C.y);
		for(i = miny; i <= maxy; i++){
			x1 = C.x + kBC * (i - C.y);
			x2 = C.x + kAC * (i - C.y);
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
