#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>

struct base
{
	char author[20];
	char name[30];
	char gerne[15];
}*RecordLibrary;

long count;


int replenishment();
int editing();
int deleting();
int sortAuthor();
int sortName(); 
int sortGerne(); 
int search();  

int main()
{
	setlocale(LC_ALL, "RUS");
	FILE *BASE;
	int c = 0;
	long int len;
	system("CLS");
	BASE = fopen("base.bin", "a+b");
	if (BASE == NULL)
	{
		printf("Не удалось открыть файл");
		system("pause");
		return 1;
	}
	fseek(BASE, 0, SEEK_END);
	len = ftell(BASE);
	count = len / 65;
	RecordLibrary = (struct base*)malloc(sizeof(struct base) * count);

	fseek(BASE, 0, SEEK_SET);

	for (int i = 0; i < count; i++)
	{
		fread(RecordLibrary + i, sizeof(struct base), 1, BASE);
	}
	while (c != 8)
	{
		system("CLS");

		printf("  №|Автор               |Название                      |Жанр\n\n");

		for (int i = 0; i < count; i++)
		{
			printf("%3d|", i + 1);
			printf("%-20s|", (RecordLibrary+i)->author);
			printf("%-30s|", (RecordLibrary+i)->name);
			printf("%s \n", (RecordLibrary+i)->gerne);
		}
		printf("\nВыберите дальнейшее действие: \n");
		printf("1) Пополнить базу новой композицией \n");
		printf("2) Отредактировать базу \n");
		printf("3) Удалить композицию из базы \n");
		printf("4) Сортировать базу по автору \n");
		printf("5) Сортировать базу по названию композиции  \n");
		printf("6) Сортировать базу по жанру \n");
		printf("7) Поиск композиции\n");
		printf("8) Отмена \n");
		scanf("%d", &c);
		switch (c)
		{
		case 1:
		{
			replenishment();
			break;
		}
		case 2:
		{
			editing();
			break;
		}
		case 3:
		{
			deleting();
			break;
		}
		case 4:
		{
			sortAuthor();
			break;
		}
		case 5:
		{
			sortName();
			break;
		}
		case 6:
		{
			sortGerne();
			break;
		}
		case 7:
		{
			search();
			break;
		}
		}
		system("CLS");
	}
	fclose(BASE);
	BASE = fopen("base.bin", "wb");
	if (BASE == NULL)
		return 1;
	for (int i = 0; i < count; i++)
	{
		fwrite((RecordLibrary + i)->author, 1, sizeof((RecordLibrary + i)->author), BASE);
		fwrite((RecordLibrary + i)->name, 1, sizeof((RecordLibrary + i)->name), BASE);
		fwrite((RecordLibrary + i)->gerne, 1, sizeof((RecordLibrary + i)->gerne), BASE);
	}

	fclose(BASE);
}
//*****************************************
int replenishment()
{
	system("CLS");
	count++;
	RecordLibrary = (struct base*)realloc(RecordLibrary, sizeof(struct base) * (count));
	printf("Введите автора композиции:   ");
	getchar();
	gets((RecordLibrary + (count - 1))->author);
	printf("Введите название композиции:   ");
	gets((RecordLibrary + (count - 1))->name);
	printf("Введите жанр композиции:   ");
	gets((RecordLibrary + (count - 1))->gerne);
	return 0;
}
//*****************************************
int editing()
{
	int j = 0;
	int k, num;

	system("CLS");
	for (int i = 0; i < count; i++)
	{
		printf("%3d|", i + 1);
		printf("%-20s|", (RecordLibrary + i)->author);
		printf("%-30s|", (RecordLibrary + i)->name);
		printf("%s \n", (RecordLibrary + i)->gerne);
	}

	printf("\n0 - Отмена \n");
	printf("Введите номер строки, которую хотите изменить - ");
	scanf("%d", &k);
	if (k == 0)
	{
		return 0;
	}

	num = k - 1;

	printf("Автор - %s\nНазвание - %s\nЖанр - %s\n", (RecordLibrary + num)->author, (RecordLibrary + num)->name, (RecordLibrary + num)->gerne);
	printf("Какой элемент вы хотите изменить :\n");
	printf("1) Автора\n");
	printf("2) Название\n");
	printf("3) Жанр\n");
	scanf("%d", &k);

	system("CLS");

	switch (k)
	{
	case 1:
	{
		getchar();
		printf("Нынешнее имя автора - %s\n", (RecordLibrary + num)->author);
		printf("Введите новое имя автора - ");
		memset((RecordLibrary + num)->author, 0, sizeof((RecordLibrary + num)->author));
		gets((RecordLibrary + num)->author);
		break;
	}
	case 2:
	{
		getchar();
		printf("Нынешнее название %s\n", (RecordLibrary + num)->name);
		printf("Введите новое название - ");
		memset((RecordLibrary + num)->name, 0, sizeof((RecordLibrary + num)->name));
		gets((RecordLibrary + num)->name);
		break;
	}
	case 3:
	{
		getchar();
		printf("Нынешний жанр  %s\n", (RecordLibrary + num)->gerne);
		printf("Введите новый жанр - ");
		memset((RecordLibrary + num)->gerne, 0, sizeof((RecordLibrary + num)->gerne));
		gets((RecordLibrary + num)->gerne);
		break;
	}
	}

	printf("Хотите продолжить редактирование? \n 1) Да \n 2) Нет \n");
	scanf("%d", &num);
	if (num == 1)
	{
		system("CLS");
		editing();
	}

	return 0;
}
//*****************************************
int deleting()
{
	int j = 0;
	int k;

	system("CLS");


	for (int i = 0; i < count; i++)
	{
		printf("%3d|", i + 1);
		printf("%-20s|", (RecordLibrary + i)->author);
		printf("%-30s|", (RecordLibrary + i)->name);
		printf("%s \n", (RecordLibrary + i)->gerne);
	}


	printf("Введите номер строки, которую хотите удалить - ");
	scanf("%d", &k);
	while (k - 1 < count)
	{
		*(RecordLibrary + (k-1)) = *(RecordLibrary + k);
		k++;
	}

	count--;
	RecordLibrary = (struct base*)realloc(RecordLibrary, sizeof(struct base) * count);

	return 0;
}
//*****************************************
int sortAuthor()
{

	char line1[20], line2[20];
	struct base *str = (struct base*)malloc(sizeof(struct base) + 1); // для свапа структур 

	for (int i = 0; i < count; i++) //для нормальной сортировки без учёта регистра 
	{
		for (int k = 0; k < count - 1; k++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (((RecordLibrary + k)->author[j] >= 'A') && ((RecordLibrary + k)->author[j] <= 'Z'))
				{
					line1[j] = (RecordLibrary + k)->author[j];
					line1[j] += 'a' - 'A';
				}
				else
				{
					line1[j] = (RecordLibrary + k)->author[j];
				}

				if (((RecordLibrary + (k+1))->author[j] >= 'A') && ((RecordLibrary + (k+1))->author[j] <= 'Z'))
				{
					line2[j] = (RecordLibrary + (k+1))->author[j];
					line2[j] += 'a' - 'A';
				}
				else
				{
					line2[j] = (RecordLibrary + (k + 1))->author[j];
				}
			}
			if (strcmp(line1, line2) > 0)
			{
				*str = *(RecordLibrary + k);
				*(RecordLibrary + k) = *(RecordLibrary + (k+1));
				*(RecordLibrary + (k+1)) = *str;
			}
		}
	}
	free(str);
	return 0;
}
//*****************************************
int sortName()
{

	char line1[30], line2[30];
	struct base *str = (struct base*)malloc(sizeof(struct base) + 1); 

	
	for (int i = 0; i < count; i++) 
	{
		for (int k = 0; k < count - 1; k++)
		{
			for (int j = 0; j < 30; j++)
			{
				if (((RecordLibrary + k)->name[j] >= 'A') && ((RecordLibrary + k)->name[j] <= 'Z'))
				{
					line1[j] = (RecordLibrary + k)->name[j];
					line1[j] += 'a' - 'A';
				}
				else
				{
					line1[j] = (RecordLibrary + k)->name[j];
				}

				if (((RecordLibrary + (k + 1))->name[j] >= 'A') && ((RecordLibrary + (k + 1))->name[j] <= 'Z'))
				{
					line2[j] = (RecordLibrary + (k + 1))->name[j];
					line2[j] += 'a' - 'A';
				}
				else
				{
					line2[j] = (RecordLibrary + (k + 1))->name[j];
				}
			}
			if (strcmp(line1, line2) > 0)
			{
				*str = *(RecordLibrary + k);
				*(RecordLibrary + k) = *(RecordLibrary + (k + 1));
				*(RecordLibrary + (k + 1)) = *str;
			}
		}
	}
	free(str);
	return 0;
}
//*****************************************
int sortGerne()
{
	char line1[15], line2[15];
	struct base *str = (struct base*)malloc(sizeof(struct base) + 1);

	for (int i = 0; i < count; i++)
	{
		for (int k = 0; k < count - 1; k++)
		{
			for (int j = 0; j < 15; j++)
			{
				if (((RecordLibrary + k)->gerne[j] >= 'A') && ((RecordLibrary + k)->gerne[j] <= 'Z'))
				{
					line1[j] = (RecordLibrary + k)->gerne[j];
					line1[j] += 'a' - 'A';
				}
				else
				{
					line1[j] = (RecordLibrary + k)->gerne[j];
				}

				if (((RecordLibrary + (k + 1))->gerne[j] >= 'A') && ((RecordLibrary + (k + 1))->gerne[j] <= 'Z'))
				{
					line2[j] = (RecordLibrary + (k + 1))->gerne[j];
					line2[j] += 'a' - 'A';
				}
				else
				{
					line2[j] = (RecordLibrary + (k + 1))->gerne[j];
				}
			}
			if (strcmp(line1, line2) > 0)
			{
				*str = *(RecordLibrary + k);
				*(RecordLibrary + k) = *(RecordLibrary + (k + 1));
				*(RecordLibrary + (k + 1)) = *str;
			}
		}
	}
	free(str);
	return 0;
}
//*****************************************
int search()
{
	int i, k = 0, j = 0, cnt = 0;
	int flag = 0;
	char *input1 = (char*)malloc(sizeof(char) * 1);
	char *input2 = (char*)malloc(sizeof(char) * 1);
	char *input3 = (char*)malloc(sizeof(char) * 1);
	struct base *mass = (struct base*)malloc(sizeof(struct base) * count);
	char array[63];
	////////////////////////////////////////////////////////////////////////////////

	printf("Введите ключевые слова: ");
	getchar();
	gets(array);
	while (array[cnt] != '\0')
	{
		if (array[cnt] >= 'A' && array[cnt] <= 'Z')
		{
			array[cnt] += 'a' - 'A';
		}
		cnt++;
	}
	cnt = 0;
	while (array[cnt] >= 'a' && array[cnt] <= 'z')
	{
		input1 = (char*)realloc(input1, sizeof(char) * (j + 1));
		*(input1 + j) = array[cnt];
		cnt++;
		j++;
	}
	input1 = (char*)realloc(input1, sizeof(char) * (j + 1));
	*(input1 + j) = '\0';
	j = 0;
	if (array[cnt] == '\n')
		goto next;
	cnt++;

	while (array[cnt] >= 'a' && array[cnt] <= 'z')
	{
		input2 = (char*)realloc(input2, sizeof(char) * (j + 1));
		*(input2 + j) = array[cnt];
		cnt++;
		j++;
	}
	j = 0;

	if (array[cnt] == '\n')
		goto next;
	cnt++;

	while (array[cnt] >= 'a' && array[cnt] <= 'z')
	{
		input3 = (char*)realloc(input3, sizeof(char) * (j + 1));
		*(input3 + j) = array[cnt];
		cnt++;
		j++;
	}
next:;
	/////////////////////////////////////////////////////////////////////////////////////
	printf("\n");
	for (i = 0; i < count; i++)
	{
		j = 0;
		while ((RecordLibrary + i)->author[j] != '\0')
		{
			if ((RecordLibrary + i)->author[j] >= 'A' && (RecordLibrary + i)->author[j] <= 'Z')
				(mass + i)->author[j] = (RecordLibrary + i)->author[j] + 'a' - 'A';
			else
				(mass + i)->author[j] = (RecordLibrary + i)->author[j];
			k++;
			j++;
		}
		(mass + i)->author[j] = '\0';
		j = 0;

		while ((RecordLibrary + i)->name[j] != '\0')
		{
			if ((RecordLibrary + i)->name[j] >= 'A' && (RecordLibrary + i)->name[j] <= 'Z')
				(mass + i)->name[j] = (RecordLibrary + i)->name[j] + 'a' - 'A';
			else
				(mass + i)->name[j] = (RecordLibrary + i)->name[j];
			k++;
			j++;
		}
		(mass + i)->name[j] = '\0';
		j = 0;

		while ((RecordLibrary + i)->gerne[j] != '\0')
		{

			if ((RecordLibrary + i)->gerne[j] >= 'A' && (RecordLibrary + i)->gerne[j] <= 'Z')
				(mass + i)->gerne[j] = (RecordLibrary + i)->gerne[j] + 'a' - 'A';
			else
				(mass + i)->gerne[j] = (RecordLibrary + i)->gerne[j];
			k++;
			j++;
		}
		(mass + i)->gerne[j] = '\0';
		j = 0;

		flag = 0;
		if (strstr((mass + i)->author, input1) != NULL ||strstr((mass + i)->author, input2) != NULL || strstr((mass + i)->author, input3) != NULL)
			flag++;
		if (strstr((mass + i)->name, input1) != NULL || strstr((mass + i)->name, input2) != NULL || strstr((mass + i)->name, input3) != NULL)
			flag++;
		if (strstr((mass + i)->gerne, input1) != NULL || strstr((mass + i)->gerne, input2) != NULL || strstr((mass + i)->gerne, input3) != NULL)
			flag++;
		if (flag > 0)
		{
			printf("%3d|", i + 1);
			printf("%-20s|", (RecordLibrary + i)->author);
			printf("%-30s|", (RecordLibrary + i)->name);
			printf("%s \n", (RecordLibrary + i)->gerne);
		}
	}
	free(mass);
	free(input1);
	free(input2);
	free(input3);
	system("pause");
	return 0;
}
