#include<stdio.h>
#include<stdlib.h>
#include<mysql.h>

void finish_with_error(MYSQL* conn) {
	fprintf(stderr, "%s\n", mysql_error(conn));
	mysql_close(conn);
	exit(0);
}

int main(int argc, char* argv[]) {
	MYSQL* conn = mysql_init(NULL);
	if (conn == NULL) {
		fprintf(stderr, "%s\n", mysql_error(conn));	
		exit(1);
	}
	if (mysql_real_connect(conn, "localhost", "xeno", "123456", "testdb", 0, NULL, 0) == NULL) {
		finish_with_error(conn);
	}
	if (mysql_query(conn, "DROP TABLE IF EXISTS CARs")) {
		finish_with_error(conn);
	}
	if (mysql_query(conn, "CREATE TABLE Cars(ID INT, Name TEXT, Price INT")) {
		finish_with_error(conn);
	}
	if (mysql_query(conn, "INSERT INTO Cars VALUES(1, 'Audi', 52642)")) {
		finish_with_error(conn);
	}
	if (mysql_query(conn, "INSERT INTO Cars VALUES(2, 'Mercedes', 57127)")) {
		finish_with_error(conn);
	}
	if (mysql_query(conn, "INSERT INTO Cars VALUES(3, ¡®Skoda¡¯, 9000)"))
	{
		finish_with_error(conn);
	}
	if (mysql_query(conn, "INSERT INTO Cars VALUES(4, ¡®Volvo¡¯, 29000)"))
	{
		finish_with_error(conn);
	}
	if (mysql_query(conn, "INSERT INTO Cars VALUES(5, ¡®Bentley¡¯, 350000)"))
	{
		finish_with_error(conn);
	}
	if (mysql_query(conn, "INSERT INTO Cars VALUES(6, ¡®Citroen¡¯, 21000)"))
	{
		finish_with_error(conn);
	}
	if (mysql_query(conn, "INSERT INTO Cars VALUES(7, ¡®Hummer¡¯, 41400)"))
	{
		finish_with_error(conn);
	}
	if (mysql_query(conn, "INSERT INTO Cars VALUES(8, ¡®Volkswagen¡¯, 21600)"))
	{
		finish_with_error(conn);
	}
	mysql_close(conn);
	exit(0);
}