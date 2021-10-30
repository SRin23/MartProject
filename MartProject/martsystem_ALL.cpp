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

void loginMain();
void managerMain();
void customerMain();
int YN_Check(int x, int y);
void init();
void gotoxy(int x, int y);
int keyControl();
static int product_Count = 0;
static int cart_Count = 0;

MYSQL* connection = NULL, conn;
int query_stat;
char query[255];

//-------------------------------------------------- MAIN -----------------------------------------------------
//main title���
int mainTitle()
{
	system("cls");
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
	gotoxy(x, y++); cout << " ########      ##         ########        ##       ##########   ##       ##";

	x = 56;
	gotoxy(x - 2, y + 2);	cout << "> ��  ��" << endl;
	gotoxy(x, y + 3);	cout << "����" << endl;
	gotoxy(x, y + 4); cout << "��  ��" << endl;

	gotoxy(10, y + 6); cout << "====================================================================================================";
	
	y = 23;
	while (true) {	//���� �ݺ�
		int n = keyControl();
		switch (n) {
		case UP:	//�踦 ������ ���
			if (y > 23) {	//y�� 17~24���̸� �̵� -> 17���� Ŀ����
				gotoxy(x - 2, y);	//���� ���ۿ� �ִ� >
				cout << " ";	//�����
				gotoxy(x - 2, --y);	//�������� 1ĭ �̵���
				cout << ">";	//�ٽ� �׸���
			}
			else if (y == 23) {	//�� �� -> �� �Ʒ��� �̵�
				gotoxy(x - 2, y);
				cout << " ";
				y = 25;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	//�鸦 ������ ���
			if (y < 25) {	//y�� 17~24���̸� �̵� -> 24���� �۾ƾ���
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);	//�Ʒ������� 1ĭ �̵���
				cout << ">";
			}
			else if (y == 25) {	//�� �Ʒ� -> �� ���� �̵�
				gotoxy(x - 2, y);
				cout << " ";
				y = 23;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case ENTER:	//���� -> �������� ���
			return y - 23;	//y-17�� �Ͽ� �� ���� ���� 1, 2, 3...���� ���� �� �ִ�. -> �� ����
		}
	}
}

void solution() {
	cout << "�����" << endl;
}

void main() {
	/*
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
	*/
	customerMain();
}

//-------------------------------------------------- login -----------------------------------------------------

//Manager, Customer���� ���ϱ�
int ManagerCustomer() {
	int x = 2, y = 4;
	//�޴����
	gotoxy(x - 2, y);	//34, 17
	cout << "> Manager" << endl;
	gotoxy(x, y + 1);	//36, 18
	cout << "Customer" << endl;

	//�޴�����
	while (true) {	//���� �ݺ�
		int n = keyControl();
		switch (n) {
		case UP:	//�踦 ������ ���
			if (y > 4) {	//y�� 17~24���̸� �̵� -> 17���� Ŀ����
				gotoxy(x - 2, y);	//���� ���ۿ� �ִ� >
				cout << " ";	//�����
				gotoxy(x - 2, --y);	//�������� 1ĭ �̵���
				cout << ">";	//�ٽ� �׸���
			}
			else if (y == 4) {	//�� �� -> �� �Ʒ��� �̵�
				gotoxy(x - 2, y);
				cout << " ";
				y = 5;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	//�鸦 ������ ���
			if (y < 5) {	//y�� 17~24���̸� �̵� -> 24���� �۾ƾ���
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);	//�Ʒ������� 1ĭ �̵���
				cout << ">";
			}
			else if (y == 5) {	//�� �Ʒ� -> �� ���� �̵�
				gotoxy(x - 2, y);
				cout << " ";
				y = 4;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case ENTER:	//���� -> �������� ���
			return y - 4;	//y-17�� �Ͽ� �� ���� ���� 1, 2, 3...���� ���� �� �ִ�. -> �� ����
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

	printf("�̸� : ");
	fgets(name, 30, stdin);
	CHOP(name);

	printf("���̵� : ");
	fgets(id, 16, stdin);
	CHOP(id);

	printf("��й�ȣ : ");
	fgets(pw, 16, stdin);
	CHOP(pw);

	printf("��й�ȣ Ȯ�� : ");
	fgets(pwCheck, 16, stdin);
	CHOP(pwCheck);

	if (strcmp(pw, pwCheck)) {
		cout << "��й�ȣ�� ��ġ���� �ʽ��ϴ�." << endl;
		cout << "�ٽ� �õ��� �ֽʽÿ�" << endl;
		Sleep(2000);
		return 0;
	}

	if (ManagerCustomer() == 0) {
		strcpy(role, "M");
	}
	else {
		strcpy(role, "C");
	}

	sprintf(query, "insert into login_info (name, id, pw, role) values ('%s', '%s', '%s', '%s')", name, id, pw, role);
	query_stat = mysql_query(connection, query);
	if (query_stat != 0) {
		//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
		printf("�Է��� ���� �ʽ��ϴ�.(insert)");
		return 1;
	}
	
	cout <<endl<<endl<< "ȸ�������� �Ϸ� �Ǿ����ϴ�." << endl;
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

	printf("ID : ");
	fgets(id, 16, stdin);
	//�Է¹��� ���ڿ��� �� �κ� ������ ������ �� ����� �����ִ� ����
	CHOP(id);
	//printf("%s\n", id);

	printf("Password : ");
	fgets(pw, 16, stdin);
	CHOP(pw);
	//printf("%s\n", pw);

	query_stat = mysql_query(connection, "select * from login_info");
	if (query_stat != 0) {
		printf("���� �ҷ��� �� �����ϴ�.(select)");
		return 1;
	}

	sql_result = mysql_store_result(connection);

	while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
		//printf("%s, %s, %s, %s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3]);
		if (!strcmp(id, sql_row[1])) {
			if (!strcmp(pw, sql_row[2])) {
				cout << sql_row[0] << "��, �α��� �Ǿ����ϴ�." << endl;
				Sleep(2000);
				if (!strcmp("M", sql_row[3])) {
					managerMain();
					return 0;
				}
				else if (!strcmp("C", sql_row[3])) {
					customerMain();
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
		printf("�� %3d �� %10s �� %16s �� ", listCount++, sql_row[0], sql_row[1]);	//���
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

	//mysql_store_result�� ���� �޸𸮸� ��ü��Ŵ-> ��ġ malloc�� free����
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
	gotoxy(x - 6, y - 1); //30, 16
	cout << "---------------------" << endl;
	gotoxy(x - 2, y);	//34, 17
	cout << ">  �α���" << endl;
	gotoxy(x, y + 1);	//36, 18
	cout << " ȸ������" << endl;
	gotoxy(x, y + 2);	//36, 19
	cout << " ȸ�����" << endl;
	gotoxy(x, y + 3);	//36, 19
	cout << " �ʱ�ȭ��" << endl;
	gotoxy(x - 6, y + 4);	//36, 25
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
				y = 15;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	//�鸦 ������ ���
			if (y < 15) {	//y�� 17~24���̸� �̵� -> 24���� �۾ƾ���
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);	//�Ʒ������� 1ĭ �̵���
				cout << ">";
			}
			else if (y == 15) {	//�� �Ʒ� -> �� ���� �̵�
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

//login����
void loginMain() {
	system("cls");
	init();
	while (true) {
		//�޴� ���� -> �Լ�
		int select = loginMenu();
		if (select == 0) signin();
		else if (select == 1) signup();
		else if (select == 2) idList();
		else if (select == 3) {
			gotoxy(0, 25); break;
		}
	}
}

//-------------------------------------------------- MANAGER -----------------------------------------------------
//������ ���
int selectQuery() {
	system("cls");
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	int listCount = 1;
	mysql_init(&conn);

	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);   //�輼�� �ٺ� �˰� �޷� �߾� selfish 
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

//ǰ�� ����Ʈ ���
int productList() {
	system("cls");
	selectQuery();
	if (keyControl() == TAB) {
		return 0;
	}
}

//managerǰ�� �߰�
int m_insertQuery() {
	char productName[30];
	char productPrice[10];
	char customerPrice[10];
	char quantity[10];

	//TAB������ ������ �ƴϸ� ��� ����
	while (true) {
		system("cls");
		selectQuery();
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
			//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
			printf("ǰ���� �߰��� �� �����ϴ�.(insert)");
			return 1;
		}
		system("cls");
		selectQuery();
		cout << "ǰ�� �߰��� �Ϸ� �Ǿ����ϴ�." << endl;
		product_Count++;
		mysql_close(connection);

		if (keyControl() == TAB) {
			break;
		}
	}
	

	return 0;
}

//managerǰ�� ����
int m_deleteQuery() {
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

		//mysql_store_result�� ���� �޸𸮸� ��ü��Ŵ-> ��ġ malloc�� free����
		mysql_free_result(sql_result);
		mysql_close(connection);

		if (keyControl() == TAB) {
			break;
		}
	}
	
}

//managerǰ�� ����
int updateQueryProductName() {
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
int updateQueryProductPrice() {
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
int updateQueryCustomerPrice() {
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
int updateQueryAll() {
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
void updateQueryAllCheck() {
	system("cls");
	cout << "ǰ���� ��ü ���� �Ͻðڽ��ϱ�?" << endl;
	cout << "(��ü���� : YES)" << endl;
	cout << "(��ü ���� : NO)" << endl;

	if (YN_Check(2, 5) == 0) {
		m_deleteQuery();
	}
	else {
		updateQueryAll();
	}
}

//manager�޴�����
int m_updateMenu() {
	system("cls");
	int x = 52;
	int y = 12;

	//�޴����
	gotoxy(x - 7, y - 1); //30, 16
	cout << "---------------------------" << endl;
	gotoxy(x - 2, y);	//34, 17
	cout << "> ��ü ����" << endl;
	gotoxy(x, y + 1);	//36, 18
	cout << "��ǰ �̸� ����" << endl;
	gotoxy(x, y + 2);	//36, 19
	cout << "��ǰ ���� ����" << endl;
	gotoxy(x, y + 3);	//36, 20
	cout << "�Һ��ڰ��� ����" << endl;
	gotoxy(x, y + 4);	//36, 22
	cout << "Main���� ������" << endl;
	gotoxy(x - 7, y + 5);	//36, 25
	cout << "---------------------------" << endl << endl;

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
				y = 16;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	//�鸦 ������ ���
			if (y < 16) {	//y�� 17~24���̸� �̵� -> 24���� �۾ƾ���
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);	//�Ʒ������� 1ĭ �̵���
				cout << ">";
			}
			else if (y == 16) {	//�� �Ʒ� -> �� ���� �̵�
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
int m_updateQuery() {
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
int m_warehousing() {
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

		//mysql_store_result�� ���� �޸𸮸� ��ü��Ŵ-> ��ġ malloc�� free����
		mysql_free_result(sql_result);
		mysql_close(connection);

		if (keyControl() == TAB) {
			break;
		}
	}
	return 0;
}
//manager���
int m_release() {
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

		//mysql_store_result�� ���� �޸𸮸� ��ü��Ŵ-> ��ġ malloc�� free����
		mysql_free_result(sql_result);
		mysql_close(connection);

		if (keyControl() == TAB) {
			break;
		}
	}
	return 0;
}

//manager title ����ϱ�
void managerTitle() {
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
	cout << "ǰ�� ����" << endl;
	gotoxy(x, y + 4);	//36, 20
	cout << " ��   ��  " << endl;
	gotoxy(x, y + 5);	//36, 21
	cout << " ��   ��" << endl;
	gotoxy(x, y +6);	//36, 22
	cout << " �α���ȭ��" << endl;
	gotoxy(x - 6, y + 7);	//36, 25
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
				y = 18;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	//�鸦 ������ ���
			if (y < 18) {	//y�� 17~24���̸� �̵� -> 24���� �۾ƾ���
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
			return y - 12;	//y-17�� �Ͽ� �� ���� ���� 1, 2, 3...���� ���� �� �ִ�. -> �� ����
		}
	}
}

//manager����
void managerMain() {
	system("cls");
	managerTitle();
	Sleep(2000);
	init();
	while (true) {
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


//-------------------------------------------------- CUSTOMER -----------------------------------------------------
int cartTotal = 0;

//īƮ ��� ǰ�� ����Ʈ 
int CartList() {
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

	query_stat = mysql_query(connection, "select * from cart order by quantity asc");
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
				sprintf(query, "delete from cart where productName='%s'", sql_row[0]);
				query_stat = mysql_query(connection, query);
				continue;
			}
			printf("�� %3d �� %-16s �� %8d �� %8d ��\n", cartCount++, sql_row[0], stoi(sql_row[1]), stoi(sql_row[2]));	//���
			cart_Count++;
		}
		printf("������������������������������������������������������������������������������������������������\n");

	}

	//mysql_store_result�� ���� �޸𸮸� ��ü��Ŵ-> ��ġ malloc�� free����
	mysql_free_result(sql_result);
}

int CartListMenu() {
	system("cls");
	CartList();
	if (keyControl() == TAB) {
		return 0;
	}
}

//īƮ�� ��ǰ �߰� => �Һ��� ���� �������
int addShoppingCart() {
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
					cartTotal += stoi(quantity) * customerPrice;
					addCheck = 1;
					sprintf(query, "insert into cart (productName, customerPrice, quantity) values ('%s', '%d', '%d')", productName, customerPrice, stoi(quantity));
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
					cout << "īƮ ��Ⱑ �Ϸ� �Ǿ����ϴ�." << endl;
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
			if (cy > y) {	//y�� 17~24���̸� �̵� -> 17���� Ŀ����
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

//���� ����
int delCartQuantity() {
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
		}
		else {
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				if (!strcmp(sql_row[0], productName)) {
					delCheck = 1;
					customerPrice = stoi(sql_row[2]);
					cartTotal -= stoi(minusQuantity) * customerPrice;

					sprintf(query, "UPDATE cart SET quantity = quantity - %d WHERE productName = '%s'", stoi(minusQuantity), productName);
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
					cout << "īƮ �� ǰ�� ������ �Ϸ� �Ǿ����ϴ�." << endl;
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

//ǰ�� �ƿ� ����
int delCartProduct() {
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
						cartTotal -= quantity * customerPrice;

						sprintf(query, "delete from cart where productName='%s'", productName);
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
						cout << "īƮ �� ǰ�� ������ �Ϸ� �Ǿ����ϴ�." << endl;
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
int deleteAll() {
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
		//��ǰ���� -> product table���� ��������
		query_stat = mysql_query(connection, "select * from cart");
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

		cout << "���� ǰ���� �����Ͻðڽ��ϱ�?";

		if (YN_Check(2, presentCur.dwCursorPosition.Y + 2) == 0) {
			

			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
					customerPrice = stoi(sql_row[1]);
					quantity = stoi(sql_row[2]);
					cartTotal -= quantity * customerPrice;

					sprintf(query, "UPDATE product SET quantity = quantity + %d WHERE productName = '%s'", quantity, sql_row[0]);
					query_stat = mysql_query(connection, query);

					if (query_stat != 0) {
						printf("���� ������ �� �����ϴ�.(update)");
						Sleep(2000);
						return 1;
					}			
			}
			sprintf(query, "delete from cart;");
			query_stat = mysql_query(connection, query);
			system("cls");
			CartList();
			cout << "īƮ �� ǰ�� ������ �Ϸ� �Ǿ����ϴ�." << endl;

			cart_Count = 0;
			cartTotal = 0;
			system("cls");
			cout << "īƮ ǰ�� ������ �Ϸ�Ǿ����ϴ�." << endl;
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
int deleteCartMenu() {
	system("cls");
	int x = 56, y = 12;
	//�޴����
	gotoxy(x - 6, y-1);	//34, 17
	cout << "������������������������������������������";
	gotoxy(x - 2, y);	//34, 17
	cout << "> ���� ����" << endl;
	gotoxy(x, y + 1);	//36, 18
	cout << "ǰ�� ����" << endl;
	gotoxy(x, y + 2);	//36, 18
	cout << "��ü ����" << endl;
	gotoxy(x, y + 3);
	cout << "���� ȭ��" << endl;
	gotoxy(x - 6, y + 4);	//34, 17
	cout << "������������������������������������������";

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
				y = 15;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	//�鸦 ������ ���
			if (y < 15) {	//y�� 17~24���̸� �̵� -> 24���� �۾ƾ���
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);	//�Ʒ������� 1ĭ �̵���
				cout << ">";
			}
			else if (y == 15) {	//�� �Ʒ� -> �� ���� �̵�
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

//īƮ ����
void deleteCart() {
	switch (deleteCartMenu()) {
	case 0: delCartQuantity(); break;
	case 1: delCartProduct(); break;
	case 2: deleteAll(); break;
	case 3: break;
	}
}

//�����߰�
int updateCartQuantity() {
	CartList();
	char productName[30];
	char plusQuantity[10];
	int customerPrice;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	mysql_init(&conn);

	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	mysql_set_character_set(connection, "euckr");
	if (connection == NULL) {
		fprintf(stderr, "Mysql connection error : %s\n", mysql_error(&conn));
		return 1;
	}

	printf("��ǰ�� : ");
	fgets(productName, 30, stdin);
	CHOP(productName);

	printf("�߰� ���� : ");
	fgets(plusQuantity, 10, stdin);
	CHOP(plusQuantity);


	//��ǰ���� -> product table���� ��������
	query_stat = mysql_query(connection, "select * from product");
	if (query_stat != 0) {
		fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
		Sleep(2000);
		return 1;
	}

	sql_result = mysql_store_result(connection);

	while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
		if (!strcmp(sql_row[0], productName)) {
			customerPrice = stoi(sql_row[2]);
			cartTotal += stoi(plusQuantity) * customerPrice;

			sprintf(query, "UPDATE cart SET quantity = quantity + %d WHERE productName = '%s'", stoi(plusQuantity), productName);
			query_stat = mysql_query(connection, query);
			sprintf(query, "UPDATE product SET quantity = quantity - %d WHERE productName = '%s'", stoi(plusQuantity), productName);
			query_stat = mysql_query(connection, query);
			if (query_stat != 0) {
				fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
				Sleep(2000);
				return 1;
			}
		}
	}

	if (sql_result == NULL) {
		cout << "Empty!!" << endl;
	}
	mysql_free_result(sql_result);


	system("cls");
	CartList();
	cout << "īƮ �� ǰ�� ������ �Ϸ� �Ǿ����ϴ�." << endl;
	Sleep(2000);
	mysql_close(connection);
	return 0;
}

int buyCheck() {
	system("cls");
	CartList();
	cout << "�����Ͻðڽ��ϱ�?" << endl;
	int x = 2, y = 15;
	//�޴����
	gotoxy(x - 2, y);	//34, 17
	cout << "> YES" << endl;
	gotoxy(x, y + 1);	//36, 18
	cout << "NO" << endl;

	//�޴�����
	while (true) {	//���� �ݺ�
		int n = keyControl();
		switch (n) {
		case UP:	//�踦 ������ ���
			if (y > 15) {	//y�� 17~24���̸� �̵� -> 17���� Ŀ����
				gotoxy(x - 2, y);	//���� ���ۿ� �ִ� >
				cout << " ";	//�����
				gotoxy(x - 2, --y);	//�������� 1ĭ �̵���
				cout << ">";	//�ٽ� �׸���
			}
			else if (y == 15) {	//�� �� -> �� �Ʒ��� �̵�
				gotoxy(x - 2, y);
				cout << " ";
				y = 16;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	//�鸦 ������ ���
			if (y < 16) {	//y�� 17~24���̸� �̵� -> 24���� �۾ƾ���
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);	//�Ʒ������� 1ĭ �̵���
				cout << ">";
			}
			else if (y == 16) {	//�� �Ʒ� -> �� ���� �̵�
				gotoxy(x - 2, y);
				cout << " ";
				y = 15;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case ENTER:	//���� -> �������� ���
			return y - 15;	//y-17�� �Ͽ� �� ���� ���� 1, 2, 3...���� ���� �� �ִ�. -> �� ����
		}
	}
}

void buy() {
	if (buyCheck() == 0) {

	}
	else {
		system("cls");
		if (YN_Check(2, 0) == 0) deleteAll();
		else cout << "��������� ��ǰ�� �����մϴ�." << endl;
	}
}

int refund() {
	char productName[30];
	char quantity[10];
	char refund_reason[100];

	mysql_init(&conn);

	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	mysql_set_character_set(connection, "euckr");

	if (connection == NULL) {
		fprintf(stderr, "Mysql connection error : %s\n", mysql_error(&conn));
		return 1;
	}

	printf("��ǰ�� : ");
	fgets(productName, 30, stdin);
	CHOP(productName);

	printf("��ǰ ���� : ");
	fgets(quantity, 10, stdin);
	CHOP(quantity);

	printf("ȯ�һ���(100�� �̳�) : ");
	fgets(refund_reason, 10, stdin);
	CHOP(refund_reason);

	sprintf(query, "insert into refund (productName, quantity, refund_reason) values ('%s', %d, '%s')", productName, stoi(quantity), refund_reason);
	query_stat = mysql_query(connection, query);
	if (query_stat != 0) {
		fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
		return 1;
	}
	system("cls");
	mysql_close(connection);
	return 0;
}

//customer title ����ϱ�
void customerTitle() {
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
int customerMenu() {
	system("cls");
	int x = 56;
	int y = 12;

	//�޴����
	gotoxy(x - 6, y - 1); //30, 16
	cout << "������������������������������������������" << endl;
	gotoxy(x - 2, y);	//34, 17
	cout << "> īƮ ���" << endl;
	gotoxy(x, y + 1);	//36, 18
	cout << "īƮ �߰�" << endl;
	gotoxy(x, y + 2);	//36, 19
	cout << "īƮ ����" << endl;
	gotoxy(x, y + 3);	//36, 20
	cout << "���� ����" << endl;
	gotoxy(x, y + 4);	//36, 21
	cout << "��     ��" << endl;
	gotoxy(x, y + 5);	//36, 22
	cout << "ȯ     ��" << endl;
	gotoxy(x, y + 6);
	cout << "��     ��" << endl;
	gotoxy(x - 6, y + 7);	//36, 25
	cout << "������������������������������������������" << endl << endl;

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
				y = 18;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	//�鸦 ������ ���
			if (y < 18) {	//y�� 17~24���̸� �̵� -> 24���� �۾ƾ���
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
			return y - 12;	//y-17�� �Ͽ� �� ���� ���� 1, 2, 3...���� ���� �� �ִ�. -> �� ����
		}
	}
}

void customerMain() {
	system("cls");
	//customerTitle();
	//Sleep(2000);
	init();
	while (true) {
		int select = customerMenu();
		if (select == 0) CartListMenu();
		else if (select == 1) addShoppingCart();
		else if (select == 2) deleteCart();
		else if (select == 3) updateCartQuantity();
		else if (select == 4) buy();
		else if (select == 5) refund();
		else if (select == 6) {
			gotoxy(0, 27); break;
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