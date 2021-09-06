#include<iostream>
#include<cstdio>
#include<conio.h>	//getch���
#include<windows.h>	//��ǥ���

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define ENTER 4
#define TAB 5

using namespace std;

void init() {
	//�ܼ� ũ�� ���ϱ�
	system("mode con cols=80 lines=30");
}

void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);	//�ܼ� �ڵ� ��������
	COORD pos = { x, y };
	SetConsoleCursorPosition(consoleHandle, pos);
}

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

void title() {
	//title ����ϱ�
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "--------------------------------------------------------------------------------" << endl<<endl;
	cout << "                ##       ##        #        #######     ########" << endl;
	cout << "                ####   ####      ## ##      ##    ##       ##" << endl;
	cout << "                ##  ###  ##     ##   ##     #######        ##" << endl;
	cout << "                ##   #   ##    #########    ##    ##       ##" << endl;
	cout << "                ##       ##   ##       ##   ##     ##      ##" << endl;
	cout << "                ##       ##   ##       ##   ##     ##      ##" << endl<<endl;
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "--------------------------------------------------------------------------------" << endl<<endl;
}


int menu(){
	int x = 36;
	int y = 14;

	//�޴����
	gotoxy(x-6, y-1); //30, 13
	cout << "---------------------" << endl;
	gotoxy(x-2, y);	//34, 14
	cout << "> ���� ����" << endl;
	gotoxy(x, y + 1);	//36, 15
	cout << "ǰ�� �߰�" << endl;
	gotoxy(x, y + 2);	//36, 16
	cout << "ǰ�� ����" << endl;
	gotoxy(x, y + 3);	//36, 17
	cout << " ��   ��  " << endl;
	gotoxy(x, y + 4);	//36, 18
	cout << " ��   ��" << endl;
	gotoxy(x, y + 5);	//36, 19
	cout << " ��   ��" << endl;
	gotoxy(x, y + 6);	//36, 20
	cout << " ȯ   ��" << endl;
	gotoxy(x, y + 7);	//36, 21
	cout << " ��   ��" << endl;
	gotoxy(x-6, y + 8);	//36, 22
	cout << "---------------------" << endl << endl;
	
	//�޴�����
	while (true) {	//���� �ݺ�
		int n = keyControl();
		switch (n) {
		case UP:	//�踦 ������ ���
			if (y > 14) {	//y�� 14~21���̸� �̵� -> 14���� Ŀ����
				gotoxy(x - 2, y);	//���� ���ۿ� �ִ� >
				cout << " ";	//�����
				gotoxy(x - 2, --y);	//�������� 1ĭ �̵���
				cout << ">";	//�ٽ� �׸���
			}
			else if (y == 14) {
				gotoxy(x - 2, y);
				cout << " ";
				y = 21;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	//�鸦 ������ ���
			if (y < 21) {	//y�� 14~21���̸� �̵� -> 21���� �۾ƾ���
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);	//�Ʒ������� 1ĭ �̵���
				cout << ">";
			}
			else if (y == 21) {
				gotoxy(x - 2, y);
				cout << " ";
				y = 14;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case ENTER:	//���� -> �������� ���
			return y - 14;	//y-14�� �Ͽ� �� ���� ���� 1, 2, 3...���� ���� �� �ִ�.
		}
	}
}

//TABŰ : Main���� ����������
struct Product {
	//��ǰ
	string productName;	//��ǰ �̸�
	int price;			//��ǰ ����
	int quantity;		//��ǰ ����
};

void totalProfit() {
	//���� ���� -> �Һ��ڵ��� ���ŷ� ���� ����
	system("cls");
	cout << "������� ������ ���� : ";

	while (true) {
		if (keyControl() == TAB) {
			break;
		}
	}
}

void addProduct() {
	//ǰ���߰�(���� ���� ��ǰ)
	system("cls");
	cout << "ǰ���� �߰��մϴ�.";

	while (true) {
		if (keyControl() == TAB) {
			break;
		}
	}

}

void delProduct() {
	//ǰ�����(���� ���� ��ǰ)
	system("cls");
	cout << "ǰ���� �����մϴ�.";

	while (true) {
		if (keyControl() == TAB) {
			break;
		}
	}
}

void buy() {
	//����(ǰ���� ã�Ƽ�, �� ������ŭ -)
	system("cls");
	cout << "�����մϴ�.";

	while (true) {
		if (keyControl() == TAB) {
			break;
		}
	}
}

void refund() {
	//ȯ��(ǰ���� ã�Ƽ�, ȯ���� ������ŭ +)
	system("cls");
	cout << "ȯ���մϴ�.";

	while (true) {
		if (keyControl() == TAB) {
			break;
		}
	}
}

void warehousing() {
	//�԰�(���� �ִ� ��ǰ�� ���� +)
	system("cls");
	cout << "�԰�˴ϴ�.";

	while (true) {
		if (keyControl() == TAB) {
			break;
		}
	}
}

void release() {
	//���(���� �ִ� ��ǰ�� ���� -)
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
			gotoxy(36, 23); break;
		}
		system("cls");
	}
	return 0;
}
	