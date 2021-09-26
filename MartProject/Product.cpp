#include "Product.h"

using namespace std;

//제품정보
class Product {
	string productName;	//제품 이름
	int price;			//제품 가격
	int customerPrice;	//소비자가격
	int quantity;		//제품 수량

public:
	Product();
	Product(string, int, int, int);
	~Product();
	void print();

	//getter
	string getProductName();
	int getPrice();
	int getCustomerPrice();
	int getQuantity();

	//수량 +/-
	void addQuantity(int quantity);
	void disQuantity(int quantity);

};


Product::Product() {
	productName = "";
	price = 0;
	customerPrice = 0;
	quantity = 0;
}

Product::Product(string productName, int price, int customerPrice, int quantity) :productName(productName), price(price), customerPrice(customerPrice), quantity(quantity) {};

Product::~Product() {}

void Product::print() {
	cout << "제품이름 : " << productName << endl;
	cout << "제품가격 : " << price << endl;
	cout << "소비자가격 : " << customerPrice << endl;
	cout << "제품수량 : " << quantity << endl;
	cout << "합계 : " << price * quantity << endl;
}

//getter
string Product::getProductName() { return this->productName; }
int Product::getPrice() { return this->price; }
int Product::getCustomerPrice() { return this->customerPrice; }
int Product::getQuantity() { return this->quantity; }

//수량 +/-
void Product::addQuantity(int quantity) { this->quantity += quantity; }
void Product::disQuantity(int quantity) { this->quantity -= quantity; }


//누적 수익 -> 소비자들의 구매로 인한 수익 -> 항상 맨위에?
void totalProfit() {
	gotoxy(0, 0);
	cout << "누적수익 : " << allSum << endl;
}


//제품목록 띄우기 -> 메뉴로 나가는거 안됨
void productList() {
	system("cls");
	//totalProfit();
	gotoxy(15, 3);
	cout << "제품 목록 LIST";
	gotoxy(0, 4);
	cout << " -----------------------------------------" << endl;
	int i = -1;
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
	//cout << "빠져나왔습니다." << endl;
	if (keyControl() == TAB) {
		return;
	}
}

