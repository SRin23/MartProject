#include "Product.h"

using namespace std;

//��ǰ����
class Product {
	string productName;	//��ǰ �̸�
	int price;			//��ǰ ����
	int customerPrice;	//�Һ��ڰ���
	int quantity;		//��ǰ ����

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

	//���� +/-
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
	cout << "��ǰ�̸� : " << productName << endl;
	cout << "��ǰ���� : " << price << endl;
	cout << "�Һ��ڰ��� : " << customerPrice << endl;
	cout << "��ǰ���� : " << quantity << endl;
	cout << "�հ� : " << price * quantity << endl;
}

//getter
string Product::getProductName() { return this->productName; }
int Product::getPrice() { return this->price; }
int Product::getCustomerPrice() { return this->customerPrice; }
int Product::getQuantity() { return this->quantity; }

//���� +/-
void Product::addQuantity(int quantity) { this->quantity += quantity; }
void Product::disQuantity(int quantity) { this->quantity -= quantity; }


//���� ���� -> �Һ��ڵ��� ���ŷ� ���� ���� -> �׻� ������?
void totalProfit() {
	gotoxy(0, 0);
	cout << "�������� : " << allSum << endl;
}


//��ǰ��� ���� -> �޴��� �����°� �ȵ�
void productList() {
	system("cls");
	//totalProfit();
	gotoxy(15, 3);
	cout << "��ǰ ��� LIST";
	gotoxy(0, 4);
	cout << " -----------------------------------------" << endl;
	int i = -1;
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
	//cout << "�������Խ��ϴ�." << endl;
	if (keyControl() == TAB) {
		return;
	}
}

