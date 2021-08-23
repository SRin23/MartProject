#include<iostream>
using namespace std;

void menu() {
	//메뉴
	cout << "----Mart Systm----" << endl;
	cout << "| 1. 품목 추가\t|" << endl;
	cout << "| 2. 품목 삭제\t|" << endl;
	cout << "| 3. 입고\t|" << endl;
	cout << "| 4. 출고\t|" << endl;
	cout << "| 5. 구매\t|" << endl;
	cout << "| 6. 환불\t|" << endl;
	cout << "| 7. 누적 수익\t|" << endl;
	cout << "| 0. 종료\t|" << endl;
	cout << "-------------------" << endl;
}

struct Product {
	//제품
	string productName;
	int price;
	int quantity;
	string company;
};

void addProduct() {
	//품목추가(원래 없는 제품)
	

}

void delProduct() {
	//품목삭제(원래 없는 제품)

}

void buy() {
	//구매

}

void refund() {
	//환불

}

void warehousing() {
	//입고(원래 있는 제품)

}

void release() {
	//출고(원래 있는 제품)

}

void totalProfit() {
	//누적 수익

}

int main() {
	while (true) {
		menu();
		int select = 0;
		cin >> select;
		if (select == 0) break;
		else if (select == 1) addProduct();
		else if (select == 2) delProduct();
		else if (select == 3) buy();
		else if (select == 4) refund();
		else if (select == 5) warehousing();
		else if (select == 6) release();
		else if (select == 7) totalProfit();
		else {
			cout<<"다시 입력해 주세요."<<endl;
			continue;
		}
	}
}
	