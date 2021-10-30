#include<stdio.h>
#include<Windows.h>
int main()
{
	CONSOLE_SCREEN_BUFFER_INFO presentCur;
	// 콘솔 출력창의 정보를 담기 위해서 정의한 구조체
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);

	//현재 커서의 위치 정보를 저장하는 함수
	printf("%d, %d\n", presentCur.dwCursorPosition.X, presentCur.dwCursorPosition.Y);

	//구조체의 저장한 값 출력
	printf("\n\n ");
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);

	printf("%d, %d\n", presentCur.dwCursorPosition.X, presentCur.dwCursorPosition.Y);
	return 0;
}
