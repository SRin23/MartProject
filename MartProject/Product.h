#pragma once

#include "main.h"
#include "util.h"


#ifndef Product_h
#define Product_h

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
#endif

void totalProfit();
void productList();