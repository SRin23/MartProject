#include<iostream>
#include<cstdio>
#include<conio.h>	//getch���
#include<windows.h>	//��ǥ���
#include <string>
#include "Manager.h"

//����Ű �� Ű�� ����
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define ENTER 4	//ENTERŰ : t����
#define TAB 5	//TABŰ : Main���� ����������

using namespace std;

//ǰ���߰�(���� ���� ��ǰ) -> ��Ʈ -> �밭 OK
//����, �ִ� ��ǰ�̶�� �����ϴ� ǰ���Դϴ�.
void Manager::addProduct() {
	string productName;	//��ǰ �̸�
	int price;			//��ǰ ����
	int customerPrice;
	int quantity;		//��ǰ ����

	while (true) {
		system("cls");
		//totalProfit();
		gotoxy(33, 2);
		cout << "<ǰ�� �߰�>" << endl;
		gotoxy(10, 4);
		cout << "�� �߰��ϰ��� �ϴ� ǰ���� �̸�, ����, ������ �Է��ϼ��� ��" << endl;

		gotoxy(30, 7);
		cout << "��ǰ �̸� : ";
		cin >> productName;
		gotoxy(30, 8);
		cout << "��ǰ ���� : ";
		cin >> price;
		gotoxy(28, 9);
		cout << "�Һ��� ���� : ";
		cin >> customerPrice;
		gotoxy(30, 10);
		cout << "��ǰ ���� : ";
		cin >> quantity;

		product[cnt++] = new Product(productName, price, customerPrice, quantity);

		gotoxy(31, 12);
		cout << "<�߰��Ǿ����ϴ�>" << endl;

		if (keyControl() == TAB) {
			return;
		}
	}
}

//ǰ�����(���� ���� ��ǰ) -> �迭 �� ���� ����
void Manager::delProduct() {
	string productName;	//��ǰ �̸�
	while (true) {
		system("cls");
		//totalProfit();
		gotoxy(33, 2);
		cout << "<ǰ�� ����>" << endl;
		gotoxy(16, 4);
		cout << "�� �����ϰ��� �ϴ� ǰ���� �̸��� �Է��ϼ��� ��" << endl;

		gotoxy(32, 7);
		cout << "��ǰ �̸� : ";
		cin >> productName;

		int check = 0;
		for (int i = 0; i < 5; i++) {
			if ((product[i]->getProductName()) == productName) {
				delete product[i];
				gotoxy(31, 12);
				cout << "<�����Ǿ����ϴ�>" << endl;
				check = 1;
				break;
			}
		}

		if (check != 1) {
			cout << "ǰ���� �߰����� �ʾ� ������ �� �����ϴ�." << endl;
		}

		if (keyControl() == TAB) {
			return;
		}
	}
}

//�԰�(���� �ִ� ��ǰ�� ���� +)
void Manager::warehousing() {
	string productName;	//��ǰ �̸�
	int quantity;		//��ǰ ����
	int check;

	while (true) {
		system("cls");
		check = 0;
		//totalProfit();
		gotoxy(33, 2);
		cout << "<�԰�>" << endl;
		gotoxy(10, 4);
		cout << "�� �԰��ϰ��� �ϴ� ǰ���� �̸�, ������ �Է��ϼ��� ��" << endl;

		gotoxy(32, 7);
		cout << "��ǰ �̸� : ";
		cin >> productName;
		gotoxy(32, 8);
		cout << "��ǰ ���� : ";
		cin >> quantity;

		//product�迭�� ��ǰ�� �ִ��� Ȯ��
		for (int i = 0; i < cnt; i++) {
			if (product[i]->getProductName() == productName) {
				product[i]->addQuantity(quantity);
				gotoxy(31, 12);
				cout << "�԰�Ǿ����ϴ�." << endl;
				check = 1;
				break;
			}
		}
		if (check != 1) {
			gotoxy(20, 12);
			cout << "�������� �ʴ� ��ǰ�Դϴ�." << endl;
			gotoxy(23, 13);
			cout << "ǰ���� �߰��� �ּ���." << endl;
		}
		if (keyControl() == TAB) {
			return;
		}
	}
}

//���(���� �ִ� ��ǰ�� ���� -)
void Manager::release() {
	string productName;	//��ǰ �̸�
	int quantity;		//��ǰ ����
	int check;

	while (true) {
		system("cls");
		check = 0;
		totalProfit();
		gotoxy(33, 2);
		cout << "<���>" << endl;
		gotoxy(10, 4);
		cout << "�� �԰��ϰ��� �ϴ� ǰ���� �̸�, ������ �Է��ϼ��� ��" << endl;

		gotoxy(32, 7);
		cout << "��ǰ �̸� : ";
		cin >> productName;
		gotoxy(32, 8);
		cout << "��ǰ ���� : ";
		cin >> quantity;

		//product�迭�� ��ǰ�� �ִ��� Ȯ��
		for (int i = 0; i < cnt; i++) {
			if (product[i]->getProductName() == productName) {
				product[i]->disQuantity(quantity);
				gotoxy(31, 12);
				cout << "���Ǿ����ϴ�." << endl;
				check = 1;
				break;
			}
		}
		if (check != 1) {
			gotoxy(20, 12);
			cout << "�������� �ʴ� ��ǰ�Դϴ�." << endl;
			gotoxy(23, 13);
			cout << "ǰ���� �߰��� �ּ���." << endl;
		}
		if (keyControl() == TAB) {
			return;
		}
	}
}

//title ����ϱ�
void Manager::title() {
	gotoxy(10, 2); cout << "------------------------------------------------------------";
	gotoxy(16, 5); cout << "##       ##        #        #######     ########";
	gotoxy(16, 6); cout << "####   ####      ## ##      ##    ##       ##";
	gotoxy(16, 7); cout << "##  ###  ##     ##   ##     #######        ##";
	gotoxy(16, 8); cout << "##   #   ##    #########    ##    ##       ##";
	gotoxy(16, 9); cout << "##       ##   ##       ##   ##     ##      ##";
	gotoxy(16, 10); cout << "##       ##   ##       ##   ##     ##      ##";
	gotoxy(55, 12); cout << "_for manager";
	gotoxy(10, 14); cout << "------------------------------------------------------------" << endl;
}

//�޴�����
int Manager::menu() {
	int x = 36;
	int y = 17;

	//�޴����
	gotoxy(x - 6, y - 1); //30, 16
	cout << "---------------------" << endl;
	gotoxy(x - 2, y);	//34, 17
	cout << "> ��ǰ ���" << endl;
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
	gotoxy(x - 6, y + 6);	//36, 25
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
				y = 22;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	//�鸦 ������ ���
			if (y < 22) {	//y�� 17~24���̸� �̵� -> 24���� �۾ƾ���
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);	//�Ʒ������� 1ĭ �̵���
				cout << ">";
			}
			else if (y == 22) {	//�� �Ʒ� -> �� ���� �̵�
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


int Manager::managerMain() {
	init();

	while (true) {
		title();

		//�޴� ���� -> �Լ�
		int select = menu();
		//if (select == 0) productList();
		if (select == 1) addProduct();
		else if (select == 2) delProduct();
		else if (select == 3) warehousing();
		else if (select == 4) release();
		else if (select == 5) {
			gotoxy(0, 27); break;
		}
		system("cls");
	}
	return 0;
}
