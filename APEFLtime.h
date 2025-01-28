#ifndef APEFLtime  
#define APEFLtime

#include"APEFLhead.h"
#include"APEFLmath.h"

#define targetfps 60

//deltatime系统 
struct timeval render_previoustime,render_presenttime,logic_previoustime,logic_presenttime;
int render_deltatime,logic_deltatime;

//fps系统（基于deltatime系统） 
queue<int> render_last20dt,logic_last20dt;
int render_fps,logic_fps;

#endif
