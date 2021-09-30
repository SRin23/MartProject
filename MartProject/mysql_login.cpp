#define _CRT_SECURE_NO_WARNINGS
#include<mysql.h>
#include<iostream>
#include <cstdio>

#pragma comment(lib, "libmySQL.lib")
#define DB_HOST "localhost"	//호스트 이름 또는 IP 주소(기본 : localhost)
#define DB_USER "root" //MySQL login id(mysql -u 여기쓰는것 -p)
#define DB_PASS "#"	//패스워드
#define DB_NAME "cpptest_db"	//데이터베이스 이름
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

	//Mysql 데이터베이스 엔진으로 연결 시도.
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);

	//C++과 mysql이 연동되지 않았을 경우 에러메세지
	//con성공 : MYSQL* 연결 핸들 (= 첫 번째 파라미터)/실패: NULL
	if (connection == NULL) {
		//fprintf -> stderr는 모니터에 에러 메세지를 보여주는 코드(원래는 파일에 작성하는 코드)
		//mysql_error로 인해 mysql에서 보내는 error를 바로 볼 수 있다.
		fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
		return 1;
	}
	
	//mysql_query함수 : mysql콘솔창에 쓰는 명령어를 입력하는 함수
	//select문 => 콘솔창에 출력
	query_stat = mysql_query(connection, "select * from login");
	if (query_stat != 0) {
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return 1;
	}

	//mysql에 나온 결과를 저장한다.(전체로)
	sql_result = mysql_store_result(connection);

	printf("ID 비밀번호\n");

	//나온 결과를 한줄씩 불러와 단어 하나하나로 나눈다. 값이 없으면 0, 있으면 포인터값 ->> 각단어를 배열로 저장
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
		printf("%s %s \n", sql_row[0], sql_row[1]);	//출력
	}

	//mysql_store_result에 사용된 메모리를 헤체시킴-> 마치 malloc의 free역할
	mysql_free_result(sql_result);

	//값을 받음
	printf("\nInsert value \n");
	printf("이름 : ");
	fgets(name, 12, stdin);
	//입력받은 문자열의 끝 부분 공백을 지워서 그 결과를 돌려주는 역할
	CHOP(name);

	printf("비밀번호 :");
	fgets(password, 80, stdin);
	CHOP(password);

	//db에서 작성
	//sprint : query에 "insert into login values ('%s', '%s')", name, passwor문장을 저장
	sprintf(query, "insert into login values ('%s', '%s')", name, password);
	query_stat = mysql_query(connection, query);
	if (query_stat != 0) {	
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return 1;
	}

	mysql_close(connection);
}