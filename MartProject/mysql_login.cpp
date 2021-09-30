#define _CRT_SECURE_NO_WARNINGS
#include<mysql.h>
#include<iostream>
#include <cstdio>

#pragma comment(lib, "libmySQL.lib")
#define DB_HOST "localhost"	//ȣ��Ʈ �̸� �Ǵ� IP �ּ�(�⺻ : localhost)
#define DB_USER "root" //MySQL login id(mysql -u ���⾲�°� -p)
#define DB_PASS "#"	//�н�����
#define DB_NAME "cpptest_db"	//�����ͺ��̽� �̸�
#define CHOP(x) x[strlen(x)-1] = ' '

int main(void) {
	MYSQL* connection = NULL, conn;	
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	int query_stat;
	char name[12];
	char password[80];
	char query[255];

	mysql_init(&conn);

	//Mysql �����ͺ��̽� �������� ���� �õ�.
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);

	//C++�� mysql�� �������� �ʾ��� ��� �����޼���
	//con���� : MYSQL* ���� �ڵ� (= ù ��° �Ķ����)/����: NULL
	if (connection == NULL) {
		//fprintf -> stderr�� ����Ϳ� ���� �޼����� �����ִ� �ڵ�(������ ���Ͽ� �ۼ��ϴ� �ڵ�)
		//mysql_error�� ���� mysql���� ������ error�� �ٷ� �� �� �ִ�.
		fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
		return 1;
	}
	
	//mysql_query�Լ� : mysql�ܼ�â�� ���� ��ɾ �Է��ϴ� �Լ�
	//select�� => �ܼ�â�� ���
	query_stat = mysql_query(connection, "select * from login");
	if (query_stat != 0) {
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return 1;
	}

	//mysql�� ���� ����� �����Ѵ�.(��ü��)
	sql_result = mysql_store_result(connection);

	printf("ID ��й�ȣ\n");

	//���� ����� ���پ� �ҷ��� �ܾ� �ϳ��ϳ��� ������. ���� ������ 0, ������ �����Ͱ� ->> ���ܾ �迭�� ����
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
		printf("%s %s \n", sql_row[0], sql_row[1]);	//���
	}

	//mysql_store_result�� ���� �޸𸮸� ��ü��Ŵ-> ��ġ malloc�� free����
	mysql_free_result(sql_result);

	//���� ����
	printf("\nInsert value \n");
	printf("�̸� : ");
	fgets(name, 12, stdin);
	//�Է¹��� ���ڿ��� �� �κ� ������ ������ �� ����� �����ִ� ����
	CHOP(name);

	printf("��й�ȣ :");
	fgets(password, 80, stdin);
	CHOP(password);

	//db���� �ۼ�
	//sprint : query�� "insert into login values ('%s', '%s')", name, passwor������ ����
	sprintf(query, "insert into login values ('%s', '%s')", name, password);
	query_stat = mysql_query(connection, query);
	if (query_stat != 0) {	
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return 1;
	}

	mysql_close(connection);
}