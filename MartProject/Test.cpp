#include<iostream>
using namespace std;

class Test{
	int a;
	int b;
public : 
	int getA() { return this->a; }
	int getB() { return this->b; }
};



void Print() {
	Test* test[10];
	test[0] = new Test();
	test[1] = new Test();
	test[2] = new Test();
	test[3] = new Test();
	test[4] = new Test();

	for (int i = 0; i < 5; i++) {
		test[i]->getA();
	}
}
int main() {

}