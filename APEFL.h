#include<bits/stdc++.h>
#include<sys/time.h>

#include<Windows.h>
#include<Mmsystem.h>
//#include<Prnasnot.h>
#include<T2embapi.h>
#include<Tvout.h>
#include<Windef.h>
#include<Windowsx.h>
#include<Wingdi.h>
#include<Winuser.h>


#ifndef APEFL   
#define APEFL  1


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
void printrect(HDC hdc,Vector2 poslt,Vector2 posrb,COLORREF color){
	BYTE *g_pBits;
	HDC g_hMemDC;
	HBITMAP g_hBmp, g_hOldBmp;
	int xMin = poslt.x;
	int yMin = poslt.y;
	int xMax = posrb.x;
	int yMax = posrb.y;
	int iWidth = xMax - xMin;
	int iHeight = yMax - yMin;
	
	int x,y;
	
	byte r = GetRValue(color);
	byte g = GetGValue(color);
	byte b = GetBValue(color);
	
	
	g_hMemDC = CreateCompatibleDC(hdc);
    if (!g_hMemDC){
        DeleteDC(hdc);
    }
    
    BYTE bmibuf[sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD)];
	
    memset(bmibuf, 0, sizeof(bmibuf));

    BITMAPINFO* pbmi = (BITMAPINFO*)bmibuf;
    
    pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);

    pbmi->bmiHeader.biWidth = iWidth;

    pbmi->bmiHeader.biHeight = iHeight;

    pbmi->bmiHeader.biPlanes = 1;


    pbmi->bmiHeader.biBitCount = 24;

    pbmi->bmiHeader.biCompression = BI_RGB;



    g_hBmp = ::CreateDIBSection(g_hMemDC, pbmi, DIB_RGB_COLORS, (void **)&g_pBits, 0, 0);

    if (!g_hBmp)

    {

        ::DeleteDC(g_hMemDC);

    }



    g_hOldBmp = (HBITMAP)::SelectObject(g_hMemDC, g_hBmp);
	
	
	
	BitBlt(g_hMemDC,0,0,iWidth,iHeight,hdc,0,0,SRCCOPY);
	
	for (y = 0; y < iHeight; y++)
	
	{
	
	  for (x = 0; x < iWidth; x++)
	
	  {
	
	   rSrc = g_pBits[y * iWidth * 3  + x * 3 + 2];
	
	   gSrc = g_pBits[y * iWidth * 3  + x * 3 + 1];
	
	   bSrc = g_pBits[y * iWidth * 3  + x * 3];
	
	   
	
	   rSrc = (rSrc * alpha + r * (255 - alpha)) >>8;
	
	   gSrc = (gSrc * alpha + g * (255 - alpha)) >>8;
	
	   bSrc = (bSrc * alpha + b * (255 - alpha)) >>8;
	
	   g_pBits[y * iWidth * 3  + x * 3 + 2] = rSrc;
	
	   g_pBits[y * iWidth * 3  + x * 3 + 1] = gSrc;
	
	   g_pBits[y * iWidth * 3  + x * 3]     = bSrc;
	
	  }
	
	}
	
	BitBlt(hdc, 0, 0, iWidth, iHeight, g_hMemDC, 0, 0, SRCCOPY); 
	
	SelectObject(g_hMemDC, g_hOldBmp); 
	
	DeleteObject(g_hBmp); 
	
	DeleteDC(g_hMemDC); 
	
	ReleaseDC(NULL, hdc); 
	
	return;
}
void gdiRectangleAlpha(HDC hdc,const RECT *rect,COLORREF color, unsigned char alpha){//Ò°¼¦²©¿ÍÕÒµÄ²Î¿¼ 

	BYTE *g_pBits;
	HDC g_hMemDC;
	
	HBITMAP g_hBmp, g_hOldBmp;
	
	int xMin = rect->left;
	int yMin = rect->top;
	int xMax = rect->right;
	int yMax = rect->bottom;
	
	int x,y;
	
	
	
	byte r = GetRValue(color);
	
	byte g = GetGValue(color);
	
	byte b = GetBValue(color);
	
	COLORREF clSrc;
	
	unsigned char   rSrc;
	
	unsigned char gSrc;
	
	unsigned char   bSrc;
	
	g_hMemDC = CreateCompatibleDC(hdc);
	
	    if (!g_hMemDC)
	    {
	        DeleteDC(hdc);

	    }
	
	
	int iWidth = rect->right - rect->left;
	
	int iHeight = rect->bottom - rect->top;
	
	
	    BYTE bmibuf[sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD)];
	
	    memset(bmibuf, 0, sizeof(bmibuf));
	
	    BITMAPINFO* pbmi = (BITMAPINFO*)bmibuf;
	
	// BITMAPINFO pbmi;
	
	    pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	
	    pbmi->bmiHeader.biWidth = iWidth;
	
	    pbmi->bmiHeader.biHeight = iHeight;
	
	    pbmi->bmiHeader.biPlanes = 1;
	
	
	    pbmi->bmiHeader.biBitCount = 24;
	
	    pbmi->bmiHeader.biCompression = BI_RGB;
	
	
	
	    g_hBmp = ::CreateDIBSection(g_hMemDC, pbmi, DIB_RGB_COLORS, (void **)&g_pBits, 0, 0);
	
	    if (!g_hBmp)
	
	    {
	
	        ::DeleteDC(g_hMemDC);
	
	    }
	
	
	
	    g_hOldBmp = (HBITMAP)::SelectObject(g_hMemDC, g_hBmp);
	
	
	
	BitBlt(g_hMemDC,0,0,iWidth,iHeight,hdc,0,0,SRCCOPY);
	
	
	
	// offset = y * (width * 24 / 8) + x * (24 / 8)
	
	for (y = 0; y < iHeight; y++)
	
	{
	
	  for (x = 0; x < iWidth; x++)
	
	  {
	
	   rSrc = g_pBits[y * iWidth * 3  + x * 3 + 2];
	
	   gSrc = g_pBits[y * iWidth * 3  + x * 3 + 1];
	
	   bSrc = g_pBits[y * iWidth * 3  + x * 3];
	
	   
	
	   rSrc = (rSrc * alpha + r * (255 - alpha)) >>8;
	
	   gSrc = (gSrc * alpha + g * (255 - alpha)) >>8;
	
	   bSrc = (bSrc * alpha + b * (255 - alpha)) >>8;
	
	   g_pBits[y * iWidth * 3  + x * 3 + 2] = rSrc;
	
	   g_pBits[y * iWidth * 3  + x * 3 + 1] = gSrc;
	
	   g_pBits[y * iWidth * 3  + x * 3]     = bSrc;
	
	  }
	
	}
	
	BitBlt(hdc, 0, 0, iWidth, iHeight, g_hMemDC, 0, 0, SRCCOPY); 
	
	SelectObject(g_hMemDC, g_hOldBmp); 
	
	DeleteObject(g_hBmp); 
	
	DeleteDC(g_hMemDC); 
	
	ReleaseDC(NULL, hdc); 
	
	return;
}


#endif
