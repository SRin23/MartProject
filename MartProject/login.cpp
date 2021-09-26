#include "login.h"

using namespace std;

void login() {
	init();
	int wrong = 0;
	while (true) {
		system("cls");
		if (wrong != 0) {
			gotoxy(25, 2);
			cout << wrong << "회 오류, 5회오류시 종료됩니다." << endl;
		}
		gotoxy(35, 10);
		cout << "<Log-in>";
		string id;
		string password;
		gotoxy(31, 12);
		cout << "아이디 : ";
		cin >> id;
		gotoxy(29, 13);
		cout << "비밀번호 : ";
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
			//잘못된 아이디/비밀번호 입니다.
			cout << "잘못된 아이디/비밀번호 입니다." << endl;
			gotoxy(29, 16);
			cout << "다시 시도해 주세요." << endl;
			Sleep(1000);
			wrong++;
		}

		if (wrong >= 5) {
			return;
		}
	}

	return;
}
