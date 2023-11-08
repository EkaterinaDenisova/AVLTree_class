#pragma once
// author: Денисова Екатерина
#include "TreeNode.h"

// класс узла AVL-дерева
template <typename T>
class AVLTreeNode : public TreeNode<T>  // наследник класса TreeNode
{
private:
	//int balanceFactor;

public:
	int balanceFactor;
	// дополнительный член класса
	// используется методами класса AVLTree и позволяет
	// избегать "перевешивания" узлов
	// 
	// конструктор без параметров
	// Компилятор напишет конструктор по умолчанию
	AVLTreeNode() = default;

	// конструктор с параметрами
	AVLTreeNode(const T& item, AVLTreeNode<T>* lptr = nullptr, AVLTreeNode<T>* rptr = nullptr, int balfact = 0);

	// методы доступа к полям указателей
	AVLTreeNode<T>* Left() const;
	AVLTreeNode<T>* Right() const;

	void SetRight(AVLTreeNode<T>* right1);
	void SetLeft(AVLTreeNode<T>* right1);


	// метод для доступа к новому полю данных
	int GetBalanceFactor();
};

// конструктор инициализирует поля данных и указателей
// значение nullptr соответствует пустому поддереву
template <typename T>
AVLTreeNode<T>::AVLTreeNode(const T& item, AVLTreeNode<T>* lptr, AVLTreeNode<T>* rptr, int balfact)
{
	this->data = item;
	this->left = lptr;
	this->right = rptr;
	this->balanceFactor = balfact;
}

// Методы Left и Right возвращают значения полей левого и правого указателей
template <typename T>
AVLTreeNode<T>* AVLTreeNode<T>::Right() const
{
	return (AVLTreeNode<T>*)this->right;
}

template <typename T>
AVLTreeNode<T>* AVLTreeNode<T>::Left() const
{
	return (AVLTreeNode<T>*)this->left;
}

// Метод задания значения правого потомка
template <typename T>
void AVLTreeNode<T>::SetRight(AVLTreeNode<T>* right1) {
	this->right = right1;
}

// Метод задания значения левого потомка
template <typename T>
void AVLTreeNode<T>::SetLeft(AVLTreeNode<T>* left1) {
	this->left = left1;
}

// метод для доступа к новому полю данных
template <typename T>
int AVLTreeNode<T>::GetBalanceFactor() {
	return this->balanceFactor;
}


// операция копирования бинарного дерева поиска
// возвращает указатель на корень нового дерева
template <typename T>
AVLTreeNode<T>* CopyTree(AVLTreeNode<T>* t) {

	// переменная newnode указывает на новый узел, 
	// присоединяемый в дальнейшем
	// к новому дереву, указатели newlptr и newrptr адресуют сыновей
	// нового узла и передаются в качестве параметров при создании узла
	AVLTreeNode<T>* newlptr, * newrptr, * newnode;
	// остановить рекурсивное прохождение при достижении пустого дерева
	if (t == nullptr)
		return nullptr;

	// CopyTree строит новое дерево в процессе прохождения узлов дерева t. в каждом
	// узле этого дерева функция CopyTree проверяет наличие левого сына, если он
	// есть, создается его копия, в противном случае возвращается NULL. CopyTree
	// создает копию узла с помощью GetTreeNode и подвешивает к нему копии сыновей.
	if (t->Left() != nullptr)
		newlptr = CopyTree(t->Left());
	else
		newlptr = nullptr;
	if (t->Right() != nullptr)
		newrptr = CopyTree(t->Right());
	else
		newrptr = nullptr;

	// построить новое дерево снизу вверх, сначала создавая
	// двух сыновей, а затем их родителя
	newnode = new AVLTreeNode<T>(t->Data(), newlptr, newrptr);

	// вернуть указатель на вновь созданное дерево
	return newnode;

}