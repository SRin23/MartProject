#pragma once

#include "Product.h"

#ifndef Manager_h
#define Manager_h

class Manager {
private :
	int allSum;
	Product* product[10];
	int cnt;
private :
	int managerMain();
	void addProduct();
	void delProduct();
	void warehousing();
	void release();
	void title();
	int menu();
};

#endif Manager_h