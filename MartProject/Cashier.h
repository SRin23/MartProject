#pragma once

#include "util.h"
#include "Product.h"

#ifndef Cashier_h
#define Cashier_h

class Cashier {
private:
	Product* product[10];
	int cnt;

	Product* buyProduct[10];
	int buyCnt;
	int customerTotal;

public:
	void addShoppingCart();
	void delShoppingCart();
	void refund();
	void cartList();
	void buy();
	void title();
	int menu();
	int cashierMain();
};

#endif Cashier_h