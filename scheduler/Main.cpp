#include "stdafx.h"
#include "inicontrol.h"

bool finish = true; //스레드 종료변수

//시간관리 변수
time_t t;
struct tm ptm;
char today[5]="";
char daycheck[5] = "";
control con;

//함수선언
DWORD WINAPI time(LPVOID); //시간관리용 스레드 함수선언
DWORD WINAPI alarm(LPVOID); //알람용 스레드 함수선언

int main(int argc, char* argv[]) {
	DWORD timeID, alarmID;
	HANDLE hthread[2];
	int msg, cin, input, mon;
	const char* check = "";

	//변수초기화
	msg = 0;
	cin = 0;

	SetConsoleTitle(TEXT("Scheduler"));

	printf("\nScheduler!");

	time(&t);
	localtime_s(&ptm, &t);
	strftime(today, sizeof(today), "%m%d", &ptm);
	for (int j = 0; j < 5; j++) {
		daycheck[j] = today[j];
	}
	con.controltime();

	hthread[0] = CreateThread(NULL, 0, time, NULL, 0, &timeID); //시간관리용 스레드실행
	hthread[1] = CreateThread(NULL, 0, alarm, NULL, 0, &alarmID); //시간관리용 스레드실행

	Sleep(1000);
	printf("\n...스케쥴러! 를 실행하려면 엔터를 입력하세요.");
	getchar();

	//프로그램 시작

	while (finish) {
		system("cls");
		printf("\n수행할 작업을 선택하세요\n\n");
		printf("     1.스케쥴보기\n     2.스케쥴추가하기\n     3.스케쥴삭제하기\n     4.스케쥴검색하기\n     5.About Scheduler!\n     6.종료\n\n입력 : ");
		scanf_s("%d", &cin);
		system("cls");
		if (cin == 1) {
			printf("\n1.오늘의 스케쥴\n2.월단위 스케쥴보기\n3.일단위 스케쥴보기\n\n입력 : ");
			scanf_s("%d", &input);
			if (input == 1) {
				con.controltime();
				con.clear();
			}
			else if (input == 3) {
				system("cls");
				con.get();
				con.read();
				con.clear();
			}
			else if(input ==2){
				system("cls");
				printf("\n스케쥴을 보고 싶은 달이 몇월인가요?\n\n입력 : ");
				scanf_s("%d", &mon);
				if (mon < 1 || mon>12) {
					printf("\n유효하지 않은 달입력입니다.");
					con.clear();
				}
				else {
					con.allprint(mon);
				}
			}
		}
		else if (cin == 2) {
			con.write();
		}
		else if (cin == 3) {
			con.del();
		}
		else if (cin == 4) {
			printf("\n기술상의 문제로 아직 구현되지 않았습니다.\n");
			con.clear();
		}
		else if (cin == 5) {
			printf("\n Scheduler!\n\n");
			printf("   Made by Sion C. Rusate");
			printf("\n\n      With KSOProject\n\n");
			printf("\n Copyrightⓒ2016  박승운. All rights reserved.\n\n");
			con.clear();
		}
		else if (cin == 6) {
			msg = MessageBox(NULL, TEXT("정말 종료하시겠습니까?"), "종료", MB_YESNO);
			if (msg == IDYES) finish = false;
		}
		else {
			while (getchar() != '\n');
		}
		
	}
		
	printf("스케쥴러 닫는중...");

	WaitForMultipleObjects(2, hthread, TRUE, INFINITE);

	return 0;
}

DWORD WINAPI time(LPVOID) {
	int checkday = 0;
	while (finish) {
		time(&t);
		localtime_s(&ptm, &t);
		strftime(today, sizeof(today), "%m%d", &ptm);
		checkday = 0;
		for (int j = 0; j < 5; j++) {
			if (daycheck[j] != today[j]) {
				checkday++;
			}
		}
		if (checkday != 0) {
			for (int j = 0; j < 5; j++) {
				daycheck[j] = today[j];
			}
			con.controltime();
			MessageBox(NULL, "날짜가 변경되었습니다.", "다음날!", MB_OK);
		}
		Sleep(1000);
	}
	return 0;
}

DWORD WINAPI alarm(LPVOID) {
	while (finish) {
		con.alarm();
		Sleep(1000);
	}
	return 0;
}