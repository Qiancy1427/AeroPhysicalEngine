#include<bits/stdc++.h>
#include<Windows.h>

#ifndef APEFL   
#define APEFL  1  

//classify vector starting
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
	Vector3 Vector3::operator+(Vector3 v1) {//addtion 
	    Vector3 vt;
	    vt.x = vt.x + v1.x;
	    vt.y = vt.y + v1.y;
	    vt.z = vt.z + v1.z;
	    return vt;
	}
	Vector3 Vector3::operator-(Vector3 v1) {//subtraction
	    Vector3 vt;
	    vt.x = vt.x - v1.x;
	    vt.y = vt.y - v1.y;
	    vt.z = vt.z - v1.z;
	    return vt;
	}
	float Vector3::operator*(Vector3 v1) {//��� 
	    float tmp;
	    Vector3 vt;
	    tmp = vt.x * v1.x + vt.y * v1.y + vt.z * v1.z;
	    return tmp;
	}
	Vector3 Vector3::operator^(float k) {//���� 
	    Vector3 vt;
	    vt.x = vt.x * k;
	    vt.y = vt.y * k;
	    vt.z = vt.z * k;
	    return vt;
	}
	void Vector3::print(Vector3 v1) {//������� 
	    std::cout << "(" << v1.x << "," << v1.y << "," << v1.z << ")\n";
	}
	
	class Vector4 {//����������� 
	public:
	    Vector4();
	    Vector4(float a, float b, float c, float d);
	    static void print(Vector4 v1);
	    static Vector3 normalize(Vector4 v1);
	    float x, y, z, w;
	};
	Vector4::Vector4() {//�½������� 
	    x = 0;
	    y = 0;
	    z = 0;
	    w = 1;
	}
	Vector4::Vector4(float a, float b, float c, float d) {//�������� 
	    x = a;
	    y = b;
	    z = c;
	    w = d;
	}
	void Vector4::print(Vector4 v1) {//������� 
	    std::cout << "(" << v1.x << "," << v1.y << "," << v1.z << "," << v1.w << ")\n";
	}
	Vector3 Vector4::normalize(Vector4 v1) {//��һ��������� 
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


#endif
