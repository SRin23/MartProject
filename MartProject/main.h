#pragma once

//방향키 및 키값 정의
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define ENTER 4	//ENTER키 : t선택
#define TAB 5	//TAB키 : Main으로 빠져나오기

#ifndef __IOSTREAM__
#define __IOSTREAM__
#include<iostream>
#endif

#ifndef __CSTDIO__
#define __CSTDIO__
#include<cstdio>
#endif

#ifndef __CONIO_H__
#define __CONIO_H__
#include<conio.h>	//getch사용
#endif

#ifndef __WINDOWS_H__
#define __WINDOWS_H__
#include<windows.h>	//좌표사용
#endif

#ifndef __STRING__
#define __STRING__
#include <string>
#endif

int allSum = 0;