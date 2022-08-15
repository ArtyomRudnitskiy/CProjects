#include "Functions.h"

int main() {

	TREENODEPTR rootPtr = NULL;
	TREENODEPTR copy = NULL;
	TREENODEPTR copyPrint = NULL;
	setlocale(LC_ALL, "Rus");
	int choice, answer, n, i, item;


	printf("����� ���������� � ��������� �� ������ � ���������!\n");
	do {
		printf("\n���������� ��� ������� ���� ������, �� ��� ������ �������� �������� ������:\n"
			"1. ���� � ����������\n"
			"2. ��������� ����\n");

		do {
			printf("? ");
			scanf_s("%d", &choice);
		} while (choice != 1 && choice != 2);

		printf("\n �������! ������� ��������� �������?\n");
		printf("? ");

		do {
			printf("�������: ");
			scanf_s("%d", &n);
			if (n < 1)
			{
				printf("������ �����. ���������!\n");
			}
		} while (n < 1);

		switch (choice)
		{
		case 1:
			printf("\n�����, ������� ����� �������� � ������:\n");
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
				printf("������� ����� �������: ");
				scanf_s("%d", &a);
				printf("������� ������ �������: ");
				scanf_s("%d", &b);
				printf("\n");

				if (a > b)
				{
					printf("������ �����. ���������!\n");
				}
			} while (a > b);

			printf("\n�����, ������� ����� �������� � ������:\n");
			for (i = 0; i < n; i++)
			{
				item = a + rand() % (b - a + 1);
				printf("%d\n", item);
				insertNode(&rootPtr, item);
			}
			break;
		default:
			printf("\n������ �����!\n");
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
					printf("\n\n������ �����:\n");
					inOrder(rootPtr);
					printf("\n\n�������� �����:\n");
					preOrder(rootPtr);
					printf("\n\n�������� �����:\n");
					postOrder(rootPtr);
				}
				else printf("\n�������� ������!");
				break;
			case 2:
				if (rootPtr != NULL) {

					for (int level = 1; level <= height(rootPtr, 0); level++)
					{
						printf("%d ����: ", level);
						level_elems(rootPtr, level, 0);
						printf("\n");
					}
				}
				else printf("\n������ ������!");


				break;
			case 3:
				if (rootPtr != NULL) {
					copyBinaryTree(&copy, &rootPtr);
					printf("������ �����������!\n");
				}
				else printf("\n���������� ������!");
				break;
			case 4:
				if (rootPtr != NULL) printf("������ ������ ����� : %d\n\n", height(rootPtr, 0));
				else printf("\n������ ������!");
				break;
			case 5:
				if (rootPtr != NULL) {
					doubleDelete(&rootPtr);
				}
				else printf("\n������ ������!");
				break;
			case 6:
				//if (rootPtr != NULL)
			{
				freeTree(&rootPtr);
				printf("\n������ �������!");
			}
			//else
			printf("\n������ �����e!");
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
				else printf("\n�������� ������!");

				break;
			case 8:
				printf("������� ������� ��� ��������: ");
				scanf_s("%d", &item);
				delete(&rootPtr, item);
				break;
			case 9:
				printf("������� ������� ��� �������: ");
				scanf_s("%d", &item);
				insertNode(&rootPtr, item);
				break;
			case 10:
				break;
			default:
				printf("\n������ �����!");
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

	printf("\n���������� ������...\n");
	return 0;

}
