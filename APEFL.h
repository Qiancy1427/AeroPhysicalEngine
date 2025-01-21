#include<bits/stdc++.h>
#include<sys/time.h>

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
	COLORREF rgbt;
	rgbt = (int)(r+g*256+b*256*256); 
	
	return rgbt;
} 

void setrect(HDC hdc,Vector2 poslt,Vector2 posrb,COLORREF color){
	for(int i=round(poslt.y);i<=round(posrb.y);i++){
		for(int j=round(poslt.x);j<=round(posrb.x);j++){
			SetPixel(hdc,j,i,color);
		}
	}
	return;
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
	if(A.x == C.x)	return ;
	float kAC = (A.y - C.y)/(A.x - C.x);
	float dy = A.y + kAC * (B.x - A.x);
	if(A.x != B.x){
		float kAB = (A.y - B.y)/(A.x - B.x);
		for(int i = ceil(A.x); i <= floor(B.x); i++){
			int y1 = A.y + kAB * (i - A.x), y2 = A.y + kAC * (i - A.x);
			for(int j = std::min(y1, y2); j <= std::max(y1, y2); j++){
				setbmppixel(pBuf, i, j, r, g, b);
			}
		}
	}
	if(B.x != C.x){
		float kBC = (B.y - C.y)/(B.x - C.x);
		for(int i = ceil(B.x); i <= floor(C.x); i++){
			int y1 = B.y + kBC * (i - B.x), y2 = dy + kAC * (i - B.x);
			for(int j = std::min(y1, y2); j <= std::max(y1, y2); j++){
				setbmppixel(pBuf, i, j, r, g, b);
			}
		}
	}
	return ;
}

#endif
