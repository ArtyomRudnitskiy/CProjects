#include "Functions.h"

void print(char data, int level, int j, int maxLevel)
{
	static int count = 0;
	static int n = 0;								/*n - правая граница, которая с каждым уровнем растет, и отсчитывается от старого n*/
	static int tempN = 0;
	count++;
	if (count == j)
	{
		n = tempN;
		n = n + pow(2, level);			/*Начинаем печатать справа налево, для этого делаем max отступ*/
		tempN = n;
	}
	level--;						/*Необходимое действия, для соблюдения симметрии; Нужно для формулы n - правой границы*/
	for (int k = 1; k < n; k++)		/*Печатаем нужное число пробелов*/
		printf(" ");
	if (data == 100)
		printf("[]\r");		/*Печатаем нужную цифру, и делаем возврат каретки в начало строки*/
	else
		printf("%2d\r", data);
	n = n - pow(2, level + 2);	/*Следуя симметрии задаем кол-во пробелов, которое соответсвует левому от текущего числа*/
	if (count == pow(2, maxLevel) - 1)
	{
		count = 0;
		tempN = 0;
	}

}

void copyBinaryTree(TREENODEPTR* root, TREENODEPTR* treePtr) {

	*root = malloc(sizeof(TREENODE));			/*Остановка рекурсии*/
	if (*root != NULL) {
		(*root)->leftPtr = NULL; /*Ставим число в нужное место, и две ветви отводим от этой ячейки и зануляем их*/
		(*root)->rightPtr = NULL;
	}
	else
		printf("No memore available.\n"); /*Защита от утечки памяти*/


	(*root)->data = (*treePtr)->data;
	if ((*treePtr)->leftPtr != NULL)
		copyBinaryTree(&((*root)->leftPtr), &((*treePtr)->leftPtr));
	if ((*treePtr)->rightPtr != NULL)
		copyBinaryTree(&((*root)->rightPtr), &((*treePtr)->rightPtr));


}

void zapolnenieNAprint(TREENODEPTR* treePtr, int maxLevel, int currentLevel)
{
	if ((*treePtr)->leftPtr != NULL)									/*На случай повторения элементов*/
		zapolnenieNAprint(&((*treePtr)->leftPtr), maxLevel, currentLevel + 1);
	else if ((*treePtr)->leftPtr == NULL && currentLevel <= maxLevel)
	{
		(*treePtr)->leftPtr = malloc(sizeof(TREENODE));
		(*treePtr)->leftPtr->data = 100;
		(*treePtr)->leftPtr->leftPtr = NULL;
		(*treePtr)->leftPtr->rightPtr = NULL;
		zapolnenieNAprint(&((*treePtr)->leftPtr), maxLevel, currentLevel + 1);
	}

	if ((*treePtr)->rightPtr != NULL)									/*На случай повторения элементов*/
		zapolnenieNAprint(&((*treePtr)->rightPtr), maxLevel, currentLevel + 1);
	else if ((*treePtr)->rightPtr == NULL && currentLevel <= maxLevel)
	{
		(*treePtr)->rightPtr = malloc(sizeof(TREENODE));
		(*treePtr)->rightPtr->data = 100;
		(*treePtr)->rightPtr->leftPtr = NULL;
		(*treePtr)->rightPtr->rightPtr = NULL;
		zapolnenieNAprint(&((*treePtr)->rightPtr), maxLevel, currentLevel + 1);
	}
}

void poiskelementa(TREENODEPTR treePtr, int number, int i, int maxLevel, int j)
{

	if (treePtr->rightPtr != NULL && i < number)
		poiskelementa(treePtr->rightPtr, number, i + 1, maxLevel, j);
	if (treePtr->leftPtr != NULL && i < number)
		poiskelementa(treePtr->leftPtr, number, i + 1, maxLevel, j);
	if (i == number)
		print(treePtr->data, maxLevel - number + 1, j, maxLevel);
}


void freeTree(TREENODEPTR* treePtr)
{
	if (*treePtr != NULL)
	{
		if ((*treePtr)->leftPtr)   freeTree(&((*treePtr)->leftPtr));
		if ((*treePtr)->rightPtr)  freeTree(&((*treePtr)->rightPtr));
		free(*treePtr);

	}
	*treePtr = NULL;
}


void inOrder(TREENODEPTR treePtr)
{
	if (treePtr != NULL) {
		inOrder(treePtr->leftPtr);				/*заходим в наше дерево, печатаем самый левый(минимальный элемент по заполнению), дальше печатаем самый левый символ не считая этот и так далее*/
		printf("%d  ", treePtr->data);
		inOrder(treePtr->rightPtr);
	}
}

void preOrder(TREENODEPTR treePtr)
{
	if (treePtr != NULL) {
		printf("%d  ", treePtr->data);
		preOrder(treePtr->leftPtr);			/*Печатаем первый, печатаем первый левый, печатаем второй левой, и тд как только эти "левые" закончились печатаем один правый и также идем по принципу печатаем "левый"*/
		preOrder(treePtr->rightPtr);
	}
}

void postOrder(TREENODEPTR treePtr)
{
	if (treePtr != NULL) {
		postOrder(treePtr->leftPtr);
		postOrder(treePtr->rightPtr);			/*Печатаем самый левый, возвращаемся к узлу, от узла идём вправо, там ищем самый левый, и тд через рекурсию*/
		printf("%d  ", treePtr->data);
	}
}


void doubleDelete(TREENODEPTR* current)
{
	TREENODEPTR temp = NULL;

	while ((*current)->leftPtr != NULL && (*current)->data == (*current)->leftPtr->data) //если значение в обрабатываемом равно значению в левом потомке
	{
		temp = (*current)->leftPtr; //сохраняем потомка для чистки
		(*current)->leftPtr = (*current)->leftPtr->leftPtr; //смещаем связь
		free(temp); //чистим 
	}

	if ((*current)->leftPtr != NULL)
	{
		doubleDelete(&((*current)->leftPtr));
	}

	if ((*current)->rightPtr != NULL)
	{
		doubleDelete(&((*current)->rightPtr));
	}
}


//удаление
void delete(TREENODEPTR* root, int key)
{

	//проверка на пустоту дерева
	if (*root == NULL)
	{
		printf("\nДерево уже пустое, удалять нечего!\n");
		return;
	}

	else
	{
		TREENODEPTR current = NULL, temp = NULL;

		//если удаляемый нами эл-т - корень
		if ((*root)->data == key)
		{
			//если дерево только из корня
			if ((*root)->leftPtr == NULL && (*root)->rightPtr == NULL)
			{
				free(*root);
				*root = NULL;
				printf("\nДерево теперь пустое!\n");
				return;
			}

			//если у корня есть листья по обе стороны
			else if ((*root)->leftPtr != NULL && (*root)->rightPtr != NULL)
			{
				current = minim((*root)->rightPtr); //то к минимальному из правой ветки прикрепляем левую ветку корня
				current->leftPtr = (*root)->leftPtr;

				temp = (*root);
				(*root) = (*root)->rightPtr; //и смещаем корень вправо
				free(temp);
				return;
			}

			//если всё дерево уходит вправо
			else if ((*root)->leftPtr == NULL)
			{
				temp = (*root);
				(*root) = (*root)->rightPtr; //то прикреплять нечего, просто смещаем корень вправо
				free(temp);
				return;
			}

			//если всё дерево уходит влево
			else if ((*root)->rightPtr == NULL)
			{
				temp = (*root);
				(*root) = (*root)->leftPtr; //то прикреплять нечего, просто смещаем корень влево
				free(temp);
				return;
			}

			return;
		}


		// если удаляемый элемент - лист
		TREENODEPTR l = NULL, m = NULL; //m-предок l-удаляемый элемент
		int flag; //будет 1, если l - это левый потомок и 0, если l- это правый потомок, нужно для 3 случая

		m = prevSearch(*root, key); //находим предка удаляемого эл-та

		if (!m)
		{
			printf("\nЗапрашиваемое на удаление число не найдено в дереве!\n");
			return;
		}


		if (m->leftPtr != NULL && m->leftPtr->data == key)//нашли удаляемый элемент, поставили флаг
		{
			l = m->leftPtr;
			flag = 1;
		}

		if (m->rightPtr != NULL && m->rightPtr->data == key)//нашли удаляемый элемент, поставили флаг
		{
			l = m->rightPtr;
			flag = 0;
		}

		// 1 случай - лист без потомков
		if ((l->leftPtr == NULL) && (l->rightPtr == NULL))
		{
			if (flag == 1) m->leftPtr = NULL; //если флаг 1, т.е. лист слева от предка, то зануляем левую связь предка
			else m->rightPtr = NULL; // иначе правую
			free(l);
		}

		// 2 случай, 1 вариант - поддерево справа
		else if ((l->leftPtr == NULL) && (l->rightPtr != NULL))
		{
			if (flag) m->leftPtr = l->rightPtr;
			else m->rightPtr = l->rightPtr;
			free(l);
		}

		// 2 случай, 2 вариант - поддерево слева
		else if ((l->leftPtr != NULL) && (l->rightPtr == NULL))
		{
			if (flag) m->leftPtr = l->leftPtr;
			else m->rightPtr = l->leftPtr;
			free(l);
		}

		// 3 случай - два потомка: и слева, и справа
		else if ((l->leftPtr != NULL) && (l->rightPtr != NULL))
		{
			current = minim(l->rightPtr);
			current->leftPtr = l->leftPtr;

			if (flag) m->leftPtr = l->rightPtr;
			else m->rightPtr = l->rightPtr;

			free(l);
		}
	}

	return;
}

//поиск нужного эл-та
TREENODEPTR search(TREENODEPTR root, int key)
{
	// Если дерево пусто или ключ корня равен искомому ключу, то возвращается указатель на корень
	if ((root == NULL) || (root->data = key))
		return root;
	// Поиск нужного узла
	if (key < root->data)
		return search(root->leftPtr, key);
	else return search(root->rightPtr, key);
}

//поиск предка (эл-та перед нужным)
TREENODEPTR prevSearch(TREENODEPTR root, int key)
{
	// если дерево пусто или ключ корня равен искомому ключу, то возвращается указатель на корень

	if ((root == NULL))
	{
		return root; //ситуация, когда искомого эл-та нет 
	}

	//находим элемент, у которого потом нам подходит
	if (root->leftPtr != NULL && root->leftPtr->data == key)
		return root;

	if (root->rightPtr != NULL && root->rightPtr->data == key)
		return root;


	// Поиск нужного узла
	if (key < root->data) prevSearch(root->leftPtr, key);
	else prevSearch(root->rightPtr, key);
}

// Минимальный элемент дерева
TREENODEPTR minim(TREENODEPTR root)
{
	TREENODEPTR l = root;
	while (l->leftPtr != NULL)
		l = l->leftPtr;
	return l;
}


void level_elems(TREENODEPTR treePtr, int level, int current)
{

	if (treePtr != NULL) {
		current++;
		if (current == level) {
			printf("%d ", treePtr->data);
			return;
		}
		else if (current < level) {
			level_elems(treePtr->leftPtr, level, current);
			level_elems(treePtr->rightPtr, level, current);

		}
	}
}


int height(TREENODEPTR treePtr, int max)
{
	max++;
	int max1;
	int max2;
	if (treePtr->leftPtr != NULL)
		max1 = height(treePtr->leftPtr, max);
	else
		max1 = max;
	if (treePtr->rightPtr != NULL)
		max2 = height(treePtr->rightPtr, max);
	else
		max2 = max;
	if (max1 > max2)
		max = max1;
	else
		max = max2;
	return max;
}


void insertNode(TREENODEPTR* treePtr, int value)
{
	static int counter = 0; //счёт рекурсий, нужно для особых действий при вставке нового корня

	if (*treePtr == NULL) {
		*treePtr = malloc(sizeof(TREENODE));			/*Остановка рекурсии*/
		if (*treePtr != NULL) {
			(*treePtr)->data = value;
			(*treePtr)->leftPtr = NULL; /*Ставим число в нужное место, и две ветви отводим от этой ячейки и зануляем их*/
			(*treePtr)->rightPtr = NULL;
		}
		else
			printf("%d not inserted. No memore available.\n", value); /*Защита от утечки памяти*/
		counter = 0;
	}
	else if (counter == 0 && value == (*treePtr)->data) //если первый раз, то хотим добавить верхушку
	{
		TREENODEPTR newPtr = malloc(sizeof(TREENODE)); //создаём новый элемент
		newPtr->data = value; //присваиваем значение
		newPtr->leftPtr = *treePtr; //прицепляем к нему  старую верхушку
		newPtr->rightPtr = (*treePtr)->rightPtr; //всю правую ветку верхушки перецепляем
		(*treePtr)->rightPtr = NULL; //режем связь к правой ветке и старой верхушки
		*treePtr = newPtr; //теперь верхушка - новый элемент
	}
	else if ((*treePtr)->leftPtr != NULL && (*treePtr)->leftPtr->data == value) //если такой же элемент нашёлся у левого потомка обрабатываемого элемента
	{
		TREENODEPTR newPtr = malloc(sizeof(TREENODE)); //создаём новый элемент
		newPtr->data = value; //присваиваем значение
		newPtr->rightPtr = (*treePtr)->leftPtr->rightPtr; //перекинули правую ветку от потомка к новому эл-ту
		(*treePtr)->leftPtr->rightPtr = NULL;
		newPtr->leftPtr = (*treePtr)->leftPtr; //присоединили левого потомка обрабатываемого к новому элементу
		(*treePtr)->leftPtr = newPtr; //прицепили новый элемент к обрабатываемому 

	}
	else if ((*treePtr)->rightPtr != NULL && (*treePtr)->rightPtr->data == value) //если такой же элемент нашёлся у правого потомка обрабатываемого элемента
	{
		TREENODEPTR newPtr = malloc(sizeof(TREENODE)); //создаём новый элемент
		newPtr->data = value; //присваиваем значение
		newPtr->rightPtr = NULL;
		newPtr->leftPtr = (*treePtr)->rightPtr->leftPtr;
		(*treePtr)->rightPtr->leftPtr = newPtr;

	}
	else if (value < (*treePtr)->data)
	{
		counter++;
		insertNode(&((*treePtr)->leftPtr), value);		/*Обход влево и снова пытаемся найти нужное место*/
	}
	else if (value > (*treePtr)->data)
	{
		counter++;
		insertNode(&((*treePtr)->rightPtr), value);/*Обход вправа и снова пытаемся найти нужное место*/
	}
}


void instructions() {
	printf("\n\nЧто желаете сделать?\n"
		"0. ВНИМАНИЕ! Нажав 0 можно всегда вызвать инструкцию!\n"
		"1. Обход дерева:прямой, обратный, концевой\n"
		"2. Поэтажный обход дерева\n"
		"3. Копирование дерева\n"
		"4. Опредление высоты дерева\n"
		"5. Удаление двойников\n"
		"6. Удалить дерево\n"
		"7. Печать дерева\n"
		"8. Удалить элемент\n"
		"9. Добавить элемент\n"
		"10. Ввести новое дерево\n"
		"11. Завершение работы\n");
}
