#include<stdio.h>
#include<stdlib.h>
#include<mysql.h>

int main() {

	printf("MYSQL Ŭ���̾�Ʈ ���� : %s\n", mysql_get_client_info());	//MYSQL�� Ŭ���̾�Ʈ ������ ȭ�鿡 ǥ��

	exit(0);
}