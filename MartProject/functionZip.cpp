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

//품목 리스트
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

	printf("| %3s | %-10s | %8s | %8s| %8s |\n", "ID", "제품명", "제품가격", "소비자가격", "수량");

	while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
		printf("| %3d | %-10s | %8d | %9d | %8d |\n", listCount++, sql_row[0], stoi(sql_row[1]), stoi(sql_row[2]), stoi(sql_row[3]));	//출력
	}
	if (sql_result == NULL) {
		cout << "Empty!!" << endl;
	}

	//mysql_store_result에 사용된 메모리를 헤체시킴-> 마치 malloc의 free역할
	mysql_free_result(sql_result);
}

int productList() {
	system("cls");
	selectQuery();
	if (keyControl() == TAB) {
		return 0;
	}
}
//품목 추가
int insertQuery() {
	selectQuery();
	char productName[30];
	char productPrice[10];
	char customerPrice[10];
	char quantity[10];

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
	system("cls");
	selectQuery();
	cout << "품목 추가가 완료 되었습니다." << endl;
	product_Count++;
	Sleep(2000);
	mysql_close(connection);
	return 0;
}

//품목 삭제
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

	cout << "제품명 : ";
	fgets(productName, 30, stdin);
	CHOP(productName);

	sprintf(query, "delete from product where productName='%s'", productName);
	query_stat = mysql_query(connection, query);
	if (query_stat != 0) {
		fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
		fprintf(stdout, "입력한 품목이 존재하지 않습니다.");
		return 1;
	}

	system("cls");
	selectQuery();
	cout << "품목 삭제가 완료 되었습니다." << endl;
	product_Count--;
	Sleep(2000);
	//id 1~부터 배열하는 함수작성하기
	mysql_close(connection);
}

//품목 수정
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

	cout << "제품명 : ";
	fgets(productName, 30, stdin);
	CHOP(productName);

	cout << "변경할 제품명 : ";
	fgets(changeName, 30, stdin);
	CHOP(changeName);

	sprintf(query, "update product set productName='%s' where productName='%s'", changeName, productName);
	query_stat = mysql_query(connection, query);
	if (query_stat != 0) {
		fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
		cout << "입력한 품목이 존재하지 않습니다.";
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

	cout << "제품명 : ";
	fgets(productName, 30, stdin);
	CHOP(productName);

	cout << "변경할 가격 : ";
	fgets(changeProductPrice, 8, stdin);
	CHOP(changeProductPrice);

	sprintf(query, "update product set productPrice= '%d' where productName='%s'", stoi(changeProductPrice), productName);
	query_stat = mysql_query(connection, query);
	if (query_stat != 0) {
		fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
		fprintf(stdout, "입력한 품목이 존재하지 않습니다.");
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

	cout << "제품명 : ";
	fgets(productName, 30, stdin);
	CHOP(productName);

	cout << "변경할 소비자 가격 : ";
	fgets(changeCustomerPrice, 8, stdin);
	CHOP(changeCustomerPrice);

	sprintf(query, "update product set customerPrice= '%d' where productName='%s'", stoi(changeCustomerPrice), productName);
	query_stat = mysql_query(connection, query);
	if (query_stat != 0) {
		fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
		fprintf(stdout, "입력한 품목이 존재하지 않습니다.");
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

	sprintf(query, " update product set productName='%s', productPrice='%d', customerPrice='%d' where productName='%s'", changeProductName, stoi(changeProductPrice), stoi(changeCustomerPrice), productName);
	query_stat = mysql_query(connection, query);
	if (query_stat != 0) {
		fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
		fprintf(stdout, "입력한 품목이 존재하지 않습니다.\n");
		return 1;
	}
	mysql_close(connection);
}
int updateQuery() {
	char choice[3];
	int i_choice;

	//수정시, 한번더 로그인

	//수정화면
	cout << "무엇을 수정하시겠습니까?" << endl;
	cout << "| 0. 전체 | 1. 제품명 | 2. 제품가격 | 3. 소비자가격 | 4. 수량 | " << endl << "==> ";

	//입력
	fgets(choice, 3, stdin);
	i_choice = stoi(choice);
	if (i_choice == 0) { updateQueryAll(); }
	else if (i_choice == 1) { updateQueryProductName(); }
	else if (i_choice == 2) { updateQueryProductPrice(); }
	else if (i_choice == 3) { updateQueryCustomerPrice(); }
	else { cout << "옳지 않은 번호 입니다." << endl; }
	return 0;
}

//입고
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

	cout << "제품명 : ";
	fgets(productName, 30, stdin);
	CHOP(productName);

	cout << "입고할 물품 개수 : ";
	fgets(addAmount, 10, stdin);
	CHOP(addAmount);

	sprintf(query, "UPDATE product SET quantity = quantity + %d WHERE productName = '%s'", stoi(addAmount), productName);
	query_stat = mysql_query(connection, query);
	if (query_stat != 0) {
		fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
		cout << "입력한 품목이 존재하지 않습니다.";
		Sleep(5000);
		return 1;
	}
	system("cls");
	selectQuery();
	cout << "입고가 완료 되었습니다." << endl;
	Sleep(2000);
	mysql_close(connection);
	return 0;
}
//출고
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

	cout << "제품명 : ";
	fgets(productName, 30, stdin);
	CHOP(productName);

	cout << "출고할 물품 개수 : ";
	fgets(minusAmount, 10, stdin);
	CHOP(minusAmount);

	sprintf(query, "UPDATE product SET quantity = quantity - %d WHERE productName = '%s'", stoi(minusAmount), productName);
	query_stat = mysql_query(connection, query);
	if (query_stat != 0) {
		fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
		cout << "입력한 품목이 존재하지 않습니다.";
		Sleep(5000);
		return 1;
	}
	system("cls");
	selectQuery();
	cout << "출고가 완료 되었습니다." << endl;
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
		//메뉴 선택 -> 함수
		int select = managerMenu();
		if (select == 0) productList();
		else if (select == 1)insertQuery();
		else if (select == 2) deleteQuery();
		else if (select == 3) warehousing();	//입고
		else if (select == 4) release();		//출고
		else if (select == 5) {
			gotoxy(0, 27); break;
		}
	}
}

//title 출력하기
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

//메뉴설정
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
	cout << " 입   고  " << endl;
	gotoxy(x, y + 4);	//36, 21
	cout << " 출   고" << endl;
	gotoxy(x, y + 5);	//36, 22
	cout << " 종   료" << endl;
	gotoxy(x - 6, y + 6);	//36, 25
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
				y = 17;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	//↓를 눌렸을 경우
			if (y < 17) {	//y는 17~24사이만 이동 -> 24보다 작아야함
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);	//아래쪽으로 1칸 이동후
				cout << ">";
			}
			else if (y == 17) {	//맨 아래 -> 맨 위로 이동
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

void cashierMain() {
	system("cls");
	managerTitle();
	Sleep(2000);
	init();
	while (true) {
		//메뉴 선택 -> 함수
		int select = managerMenu();
		if (select == 0) productList();
		else if (select == 1)insertQuery();
		else if (select == 2) deleteQuery();
		else if (select == 3) warehousing();	//입고
		else if (select == 4) release();		//출고
		else if (select == 5) {
			gotoxy(0, 27); break;
		}
	}
}

//title 출력하기
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

//메뉴설정
int cashierMenu() {
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
	cout << " 입   고  " << endl;
	gotoxy(x, y + 4);	//36, 21
	cout << " 출   고" << endl;
	gotoxy(x, y + 5);	//36, 22
	cout << " 종   료" << endl;
	gotoxy(x - 6, y + 6);	//36, 25
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
				y = 17;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	//↓를 눌렸을 경우
			if (y < 17) {	//y는 17~24사이만 이동 -> 24보다 작아야함
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);	//아래쪽으로 1칸 이동후
				cout << ">";
			}
			else if (y == 17) {	//맨 아래 -> 맨 위로 이동
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

