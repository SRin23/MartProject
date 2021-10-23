#define _CRT_SECURE_NO_WARNINGS
#include<mysql.h>
#include<iostream>
#include<cstdio>
#include<conio.h>	//getch���
#include<windows.h>	//��ǥ���
#include <string.h>
#include<string>


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

void mainTitle();
void managerMain();
void managerTitle();
int managerMenu();
void init();
void gotoxy(int x, int y);
int keyControl();
static int product_Count = 0;

MYSQL* connection = NULL, conn;
int query_stat;
char query[255];

//ǰ�� ����Ʈ
int selectQuery() {
	system("cls");
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	int listCount = 1;
	mysql_init(&conn);

	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	mysql_set_character_set(connection, "euckr");
	if (connection == NULL) {
		fprintf(stderr, "Mysql connection error : %s\n", mysql_error(&conn));
		return 1;
	}

	query_stat = mysql_query(connection, "select * from product");
	if (query_stat != 0) {
		fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
		return 1;
	}

	sql_result = mysql_store_result(connection);

	printf("| %3s | %-10s | %8s | %8s| %8s |\n", "ID", "��ǰ��", "��ǰ����", "�Һ��ڰ���", "����");

	while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
		printf("| %3d | %-10s | %8d | %9d | %8d |\n", listCount++, sql_row[0], stoi(sql_row[1]), stoi(sql_row[2]), stoi(sql_row[3]));	//���
	}
	if (sql_result == NULL) {
		cout << "Empty!!" << endl;
	}

	//mysql_store_result�� ���� �޸𸮸� ��ü��Ŵ-> ��ġ malloc�� free����
	mysql_free_result(sql_result);
}

int productList() {
	system("cls");
	selectQuery();
	if (keyControl() == TAB) {
		return 0;
	}
}
//ǰ�� �߰�
int insertQuery() {
	selectQuery();
	char productName[30];
	char productPrice[10];
	char customerPrice[10];
	char quantity[10];

	mysql_init(&conn);

	//Mysql �����ͺ��̽� �������� ���� �õ�.
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	mysql_set_character_set(connection, "euckr");
	//C++�� mysql�� �������� �ʾ��� ��� �����޼���
	//con���� : MYSQL* ���� �ڵ� (= ù ��° �Ķ����)/����: NULL
	if (connection == NULL) {
		//fprintf -> stderr�� ����Ϳ� ���� �޼����� �����ִ� �ڵ�(������ ���Ͽ� �ۼ��ϴ� �ڵ�)
		//mysql_error�� ���� mysql���� ������ error�� �ٷ� �� �� �ִ�.
		fprintf(stderr, "Mysql connection error : %s\n", mysql_error(&conn));
		return 1;
	}

	printf("��ǰ�� : ");
	fgets(productName, 30, stdin);
	//�Է¹��� ���ڿ��� �� �κ� ������ ������ �� ����� �����ִ� ����
	CHOP(productName);

	printf("��ǰ���� : ");
	fgets(productPrice, 10, stdin);
	CHOP(productPrice);

	printf("�Һ��ڰ��� : ");
	fgets(customerPrice, 10, stdin);
	CHOP(customerPrice);

	printf("��ǰ���� : ");
	fgets(quantity, 10, stdin);
	CHOP(quantity);

	//db���� �ۼ�
	//sprint : query�� "insert into login values ('%s', '%s')", name, passwor������ ����
	sprintf(query, "insert into product (productName, productPrice, customerPrice, quantity) values ('%s', '%d', '%d', '%d')", productName, stoi(productPrice), stoi(customerPrice), stoi(quantity));
	query_stat = mysql_query(connection, query);
	if (query_stat != 0) {
		fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
		return 1;
	}
	system("cls");
	selectQuery();
	cout << "ǰ�� �߰��� �Ϸ� �Ǿ����ϴ�." << endl;
	product_Count++;
	Sleep(2000);
	mysql_close(connection);
	return 0;
}

//ǰ�� ����
int deleteQuery() {
	selectQuery();
	char productName[30];

	mysql_init(&conn);

	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	mysql_set_character_set(connection, "euckr");
	if (connection == NULL) {
		fprintf(stderr, "Mysql connection error : %s\n", mysql_error(&conn));
		return 1;
	}

	cout << "��ǰ�� : ";
	fgets(productName, 30, stdin);
	CHOP(productName);

	sprintf(query, "delete from product where productName='%s'", productName);
	query_stat = mysql_query(connection, query);
	if (query_stat != 0) {
		fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
		fprintf(stdout, "�Է��� ǰ���� �������� �ʽ��ϴ�.");
		return 1;
	}

	system("cls");
	selectQuery();
	cout << "ǰ�� ������ �Ϸ� �Ǿ����ϴ�." << endl;
	product_Count--;
	Sleep(2000);
	//id 1~���� �迭�ϴ� �Լ��ۼ��ϱ�
	mysql_close(connection);
}

//ǰ�� ����
int updateQueryProductName() {
	char productName[30];
	char changeName[30];

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

	cout << "������ ��ǰ�� : ";
	fgets(changeName, 30, stdin);
	CHOP(changeName);

	sprintf(query, "update product set productName='%s' where productName='%s'", changeName, productName);
	query_stat = mysql_query(connection, query);
	if (query_stat != 0) {
		fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
		cout << "�Է��� ǰ���� �������� �ʽ��ϴ�.";
		return 1;
	}
	mysql_close(connection);
}
int updateQueryProductPrice() {
	char productName[30];
	char changeProductPrice[8];

	mysql_init(&conn);

	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	mysql_set_character_set(connection, "euckr");
	if (connection == NULL) {
		fprintf(stderr, "Mysql connection error : %s\n", mysql_error(&conn));
		return 1;
	}

	cout << "��ǰ�� : ";
	fgets(productName, 30, stdin);
	CHOP(productName);

	cout << "������ ���� : ";
	fgets(changeProductPrice, 8, stdin);
	CHOP(changeProductPrice);

	sprintf(query, "update product set productPrice= '%d' where productName='%s'", stoi(changeProductPrice), productName);
	query_stat = mysql_query(connection, query);
	if (query_stat != 0) {
		fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
		fprintf(stdout, "�Է��� ǰ���� �������� �ʽ��ϴ�.");
		return 1;
	}
	mysql_close(connection);
	return 0;
}
int updateQueryCustomerPrice() {
	char productName[30];
	char changeCustomerPrice[8];

	mysql_init(&conn);

	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	mysql_set_character_set(connection, "euckr");
	if (connection == NULL) {
		fprintf(stderr, "Mysql connection error : %s\n", mysql_error(&conn));
		return 1;
	}

	cout << "��ǰ�� : ";
	fgets(productName, 30, stdin);
	CHOP(productName);

	cout << "������ �Һ��� ���� : ";
	fgets(changeCustomerPrice, 8, stdin);
	CHOP(changeCustomerPrice);

	sprintf(query, "update product set customerPrice= '%d' where productName='%s'", stoi(changeCustomerPrice), productName);
	query_stat = mysql_query(connection, query);
	if (query_stat != 0) {
		fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
		fprintf(stdout, "�Է��� ǰ���� �������� �ʽ��ϴ�.");
		return 1;
	}
	mysql_close(connection);
	return 0;
}
int updateQueryAll() {
	char productName[30];
	char changeProductName[30];
	char changeProductPrice[8];
	char changeCustomerPrice[8];

	mysql_init(&conn);

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

	sprintf(query, " update product set productName='%s', productPrice='%d', customerPrice='%d' where productName='%s'", changeProductName, stoi(changeProductPrice), stoi(changeCustomerPrice), productName);
	query_stat = mysql_query(connection, query);
	if (query_stat != 0) {
		fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
		fprintf(stdout, "�Է��� ǰ���� �������� �ʽ��ϴ�.\n");
		return 1;
	}
	mysql_close(connection);
}
int updateQuery() {
	char choice[3];
	int i_choice;

	//������, �ѹ��� �α���

	//����ȭ��
	cout << "������ �����Ͻðڽ��ϱ�?" << endl;
	cout << "| 0. ��ü | 1. ��ǰ�� | 2. ��ǰ���� | 3. �Һ��ڰ��� | 4. ���� | " << endl << "==> ";

	//�Է�
	fgets(choice, 3, stdin);
	i_choice = stoi(choice);
	if (i_choice == 0) { updateQueryAll(); }
	else if (i_choice == 1) { updateQueryProductName(); }
	else if (i_choice == 2) { updateQueryProductPrice(); }
	else if (i_choice == 3) { updateQueryCustomerPrice(); }
	else { cout << "���� ���� ��ȣ �Դϴ�." << endl; }
	return 0;
}

//�԰�
int warehousing() {
	system("cls");

	selectQuery();
	char productName[30];
	char addAmount[10];

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

	cout << "�԰��� ��ǰ ���� : ";
	fgets(addAmount, 10, stdin);
	CHOP(addAmount);

	sprintf(query, "UPDATE product SET quantity = quantity + %d WHERE productName = '%s'", stoi(addAmount), productName);
	query_stat = mysql_query(connection, query);
	if (query_stat != 0) {
		fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
		cout << "�Է��� ǰ���� �������� �ʽ��ϴ�.";
		Sleep(5000);
		return 1;
	}
	system("cls");
	selectQuery();
	cout << "�԰� �Ϸ� �Ǿ����ϴ�." << endl;
	Sleep(2000);
	mysql_close(connection);
	return 0;
}
//���
int release() {
	system("cls");

	selectQuery();
	char productName[30];
	char minusAmount[10];

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

	cout << "����� ��ǰ ���� : ";
	fgets(minusAmount, 10, stdin);
	CHOP(minusAmount);

	sprintf(query, "UPDATE product SET quantity = quantity - %d WHERE productName = '%s'", stoi(minusAmount), productName);
	query_stat = mysql_query(connection, query);
	if (query_stat != 0) {
		fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
		cout << "�Է��� ǰ���� �������� �ʽ��ϴ�.";
		Sleep(5000);
		return 1;
	}
	system("cls");
	selectQuery();
	cout << "��� �Ϸ� �Ǿ����ϴ�." << endl;
	Sleep(2000);
	mysql_close(connection);
	return 0;
}

int main() {
	//mainTitle();
	//Sleep(2000);
	managerMain();
	return 0;
}

void mainTitle()
{
	int x = 16, y = 7;
	gotoxy(10, y - 3); cout << "====================================================================================================";
	gotoxy(x, y++); cout << "##       ##        #        #######     ########";
	gotoxy(x, y++); cout << "####   ####      ## ##      ##    ##       ##";
	gotoxy(x, y++); cout << "##  ###  ##     ##   ##     #######        ##";
	gotoxy(x, y++); cout << "##   #   ##    #########    ##    ##       ##";
	gotoxy(x, y++); cout << "##       ##   ##       ##   ##     ##      ##";
	gotoxy(x, y++); cout << "##       ##   ##       ##   ##     ##      ##";

	x = 25, y = 15;
	gotoxy(x, y++); cout << "  #######   ##      ##     #######    ##########   ##########   ##       ##";
	gotoxy(x, y++); cout << "##           ##    ##    ##               ##       ##           ####   ####";
	gotoxy(x, y++); cout << " #######      ##  ##      #######         ##       #######      ##  ###  ##";
	gotoxy(x, y++); cout << "        ##     ##                ##       ##       ##           ##   #   ##";
	gotoxy(x, y++); cout << "        ##     ##                ##       ##       ##           ##       ##";
	gotoxy(x, y); cout << " ########      ##         ########        ##       ##########   ##       ##";
	gotoxy(10, y + 3); cout << "====================================================================================================";
}

void managerMain() {
	system("cls");
	managerTitle();
	Sleep(2000);
	init();
	while (true) {
		//�޴� ���� -> �Լ�
		int select = managerMenu();
		if (select == 0) productList();
		else if (select == 1)insertQuery();
		else if (select == 2) deleteQuery();
		else if (select == 3) warehousing();	//�԰�
		else if (select == 4) release();		//���
		else if (select == 5) {
			gotoxy(0, 27); break;
		}
	}
}

//title ����ϱ�
void managerTitle(){
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

//�޴�����
int managerMenu() {
	system("cls");
	int x = 56;
	int y = 12;

	//�޴����
	gotoxy(x - 6, y - 1); //30, 16
	cout << "---------------------" << endl;
	gotoxy(x - 2, y);	//34, 17
	cout << "> ��ǰ ���" << endl;
	gotoxy(x, y + 1);	//36, 18
	cout << "ǰ�� �߰�" << endl;
	gotoxy(x, y + 2);	//36, 19
	cout << "ǰ�� ����" << endl;
	gotoxy(x, y + 3);	//36, 20
	cout << " ��   ��  " << endl;
	gotoxy(x, y + 4);	//36, 21
	cout << " ��   ��" << endl;
	gotoxy(x, y + 5);	//36, 22
	cout << " ��   ��" << endl;
	gotoxy(x - 6, y + 6);	//36, 25
	cout << "---------------------" << endl << endl;

	//�޴�����
	while (true) {	//���� �ݺ�
		int n = keyControl();
		switch (n) {
		case UP:	//�踦 ������ ���
			if (y > 12) {	//y�� 17~24���̸� �̵� -> 17���� Ŀ����
				gotoxy(x - 2, y);	//���� ���ۿ� �ִ� >
				cout << " ";	//�����
				gotoxy(x - 2, --y);	//�������� 1ĭ �̵���
				cout << ">";	//�ٽ� �׸���
			}
			else if (y == 12) {	//�� �� -> �� �Ʒ��� �̵�
				gotoxy(x - 2, y);
				cout << " ";
				y = 17;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	//�鸦 ������ ���
			if (y < 17) {	//y�� 17~24���̸� �̵� -> 24���� �۾ƾ���
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);	//�Ʒ������� 1ĭ �̵���
				cout << ">";
			}
			else if (y == 17) {	//�� �Ʒ� -> �� ���� �̵�
				gotoxy(x - 2, y);
				cout << " ";
				y = 12;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case ENTER:	//���� -> �������� ���
			return y - 12;	//y-17�� �Ͽ� �� ���� ���� 1, 2, 3...���� ���� �� �ִ�. -> �� ����
		}
	}
}

void cashierMain() {
	system("cls");
	managerTitle();
	Sleep(2000);
	init();
	while (true) {
		//�޴� ���� -> �Լ�
		int select = managerMenu();
		if (select == 0) productList();
		else if (select == 1)insertQuery();
		else if (select == 2) deleteQuery();
		else if (select == 3) warehousing();	//�԰�
		else if (select == 4) release();		//���
		else if (select == 5) {
			gotoxy(0, 27); break;
		}
	}
}

//title ����ϱ�
void cashierTitle() {
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

//�޴�����
int cashierMenu() {
	system("cls");
	int x = 56;
	int y = 12;

	//�޴����
	gotoxy(x - 6, y - 1); //30, 16
	cout << "---------------------" << endl;
	gotoxy(x - 2, y);	//34, 17
	cout << "> ��ǰ ���" << endl;
	gotoxy(x, y + 1);	//36, 18
	cout << "ǰ�� �߰�" << endl;
	gotoxy(x, y + 2);	//36, 19
	cout << "ǰ�� ����" << endl;
	gotoxy(x, y + 3);	//36, 20
	cout << " ��   ��  " << endl;
	gotoxy(x, y + 4);	//36, 21
	cout << " ��   ��" << endl;
	gotoxy(x, y + 5);	//36, 22
	cout << " ��   ��" << endl;
	gotoxy(x - 6, y + 6);	//36, 25
	cout << "---------------------" << endl << endl;

	//�޴�����
	while (true) {	//���� �ݺ�
		int n = keyControl();
		switch (n) {
		case UP:	//�踦 ������ ���
			if (y > 12) {	//y�� 17~24���̸� �̵� -> 17���� Ŀ����
				gotoxy(x - 2, y);	//���� ���ۿ� �ִ� >
				cout << " ";	//�����
				gotoxy(x - 2, --y);	//�������� 1ĭ �̵���
				cout << ">";	//�ٽ� �׸���
			}
			else if (y == 12) {	//�� �� -> �� �Ʒ��� �̵�
				gotoxy(x - 2, y);
				cout << " ";
				y = 17;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	//�鸦 ������ ���
			if (y < 17) {	//y�� 17~24���̸� �̵� -> 24���� �۾ƾ���
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);	//�Ʒ������� 1ĭ �̵���
				cout << ">";
			}
			else if (y == 17) {	//�� �Ʒ� -> �� ���� �̵�
				gotoxy(x - 2, y);
				cout << " ";
				y = 12;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case ENTER:	//���� -> �������� ���
			return y - 12;	//y-17�� �Ͽ� �� ���� ���� 1, 2, 3...���� ���� �� �ִ�. -> �� ����
		}
	}
}

//--------------------------------------------------���� �Լ�-----------------------------------------------------
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

