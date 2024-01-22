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

int error(FILE* f); // определение ошибки при открытии файла
float walls(); // ввод параметров стен 
int write(noisem* p, int size); // считывание информации о панелях из файла в структуру
int read(noisem* p, int size);// внесение информации о новой панели
int del(noisem* p, int size, int n); // удаление информации о панели 
float calc(float s, noisem* p, int n); // подсчет количества панелей
void res_to_file(noisem* p, float s, float r, int n); // занесение информации о расчетах в новый файл

int main()
{
	setlocale(LC_CTYPE, "RUS");
	noisem panel[N]; // массив структур с панелями
	float s = 0; // площадь всех стен помещения
	float res = 0; // количество панелей, результат работы калькулятора
	int c = 1; // выбор пункта меню
	int num = 0;// номер выбранной панели
	int size = 4; // размер массива структур с панелями
	noisem* ptr_panel = panel; // указатель на массив структур с панелями

	printf("\n --------------------------------- ");
	printf("\n|                                 |");
	printf("\n|  Калькулятор звукоизоляционных  |");
	printf("\n|             панелей             |");
	printf("\n|                                 |");
	printf("\n --------------------------------- ");
	printf("\nВсе значения задаются в метрах с точностью до сотых\n");
	while (c == 1)
	{
		printf("\n                   МЕНЮ");
		printf("\n 1. Ввод параметров стен помещения\n 2. Просмотр каталога звукоизоляционных панелей\n 3. Внесение своего варианта панели в каталог\n 4. Удаление панели из каталога\n 5. Подсчет количества звукоизоляционных панелей\n 6. Внесение результатов в файл\n 7. Выход \n\nВаш выбор: ");
		scanf("%d", &c);
		if (c == 1 || c == 2 || c == 3 || c == 4 || c == 5 || c == 6 || c == 7)
		{
			switch (c)
			{
			case 1:
				printf("\n");
				s = walls();
				break;
			case 2:
				printf("\n");
				num = read(ptr_panel, size);
				break;
			case 3:
				size = write(ptr_panel, size);
				break;
			case 4:
				num = del(ptr_panel, size, num);
				size--;
				break;
			case 5:
				res = calc(s, ptr_panel, num);
				break;
			case 6:
				res_to_file(ptr_panel, s, res, num);
				break;
			case 7:
				exit(0);
			}
		}
		else
		{
			printf("Введен неверный символ");
			exit(0);
		}
		printf("---------------------------------------------------------------------------------------------\n");
		printf("Вернуться в главное меню? \n 1. Да \n 2. Нет \nВаш выбор: ");
		scanf("%d", &c);
	}
	return 0;
}

int error(FILE* f) // определение ошибки при открытии файла
{
	if (f == NULL)
	{
		printf("Ошибка открытия файла");
		return 0;
	}
}

float walls() // ввод параметров стен и подсчет их площади
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
	printf("Площадь всех стен равна %.2f \n", s);
	return s;
}

int read(noisem* p, int size) // считывание информации о панелях из файла в структуру
{
	int num;
	FILE* file;
	file = fopen("course work.txt", "r");
	error(file);
	// считывание панелей из файла и вывод их на экран
	for (int i = 0; i < size; i++)
	{
		fscanf(file, "%d%s%s%f%f%f", &p[i].number, &p[i].name, &p[i].type, &p[i].lenght, &p[i].wight, &p[i].thickness);
		printf(" Номер: %d Название: %s Тип: %s Длина: %.2f Ширина: %.2f Толщина: %.2f\n", p[i].number, p[i].name, p[i].type, p[i].lenght, p[i].wight, p[i].thickness);
	}
	printf("\nВы хотите использовать один из этих вариантов:\n 1. Да\n 2. Нет \nВаш выбор: ");
	int c;
	scanf("%d", &c);
	int f = 0;
	if (c == 1 || c == 2)
	{
		switch (c)
		{
		case 1:
			printf("Введите номер выбранной панели: ");
			scanf("%d", &num);
			for (int i = 0; i < size; i++)
			{
				if (i == (num - 1))
				{
					printf("Выбранная панель:\n Номер: %d Название: %s Тип: %s Длина: %.2f Ширина: %.2f Толщина: %.2f\n", p[num - 1].number, p[num - 1].name, p[num - 1].type, p[num - 1].lenght, p[num - 1].wight, p[num - 1].thickness);
					f = 1;
				}
			}
			if (f == 0)printf("Такой панели нет\n");
			break;
		case 2:
			num = 0;
			break;
		}
	}
	else
	{
		printf("\nВведен неверный символ");
		exit(0);
	}
	fclose(file);
	return num;
}

int write(noisem* p, int size) // занесение информации о новой панели
{
	FILE* file; 
	file = fopen("course work.txt", "a");
	error(file);
	// считывания панелей из файла на случай, если это не было сделано раньше
	for (int i = 0; i < size; i++)
	{
		fscanf(file, "%d%s%s%f%f%f", &p[i].number, &p[i].name, &p[i].type, &p[i].lenght, &p[i].wight, &p[i].thickness);
	}
	noisem n;
	// ввод параметров панели с клавиатуры
	n.number = size + 1;
	printf("\nВведите название панели: ");
	scanf("%s", &n.name);
	printf("Введите тип панели: ");
	scanf("%s", &n.type);
	printf("Введите длину панели: ");
	scanf("%f", &n.lenght);
	printf("Введите ширину панели: ");
	scanf("%f", &n.wight);
	printf("Введите толщину панели: ");
	scanf("%f", &n.thickness);
	// запись панели в файл
	fprintf(file, "%d %s %s %.2f %.2f %.2f", n.number, n.name, n.type, n.lenght, n.wight, n.thickness);
	p[size] = n;
	size += 1;
	fclose(file);
	printf("\nПанель внесена в каталог\n");
	return size;
}

int del(noisem* p, int size, int n) // удаление информации о панели 
{
	FILE* file;
	file = fopen("course work.txt", "r");
	error(file);
	int d;
	printf("Каталог панелей:\n");
	// вывод панелей на экран
	for (int i = 0; i < size; i++)
	{
		fscanf(file, "%d%s%s%f%f%f", &p[i].number, &p[i].name, &p[i].type, &p[i].lenght, &p[i].wight, &p[i].thickness);
		printf(" Номер: %d Название: %s Тип: %s Длина: %.2f Ширина: %.2f Толщина: %.2f\n", p[i].number, p[i].name, p[i].type, p[i].lenght, p[i].wight, p[i].thickness);
	}
	fclose(file);
	file = fopen("course work.txt", "w");
	error(file);
	printf("\nВведите номер панели, которую хотите удалить ");
	scanf("%d", &d);
	// проверка на то, была ли эта панель выбрана ранее
	if (d == n)
	{
		printf("Вы удалили панель, выбранную ранее");
		n = 0;
	}
	// проверка на то, есть ли панель под введенным номером
	int f = 0;
	for (int i = 1; i <= size; i++)
	{
		if (i == d)f = 1;
	}
	if (f == 0)printf("Такой панели нет\n");
	else
	{
		// перезапись структуры, без учета панели, которую надо удалить
		for (int i = 0; i < size - 1; i++)
		{
			if (p[i].number >= d)
			{
				p[i] = p[i + 1];
				p[i].number -= 1;
			}
		}
		size -= 1;
		printf("\n\nПанель удалена. Каталог панелей:\n");
		// запись обновленного каталога в файл
		for (int i = 0; i < size; i++)
		{
			printf(" %d %s %s %.2f %.2f %.2f\n", p[i].number, p[i].name, p[i].type, p[i].lenght, p[i].wight, p[i].thickness);
			fprintf(file, "%d %s %s %.2f %.2f %.2f\n", p[i].number, p[i].name, p[i].type, p[i].lenght, p[i].wight, p[i].thickness);
		}
	}
	fclose(file);

	return n;
}

float calc(float s, noisem* p, int n) // подсчет количества панелей
{
	float r;
	p[n - 1].area = p[n - 1].lenght * p[n - 1].wight; // подсчет площади одной панели
	if (s != 0 && n != 0)
	{
		r = ceil(s / p[n - 1].area); // подсчет количества панелей
		printf("Количество панелей номер %d под названием %s типа %s равно %.0f. \nПри этом их толщина будет равна %.2f\n", p[n - 1].number, p[n - 1].name, p[n - 1].type, r, p[n - 1].thickness);
		
	}
	else
	{
		printf("Вы ввели недостаточно данных\n");
		r = 0;
	}
	
	return r;
}

void res_to_file(noisem* p, float s, float r, int n) // занесение информации о расчетах в новый файл
{
	if (r != 0)
	{
		// запись в файл
		FILE* file; 
		file = fopen("results of calculation.txt", "w");
		error(file);
		fprintf(file, "Все значения задаются в метрах с точностью до сотых\n\nПанель:\n Номер: %d\n Название: %s\n Тип: %s\n Длина: %.2f\n Ширина: %.2f\n Толщина: %.2f\n Площадь: %.2f \n", p[n - 1].number, p[n - 1].name, p[n - 1].type, p[n - 1].lenght, p[n - 1].wight, p[n - 1].thickness, p[n - 1].area);
		fprintf(file, "\nПлощадь помещения: %.2f", s);
		fprintf(file, "\n\nНеобходимое количество панелей: %.0f", r);
		printf("Информация успешно занесена в файл под названием results of calculation.txt\n");
	}
	else printf("Вы не ввели всю необходимую информацию \n");
}
