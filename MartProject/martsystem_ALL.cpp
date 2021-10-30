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
//main title출력
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
	gotoxy(x - 2, y + 2);	cout << "> 시  작" << endl;
	gotoxy(x, y + 3);	cout << "도움말" << endl;
	gotoxy(x, y + 4); cout << "종  료" << endl;

	gotoxy(10, y + 6); cout << "====================================================================================================";
	
	y = 23;
	while (true) {	//무한 반복
		int n = keyControl();
		switch (n) {
		case UP:	//↑를 눌렸을 경우
			if (y > 23) {	//y는 17~24사이만 이동 -> 17보다 커야함
				gotoxy(x - 2, y);	//게임 시작에 있던 >
				cout << " ";	//지우고
				gotoxy(x - 2, --y);	//위쪽으로 1칸 이동후
				cout << ">";	//다시 그리기
			}
			else if (y == 23) {	//맨 위 -> 맨 아래로 이동
				gotoxy(x - 2, y);
				cout << " ";
				y = 25;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	//↓를 눌렸을 경우
			if (y < 25) {	//y는 17~24사이만 이동 -> 24보다 작아야함
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);	//아래쪽으로 1칸 이동후
				cout << ">";
			}
			else if (y == 25) {	//맨 아래 -> 맨 위로 이동
				gotoxy(x - 2, y);
				cout << " ";
				y = 23;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case ENTER:	//엔터 -> 선택했을 경우
			return y - 23;	//y-17를 하여 각 값에 대한 1, 2, 3...값을 받을 수 있다. -> 값 선택
		}
	}
}

void solution() {
	cout << "사용방법" << endl;
}

void main() {
	/*
	system("cls");
	init();
	while (true) {
		//메뉴 선택 -> 함수
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

//Manager, Customer역할 정하기
int ManagerCustomer() {
	int x = 2, y = 4;
	//메뉴출력
	gotoxy(x - 2, y);	//34, 17
	cout << "> Manager" << endl;
	gotoxy(x, y + 1);	//36, 18
	cout << "Customer" << endl;

	//메뉴선택
	while (true) {	//무한 반복
		int n = keyControl();
		switch (n) {
		case UP:	//↑를 눌렸을 경우
			if (y > 4) {	//y는 17~24사이만 이동 -> 17보다 커야함
				gotoxy(x - 2, y);	//게임 시작에 있던 >
				cout << " ";	//지우고
				gotoxy(x - 2, --y);	//위쪽으로 1칸 이동후
				cout << ">";	//다시 그리기
			}
			else if (y == 4) {	//맨 위 -> 맨 아래로 이동
				gotoxy(x - 2, y);
				cout << " ";
				y = 5;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	//↓를 눌렸을 경우
			if (y < 5) {	//y는 17~24사이만 이동 -> 24보다 작아야함
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);	//아래쪽으로 1칸 이동후
				cout << ">";
			}
			else if (y == 5) {	//맨 아래 -> 맨 위로 이동
				gotoxy(x - 2, y);
				cout << " ";
				y = 4;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case ENTER:	//엔터 -> 선택했을 경우
			return y - 4;	//y-17를 하여 각 값에 대한 1, 2, 3...값을 받을 수 있다. -> 값 선택
		}
	}
}

//회원가입
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
		printf("데이터베이스와의 연결이 끊어졌습니다.");
		return 1;
	}

	printf("이름 : ");
	fgets(name, 30, stdin);
	CHOP(name);

	printf("아이디 : ");
	fgets(id, 16, stdin);
	CHOP(id);

	printf("비밀번호 : ");
	fgets(pw, 16, stdin);
	CHOP(pw);

	printf("비밀번호 확인 : ");
	fgets(pwCheck, 16, stdin);
	CHOP(pwCheck);

	if (strcmp(pw, pwCheck)) {
		cout << "비밀번호가 일치하지 않습니다." << endl;
		cout << "다시 시도해 주십시오" << endl;
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
		printf("입력이 되지 않습니다.(insert)");
		return 1;
	}
	
	cout <<endl<<endl<< "회원가입이 완료 되었습니다." << endl;
	mysql_close(connection);

	if (keyControl() == TAB) {
		return 0;
	}
}

//로그인
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
		printf("데이터베이스와의 연결이 끊어졌습니다.");
		return 1;
	}

	printf("ID : ");
	fgets(id, 16, stdin);
	//입력받은 문자열의 끝 부분 공백을 지워서 그 결과를 돌려주는 역할
	CHOP(id);
	//printf("%s\n", id);

	printf("Password : ");
	fgets(pw, 16, stdin);
	CHOP(pw);
	//printf("%s\n", pw);

	query_stat = mysql_query(connection, "select * from login_info");
	if (query_stat != 0) {
		printf("값을 불러올 수 없습니다.(select)");
		return 1;
	}

	sql_result = mysql_store_result(connection);

	while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
		//printf("%s, %s, %s, %s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3]);
		if (!strcmp(id, sql_row[1])) {
			if (!strcmp(pw, sql_row[2])) {
				cout << sql_row[0] << "님, 로그인 되었습니다." << endl;
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
					cout << "접근할 수 없는 회원입니다." << endl;
					Sleep(2000);
					return 0;
				}
			}
			else {
				cout << "잘못된 비밀번호 입니다." << endl;
				Sleep(2000);
				return 0;
			}
		}
	}
	cout << "아이디/비밀번호가 없습니다." << endl;
	Sleep(2000);

	//mysql_store_result에 사용된 메모리를 헤체시킴-> 마치 malloc의 free역할
	mysql_free_result(sql_result);
}


//가입된 아이디 리스트
int idList() {
	system("cls");
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	int listCount = 1;
	mysql_init(&conn);

	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	mysql_set_character_set(connection, "euckr");
	if (connection == NULL) {
		printf("데이터베이스와의 연결이 끊어졌습니다.");
		return 1;
	}

	query_stat = mysql_query(connection, "select * from login_info");
	if (query_stat != 0) {
		printf("값을 불러올 수 없습니다.(select)");
		return 1;
	}

	sql_result = mysql_store_result(connection);
	printf("┏━━━━━┳━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━┳━━━━━━━┓\n");
	printf("┃ %3s ┃ %10s ┃ %16s ┃ %16s ┃ %5s ┃\n", "NO", "NAME", "ID", "PW", "ROLE");
	printf("┣━━━━━╋━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━╋━━━━━━━┫\n");
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
		printf("┃ %3d ┃ %10s ┃ %16s ┃ ", listCount++, sql_row[0], sql_row[1]);	//출력
		for (int i = 0; i < 16-strlen(sql_row[2]); i++) {
			printf(" ");
		}
		for (int i = 0; i < strlen(sql_row[2]); i++) {
			printf("*");
		}
		printf(" ┃ %5s ┃ \n", sql_row[3]);
		
	}
	printf("┗━━━━━┻━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━┻━━━━━━━┛\n");
	if (sql_result == NULL) {
		cout << "값이 없습니다." << endl;
	}

	//mysql_store_result에 사용된 메모리를 헤체시킴-> 마치 malloc의 free역할
	mysql_free_result(sql_result);

	if (keyControl() == TAB) {
		return 0;
	}
}

//login메뉴설정 
int loginMenu() {
	system("cls");
	int x = 56;
	int y = 12;

	//메뉴출력
	gotoxy(x - 6, y - 1); //30, 16
	cout << "---------------------" << endl;
	gotoxy(x - 2, y);	//34, 17
	cout << ">  로그인" << endl;
	gotoxy(x, y + 1);	//36, 18
	cout << " 회원가입" << endl;
	gotoxy(x, y + 2);	//36, 19
	cout << " 회원목록" << endl;
	gotoxy(x, y + 3);	//36, 19
	cout << " 초기화면" << endl;
	gotoxy(x - 6, y + 4);	//36, 25
	cout << "---------------------" << endl << endl;

	//메뉴선택
	while (true) {	//무한 반복
		int n = keyControl();
		switch (n) {
		case UP:	//↑를 눌렸을 경우
			if (y > 12) {	//y는 17~24사이만 이동 -> 17보다 커야함
				gotoxy(x - 2, y);	//게임 시작에 있던 >
				cout << " ";	//지우고
				gotoxy(x - 2, --y);	//위쪽으로 1칸 이동후
				cout << ">";	//다시 그리기
			}
			else if (y == 12) {	//맨 위 -> 맨 아래로 이동
				gotoxy(x - 2, y);
				cout << " ";
				y = 15;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	//↓를 눌렸을 경우
			if (y < 15) {	//y는 17~24사이만 이동 -> 24보다 작아야함
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);	//아래쪽으로 1칸 이동후
				cout << ">";
			}
			else if (y == 15) {	//맨 아래 -> 맨 위로 이동
				gotoxy(x - 2, y);
				cout << " ";
				y = 12;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case ENTER:	//엔터 -> 선택했을 경우
			return y - 12;	//y-17를 하여 각 값에 대한 1, 2, 3...값을 받을 수 있다. -> 값 선택
		}
	}
}

//login메인
void loginMain() {
	system("cls");
	init();
	while (true) {
		//메뉴 선택 -> 함수
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
//데이터 출력
int selectQuery() {
	system("cls");
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	int listCount = 1;
	mysql_init(&conn);

	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);   //김세린 바보 똥개 메롱 야야 selfish 
	mysql_set_character_set(connection, "euckr");
	if (connection == NULL) {
		//fprintf(stderr, "Mysql connection error : %s\n", mysql_error(&conn));
		printf("데이터베이스와의 연결이 끊어졌습니다.");
		return 1;
	}

	query_stat = mysql_query(connection, "select * from product");
	if (query_stat != 0) {
		printf("값을 불러올 수 없습니다.(select)");
		//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
		return 1;
	}

	sql_result = mysql_store_result(connection);
	if (sql_result == NULL) {
		cout << "Empty!!" << endl;
	}
	else {
		printf("┏━━━━━┳━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━━━┳━━━━━━━━━━┓\n");
		printf("┃ %3s ┃ %-16s ┃ %8s ┃ %9s ┃ %8s ┃\n", "ID", "제품명", "제품가격", "소비자가격", "수량");
		printf("┣━━━━━╋━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━━━╋━━━━━━━━━━┫\n");
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
			if (stoi(sql_row[3]) == 0) {
				sprintf(query, "delete from product where productName='%s'", sql_row[0]);
				query_stat = mysql_query(connection, query);
				continue;
			}
			printf("┃ %3d ┃ %-16s ┃ %8d ┃ %10d ┃ %8d ┃\n", listCount++, sql_row[0], stoi(sql_row[1]), stoi(sql_row[2]), stoi(sql_row[3]));	//출력
		}
		printf("┗━━━━━┻━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━━━┻━━━━━━━━━━┛\n");
	}
	
	//mysql_store_result에 사용된 메모리를 헤체시킴-> 마치 malloc의 free역할
	mysql_free_result(sql_result);
}

//품목 리스트 출력
int productList() {
	system("cls");
	selectQuery();
	if (keyControl() == TAB) {
		return 0;
	}
}

//manager품목 추가
int m_insertQuery() {
	char productName[30];
	char productPrice[10];
	char customerPrice[10];
	char quantity[10];

	//TAB누르면 나가기 아니면 계속 진행
	while (true) {
		system("cls");
		selectQuery();
		mysql_init(&conn);

		//Mysql 데이터베이스 엔진으로 연결 시도.
		connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
		mysql_set_character_set(connection, "euckr");
		//C++과 mysql이 연동되지 않았을 경우 에러메세지
		//con성공 : MYSQL* 연결 핸들 (= 첫 번째 파라미터)/실패: NULL
		if (connection == NULL) {
			//fprintf -> stderr는 모니터에 에러 메세지를 보여주는 코드(원래는 파일에 작성하는 코드)
			//mysql_error로 인해 mysql에서 보내는 error를 바로 볼 수 있다.
			//fprintf(stderr, "Mysql connection error : %s\n", mysql_error(&conn));
			printf("데이터베이스와의 연결이 끊어졌습니다.");
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
			//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
			printf("품목을 추가할 수 없습니다.(insert)");
			return 1;
		}
		system("cls");
		selectQuery();
		cout << "품목 추가가 완료 되었습니다." << endl;
		product_Count++;
		mysql_close(connection);

		if (keyControl() == TAB) {
			break;
		}
	}
	

	return 0;
}

//manager품목 삭제
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
			printf("데이터베이스와의 연결이 끊어졌습니다.");
			return 1;
		}

		cout << "제품명 : ";
		fgets(productName, 30, stdin);
		CHOP(productName);

		query_stat = mysql_query(connection, "select * from product");
		if (query_stat != 0) {
			printf("값을 불러올 수 없습니다.(select)");
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
					fprintf(stdout, "delete가 실행되지 않습니다.");
					return 1;
				}
				product_Count--;
				system("cls");
				selectQuery();
				cout << "품목 삭제가 완료 되었습니다." << endl;
			}
		}

		if (deleteCheck == 0) {
			printf("입력한 품목이 존재하지 않습니다.");
		}

		//mysql_store_result에 사용된 메모리를 헤체시킴-> 마치 malloc의 free역할
		mysql_free_result(sql_result);
		mysql_close(connection);

		if (keyControl() == TAB) {
			break;
		}
	}
	
}

//manager품목 수정
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
			printf("데이터베이스와의 연결이 끊어졌습니다.");
			return 1;
		}

		cout << "제품명 : ";
		fgets(productName, 30, stdin);
		CHOP(productName);

		cout << "변경할 제품명 : ";
		fgets(changeName, 30, stdin);
		CHOP(changeName);

		query_stat = mysql_query(connection, "select * from product");
		if (query_stat != 0) {
			printf("값을 불러올 수 없습니다.(select)");
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
					fprintf(stdout, "update가 실행되지 않습니다.");
					return 1;
				}
				system("cls");
				selectQuery();
				cout << "품목 수정이 완료 되었습니다." << endl;
			}
		}

		if (updateCheck == 0) {
			printf("입력한 품목이 존재하지 않습니다.");
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
			printf("데이터베이스와의 연결이 끊어졌습니다.");
			return 1;
		}

		cout << "제품명 : ";
		fgets(productName, 30, stdin);
		CHOP(productName);

		cout << "변경할 가격 : ";
		fgets(changeProductPrice, 8, stdin);
		CHOP(changeProductPrice);


		query_stat = mysql_query(connection, "select * from product");
		if (query_stat != 0) {
			printf("값을 불러올 수 없습니다.(select)");
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
					fprintf(stdout, "update가 실행되지 않습니다.");
					return 1;
				}
				system("cls");
				selectQuery();
				cout << "품목 수정이 완료 되었습니다." << endl;
			}
		}

		if (updateCheck == 0) {
			printf("입력한 품목이 존재하지 않습니다.");
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
			printf("데이터베이스와의 연결이 끊어졌습니다.");
			return 1;
		}

		cout << "제품명 : ";
		fgets(productName, 30, stdin);
		CHOP(productName);

		cout << "변경할 소비자 가격 : ";
		fgets(changeCustomerPrice, 8, stdin);
		CHOP(changeCustomerPrice);


		query_stat = mysql_query(connection, "select * from product");
		if (query_stat != 0) {
			printf("값을 불러올 수 없습니다.(select)");
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
					fprintf(stdout, "update가 실행되지 않습니다.");
					return 1;
				}
				system("cls");
				selectQuery();
				cout << "품목 수정이 완료 되었습니다." << endl;
			}
		}

		if (updateCheck == 0) {
			printf("입력한 품목이 존재하지 않습니다.");
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


		cout << "제품명 : ";
		fgets(productName, 30, stdin);
		CHOP(productName);

		cout << "변경할 이름 : ";
		fgets(changeProductName, 8, stdin);
		CHOP(changeProductName);

		cout << "변경할 가격 : ";
		fgets(changeProductPrice, 8, stdin);
		CHOP(changeProductPrice);

		cout << "변경할 소비자가격 : ";
		fgets(changeCustomerPrice, 8, stdin);
		CHOP(changeCustomerPrice);

		query_stat = mysql_query(connection, "select * from product");
		if (query_stat != 0) {
			printf("값을 불러올 수 없습니다.(select)");
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
					fprintf(stdout, "update가 실행되지 않습니다.");
					return 1;
				}
				system("cls");
				selectQuery();
				cout << "품목 수정이 완료 되었습니다." << endl;
			}
		}

		if (updateCheck == 0) {
			printf("입력한 품목이 존재하지 않습니다.");
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
	cout << "품목을 전체 삭제 하시겠습니까?" << endl;
	cout << "(전체삭제 : YES)" << endl;
	cout << "(전체 수정 : NO)" << endl;

	if (YN_Check(2, 5) == 0) {
		m_deleteQuery();
	}
	else {
		updateQueryAll();
	}
}

//manager메뉴설정
int m_updateMenu() {
	system("cls");
	int x = 52;
	int y = 12;

	//메뉴출력
	gotoxy(x - 7, y - 1); //30, 16
	cout << "---------------------------" << endl;
	gotoxy(x - 2, y);	//34, 17
	cout << "> 전체 수정" << endl;
	gotoxy(x, y + 1);	//36, 18
	cout << "제품 이름 수정" << endl;
	gotoxy(x, y + 2);	//36, 19
	cout << "제품 가격 수정" << endl;
	gotoxy(x, y + 3);	//36, 20
	cout << "소비자가격 수정" << endl;
	gotoxy(x, y + 4);	//36, 22
	cout << "Main으로 나가기" << endl;
	gotoxy(x - 7, y + 5);	//36, 25
	cout << "---------------------------" << endl << endl;

	//메뉴선택
	while (true) {	//무한 반복
		int n = keyControl();
		switch (n) {
		case UP:	//↑를 눌렸을 경우
			if (y > 12) {	//y는 17~24사이만 이동 -> 17보다 커야함
				gotoxy(x - 2, y);	//게임 시작에 있던 >
				cout << " ";	//지우고
				gotoxy(x - 2, --y);	//위쪽으로 1칸 이동후
				cout << ">";	//다시 그리기
			}
			else if (y == 12) {	//맨 위 -> 맨 아래로 이동
				gotoxy(x - 2, y);
				cout << " ";
				y = 16;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	//↓를 눌렸을 경우
			if (y < 16) {	//y는 17~24사이만 이동 -> 24보다 작아야함
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);	//아래쪽으로 1칸 이동후
				cout << ">";
			}
			else if (y == 16) {	//맨 아래 -> 맨 위로 이동
				gotoxy(x - 2, y);
				cout << " ";
				y = 12;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case ENTER:	//엔터 -> 선택했을 경우
			return y - 12;	//y-17를 하여 각 값에 대한 1, 2, 3...값을 받을 수 있다. -> 값 선택
		}
	}
}
int m_updateQuery() {
	system("cls");
	
	while (true) {
		//메뉴 선택 -> 함수
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

//manager입고
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
			printf("데이터베이스와의 연결이 끊어졌습니다.");
			return 1;
		}

		cout << "제품명 : ";
		fgets(productName, 30, stdin);
		CHOP(productName);

		cout << "입고할 물품 개수 : ";
		fgets(addAmount, 10, stdin);
		CHOP(addAmount);

		query_stat = mysql_query(connection, "select * from product");
		if (query_stat != 0) {
			printf("값을 불러올 수 없습니다.(select)");
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
					fprintf(stdout, "update가 실행되지 않습니다.(입고 불가)");
					return 1;
				}
				system("cls");
				selectQuery();
				cout << "입고가 완료 되었습니다." << endl;
			}
		}

		if (warehousingCheck == 0) {
			printf("입력한 품목이 존재하지 않습니다.");
		}

		//mysql_store_result에 사용된 메모리를 헤체시킴-> 마치 malloc의 free역할
		mysql_free_result(sql_result);
		mysql_close(connection);

		if (keyControl() == TAB) {
			break;
		}
	}
	return 0;
}
//manager출고
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
			printf("데이터베이스와의 연결이 끊어졌습니다.");
			return 1;
		}

		cout << "제품명 : ";
		fgets(productName, 30, stdin);
		CHOP(productName);

		cout << "출고할 물품 개수 : ";
		fgets(minusAmount, 10, stdin);
		CHOP(minusAmount);

		query_stat = mysql_query(connection, "select * from product");
		if (query_stat != 0) {
			printf("값을 불러올 수 없습니다.(select)");
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
					fprintf(stdout, "update가 실행되지 않습니다.(출고 불가)");
					return 1;
				}
				system("cls");
				selectQuery();
				cout << "출고가 완료 되었습니다." << endl;
			}
		}

		if (warehousingCheck == 0) {
			printf("입력한 품목이 존재하지 않습니다.");
		}

		//mysql_store_result에 사용된 메모리를 헤체시킴-> 마치 malloc의 free역할
		mysql_free_result(sql_result);
		mysql_close(connection);

		if (keyControl() == TAB) {
			break;
		}
	}
	return 0;
}

//manager title 출력하기
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

//manager메뉴설정
int managerMenu() {
	system("cls");
	int x = 56;
	int y = 12;

	//메뉴출력
	gotoxy(x - 6, y - 1); //30, 16
	cout << "---------------------" << endl;
	gotoxy(x - 2, y);	//34, 17
	cout << "> 제품 목록" << endl;
	gotoxy(x, y + 1);	//36, 18
	cout << "품목 추가" << endl;
	gotoxy(x, y + 2);	//36, 19
	cout << "품목 삭제" << endl;
	gotoxy(x, y + 3);	//36, 20
	cout << "품목 수정" << endl;
	gotoxy(x, y + 4);	//36, 20
	cout << " 입   고  " << endl;
	gotoxy(x, y + 5);	//36, 21
	cout << " 출   고" << endl;
	gotoxy(x, y +6);	//36, 22
	cout << " 로그인화면" << endl;
	gotoxy(x - 6, y + 7);	//36, 25
	cout << "---------------------" << endl << endl;

	//메뉴선택
	while (true) {	//무한 반복
		int n = keyControl();
		switch (n) {
		case UP:	//↑를 눌렸을 경우
			if (y > 12) {	//y는 17~24사이만 이동 -> 17보다 커야함
				gotoxy(x - 2, y);	//게임 시작에 있던 >
				cout << " ";	//지우고
				gotoxy(x - 2, --y);	//위쪽으로 1칸 이동후
				cout << ">";	//다시 그리기
			}
			else if (y == 12) {	//맨 위 -> 맨 아래로 이동
				gotoxy(x - 2, y);
				cout << " ";
				y = 18;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	//↓를 눌렸을 경우
			if (y < 18) {	//y는 17~24사이만 이동 -> 24보다 작아야함
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);	//아래쪽으로 1칸 이동후
				cout << ">";
			}
			else if (y == 18) {	//맨 아래 -> 맨 위로 이동
				gotoxy(x - 2, y);
				cout << " ";
				y = 12;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case ENTER:	//엔터 -> 선택했을 경우
			return y - 12;	//y-17를 하여 각 값에 대한 1, 2, 3...값을 받을 수 있다. -> 값 선택
		}
	}
}

//manager메인
void managerMain() {
	system("cls");
	managerTitle();
	Sleep(2000);
	init();
	while (true) {
		//메뉴 선택 -> 함수
		int select = managerMenu();
		if (select == 0) productList();
		else if (select == 1)m_insertQuery();
		else if (select == 2) m_deleteQuery();
		else if (select == 3) m_updateQuery();
		else if (select == 4) m_warehousing();	//입고
		else if (select == 5) m_release();		//출고
		else if (select == 6) {
			gotoxy(20, 15);  break;
		}
	}
	return;
}


//-------------------------------------------------- CUSTOMER -----------------------------------------------------
int cartTotal = 0;

//카트 담긴 품목 리스트 
int CartList() {
	system("cls");
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	int cartCount = 1;
	mysql_init(&conn);

	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	mysql_set_character_set(connection, "euckr");
	if (connection == NULL) {
		printf("데이터베이스와의 연결이 끊어졌습니다.");
		return 1;
	}

	query_stat = mysql_query(connection, "select * from cart order by quantity asc");
	if (query_stat != 0) {
		printf("값을 불러올 수 없습니다.(select)");
		return 1;
	}

	sql_result = mysql_store_result(connection);
	if (sql_result == NULL) {
		cout << "Empty!!" << endl;
	}
	else {
		printf("┏━━━━━┳━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┓\n");
		printf("┃ %3s ┃ %-16s ┃ %8s ┃ %8s ┃\n", "ID", "제품명", "가격", "수량");
		printf("┣━━━━━╋━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━┫\n");
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
			if (stoi(sql_row[2]) == 0) {
				sprintf(query, "delete from cart where productName='%s'", sql_row[0]);
				query_stat = mysql_query(connection, query);
				continue;
			}
			printf("┃ %3d ┃ %-16s ┃ %8d ┃ %8d ┃\n", cartCount++, sql_row[0], stoi(sql_row[1]), stoi(sql_row[2]));	//출력
			cart_Count++;
		}
		printf("┗━━━━━┻━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┛\n");

	}

	//mysql_store_result에 사용된 메모리를 헤체시킴-> 마치 malloc의 free역할
	mysql_free_result(sql_result);
}

int CartListMenu() {
	system("cls");
	CartList();
	if (keyControl() == TAB) {
		return 0;
	}
}

//카트에 물품 추가 => 소비자 가격 끌어오기
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
			printf("데이터베이스와의 연결이 끊어졌습니다.");
			Sleep(2000);
			return 1;
		}

		printf("제품명 : ");
		fgets(productName, 30, stdin);
		CHOP(productName);

		printf("제품수량 : ");
		fgets(quantity, 10, stdin);
		CHOP(quantity);

		query_stat = mysql_query(connection, "select * from product");
		if (query_stat != 0) {
			printf("값을 불러올 수 없습니다.(select)");
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
						printf("값을 추가할 수 없습니다.");
						Sleep(2000);
						return 1;
					}
					system("cls");
					CartList();
					cart_Count++;
					cout << "카트 담기가 완료 되었습니다." << endl;
				}
			}
			if (addCheck == 0) {
				printf("입력한 품목이 존재하지 않습니다.");
			}

		}
		
		mysql_free_result(sql_result);
		mysql_close(connection);

		if (keyControl() == TAB) {
			return 0;
		}
	}

}

//전체 삭제 체크 => 해야함
int YN_Check(int x, int y) {
	int cx = x;
	int cy = y;
	//메뉴출력
	gotoxy(cx - 2, cy);	//34, 17
	cout << "> YES" << endl;
	gotoxy(cx, cy + 1);	//36, 18
	cout << "NO" << endl;

	while (true) {	//무한 반복
		int n = keyControl();
		switch (n) {
		case UP:	//↑를 눌렸을 경우
			if (cy > y) {	//y는 17~24사이만 이동 -> 17보다 커야함
				gotoxy(cx - 2, cy);	//게임 시작에 있던 >
				cout << " ";	//지우고
				gotoxy(cx - 2, --cy);	//위쪽으로 1칸 이동후
				cout << ">";	//다시 그리기
			}
			else if (cy == y) {	//맨 위 -> 맨 아래로 이동
				gotoxy(cx - 2, cy);
				cout << " ";
				cy = y + 1;
				gotoxy(cx - 2, cy);
				cout << ">";
			}
			break;

		case DOWN:	//↓를 눌렸을 경우
			if (cy < y + 1) {	//y는 17~24사이만 이동 -> 24보다 작아야함
				gotoxy(cx - 2, cy);
				cout << " ";
				gotoxy(cx - 2, ++cy);	//아래쪽으로 1칸 이동후
				cout << ">";
			}
			else if (cy == y + 1) {	//맨 아래 -> 맨 위로 이동
				gotoxy(cx - 2, cy);
				cout << " ";
				cy = y;
				gotoxy(cx - 2, cy);
				cout << ">";
			}
			break;

		case ENTER:	//엔터 -> 선택했을 경우
			return cy - y;	//y-17를 하여 각 값에 대한 1, 2, 3...값을 받을 수 있다. -> 값 선택
		}
	}
}

//개별 삭제
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
			printf("데이터베이스와의 연결이 끊어졌습니다.");
			return 1;
		}

		printf("제품명 : ");
		fgets(productName, 30, stdin);
		CHOP(productName);

		printf("삭제 수량 : ");
		fgets(minusQuantity, 10, stdin);
		CHOP(minusQuantity);


		//제품가격 -> product table에서 가져오기
		query_stat = mysql_query(connection, "select * from product");
		if (query_stat != 0) {
			printf("값을 불러올 수 없습니다.(select)");
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
						printf("update가 취소되었습니다.");
						Sleep(2000);
						return 1;
					}
					system("cls");
					CartList();
					cout << "카트 내 품목 삭제가 완료 되었습니다." << endl;
					break;
				}
			}

			if (delCheck == 0) {
				printf("입력한 품목이 존재하지 않습니다.");
			}
			
		}
		mysql_free_result(sql_result);
		mysql_close(connection);
		if (keyControl() == TAB) {
			return 0;
		}
	}
	
}

//품목 아예 삭제
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
			printf("데이터베이스와의 연결이 끊어졌습니다.");
			return 1;
		}

		printf("제품명 : ");
		fgets(productName, 30, stdin);
		CHOP(productName);

		//제품가격 -> product table에서 가져오기
		query_stat = mysql_query(connection, "select * from product");
		if (query_stat != 0) {
			printf("값을 불러올 수 없습니다.(select)");
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
			cout << "정말 품목을 삭제하시겠습니까?";
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
							printf("값을 삭제할 수 없습니다.(delete)");
							Sleep(2000);
							return 1;
						}
						cart_Count--;
						system("cls");
						CartList();
						cout << "카트 내 품목 삭제가 완료 되었습니다." << endl;
					}
				}
				mysql_free_result(sql_result);
				mysql_close(connection);
				if (delCount == 0) {
					cout << "일치하는 품목이 없습니다.";
				}
			}
			else {
				system("cls");
				CartList();
				cout << "제품 삭제가 취소되었습니다." << endl;
			}
		}
		if (keyControl() == TAB) {
			return 0;
		}
	}
}

//전체 삭제 => 수량 삭제 구현 필요
int deleteAll() {
	int customerPrice;
	int quantity;

	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;

	mysql_init(&conn);

	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	mysql_set_character_set(connection, "euckr");
	if (connection == NULL) {
		printf("데이터베이스와의 연결이 끊어졌습니다.");
		return 1;
	}
	system("cls");
	if (cart_Count == 0) {
		cout << "카트에 삭제할 품목이 없습니다." << endl;
	}
	else {
		//제품가격 -> product table에서 가져오기
		query_stat = mysql_query(connection, "select * from cart");
		if (query_stat != 0) {
			printf("값을 불러올 수 없습니다.(select)");
			Sleep(2000);
			return 1;
		}
		sql_result = mysql_store_result(connection);

		CartList();

		// 콘솔 출력창의 정보를 담기 위해서 정의한 구조체
		CONSOLE_SCREEN_BUFFER_INFO presentCur;

		//현재 콘솔 위치 반환
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);

		cout << "정말 품목을 삭제하시겠습니까?";

		if (YN_Check(2, presentCur.dwCursorPosition.Y + 2) == 0) {
			

			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
					customerPrice = stoi(sql_row[1]);
					quantity = stoi(sql_row[2]);
					cartTotal -= quantity * customerPrice;

					sprintf(query, "UPDATE product SET quantity = quantity + %d WHERE productName = '%s'", quantity, sql_row[0]);
					query_stat = mysql_query(connection, query);

					if (query_stat != 0) {
						printf("값을 삭제할 수 없습니다.(update)");
						Sleep(2000);
						return 1;
					}			
			}
			sprintf(query, "delete from cart;");
			query_stat = mysql_query(connection, query);
			system("cls");
			CartList();
			cout << "카트 내 품목 삭제가 완료 되었습니다." << endl;

			cart_Count = 0;
			cartTotal = 0;
			system("cls");
			cout << "카트 품목 삭제가 완료되었습니다." << endl;
		}
		else {
			system("cls");
			CartList();
			cout << "삭제가 취소되었습니다." << endl;
		}

		mysql_close(connection);
	}
	
	if (keyControl() == TAB) {
		return 0;
	}

}
 
//카트 삭제 메뉴
int deleteCartMenu() {
	system("cls");
	int x = 56, y = 12;
	//메뉴출력
	gotoxy(x - 6, y-1);	//34, 17
	cout << "─────────────────────";
	gotoxy(x - 2, y);	//34, 17
	cout << "> 개별 삭제" << endl;
	gotoxy(x, y + 1);	//36, 18
	cout << "품목 삭제" << endl;
	gotoxy(x, y + 2);	//36, 18
	cout << "전체 삭제" << endl;
	gotoxy(x, y + 3);
	cout << "메인 화면" << endl;
	gotoxy(x - 6, y + 4);	//34, 17
	cout << "─────────────────────";

	while (true) {	//무한 반복
		int n = keyControl();
		switch (n) {
		case UP:	//↑를 눌렸을 경우
			if (y > 12) {	//y는 17~24사이만 이동 -> 17보다 커야함
				gotoxy(x - 2, y);	//게임 시작에 있던 >
				cout << " ";	//지우고
				gotoxy(x - 2, --y);	//위쪽으로 1칸 이동후
				cout << ">";	//다시 그리기
			}
			else if (y == 12) {	//맨 위 -> 맨 아래로 이동
				gotoxy(x - 2, y);
				cout << " ";
				y = 15;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	//↓를 눌렸을 경우
			if (y < 15) {	//y는 17~24사이만 이동 -> 24보다 작아야함
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);	//아래쪽으로 1칸 이동후
				cout << ">";
			}
			else if (y == 15) {	//맨 아래 -> 맨 위로 이동
				gotoxy(x - 2, y);
				cout << " ";
				y = 12;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case ENTER:	//엔터 -> 선택했을 경우
			return y - 12;	//y-17를 하여 각 값에 대한 1, 2, 3...값을 받을 수 있다. -> 값 선택
		}
	}
}

//카트 삭제
void deleteCart() {
	switch (deleteCartMenu()) {
	case 0: delCartQuantity(); break;
	case 1: delCartProduct(); break;
	case 2: deleteAll(); break;
	case 3: break;
	}
}

//수량추가
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

	printf("제품명 : ");
	fgets(productName, 30, stdin);
	CHOP(productName);

	printf("추가 수량 : ");
	fgets(plusQuantity, 10, stdin);
	CHOP(plusQuantity);


	//제품가격 -> product table에서 가져오기
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
	cout << "카트 내 품목 삭제가 완료 되었습니다." << endl;
	Sleep(2000);
	mysql_close(connection);
	return 0;
}

int buyCheck() {
	system("cls");
	CartList();
	cout << "구매하시겠습니까?" << endl;
	int x = 2, y = 15;
	//메뉴출력
	gotoxy(x - 2, y);	//34, 17
	cout << "> YES" << endl;
	gotoxy(x, y + 1);	//36, 18
	cout << "NO" << endl;

	//메뉴선택
	while (true) {	//무한 반복
		int n = keyControl();
		switch (n) {
		case UP:	//↑를 눌렸을 경우
			if (y > 15) {	//y는 17~24사이만 이동 -> 17보다 커야함
				gotoxy(x - 2, y);	//게임 시작에 있던 >
				cout << " ";	//지우고
				gotoxy(x - 2, --y);	//위쪽으로 1칸 이동후
				cout << ">";	//다시 그리기
			}
			else if (y == 15) {	//맨 위 -> 맨 아래로 이동
				gotoxy(x - 2, y);
				cout << " ";
				y = 16;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	//↓를 눌렸을 경우
			if (y < 16) {	//y는 17~24사이만 이동 -> 24보다 작아야함
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);	//아래쪽으로 1칸 이동후
				cout << ">";
			}
			else if (y == 16) {	//맨 아래 -> 맨 위로 이동
				gotoxy(x - 2, y);
				cout << " ";
				y = 15;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case ENTER:	//엔터 -> 선택했을 경우
			return y - 15;	//y-17를 하여 각 값에 대한 1, 2, 3...값을 받을 수 있다. -> 값 선택
		}
	}
}

void buy() {
	if (buyCheck() == 0) {

	}
	else {
		system("cls");
		if (YN_Check(2, 0) == 0) deleteAll();
		else cout << "현재까지의 상품을 저장합니다." << endl;
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

	printf("제품명 : ");
	fgets(productName, 30, stdin);
	CHOP(productName);

	printf("제품 수량 : ");
	fgets(quantity, 10, stdin);
	CHOP(quantity);

	printf("환불사유(100자 이내) : ");
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

//customer title 출력하기
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

//메뉴설정
int customerMenu() {
	system("cls");
	int x = 56;
	int y = 12;

	//메뉴출력
	gotoxy(x - 6, y - 1); //30, 16
	cout << "─────────────────────" << endl;
	gotoxy(x - 2, y);	//34, 17
	cout << "> 카트 목록" << endl;
	gotoxy(x, y + 1);	//36, 18
	cout << "카트 추가" << endl;
	gotoxy(x, y + 2);	//36, 19
	cout << "카트 삭제" << endl;
	gotoxy(x, y + 3);	//36, 20
	cout << "수량 변경" << endl;
	gotoxy(x, y + 4);	//36, 21
	cout << "구     매" << endl;
	gotoxy(x, y + 5);	//36, 22
	cout << "환     불" << endl;
	gotoxy(x, y + 6);
	cout << "종     료" << endl;
	gotoxy(x - 6, y + 7);	//36, 25
	cout << "─────────────────────" << endl << endl;

	//메뉴선택
	while (true) {	//무한 반복
		int n = keyControl();
		switch (n) {
		case UP:	//↑를 눌렸을 경우
			if (y > 12) {	//y는 17~24사이만 이동 -> 17보다 커야함
				gotoxy(x - 2, y);	//게임 시작에 있던 >
				cout << " ";	//지우고
				gotoxy(x - 2, --y);	//위쪽으로 1칸 이동후
				cout << ">";	//다시 그리기
			}
			else if (y == 12) {	//맨 위 -> 맨 아래로 이동
				gotoxy(x - 2, y);
				cout << " ";
				y = 18;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	//↓를 눌렸을 경우
			if (y < 18) {	//y는 17~24사이만 이동 -> 24보다 작아야함
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);	//아래쪽으로 1칸 이동후
				cout << ">";
			}
			else if (y == 18) {	//맨 아래 -> 맨 위로 이동
				gotoxy(x - 2, y);
				cout << " ";
				y = 12;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case ENTER:	//엔터 -> 선택했을 경우
			return y - 12;	//y-17를 하여 각 값에 대한 1, 2, 3...값을 받을 수 있다. -> 값 선택
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

//--------------------------------------------------공통 함수-----------------------------------------------------
void init() {
	//콘솔 크기 정하기
	system("mode con cols=120 lines=30");

	//깜빡거리는 커서 숨기기
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

//좌표찍기
void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x, y };
	SetConsoleCursorPosition(consoleHandle, pos);
}

//방향키로 좌표 조절하기
int keyControl() {
	char tmp = _getch();
	if (tmp == -32) {
		tmp = _getch();
		switch (tmp) {
		case 72:	//위
			return UP; break;
		case 80:	//아래
			return DOWN; break;
		case 75:	//왼쪽
			return LEFT; break;
		case 77:	//오른쪽
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