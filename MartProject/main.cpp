#include<iostream>
#include<cstdio>
#include<conio.h>	//getch���
#include<windows.h>	//��ǥ���

//����Ű �� Ű�� ����
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define ENTER 4	//ENTERŰ : t����
#define TAB 5	//TABŰ : Main���� ����������

using namespace std;

void init();	//�ʱ�ȭ
void gotoxy(int x, int y);	//��ǥ���
int keyControl();	//����Ű�� ��ǥ �����ϱ�
void title();	//title ����ϱ�
int menu();	//�޴� ���, ����

//��ǰ����
struct Product {
	string productName;	//��ǰ �̸�
	int price;			//��ǰ ����
	int quantity;		//��ǰ ����
};


//-------------���ÿ� ���� ��� �Լ���----------------//

//���� ���� -> �Һ��ڵ��� ���ŷ� ���� ����
void totalProfit() {
	system("cls");
	cout << "������� ������ ���� : ";

	while (true) {
		if (keyControl() == TAB) {
			break;
		}
	}
}

//ǰ���߰�(���� ���� ��ǰ)
void addProduct() {
	system("cls");
	cout << "ǰ���� �߰��մϴ�.";

	while (true) {
		if (keyControl() == TAB) {
			break;
		}
	}

}

//ǰ�����(���� ���� ��ǰ)
void delProduct() {
	system("cls");
	cout << "ǰ���� �����մϴ�.";

	while (true) {
		if (keyControl() == TAB) {
			break;
		}
	}
}

//����(ǰ���� ã�Ƽ�, �� ������ŭ -)
void buy() {
	system("cls");
	cout << "�����մϴ�.";

	while (true) {
		if (keyControl() == TAB) {
			break;
		}
	}
}

//ȯ��(ǰ���� ã�Ƽ�, ȯ���� ������ŭ +)
void refund() {
	system("cls");
	cout << "ȯ���մϴ�.";

	while (true) {
		if (keyControl() == TAB) {
			break;
		}
	}
}

//�԰�(���� �ִ� ��ǰ�� ���� +)
void warehousing() {
	system("cls");
	cout << "�԰�˴ϴ�.";

	while (true) {
		if (keyControl() == TAB) {
			break;
		}
	}
}

//���(���� �ִ� ��ǰ�� ���� -)
void release() {
	system("cls");
	cout << "���˴ϴ�.";

	while (true) {
		if (keyControl() == TAB) {
			break;
		}
	}
}

int main() {
	init();
	
	while (true) {
		title();
		
		//�޴� ���� -> �Լ�
		int select = menu();
		if (select == 0) totalProfit();
		else if (select == 1) addProduct();
		else if (select == 2) delProduct();
		else if (select == 3) warehousing();
		else if (select == 4) release();
		else if (select == 5) buy();
		else if (select == 6) refund();
		else if (select == 7) {
			gotoxy(0, 27); break;
		}
		system("cls");
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

//����Ű�� ��ǥ �����ϱ�
int keyControl() {
	/*
	if (GetAsyncKeyState(VK_UP) & 0x0001) {	//����
		return UP;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x0001) {	//�Ʒ���
		return DOWN;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x0001) {	//����
		return LEFT;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x0001) {	//������
		return RIGHT;
	}
	if (GetAsyncKeyState(VK_RETURN) & 0x0001) {	//����Ű
		return ENTER;
	}
	*/
	char tmp = _getch();
	if (tmp == -32) {
		tmp = _getch();
		switch (tmp) {
		case 72:	//��
			return UP; break;
		case 80:	//�Ʒ�
			return DOWN; break;
		case 75:	//����
			return LEFT; break;
		case 77:	//������
			return RIGHT; break;
		}
	}
	if (tmp == 13) {	//enter
		return ENTER;
	}
	if (tmp == 9) {		//tab
		return TAB;
	}
}

//title ����ϱ�
void title() {
	gotoxy(10, 2);cout << "------------------------------------------------------------" << endl;
	gotoxy(16, 5); cout << "##       ##        #        #######     ########" << endl;
	gotoxy(16, 6); cout << "####   ####      ## ##      ##    ##       ##" << endl;
	gotoxy(16, 7); cout << "##  ###  ##     ##   ##     #######        ##" << endl;
	gotoxy(16, 8); cout << "##   #   ##    #########    ##    ##       ##" << endl;
	gotoxy(16, 9); cout << "##       ##   ##       ##   ##     ##      ##" << endl;
	gotoxy(16, 10); cout << "##       ##   ##       ##   ##     ##      ##" << endl << endl;
	gotoxy(10, 13); cout << "------------------------------------------------------------" << endl;
}

//�޴�����
int menu() {
	int x = 36;
	int y = 17;

	//�޴����
	gotoxy(x - 6, y - 1); //30, 16
	cout << "---------------------" << endl;
	gotoxy(x - 2, y);	//34, 17
	cout << "> ���� ����" << endl;
	gotoxy(x, y + 1);	//36, 18
	cout << "ǰ�� �߰�" << endl;
	gotoxy(x, y + 2);	//36, 19
	cout << "ǰ�� ����" << endl;
	gotoxy(x, y + 3);	//36, 20
	cout << " ��   ��  " << endl;
	gotoxy(x, y + 4);	//36, 21
	cout << " ��   ��" << endl;
	gotoxy(x, y + 5);	//36, 22
	cout << " ��   ��" << endl;
	gotoxy(x, y + 6);	//36, 23
	cout << " ȯ   ��" << endl;
	gotoxy(x, y + 7);	//36, 24
	cout << " ��   ��" << endl;
	gotoxy(x - 6, y + 8);	//36, 25
	cout << "---------------------" << endl << endl;

	//�޴�����
	while (true) {	//���� �ݺ�
		int n = keyControl();
		switch (n) {
		case UP:	//�踦 ������ ���
			if (y > 17) {	//y�� 17~24���̸� �̵� -> 17���� Ŀ����
				gotoxy(x - 2, y);	//���� ���ۿ� �ִ� >
				cout << " ";	//�����
				gotoxy(x - 2, --y);	//�������� 1ĭ �̵���
				cout << ">";	//�ٽ� �׸���
			}
			else if (y == 17) {	//�� �� -> �� �Ʒ��� �̵�
				gotoxy(x - 2, y);
				cout << " ";
				y = 24;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	//�鸦 ������ ���
			if (y < 24) {	//y�� 17~24���̸� �̵� -> 24���� �۾ƾ���
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);	//�Ʒ������� 1ĭ �̵���
				cout << ">";
			}
			else if (y == 24) {	//�� �Ʒ� -> �� ���� �̵�
				gotoxy(x - 2, y);
				cout << " ";
				y = 17;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case ENTER:	//���� -> �������� ���
			return y - 17;	//y-17�� �Ͽ� �� ���� ���� 1, 2, 3...���� ���� �� �ִ�. -> �� ����
		}
	}
}
