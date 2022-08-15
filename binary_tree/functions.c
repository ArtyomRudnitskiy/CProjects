#include "Functions.h"

void print(char data, int level, int j, int maxLevel)
{
	static int count = 0;
	static int n = 0;								/*n - ������ �������, ������� � ������ ������� ������, � ������������� �� ������� n*/
	static int tempN = 0;
	count++;
	if (count == j)
	{
		n = tempN;
		n = n + pow(2, level);			/*�������� �������� ������ ������, ��� ����� ������ max ������*/
		tempN = n;
	}
	level--;						/*����������� ��������, ��� ���������� ���������; ����� ��� ������� n - ������ �������*/
	for (int k = 1; k < n; k++)		/*�������� ������ ����� ��������*/
		printf(" ");
	if (data == 100)
		printf("[]\r");		/*�������� ������ �����, � ������ ������� ������� � ������ ������*/
	else
		printf("%2d\r", data);
	n = n - pow(2, level + 2);	/*������ ��������� ������ ���-�� ��������, ������� ������������ ������ �� �������� �����*/
	if (count == pow(2, maxLevel) - 1)
	{
		count = 0;
		tempN = 0;
	}

}

void copyBinaryTree(TREENODEPTR* root, TREENODEPTR* treePtr) {

	*root = malloc(sizeof(TREENODE));			/*��������� ��������*/
	if (*root != NULL) {
		(*root)->leftPtr = NULL; /*������ ����� � ������ �����, � ��� ����� ������� �� ���� ������ � �������� ��*/
		(*root)->rightPtr = NULL;
	}
	else
		printf("No memore available.\n"); /*������ �� ������ ������*/


	(*root)->data = (*treePtr)->data;
	if ((*treePtr)->leftPtr != NULL)
		copyBinaryTree(&((*root)->leftPtr), &((*treePtr)->leftPtr));
	if ((*treePtr)->rightPtr != NULL)
		copyBinaryTree(&((*root)->rightPtr), &((*treePtr)->rightPtr));


}

void zapolnenieNAprint(TREENODEPTR* treePtr, int maxLevel, int currentLevel)
{
	if ((*treePtr)->leftPtr != NULL)									/*�� ������ ���������� ���������*/
		zapolnenieNAprint(&((*treePtr)->leftPtr), maxLevel, currentLevel + 1);
	else if ((*treePtr)->leftPtr == NULL && currentLevel <= maxLevel)
	{
		(*treePtr)->leftPtr = malloc(sizeof(TREENODE));
		(*treePtr)->leftPtr->data = 100;
		(*treePtr)->leftPtr->leftPtr = NULL;
		(*treePtr)->leftPtr->rightPtr = NULL;
		zapolnenieNAprint(&((*treePtr)->leftPtr), maxLevel, currentLevel + 1);
	}

	if ((*treePtr)->rightPtr != NULL)									/*�� ������ ���������� ���������*/
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
		inOrder(treePtr->leftPtr);				/*������� � ���� ������, �������� ����� �����(����������� ������� �� ����������), ������ �������� ����� ����� ������ �� ������ ���� � ��� �����*/
		printf("%d  ", treePtr->data);
		inOrder(treePtr->rightPtr);
	}
}

void preOrder(TREENODEPTR treePtr)
{
	if (treePtr != NULL) {
		printf("%d  ", treePtr->data);
		preOrder(treePtr->leftPtr);			/*�������� ������, �������� ������ �����, �������� ������ �����, � �� ��� ������ ��� "�����" ����������� �������� ���� ������ � ����� ���� �� �������� �������� "�����"*/
		preOrder(treePtr->rightPtr);
	}
}

void postOrder(TREENODEPTR treePtr)
{
	if (treePtr != NULL) {
		postOrder(treePtr->leftPtr);
		postOrder(treePtr->rightPtr);			/*�������� ����� �����, ������������ � ����, �� ���� ��� ������, ��� ���� ����� �����, � �� ����� ��������*/
		printf("%d  ", treePtr->data);
	}
}


void doubleDelete(TREENODEPTR* current)
{
	TREENODEPTR temp = NULL;

	while ((*current)->leftPtr != NULL && (*current)->data == (*current)->leftPtr->data) //���� �������� � �������������� ����� �������� � ����� �������
	{
		temp = (*current)->leftPtr; //��������� ������� ��� ������
		(*current)->leftPtr = (*current)->leftPtr->leftPtr; //������� �����
		free(temp); //������ 
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


//��������
void delete(TREENODEPTR* root, int key)
{

	//�������� �� ������� ������
	if (*root == NULL)
	{
		printf("\n������ ��� ������, ������� ������!\n");
		return;
	}

	else
	{
		TREENODEPTR current = NULL, temp = NULL;

		//���� ��������� ���� ��-� - ������
		if ((*root)->data == key)
		{
			//���� ������ ������ �� �����
			if ((*root)->leftPtr == NULL && (*root)->rightPtr == NULL)
			{
				free(*root);
				*root = NULL;
				printf("\n������ ������ ������!\n");
				return;
			}

			//���� � ����� ���� ������ �� ��� �������
			else if ((*root)->leftPtr != NULL && (*root)->rightPtr != NULL)
			{
				current = minim((*root)->rightPtr); //�� � ������������ �� ������ ����� ����������� ����� ����� �����
				current->leftPtr = (*root)->leftPtr;

				temp = (*root);
				(*root) = (*root)->rightPtr; //� ������� ������ ������
				free(temp);
				return;
			}

			//���� �� ������ ������ ������
			else if ((*root)->leftPtr == NULL)
			{
				temp = (*root);
				(*root) = (*root)->rightPtr; //�� ����������� ������, ������ ������� ������ ������
				free(temp);
				return;
			}

			//���� �� ������ ������ �����
			else if ((*root)->rightPtr == NULL)
			{
				temp = (*root);
				(*root) = (*root)->leftPtr; //�� ����������� ������, ������ ������� ������ �����
				free(temp);
				return;
			}

			return;
		}


		// ���� ��������� ������� - ����
		TREENODEPTR l = NULL, m = NULL; //m-������ l-��������� �������
		int flag; //����� 1, ���� l - ��� ����� ������� � 0, ���� l- ��� ������ �������, ����� ��� 3 ������

		m = prevSearch(*root, key); //������� ������ ���������� ��-��

		if (!m)
		{
			printf("\n������������� �� �������� ����� �� ������� � ������!\n");
			return;
		}


		if (m->leftPtr != NULL && m->leftPtr->data == key)//����� ��������� �������, ��������� ����
		{
			l = m->leftPtr;
			flag = 1;
		}

		if (m->rightPtr != NULL && m->rightPtr->data == key)//����� ��������� �������, ��������� ����
		{
			l = m->rightPtr;
			flag = 0;
		}

		// 1 ������ - ���� ��� ��������
		if ((l->leftPtr == NULL) && (l->rightPtr == NULL))
		{
			if (flag == 1) m->leftPtr = NULL; //���� ���� 1, �.�. ���� ����� �� ������, �� �������� ����� ����� ������
			else m->rightPtr = NULL; // ����� ������
			free(l);
		}

		// 2 ������, 1 ������� - ��������� ������
		else if ((l->leftPtr == NULL) && (l->rightPtr != NULL))
		{
			if (flag) m->leftPtr = l->rightPtr;
			else m->rightPtr = l->rightPtr;
			free(l);
		}

		// 2 ������, 2 ������� - ��������� �����
		else if ((l->leftPtr != NULL) && (l->rightPtr == NULL))
		{
			if (flag) m->leftPtr = l->leftPtr;
			else m->rightPtr = l->leftPtr;
			free(l);
		}

		// 3 ������ - ��� �������: � �����, � ������
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

//����� ������� ��-��
TREENODEPTR search(TREENODEPTR root, int key)
{
	// ���� ������ ����� ��� ���� ����� ����� �������� �����, �� ������������ ��������� �� ������
	if ((root == NULL) || (root->data = key))
		return root;
	// ����� ������� ����
	if (key < root->data)
		return search(root->leftPtr, key);
	else return search(root->rightPtr, key);
}

//����� ������ (��-�� ����� ������)
TREENODEPTR prevSearch(TREENODEPTR root, int key)
{
	// ���� ������ ����� ��� ���� ����� ����� �������� �����, �� ������������ ��������� �� ������

	if ((root == NULL))
	{
		return root; //��������, ����� �������� ��-�� ��� 
	}

	//������� �������, � �������� ����� ��� ��������
	if (root->leftPtr != NULL && root->leftPtr->data == key)
		return root;

	if (root->rightPtr != NULL && root->rightPtr->data == key)
		return root;


	// ����� ������� ����
	if (key < root->data) prevSearch(root->leftPtr, key);
	else prevSearch(root->rightPtr, key);
}

// ����������� ������� ������
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
	static int counter = 0; //���� ��������, ����� ��� ������ �������� ��� ������� ������ �����

	if (*treePtr == NULL) {
		*treePtr = malloc(sizeof(TREENODE));			/*��������� ��������*/
		if (*treePtr != NULL) {
			(*treePtr)->data = value;
			(*treePtr)->leftPtr = NULL; /*������ ����� � ������ �����, � ��� ����� ������� �� ���� ������ � �������� ��*/
			(*treePtr)->rightPtr = NULL;
		}
		else
			printf("%d not inserted. No memore available.\n", value); /*������ �� ������ ������*/
		counter = 0;
	}
	else if (counter == 0 && value == (*treePtr)->data) //���� ������ ���, �� ����� �������� ��������
	{
		TREENODEPTR newPtr = malloc(sizeof(TREENODE)); //������ ����� �������
		newPtr->data = value; //����������� ��������
		newPtr->leftPtr = *treePtr; //���������� � ����  ������ ��������
		newPtr->rightPtr = (*treePtr)->rightPtr; //��� ������ ����� �������� �����������
		(*treePtr)->rightPtr = NULL; //����� ����� � ������ ����� � ������ ��������
		*treePtr = newPtr; //������ �������� - ����� �������
	}
	else if ((*treePtr)->leftPtr != NULL && (*treePtr)->leftPtr->data == value) //���� ����� �� ������� ������� � ������ ������� ��������������� ��������
	{
		TREENODEPTR newPtr = malloc(sizeof(TREENODE)); //������ ����� �������
		newPtr->data = value; //����������� ��������
		newPtr->rightPtr = (*treePtr)->leftPtr->rightPtr; //���������� ������ ����� �� ������� � ������ ��-��
		(*treePtr)->leftPtr->rightPtr = NULL;
		newPtr->leftPtr = (*treePtr)->leftPtr; //������������ ������ ������� ��������������� � ������ ��������
		(*treePtr)->leftPtr = newPtr; //��������� ����� ������� � ��������������� 

	}
	else if ((*treePtr)->rightPtr != NULL && (*treePtr)->rightPtr->data == value) //���� ����� �� ������� ������� � ������� ������� ��������������� ��������
	{
		TREENODEPTR newPtr = malloc(sizeof(TREENODE)); //������ ����� �������
		newPtr->data = value; //����������� ��������
		newPtr->rightPtr = NULL;
		newPtr->leftPtr = (*treePtr)->rightPtr->leftPtr;
		(*treePtr)->rightPtr->leftPtr = newPtr;

	}
	else if (value < (*treePtr)->data)
	{
		counter++;
		insertNode(&((*treePtr)->leftPtr), value);		/*����� ����� � ����� �������� ����� ������ �����*/
	}
	else if (value > (*treePtr)->data)
	{
		counter++;
		insertNode(&((*treePtr)->rightPtr), value);/*����� ������ � ����� �������� ����� ������ �����*/
	}
}


void instructions() {
	printf("\n\n��� ������� �������?\n"
		"0. ��������! ����� 0 ����� ������ ������� ����������!\n"
		"1. ����� ������:������, ��������, ��������\n"
		"2. ��������� ����� ������\n"
		"3. ����������� ������\n"
		"4. ���������� ������ ������\n"
		"5. �������� ���������\n"
		"6. ������� ������\n"
		"7. ������ ������\n"
		"8. ������� �������\n"
		"9. �������� �������\n"
		"10. ������ ����� ������\n"
		"11. ���������� ������\n");
}
