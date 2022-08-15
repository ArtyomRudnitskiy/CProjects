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

void print(char data, int level, int j, int maxLevel); //функция №1
void copyBinaryTree(TREENODEPTR* root, TREENODEPTR* treePtr); //копирование дерева
void zapolnenieNAprint(TREENODEPTR* treePtr, int maxLevel, int currentLevel); //вспом. функция для печати (чтобы не было пустых элементов)
void poiskelementa(TREENODEPTR treePtr, int number, int i, int maxLevel, int j); //поэтажный обход


void freeTree(TREENODEPTR* treePtr); //функция №2

void inOrder(TREENODEPTR);	//функция №3	/*По возрастанию*/
void preOrder(TREENODEPTR);
void postOrder(TREENODEPTR);

void doubleDelete(TREENODEPTR* current); //функция №4

void delete(TREENODEPTR* root, int key); //функция №5
TREENODEPTR search(TREENODEPTR root, int key);
TREENODEPTR prevSearch(TREENODEPTR root, int key);
TREENODEPTR minim(TREENODEPTR root);

void level_elems(TREENODEPTR treePtr, int level, int current);//функция №6

void copyBinaryTree(TREENODEPTR* root, TREENODEPTR* treePtr); //функция №7

int height(TREENODEPTR treePtr, int max); //функция №8

void insertNode(TREENODEPTR*, int);

void instructions();

