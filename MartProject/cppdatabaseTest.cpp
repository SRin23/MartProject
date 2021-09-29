#define _CRT_SECURE_NO_WARNINGS
#define SOCKET int



#include <string.h>

#include <mysql.h>

#include<iostream>

using namespace std;


#pragma comment(lib, "libmysql.lib")

#pragma comment(lib, "ws2_32.lib")  



#define DB_HOST "localhost"//"호스트IP, 도메인또는localhost"

#define DB_USER "root"

#define DB_PASS "mirim"

#define DB_NAME "cpptest_db"



#define SQL_CREATE_TABLE  "CREATE TABLE playerinfo(id INT AUTO_INCREMENT, name VARCHAR(30), xpos INT, PRIMARY KEY(id));"

#define SQL_INSERT_RECORD "INSERT INTO playerinfo VALUES (NULL, %s, %d); " 

#define SQL_SELECT_RECORD "SELECT * FROM playerinfo"

#define SQL_DROP_TABLE "DROP TABLE playerinfo"


int main()

{

    MYSQL* connection = NULL, conn;

    MYSQL_RES* sql_result;

    MYSQL_ROW sql_row;

    int query_stat;

    int i;



    char query[255];



    mysql_init(&conn);



    // DB 연결

    connection = mysql_real_connect(&conn, DB_HOST,

        DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);

    if (connection == NULL)

    {

        fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));

        return 1;

    }



    // 테이블삭제

    query_stat = mysql_query(connection, SQL_DROP_TABLE);

    if (query_stat != 0)

    {

        fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));

        //          return 1;

    }



    //한글사용을위해추가.

    mysql_query(connection, "set session character_set_connection=euckr;");

    mysql_query(connection, "set session character_set_results=euckr;");

    mysql_query(connection, "set session character_set_client=euckr;");



    //// 테이블생성

    query_stat = mysql_query(connection, SQL_CREATE_TABLE);

    if (query_stat != 0)

    {

        cout << "여기?" << endl;

        fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));

        return 1;

    }



    // 레코드삽입

    for (i = 0; i < 5; i++)

    {

        sprintf(query, SQL_INSERT_RECORD, "'ㅁㅁㅁ'", 100 + i);

        cout << query << endl;

        query_stat = mysql_query(connection, query);



        if (query_stat != 0)

        {

            cout << "여기" << endl;

            fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));

            return 1;

        }

    }



    // 셀렉트

    query_stat = mysql_query(connection, SQL_SELECT_RECORD);

    if (query_stat != 0)

    {

        fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));

        return 1;

    }



    // 결과출력

    sql_result = mysql_store_result(connection);

    while ((sql_row = mysql_fetch_row(sql_result)) != NULL)

    {

        printf("%2s %2s %s\n", sql_row[0], sql_row[1], sql_row[2]);

    }

    mysql_free_result(sql_result);



    // 테이블삭제

    query_stat = mysql_query(connection, SQL_DROP_TABLE);

    if (query_stat != 0)

    {

        fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));

        return 1;

    }



    // DB 연결닫기

    mysql_close(connection);

    return 0;

}