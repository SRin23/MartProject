#include<iostream>
using namespace std;

void menu() {
	//�޴�
	cout << "----Mart Systm----" << endl;
	cout << "| 1. ǰ�� �߰�\t|" << endl;
	cout << "| 2. ǰ�� ����\t|" << endl;
	cout << "| 3. �԰�\t|" << endl;
	cout << "| 4. ���\t|" << endl;
	cout << "| 5. ����\t|" << endl;
	cout << "| 6. ȯ��\t|" << endl;
	cout << "| 7. ���� ����\t|" << endl;
	cout << "| 0. ����\t|" << endl;
	cout << "-------------------" << endl;
}

struct Product {
	//��ǰ
	string productName;
	int price;
	int quantity;
	string company;
};

void addProduct() {
	//ǰ���߰�(���� ���� ��ǰ)
	

}

void delProduct() {
	//ǰ�����(���� ���� ��ǰ)

}

void buy() {
	//����

}

void refund() {
	//ȯ��

}

void warehousing() {
	//�԰�(���� �ִ� ��ǰ)

}

void release() {
	//���(���� �ִ� ��ǰ)

}

void totalProfit() {
	//���� ����

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
			cout<<"�ٽ� �Է��� �ּ���."<<endl;
			continue;
		}
	}
}
	