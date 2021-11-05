#define _CRT_SECURE_NO_WARNINGS
#include<mysql.h>
#include<iostream>
#include<cstdio>
#include<conio.h>	//getch사용
#include<windows.h>	//좌표사용
#include <string.h>
#include<string>
#include <ctime> //C++

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
//main title출력
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
	gotoxy(x - 2, y + 2);	cout << "> 시  작" << endl;
	gotoxy(x, y + 3);	cout << "도움말" << endl;
	gotoxy(x, y + 4); cout << "종  료" << endl;

	gotoxy(10, y + 6); cout << "====================================================================================================";
	
	y = 22;
	while (true) {	//무한 반복
		int n = keyControl();
		switch (n) {
		case UP:	//↑를 눌렸을 경우
			if (y > 22) {	//y는 17~24사이만 이동 -> 17보다 커야함
				gotoxy(x - 2, y);	//게임 시작에 있던 >
				cout << " ";	//지우고
				gotoxy(x - 2, --y);	//위쪽으로 1칸 이동후
				cout << ">";	//다시 그리기
			}
			else if (y == 22) {	//맨 위 -> 맨 아래로 이동
				gotoxy(x - 2, y);
				cout << " ";
				y = 24;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case DOWN:	//↓를 눌렸을 경우
			if (y < 24) {	//y는 17~24사이만 이동 -> 24보다 작아야함
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);	//아래쪽으로 1칸 이동후
				cout << ">";
			}
			else if (y == 24) {	//맨 아래 -> 맨 위로 이동
				gotoxy(x - 2, y);
				cout << " ";
				y = 22;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case ENTER:	//엔터 -> 선택했을 경우
			return y - 22;	//y-17를 하여 각 값에 대한 1, 2, 3...값을 받을 수 있다. -> 값 선택
		}
	}
}

void solution() {
	system("cls");
	cout << "[ 사용방법 ]" << endl<<endl<<endl;
	cout << " - Manager와 Customer로 이루어진 마트 관리 시스템 입니다." << endl;
	cout << " - 각각의 역할을 맡고자 하시면 회원가입을 진행해 주세요" << endl;
	cout << " - 아이디가 없으시다면 프로그램을 실행 할 수 없습니다." << endl;
	cout << " - 모든 화면에서 이전화면으로 넘어가려면 TAB을 눌러주세요." << endl;
	cout << " - 모든 화면에서 선택하려면 ENTER를 눌러주세요." << endl;
	cout << " - 모든 메뉴 하단에는 종료/이전화면 버튼이 있습니다." << endl;
	cout << " - 그럼 편하게 사용해주세요^^" << endl;

	if (keyControl() == TAB) {
		return;
	}
}

void main() {
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
		printf("데이터베이스와의 연결이 끊어졌습니다.");
		return 1;
	}

	query_stat = mysql_query(connection, tableCartName);
	if (query_stat != 0) {
		printf("값을 불러올 수 없습니다.(create)");
		//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
		return 1;
	}

	query_stat = mysql_query(connection, tableHistoryName);
	if (query_stat != 0) {
		printf("값을 불러올 수 없습니다.(create)");
		//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
		return 1;
	}
	sql_result = mysql_store_result(connection);

	
}

//Manager, Customer역할 정하기
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
	gotoxy(54, 11);
	printf("이름 : ");
	fgets(name, 30, stdin);
	CHOP(name);

	gotoxy(52, 12);
	printf("아이디 : ");
	fgets(id, 16, stdin);
	CHOP(id);

	gotoxy(50, 13);
	printf("비밀번호 : ");
	fgets(pw, 16, stdin);
	CHOP(pw);

	gotoxy(50, 13);
	printf("비밀번호 : ");
	for (int i = 0; i < strlen(pw); i++) {
		printf("*");
	}

	gotoxy(45, 14);
	printf("비밀번호 확인 : ");
	fgets(pwCheck, 16, stdin);
	CHOP(pwCheck);

	gotoxy(45, 14);
	printf("비밀번호 확인 : ");
	for (int i = 0; i < strlen(pwCheck); i++) {
		printf("*");
	}

	gotoxy(43, 16);
	if (strcmp(pw, pwCheck)) {
		cout << "비밀번호가 일치하지 않습니다." << endl;
		gotoxy(43, 17);
		cout << "다시 시도해 주십시오" << endl;
		Sleep(2000);
		return 0;
	}

	// 콘솔 출력창의 정보를 담기 위해서 정의한 구조체
	CONSOLE_SCREEN_BUFFER_INFO presentCur;

	//현재 콘솔 위치 반환
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
		printf("입력이 되지 않습니다.(insert)");
		return 1;
	}

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
	gotoxy(presentCur.dwCursorPosition.X + 44, presentCur.dwCursorPosition.Y + 1);
	cout <<"회원가입이 완료 되었습니다." << endl;
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
	gotoxy(52, 11);
	printf("아이디 : ");
	fgets(id, 16, stdin);
	CHOP(id);

	gotoxy(50, 12);
	printf("비밀번호 : ");
	fgets(pw, 16, stdin);
	CHOP(pw);

	gotoxy(50, 12);
	printf("비밀번호 : ");
	for (int i = 0; i < strlen(pw); i++) {
		printf("*");
	}

	query_stat = mysql_query(connection, "select * from login_info");
	if (query_stat != 0) {
		gotoxy(55, 14);
		printf("값을 불러올 수 없습니다.(select)");
		return 1;
	}

	sql_result = mysql_store_result(connection);
	gotoxy(45, 16);
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
		//printf("%s, %s, %s, %s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3]);
		if (!strcmp(id, sql_row[1])) {
			if (!strcmp(pw, sql_row[2])) {
				cout << sql_row[0] << "님, 로그인 되었습니다." << endl;
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
		printf("┃ %3d ┃ %10s ┃ %16s ┃ ", listCount++, sql_row[0], sql_row[1]);
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
	gotoxy(x - 6, y - 1); 
	cout << "━━━━━━━━━━━━━━━━━━━━━" << endl;
	gotoxy(x - 2, y);	
	cout << ">  로그인" << endl;
	gotoxy(x, y + 2);	
	cout << " 회원가입" << endl;
	gotoxy(x, y + 4);	
	cout << " 회원목록" << endl;
	gotoxy(x, y + 6);	
	cout << " 초기화면" << endl;
	gotoxy(x - 6, y + 7);	
	cout << "━━━━━━━━━━━━━━━━━━━━━" << endl << endl;


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

//login메인
void loginMain() {
	system("cls");
	init();
	while (true) {
		//메뉴 선택 -> 함수
		int select = loginMenu();
		if (select == 0) signin();
		else if (select == 2) signup();
		else if (select == 4) idList();
		else if (select == 6) {
			gotoxy(0, 25); break;
		}
	}
}

//------------------------------------------------ MANAGER 함수-----------------------------------------------------

//품목 리스트 출력
int Manager::productList() {
	system("cls");
	selectQuery();
	if (keyControl() == TAB) {
		return 0;
	}
}

//manager품목 추가
int Manager::m_insertQuery() {
	char productName[30];
	char productPrice[10];
	char customerPrice[10];
	char quantity[10];
	bool addCheck = 0;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;

	//TAB누르면 나가기 아니면 계속 진행
	while (true) {
		system("cls");
		selectQuery();
		addCheck = 0;
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
				printf("제품수량 : ");
				fgets(quantity, 10, stdin);
				CHOP(quantity);
				addCheck = 1;

				sprintf(query, "UPDATE product SET quantity = quantity + %d WHERE productName = '%s'", stoi(quantity), productName);
				query_stat = mysql_query(connection, query);
				if (query_stat != 0) {
					//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
					fprintf(stdout, "update가 실행되지 않습니다.(품목 추가 불가)");
					return 1;
				}
				system("cls");
				selectQuery();
				cout << "품목 추가가 완료 되었습니다." << endl;

				mysql_free_result(sql_result);

				if (keyControl() == TAB) {
					return 0;
				}
			}
		}
		if (addCheck == 1) {
			continue;
		}

		printf("제품가격 : ");
		fgets(productPrice, 10, stdin);
		CHOP(productPrice);

		printf("소비자가격 : ");
		fgets(customerPrice, 10, stdin);
		CHOP(customerPrice);

		printf("제품수량 : ");
		fgets(quantity, 10, stdin);
		CHOP(quantity);

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


		
		//mysql_store_result에 사용된 메모리를 헤체시킴-> 마치 malloc의 free역할
		mysql_free_result(sql_result);
		mysql_close(connection);

		if (keyControl() == TAB) {
			break;
		}
	}
	

	return 0;
}

//manager품목 삭제
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

		mysql_free_result(sql_result);
		mysql_close(connection);

		if (keyControl() == TAB) {
			break;
		}
	}
	
}

//manager품목 수정
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
void Manager::updateQueryAllCheck() {
	system("cls");
	cout << "품목을 전체 수정 하시려면 YES" << endl;
	cout << "품목을 전체 삭제 하시려면 NO" << endl;

	if (YN_Check(2, 4) == 0) {
		updateQueryAll();
	}
	else {
		m_deleteQuery();
	}
}

//manager메뉴설정
int Manager::m_updateMenu() {
	system("cls");
	int x = 52;
	int y = 12;

	//메뉴출력
	gotoxy(x - 7, y - 1); //30, 16
	cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
	gotoxy(x - 2, y);	//34, 17
	cout << "> 전체 수정" << endl;
	gotoxy(x, y + 1);	//36, 18
	cout << "제품 이름 수정" << endl;
	gotoxy(x, y + 2);	//36, 19
	cout << "제품 가격 수정" << endl;
	gotoxy(x, y + 3);	//36, 20
	cout << "소비자가격 수정" << endl;
	gotoxy(x, y + 4);	//36, 22
	cout << "이전 화면" << endl;
	gotoxy(x - 7, y + 5);	//36, 25
	cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl << endl;

	//메뉴선택
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

		mysql_free_result(sql_result);
		mysql_close(connection);

		if (keyControl() == TAB) {
			break;
		}
	}
	return 0;
}
//manager출고
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

		mysql_free_result(sql_result);
		mysql_close(connection);

		if (keyControl() == TAB) {
			break;
		}
	}
	return 0;
}

//manager title 출력하기
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

//manager메뉴설정
int Manager::managerMenu() {
	int x = 56;
	int y = 12;

	//메뉴출력
	gotoxy(x - 6, y - 1); //30, 16
	cout << "━━━━━━━━━━━━━━━━━━━━━" << endl;
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
	cout << "이전 화면" << endl;
	gotoxy(x - 6, y + 7);	//36, 25
	cout << "━━━━━━━━━━━━━━━━━━━━━" << endl << endl;

	//메뉴선택
	while (true) {	//무한 반복
		int n = keyControl();
		switch (n) {
		case UP:	//↑를 눌렸을 경우
			if (y > 12) {	//y는 12~18사이만 이동 -> 12보다 커야함
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
			if (y < 18) {	//y는 12~18사이만 이동 -> 18보다 작아야함
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
			return y - 12;	//y-12를 하여 각 값에 대한 1, 2, 3...값을 받을 수 있다. -> 값 선택
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
		printf("데이터베이스와의 연결이 끊어졌습니다.");
		return 1;
	}

	query_stat = mysql_query(connection, "select * from total");
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
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
			return stoi(sql_row[1]);
		}
	}
	return 0;
	mysql_free_result(sql_result);
}

//manager메인
void Manager::managerMain() {
	system("cls");
	managerTitle();
	Sleep(2000);
	init();
	

	while (true) {
		system("cls");
		gotoxy(0, 0);
		printf("누적 총 수입 : %d", totalSelect());
		cout << endl;
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


//--------------------------------------------- CUSTOMER 함수 -----------------------------------------------------

//카트 담긴 품목 리스트 
int Customer::CartList() {
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

	string TCN = "select * from cart_" + tableName + " order by quantity asc";
	const char* seletetableCartName = TCN.c_str();

	query_stat = mysql_query(connection, seletetableCartName);
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
				sprintf(query, "delete from %s where productName='%s'", tableCartName, sql_row[0]);
				query_stat = mysql_query(connection, query);
				continue;
			}
			printf("┃ %3d ┃ %-16s ┃ %8d ┃ %8d ┃\n", cartCount++, sql_row[0], stoi(sql_row[1]), stoi(sql_row[2]));
			cart_Count++;
		}
		printf("┗━━━━━┻━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┛\n");

	}

	mysql_free_result(sql_result);
}

//장바구니 리스트
int Customer::CartListMenu() {
	system("cls");
	CartList();
	if (keyControl() == TAB) {
		return 0;
	}
}

//카트에 물품 추가 => 소비자 가격 끌어오기
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

		string TCN = "select * from cart_" + tableName;
		const char* selecttableCartName = TCN.c_str();

		query_stat = mysql_query(connection, selecttableCartName);
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
					customerPrice = stoi(sql_row[1]);

					sprintf(query, "UPDATE %s set quantity = quantity + %d WHERE productName='%s'", tableCartName, stoi(quantity), productName);
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
					cout << "장바구니에 물품이 담겼습니다." << endl;
					cout << "3초뒤 자동으로 메인화면으로 넘어갑니다..." << endl;
					Sleep(3000);

					mysql_free_result(sql_result);
					mysql_close(connection);
					
					return 0;

				}
			}
		}

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
					addCheck = 1;
					sprintf(query, "insert into %s (productName, customerPrice, quantity, total) values ('%s', '%d', '%d', %d)", tableCartName, productName, customerPrice, stoi(quantity), customerPrice*stoi(quantity));
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
					cout << "장바구니에 물품이 담겼습니다." << endl;
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

//품목 아예 삭제
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

						sprintf(query, "delete from %s where productName='%s'", tableCartName, productName);
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
						cout << "장바구니의 제품 삭제가 완료 되었습니다." << endl;
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
int Customer::deleteAll() {
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
		string TCN = "select * from cart_" + tableName;
		const char* seletetableCartName = TCN.c_str();

		query_stat = mysql_query(connection, seletetableCartName);
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

		cout << "정말 장바구니 내 물품을 모두 삭제하시겠습니까?";

		if (YN_Check(2, presentCur.dwCursorPosition.Y + 2) == 0) {
			

			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
					customerPrice = stoi(sql_row[1]);
					quantity = stoi(sql_row[2]);

					sprintf(query, "UPDATE product SET quantity = quantity + %d WHERE productName = '%s'", quantity, sql_row[0]);
					query_stat = mysql_query(connection, query);

					if (query_stat != 0) {
						printf("값을 삭제할 수 없습니다.(update)");
						Sleep(2000);
						return 1;
					}			
			}
			sprintf(query, "delete from %s;", tableCartName);
			query_stat = mysql_query(connection, query);
			system("cls");
			CartList();
			cout << "장바구니의 모든 제품이 삭제되었습니다." << endl;
			cart_Count = 0;

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
int Customer::deleteCartMenu() {
	system("cls");
	int x = 56, y = 12;
	//메뉴출력
	gotoxy(x - 6, y - 1);	
	cout << "─────────────────────";
	gotoxy(x - 2, y);	
	cout << "> 품목 삭제" << endl;
	gotoxy(x, y + 2);	
	cout << "전체 삭제" << endl;
	gotoxy(x, y + 4);	
	cout << "메인 화면" << endl;
	gotoxy(x - 6, y + 5);	
	cout << "─────────────────────";

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

//카트 삭제
void Customer::deleteCart() {
	switch (deleteCartMenu()) {
	case 0: delCartProduct(); break;
	case 2: deleteAll(); break;
	case 4:  break;
	}
}

//수량추가
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
			printf("데이터베이스와의 연결이 끊어졌습니다.");
			return 1;
		}

		printf("제품명 : ");
		fgets(productName, 30, stdin);
		CHOP(productName);

		printf("추가 수량 : ");
		fgets(minusQuantity, 10, stdin);
		CHOP(minusQuantity);


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

					sprintf(query, "UPDATE %s SET quantity = quantity + %d WHERE productName = '%s'", tableCartName,  stoi(minusQuantity), productName);
					query_stat = mysql_query(connection, query);

					sprintf(query, "UPDATE product SET quantity = quantity - %d WHERE productName = '%s'", stoi(minusQuantity), productName);
					query_stat = mysql_query(connection, query);
					if (query_stat != 0) {
						printf("update가 취소되었습니다.");
						Sleep(2000);
						return 1;
					}
					system("cls");
					CartList();
					cout << "장바구니 제품의 수량이 추가되었습니다." << endl;
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

//수량 삭제
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
			printf("데이터베이스와의 연결이 끊어졌습니다.");
			return 1;
		}

		printf("제품명 : ");
		fgets(productName, 30, stdin);
		CHOP(productName);

		printf("삭제 수량 : ");
		fgets(minusQuantity, 10, stdin);
		CHOP(minusQuantity);

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

					sprintf(query, "UPDATE %s SET quantity = quantity - %d WHERE productName = '%s'", tableCartName, stoi(minusQuantity), productName);
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
					cout << "장바구니 제품의 수량이 감소되었습니다." << endl;
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

//카트 변경 메뉴
int Customer::updateCartMenu() {
	system("cls");
	int x = 56, y = 12;
	//메뉴출력
	gotoxy(x - 6, y - 1);	
	cout << "─────────────────────";
	gotoxy(x - 2, y);	
	cout << "> 수량 추가" << endl;
	gotoxy(x, y + 2);	
	cout << "수량 삭제" << endl;
	gotoxy(x, y + 4);	
	cout << "메인 화면" << endl;
	gotoxy(x - 6, y + 5);	
	cout << "─────────────────────";

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

//카트 물품 변경
void Customer::UpdateCart() {
	switch (updateCartMenu()) {
	case 0: updatePlusCartQuantity(); break;
	case 2: updateMinusCartQuantity(); break;
	case 4:  break;
	}
}

//구매
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
		printf("데이터베이스와의 연결이 끊어졌습니다.");
		Sleep(2000);
		return 1;
	}

	string TCN = "select * from cart_" + tableName;
	const char* seletetableCartName = TCN.c_str();

	query_stat = mysql_query(connection, seletetableCartName);

	if (query_stat != 0) {
		printf("값을 불러올 수 없습니다.(select)");
		Sleep(2000);
		return 1;
	}
	sql_result = mysql_store_result(connection);

	
	if (cart_Count == 0) {
		cout << "카트에 구매할 품목이 없습니다." << endl;
		Sleep(2000);
		return 0;
	}
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
		
		cart_Total += stoi(sql_row[3]);

		if (query_stat != 0) {
			printf("주문 내역을 추가할 수 없습니다.");
			Sleep(2000);
			return 1;
		}
	}
	CartList();
	printf("┏━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("┃  총합  ┃ %35d ┃\n", cart_Total);
	printf("┗━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	// 콘솔 출력창의 정보를 담기 위해서 정의한 구조체
	CONSOLE_SCREEN_BUFFER_INFO presentCur;

	//현재 콘솔 위치 반환
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);

	cout << endl << "정말 구매 하시겠습니까?" << endl;

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
					//printf("\n\n구매 내역을 추가할 수 없습니다.");
					fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
					Sleep(2000);
					return 1;
				}
			}

		}
		sprintf(query, "delete from %s;", tableCartName);
		query_stat = mysql_query(connection, query);

		if (query_stat != 0) {
			printf("값을 삭제할 수 없습니다.(delete)");
			Sleep(2000);
			return 1;
		}

		cart_Count = 0;

		system("cls");
		cout << "구매가 완료되었습니다." << endl;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
		cout << "지금까지의 주문내역을 보시겠습니까?" << endl;
		if (YN_Check(2, presentCur.dwCursorPosition.Y + 2) == 0) {
			system("cls");

			string THN = "select * from history_" + tableName;
			const char* seletetableHistoryName = THN.c_str();

			query_stat = mysql_query(connection, seletetableHistoryName);
			if (query_stat != 0) {
				printf("값을 불러올 수 없습니다.(select)");
				return 1;
			}

			sql_result = mysql_store_result(connection);
			if (sql_result == NULL) {
				cout << "Empty!!" << endl;
			}
			else {
				printf("┏━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┓\n");
				printf("┃ %8s ┃ %16s ┃ %-16s ┃ %8s ┃ %8s ┃\n", "구매여부", "날짜", "제품명", "가격", "수량");
				printf("┣━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━┫\n");
				while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
					printf("┃ %8s ┃ %16s ┃ %-16s ┃ %8d ┃ %8d ┃\n", sql_row[0], sql_row[1], sql_row[2], stoi(sql_row[3]), stoi(sql_row[4]));	//출력
				}
				printf("┗━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┛\n");

			}
		}
		else {
			system("cls");
			cout << "메인으로 가고자 하시면 TAB키를 눌러주세요.." << endl;
		}
		mysql_free_result(sql_result);
		mysql_close(connection);
	}
	else {
		system("cls");
		cout << "현재까지의 상품을 저장합니다." << endl;
	}
	

	if (keyControl() == TAB) {
		return 0;
	}
}

//환불
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
			printf("데이터베이스와의 연결이 끊어졌습니다.");
			return 1;
		}

		string THN = "select * from history_" + tableName;
		const char* seletetableHistoryName = THN.c_str();

		query_stat = mysql_query(connection, seletetableHistoryName);
		if (query_stat != 0) {
			printf("값을 불러올 수 없습니다.(select)");
			return 1;
		}

		sql_result = mysql_store_result(connection);

		printf("┏━━━━━━━━━━┳━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
		printf("┃ %8s ┃ %10s ┃ %16s ┃ %8s ┃ %48s ┃\n", "주문", "날짜", "제품명", "수량", "환불 사유");
		printf("┣━━━━━━━━━━╋━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
			if (sql_row[5] == NULL) {
				printf("┃ %8s ┃ %10s ┃ %16s ┃ %8d ┃ %48s ┃\n", sql_row[0], sql_row[1], sql_row[2], stoi(sql_row[4]), "");	//출력
			}
			else {
				printf("┃ %8s ┃ %10s ┃ %16s ┃ %8d ┃ %48s ┃\n", sql_row[0], sql_row[1], sql_row[2], stoi(sql_row[4]), sql_row[5]);	//출력
			}
		}
		printf("┗━━━━━━━━━━┻━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");


		printf("제품명 : ");
		fgets(productName, 30, stdin);
		CHOP(productName);

		printf("환불사유(100자 이내) : ");
		fgets(refund_reason, 100, stdin);
		CHOP(refund_reason);

		// 콘솔 출력창의 정보를 담기 위해서 정의한 구조체
		CONSOLE_SCREEN_BUFFER_INFO presentCur;

		//현재 콘솔 위치 반환
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);

		cout << endl << "정말 환불 하시겠습니까?" << endl;

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
								printf("\n\n환불 내역을 추가할 수 없습니다.");
								//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
								Sleep(2000);
								return 1;
							}
							sprintf(query, "UPDATE total SET managerTotal = managerTotal - %d WHERE id = 1", stoi(sql_row[3]) * stoi(sql_row[4]));
							query_stat = mysql_query(connection, query);
							if (query_stat != 0) {
								printf("\n\n수익을 추가 할 수 없습니다.");
								//fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
								Sleep(2000);
								return 1;
							}
							sprintf(query, "UPDATE product SET quantity = quantity + %d WHERE productName = '%s'", stoi(sql_row[4]), productName);
							query_stat = mysql_query(connection, query);

							if (query_stat != 0) {
								printf("\n\n제품 수량을 추가할 수 없습니다.");
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
				cout << "주문 이력이 없습니다." << endl; 
				cout << "3초뒤 자동으로 메인화면으로 이동합니다..." << endl;
				Sleep(3000);
				return 0;
			case 2: cout << "해당하는 제품이 없습니다." << endl; 
				cout << "3초뒤 자동으로 메인화면으로 이동합니다..." << endl;
				Sleep(3000);
				return 0;
			case 3: cout << "환불이 완료되었습니다." << endl << endl;
				Sleep(1000); break;
			}

			
			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
			cout << "지금까지의 주문내역을 보시겠습니까?" << endl;
			if (YN_Check(2, presentCur.dwCursorPosition.Y + 2) == 0) {
				system("cls");
				string THN = "select * from history_" + tableName;
				const char* seletetableHistoryName = THN.c_str();

				query_stat = mysql_query(connection, seletetableHistoryName);
				if (query_stat != 0) {
					printf("값을 불러올 수 없습니다.(select)");
					return 1;
				}

				sql_result = mysql_store_result(connection);
				if (sql_result == NULL) {
					cout << "Empty!!" << endl;
				}
				else {
					printf("┏━━━━━━━━━━┳━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
					printf("┃ %8s ┃ %10s ┃ %16s ┃ %8s ┃ %48s ┃\n", "주문", "날짜", "제품명", "수량", "환불 사유");
					printf("┣━━━━━━━━━━╋━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
						if (sql_row[5] == NULL) {
							printf("┃ %8s ┃ %10s ┃ %16s ┃ %8d ┃ %48s ┃\n", sql_row[0], sql_row[1], sql_row[2], stoi(sql_row[4]), "");	//출력
						}
						else {
							printf("┃ %8s ┃ %10s ┃ %16s ┃ %8d ┃ %48s ┃\n", sql_row[0], sql_row[1], sql_row[2], stoi(sql_row[4]), sql_row[5]);	//출력
						}
					}
					printf("┗━━━━━━━━━━┻━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
				}
			}
			else {
				system("cls");
				cout << "메인으로 가고자 하시면 TAB키를 눌러주세요.." << endl;
			}

			mysql_free_result(sql_result);
			mysql_close(connection);
		}

		else {
			system("cls");
			cout << "환불을 취소합니다." << endl;
		}

		if (keyControl() == TAB) {
			return 0;
		}
	}
}

//주문 내역 리스트
int Customer::historyList() {
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

	string THN = "select * from history_" + tableName;
	const char* seletetableHistoryName = THN.c_str();

	query_stat = mysql_query(connection, seletetableHistoryName);
	if (query_stat != 0) {
		printf("값을 불러올 수 없습니다.(select)");
		return 1;
	}

	sql_result = mysql_store_result(connection);
	if (sql_result == NULL) {
		cout << "Empty!!" << endl;
	}
	else {
		printf("┏━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┓\n");
		printf("┃ %8s ┃ %16s ┃ %-16s ┃ %8s ┃ %8s ┃\n", "구매여부", "날짜", "제품명", "가격", "수량");
		printf("┣━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━┫\n");
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
			printf("┃ %8s ┃ %16s ┃ %-16s ┃ %8d ┃ %8d ┃\n", sql_row[0], sql_row[1], sql_row[2], stoi(sql_row[3]), stoi(sql_row[4]));	//출력
		}
		printf("┗━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┛\n");

	}
	mysql_free_result(sql_result);

	if (keyControl() == TAB) {
		return 0;
	}
}

//customer title 출력하기
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

//메뉴설정
int Customer::customerMenu() {
	system("cls");
	int x = 56;
	int y = 12;

	//메뉴출력
	gotoxy(x - 6, y - 1); 
	cout << "─────────────────────" << endl;
	gotoxy(x - 2, y);	
	cout << "> 카트 목록" << endl;
	gotoxy(x, y + 1);	
	cout << "카트 추가" << endl;
	gotoxy(x, y + 2);	
	cout << "카트 삭제" << endl;
	gotoxy(x, y + 3);	
	cout << "수량 변경" << endl;
	gotoxy(x, y + 4);	
	cout << "주문 내역" << endl;
	gotoxy(x, y + 5);	
	cout << "구     매" << endl;
	gotoxy(x, y + 6);
	cout << "환     불" << endl;
	gotoxy(x, y + 7);
	cout << "종     료" << endl;
	gotoxy(x - 6, y + 8);	
	cout << "─────────────────────" << endl << endl;

	//메뉴선택
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

//고객 메인
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

//--------------------------------------------------공통 함수-----------------------------------------------------
//데이터 출력
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
			if (cy > y) {	//y는 17~24사이만 이동 -> 17보다 커야함s
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

//초기화면 구성
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