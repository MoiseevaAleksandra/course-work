#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#define N 30
struct NOISEM
{
	int number; //порядковый номер 
	char name[N]; //название панели
	char type[N]; //тип панели
	float lenght; //длина панели
	float wight; //ширина панели
	float thickness; //толщина панели
	float area; // площадь структуры
};
typedef struct NOISEM noisem;

int menu(); // вывод на экран меню
int next(); // предложение выйти в главное меню
float walls(); // ввод параметров стен помещения и подсчет площади помещения
noisem choice(FILE* f); // выбор варианта звукоизоляционной панели

void main()
{
	setlocale(LC_CTYPE, "RUS");
    noisem material; // структура с характеристиками панели
	float s=0; // площадь всех стен помещения
	float res; // количество панелей, результат работы калькулятора
	int c; // выбор пункта меню
	FILE* file; // указатель на файл

	file = fopen("course work.txt", "r");
	if (file == NULL)
	{
		printf("Ошибка открытия файла");
		return 0;
	}
	material.area = 0;
	printf("\n --------------------------------- ");
	printf("\n|                                 |");
	printf("\n|  калькулятор звукоизоляционных  |");
	printf("\n|             панелей             |");
	printf("\n|                                 |");
	printf("\n --------------------------------- ");
	printf("\nВсе значения задаются в метрах с точностью до сотых\n");
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
				printf("Площадь всех стен равна %.2f \n", s);
				break;
			case 2:
				printf("\n");
				material = choice(file);
				printf("\nПлощадь панели равна %.2f\n", material.area);
				break;
			case 3:
				printf("\n");
				if (s != 0 && material.area != 0)
				{
					res = ceil(s / material.area);
					printf("Количество панелей под названием %s типа %s равно %.0f. \nПри этом их толщина будет равна %.2f\n", material.name, material.type, res, material.thickness);
				}
				else printf("Вы не ввели достаточно данных\n");
				break;
			case 4:
				exit(0);
			}
		}
		else
		{
			printf("Введен неверный символ");
			exit(0);
		}
		c = next();	
	}
	fclose(file);
}


int menu()
{
	int c;
	printf("\n                МЕНЮ");
	printf("\n 1.Ввод параметров стен помещения\n 2.Выбор варианта звукоизоляционной панели\n 3.Подсчет количества звукоизоляционных панелей\n 4.Выход \n");
	scanf("%d", &c);
	return c;
}

int next()
{
	int с;
	printf("---------------------------------------------------------------------------------------------\n");
	printf("Вернуться в главное меню? \n1. Да \n2. Нет \n");
	scanf("%d", &с);
	return с;
}

float walls()
{
	int n; // количество стен
	int k; // количество проемов
	float a1; // высота стены
	float a2; // ширина стены
	float p1; // высота проема
	float p2; // ширина проема
	float s1; // площадь одной стены
	float s = 0; // площадь всех стен

	printf("Введите количество стен: ");
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		int p = 0;
		printf("Введите высоту %d стены: ", i);
		scanf("%f", &a1);
		printf("Введите ширину %d стены: ", i);
		scanf("%f", &a2);
		printf("Введите количество проемов в стене %d: ", i);
		scanf("%d", &k);
		if (k != 0)
		{
			for (int j = 1; j <= k; j++)
			{
				printf("Введите высоту %d проема: ", j);
				scanf("%f", &p1);
				printf("Введите ширину %d проема: ", j);
				scanf("%f", &p2);
				p += (p1 * p2); // подсчет площади проема
			}
		}
		s1 = ((a1 * a2) - p); // подсчет площади одной стены
		s += s1; // суммирование площадей всех стен
		printf("\n");
	}
	return s;
}

noisem choice(FILE* f)
{
	noisem m;

	printf("Возможные варианты панелей: \n");
	for (int i = 0; i < 4; i++)
	{
		fscanf(f, "%d%s%s%f%f%f", &m.number, &m.name, &m.type, &m.lenght, &m.wight, &m.thickness);
		printf("Номер: %d Название: %s Тип: %s Длина: %.2f Ширина: %.2f Толщина: %.2f\n", m.number, m.name, m.type, m.lenght, m.wight, m.thickness);
	}
	printf("\nВы хотите:\n 1. Использовать один из вариантов панелей\n 2. Внести свой вариант \n");
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
			printf("Введите номер выбранной панели: ");
			scanf("%d", &num);
			for (int i = 0; i < 4; i++)
			{
				fscanf(f, "%d%s%s%f%f%f", &m.number, &m.name, &m.type, &m.lenght, &m.wight, &m.thickness);
				if (m.number == num) break;
			}
			break;
		case 2:
			m.number = 0;
			printf("Введите название панели: ");
			scanf("%s", &m.name);
			printf("Введите тип панели: ");
			scanf("%s", &m.type);
			printf("Введите длину панели: ");
			scanf("%f", &m.lenght);
			printf("Введите ширину панели: ");
			scanf("%f", &m.wight);
			printf("Введите толщину панели: ");
			scanf("%f", &m.thickness);

		}
	}
	else
	{
		printf("Введен неверный символ");
		exit(0);
	}
	printf("Панель:\n Номер: %d Название: %s Тип: %s Длина: %.2f Ширина: %.2f Толщина: %.2f\n", m.number, m.name, m.type, m.lenght, m.wight, m.thickness);
	m.area = m.lenght * m.wight;
	return m;
}

