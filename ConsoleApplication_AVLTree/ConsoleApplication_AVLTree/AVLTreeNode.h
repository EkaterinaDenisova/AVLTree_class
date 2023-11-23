#pragma once
// author: Денисова Екатерина
#include "TreeNode.h"

// класс узла AVL-дерева
template <typename T>
class AVLTreeNode : public TreeNode<T>  // наследник класса TreeNode
{
private:
	// дополнительный член класса
	// используется методами класса AVLTree и позволяет
	// избегать "перевешивания" узлов
	int balanceFactor;

public:
	//int balanceFactor;
	
	// конструктор без параметров
	// Компилятор напишет конструктор по умолчанию
	AVLTreeNode() = default;

	// конструктор с параметрами
	AVLTreeNode(const T& item, AVLTreeNode<T>* lptr = nullptr, AVLTreeNode<T>* rptr = nullptr, int balfact = 0);

	// методы доступа к полям указателей
	AVLTreeNode<T>* Left() const;
	AVLTreeNode<T>* Right() const;
	//T Data() const;

	void SetRight(AVLTreeNode<T>* right1);
	void SetLeft(AVLTreeNode<T>* right1);


	// метод для доступа к balance factor
	int GetBalanceFactor();
	//установка balance factor
	void SetBalanceFactor(int bfactor);
	// вычисление balance factor для узла
	//int ResetBalanceFactor(AVLTreeNode<T>* avlnode);

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
	//return dynamic_cast<AVLTreeNode<T>*>(this->right);
	return (AVLTreeNode<T>*)this->right;
}

template <typename T>
AVLTreeNode<T>* AVLTreeNode<T>::Left() const
{
	//return dynamic_cast<AVLTreeNode<T>*>(this->left);
	return (AVLTreeNode<T>*)this->left;
}

// Метод Data возвращает значение поля данных
/*template <typename T>
T AVLTreeNode<T>::Data() const
{
	return this->data;
}*/

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

// метод для доступа к balance factor
template <typename T>
int AVLTreeNode<T>::GetBalanceFactor() {
	//this->balanceFactor = ResetBalanceFactor(this);
	//базовый случай
	/*if (this == nullptr) {
		return 0;
	}*/
	//пересчитываем balance factor
	this->balanceFactor = treeHeight(this->right) - treeHeight(this->left);
	return this->balanceFactor;
}

//установка balance factor
template <typename T>
void AVLTreeNode<T>::SetBalanceFactor(int bfactor) {
	balanceFactor = bfactor;
}

// вычисление balance factor для узла
/*template <typename T>
int AVLTreeNode<T>::ResetBalanceFactor(AVLTreeNode<T>* avlnode) {
	//базовый случай
	if (avlnode == nullptr) {
		return 0;
	}
	//пересчитываем balance factor
	return treeHeight(avlnode->Right()) - treeHeight(avlnode->Left());
}*/

// одинарные повороты узлов в avl-дереве
// (двойные повороты реализуются на основе одинарных)
// левый поворот
template <typename T>
AVLTreeNode<T>* SingleRotateLeft(AVLTreeNode<T>* avlnode) {

	AVLTreeNode<T>* rightTree = avlnode->Right();
	AVLTreeNode<T>* rightTree_left = rightTree->Left();

	// делаем поворот

	// avlnode становится левым потомком своего прежнего правого потомка (поворот против часовой стрелки)
	rightTree->SetLeft(avlnode);
	
	// если у правого потомка avlnode были левые потомки (левое поддерево)
	// то они становятся правыми потомками avlnode
	avlnode->SetRight(rightTree_left);
	
	// возвращаем указатель на новый корень (который раньше был правым потомком avlnode)
	return rightTree;
}

// правый поворот
template <typename T>
AVLTreeNode<T>* SingleRotateRight(AVLTreeNode<T>* avlnode) {

	AVLTreeNode<T>* leftTree = avlnode->Left();
	AVLTreeNode<T>* leftTree_right = leftTree->Right();

	// делаем поворот

	// avlnode становится правым потомком своего прежнего левого потомка (поворот по часовой стрелке)
	leftTree->SetRight(avlnode);

	// если у левого потомка avlnode были правые потомки (правое поддерево)
	// то они становятся левыми потомками avlnode
	avlnode->SetLeft(leftTree_right);

	// возвращаем указатель на новый корень (который раньше был левым потомком avlnode)
	return leftTree;
}

//балансировка дерева (поддерева) с корнем root
//возвращает корень сбалансированного дерева (поддерева)
template <typename T>
AVLTreeNode<T>* RebalanceTree(AVLTreeNode<T>* root) {
	// базовый случай
	if (root == nullptr) {
		return nullptr;
	}

	// пересчитываем balance factor для корня, запиисываем его значение в переменную balfact
	//root->SetBalanceFactor(ResetBalanceFactor(root));
	int balfact = root->GetBalanceFactor();

	// проверяем перевес дерева в какую-либо из сторон, делаем соответствующие повороты
	// Если дерево имеет перевес влево
	if (balfact <= -2) {
		// Если при этом левое поддерево имеет больше узлов в своём правом поддереве
		// то необходим двойной поворот 
		if (root->Left()->GetBalanceFactor() > 0) {
			// т.е. сначала нужно сделать левый поворот левого поддерева (чтобы оно не перевешивало вправо)
			root->SetLeft(SingleRotateLeft(root->Left()));
		}
		// правый поворот для корня текущего дерева (поддерева)
		return SingleRotateRight(root);
	}

	// Если же дерево имеет перевес вправо
	else if (balfact >= 2) {
		// Если при этом правое поддерево имеет больше узлов в своём левом поддереве
		// то необходим двойной поворот 
		if (root->Right()->GetBalanceFactor() < 0) {
			// т.е. сначала нужно сделать правый поворот правого поддерева (чтобы оно не перевешивало влево)
			root->SetRight(SingleRotateRight(root->Right()));
		}
		// левый поворот для корня текущего дерева (поддерева)
		return SingleRotateLeft(root);
	}
	// если балансировка не нужна
	return root;
}

// операция вставки узла в AVL-дерево
template <typename T>
AVLTreeNode<T>* InsertNode(AVLTreeNode<T>* root, const T value) {

	if (root == nullptr) {

		// если дерево пустое, то создаём корень (первый узел)
		return new AVLTreeNode<T>(value);
	}

	// Вставляем данные либо в левое, либо в правое поддерево
	if (value > root->Data()) {
		// если значение, которое нужно добавить, больше текущего
		root->SetRight(InsertNode(root->Right(), value));
	}
	else if (value < root->Data()) {
		// если значение, которое нужно добавить, меньше текущего
		root->SetLeft(InsertNode(root->Left(), value));
	}

	// по сравнению с методом вставки для обычного бинарного дерева поиска
	// в AVL-дереве добавляется балансировка по balance factor

	//возвращаем корень сбалансированного дерева
	return RebalanceTree(root);
}

// опрерация удаления узла из дерева
// операция удаления узла из бинарного дерева поиска
template <typename T>
AVLTreeNode<T>* DeleteNode(AVLTreeNode<T>* root, const T value) {

	// базовый случай
	if (root == nullptr) {
		return root;
	}

	// рекурсивный вызов функции, пока не будет найден узел, который нужно удалить
	if (root->Data() > value) {
		root->SetLeft(DeleteNode(root->Left(), value));
		return RebalanceTree(root);
	}
	else if (root->Data() < value) {
		root->SetRight(DeleteNode(root->Right(), value));
		return RebalanceTree(root);
	}
	else { // Когда найден узел на удаление
		

		// Случаи 1 и 2. если есть только 1 потомок или удалить необходимо лист (0 потомков)
		// если нет левого потомка, то правый поднимается на место удаляемого узла
		if (root->Left() == nullptr) {
			AVLTreeNode<T>* temp = root->Right();
			delete root;
			return RebalanceTree(temp);
		}
		// если нет правого потомка, то левый поднимается на место удаляемого узла
		else if (root->Right() == nullptr) {
			AVLTreeNode<T>* temp = root->Left();
			delete root;
			return RebalanceTree(temp);
		}

		// Случай 3. если есть оба потомка
		else {

			// узел, который является родителем ближайшего наибольшего
			AVLTreeNode<T>* succParent = root;

			// Находим ближайшее наибольшее (самый левый узел в правом поддереве) и его родителя
			AVLTreeNode<T>* succ = root->Right();
			while (succ->Left() != nullptr) {
				succParent = succ;
				succ = succ->Left();
			}


			// задача сводится к случаю удаления узла только с правым потомком
			// правого потомка ближайшего наибольшего делаем левым потомком родителя
			// ближайшего наибольшего

			if (succParent != root)
				succParent->SetLeft(succ->Right());
			else
				// если спуска по левому поддереву не было
				succParent->SetRight(succ->Right());


			// данные из ближайшего наибольшего переносятся на место удаляемого узла
			root->SetData(succ->Data());

			// Удаляем ближайшее наибольшее
			delete succ;
			return RebalanceTree(root);
		}
	}
}





// операция копирования бинарного дерева поиска
// возвращает указатель на корень нового дерева
/*template <typename T>
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

}*/