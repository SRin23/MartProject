#include<iostream>
#include<cstdio>
#include<conio.h>	//getch���
#include<windows.h>	//��ǥ���

using namespace std;

void init();	//�ʱ�ȭ
void gotoxy(int x, int y);	//��ǥ���

int main() {
	init();
	gotoxy(35, 10);
	cout << "<Log-in>";
	string id;
	string password;
	gotoxy(31, 12);
	cout << "���̵� : ";
	cin >> id;
	gotoxy(31, 13);
	cout << "��й�ȣ : ";
	cin >> password;

	if (id == "manager" && password == "manager01") {
		//martSystem_Manager.cpp
		cout << "��Ʈ����" << endl;
	}
	else if (id == "cashier" && password == "cashier01") {
		//martSystem_Cashier.cpp
		cout << "��Ʈ���" << endl;
	}
	else {
		//�߸��� ���̵�/��й�ȣ �Դϴ�.
		cout << "�߸��� ���̵�/��й�ȣ �Դϴ�." << endl;
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
