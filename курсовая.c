#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#define N 30
struct NOISEM
{
	int number; //���������� ����� 
	char name[N]; //�������� ������
	char type[N]; //��� ������
	float lenght; //����� ������
	float wight; //������ ������
	float thickness; //������� ������
	float area; // ������� ���������
};
typedef struct NOISEM noisem;

int menu(); // ����� �� ����� ����
int next(); // ����������� ����� � ������� ����
float walls(); // ���� ���������� ���� ��������� � ������� ������� ���������
noisem choice(FILE* f); // ����� �������� ����������������� ������

void main()
{
	setlocale(LC_CTYPE, "RUS");
    noisem material; // ��������� � ���������������� ������
	float s=0; // ������� ���� ���� ���������
	float res; // ���������� �������, ��������� ������ ������������
	int c; // ����� ������ ����
	FILE* file; // ��������� �� ����

	file = fopen("course work.txt", "r");
	if (file == NULL)
	{
		printf("������ �������� �����");
		return 0;
	}
	material.area = 0;
	printf("\n --------------------------------- ");
	printf("\n|                                 |");
	printf("\n|  ����������� �����������������  |");
	printf("\n|             �������             |");
	printf("\n|                                 |");
	printf("\n --------------------------------- ");
	printf("\n��� �������� �������� � ������ � ��������� �� �����\n");
	c = 1;
	while (c == 1) 
	{
		c=menu();
		if (c == 1 || c == 2 || c == 3 | c == 4)
		{
			switch (c)
			{
			case 1:
				printf("\n");
				s = walls();
				printf("������� ���� ���� ����� %.2f \n", s);
				break;
			case 2:
				printf("\n");
				material = choice(file);
				printf("\n������� ������ ����� %.2f\n", material.area);
				break;
			case 3:
				printf("\n");
				if (s != 0 && material.area != 0)
				{
					res = ceil(s / material.area);
					printf("���������� ������� ��� ��������� %s ���� %s ����� %.0f. \n��� ���� �� ������� ����� ����� %.2f\n", material.name, material.type, res, material.thickness);
				}
				else printf("�� �� ����� ���������� ������\n");
				break;
			case 4:
				exit(0);
			}
		}
		else
		{
			printf("������ �������� ������");
			exit(0);
		}
		c = next();	
	}
	fclose(file);
}


int menu()
{
	int c;
	printf("\n                ����");
	printf("\n 1.���� ���������� ���� ���������\n 2.����� �������� ����������������� ������\n 3.������� ���������� ����������������� �������\n 4.����� \n");
	scanf("%d", &c);
	return c;
}

int next()
{
	int �;
	printf("---------------------------------------------------------------------------------------------\n");
	printf("��������� � ������� ����? \n1. �� \n2. ��� \n");
	scanf("%d", &�);
	return �;
}

float walls()
{
	int n; // ���������� ����
	int k; // ���������� �������
	float a1; // ������ �����
	float a2; // ������ �����
	float p1; // ������ ������
	float p2; // ������ ������
	float s1; // ������� ����� �����
	float s = 0; // ������� ���� ����

	printf("������� ���������� ����: ");
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		int p = 0;
		printf("������� ������ %d �����: ", i);
		scanf("%f", &a1);
		printf("������� ������ %d �����: ", i);
		scanf("%f", &a2);
		printf("������� ���������� ������� � ����� %d: ", i);
		scanf("%d", &k);
		if (k != 0)
		{
			for (int j = 1; j <= k; j++)
			{
				printf("������� ������ %d ������: ", j);
				scanf("%f", &p1);
				printf("������� ������ %d ������: ", j);
				scanf("%f", &p2);
				p += (p1 * p2); // ������� ������� ������
			}
		}
		s1 = ((a1 * a2) - p); // ������� ������� ����� �����
		s += s1; // ������������ �������� ���� ����
		printf("\n");
	}
	return s;
}

noisem choice(FILE* f)
{
	noisem m;

	printf("��������� �������� �������: \n");
	for (int i = 0; i < 4; i++)
	{
		fscanf(f, "%d%s%s%f%f%f", &m.number, &m.name, &m.type, &m.lenght, &m.wight, &m.thickness);
		printf("�����: %d ��������: %s ���: %s �����: %.2f ������: %.2f �������: %.2f\n", m.number, m.name, m.type, m.lenght, m.wight, m.thickness);
	}
	printf("\n�� ������:\n 1. ������������ ���� �� ��������� �������\n 2. ������ ���� ������� \n");
	int c;
	scanf("%d", &c);
	if (c == 1 || c == 2)
	{
		switch (c)
		{
		case 1:
			fclose(f);
			f = fopen("course work.txt", "r");
			int num;
			printf("������� ����� ��������� ������: ");
			scanf("%d", &num);
			for (int i = 0; i < 4; i++)
			{
				fscanf(f, "%d%s%s%f%f%f", &m.number, &m.name, &m.type, &m.lenght, &m.wight, &m.thickness);
				if (m.number == num) break;
			}
			break;
		case 2:
			m.number = 0;
			printf("������� �������� ������: ");
			scanf("%s", &m.name);
			printf("������� ��� ������: ");
			scanf("%s", &m.type);
			printf("������� ����� ������: ");
			scanf("%f", &m.lenght);
			printf("������� ������ ������: ");
			scanf("%f", &m.wight);
			printf("������� ������� ������: ");
			scanf("%f", &m.thickness);

		}
	}
	else
	{
		printf("������ �������� ������");
		exit(0);
	}
	printf("������:\n �����: %d ��������: %s ���: %s �����: %.2f ������: %.2f �������: %.2f\n", m.number, m.name, m.type, m.lenght, m.wight, m.thickness);
	m.area = m.lenght * m.wight;
	return m;
}

