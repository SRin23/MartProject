/*
 - DB���� -> ��ǰ���� ����(�� �� �ִٸ� ����Ⱓ �������� ����)
 - product�� ���Ḯ��Ʈ�� ����
 - loginȭ��(manager, cashier)
 - cashierȭ�� ����
 - ǰ�� ���� ����
*/

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
class Product {
	string productName;	//��ǰ �̸�
	int price;			//��ǰ ����
	int quantity;		//��ǰ ����

public:
	Product() {
		productName = "";
		price = 0;
		quantity = 0;
	}
	Product(string productName, int price, int quantity) :productName(productName), price(price), quantity(quantity) {};
	~Product() {}
	void print() {
		cout << "��ǰ�̸� : " << productName << endl;
		cout << "��ǰ���� : " << price << endl;
		cout << "��ǰ���� : " << quantity << endl;
		cout << "�հ� : " << price * quantity << endl;
	}

	//getter
	string getProductName() { return this->productName; }
	int getPrice() { return this->price; }
	int getQuantity() { return this->quantity; }
};

//�����������
int allSum = 0;
Product* product[10];
int cnt = 0;

//���� ���� -> �Һ��ڵ��� ���ŷ� ���� ���� -> �׻� ������?
void totalProfit() {
	system("cls");
	gotoxy(0, 0);
	cout << "������� ������ ���� : " << allSum << endl;

	while (true) {
		if (keyControl() == TAB) {
			break;
		}
	}
}
//��ǰ��� ���� -> �޴��� �����°� �ȵ�
void productList() {
	system("cls");
	gotoxy(15, 1);
	cout << "��ǰ ��� LIST";
	gotoxy(0, 2);
	cout << " -----------------------------------------" << endl;
	int i = 0;
	while (i < cnt) {	//i<��ǰ����
		cout << " | " << i + 1 << " | ��ǰ�� : " << product[i]->getProductName() << "\t | ���� : " << product[i]->getQuantity() << "\t |" << endl;
		cout << " -----------------------------------------" << endl;
		i++;
	}
	//cout << "�������Խ��ϴ�." << endl;
	while (true) {
		if (keyControl() == TAB) {
			break;
		}
	}
}

//ǰ���߰�(���� ���� ��ǰ) -> ��Ʈ -> �밭 OK
void addProduct() {
	string productName;	//��ǰ �̸�
	int price;			//��ǰ ����
	int quantity;		//��ǰ ����

	while (true) {
		system("cls");
		gotoxy(33, 2);
		cout << "<ǰ�� �߰�>" << endl;
		gotoxy(10, 4);
		cout << "�� �߰��ϰ��� �ϴ� ǰ���� �̸�, ����, ������ �Է��ϼ��� ��" << endl;

		gotoxy(32, 7);
		cout << "��ǰ �̸� : ";
		cin >> productName;
		gotoxy(32, 8);
		cout << "��ǰ ���� : ";
		cin >> price;
		gotoxy(32, 9);
		cout << "��ǰ ���� : ";
		cin >> quantity;

		product[cnt++] = new Product(productName, price, quantity);

		gotoxy(31, 12);
		cout << "<�߰��Ǿ����ϴ�>" << endl;

		if (keyControl() == TAB) {
			break;
		}
	}
}

//ǰ�����(���� ���� ��ǰ)
void delProduct() {
	string productName;	//��ǰ �̸�
	while (true) {
		system("cls");
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
			break;
		}
	}
}

//�԰�(���� �ִ� ��ǰ�� ���� +)
void warehousing() {
	system("cls");
	cout << "�԰�˴ϴ�.";

	//product�迭�� ��ǰ�� �ִ��� Ȯ��
	//������ ����+
	//������ ���� ��ǰ�Դϴ�. ����

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

	//product�迭�� ��ǰ�� �ִ��� Ȯ��
	//������ ���� -
	//������ ���� ��ǰ�Դϴ�. ����
	//��� �Ǵ� ���� : �������?, 


	while (true) {
		if (keyControl() == TAB) {
			break;
		}
	}
}

int Managermain() {
	init();

	while (true) {
		title();

		//�޴� ���� -> �Լ�
		int select = menu();
		if (select == 0) productList();
		else if (select == 1) addProduct();
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

//����(ǰ���� ã�Ƽ�, �� ������ŭ -)
void buy() {
	system("cls");
	totalProfit();
	gotoxy(33, 2);
	cout << "<����>" << endl;
	gotoxy(10, 4);
	cout << "�� �����ϰ��� �ϴ� ǰ���� �̸�, ����, ������ �Է��ϼ��� ��" << endl;

	string productName;	//��ǰ �̸�
	int price;			//��ǰ ����
	int quantity;		//��ǰ ����

	gotoxy(32, 7);
	cout << "��ǰ �̸� : ";
	cin >> productName;
	gotoxy(32, 8);
	cout << "��ǰ ���� : ";
	cin >> price;
	gotoxy(32, 9);
	cout << "��ǰ ���� : ";
	cin >> quantity;

	gotoxy(31, 12);
	cout << "<���ŵǾ����ϴ�>" << endl;

	//���� �� ��ǰ�� ���� ������ ���ϱ�
	allSum += price * quantity;

	//product[i].print();
	while (true) {
		if (keyControl() == TAB) {
			break;
		}
	}
}

//ȯ��(ǰ���� ã�Ƽ�, ȯ���� ������ŭ +)
void refund() {
	system("cls");
	totalProfit();
	//product[i].print();
	while (true) {
		if (keyControl() == TAB) {
			break;
		}
	}
}

int Cashiermain() {
	init();

	while (true) {
		title();

		//�޴� ���� -> �Լ�
		int select = menu();
		if (select == 0) productList();
		else if (select == 1) buy();
		else if (select == 2) refund();
		else if (select == 3) {
			gotoxy(0, 27); break;
		}
		system("cls");
	}
	return 0;
}


int login() {
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
void cashierRitle() {
	gotoxy(10, 2); cout << "------------------------------------------------------------" << endl;
	gotoxy(16, 5); cout << "##       ##        #        #######     ########" << endl;
	gotoxy(16, 6); cout << "####   ####      ## ##      ##    ##       ##" << endl;
	gotoxy(16, 7); cout << "##  ###  ##     ##   ##     #######        ##" << endl;
	gotoxy(16, 8); cout << "##   #   ##    #########    ##    ##       ##" << endl;
	gotoxy(16, 9); cout << "##       ##   ##       ##   ##     ##      ##" << endl;
	gotoxy(16, 10); cout << "##       ##   ##       ##   ##     ##      ##" << endl << endl;
	gotoxy(10, 13); cout << "------------------------------------------------------------" << endl;
}

//�޴�����
int cashiermenu() {
	int x = 36;
	int y = 19;

	//�޴����
	gotoxy(x - 6, y - 1);
	cout << "---------------------" << endl;
	gotoxy(x - 2, y);
	cout << "> ��ǰ ���" << endl;
	gotoxy(x, y + 1);
	cout << " ��   ��" << endl;
	gotoxy(x, y + 2);
	cout << " ȯ   ��" << endl;
	gotoxy(x, y + 3);
	cout << " ��   ��" << endl;
	gotoxy(x - 6, y + 4);
	cout << "---------------------" << endl << endl;

	//�޴�����
	while (true) {
		int n = keyControl();
		switch (n) {
		case UP:
			if (y > 19) {
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, --y);
				cout << ">";
			}
			else if (y == 19) {
				gotoxy(x - 2, y);
				cout << " ";
				y = 22;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:
			if (y < 22) {
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);
				cout << ">";
			}
			else if (y == 22) {
				gotoxy(x - 2, y);
				cout << " ";
				y = 19;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case ENTER:
			return y - 19;
		}
	}
}

//title ����ϱ�
void managerTitle() {
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
int managerMenu() {
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
