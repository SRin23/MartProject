#include "Cashier.h"

using namespace std;

//����(ǰ���� ã�Ƽ�, �� ������ŭ -)
void Cashier::addShoppingCart() {
	string productName;	//��ǰ �̸�
	int quantity;		//��ǰ ����
	int check;
	while (true) {
		system("cls");
		//totalProfit();
		check = 0;
		gotoxy(33, 2);
		cout << "<����>" << endl;
		gotoxy(10, 4);
		cout << "�� �����ϰ��� �ϴ� ǰ���� �̸�, ����, ������ �Է��ϼ��� ��" << endl;

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
				cout << "���ŵǾ����ϴ�." << endl;

				buyProduct[buyCnt++] = new Product(product[i]->getProductName(), product[i]->getPrice(), product[i]->getCustomerPrice(), product[i]->getQuantity());
				//���� �� ��ǰ�� ���� ������ ���ϱ�
				allSum += product[i]->getCustomerPrice() * quantity;
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
void Cashier::delShoppingCart() {
	string productName;	//��ǰ �̸�
	int quantity;		//��ǰ ����
	int check;
	while (true) {
		system("cls");
		//totalProfit();
		check = 0;
		gotoxy(33, 2);
		cout << "<�������>" << endl;
		gotoxy(10, 4);
		cout << "�� ���Ÿ� ����ϰ��� �ϴ� ǰ���� �̸�, ����, ������ �Է��ϼ��� ��" << endl;

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
				cout << "���ŵǾ����ϴ�." << endl;

				//���� �� ��ǰ�� ���� ������ ���ϱ�
				allSum += product[i]->getCustomerPrice() * quantity;

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
void Cashier::refund() {
	string productName;	//��ǰ �̸�
	int quantity;		//��ǰ ����
	string refundMemo;	//ȯ�һ���
	int check;
	while (true) {
		system("cls");
		//totalProfit();
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
void Cashier::cartList() {
	system("cls");
	//totalProfit();
	gotoxy(15, 3);
	cout << "���� ��� LIST";
	gotoxy(0, 4);
	cout << " --------------------------------------------------------- " << endl;
	int i = -1;
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
	cout << " | - | ��ü �հ� : " << customerTotal << "\t\t\t\t         |" << endl;
	cout << " --------------------------------------------------------- " << endl;
	//cout << "�������Խ��ϴ�." << endl;
}

//����
void Cashier::buy() {
	system("cls");
	cartList();
	cout << endl << endl << "�����Ͻðڽ��ϱ�?" << endl;
	cout << "���ŵǾ����ϴ�." << endl;
	if (keyControl() == TAB) {
		return;
	}
}

int Cashier::cashierMain() {
	init();

	while (true) {
		cashierTitle();

		//�޴� ���� -> �Լ�
		int select = cashierMenu();
		//if (select == 0) productList();
		if (select == 1) addShoppingCart();
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

//title ����ϱ�
void Cashier::title() {
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
int Cashier::menu() {
	int x = 33;
	int y = 19;

	//�޴����
	gotoxy(x - 5, y - 1);
	cout << "----------------------" << endl;
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
	cout << "----------------------" << endl << endl;

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
