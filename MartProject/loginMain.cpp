#include<iostream>
#include<cstdio>
#include<conio.h>	//getch���
#include<windows.h>	//��ǥ���

using namespace std;

void init();	//�ʱ�ȭ
void gotoxy(int x, int y);	//��ǥ���

int main() {
	init();
	gotoxy(10, 20);
	cout << "�α���";
	string id;
	string password;
	if (id == "manager" && password == "manager01") {
		//martSystem_Manager.cpp
	}
	else if (id == "cashier" && password == "cashier01") {
		//martSystem_Cashier.cpp
	}
	else {
		//�߸��� ���̵�/��й�ȣ �Դϴ�.
	}
	return 0;
}

//�ʱ�ȭ
void init() {
	//�ܼ� ũ�� ���ϱ�
	system("mode con cols=80 lines=30");

	//�����Ÿ��� Ŀ�� �����
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

//��ǥ���
void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x, y };
	SetConsoleCursorPosition(consoleHandle, pos);
}
