#include<iostream>
#include<cstdio>
#include<conio.h>	//getch사용
#include<windows.h>	//좌표사용

//방향키 및 키값 정의
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define ENTER 4	//ENTER키 : t선택
#define TAB 5	//TAB키 : Main으로 빠져나오기

using namespace std;

void init();	//초기화
void gotoxy(int x, int y);	//좌표찍기
int keyControl();	//방향키로 좌표 조절하기
void title();	//title 출력하기
int menu();	//메뉴 출력, 선택


//제품정보
class Product {
	string productName;	//제품 이름
	int price;			//제품 가격
	int quantity;		//제품 수량

public:
	Product() {
		productName = "";
		price = 0;
		quantity = 0;
	}
	Product(string productName, int price, int quantity) :productName(productName), price(price), quantity(quantity) {};
	~Product() {}
	void print() {
		cout << "제품이름 : " << productName << endl;
		cout << "제품가격 : " << price << endl;
		cout << "제품수량 : " << quantity << endl;
		cout << "합계 : " << price * quantity << endl;
	}

	string getProductName() { return this->productName; }
	int getPrice() { return this->price; }
	int getQuantity() { return this->quantity; }
};

//전역멤버변수
int allSum = 0;
Product* product[10];


//누적 수익 -> 소비자들의 구매로 인한 수익 -> 항상 맨위에?
void totalProfit() {
	system("cls");
	gotoxy(0, 0);
	cout << "현재까지 누적된 수익 : " << allSum << endl;

	while (true) {
		if (keyControl() == TAB) {
			break;
		}
	}
}

//제품목록 띄우기 -> 메뉴로 나가는거 안됨
void productList() {
	system("cls");
	gotoxy(15, 1);
	cout << "제품 목록 LIST";
	gotoxy(0, 2);
	cout << " -----------------------------------------" << endl;
	while (true) {
		for (int i = 0; i < 5; i++) {
			cout << " | " << i + 1 << " | 제품명 : " << product[i]->getProductName() << "\t | 수량 : " << product[i]->getQuantity() << "\t |" << endl;
			cout << " -----------------------------------------" << endl;
		}
		if (keyControl() == TAB) {
			break;
		}
	}
}

//구매(품목을 찾아서, 산 수량만큼 -)
void buy() {
	system("cls");
	totalProfit();
	gotoxy(33, 2);
	cout << "<구매>" << endl;
	gotoxy(10, 4);
	cout << "※ 구매하고자 하는 품목의 이름, 가격, 수량을 입력하세요 ※" << endl;

	string productName;	//제품 이름
	int price;			//제품 가격
	int quantity;		//제품 수량

	gotoxy(32, 7);
	cout << "제품 이름 : ";
	cin >> productName;
	gotoxy(32, 8);
	cout << "제품 가격 : ";
	cin >> price;
	gotoxy(32, 9);
	cout << "제품 수량 : ";
	cin >> quantity;

	gotoxy(31, 12);
	cout << "<구매되었습니다>" << endl;

	//고객이 산 제품에 대해 누적합 구하기
	allSum += price * quantity;

	//product[i].print();
	while (true) {
		if (keyControl() == TAB) {
			break;
		}
	}
}

//환불(품목을 찾아서, 환불할 수량만큼 +)
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

int main() {
	init();

	while (true) {
		title();

		//메뉴 선택 -> 함수
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

//초기화
void init() {
	//콘솔 크기 정하기
	system("mode con cols=80 lines=30");

	//깜빡거리는 커서 숨기기
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

//좌표찍기
void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x, y };
	SetConsoleCursorPosition(consoleHandle, pos);
}

//방향키로 좌표 조절하기
int keyControl() {
	char tmp = _getch();
	if (tmp == -32) {
		tmp = _getch();
		switch (tmp) {
		case 72:	//위
			return UP; break;
		case 80:	//아래
			return DOWN; break;
		case 75:	//왼쪽
			return LEFT; break;
		case 77:	//오른쪽
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

//title 출력하기
void title() {
	gotoxy(10, 2); cout << "------------------------------------------------------------" << endl;
	gotoxy(16, 5); cout << "##       ##        #        #######     ########" << endl;
	gotoxy(16, 6); cout << "####   ####      ## ##      ##    ##       ##" << endl;
	gotoxy(16, 7); cout << "##  ###  ##     ##   ##     #######        ##" << endl;
	gotoxy(16, 8); cout << "##   #   ##    #########    ##    ##       ##" << endl;
	gotoxy(16, 9); cout << "##       ##   ##       ##   ##     ##      ##" << endl;
	gotoxy(16, 10); cout << "##       ##   ##       ##   ##     ##      ##" << endl << endl;
	gotoxy(10, 13); cout << "------------------------------------------------------------" << endl;
}

//메뉴설정
int menu() {
	int x = 36;
	int y = 19;

	//메뉴출력
	gotoxy(x - 6, y - 1); 
	cout << "---------------------" << endl;
	gotoxy(x - 2, y);	
	cout << "> 제품 목록" << endl;
	gotoxy(x, y + 1);	
	cout << " 구   매" << endl;
	gotoxy(x, y + 2);	
	cout << " 환   불" << endl;
	gotoxy(x, y + 3);	
	cout << " 종   료" << endl;
	gotoxy(x - 6, y + 4);	
	cout << "---------------------" << endl << endl;

	//메뉴선택
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
