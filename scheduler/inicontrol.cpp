#include "inicontrol.h"

const char* day = "";
const char* name = "";
const char* timet = "";
char daytemp[5] = "", nametemp[100] = "", temp[100] = "", timetemp[5] = "", inic[100] = "", temp2[100] ="",init[5]="";
char schedule[100][100] = { "" };
char scheduletime[100][100] = { "" };

char alarmtoday[5] = "";
char timecheck[5] = "";

int scheduleindex = 0;
int ini, tempd, tempt;
time_t controlt;
struct tm controlptm;
char controltoday[5];

time_t tm;
struct tm ptmm;
char todaym[5] = "";

void control::clear() {
	while (getchar() != '\n');
	printf("\n...���͸� �Է��ϼ���.");
	getchar();
	system("cls");
	return;
}

void control::controltime() {
	scheduleindex = 0;
	time(&controlt);
	localtime_s(&controlptm, &controlt);
	strftime(controltoday, sizeof(controltoday), "%m%d", &controlptm);
	day = controltoday;
	printf("\n[%c%c�� %c%c���� ������]\n", controltoday[0], controltoday[1], controltoday[2], controltoday[3]);

	for (int i = 1;; i++) {
		sprintf_s(nametemp, "%d", i);
		GetPrivateProfileString(day, nametemp, "Default", inic, sizeof(inic), "./Source/schedule.ini");
		if (inic[0] == 'D'&&inic[1] == 'e'&&inic[2] == 'f'&&inic[3] == 'a'&&inic[4] == 'u'&&inic[5] == 'l'&&inic[6] == 't') break;
		ini = ::GetPrivateProfileInt(day, inic, 0000, "./Source/schedule.ini");
		GetPrivateProfileString(day, inic, "opps", init, sizeof(init), "./Source/schedule.ini");
		if (ini < 1000) {
			init[3] = init[2];
			init[2] = init[1];
			init[1] = init[0];
			init[0]='0';
		}
		printf("%d. %s | %c%c�� %c%c��\n", i, inic, init[0], init[1], init[2], init[3]);
		for (int k = 0; inic[k] != '\0'; k++) {
			schedule[i][k] = inic[k];
		}
		for (int k = 0; k < 4; k++) {
			scheduletime[i][k] = init[k];
		}
		scheduleindex = i;
	}
	return;
}

void control::alarm() {
	int checktime = 0, scht=0;
	time(&tm);
	localtime_s(&ptmm, &tm);
	strftime(todaym, sizeof(todaym), "%m%d", &ptmm);
	strftime(alarmtoday, sizeof(alarmtoday), "%H%M", &ptmm);
	for (int j = 0; j < 5; j++) {
		if (timecheck[j] != alarmtoday[j]) {
			checktime++;
		}
	}
	if (checktime != 0) {
		for (int j = 0; j < 5; j++) {
			timecheck[j] = alarmtoday[j];
		}
		for (int k = 1; k <= scheduleindex; k++) {
			scht = 0;
			for (int q = 0; q < 4; q++) {
				if (scheduletime[k][q] == alarmtoday[q]) {
					scht++;
				}
			}
			if (scht == 4) {
				MessageBox(NULL, schedule[k], "������ �˶�!", MB_OK);
				break;
			}
		}
	}
	return;
}

void control::get() {
	printf("\n�������� ������ �ϴ� ��¥�� ���ڸ� ���ڷ� �Է��ϼ���. \n(��)12�� 3�� -> 1203\n�Է� : ");
	scanf_s("%d", &tempd);
	sprintf_s(daytemp, "%d", tempd);
	day = daytemp;
	return;
}

void control::read() { //�д��Լ�
	int i = 1;
	sprintf_s(nametemp, "%d", i);
	GetPrivateProfileString(day, nametemp, "Default", inic, sizeof(inic), "./Source/schedule.ini");
	ini = ::GetPrivateProfileInt(day, inic, 0000, ".Source//schedule.ini");
	if (inic[0] == 'D'&&inic[1] == 'e'&&inic[2] == 'f'&&inic[3] == 'a'&&inic[4] == 'u'&&inic[5] == 'l'&&inic[6] == 't') return;
	printf("\n[%d�� %d���� ������]\n", tempd / 100, tempd % 100);
	printf("%d. %s | %d�� %d��\n", i, inic, ini / 100, ini % 100);
	for (i = 2;; i++) {
		sprintf_s(nametemp, "%d", i);
		GetPrivateProfileString(day, nametemp, "Default", inic, sizeof(inic), "./Source/schedule.ini");
		ini = ::GetPrivateProfileInt(day, inic, 0000, "./Source/schedule.ini");
		if (inic[0] == 'D'&&inic[1] == 'e'&&inic[2] == 'f'&&inic[3] == 'a'&&inic[4] == 'u'&&inic[5] == 'l'&&inic[6] == 't') break;
		printf("%d. %s | %d�� %d��\n", i, inic, ini / 100, ini % 100);
	}
	return;
}



void control::write() {
	//��¥ �Է�
	printf("\n�߰��� �������� ��¥�� ���ڸ� ���ڷ� �Է��ϼ���. \n(��)12�� 3�� -> 1203.\n (��Ҵ� 0�� �Է��ϼ���)\n\n�Է� : ");
	fflush(stdin);
	scanf_s("%d", &tempd);
	if (tempd == 0) { //cancel
		system("cls");
		return;
	}

	//��¥�� �޷���
	if ((tempd / 100) < 1 || (tempd % 100) < 1 || (tempd / 100)>12) {
		printf("\n��ȿ�� ��¥�� �ƴմϴ�.");
		clear();
		write();
		return;
	}
	if ((((tempd % 100) > 30) && ((tempd / 100) == 4 | 6 | 9 | 11)) || (((tempd % 100) > 31) && ((tempd / 100) == 1 | 3 | 5 | 7 | 8 | 10 | 12)) || (((tempd % 100) > 29) && ((tempd / 100) == 2))) {
		printf("\n��ȿ�� ��¥�� �ƴմϴ�.");
		clear();
		write();
		return;
	}

	sprintf_s(daytemp, "%d", tempd);
	day = daytemp;

	//������ �Է�
	system("cls");
	read();
	printf("\n�߰��� �������� �̸��� �Է��ϼ���.\n (��Ҵ� 'cancel'�� �Է��ϼ���)\n\n�Է� : ");
	fflush(stdin);
	scanf_s("%s", nametemp, sizeof(nametemp));

	if (nametemp[0] == 'c'&&nametemp[1] == 'a'&&nametemp[2] == 'n'&&nametemp[3] == 'c'&&nametemp[4] == 'e'&&nametemp[5] == 'l') {
		system("cls");
		return;
	}//cancel

	 //�ð��Է�
	printf("\n�߰��� �������� ���۽ð��� ���ڸ� ���ڷ� �Է��ϼ���. \n(��)���� 6�� 40�� -> 1840\n\n �Է� : ");
	fflush(stdin);
	scanf_s("%d", &tempt);

	//�ð��� �޷���
	if (tempt<0 || (tempt / 100)>23 || (tempt % 100)>59) {
		printf("\n��ȿ�� �ð��� �ƴմϴ�.");
		clear();
		write();
		return;
	}

	name = nametemp;
	sprintf_s(timetemp, "%d", tempt);
	timet = timetemp;


	for (int i = 1;; i++) { //����ִ� ���� ã��
		sprintf_s(temp, "%d", i);
		GetPrivateProfileString(day, temp, "Default", inic, sizeof(inic), "./Source/schedule.ini");
		if (inic[0] == 'D'&&inic[1] == 'e'&&inic[2] == 'f'&&inic[3] == 'a'&&inic[4] == 'u'&&inic[5] == 'l'&&inic[6] == 't') break;
	}
	WritePrivateProfileString(day, temp, name, "./Source/schedule.ini");
	WritePrivateProfileString(day, name, timet, "./Source/schedule.ini");

	printf("���������� �߰��Ǿ����ϴ�.\n");

	Sleep(1000);
	system("cls");
	read();
	clear();
	return;
}

void control::del() {
	printf("\n������ �������� ��¥�� �Է��ϼ���.\n (��Ҵ� 0�� �Է��ϼ���)\n\n�Է� : ");
	fflush(stdin);
	scanf_s("%d", &tempd);

	if (tempd == 0) { //cancel
		system("cls");
		return;
	}

	//��¥�� �޷���
	if ((tempd / 100) < 1 || (tempd % 100) < 1 || (tempd / 100)>12) {
		printf("\n��ȿ�� ��¥�� �ƴմϴ�.");
		clear();
		write();
		return;
	}
	if ((((tempd % 100) > 30) && ((tempd / 100) == 4 | 6 | 9 | 11)) || (((tempd % 100) > 31) && ((tempd / 100) == 1 | 3 | 5 | 7 | 8 | 10 | 12)) || (((tempd % 100) > 29) && ((tempd / 100) == 2))) {
		printf("\n��ȿ�� ��¥�� �ƴմϴ�.");
		clear();
		write();
		return;
	}

	sprintf_s(daytemp, "%d", tempd);
	day = daytemp;

	system("cls");
	read();
	printf("������ �������� �̸��� �Է��ϼ���.\n (��Ҵ� 'cancel'�� �Է��ϼ���)\n\n�Է� : ");
	fflush(stdin);
	scanf_s("%s", nametemp, sizeof(nametemp));

	if (nametemp[0] == 'c'&&nametemp[1] == 'a'&&nametemp[2] == 'n'&&nametemp[3] == 'c'&&nametemp[4] == 'e'&&nametemp[5] == 'l') {
		system("cls");
		return;
	}//cancel

	int q;
	int check = 0;
	name = nametemp;
	WritePrivateProfileString(day, name, NULL, "./Source/schedule.ini");
	for (int i = 1;; i++) { //�ش��׸� ã��
		for (int k=0; nametemp[k] != '\0'; k++) {
			check++;
		}
		q = i;
		sprintf_s(temp, "%d", i);
		GetPrivateProfileString(day, temp, "Default", inic, sizeof(inic), "./Source/schedule.ini");
		for (int k=0; nametemp[k] != '\0'; k++) {
			if (inic[k] == nametemp[k]) {
				check--;
			}
		}
		if (check == 0) {
			break;
		}
		if (inic[0] == 'D'&&inic[1] == 'e'&&inic[2] == 'f'&&inic[3] == 'a'&&inic[4] == 'u'&&inic[5] == 'l'&&inic[6] == 't') { check = -1; break; }
	}
	if (check == -1) {
		printf("\n...�׸��� �������� �ʽ��ϴ�.");
	}
	else {
		for (int i = q;; i++) { //����
			int w;
			w = i + 1;
			sprintf_s(temp2, "%d", w);
			sprintf_s(temp, "%d", i);
			GetPrivateProfileString(day, temp2, "Default", inic, sizeof(inic), "./Source/schedule.ini");
			printf("������...");
			if (inic[0] == 'D'&&inic[1] == 'e'&&inic[2] == 'f'&&inic[3] == 'a'&&inic[4] == 'u'&&inic[5] == 'l'&&inic[6] == 't') {
				WritePrivateProfileString(day, temp, NULL, "./Source/schedule.ini");
				break;
			}
			WritePrivateProfileString(day, temp, inic, "./Source/schedule.ini");
		}

		printf("\n...���������� �����Ǿ����ϴ�.\n");
	}

	Sleep(1000);
	system("cls");
	read();
	clear();
	return;
}


void control::allprint(int mon) {
	system("cls");
	switch (mon) {
	case 1:
		for (int i = 1; i <= 31; i++) {
			tempd = 100 + i;
			sprintf_s(daytemp, "%d", tempd);
			day = daytemp;
			read();
		} break;
	case 2:
		for (int i = 1; i <= 31; i++) {
			tempd = 200 + i;
			sprintf_s(daytemp, "%d", tempd);
			day = daytemp;
			read();
		} break;
	case 3:
		for (int i = 1; i <= 31; i++) {
			tempd = 300 + i;
			sprintf_s(daytemp, "%d", tempd);
			day = daytemp;
			read();
		}break;
	case 4:
		for (int i = 1; i <= 31; i++) {
			tempd = 400 + i;
			sprintf_s(daytemp, "%d", tempd);
			day = daytemp;
			read();
		}break;
	case 5:
		for (int i = 1; i <= 31; i++) {
			tempd = 500 + i;
			sprintf_s(daytemp, "%d", tempd);
			day = daytemp;
			read();
		} break;
	case 6:
		for (int i = 1; i <= 31; i++) {
			tempd = 600 + i;
			sprintf_s(daytemp, "%d", tempd);
			day = daytemp;
			read();
		} break;
	case 7:
		for (int i = 1; i <= 31; i++) {
			tempd = 700 + i;
			sprintf_s(daytemp, "%d", tempd);
			day = daytemp;
			read();
		} break;
	case 8:
		for (int i = 1; i <= 31; i++) {
			tempd = 800 + i;
			sprintf_s(daytemp, "%d", tempd);
			day = daytemp;
			read();
		}break;
	case 9:
		for (int i = 1; i <= 31; i++) {
			tempd = 900 + i;
			sprintf_s(daytemp, "%d", tempd);
			day = daytemp;
			read();
		} break;
	case 10:
		for (int i = 1; i <= 31; i++) {
			tempd = 1000 + i;
			sprintf_s(daytemp, "%d", tempd);
			day = daytemp;
			read();
		} break;
	case 11:
		for (int i = 1; i <= 31; i++) {
			tempd = 1100 + i;
			sprintf_s(daytemp, "%d", tempd);
			day = daytemp;
			read();
		}break;
	case 12:
		for (int i = 1; i <= 31; i++) {
			tempd = 1200 + i;
			sprintf_s(daytemp, "%d", tempd);
			day = daytemp;
			read();
		} break;
	}

	clear();
	return;
}