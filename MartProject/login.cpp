#include "login.h"

using namespace std;

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
			//managerMain();
			continue;
		}
		else if (id == "cashier" && password == "cashier01") {
			//cashierMain();
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
