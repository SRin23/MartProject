#pragma once

#include "main.h"
#include "util.h"


#ifndef Product_h
#define Product_h

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
#endif

void totalProfit();
void productList();