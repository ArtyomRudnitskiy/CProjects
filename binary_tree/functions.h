#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <math.h>

struct treeNode {
	struct treeNode* leftPtr;
	char data;
	struct treeNode* rightPtr;
};

typedef struct treeNode TREENODE;
typedef  TREENODE* TREENODEPTR;

void print(char data, int level, int j, int maxLevel); //������� �1
void copyBinaryTree(TREENODEPTR* root, TREENODEPTR* treePtr); //����������� ������
void zapolnenieNAprint(TREENODEPTR* treePtr, int maxLevel, int currentLevel); //�����. ������� ��� ������ (����� �� ���� ������ ���������)
void poiskelementa(TREENODEPTR treePtr, int number, int i, int maxLevel, int j); //��������� �����


void freeTree(TREENODEPTR* treePtr); //������� �2

void inOrder(TREENODEPTR);	//������� �3	/*�� �����������*/
void preOrder(TREENODEPTR);
void postOrder(TREENODEPTR);

void doubleDelete(TREENODEPTR* current); //������� �4

void delete(TREENODEPTR* root, int key); //������� �5
TREENODEPTR search(TREENODEPTR root, int key);
TREENODEPTR prevSearch(TREENODEPTR root, int key);
TREENODEPTR minim(TREENODEPTR root);

void level_elems(TREENODEPTR treePtr, int level, int current);//������� �6

void copyBinaryTree(TREENODEPTR* root, TREENODEPTR* treePtr); //������� �7

int height(TREENODEPTR treePtr, int max); //������� �8

void insertNode(TREENODEPTR*, int);

void instructions();

