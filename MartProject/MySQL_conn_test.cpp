//#include<my_global.h>
#include<winsock2.h>
#include<mysql.h>
#include<stdio.h>
#pragma commnet(lib, "libmysql.lib")

void main() {
	//printf("MySQL client Version : %s\n", mysql_get_client_info);
	MYSQL mysql;
	mysql_init(&mysql);
	if (!mysql_real_connect(&mysql, "localhost", "root", "mirim", "cpptest_db", 3306, NULL, 0)) {
		printf("error");
	}
	else
	{
		printf("success");
		mysql_close(&mysql);
	}
}