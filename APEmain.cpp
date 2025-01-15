#include"APEFL.h"

using namespace std;

int main(){
	HDC hdc = GetDC(NULL);
	Vector4 vt=Vector4(1,5,4,3);
	Vector4::print(vt); 
	Vector3 vtt=Vector3(5,7,2);
	Vector3::print(vtt); 
	int k=-10086;
	cout<<abs(k)<<"\n"; //测试中文注释
    return 0;
}
