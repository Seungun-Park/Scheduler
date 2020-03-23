#include "stdafx.h"
#include "inicontrol.h"

bool finish = true; //������ ���ắ��

//�ð����� ����
time_t t;
struct tm ptm;
char today[5]="";
char daycheck[5] = "";
control con;

//�Լ�����
DWORD WINAPI time(LPVOID); //�ð������� ������ �Լ�����
DWORD WINAPI alarm(LPVOID); //�˶��� ������ �Լ�����

int main(int argc, char* argv[]) {
	DWORD timeID, alarmID;
	HANDLE hthread[2];
	int msg, cin, input, mon;
	const char* check = "";

	//�����ʱ�ȭ
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

	hthread[0] = CreateThread(NULL, 0, time, NULL, 0, &timeID); //�ð������� ���������
	hthread[1] = CreateThread(NULL, 0, alarm, NULL, 0, &alarmID); //�ð������� ���������

	Sleep(1000);
	printf("\n...�����췯! �� �����Ϸ��� ���͸� �Է��ϼ���.");
	getchar();

	//���α׷� ����

	while (finish) {
		system("cls");
		printf("\n������ �۾��� �����ϼ���\n\n");
		printf("     1.�����캸��\n     2.�������߰��ϱ�\n     3.����������ϱ�\n     4.������˻��ϱ�\n     5.About Scheduler!\n     6.����\n\n�Է� : ");
		scanf_s("%d", &cin);
		system("cls");
		if (cin == 1) {
			printf("\n1.������ ������\n2.������ �����캸��\n3.�ϴ��� �����캸��\n\n�Է� : ");
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
				printf("\n�������� ���� ���� ���� ����ΰ���?\n\n�Է� : ");
				scanf_s("%d", &mon);
				if (mon < 1 || mon>12) {
					printf("\n��ȿ���� ���� ���Է��Դϴ�.");
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
			printf("\n������� ������ ���� �������� �ʾҽ��ϴ�.\n");
			con.clear();
		}
		else if (cin == 5) {
			printf("\n Scheduler!\n\n");
			printf("   Made by Sion C. Rusate");
			printf("\n\n      With KSOProject\n\n");
			printf("\n Copyright��2016  �ڽ¿�. All rights reserved.\n\n");
			con.clear();
		}
		else if (cin == 6) {
			msg = MessageBox(NULL, TEXT("���� �����Ͻðڽ��ϱ�?"), "����", MB_YESNO);
			if (msg == IDYES) finish = false;
		}
		else {
			while (getchar() != '\n');
		}
		
	}
		
	printf("�����췯 �ݴ���...");

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
			MessageBox(NULL, "��¥�� ����Ǿ����ϴ�.", "������!", MB_OK);
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