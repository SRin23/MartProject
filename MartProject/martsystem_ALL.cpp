#define _CRT_SECURE_NO_WARNINGS
#include<mysql.h>
#include<iostream>
#include<cstdio>
#include<conio.h>	//getch���
#include<windows.h>	//��ǥ���
#include <string.h>
#include<string>
#include <ctime> //C++

//����Ű �� Ű�� ����
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define ENTER 4	//ENTERŰ : t����
#define TAB 5	//TABŰ : Main���� ����������
#define ESC 6	//���α׷� ����

#pragma comment(lib, "libmySQL.lib")
#define DB_HOST "localhost"	//ȣ��Ʈ �̸� �Ǵ� IP �ּ�(�⺻ : localhost)
#define DB_USER "root" //MySQL login id(mysql -u ���⾲�°� -p)
#define DB_PASS "mirim"	//�н�����
#define DB_NAME "martsystem_db"	//�����ͺ��̽� �̸�
#define CHOP(x) x[strlen(x)-1] = ' '

using namespace std;

void loginMain();
int selectQuery();
int YN_Check(int x, int y);
void init();
void gotoxy(int x, int y);
int keyControl();
static int product_Count = 0;
static int cart_Count = 0;

MYSQL* connection = NULL, conn;
int query_stat;
char query[255];


//--------------------------------------------------CLASS------------------------------------------------------
class Manager {
public:
	int productList();
	int m_insertQuery();
	int m_deleteQuery();
	int updateQueryProductName();
	int updateQueryProductPrice();
	int updateQueryCustomerPrice();
	int updateQueryAll();
	void updateQueryAllCheck();
	int m_updateMenu();
	int m_updateQuery();
	int m_warehousing();
	int m_release();
	void managerTitle();
	int managerMenu();
	int totalSelect();
	void managerMain();
};

class Customer {
private : 
	string tableName;
	string cartNamestr = "cart_" + tableName;
	const char* tableCartName = cartNamestr.c_str();
	string historyNamestr = "history_" + tableName;
	const char* tableHistoryName = historyNamestr.c_str();

public:
	Customer() {}
	Customer(string tableName) :tableName(tableName) {};
	int CartList();
	int CartListMenu();
	int addShoppingCart();
	int delCartProduct();
	int deleteAll();
	int deleteCartMenu();
	void deleteCart();
	int updatePlusCartQuantity();
	int updateMinusCartQuantity();
	int updateCartMenu();
	void UpdateCart();
	int buy();
	int refund();
	int historyList();
	void customerTitle();
	int customerMenu();
	void customerMain();
};

//-------------------------------------------------- MAIN -----------------------------------------------------
//main title���
int mainTitle()
{
	system("cls");
	int x = 16, y = 6;
	gotoxy(10, y - 3); cout << "====================================================================================================";
	gotoxy(x, y++); cout << "##       ##        #        #######     ########";
	gotoxy(x, y++); cout << "####   ####      ## ##      ##    ##       ##";
	gotoxy(x, y++); cout << "##  ###  ##     ##   ##     #######        ##";
	gotoxy(x, y++); cout << "##   #   ##    #########    ##    ##       ##";
	gotoxy(x, y++); cout << "##       ##   ##       ##   ##     ##      ##";
	gotoxy(x, y++); cout << "##       ##   ##       ##   ##     ##      ##";

	x = 25, y = 14;
	gotoxy(x, y++); cout << "  #######   ##      ##     #######    ##########   ##########   ##       ##";
	gotoxy(x, y++); cout << "##           ##    ##    ##               ##       ##           ####   ####";
	gotoxy(x, y++); cout << " #######      ##  ##      #######         ##       #######      ##  ###  ##";
	gotoxy(x, y++); cout << "        ##     ##                ##       ##       ##           ##   #   ##";
	gotoxy(x, y++); cout << "        ##     ##                ##       ##       ##           ##       ##";
	gotoxy(x, y++); cout << " ########      ##         ########        ##       ##########   ##       ##";

	x = 56;
	gotoxy(x - 2, y + 2);	cout << "> ��  ��" << endl;
	gotoxy(x, y + 3);	cout << "����" << endl;
	gotoxy(x, y + 4); cout << "��  ��" << endl;

	gotoxy(10, y + 6); cout << "====================================================================================================";
	
	y = 22;
	while (true) {	//���� �ݺ�
		int n = keyControl();
		switch (n) {
		case UP:	//�踦 ������ ���
			if (y > 22) {	//y�� 17~24���̸� �̵� -> 17���� Ŀ����
				gotoxy(x - 2, y);	//���� ���ۿ� �ִ� >
				cout << " ";	//�����
				gotoxy(x - 2, --y);	//�������� 1ĭ �̵���
				cout << ">";	//�ٽ� �׸���
			}
			else if (y == 22) {	//�� �� -> �� �Ʒ��� �̵�
				gotoxy(x - 2, y);
				cout << " ";
				y = 24;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	//�鸦 ������ ���
			if (y < 24) {	//y�� 17~24���̸� �̵� -> 24���� �۾ƾ���
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);	//�Ʒ������� 1ĭ �̵���
				cout << ">";
			}
			else if (y == 24) {	//�� �Ʒ� -> �� ���� �̵�
				gotoxy(x - 2, y);
				cout << " ";
				y = 22;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case ENTER:	//���� -> �������� ���
			return y - 22;	//y-17�� �Ͽ� �� ���� ���� 1, 2, 3...���� ���� �� �ִ�. -> �� ����
		}
	}
}

void solution() {
	system("cls");
	cout << "[ ����� ]" << endl<<endl<<endl;
	cout << " - Manager�� Customer�� �̷���� ��Ʈ ���� �ý��� �Դϴ�." << endl;
	cout << " - ������ ������ �ð��� �Ͻø� ȸ�������� ������ �ּ���" << endl;
	cout << " - ���̵� �����ôٸ� ���α׷��� ���� �� �� �����ϴ�." << endl;
	cout << " - ��� ȭ�鿡�� ����ȭ������ �Ѿ���� TAB�� �����ּ���." << endl;
	cout << " - ��� ȭ�鿡�� �����Ϸ��� ENTER�� �����ּ���." << endl;
	cout << " - ��� �޴� �ϴܿ��� ����/����ȭ�� ��ư�� �ֽ��ϴ�." << endl;
	cout << " - �׷� ���ϰ� ������ּ���^^" << endl;

	if (keyControl() == TAB) {
		return;
	}
}

void main() {
	system("cls");
	init();
	while (true) {
		//�޴� ���� -> �Լ�
		int select = mainTitle();
		if (select == 0) loginMain();
		else if (select == 1) solution();
		else if (select == 2) { gotoxy(0, 28); return; }
	}
	return;
}

//-------------------------------------------------- login -----------------------------------------------------
int createTable(string tableName) {
	MYSQL_RES* sql_result;
	mysql_init(&conn);

	string TCN = "Create table cart_" + tableName + " (productName varchar(30) not null, customerprice int, quantity int, total int)";
	const char* tableCartName = TCN.c_str();

	string THN = "Create table history_" + tableName + " (history varchar(10) not null, date date, productName varchar(30), customerprice int, quantity int, refund_reason varchar(100))";
	const char* tableHistoryName = THN.c_str();

	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	mysql_set_character_set(connection, "euckr");
	if (connection == NULL) {
		//fprintf(stderr, "Mysql connection error : %s\n", mysql_error(&conn));
		printf("�����ͺ��̽����� ������ ���������ϴ�.");
		return 1;
	}

	query_stat = mysql_query(connection, tableCartName);
	if (query_stat != 0) {
		printf("���� �ҷ��� �� �����ϴ�.(create)");
		//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
		return 1;
	}

	query_stat = mysql_query(connection, tableHistoryName);
	if (query_stat != 0) {
		printf("���� �ҷ��� �� �����ϴ�.(create)");
		//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
		return 1;
	}
	sql_result = mysql_store_result(connection);

	
}

//Manager, Customer���� ���ϱ�
int ManagerCustomer(int x, int y) {
	int cx = x;
	int cy = y;

	gotoxy(cx - 2, cy);	
	cout << "> Manager" << endl;
	gotoxy(cx, cy + 1);	
	cout << "Customer" << endl;

	while (true) {	
		int n = keyControl();
		switch (n) {
		case UP:	
			if (cy > y) {	
				gotoxy(cx - 2, cy);
				cout << " ";	
				gotoxy(cx - 2, --cy);	
				cout << ">";	
			}
			else if (cy == y) {	
				gotoxy(cx - 2, cy);
				cout << " ";
				cy = y + 1;
				gotoxy(cx - 2, cy);
				cout << ">";
			}
			break;

		case DOWN:	
			if (cy < y + 1) {	
				gotoxy(cx - 2, cy);
				cout << " ";
				gotoxy(cx - 2, ++cy);	
				cout << ">";
			}
			else if (cy == y + 1) {	
				gotoxy(cx - 2, cy);
				cout << " ";
				cy = y;
				gotoxy(cx - 2, cy);
				cout << ">";
			}
			break;

		case ENTER:	
			return cy - y;	
		}
	}
}

//ȸ������
int signup() {
	system("cls");
	char name[30];
	char id[16];
	char pw[16];
	char pwCheck[16];
	char role[5];

	mysql_init(&conn);

	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	mysql_set_character_set(connection, "euckr");
	if (connection == NULL) {
		printf("�����ͺ��̽����� ������ ���������ϴ�.");
		return 1;
	}
	gotoxy(54, 11);
	printf("�̸� : ");
	fgets(name, 30, stdin);
	CHOP(name);

	gotoxy(52, 12);
	printf("���̵� : ");
	fgets(id, 16, stdin);
	CHOP(id);

	gotoxy(50, 13);
	printf("��й�ȣ : ");
	fgets(pw, 16, stdin);
	CHOP(pw);

	gotoxy(50, 13);
	printf("��й�ȣ : ");
	for (int i = 0; i < strlen(pw); i++) {
		printf("*");
	}

	gotoxy(45, 14);
	printf("��й�ȣ Ȯ�� : ");
	fgets(pwCheck, 16, stdin);
	CHOP(pwCheck);

	gotoxy(45, 14);
	printf("��й�ȣ Ȯ�� : ");
	for (int i = 0; i < strlen(pwCheck); i++) {
		printf("*");
	}

	gotoxy(43, 16);
	if (strcmp(pw, pwCheck)) {
		cout << "��й�ȣ�� ��ġ���� �ʽ��ϴ�." << endl;
		gotoxy(43, 17);
		cout << "�ٽ� �õ��� �ֽʽÿ�" << endl;
		Sleep(2000);
		return 0;
	}

	// �ܼ� ���â�� ������ ��� ���ؼ� ������ ����ü
	CONSOLE_SCREEN_BUFFER_INFO presentCur;

	//���� �ܼ� ��ġ ��ȯ
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
	if (ManagerCustomer(presentCur.dwCursorPosition.X + 12, presentCur.dwCursorPosition.Y + 1) == 0) {
		strcpy(role, "M");
	}
	else {
		strcpy(role, "C");
		createTable(id);
	}

	sprintf(query, "insert into login_info (name, id, pw, role) values ('%s', '%s', '%s', '%s')", name, id, pw, role);
	query_stat = mysql_query(connection, query);
	if (query_stat != 0) {
		//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
		printf("�Է��� ���� �ʽ��ϴ�.(insert)");
		return 1;
	}

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
	gotoxy(presentCur.dwCursorPosition.X + 44, presentCur.dwCursorPosition.Y + 1);
	cout <<"ȸ�������� �Ϸ� �Ǿ����ϴ�." << endl;
	mysql_close(connection);

	if (keyControl() == TAB) {
		return 0;
	}
}

//�α���
int signin() {
	system("cls");
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	char id[16];
	char pw[16];
	int listCount = 1;
	mysql_init(&conn);

	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	mysql_set_character_set(connection, "euckr");
	if (connection == NULL) {
		printf("�����ͺ��̽����� ������ ���������ϴ�.");
		return 1;
	}
	gotoxy(52, 11);
	printf("���̵� : ");
	fgets(id, 16, stdin);
	CHOP(id);

	gotoxy(50, 12);
	printf("��й�ȣ : ");
	fgets(pw, 16, stdin);
	CHOP(pw);

	gotoxy(50, 12);
	printf("��й�ȣ : ");
	for (int i = 0; i < strlen(pw); i++) {
		printf("*");
	}

	query_stat = mysql_query(connection, "select * from login_info");
	if (query_stat != 0) {
		gotoxy(55, 14);
		printf("���� �ҷ��� �� �����ϴ�.(select)");
		return 1;
	}

	sql_result = mysql_store_result(connection);
	gotoxy(45, 16);
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
		//printf("%s, %s, %s, %s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3]);
		if (!strcmp(id, sql_row[1])) {
			if (!strcmp(pw, sql_row[2])) {
				cout << sql_row[0] << "��, �α��� �Ǿ����ϴ�." << endl;
				Sleep(2000);
				if (!strcmp("M", sql_row[3])) {
					Manager* m = new Manager();
					m->managerMain();
					return 0;
				}
				else if (!strcmp("C", sql_row[3])) {
					Customer* c = new Customer(id);
					c->customerMain();
					return 0;
				}
				else {
					cout << "������ �� ���� ȸ���Դϴ�." << endl;
					Sleep(2000);
					return 0;
				}
			}
			else {
				cout << "�߸��� ��й�ȣ �Դϴ�." << endl;
				Sleep(2000);
				return 0;
			}
		}
	}
	cout << "���̵�/��й�ȣ�� �����ϴ�." << endl;
	Sleep(2000);

	//mysql_store_result�� ���� �޸𸮸� ��ü��Ŵ-> ��ġ malloc�� free����
	mysql_free_result(sql_result);
}

//���Ե� ���̵� ����Ʈ
int idList() {
	system("cls");
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	int listCount = 1;
	mysql_init(&conn);

	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	mysql_set_character_set(connection, "euckr");
	if (connection == NULL) {
		printf("�����ͺ��̽����� ������ ���������ϴ�.");
		return 1;
	}

	query_stat = mysql_query(connection, "select * from login_info");
	if (query_stat != 0) {
		printf("���� �ҷ��� �� �����ϴ�.(select)");
		return 1;
	}

	sql_result = mysql_store_result(connection);
	printf("������������������������������������������������������������������������������������������������������������������������������������\n");
	printf("�� %3s �� %10s �� %16s �� %16s �� %5s ��\n", "NO", "NAME", "ID", "PW", "ROLE");
	printf("������������������������������������������������������������������������������������������������������������������������������������\n");
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
		printf("�� %3d �� %10s �� %16s �� ", listCount++, sql_row[0], sql_row[1]);
		for (int i = 0; i < 16-strlen(sql_row[2]); i++) {
			printf(" ");
		}
		for (int i = 0; i < strlen(sql_row[2]); i++) {
			printf("*");
		}
		printf(" �� %5s �� \n", sql_row[3]);
		
	}
	printf("������������������������������������������������������������������������������������������������������������������������������������\n");
	if (sql_result == NULL) {
		cout << "���� �����ϴ�." << endl;
	}

	mysql_free_result(sql_result);

	if (keyControl() == TAB) {
		return 0;
	}
}

//login�޴����� 
int loginMenu() {
	system("cls");
	int x = 56;
	int y = 12;

	//�޴����
	gotoxy(x - 6, y - 1); 
	cout << "������������������������������������������" << endl;
	gotoxy(x - 2, y);	
	cout << ">  �α���" << endl;
	gotoxy(x, y + 2);	
	cout << " ȸ������" << endl;
	gotoxy(x, y + 4);	
	cout << " ȸ�����" << endl;
	gotoxy(x, y + 6);	
	cout << " �ʱ�ȭ��" << endl;
	gotoxy(x - 6, y + 7);	
	cout << "������������������������������������������" << endl << endl;


	while (true) {
		int n = keyControl();
		switch (n) {
		case UP:	
			if (y > 12) {	
				gotoxy(x - 2, y);	
				cout << " ";	
				gotoxy(x - 2, y-=2);	
				cout << ">";	
			}
			else if (y == 12) {	
				gotoxy(x - 2, y);
				cout << " ";
				y = 18;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	
			if (y < 18) {	
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, y+=2);	
				cout << ">";
			}
			else if (y == 18) {	
				gotoxy(x - 2, y);
				cout << " ";
				y = 12;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case ENTER:	
			return y - 12;	
		}
	}
}

//login����
void loginMain() {
	system("cls");
	init();
	while (true) {
		//�޴� ���� -> �Լ�
		int select = loginMenu();
		if (select == 0) signin();
		else if (select == 2) signup();
		else if (select == 4) idList();
		else if (select == 6) {
			gotoxy(0, 25); break;
		}
	}
}

//------------------------------------------------ MANAGER �Լ�-----------------------------------------------------

//ǰ�� ����Ʈ ���
int Manager::productList() {
	system("cls");
	selectQuery();
	if (keyControl() == TAB) {
		return 0;
	}
}

//managerǰ�� �߰�
int Manager::m_insertQuery() {
	char productName[30];
	char productPrice[10];
	char customerPrice[10];
	char quantity[10];
	bool addCheck = 0;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;

	//TAB������ ������ �ƴϸ� ��� ����
	while (true) {
		system("cls");
		selectQuery();
		addCheck = 0;
		mysql_init(&conn);

		//Mysql �����ͺ��̽� �������� ���� �õ�.
		connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
		mysql_set_character_set(connection, "euckr");
		//C++�� mysql�� �������� �ʾ��� ��� �����޼���
		//con���� : MYSQL* ���� �ڵ� (= ù ��° �Ķ����)/����: NULL
		if (connection == NULL) {
			//fprintf -> stderr�� ����Ϳ� ���� �޼����� �����ִ� �ڵ�(������ ���Ͽ� �ۼ��ϴ� �ڵ�)
			//mysql_error�� ���� mysql���� ������ error�� �ٷ� �� �� �ִ�.
			//fprintf(stderr, "Mysql connection error : %s\n", mysql_error(&conn));
			printf("�����ͺ��̽����� ������ ���������ϴ�.");
			return 1;
		}

		printf("��ǰ�� : ");
		fgets(productName, 30, stdin);
		//�Է¹��� ���ڿ��� �� �κ� ������ ������ �� ����� �����ִ� ����
		CHOP(productName);

		query_stat = mysql_query(connection, "select * from product");
		if (query_stat != 0) {
			printf("���� �ҷ��� �� �����ϴ�.(select)");
			//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
			return 1;
		}

		sql_result = mysql_store_result(connection);
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
			//printf("%s", sql_row[0]);
			if (!strcmp(sql_row[0], productName)) {
				printf("��ǰ���� : ");
				fgets(quantity, 10, stdin);
				CHOP(quantity);
				addCheck = 1;

				sprintf(query, "UPDATE product SET quantity = quantity + %d WHERE productName = '%s'", stoi(quantity), productName);
				query_stat = mysql_query(connection, query);
				if (query_stat != 0) {
					//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
					fprintf(stdout, "update�� ������� �ʽ��ϴ�.(ǰ�� �߰� �Ұ�)");
					return 1;
				}
				system("cls");
				selectQuery();
				cout << "ǰ�� �߰��� �Ϸ� �Ǿ����ϴ�." << endl;

				mysql_free_result(sql_result);

				if (keyControl() == TAB) {
					return 0;
				}
			}
		}
		if (addCheck == 1) {
			continue;
		}

		printf("��ǰ���� : ");
		fgets(productPrice, 10, stdin);
		CHOP(productPrice);

		printf("�Һ��ڰ��� : ");
		fgets(customerPrice, 10, stdin);
		CHOP(customerPrice);

		printf("��ǰ���� : ");
		fgets(quantity, 10, stdin);
		CHOP(quantity);

		sprintf(query, "insert into product (productName, productPrice, customerPrice, quantity) values ('%s', '%d', '%d', '%d')", productName, stoi(productPrice), stoi(customerPrice), stoi(quantity));
		query_stat = mysql_query(connection, query);
		if (query_stat != 0) {
			//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
			printf("ǰ���� �߰��� �� �����ϴ�.(insert)");
			return 1;
		}
		system("cls");
		selectQuery();
		cout << "ǰ�� �߰��� �Ϸ� �Ǿ����ϴ�." << endl;
		product_Count++;


		
		//mysql_store_result�� ���� �޸𸮸� ��ü��Ŵ-> ��ġ malloc�� free����
		mysql_free_result(sql_result);
		mysql_close(connection);

		if (keyControl() == TAB) {
			break;
		}
	}
	

	return 0;
}

//managerǰ�� ����
int Manager::m_deleteQuery() {
	char productName[30];
	bool deleteCheck = 0;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;

	while (true) {
		system("cls");
		selectQuery();

		mysql_init(&conn);

		connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
		mysql_set_character_set(connection, "euckr");
		if (connection == NULL) {
			//fprintf(stderr, "Mysql connection error : %s\n", mysql_error(&conn));
			printf("�����ͺ��̽����� ������ ���������ϴ�.");
			return 1;
		}

		cout << "��ǰ�� : ";
		fgets(productName, 30, stdin);
		CHOP(productName);

		query_stat = mysql_query(connection, "select * from product");
		if (query_stat != 0) {
			printf("���� �ҷ��� �� �����ϴ�.(select)");
			//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
			return 1;
		}

		sql_result = mysql_store_result(connection);
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
			//printf("%s", sql_row[0]);
			if (!strcmp(sql_row[0], productName)) {
				deleteCheck = 1;
				sprintf(query, "delete from product where productName='%s'", productName);
				query_stat = mysql_query(connection, query);
				if (query_stat != 0) {
					//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
					fprintf(stdout, "delete�� ������� �ʽ��ϴ�.");
					return 1;
				}
				product_Count--;
				system("cls");
				selectQuery();
				cout << "ǰ�� ������ �Ϸ� �Ǿ����ϴ�." << endl;
			}
		}

		if (deleteCheck == 0) {
			printf("�Է��� ǰ���� �������� �ʽ��ϴ�.");
		}

		mysql_free_result(sql_result);
		mysql_close(connection);

		if (keyControl() == TAB) {
			break;
		}
	}
	
}

//managerǰ�� ����
int Manager::updateQueryProductName() {
	char productName[30];
	char changeName[30];
	bool updateCheck = 0;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	system("cls");

	while (true) {
		system("cls");
		selectQuery();
		mysql_init(&conn);
		mysql_set_character_set(connection, "euckr");
		connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
		mysql_set_character_set(connection, "euckr");
		if (connection == NULL) {
			printf("�����ͺ��̽����� ������ ���������ϴ�.");
			return 1;
		}

		cout << "��ǰ�� : ";
		fgets(productName, 30, stdin);
		CHOP(productName);

		cout << "������ ��ǰ�� : ";
		fgets(changeName, 30, stdin);
		CHOP(changeName);

		query_stat = mysql_query(connection, "select * from product");
		if (query_stat != 0) {
			printf("���� �ҷ��� �� �����ϴ�.(select)");
			//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
			return 1;
		}

		sql_result = mysql_store_result(connection);
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
			//printf("%s", sql_row[0]);
			if (!strcmp(sql_row[0], productName)) {
				updateCheck = 1;
				sprintf(query, "update product set productName='%s' where productName='%s'", changeName, productName);
				query_stat = mysql_query(connection, query);
				if (query_stat != 0) {
					//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
					fprintf(stdout, "update�� ������� �ʽ��ϴ�.");
					return 1;
				}
				system("cls");
				selectQuery();
				cout << "ǰ�� ������ �Ϸ� �Ǿ����ϴ�." << endl;
			}
		}

		if (updateCheck == 0) {
			printf("�Է��� ǰ���� �������� �ʽ��ϴ�.");
		}


		mysql_free_result(sql_result);
		mysql_close(connection);

		if (keyControl() == TAB) {
			return 0;
		}
	}
	
}
int Manager::updateQueryProductPrice() {
	char productName[30];
	char changeProductPrice[8];
	bool updateCheck = 0;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;

	system("cls");
	while (true) {
		system("cls");
		selectQuery();
		mysql_init(&conn);
		mysql_set_character_set(connection, "euckr");
		connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
		mysql_set_character_set(connection, "euckr");
		if (connection == NULL) {
			printf("�����ͺ��̽����� ������ ���������ϴ�.");
			return 1;
		}

		cout << "��ǰ�� : ";
		fgets(productName, 30, stdin);
		CHOP(productName);

		cout << "������ ���� : ";
		fgets(changeProductPrice, 8, stdin);
		CHOP(changeProductPrice);


		query_stat = mysql_query(connection, "select * from product");
		if (query_stat != 0) {
			printf("���� �ҷ��� �� �����ϴ�.(select)");
			//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
			return 1;
		}

		sql_result = mysql_store_result(connection);
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
			//printf("%s", sql_row[0]);
			if (!strcmp(sql_row[0], productName)) {
				updateCheck = 1;
				sprintf(query, "update product set productPrice= '%d' where productName='%s'", stoi(changeProductPrice), productName);
				query_stat = mysql_query(connection, query);
				if (query_stat != 0) {
					//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
					fprintf(stdout, "update�� ������� �ʽ��ϴ�.");
					return 1;
				}
				system("cls");
				selectQuery();
				cout << "ǰ�� ������ �Ϸ� �Ǿ����ϴ�." << endl;
			}
		}

		if (updateCheck == 0) {
			printf("�Է��� ǰ���� �������� �ʽ��ϴ�.");
		}


		mysql_free_result(sql_result);
		mysql_close(connection);

		if (keyControl() == TAB) {
			return 0;
		}
	}
}
int Manager::updateQueryCustomerPrice() {
	char productName[30];
	char changeCustomerPrice[8];
	bool updateCheck = 0;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	system("cls");
	while (true) {
		system("cls");
		selectQuery();
		mysql_init(&conn);
		mysql_set_character_set(connection, "euckr");
		connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
		mysql_set_character_set(connection, "euckr");
		if (connection == NULL) {
			printf("�����ͺ��̽����� ������ ���������ϴ�.");
			return 1;
		}

		cout << "��ǰ�� : ";
		fgets(productName, 30, stdin);
		CHOP(productName);

		cout << "������ �Һ��� ���� : ";
		fgets(changeCustomerPrice, 8, stdin);
		CHOP(changeCustomerPrice);


		query_stat = mysql_query(connection, "select * from product");
		if (query_stat != 0) {
			printf("���� �ҷ��� �� �����ϴ�.(select)");
			//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
			return 1;
		}

		sql_result = mysql_store_result(connection);
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
			//printf("%s", sql_row[0]);
			if (!strcmp(sql_row[0], productName)) {
				updateCheck = 1;
				sprintf(query, "update product set customerPrice= '%d' where productName='%s'", stoi(changeCustomerPrice), productName);
				query_stat = mysql_query(connection, query);
				if (query_stat != 0) {
					//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
					fprintf(stdout, "update�� ������� �ʽ��ϴ�.");
					return 1;
				}
				system("cls");
				selectQuery();
				cout << "ǰ�� ������ �Ϸ� �Ǿ����ϴ�." << endl;
			}
		}

		if (updateCheck == 0) {
			printf("�Է��� ǰ���� �������� �ʽ��ϴ�.");
		}


		mysql_free_result(sql_result);
		mysql_close(connection);

		if (keyControl() == TAB) {
			return 0;
		}
	}
}
int Manager::updateQueryAll() {
	char productName[30];
	char changeProductName[30];
	char changeProductPrice[8];
	char changeCustomerPrice[8];
	bool updateCheck = 0;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;

	system("cls");
	while (true) {
		system("cls");
		selectQuery();
		mysql_init(&conn);
		mysql_set_character_set(connection, "euckr");
		connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
		mysql_set_character_set(connection, "euckr");
		if (connection == NULL) {
			fprintf(stderr, "Mysql connection error : %s\n", mysql_error(&conn));
			return 1;
		}


		cout << "��ǰ�� : ";
		fgets(productName, 30, stdin);
		CHOP(productName);

		cout << "������ �̸� : ";
		fgets(changeProductName, 8, stdin);
		CHOP(changeProductName);

		cout << "������ ���� : ";
		fgets(changeProductPrice, 8, stdin);
		CHOP(changeProductPrice);

		cout << "������ �Һ��ڰ��� : ";
		fgets(changeCustomerPrice, 8, stdin);
		CHOP(changeCustomerPrice);

		query_stat = mysql_query(connection, "select * from product");
		if (query_stat != 0) {
			printf("���� �ҷ��� �� �����ϴ�.(select)");
			//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
			return 1;
		}

		sql_result = mysql_store_result(connection);
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
			//printf("%s", sql_row[0]);
			if (!strcmp(sql_row[0], productName)) {
				updateCheck = 1;
				sprintf(query, " update product set productName='%s', productPrice='%d', customerPrice='%d' where productName='%s'", changeProductName, stoi(changeProductPrice), stoi(changeCustomerPrice), productName);
				query_stat = mysql_query(connection, query);
				if (query_stat != 0) {
					//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
					fprintf(stdout, "update�� ������� �ʽ��ϴ�.");
					return 1;
				}
				system("cls");
				selectQuery();
				cout << "ǰ�� ������ �Ϸ� �Ǿ����ϴ�." << endl;
			}
		}

		if (updateCheck == 0) {
			printf("�Է��� ǰ���� �������� �ʽ��ϴ�.");
		}


		mysql_free_result(sql_result);
		mysql_close(connection);

		if (keyControl() == TAB) {
			return 0;
		}
	}
}
void Manager::updateQueryAllCheck() {
	system("cls");
	cout << "ǰ���� ��ü ���� �Ͻ÷��� YES" << endl;
	cout << "ǰ���� ��ü ���� �Ͻ÷��� NO" << endl;

	if (YN_Check(2, 4) == 0) {
		updateQueryAll();
	}
	else {
		m_deleteQuery();
	}
}

//manager�޴�����
int Manager::m_updateMenu() {
	system("cls");
	int x = 52;
	int y = 12;

	//�޴����
	gotoxy(x - 7, y - 1); //30, 16
	cout << "������������������������������������������������������" << endl;
	gotoxy(x - 2, y);	//34, 17
	cout << "> ��ü ����" << endl;
	gotoxy(x, y + 1);	//36, 18
	cout << "��ǰ �̸� ����" << endl;
	gotoxy(x, y + 2);	//36, 19
	cout << "��ǰ ���� ����" << endl;
	gotoxy(x, y + 3);	//36, 20
	cout << "�Һ��ڰ��� ����" << endl;
	gotoxy(x, y + 4);	//36, 22
	cout << "���� ȭ��" << endl;
	gotoxy(x - 7, y + 5);	//36, 25
	cout << "������������������������������������������������������" << endl << endl;

	//�޴�����
	while (true) {	
		int n = keyControl();
		switch (n) {
		case UP:	
			if (y > 12) {	
				gotoxy(x - 2, y);	
				cout << " ";	
				gotoxy(x - 2, --y);	
				cout << ">";	
			}
			else if (y == 12) {
				gotoxy(x - 2, y);
				cout << " ";
				y = 16;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	
			if (y < 16) {	
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);	
				cout << ">";
			}
			else if (y == 16) {
				gotoxy(x - 2, y);
				cout << " ";
				y = 12;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case ENTER:	
			return y - 12;	
		}
	}
}
int Manager::m_updateQuery() {
	system("cls");
	
	while (true) {
		//�޴� ���� -> �Լ�
		int select = m_updateMenu();
		if (select == 0) updateQueryAllCheck();
		else if (select == 1)updateQueryProductName();
		else if (select == 2) updateQueryProductPrice();
		else if (select == 3) updateQueryCustomerPrice();
		else if (select == 4) {
			break;
		}
	}
	return 0;
}

//manager�԰�
int Manager::m_warehousing() {
	char productName[30];
	char addAmount[10];
	bool warehousingCheck= 0;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;

	while (true) {
		system("cls");

		selectQuery();

		mysql_init(&conn);
		mysql_set_character_set(connection, "euckr");
		connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
		mysql_set_character_set(connection, "euckr");
		if (connection == NULL) {
			printf("�����ͺ��̽����� ������ ���������ϴ�.");
			return 1;
		}

		cout << "��ǰ�� : ";
		fgets(productName, 30, stdin);
		CHOP(productName);

		cout << "�԰��� ��ǰ ���� : ";
		fgets(addAmount, 10, stdin);
		CHOP(addAmount);

		query_stat = mysql_query(connection, "select * from product");
		if (query_stat != 0) {
			printf("���� �ҷ��� �� �����ϴ�.(select)");
			//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
			return 1;
		}

		sql_result = mysql_store_result(connection);
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
			//printf("%s", sql_row[0]);
			if (!strcmp(sql_row[0], productName)) {
				warehousingCheck = 1;
				sprintf(query, "UPDATE product SET quantity = quantity + %d WHERE productName = '%s'", stoi(addAmount), productName);
				query_stat = mysql_query(connection, query);
				if (query_stat != 0) {
					//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
					fprintf(stdout, "update�� ������� �ʽ��ϴ�.(�԰� �Ұ�)");
					return 1;
				}
				system("cls");
				selectQuery();
				cout << "�԰� �Ϸ� �Ǿ����ϴ�." << endl;
			}
		}

		if (warehousingCheck == 0) {
			printf("�Է��� ǰ���� �������� �ʽ��ϴ�.");
		}

		mysql_free_result(sql_result);
		mysql_close(connection);

		if (keyControl() == TAB) {
			break;
		}
	}
	return 0;
}
//manager���
int Manager::m_release() {
	char productName[30];
	char minusAmount[10];

	bool warehousingCheck = 0;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;

	while (true) {
		system("cls");

		selectQuery();

		mysql_init(&conn);
		mysql_set_character_set(connection, "euckr");
		connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
		mysql_set_character_set(connection, "euckr");
		if (connection == NULL) {
			printf("�����ͺ��̽����� ������ ���������ϴ�.");
			return 1;
		}

		cout << "��ǰ�� : ";
		fgets(productName, 30, stdin);
		CHOP(productName);

		cout << "����� ��ǰ ���� : ";
		fgets(minusAmount, 10, stdin);
		CHOP(minusAmount);

		query_stat = mysql_query(connection, "select * from product");
		if (query_stat != 0) {
			printf("���� �ҷ��� �� �����ϴ�.(select)");
			//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
			return 1;
		}

		sql_result = mysql_store_result(connection);
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
			//printf("%s", sql_row[0]);
			if (!strcmp(sql_row[0], productName)) {
				warehousingCheck = 1;
				sprintf(query, "UPDATE product SET quantity = quantity - %d WHERE productName = '%s'", stoi(minusAmount), productName);
				query_stat = mysql_query(connection, query);
				if (query_stat != 0) {
					//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
					fprintf(stdout, "update�� ������� �ʽ��ϴ�.(��� �Ұ�)");
					return 1;
				}
				system("cls");
				selectQuery();
				cout << "��� �Ϸ� �Ǿ����ϴ�." << endl;
			}
		}

		if (warehousingCheck == 0) {
			printf("�Է��� ǰ���� �������� �ʽ��ϴ�.");
		}

		mysql_free_result(sql_result);
		mysql_close(connection);

		if (keyControl() == TAB) {
			break;
		}
	}
	return 0;
}

//manager title ����ϱ�
void Manager::managerTitle() {
	int x = 9, y = 7;
	gotoxy(5, y - 3); cout << "============================================================================================================";
	gotoxy(x, y++); cout << "##       ##        #        #######     ########";
	gotoxy(x, y++); cout << "####   ####      ## ##      ##    ##       ##";
	gotoxy(x, y++); cout << "##  ###  ##     ##   ##     #######        ##";
	gotoxy(x, y++); cout << "##   #   ##    #########    ##    ##       ##";
	gotoxy(x, y++); cout << "##       ##   ##       ##   ##     ##      ##";
	gotoxy(x, y); cout << "##       ##   ##       ##   ##     ##      ##";

	x = 18, y = 15;
	gotoxy(x, y++); cout << "##       ##        #        ##       ##        #          #######     ##########   #######";
	gotoxy(x, y++); cout << "####   ####      ## ##      ####     ##      ## ##       ##           ##           ##    ##";
	gotoxy(x, y++); cout << "##  ###  ##     ##   ##     ##  ##   ##     ##   ##     ##            ########     #######";
	gotoxy(x, y++); cout << "##   #   ##    #########    ##    ## ##    #########    ##    ####    ##           ##    ##";
	gotoxy(x, y++); cout << "##       ##   ##       ##   ##      ###   ##       ##    ##      ##   ##           ##     ##";
	gotoxy(x, y); cout << "##       ##   ##       ##   ##       ##   ##       ##     ########    ##########   ##     ##";
	gotoxy(5, y + 3); cout << "============================================================================================================";
}

//manager�޴�����
int Manager::managerMenu() {
	int x = 56;
	int y = 12;

	//�޴����
	gotoxy(x - 6, y - 1); //30, 16
	cout << "������������������������������������������" << endl;
	gotoxy(x - 2, y);	//34, 17
	cout << "> ��ǰ ���" << endl;
	gotoxy(x, y + 1);	//36, 18
	cout << "ǰ�� �߰�" << endl;
	gotoxy(x, y + 2);	//36, 19
	cout << "ǰ�� ����" << endl;
	gotoxy(x, y + 3);	//36, 20
	cout << "ǰ�� ����" << endl;
	gotoxy(x, y + 4);	//36, 20
	cout << " ��   ��  " << endl;
	gotoxy(x, y + 5);	//36, 21
	cout << " ��   ��" << endl;
	gotoxy(x, y +6);	//36, 22
	cout << "���� ȭ��" << endl;
	gotoxy(x - 6, y + 7);	//36, 25
	cout << "������������������������������������������" << endl << endl;

	//�޴�����
	while (true) {	//���� �ݺ�
		int n = keyControl();
		switch (n) {
		case UP:	//�踦 ������ ���
			if (y > 12) {	//y�� 12~18���̸� �̵� -> 12���� Ŀ����
				gotoxy(x - 2, y);	//���� ���ۿ� �ִ� >
				cout << " ";	//�����
				gotoxy(x - 2, --y);	//�������� 1ĭ �̵���
				cout << ">";	//�ٽ� �׸���
			}
			else if (y == 12) {	//�� �� -> �� �Ʒ��� �̵�
				gotoxy(x - 2, y);
				cout << " ";
				y = 18;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	//�鸦 ������ ���
			if (y < 18) {	//y�� 12~18���̸� �̵� -> 18���� �۾ƾ���
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);	//�Ʒ������� 1ĭ �̵���
				cout << ">";
			}
			else if (y == 18) {	//�� �Ʒ� -> �� ���� �̵�
				gotoxy(x - 2, y);
				cout << " ";
				y = 12;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case ENTER:	//���� -> �������� ���
			return y - 12;	//y-12�� �Ͽ� �� ���� ���� 1, 2, 3...���� ���� �� �ִ�. -> �� ����
		}
	}
}

int Manager::totalSelect() {
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	int totalCheck = 0;

	mysql_init(&conn);

	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);   
	mysql_set_character_set(connection, "euckr");
	if (connection == NULL) {
		//fprintf(stderr, "Mysql connection error : %s\n", mysql_error(&conn));
		printf("�����ͺ��̽����� ������ ���������ϴ�.");
		return 1;
	}

	query_stat = mysql_query(connection, "select * from total");
	if (query_stat != 0) {
		printf("���� �ҷ��� �� �����ϴ�.(select)");
		//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
		return 1;
	}

	sql_result = mysql_store_result(connection);
	if (sql_result == NULL) {
		cout << "Empty!!" << endl;
	}
	else {
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
			return stoi(sql_row[1]);
		}
	}
	return 0;
	mysql_free_result(sql_result);
}

//manager����
void Manager::managerMain() {
	system("cls");
	managerTitle();
	Sleep(2000);
	init();
	

	while (true) {
		system("cls");
		gotoxy(0, 0);
		printf("���� �� ���� : %d", totalSelect());
		cout << endl;
		//�޴� ���� -> �Լ�
		int select = managerMenu();
		if (select == 0) productList();
		else if (select == 1)m_insertQuery();
		else if (select == 2) m_deleteQuery();
		else if (select == 3) m_updateQuery();
		else if (select == 4) m_warehousing();	//�԰�
		else if (select == 5) m_release();		//���
		else if (select == 6) {
			gotoxy(20, 15);  break;
		}
	}
	return;
}


//--------------------------------------------- CUSTOMER �Լ� -----------------------------------------------------

//īƮ ��� ǰ�� ����Ʈ 
int Customer::CartList() {
	system("cls");
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	int cartCount = 1;
	mysql_init(&conn);

	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	mysql_set_character_set(connection, "euckr");
	if (connection == NULL) {
		printf("�����ͺ��̽����� ������ ���������ϴ�.");
		return 1;
	}

	string TCN = "select * from cart_" + tableName + " order by quantity asc";
	const char* seletetableCartName = TCN.c_str();

	query_stat = mysql_query(connection, seletetableCartName);
	if (query_stat != 0) {
		printf("���� �ҷ��� �� �����ϴ�.(select)");
		return 1;
	}

	sql_result = mysql_store_result(connection);
	if (sql_result == NULL) {
		cout << "Empty!!" << endl;
	}
	else {
		printf("������������������������������������������������������������������������������������������������\n");
		printf("�� %3s �� %-16s �� %8s �� %8s ��\n", "ID", "��ǰ��", "����", "����");
		printf("������������������������������������������������������������������������������������������������\n");
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
			if (stoi(sql_row[2]) == 0) {
				sprintf(query, "delete from %s where productName='%s'", tableCartName, sql_row[0]);
				query_stat = mysql_query(connection, query);
				continue;
			}
			printf("�� %3d �� %-16s �� %8d �� %8d ��\n", cartCount++, sql_row[0], stoi(sql_row[1]), stoi(sql_row[2]));
			cart_Count++;
		}
		printf("������������������������������������������������������������������������������������������������\n");

	}

	mysql_free_result(sql_result);
}

//��ٱ��� ����Ʈ
int Customer::CartListMenu() {
	system("cls");
	CartList();
	if (keyControl() == TAB) {
		return 0;
	}
}

//īƮ�� ��ǰ �߰� => �Һ��� ���� �������
int Customer::addShoppingCart() {
	char productName[30];
	int customerPrice;
	char quantity[10];
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	int addCheck = 0;

	while (true) {
		system("cls");
		selectQuery();

		mysql_init(&conn);

		connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
		mysql_set_character_set(connection, "euckr");
		if (connection == NULL) {
			printf("�����ͺ��̽����� ������ ���������ϴ�.");
			Sleep(2000);
			return 1;
		}

		printf("��ǰ�� : ");
		fgets(productName, 30, stdin);
		CHOP(productName);


		printf("��ǰ���� : ");
		fgets(quantity, 10, stdin);
		CHOP(quantity);

		string TCN = "select * from cart_" + tableName;
		const char* selecttableCartName = TCN.c_str();

		query_stat = mysql_query(connection, selecttableCartName);
		if (query_stat != 0) {
			printf("���� �ҷ��� �� �����ϴ�.(select)");
			Sleep(2000);
			return 1;
		}

		sql_result = mysql_store_result(connection);

		if (sql_result == NULL) {
			cout << "Empty!!" << endl;
		}
		else {
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				if (!strcmp(sql_row[0], productName)) {
					customerPrice = stoi(sql_row[1]);

					sprintf(query, "UPDATE %s set quantity = quantity + %d WHERE productName='%s'", tableCartName, stoi(quantity), productName);
					query_stat = mysql_query(connection, query);

					sprintf(query, "UPDATE product SET quantity = quantity- %d WHERE productName = '%s'", stoi(quantity), productName);
					query_stat = mysql_query(connection, query);

					if (query_stat != 0) {
						printf("���� �߰��� �� �����ϴ�.");
						Sleep(2000);
						return 1;
					}
					system("cls");
					CartList();
					cout << "��ٱ��Ͽ� ��ǰ�� �����ϴ�." << endl;
					cout << "3�ʵ� �ڵ����� ����ȭ������ �Ѿ�ϴ�..." << endl;
					Sleep(3000);

					mysql_free_result(sql_result);
					mysql_close(connection);
					
					return 0;

				}
			}
		}

		query_stat = mysql_query(connection, "select * from product");
		if (query_stat != 0) {
			printf("���� �ҷ��� �� �����ϴ�.(select)");
			Sleep(2000);
			return 1;
		}

		sql_result = mysql_store_result(connection);

		if (sql_result == NULL) {
			cout << "Empty!!" << endl;
		}
		else {
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				if (!strcmp(sql_row[0], productName)) {
					customerPrice = stoi(sql_row[2]);
					addCheck = 1;
					sprintf(query, "insert into %s (productName, customerPrice, quantity, total) values ('%s', '%d', '%d', %d)", tableCartName, productName, customerPrice, stoi(quantity), customerPrice*stoi(quantity));
					query_stat = mysql_query(connection, query);

					sprintf(query, "UPDATE product SET quantity = quantity- %d WHERE productName = '%s'", stoi(quantity), productName);
					query_stat = mysql_query(connection, query);

					if (query_stat != 0) {
						printf("���� �߰��� �� �����ϴ�.");
						Sleep(2000);
						return 1;
					}
					system("cls");
					CartList();
					cart_Count++;
					cout << "��ٱ��Ͽ� ��ǰ�� �����ϴ�." << endl;
				}
			}
			if (addCheck == 0) {
				printf("�Է��� ǰ���� �������� �ʽ��ϴ�.");
			}

		}
		
		mysql_free_result(sql_result);
		mysql_close(connection);

		if (keyControl() == TAB) {
			return 0;
		}
	}

}

//ǰ�� �ƿ� ����
int Customer::delCartProduct() {
	char productName[30];
	int customerPrice;
	int quantity;
	bool delCount = 0;

	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	while (true) {
		system("cls");
		CartList();

		mysql_init(&conn);

		connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
		mysql_set_character_set(connection, "euckr");
		if (connection == NULL) {
			printf("�����ͺ��̽����� ������ ���������ϴ�.");
			return 1;
		}

		printf("��ǰ�� : ");
		fgets(productName, 30, stdin);
		CHOP(productName);

		//��ǰ���� -> product table���� ��������
		query_stat = mysql_query(connection, "select * from product");
		if (query_stat != 0) {
			printf("���� �ҷ��� �� �����ϴ�.(select)");
			Sleep(2000);
			return 1;
		}

		sql_result = mysql_store_result(connection);

		if (sql_result == NULL) {
			cout << "Empty!!" << endl;
			Sleep(2000);
		}
		else {
			system("cls");
			cout << "���� ǰ���� �����Ͻðڽ��ϱ�?";
			if (YN_Check(2, 2) == 0) {	//yes


				while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
					if (!strcmp(sql_row[0], productName)) {
						delCount = 1;
						customerPrice = stoi(sql_row[2]);
						quantity = stoi(sql_row[3]);

						sprintf(query, "delete from %s where productName='%s'", tableCartName, productName);
						query_stat = mysql_query(connection, query);

						sprintf(query, "UPDATE product SET quantity = quantity + %d WHERE productName = '%s'", quantity, productName);
						query_stat = mysql_query(connection, query);

						if (query_stat != 0) {
							printf("���� ������ �� �����ϴ�.(delete)");
							Sleep(2000);
							return 1;
						}
						cart_Count--;
						system("cls");
						CartList();
						cout << "��ٱ����� ��ǰ ������ �Ϸ� �Ǿ����ϴ�." << endl;
					}
				}
				mysql_free_result(sql_result);
				mysql_close(connection);
				if (delCount == 0) {
					cout << "��ġ�ϴ� ǰ���� �����ϴ�.";
				}
			}
			else {
				system("cls");
				CartList();
				cout << "��ǰ ������ ��ҵǾ����ϴ�." << endl;
			}
		}
		if (keyControl() == TAB) {
			return 0;
		}
	}
}

//��ü ���� => ���� ���� ���� �ʿ�
int Customer::deleteAll() {
	int customerPrice;
	int quantity;

	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;

	mysql_init(&conn);

	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	mysql_set_character_set(connection, "euckr");
	if (connection == NULL) {
		printf("�����ͺ��̽����� ������ ���������ϴ�.");
		return 1;
	}
	system("cls");
	if (cart_Count == 0) {
		cout << "īƮ�� ������ ǰ���� �����ϴ�." << endl;
	}
	else {
		string TCN = "select * from cart_" + tableName;
		const char* seletetableCartName = TCN.c_str();

		query_stat = mysql_query(connection, seletetableCartName);
		if (query_stat != 0) {
			printf("���� �ҷ��� �� �����ϴ�.(select)");
			Sleep(2000);
			return 1;
		}
		sql_result = mysql_store_result(connection);

		CartList();

		// �ܼ� ���â�� ������ ��� ���ؼ� ������ ����ü
		CONSOLE_SCREEN_BUFFER_INFO presentCur;

		//���� �ܼ� ��ġ ��ȯ
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);

		cout << "���� ��ٱ��� �� ��ǰ�� ��� �����Ͻðڽ��ϱ�?";

		if (YN_Check(2, presentCur.dwCursorPosition.Y + 2) == 0) {
			

			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
					customerPrice = stoi(sql_row[1]);
					quantity = stoi(sql_row[2]);

					sprintf(query, "UPDATE product SET quantity = quantity + %d WHERE productName = '%s'", quantity, sql_row[0]);
					query_stat = mysql_query(connection, query);

					if (query_stat != 0) {
						printf("���� ������ �� �����ϴ�.(update)");
						Sleep(2000);
						return 1;
					}			
			}
			sprintf(query, "delete from %s;", tableCartName);
			query_stat = mysql_query(connection, query);
			system("cls");
			CartList();
			cout << "��ٱ����� ��� ��ǰ�� �����Ǿ����ϴ�." << endl;
			cart_Count = 0;

		}
		else {
			system("cls");
			CartList();
			cout << "������ ��ҵǾ����ϴ�." << endl;
		}

		mysql_close(connection);
	}
	
	if (keyControl() == TAB) {
		return 0;
	}

}
 
//īƮ ���� �޴�
int Customer::deleteCartMenu() {
	system("cls");
	int x = 56, y = 12;
	//�޴����
	gotoxy(x - 6, y - 1);	
	cout << "������������������������������������������";
	gotoxy(x - 2, y);	
	cout << "> ǰ�� ����" << endl;
	gotoxy(x, y + 2);	
	cout << "��ü ����" << endl;
	gotoxy(x, y + 4);	
	cout << "���� ȭ��" << endl;
	gotoxy(x - 6, y + 5);	
	cout << "������������������������������������������";

	while (true) {	
		int n = keyControl();
		switch (n) {
		case UP:	
			if (y > 12) {	
				gotoxy(x - 2, y);	
				cout << " ";	
				gotoxy(x - 2, y-=2);	
				cout << ">";	
			}
			else if (y == 12) {	
				gotoxy(x - 2, y);
				cout << " ";
				y = 16;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	
			if (y < 16) {	
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, y+=2);	
				cout << ">";
			}
			else if (y == 16) {	
				gotoxy(x - 2, y);
				cout << " ";
				y = 12;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case ENTER:	
			return y - 12;	
		}
	}
}

//īƮ ����
void Customer::deleteCart() {
	switch (deleteCartMenu()) {
	case 0: delCartProduct(); break;
	case 2: deleteAll(); break;
	case 4:  break;
	}
}

//�����߰�
int Customer::updatePlusCartQuantity() {
	CartList();
	char productName[30];
	char minusQuantity[10];
	int customerPrice;
	int delCheck = 0;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;

	while (true) {
		system("cls");
		CartList();

		mysql_init(&conn);

		connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
		mysql_set_character_set(connection, "euckr");
		if (connection == NULL) {
			printf("�����ͺ��̽����� ������ ���������ϴ�.");
			return 1;
		}

		printf("��ǰ�� : ");
		fgets(productName, 30, stdin);
		CHOP(productName);

		printf("�߰� ���� : ");
		fgets(minusQuantity, 10, stdin);
		CHOP(minusQuantity);


		query_stat = mysql_query(connection, "select * from product");
		if (query_stat != 0) {
			printf("���� �ҷ��� �� �����ϴ�.(select)");
			Sleep(2000);
			return 1;
		}

		sql_result = mysql_store_result(connection);

		if (sql_result == NULL) {
			cout << "Empty!!" << endl;
		}
		else {
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				if (!strcmp(sql_row[0], productName)) {
					delCheck = 1;
					customerPrice = stoi(sql_row[2]);

					sprintf(query, "UPDATE %s SET quantity = quantity + %d WHERE productName = '%s'", tableCartName,  stoi(minusQuantity), productName);
					query_stat = mysql_query(connection, query);

					sprintf(query, "UPDATE product SET quantity = quantity - %d WHERE productName = '%s'", stoi(minusQuantity), productName);
					query_stat = mysql_query(connection, query);
					if (query_stat != 0) {
						printf("update�� ��ҵǾ����ϴ�.");
						Sleep(2000);
						return 1;
					}
					system("cls");
					CartList();
					cout << "��ٱ��� ��ǰ�� ������ �߰��Ǿ����ϴ�." << endl;
					break;
				}
			}

			if (delCheck == 0) {
				printf("�Է��� ǰ���� �������� �ʽ��ϴ�.");
			}

		}
		mysql_free_result(sql_result);
		mysql_close(connection);
		if (keyControl() == TAB) {
			return 0;
		}
	}

}

//���� ����
int Customer::updateMinusCartQuantity() {
	CartList();
	char productName[30];
	char minusQuantity[10];
	int customerPrice;
	int delCheck = 0;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;

	while (true) {
		system("cls");
		CartList();

		mysql_init(&conn);

		connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
		mysql_set_character_set(connection, "euckr");
		if (connection == NULL) {
			printf("�����ͺ��̽����� ������ ���������ϴ�.");
			return 1;
		}

		printf("��ǰ�� : ");
		fgets(productName, 30, stdin);
		CHOP(productName);

		printf("���� ���� : ");
		fgets(minusQuantity, 10, stdin);
		CHOP(minusQuantity);

		query_stat = mysql_query(connection, "select * from product");
		if (query_stat != 0) {
			printf("���� �ҷ��� �� �����ϴ�.(select)");
			Sleep(2000);
			return 1;
		}

		sql_result = mysql_store_result(connection);

		if (sql_result == NULL) {
			cout << "Empty!!" << endl;
		}
		else {
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				if (!strcmp(sql_row[0], productName)) {
					delCheck = 1;
					customerPrice = stoi(sql_row[2]);

					sprintf(query, "UPDATE %s SET quantity = quantity - %d WHERE productName = '%s'", tableCartName, stoi(minusQuantity), productName);
					query_stat = mysql_query(connection, query);

					sprintf(query, "UPDATE product SET quantity = quantity + %d WHERE productName = '%s'", stoi(minusQuantity), productName);
					query_stat = mysql_query(connection, query);
					if (query_stat != 0) {
						printf("update�� ��ҵǾ����ϴ�.");
						Sleep(2000);
						return 1;
					}
					system("cls");
					CartList();
					cout << "��ٱ��� ��ǰ�� ������ ���ҵǾ����ϴ�." << endl;
					break;
				}
			}

			if (delCheck == 0) {
				printf("�Է��� ǰ���� �������� �ʽ��ϴ�.");
			}

		}
		mysql_free_result(sql_result);
		mysql_close(connection);
		if (keyControl() == TAB) {
			return 0;
		}
	}

}

//īƮ ���� �޴�
int Customer::updateCartMenu() {
	system("cls");
	int x = 56, y = 12;
	//�޴����
	gotoxy(x - 6, y - 1);	
	cout << "������������������������������������������";
	gotoxy(x - 2, y);	
	cout << "> ���� �߰�" << endl;
	gotoxy(x, y + 2);	
	cout << "���� ����" << endl;
	gotoxy(x, y + 4);	
	cout << "���� ȭ��" << endl;
	gotoxy(x - 6, y + 5);	
	cout << "������������������������������������������";

	while (true) {	
		int n = keyControl();
		switch (n) {
		case UP:	
			if (y > 12) {	
				gotoxy(x - 2, y);	
				cout << " ";	
				gotoxy(x - 2, y-=2);	
				cout << ">";	
			}
			else if (y == 12) {	
				gotoxy(x - 2, y);
				cout << " ";
				y = 16;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	
			if (y < 16) {	
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, y+=2);	
				cout << ">";
			}
			else if (y == 16) {
				gotoxy(x - 2, y);
				cout << " ";
				y = 12;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case ENTER:	
			return y - 12;	
		}
	}
}

//īƮ ��ǰ ����
void Customer::UpdateCart() {
	switch (updateCartMenu()) {
	case 0: updatePlusCartQuantity(); break;
	case 2: updateMinusCartQuantity(); break;
	case 4:  break;
	}
}

//����
int Customer::buy() {
	system("cls");
	int cart_Total = 0;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	int query_state_history;
	MYSQL_RES* sql_result_history;
	MYSQL_ROW sql_row_history;

	mysql_init(&conn);

	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	mysql_set_character_set(connection, "euckr");
	if (connection == NULL) {
		printf("�����ͺ��̽����� ������ ���������ϴ�.");
		Sleep(2000);
		return 1;
	}

	string TCN = "select * from cart_" + tableName;
	const char* seletetableCartName = TCN.c_str();

	query_stat = mysql_query(connection, seletetableCartName);

	if (query_stat != 0) {
		printf("���� �ҷ��� �� �����ϴ�.(select)");
		Sleep(2000);
		return 1;
	}
	sql_result = mysql_store_result(connection);

	
	if (cart_Count == 0) {
		cout << "īƮ�� ������ ǰ���� �����ϴ�." << endl;
		Sleep(2000);
		return 0;
	}
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
		
		cart_Total += stoi(sql_row[3]);

		if (query_stat != 0) {
			printf("�ֹ� ������ �߰��� �� �����ϴ�.");
			Sleep(2000);
			return 1;
		}
	}
	CartList();
	printf("������������������������������������������������������������������������������������������������\n");
	printf("��  ����  �� %35d ��\n", cart_Total);
	printf("������������������������������������������������������������������������������������������������\n");
	// �ܼ� ���â�� ������ ��� ���ؼ� ������ ����ü
	CONSOLE_SCREEN_BUFFER_INFO presentCur;

	//���� �ܼ� ��ġ ��ȯ
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);

	cout << endl << "���� ���� �Ͻðڽ��ϱ�?" << endl;

	query_stat = mysql_query(connection, seletetableCartName);
	sql_result = mysql_store_result(connection);

	if (YN_Check(2, presentCur.dwCursorPosition.Y + 2) == 0) {
		if (sql_result == NULL) {
			cout << "Empty!!" << endl;
			Sleep(2000);
			return 0;
		}
		else {
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				sprintf(query, "insert into %s (history, date, productName, customerprice, quantity) values ('buy', now(), '%s', %d , %d)", tableHistoryName, sql_row[0], stoi(sql_row[1]), stoi(sql_row[2]));
				query_stat = mysql_query(connection, query);

				sprintf(query, "UPDATE total SET managerTotal = managerTotal + %d WHERE id = 1", cart_Total);
				query_stat = mysql_query(connection, query);

				if (query_stat != 0) {
					//printf("\n\n���� ������ �߰��� �� �����ϴ�.");
					fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
					Sleep(2000);
					return 1;
				}
			}

		}
		sprintf(query, "delete from %s;", tableCartName);
		query_stat = mysql_query(connection, query);

		if (query_stat != 0) {
			printf("���� ������ �� �����ϴ�.(delete)");
			Sleep(2000);
			return 1;
		}

		cart_Count = 0;

		system("cls");
		cout << "���Ű� �Ϸ�Ǿ����ϴ�." << endl;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
		cout << "���ݱ����� �ֹ������� ���ðڽ��ϱ�?" << endl;
		if (YN_Check(2, presentCur.dwCursorPosition.Y + 2) == 0) {
			system("cls");

			string THN = "select * from history_" + tableName;
			const char* seletetableHistoryName = THN.c_str();

			query_stat = mysql_query(connection, seletetableHistoryName);
			if (query_stat != 0) {
				printf("���� �ҷ��� �� �����ϴ�.(select)");
				return 1;
			}

			sql_result = mysql_store_result(connection);
			if (sql_result == NULL) {
				cout << "Empty!!" << endl;
			}
			else {
				printf("������������������������������������������������������������������������������������������������������������������������������������������������\n");
				printf("�� %8s �� %16s �� %-16s �� %8s �� %8s ��\n", "���ſ���", "��¥", "��ǰ��", "����", "����");
				printf("������������������������������������������������������������������������������������������������������������������������������������������������\n");
				while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
					printf("�� %8s �� %16s �� %-16s �� %8d �� %8d ��\n", sql_row[0], sql_row[1], sql_row[2], stoi(sql_row[3]), stoi(sql_row[4]));	//���
				}
				printf("������������������������������������������������������������������������������������������������������������������������������������������������\n");

			}
		}
		else {
			system("cls");
			cout << "�������� ������ �Ͻø� TABŰ�� �����ּ���.." << endl;
		}
		mysql_free_result(sql_result);
		mysql_close(connection);
	}
	else {
		system("cls");
		cout << "��������� ��ǰ�� �����մϴ�." << endl;
	}
	

	if (keyControl() == TAB) {
		return 0;
	}
}

//ȯ��
int Customer::refund() {
	char productName[30];
	char refund_reason[100];
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	int refundCheck = 0;

	while (true) {
		system("cls");
		refundCheck = 0;
		mysql_init(&conn);

		connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
		mysql_set_character_set(connection, "euckr");

		if (connection == NULL) {
			printf("�����ͺ��̽����� ������ ���������ϴ�.");
			return 1;
		}

		string THN = "select * from history_" + tableName;
		const char* seletetableHistoryName = THN.c_str();

		query_stat = mysql_query(connection, seletetableHistoryName);
		if (query_stat != 0) {
			printf("���� �ҷ��� �� �����ϴ�.(select)");
			return 1;
		}

		sql_result = mysql_store_result(connection);

		printf("��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
		printf("�� %8s �� %10s �� %16s �� %8s �� %48s ��\n", "�ֹ�", "��¥", "��ǰ��", "����", "ȯ�� ����");
		printf("��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
			if (sql_row[5] == NULL) {
				printf("�� %8s �� %10s �� %16s �� %8d �� %48s ��\n", sql_row[0], sql_row[1], sql_row[2], stoi(sql_row[4]), "");	//���
			}
			else {
				printf("�� %8s �� %10s �� %16s �� %8d �� %48s ��\n", sql_row[0], sql_row[1], sql_row[2], stoi(sql_row[4]), sql_row[5]);	//���
			}
		}
		printf("��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");


		printf("��ǰ�� : ");
		fgets(productName, 30, stdin);
		CHOP(productName);

		printf("ȯ�һ���(100�� �̳�) : ");
		fgets(refund_reason, 100, stdin);
		CHOP(refund_reason);

		// �ܼ� ���â�� ������ ��� ���ؼ� ������ ����ü
		CONSOLE_SCREEN_BUFFER_INFO presentCur;

		//���� �ܼ� ��ġ ��ȯ
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);

		cout << endl << "���� ȯ�� �Ͻðڽ��ϱ�?" << endl;

		query_stat = mysql_query(connection, seletetableHistoryName);
		sql_result = mysql_store_result(connection);
		if (YN_Check(2, presentCur.dwCursorPosition.Y + 2) == 0) {
			if (sql_result == NULL) {
				cout << "Empty!!" << endl;
				Sleep(2000);
			}
			else {
				while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
					//printf("%s, %s, %d\n", sql_row[0], sql_row[2], stoi(sql_row[4]));
					if (!strcmp(sql_row[0], "buy")) {
						refundCheck = 2;
						if (!strcmp(sql_row[2], productName)) {
							sprintf(query, "update %s set history = 'refund', date = now(), refund_reason='%s' where productName='%s' limit 1", tableHistoryName, refund_reason, productName);
							query_stat = mysql_query(connection, query);
							if (query_stat != 0) {
								printf("\n\nȯ�� ������ �߰��� �� �����ϴ�.");
								//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
								Sleep(2000);
								return 1;
							}
							sprintf(query, "UPDATE total SET managerTotal = managerTotal - %d WHERE id = 1", stoi(sql_row[3]) * stoi(sql_row[4]));
							query_stat = mysql_query(connection, query);
							if (query_stat != 0) {
								printf("\n\n������ �߰� �� �� �����ϴ�.");
								//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
								Sleep(2000);
								return 1;
							}
							sprintf(query, "UPDATE product SET quantity = quantity + %d WHERE productName = '%s'", stoi(sql_row[4]), productName);
							query_stat = mysql_query(connection, query);

							if (query_stat != 0) {
								printf("\n\n��ǰ ������ �߰��� �� �����ϴ�.");
								//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
								Sleep(2000);
								return 1;
							}
							refundCheck = 3;
							break;
						}
					}
				}
			}
			system("cls");
			switch (refundCheck) {
			case 1: 
				cout << "�ֹ� �̷��� �����ϴ�." << endl; 
				cout << "3�ʵ� �ڵ����� ����ȭ������ �̵��մϴ�..." << endl;
				Sleep(3000);
				return 0;
			case 2: cout << "�ش��ϴ� ��ǰ�� �����ϴ�." << endl; 
				cout << "3�ʵ� �ڵ����� ����ȭ������ �̵��մϴ�..." << endl;
				Sleep(3000);
				return 0;
			case 3: cout << "ȯ���� �Ϸ�Ǿ����ϴ�." << endl << endl;
				Sleep(1000); break;
			}

			
			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
			cout << "���ݱ����� �ֹ������� ���ðڽ��ϱ�?" << endl;
			if (YN_Check(2, presentCur.dwCursorPosition.Y + 2) == 0) {
				system("cls");
				string THN = "select * from history_" + tableName;
				const char* seletetableHistoryName = THN.c_str();

				query_stat = mysql_query(connection, seletetableHistoryName);
				if (query_stat != 0) {
					printf("���� �ҷ��� �� �����ϴ�.(select)");
					return 1;
				}

				sql_result = mysql_store_result(connection);
				if (sql_result == NULL) {
					cout << "Empty!!" << endl;
				}
				else {
					printf("��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
					printf("�� %8s �� %10s �� %16s �� %8s �� %48s ��\n", "�ֹ�", "��¥", "��ǰ��", "����", "ȯ�� ����");
					printf("��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
						if (sql_row[5] == NULL) {
							printf("�� %8s �� %10s �� %16s �� %8d �� %48s ��\n", sql_row[0], sql_row[1], sql_row[2], stoi(sql_row[4]), "");	//���
						}
						else {
							printf("�� %8s �� %10s �� %16s �� %8d �� %48s ��\n", sql_row[0], sql_row[1], sql_row[2], stoi(sql_row[4]), sql_row[5]);	//���
						}
					}
					printf("��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
				}
			}
			else {
				system("cls");
				cout << "�������� ������ �Ͻø� TABŰ�� �����ּ���.." << endl;
			}

			mysql_free_result(sql_result);
			mysql_close(connection);
		}

		else {
			system("cls");
			cout << "ȯ���� ����մϴ�." << endl;
		}

		if (keyControl() == TAB) {
			return 0;
		}
	}
}

//�ֹ� ���� ����Ʈ
int Customer::historyList() {
	system("cls");
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	int cartCount = 1;
	mysql_init(&conn);

	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	mysql_set_character_set(connection, "euckr");
	if (connection == NULL) {
		printf("�����ͺ��̽����� ������ ���������ϴ�.");
		return 1;
	}

	string THN = "select * from history_" + tableName;
	const char* seletetableHistoryName = THN.c_str();

	query_stat = mysql_query(connection, seletetableHistoryName);
	if (query_stat != 0) {
		printf("���� �ҷ��� �� �����ϴ�.(select)");
		return 1;
	}

	sql_result = mysql_store_result(connection);
	if (sql_result == NULL) {
		cout << "Empty!!" << endl;
	}
	else {
		printf("������������������������������������������������������������������������������������������������������������������������������������������������\n");
		printf("�� %8s �� %16s �� %-16s �� %8s �� %8s ��\n", "���ſ���", "��¥", "��ǰ��", "����", "����");
		printf("������������������������������������������������������������������������������������������������������������������������������������������������\n");
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
			printf("�� %8s �� %16s �� %-16s �� %8d �� %8d ��\n", sql_row[0], sql_row[1], sql_row[2], stoi(sql_row[3]), stoi(sql_row[4]));	//���
		}
		printf("������������������������������������������������������������������������������������������������������������������������������������������������\n");

	}
	mysql_free_result(sql_result);

	if (keyControl() == TAB) {
		return 0;
	}
}

//customer title ����ϱ�
void Customer::customerTitle() {
	int x = 10, y = 7;
	gotoxy(5, y - 3); cout << "============================================================================================================";
	gotoxy(x, y++); cout << "##       ##        #        #######     ########";
	gotoxy(x, y++); cout << "####   ####      ## ##      ##    ##       ##";
	gotoxy(x, y++); cout << "##  ###  ##     ##   ##     #######        ##";
	gotoxy(x, y++); cout << "##   #   ##    #########    ##    ##       ##";
	gotoxy(x, y++); cout << "##       ##   ##       ##   ##     ##      ##";
	gotoxy(x, y);   cout << "##       ##   ##       ##   ##     ##      ##";

	x = 15, y = 15;
	gotoxy(x, y++); cout << "  #######  ##      ##    ######    ########     ####     ##       ##  #########  #######";
	gotoxy(x, y++); cout << "##         ##      ##  ##             ##      ##    ##   ####   ####  ##         ##    ##";
	gotoxy(x, y++); cout << "##         ##      ##    #######      ##     ##      ##  ##  ###  ##  #######    #######";
	gotoxy(x, y++); cout << "##         ##      ##          ##     ##     ##      ##  ##   #   ##  ##         ##    ##"; 
	gotoxy(x, y++); cout << "##         ##      ##          ##     ##      ##    ##   ##       ##  ##         ##     ##";
	gotoxy(x, y);   cout << "  #######    ######     ########      ##        ####     ##       ##  #########  ##     ##";
	gotoxy(5, y + 3); cout << "============================================================================================================";
}

//�޴�����
int Customer::customerMenu() {
	system("cls");
	int x = 56;
	int y = 12;

	//�޴����
	gotoxy(x - 6, y - 1); 
	cout << "������������������������������������������" << endl;
	gotoxy(x - 2, y);	
	cout << "> īƮ ���" << endl;
	gotoxy(x, y + 1);	
	cout << "īƮ �߰�" << endl;
	gotoxy(x, y + 2);	
	cout << "īƮ ����" << endl;
	gotoxy(x, y + 3);	
	cout << "���� ����" << endl;
	gotoxy(x, y + 4);	
	cout << "�ֹ� ����" << endl;
	gotoxy(x, y + 5);	
	cout << "��     ��" << endl;
	gotoxy(x, y + 6);
	cout << "ȯ     ��" << endl;
	gotoxy(x, y + 7);
	cout << "��     ��" << endl;
	gotoxy(x - 6, y + 8);	
	cout << "������������������������������������������" << endl << endl;

	//�޴�����
	while (true) {	
		int n = keyControl();
		switch (n) {
		case UP:	
			if (y > 12) {	
				gotoxy(x - 2, y);	
				cout << " ";	
				gotoxy(x - 2, --y);	
				cout << ">";	
			}
			else if (y == 12) {	
				gotoxy(x - 2, y);
				cout << " ";
				y = 19;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	
			if (y < 19) {	
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);	
				cout << ">";
			}
			else if (y == 19) {	
				gotoxy(x - 2, y);
				cout << " ";
				y = 12;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case ENTER:	
			return y - 12;	
		}
	}
}

//�� ����
void Customer::customerMain() {
	system("cls");
	customerTitle();
	Sleep(2000);
	init();
	while (true) {
		int select = customerMenu();
		if (select == 0) CartListMenu();
		else if (select == 1) addShoppingCart();
		else if (select == 2) deleteCart();
		else if (select == 3) UpdateCart();
		else if (select == 4) historyList(); 
		else if (select == 5) buy(); 
		else if (select == 6) refund();
		else if (select == 7) {
			gotoxy(0, 27); break;
		}
	}
}

//--------------------------------------------------���� �Լ�-----------------------------------------------------
//������ ���
int selectQuery() {
	system("cls");
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	int listCount = 1;
	mysql_init(&conn);

	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);  
	mysql_set_character_set(connection, "euckr");
	if (connection == NULL) {
		//fprintf(stderr, "Mysql connection error : %s\n", mysql_error(&conn));
		printf("�����ͺ��̽����� ������ ���������ϴ�.");
		return 1;
	}

	query_stat = mysql_query(connection, "select * from product");
	if (query_stat != 0) {
		printf("���� �ҷ��� �� �����ϴ�.(select)");
		//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
		return 1;
	}

	sql_result = mysql_store_result(connection);
	if (sql_result == NULL) {
		cout << "Empty!!" << endl;
	}
	else {
		printf("��������������������������������������������������������������������������������������������������������������������������\n");
		printf("�� %3s �� %-16s �� %8s �� %9s �� %8s ��\n", "ID", "��ǰ��", "��ǰ����", "�Һ��ڰ���", "����");
		printf("��������������������������������������������������������������������������������������������������������������������������\n");
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
			if (stoi(sql_row[3]) == 0) {
				sprintf(query, "delete from product where productName='%s'", sql_row[0]);
				query_stat = mysql_query(connection, query);
				continue;
			}
			printf("�� %3d �� %-16s �� %8d �� %10d �� %8d ��\n", listCount++, sql_row[0], stoi(sql_row[1]), stoi(sql_row[2]), stoi(sql_row[3]));	//���
		}
		printf("��������������������������������������������������������������������������������������������������������������������������\n");
	}

	//mysql_store_result�� ���� �޸𸮸� ��ü��Ŵ-> ��ġ malloc�� free����
	mysql_free_result(sql_result);
}


//��ü ���� üũ => �ؾ���
int YN_Check(int x, int y) {
	int cx = x;
	int cy = y;
	//�޴����
	gotoxy(cx - 2, cy);	//34, 17
	cout << "> YES" << endl;
	gotoxy(cx, cy + 1);	//36, 18
	cout << "NO" << endl;

	while (true) {	//���� �ݺ�
		int n = keyControl();
		switch (n) {
		case UP:	//�踦 ������ ���
			if (cy > y) {	//y�� 17~24���̸� �̵� -> 17���� Ŀ����s
				gotoxy(cx - 2, cy);	//���� ���ۿ� �ִ� >
				cout << " ";	//�����
				gotoxy(cx - 2, --cy);	//�������� 1ĭ �̵���
				cout << ">";	//�ٽ� �׸���
			}
			else if (cy == y) {	//�� �� -> �� �Ʒ��� �̵�
				gotoxy(cx - 2, cy);
				cout << " ";
				cy = y + 1;
				gotoxy(cx - 2, cy);
				cout << ">";
			}
			break;

		case DOWN:	//�鸦 ������ ���
			if (cy < y + 1) {	//y�� 17~24���̸� �̵� -> 24���� �۾ƾ���
				gotoxy(cx - 2, cy);
				cout << " ";
				gotoxy(cx - 2, ++cy);	//�Ʒ������� 1ĭ �̵���
				cout << ">";
			}
			else if (cy == y + 1) {	//�� �Ʒ� -> �� ���� �̵�
				gotoxy(cx - 2, cy);
				cout << " ";
				cy = y;
				gotoxy(cx - 2, cy);
				cout << ">";
			}
			break;

		case ENTER:	//���� -> �������� ���
			return cy - y;	//y-17�� �Ͽ� �� ���� ���� 1, 2, 3...���� ���� �� �ִ�. -> �� ����
		}
	}
}

//�ʱ�ȭ�� ����
void init() {
	//�ܼ� ũ�� ���ϱ�
	system("mode con cols=120 lines=30");

	//�����Ÿ��� Ŀ�� �����
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

//��ǥ���
void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x, y };
	SetConsoleCursorPosition(consoleHandle, pos);
}

//����Ű�� ��ǥ �����ϱ�
int keyControl() {
	char tmp = _getch();
	if (tmp == -32) {
		tmp = _getch();
		switch (tmp) {
		case 72:	//��
			return UP; break;
		case 80:	//�Ʒ�
			return DOWN; break;
		case 75:	//����
			return LEFT; break;
		case 77:	//������
			return RIGHT; break;
		}
	}
	if (tmp == 13) {	//enter
		return ENTER;
	}
	if (tmp == 9) {		//tab
		return TAB;
	}
	if (tmp == 27) {
		return ESC;
	}
	return 0;
}