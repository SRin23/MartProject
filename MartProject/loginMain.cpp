#include<iostream>
#include<cstdio>
#include<conio.h>	//getch사용
#include<windows.h>	//좌표사용

using namespace std;

void init();	//초기화
void gotoxy(int x, int y);	//좌표찍기

int main() {
	init();
	gotoxy(10, 20);
	cout << "로그인";
	string id;
	string password;
	if (id == "manager" && password == "manager01") {
		//martSystem_Manager.cpp
	}
	else if (id == "cashier" && password == "cashier01") {
		//martSystem_Cashier.cpp
	}
	else {
		//잘못된 아이디/비밀번호 입니다.
	}
	return 0;
}

//초기화
void init() {
	//콘솔 크기 정하기
	system("mode con cols=80 lines=30");

	//깜빡거리는 커서 숨기기
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

//좌표찍기
void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x, y };
	SetConsoleCursorPosition(consoleHandle, pos);
}
