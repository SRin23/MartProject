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

public : 
	Product() {
		productName = "";
		price = 0;
		quantity = 0;
	}
	Product(string productName, int price, int quantity) :productName(productName), price(price), quantity(quantity) {};
	~Product(){}
	void print() {
		cout << "제품이름 : " << productName << endl;
		cout << "제품가격 : " << price << endl;
		cout << "제품수량 : " << quantity<< endl;
		cout << "합계 : " << price* quantity << endl;
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

//품목추가(원래 없는 제품) -> 마트 -> 대강 OK
void addProduct() {
	static int cnt = 0;
	string productName;	//제품 이름
	int price;			//제품 가격
	int quantity;		//제품 수량

	while (true) {
		system("cls");
		gotoxy(33, 2);
		cout << "<품목 추가>" << endl;
		gotoxy(10, 4);
		cout << "※ 추가하고자 하는 품목의 이름, 가격, 수량을 입력하세요 ※" << endl;

		gotoxy(32, 7);
		cout << "제품 이름 : ";
		cin >> productName;
		gotoxy(32, 8);
		cout << "제품 가격 : ";
		cin >> price;
		gotoxy(32, 9);
		cout << "제품 수량 : ";
		cin >> quantity;

		product[cnt++] = new Product(productName, price, quantity);

		gotoxy(31, 12);
		cout << "<추가되었습니다>" << endl;

		if (keyControl() == TAB) {
			break;
		}
	}
}

//품목삭제(원래 없는 제품)
void delProduct() {
	string productName;	//제품 이름
	while (true) {
		system("cls");
		gotoxy(33, 2);
		cout << "<품목 삭제>" << endl;
		gotoxy(16, 4);
		cout << "※ 삭제하고자 하는 품목의 이름을 입력하세요 ※" << endl;

		gotoxy(32, 7);
		cout << "제품 이름 : ";
		cin >> productName;

		int check = 0;
		for (int i = 0; i < 5; i++) {
			if ((product[i]->getProductName()) == productName) {
				delete product[i];
				gotoxy(31, 12);
				cout << "<삭제되었습니다>" << endl;
				check = 1;
				break;
			}
		}

		if (check != 1) {
			cout << "품목이 추가되지 않아 삭제할 수 없습니다." << endl;
		}

		if (keyControl() == TAB) {
			break;
		}
	}
}

//입고(원래 있는 제품에 수량 +)
void warehousing() {
	system("cls");
	cout << "입고됩니다.";

	//product배열에 물품이 있는지 확인
	//있으면 수량+
	//없으면 없는 물품입니다. 띄우기

	while (true) {
		if (keyControl() == TAB) {
			break;
		}
	}
}

//출고(원래 있는 제품에 수량 -)
void release() {
	system("cls");
	cout << "출고됩니다.";

	//product배열에 물품이 있는지 확인
	//있으면 수량 -
	//없으면 없는 물품입니다. 띄우기
	//출고가 되는 조건 : 유통기한?, 


	while (true) {
		if (keyControl() == TAB) {
			break;
		}
	}
}

//구매(품목을 찾아서, 산 수량만큼 -)
void buy() {
	system("cls");
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
	/*
	if (GetAsyncKeyState(VK_UP) & 0x0001) {	//위쪽
		return UP;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x0001) {	//아래쪽
		return DOWN;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x0001) {	//왼쪽
		return LEFT;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x0001) {	//오른쪽
		return RIGHT;
	}
	if (GetAsyncKeyState(VK_RETURN) & 0x0001) {	//엔터키
		return ENTER;
	}
	*/
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
	gotoxy(10, 2);cout << "------------------------------------------------------------" << endl;
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
	int y = 17;

	//메뉴출력
	gotoxy(x - 6, y - 1); //30, 16
	cout << "---------------------" << endl;
	gotoxy(x - 2, y);	//34, 17
	cout << "> 제품 목록" << endl;
	gotoxy(x, y + 1);	//36, 18
	cout << "품목 추가" << endl;
	gotoxy(x, y + 2);	//36, 19
	cout << "품목 삭제" << endl;
	gotoxy(x, y + 3);	//36, 20
	cout << " 입   고  " << endl;
	gotoxy(x, y + 4);	//36, 21
	cout << " 출   고" << endl;
	gotoxy(x, y + 5);	//36, 22
	cout << " 구   매" << endl;
	gotoxy(x, y + 6);	//36, 23
	cout << " 환   불" << endl;
	gotoxy(x, y + 7);	//36, 24
	cout << " 종   료" << endl;
	gotoxy(x - 6, y + 8);	//36, 25
	cout << "---------------------" << endl << endl;

	//메뉴선택
	while (true) {	//무한 반복
		int n = keyControl();
		switch (n) {
		case UP:	//↑를 눌렸을 경우
			if (y > 17) {	//y는 17~24사이만 이동 -> 17보다 커야함
				gotoxy(x - 2, y);	//게임 시작에 있던 >
				cout << " ";	//지우고
				gotoxy(x - 2, --y);	//위쪽으로 1칸 이동후
				cout << ">";	//다시 그리기
			}
			else if (y == 17) {	//맨 위 -> 맨 아래로 이동
				gotoxy(x - 2, y);
				cout << " ";
				y = 24;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	//↓를 눌렸을 경우
			if (y < 24) {	//y는 17~24사이만 이동 -> 24보다 작아야함
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);	//아래쪽으로 1칸 이동후
				cout << ">";
			}
			else if (y == 24) {	//맨 아래 -> 맨 위로 이동
				gotoxy(x - 2, y);
				cout << " ";
				y = 17;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case ENTER:	//엔터 -> 선택했을 경우
			return y - 17;	//y-17를 하여 각 값에 대한 1, 2, 3...값을 받을 수 있다. -> 값 선택
		}
	}
}
