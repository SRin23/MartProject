/*
 - DB���� -> ��ǰ���� ����(�� �� �ִٸ� ����Ⱓ �������� ����)
 - product�� ���Ḯ��Ʈ�� ����
 - ǰ�� ���� ����
*/

#include<iostream>
#include<cstdio>
#include<conio.h>	//getch���
#include<windows.h>	//��ǥ���
#include <string.h>


//����Ű �� Ű�� ����
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define ENTER 4	//ENTERŰ : t����
#define TAB 5	//TABŰ : Main���� ����������ma
#define ESC 6	//���α׷� ����

using namespace std;

void init();	//�ʱ�ȭ
void gotoxy(int x, int y);	//��ǥ���
int keyControl();	//����Ű�� ��ǥ �����ϱ�
void cashierTitle();	//title ����ϱ�
int cashierMenu();	//�޴� ���, ����
void managerTitle();	//title ����ϱ�
int managerMenu();	//�޴� ���, ����

//��ǰ����
class Product {
	string productName;	//��ǰ �̸�
	int price;			//��ǰ ����
	int customerPrice;	//�Һ��ڰ���
	int quantity;		//��ǰ ����

public:
	Product() {
		productName = "";
		price = 0;
		customerPrice = 0;
		quantity = 0;
	}
	Product(string productName, int price, int customerPrice, int quantity) :productName(productName), price(price), customerPrice(customerPrice), quantity(quantity) {};
	~Product() {}
	void print() {
		cout << "��ǰ�̸� : " << productName << endl;
		cout << "��ǰ���� : " << price << endl;
		cout << "�Һ��ڰ��� : " << customerPrice << endl;
		cout << "��ǰ���� : " << quantity << endl;
		cout << "�հ� : " << price * quantity << endl;
	}

	//getter
	string getProductName() { return this->productName; }
	int getPrice() { return this->price; }
	int getCustomerPrice() { return this->customerPrice; }
	int getQuantity() { return this->quantity; }

	//���� +/-
	void addQuantity(int quantity) { this->quantity += quantity; }
	void disQuantity(int quantity) { this->quantity -= quantity; }

};

//�����������
int allSum = 0;
Product* product[10];
int cnt = -1;


//��ǰ��� ���� -> �޴��� �����°� �ȵ�
void productList() {
	system("cls");
	gotoxy(15, 3);
	cout << "��ǰ ��� LIST";
	gotoxy(0, 4);
	cout << " -----------------------------------------" << endl;
	int i = -1;
	if (cnt < 0) {
		gotoxy(10, 5);
		cout << "��ǰ�� ��� �����ϴ�." << endl;
	}
	else {
		while (i < cnt) {	//i<��ǰ����
			i++;
			if (product[i] != nullptr) {
				cout << " | " << i + 1 << " | ��ǰ�� : " << product[i]->getProductName() << "\t | ���� : " << product[i]->getQuantity() << "\t |" << endl;
				cout << " -----------------------------------------" << endl;
			}
			else {
				continue;
			}
		}
	}
	
	//cout << "�������Խ��ϴ�." << endl;
	if (keyControl() == TAB) {
		return;
	}
}

//Manager
//ǰ���߰�(���� ���� ��ǰ) -> ��Ʈ -> �밭 OK
//����, �ִ� ��ǰ�̶�� �����ϴ� ǰ���Դϴ�.
void addProduct() {
	string productName;	//��ǰ �̸�
	int price;			//��ǰ ����
	int customerPrice;
	int quantity;		//��ǰ ����

	while (true) {
		system("cls");
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
		

		/*for (int i = 0; i < cnt; i++) {
			if (productName == product[i]->getProductName()) {
				cout << "���� ǰ���� �����մϴ�. �԰�â���� �Ѿ �ּ���.";
			}
			else {
				cnt++;
				product[cnt] = new Product(productName, price, customerPrice, quantity);
				gotoxy(31, 12);
				cout << "<�߰��Ǿ����ϴ�>" << endl;

			}
		}*/
		cnt++;
		product[cnt] = new Product(productName, price, customerPrice, quantity);
		gotoxy(31, 12);
		cout << "<�߰��Ǿ����ϴ�>" << endl;

		
		if (keyControl() == TAB) {
			return;
		}
	}
}

//ǰ�����(���� ���� ��ǰ) -> �迭 �� ���� ����
void delProduct() {
	string productName;	//��ǰ �̸�
	while (true) {
		system("cls");
		gotoxy(33, 2);
		cout << "<ǰ�� ����>" << endl;
		gotoxy(16, 4);
		cout << "�� �����ϰ��� �ϴ� ǰ���� �̸��� �Է��ϼ��� ��" << endl;

		gotoxy(27, 7);
		cout << "��ǰ �̸� : ";
		cin >> productName;

		int check = 0;
		for (int i = 0; i < 5; i++) {
			if ((product[i]->getProductName()) == productName) {
				delete product[i];
				gotoxy(31, 12);
				cout << "<�����Ǿ����ϴ�>" << endl;
				check = 1;
				cnt--;
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
void warehousing() {
	string productName;	//��ǰ �̸�
	int quantity;		//��ǰ ����
	int check;

	while (true) {
		system("cls");
		check = 0;
		gotoxy(33, 2);
		cout << "<�԰�>" << endl;
		gotoxy(16, 4);
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
			cout<<"�������� �ʴ� ��ǰ�Դϴ�."<<endl;
			gotoxy(23, 13);
			cout << "ǰ���� �߰��� �ּ���." << endl;
		}
		if (keyControl() == TAB) {
			return;
		}
	}
}

//���(���� �ִ� ��ǰ�� ���� -)
void release() {
	string productName;	//��ǰ �̸�
	int quantity;		//��ǰ ����
	int check;

	while (true) {
		system("cls");
		check = 0;
		gotoxy(33, 2);
		cout << "<���>" << endl;
		gotoxy(16, 4);
		cout << "�� ����ϰ��� �ϴ� ǰ���� �̸�, ������ �Է��ϼ��� ��" << endl;

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

int managerMain() {
	init();

	while (true) {
		managerTitle();

		//�޴� ���� -> �Լ�
		int select = managerMenu();
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

//Cashier
Product *buyProduct[10];
int buyCnt = 0;
int customerTotal = 0;

//���� ���� -> �Һ��ڵ��� ���ŷ� ���� ���� -> �׻� ������?
void totalProfit() {
	gotoxy(0, 0);
	cout << "�������� : " << customerTotal << endl;
}

//����(ǰ���� ã�Ƽ�, �� ������ŭ -)
void addShoppingCart() {
	string productName;	//��ǰ �̸�
	int quantity;		//��ǰ ����
	int check;
	while (true) {
		system("cls");
		totalProfit();
		check = 0;
		gotoxy(33, 2);
		cout << "<��ٱ��� ���>" << endl;
		gotoxy(10, 4);
		cout << "�� ��ٱ��Ͽ� ����� �ϴ� ǰ���� �̸�, ����, ������ �Է��ϼ��� ��" << endl;

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
				cout << "��ٱ��Ͽ� �߰� �Ǿ����ϴ�." << endl;

				buyProduct[buyCnt++] = new Product(product[i]->getProductName(), product[i]->getPrice(), product[i]->getCustomerPrice(), product[i]->getQuantity());
				customerTotal += buyProduct[i]->getCustomerPrice() * quantity;
				
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

		//product[i].print();
		if (keyControl() == TAB) {
			return;
		}
	}
}

//��ٱ��Ͽ� �ִ� ��ǰ ���� ���
void delShoppingCart() {
	string productName;	//��ǰ �̸�
	int quantity;		//��ǰ ����
	int check;
	while (true) {
		system("cls");
		totalProfit();
		check = 0;
		gotoxy(33, 2);
		cout << "<��ٱ��� ����>" << endl;
		gotoxy(10, 4);
		cout << "�� ��ٱ��Ͽ��� �����ϰ��� �ϴ� ǰ���� �̸�, ����, ������ �Է��ϼ��� ��" << endl;

		gotoxy(32, 7);
		cout << "��ǰ �̸� : ";
		cin >> productName;
		gotoxy(32, 8);
		cout << "��ǰ ���� : ";
		cin >> quantity;

		//product�迭�� ��ǰ�� �ִ��� Ȯ��
		for (int i = 0; i < buyCnt; i++) {
			if (buyProduct[i]->getProductName() == productName) {
				buyProduct[i]->disQuantity(quantity);
				gotoxy(31, 12);
				cout << "��ٱ��Ͽ��� ���� �Ǿ����ϴ�." << endl;

				delete buyProduct[i];
				buyCnt--;

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

		//product[i].print();
		if (keyControl() == TAB) {
			return;
		}
	}
}

//ȯ��(ǰ���� ã�Ƽ�, ȯ���� ������ŭ +)
void refund() {
	string productName;	//��ǰ �̸�
	int quantity;		//��ǰ ����
	string refundMemo;	//ȯ�һ���
	int check;
	while (true) {
		system("cls");
		totalProfit();
		check = 0;
		gotoxy(33, 2);
		cout << "<ȯ��>" << endl;
		gotoxy(10, 4);
		cout << "�� ȯ���ϰ��� �ϴ� ǰ���� �̸�, ����, ������ �Է��ϼ��� ��" << endl;

		gotoxy(32, 7);
		cout << "��ǰ �̸� : ";
		cin >> productName;
		gotoxy(32, 8);
		cout << "��ǰ ���� : ";
		cin >> quantity;
		gotoxy(32, 9);
		cout << "ȯ�� ���� : ";
		cin >> refundMemo;

		//product�迭�� ��ǰ�� �ִ��� Ȯ��
		for (int i = 0; i < cnt; i++) {
			if (product[i]->getProductName() == productName) {
				product[i]->addQuantity(quantity);
				gotoxy(31, 12);
				cout << "ȯ�ҵǾ����ϴ�." << endl;

				//���� �� ��ǰ�� ���� ������ ���ϱ�
				allSum -= product[i]->getCustomerPrice() * quantity;

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

		//product[i].print();
		if (keyControl() == TAB) {
			return;
		}
	}
}

//���� ����Ʈ
void cartList() {
	system("cls");
	totalProfit();
	gotoxy(15, 3);
	cout << "���� ��� LIST";
	gotoxy(0, 4);
	cout << " --------------------------------------------------------- " << endl;
	int i = -1;
	if (buyCnt < 0) {
		gotoxy(10, 5);
		cout << "��ٱ��Ͽ� �ƹ��͵� �����ϴ�." << endl;
	}
	while (i < buyCnt) {	//i<��ǰ����
		i++;
		if (buyProduct[i] != nullptr) {
			cout << " | " << i + 1 << " | ��ǰ�� : " << buyProduct[i]->getProductName() << "\t | ���� : " << buyProduct[i]->getQuantity() << "\t | ���� : " << buyProduct[i]->getCustomerPrice() << "\t |" << endl;
			cout << " --------------------------------------------------------- " << endl;
		}
		else {
			continue;
		}

	}
	cout << " | ��ü �հ� : " << customerTotal <<"\t\t\t         |" << endl;
	cout << " --------------------------------------------------------- " << endl;
	//cout << "�������Խ��ϴ�." << endl;
}

//����
void buy() {
	system("cls");
	cartList();
	cout << endl << endl << "�����Ͻðڽ��ϱ�?" << endl;
	
	/*char* choice = 0;
	//�޴����
	char* choice = 0;
	cout << "YES or NO : ";
	cin >> choice;
	for (int i = 0; i < strlen(choice); i++) {
		choice[i] = tolower(choice[i]);
	}
	if (choice == "yes") {
		cout << "���ŵǾ����ϴ�." << endl;
		for (int i = 0; i < buyCnt; i++) {
			allSum += buyProduct[i]->getCustomerPrice() * buyProduct[i]->getQuantity();
		}
	}
	else if (choice == "no") {
		cout << "���Ű� ��ҵǾ����ϵ�." << endl;
	}
	else {
		cout << "���� ���� ������ ���Դϴ�." << endl;
	}
	*/
	cout << "���ŵǾ����ϴ�." << endl;
	if (keyControl() == TAB) {
		return;
	}
}

int cashierMain() {
	init();

	while (true) {
		cashierTitle();

		//�޴� ���� -> �Լ�
		int select = cashierMenu();
		if (select == 0) productList();
		else if (select == 1) addShoppingCart();
		else if (select == 2) delShoppingCart();
		else if (select == 3) buy();
		else if (select == 4) refund();
		else if (select == 5) {
			gotoxy(0, 27); break;
		}
		system("cls");
	}
	return 0;
}


void login() {
	init();
	int wrong = 0;
	while (true) {
		system("cls");
		if (wrong != 0) {
			gotoxy(25, 2);
			cout << wrong << "ȸ ����, 5ȸ������ ����˴ϴ�." << endl;
		}
		gotoxy(35, 10);
		cout << "<Log-in>";
		string id;
		string password;
		gotoxy(31, 12);
		cout << "���̵� : ";
		cin >> id;
		gotoxy(29, 13);
		cout << "��й�ȣ : ";
		cin >> password;

		if (id == "manager" && password == "manager01") {
			managerMain();
			continue;
		}
		else if (id == "cashier" && password == "cashier01") {
			cashierMain();
			continue;
		}
		else {
			gotoxy(25, 15);
			//�߸��� ���̵�/��й�ȣ �Դϴ�.
			cout << "�߸��� ���̵�/��й�ȣ �Դϴ�." << endl;
			gotoxy(29, 16);
			cout << "�ٽ� �õ��� �ּ���." << endl;
			Sleep(1000);
			wrong++;
		}
		
		if (wrong >= 5) {
			return;
		}
	}

	return;
}

int main() {
	init();
	login();
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
	if (tmp == 27) {
		return ESC;
	}
}
//title ����ϱ�
void cashierTitle() {
	gotoxy(10, 2); cout << "------------------------------------------------------------";
	gotoxy(16, 5); cout << "##       ##        #        #######     ########";
	gotoxy(16, 6); cout << "####   ####      ## ##      ##    ##       ##";
	gotoxy(16, 7); cout << "##  ###  ##     ##   ##     #######        ##";
	gotoxy(16, 8); cout << "##   #   ##    #########    ##    ##       ##";
	gotoxy(16, 9); cout << "##       ##   ##       ##   ##     ##      ##";
	gotoxy(16, 10); cout << "##       ##   ##       ##   ##     ##      ##";
	gotoxy(55, 12); cout << "_for cashier";
	gotoxy(10, 14); cout << "------------------------------------------------------------" << endl;
}

//�޴�����
int cashierMenu() {
	int x = 33;
	int y = 19;

	//�޴����
	gotoxy(x - 5, y - 1);
	cout << "-------------------------" << endl;
	gotoxy(x - 2, y);
	cout << ">    ��ǰ ���" << endl;
	gotoxy(x, y + 1);
	cout << " ��ٱ��� �߰�" << endl;
	gotoxy(x, y + 2);
	cout << " ��ٱ��� ����" << endl;
	gotoxy(x, y + 3);
	cout << "   ��     ��" << endl;
	gotoxy(x, y + 4);
	cout << "   ȯ     ��" << endl;
	gotoxy(x, y + 5);
	cout << "   ��     ��" << endl;
	gotoxy(x - 5, y + 6);
	cout << "-------------------------" << endl << endl;

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
				y = 24;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:
			if (y < 24) {
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);
				cout << ">";
			}
			else if (y == 24) {
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
