#include<stdio.h>
#include<stdlib.h>
#include<mysql.h>

int main() {

	printf("MYSQL 클라이언트 버전 : %s\n", mysql_get_client_info());	//MYSQL의 클라이언트 버전을 화면에 표시

	exit(0);
}