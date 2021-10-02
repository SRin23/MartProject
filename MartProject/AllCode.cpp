/*
 - DB연동 -> 제품정보 저장(할 수 있다면 유통기간 정보까지 전달)
 - product를 연결리스트로 구현
 - 품목 삭제 구현
*/

#include<iostream>
#include<cstdio>
#include<conio.h>	//getch사용
#include<windows.h>	//좌표사용
#include <string.h>


//방향키 및 키값 정의
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define ENTER 4	//ENTER키 : t선택
#define TAB 5	//TAB키 : Main으로 빠져나오기ma
#define ESC 6	//프로그램 종료

using namespace std;

void init();	//초기화
void gotoxy(int x, int y);	//좌표찍기
int keyControl();	//방향키로 좌표 조절하기
void cashierTitle();	//title 출력하기
int cashierMenu();	//메뉴 출력, 선택
void managerTitle();	//title 출력하기
int managerMenu();	//메뉴 출력, 선택

//제품정보
class Product {
	string productName;	//제품 이름
	int price;			//제품 가격
	int customerPrice;	//소비자가격
	int quantity;		//제품 수량

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
		cout << "제품이름 : " << productName << endl;
		cout << "제품가격 : " << price << endl;
		cout << "소비자가격 : " << customerPrice << endl;
		cout << "제품수량 : " << quantity << endl;
		cout << "합계 : " << price * quantity << endl;
	}

	//getter
	string getProductName() { return this->productName; }
	int getPrice() { return this->price; }
	int getCustomerPrice() { return this->customerPrice; }
	int getQuantity() { return this->quantity; }

	//수량 +/-
	void addQuantity(int quantity) { this->quantity += quantity; }
	void disQuantity(int quantity) { this->quantity -= quantity; }

};

//전역멤버변수
int allSum = 0;
Product* product[10];
int cnt = -1;


//제품목록 띄우기 -> 메뉴로 나가는거 안됨
void productList() {
	system("cls");
	gotoxy(15, 3);
	cout << "제품 목록 LIST";
	gotoxy(0, 4);
	cout << " -----------------------------------------" << endl;
	int i = -1;
	if (cnt < 0) {
		gotoxy(10, 5);
		cout << "제품의 재고가 없습니다." << endl;
	}
	else {
		while (i < cnt) {	//i<제품개수
			i++;
			if (product[i] != nullptr) {
				cout << " | " << i + 1 << " | 제품명 : " << product[i]->getProductName() << "\t | 수량 : " << product[i]->getQuantity() << "\t |" << endl;
				cout << " -----------------------------------------" << endl;
			}
			else {
				continue;
			}
		}
	}
	
	//cout << "빠져나왔습니다." << endl;
	if (keyControl() == TAB) {
		return;
	}
}

//Manager
//품목추가(원래 없는 제품) -> 마트 -> 대강 OK
//만약, 있는 제품이라면 존재하는 품목입니다.
void addProduct() {
	string productName;	//제품 이름
	int price;			//제품 가격
	int customerPrice;
	int quantity;		//제품 수량

	while (true) {
		system("cls");
		gotoxy(33, 2);
		cout << "<품목 추가>" << endl;
		gotoxy(10, 4);
		cout << "※ 추가하고자 하는 품목의 이름, 가격, 수량을 입력하세요 ※" << endl;

		gotoxy(30, 7);
		cout << "제품 이름 : ";
		cin >> productName;
		gotoxy(30, 8);
		cout << "제품 가격 : ";
		cin >> price;
		gotoxy(28, 9);
		cout << "소비자 가격 : ";
		cin >> customerPrice;
		gotoxy(30, 10);
		cout << "제품 수량 : ";
		cin >> quantity;
		

		/*for (int i = 0; i < cnt; i++) {
			if (productName == product[i]->getProductName()) {
				cout << "같은 품목이 존재합니다. 입고창으로 넘어가 주세요.";
			}
			else {
				cnt++;
				product[cnt] = new Product(productName, price, customerPrice, quantity);
				gotoxy(31, 12);
				cout << "<추가되었습니다>" << endl;

			}
		}*/
		cnt++;
		product[cnt] = new Product(productName, price, customerPrice, quantity);
		gotoxy(31, 12);
		cout << "<추가되었습니다>" << endl;

		
		if (keyControl() == TAB) {
			return;
		}
	}
}

//품목삭제(원래 없는 제품) -> 배열 내 삭제 구현
void delProduct() {
	string productName;	//제품 이름
	while (true) {
		system("cls");
		gotoxy(33, 2);
		cout << "<품목 삭제>" << endl;
		gotoxy(16, 4);
		cout << "※ 삭제하고자 하는 품목의 이름을 입력하세요 ※" << endl;

		gotoxy(27, 7);
		cout << "제품 이름 : ";
		cin >> productName;

		int check = 0;
		for (int i = 0; i < 5; i++) {
			if ((product[i]->getProductName()) == productName) {
				delete product[i];
				gotoxy(31, 12);
				cout << "<삭제되었습니다>" << endl;
				check = 1;
				cnt--;
				break;
			}
		}

		if (check != 1) {
			cout << "품목이 추가되지 않아 삭제할 수 없습니다." << endl;
		}

		if (keyControl() == TAB) {
			return;
		}
	}
}

//입고(원래 있는 제품에 수량 +)
void warehousing() {
	string productName;	//제품 이름
	int quantity;		//제품 수량
	int check;

	while (true) {
		system("cls");
		check = 0;
		gotoxy(33, 2);
		cout << "<입고>" << endl;
		gotoxy(16, 4);
		cout << "※ 입고하고자 하는 품목의 이름, 수량을 입력하세요 ※" << endl;

		gotoxy(32, 7);
		cout << "제품 이름 : ";
		cin >> productName;
		gotoxy(32, 8);
		cout << "제품 수량 : ";
		cin >> quantity;

		//product배열에 물품이 있는지 확인
		for (int i = 0; i < cnt; i++) {
			if (product[i]->getProductName() == productName) {
				product[i]->addQuantity(quantity);
				gotoxy(31, 12);
				cout << "입고되었습니다." << endl;
				check = 1;
				break;
			}
		}
		if (check != 1) {
			gotoxy(20, 12);
			cout<<"존재하지 않는 제품입니다."<<endl;
			gotoxy(23, 13);
			cout << "품목을 추가해 주세요." << endl;
		}
		if (keyControl() == TAB) {
			return;
		}
	}
}

//출고(원래 있는 제품에 수량 -)
void release() {
	string productName;	//제품 이름
	int quantity;		//제품 수량
	int check;

	while (true) {
		system("cls");
		check = 0;
		gotoxy(33, 2);
		cout << "<출고>" << endl;
		gotoxy(16, 4);
		cout << "※ 출고하고자 하는 품목의 이름, 수량을 입력하세요 ※" << endl;

		gotoxy(32, 7);
		cout << "제품 이름 : ";
		cin >> productName;
		gotoxy(32, 8);
		cout << "제품 수량 : ";
		cin >> quantity;

		//product배열에 물품이 있는지 확인
		for (int i = 0; i < cnt; i++) {
			if (product[i]->getProductName() == productName) {
				product[i]->disQuantity(quantity);
				gotoxy(31, 12);
				cout << "출고되었습니다." << endl;
				check = 1;
				break;
			}
		}
		if (check != 1) {
			gotoxy(20, 12);
			cout << "존재하지 않는 제품입니다." << endl;
			gotoxy(23, 13);
			cout << "품목을 추가해 주세요." << endl;
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

		//메뉴 선택 -> 함수
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

//누적 수익 -> 소비자들의 구매로 인한 수익 -> 항상 맨위에?
void totalProfit() {
	gotoxy(0, 0);
	cout << "누적수익 : " << customerTotal << endl;
}

//구매(품목을 찾아서, 산 수량만큼 -)
void addShoppingCart() {
	string productName;	//제품 이름
	int quantity;		//제품 수량
	int check;
	while (true) {
		system("cls");
		totalProfit();
		check = 0;
		gotoxy(33, 2);
		cout << "<장바구니 담기>" << endl;
		gotoxy(10, 4);
		cout << "※ 장바구니에 담고자 하는 품목의 이름, 가격, 수량을 입력하세요 ※" << endl;

		gotoxy(32, 7);
		cout << "제품 이름 : ";
		cin >> productName;
		gotoxy(32, 8);
		cout << "제품 수량 : ";
		cin >> quantity;

		//product배열에 물품이 있는지 확인
		for (int i = 0; i < cnt; i++) {
			if (product[i]->getProductName() == productName) {
				product[i]->disQuantity(quantity);
				gotoxy(31, 12);
				cout << "장바구니에 추가 되었습니다." << endl;

				buyProduct[buyCnt++] = new Product(product[i]->getProductName(), product[i]->getPrice(), product[i]->getCustomerPrice(), product[i]->getQuantity());
				customerTotal += buyProduct[i]->getCustomerPrice() * quantity;
				
				check = 1;
				break;
			}
		}

		if (check != 1) {
			gotoxy(20, 12);
			cout << "존재하지 않는 제품입니다." << endl;
			gotoxy(23, 13);
			cout << "품목을 추가해 주세요." << endl;
		}

		//product[i].print();
		if (keyControl() == TAB) {
			return;
		}
	}
}

//장바구니에 있는 제품 구매 취소
void delShoppingCart() {
	string productName;	//제품 이름
	int quantity;		//제품 수량
	int check;
	while (true) {
		system("cls");
		totalProfit();
		check = 0;
		gotoxy(33, 2);
		cout << "<장바구니 삭제>" << endl;
		gotoxy(10, 4);
		cout << "※ 장바구니에서 삭제하고자 하는 품목의 이름, 가격, 수량을 입력하세요 ※" << endl;

		gotoxy(32, 7);
		cout << "제품 이름 : ";
		cin >> productName;
		gotoxy(32, 8);
		cout << "제품 수량 : ";
		cin >> quantity;

		//product배열에 물품이 있는지 확인
		for (int i = 0; i < buyCnt; i++) {
			if (buyProduct[i]->getProductName() == productName) {
				buyProduct[i]->disQuantity(quantity);
				gotoxy(31, 12);
				cout << "장바구니에서 삭제 되었습니다." << endl;

				delete buyProduct[i];
				buyCnt--;

				check = 1;
				break;
			}
		}

		if (check != 1) {
			gotoxy(20, 12);
			cout << "존재하지 않는 제품입니다." << endl;
			gotoxy(23, 13);
			cout << "품목을 추가해 주세요." << endl;
		}

		//product[i].print();
		if (keyControl() == TAB) {
			return;
		}
	}
}

//환불(품목을 찾아서, 환불할 수량만큼 +)
void refund() {
	string productName;	//제품 이름
	int quantity;		//제품 수량
	string refundMemo;	//환불사유
	int check;
	while (true) {
		system("cls");
		totalProfit();
		check = 0;
		gotoxy(33, 2);
		cout << "<환불>" << endl;
		gotoxy(10, 4);
		cout << "※ 환불하고자 하는 품목의 이름, 가격, 수량을 입력하세요 ※" << endl;

		gotoxy(32, 7);
		cout << "제품 이름 : ";
		cin >> productName;
		gotoxy(32, 8);
		cout << "제품 수량 : ";
		cin >> quantity;
		gotoxy(32, 9);
		cout << "환불 사유 : ";
		cin >> refundMemo;

		//product배열에 물품이 있는지 확인
		for (int i = 0; i < cnt; i++) {
			if (product[i]->getProductName() == productName) {
				product[i]->addQuantity(quantity);
				gotoxy(31, 12);
				cout << "환불되었습니다." << endl;

				//고객이 산 제품에 대해 누적합 구하기
				allSum -= product[i]->getCustomerPrice() * quantity;

				check = 1;
				break;
			}
		}

		if (check != 1) {
			gotoxy(20, 12);
			cout << "존재하지 않는 제품입니다." << endl;
			gotoxy(23, 13);
			cout << "품목을 추가해 주세요." << endl;
		}

		//product[i].print();
		if (keyControl() == TAB) {
			return;
		}
	}
}

//구매 리스트
void cartList() {
	system("cls");
	totalProfit();
	gotoxy(15, 3);
	cout << "구매 목록 LIST";
	gotoxy(0, 4);
	cout << " --------------------------------------------------------- " << endl;
	int i = -1;
	if (buyCnt < 0) {
		gotoxy(10, 5);
		cout << "장바구니에 아무것도 없습니다." << endl;
	}
	while (i < buyCnt) {	//i<제품개수
		i++;
		if (buyProduct[i] != nullptr) {
			cout << " | " << i + 1 << " | 제품명 : " << buyProduct[i]->getProductName() << "\t | 수량 : " << buyProduct[i]->getQuantity() << "\t | 가격 : " << buyProduct[i]->getCustomerPrice() << "\t |" << endl;
			cout << " --------------------------------------------------------- " << endl;
		}
		else {
			continue;
		}

	}
	cout << " | 전체 합계 : " << customerTotal <<"\t\t\t         |" << endl;
	cout << " --------------------------------------------------------- " << endl;
	//cout << "빠져나왔습니다." << endl;
}

//구매
void buy() {
	system("cls");
	cartList();
	cout << endl << endl << "구매하시겠습니까?" << endl;
	
	/*char* choice = 0;
	//메뉴출력
	char* choice = 0;
	cout << "YES or NO : ";
	cin >> choice;
	for (int i = 0; i < strlen(choice); i++) {
		choice[i] = tolower(choice[i]);
	}
	if (choice == "yes") {
		cout << "구매되었습니다." << endl;
		for (int i = 0; i < buyCnt; i++) {
			allSum += buyProduct[i]->getCustomerPrice() * buyProduct[i]->getQuantity();
		}
	}
	else if (choice == "no") {
		cout << "구매가 취소되었습니디." << endl;
	}
	else {
		cout << "옳지 않은 형식의 값입니다." << endl;
	}
	*/
	cout << "구매되었습니다." << endl;
	if (keyControl() == TAB) {
		return;
	}
}

int cashierMain() {
	init();

	while (true) {
		cashierTitle();

		//메뉴 선택 -> 함수
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
			managerMain();
			continue;
		}
		else if (id == "cashier" && password == "cashier01") {
			cashierMain();
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

int main() {
	init();
	login();
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
	if (tmp == 27) {
		return ESC;
	}
}
//title 출력하기
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

//메뉴설정
int cashierMenu() {
	int x = 33;
	int y = 19;

	//메뉴출력
	gotoxy(x - 5, y - 1);
	cout << "-------------------------" << endl;
	gotoxy(x - 2, y);
	cout << ">    제품 목록" << endl;
	gotoxy(x, y + 1);
	cout << " 장바구니 추가" << endl;
	gotoxy(x, y + 2);
	cout << " 장바구니 삭제" << endl;
	gotoxy(x, y + 3);
	cout << "   구     매" << endl;
	gotoxy(x, y + 4);
	cout << "   환     불" << endl;
	gotoxy(x, y + 5);
	cout << "   종     료" << endl;
	gotoxy(x - 5, y + 6);
	cout << "-------------------------" << endl << endl;

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

//title 출력하기
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

//메뉴설정
int managerMenu() {
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
	cout << " 종   료" << endl;
	gotoxy(x - 6, y + 6);	//36, 25
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
				y = 22;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	//↓를 눌렸을 경우
			if (y < 22) {	//y는 17~24사이만 이동 -> 24보다 작아야함
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);	//아래쪽으로 1칸 이동후
				cout << ">";
			}
			else if (y == 22) {	//맨 아래 -> 맨 위로 이동
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
