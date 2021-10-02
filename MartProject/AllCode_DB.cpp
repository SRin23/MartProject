#define _CRT_SECURE_NO_WARNINGS
#include<mysql.h>
#include<iostream>
#include<cstdio>
#include<conio.h>	//getch사용
#include<windows.h>	//좌표사용
#include <string.h>
#include<string>


//방향키 및 키값 정의
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define ENTER 4	//ENTER키 : t선택
#define TAB 5	//TAB키 : Main으로 빠져나오기
#define ESC 6	//프로그램 종료

#pragma comment(lib, "libmySQL.lib")
#define DB_HOST "localhost"	//호스트 이름 또는 IP 주소(기본 : localhost)
#define DB_USER "root" //MySQL login id(mysql -u 여기쓰는것 -p)
#define DB_PASS "mirim"	//패스워드
#define DB_NAME "martsystem_db"	//데이터베이스 이름
#define CHOP(x) x[strlen(x)-1] = ' '

using namespace std;

//품목 추가
int insertQuery() {
	MYSQL* connection = NULL, conn;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	int query_stat;
	char productName[30];
	char productPrice[10];
	char customerPrice[10];
	char quantity[10];
	char query[255];

	mysql_init(&conn);

	//Mysql 데이터베이스 엔진으로 연결 시도.
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	mysql_set_character_set(connection, "euckr");
	//C++과 mysql이 연동되지 않았을 경우 에러메세지
	//con성공 : MYSQL* 연결 핸들 (= 첫 번째 파라미터)/실패: NULL
	if (connection == NULL) {
		//fprintf -> stderr는 모니터에 에러 메세지를 보여주는 코드(원래는 파일에 작성하는 코드)
		//mysql_error로 인해 mysql에서 보내는 error를 바로 볼 수 있다.
		fprintf(stderr, "Mysql connection error : %s\n", mysql_error(&conn));
		return 1;
	}

	printf("제품명 : ");
	fgets(productName, 30, stdin);
	//입력받은 문자열의 끝 부분 공백을 지워서 그 결과를 돌려주는 역할
	CHOP(productName);

	printf("제품가격 : ");
	fgets(productPrice, 10, stdin);
	CHOP(productPrice);

	printf("소비자가격 : ");
	fgets(customerPrice, 10, stdin);
	CHOP(customerPrice);

	printf("제품수량 : ");
	fgets(quantity, 10, stdin);
	CHOP(quantity);

	//db에서 작성
	//sprint : query에 "insert into login values ('%s', '%s')", name, passwor문장을 저장
	sprintf(query, "insert into product (productName, productPrice, customerPrice, quantity) values ('%s', '%d', '%d', '%d')", productName, stoi(productPrice), stoi(customerPrice), stoi(quantity));
	query_stat = mysql_query(connection, query);
	if (query_stat != 0) {
		fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
		return 1;
	}

	mysql_close(connection);
}

//품목 리스트
int selectQuary() {
	MYSQL* connection = NULL, conn;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	int query_stat;
	mysql_init(&conn);

	//Mysql 데이터베이스 엔진으로 연결 시도.
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	mysql_set_character_set(connection, "euckr");
	//C++과 mysql이 연동되지 않았을 경우 에러메세지
	//con성공 : MYSQL* 연결 핸들 (= 첫 번째 파라미터)/실패: NULL
	if (connection == NULL) {
		//fprintf -> stderr는 모니터에 에러 메세지를 보여주는 코드(원래는 파일에 작성하는 코드)
		//mysql_error로 인해 mysql에서 보내는 error를 바로 볼 수 있다.
		fprintf(stderr, "Mysql connection error : %s\n", mysql_error(&conn));
		return 1;
	}

	//mysql_query함수 : mysql콘솔창에 쓰는 명령어를 입력하는 함수
	//select문 => 콘솔창에 출력
	query_stat = mysql_query(connection, "select * from product");
	if (query_stat != 0) {
		fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
		return 1;
	}

	//mysql에 나온 결과를 저장한다.(전체로)
	sql_result = mysql_store_result(connection);

	printf("| %3s | %-10s | %8s | %8s| %8s |\n", "ID", "제품명", "제품가격", "소비자가격", "수량");

	//나온 결과를 한줄씩 불러와 단어 하나하나로 나눈다. 값이 없으면 0, 있으면 포인터값 ->> 각단어를 배열로 저장
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
		printf("| %3d | %-10s | %8d | %9d | %8d |\n", stoi(sql_row[0]), sql_row[1], stoi(sql_row[2]), stoi(sql_row[3]), stoi(sql_row[4]));	//출력
	}
	if (sql_result == NULL){
	cout << "Empty!!" << endl;
	}

	//mysql_store_result에 사용된 메모리를 헤체시킴-> 마치 malloc의 free역할
	mysql_free_result(sql_result);
}

int main() {
	selectQuary();
	insertQuery();

	selectQuary();
	return 0;
}