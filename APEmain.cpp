#include<bits/stdc++.h>
#include<windows.h>
#include<winuser.h>
#include<wingdi.h>
#include<conio.h>
#include"APEFL.h"

using namespace std;

//int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, char *lpcmdline, int nShowcmd){
//    return MessageBox(NULL, L"hello world", L"caption", 0);
//}

int main(){
#ifdef UNICODE
    cout << L"UNICODE";
#else
    cout << "UNICODE";
#endif
    return 0;
}
