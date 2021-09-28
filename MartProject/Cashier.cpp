#include "Cashier.h"

using namespace std;

//구매(품목을 찾아서, 산 수량만큼 -)
void Cashier::addShoppingCart() {
	string productName;	//제품 이름
	int quantity;		//제품 수량
	int check;
	while (true) {
		system("cls");
		//totalProfit();
		check = 0;
		gotoxy(33, 2);
		cout << "<구매>" << endl;
		gotoxy(10, 4);
		cout << "※ 구매하고자 하는 품목의 이름, 가격, 수량을 입력하세요 ※" << endl;

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
				cout << "구매되었습니다." << endl;

				buyProduct[buyCnt++] = new Product(product[i]->getProductName(), product[i]->getPrice(), product[i]->getCustomerPrice(), product[i]->getQuantity());
				//고객이 산 제품에 대해 누적합 구하기
				allSum += product[i]->getCustomerPrice() * quantity;
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
void Cashier::delShoppingCart() {
	string productName;	//제품 이름
	int quantity;		//제품 수량
	int check;
	while (true) {
		system("cls");
		//totalProfit();
		check = 0;
		gotoxy(33, 2);
		cout << "<구매취소>" << endl;
		gotoxy(10, 4);
		cout << "※ 구매를 취소하고자 하는 품목의 이름, 가격, 수량을 입력하세요 ※" << endl;

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
				cout << "구매되었습니다." << endl;

				//고객이 산 제품에 대해 누적합 구하기
				allSum += product[i]->getCustomerPrice() * quantity;

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
void Cashier::refund() {
	string productName;	//제품 이름
	int quantity;		//제품 수량
	string refundMemo;	//환불사유
	int check;
	while (true) {
		system("cls");
		//totalProfit();
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
void Cashier::cartList() {
	system("cls");
	//totalProfit();
	gotoxy(15, 3);
	cout << "구매 목록 LIST";
	gotoxy(0, 4);
	cout << " --------------------------------------------------------- " << endl;
	int i = -1;
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
	cout << " | - | 전체 합계 : " << customerTotal << "\t\t\t\t         |" << endl;
	cout << " --------------------------------------------------------- " << endl;
	//cout << "빠져나왔습니다." << endl;
}

//구매
void Cashier::buy() {
	system("cls");
	cartList();
	cout << endl << endl << "구매하시겠습니까?" << endl;
	cout << "구매되었습니다." << endl;
	if (keyControl() == TAB) {
		return;
	}
}

int Cashier::cashierMain() {
	init();

	while (true) {
		cashierTitle();

		//메뉴 선택 -> 함수
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

//title 출력하기
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

//메뉴설정
int Cashier::menu() {
	int x = 33;
	int y = 19;

	//메뉴출력
	gotoxy(x - 5, y - 1);
	cout << "----------------------" << endl;
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
	cout << "----------------------" << endl << endl;

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
