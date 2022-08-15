#include "Functions.h"

int main() {

	TREENODEPTR rootPtr = NULL;
	TREENODEPTR copy = NULL;
	TREENODEPTR copyPrint = NULL;
	setlocale(LC_ALL, "Rus");
	int choice, answer, n, i, item;


	printf("Добро пожаловать в программу по работе с деревьями!\n");
	do {
		printf("\nПредлагаем Вам создать свое дерево, но для начала выберете желаемый способ:\n"
			"1. Ввод с клавиатуры\n"
			"2. Случайный ввод\n");

		do {
			printf("? ");
			scanf_s("%d", &choice);
		} while (choice != 1 && choice != 2);

		printf("\n Принято! Сколько элементов желаете?\n");
		printf("? ");

		do {
			printf("Введите: ");
			scanf_s("%d", &n);
			if (n < 1)
			{
				printf("Ошибка ввода. Повторите!\n");
			}
		} while (n < 1);

		switch (choice)
		{
		case 1:
			printf("\nЧисла, которые будут помещены в дерево:\n");
			for (i = 0; i < n; i++)
			{
				scanf_s("%d", &item);
				insertNode(&rootPtr, item);
			}
			break;
		case 2:
			srand((unsigned int)time(NULL));
			int a, b;

			do {
				printf("Введите левую границу: ");
				scanf_s("%d", &a);
				printf("Введите правую границу: ");
				scanf_s("%d", &b);
				printf("\n");

				if (a > b)
				{
					printf("Ошибка ввода. Повторите!\n");
				}
			} while (a > b);

			printf("\nЧисла, которые будут помещены в дерево:\n");
			for (i = 0; i < n; i++)
			{
				item = a + rand() % (b - a + 1);
				printf("%d\n", item);
				insertNode(&rootPtr, item);
			}
			break;
		default:
			printf("\nОшибка ввода!\n");
			break;
		}

		instructions();
		printf("? ");
		scanf_s("%d", &answer);
		while (answer != 11) {
			switch (answer)
			{
			case 0:
				instructions();
				break;
			case 1:
				if (rootPtr != NULL) {
					printf("\n\nПрямой обход:\n");
					inOrder(rootPtr);
					printf("\n\nОбратный обход:\n");
					preOrder(rootPtr);
					printf("\n\nКонцевой обход:\n");
					postOrder(rootPtr);
				}
				else printf("\nПечатать нечего!");
				break;
			case 2:
				if (rootPtr != NULL) {

					for (int level = 1; level <= height(rootPtr, 0); level++)
					{
						printf("%d этаж: ", level);
						level_elems(rootPtr, level, 0);
						printf("\n");
					}
				}
				else printf("\nДерево пустое!");


				break;
			case 3:
				if (rootPtr != NULL) {
					copyBinaryTree(&copy, &rootPtr);
					printf("Дерево скопировано!\n");
				}
				else printf("\nКопировать нечего!");
				break;
			case 4:
				if (rootPtr != NULL) printf("Высота дерева равна : %d\n\n", height(rootPtr, 0));
				else printf("\nДерево пустое!");
				break;
			case 5:
				if (rootPtr != NULL) {
					doubleDelete(&rootPtr);
				}
				else printf("\nДерево пустое!");
				break;
			case 6:
				//if (rootPtr != NULL)
			{
				freeTree(&rootPtr);
				printf("\nДерево удалено!");
			}
			//else
			printf("\nДерево пустоe!");
			break;
			case 7:

				if (rootPtr != NULL) {
					copyBinaryTree(&copyPrint, &rootPtr);
					zapolnenieNAprint(&copyPrint, height(rootPtr, 0), 1);
					for (int j = 1; j <= height(rootPtr, 0); j++) {
						i = pow(2, j - 1);
						poiskelementa(copyPrint, j, 1, height(rootPtr, 0), i);
						printf("\n");
					}
					freeTree(&copyPrint);
					copyPrint = NULL;
				}
				else printf("\nПечатать нечего!");

				break;
			case 8:
				printf("Введите элемент для удаления: ");
				scanf_s("%d", &item);
				delete(&rootPtr, item);
				break;
			case 9:
				printf("Введите элемент для вставки: ");
				scanf_s("%d", &item);
				insertNode(&rootPtr, item);
				break;
			case 10:
				break;
			default:
				printf("\nОшибка ввода!");
				instructions();

				break;
			}
			if (answer != 10)
			{
				printf("\n\n? ");
				scanf_s("%d", &answer);
			}
		}

		freeTree(&rootPtr);
		freeTree(&copyPrint);
		freeTree(&copy);

	} while (answer == 10);

	printf("\nЗавершение работы...\n");
	return 0;

}
