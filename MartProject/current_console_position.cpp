#include<stdio.h>
#include<Windows.h>
int main()
{
	CONSOLE_SCREEN_BUFFER_INFO presentCur;
	// �ܼ� ���â�� ������ ��� ���ؼ� ������ ����ü
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);

	//���� Ŀ���� ��ġ ������ �����ϴ� �Լ�
	printf("%d, %d\n", presentCur.dwCursorPosition.X, presentCur.dwCursorPosition.Y);

	//����ü�� ������ �� ���
	printf("\n\n ");
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);

	printf("%d, %d\n", presentCur.dwCursorPosition.X, presentCur.dwCursorPosition.Y);
	return 0;
}
