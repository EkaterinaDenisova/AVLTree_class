#pragma once
// author: Денисова Екатерина

#include "AVLTreeNode.h"


const int leftheavy = -1;
const int balanced = 0;
const int rightheavy = 1;

// класс AVL-дерева
template <typename T>
class AVLTree
{
private:
	// указатели на корень 
	AVLTreeNode<T>* root;
	//AVLTreeNode<T>* current;

	// число элементов дерева 
	int size;

public:
	// конструктор по умолчанию
	AVLTree();

	// конструктор с параметром
	AVLTree(AVLTreeNode<T>* tree);


	// конструктор копирования
	//AVLTree(const AVLTree<T>& tree);

	// оператор копирования (присваивания)
	//AVLTree<T>& operator= (const AVLTree<T>& rhs);

	// деструктор
	~AVLTree() { deleteTree(this->root); }


	// стандартные методы обработки списков

	// возвращает уровень, на котором находится искомый узел
	// либо -1, если узла с таким значением в дереве нет
	int Find(const T& item);

	/*void UpdateLeftTree(AVLTreeNode<T>*& p,
		int reviseBalanceFactor);

	void UpdateRightTree(AVLTreeNode<T>*& p,
		int reviseBalanceFactor);*/


	/*void AVLInsert(AVLTreeNode<T>* tree,
		AVLTreeNode<T>* newNode, int& reviseBalanceFactor);

	void SingleRotateRight(AVLTreeNode<T>*& p);
	void SingleRotateLeft(AVLTreeNode<T>*& p);
	void DoubleRotateRight(AVLTreeNode<T>*& p);
	void DoubleRotateLeft(AVLTreeNode<T>*& p);*/

	void Insert(const T& item);
	void Delete(const T& item);
	void ClearList();

	// проверка, пустое ли дерево
	bool ListEmpty() const;

	// количество узлов в дереве
	int ListSize() const;

	AVLTreeNode<T>* GetRoot();

};

// конструктор по умолчанию
template <typename T>
AVLTree<T>::AVLTree()
{
	this->root = nullptr;
	//this->current = nullptr;
	this->size = 0;
}

// конструктор с параметрами
template <typename T>
AVLTree<T>::AVLTree(AVLTreeNode<T>* tree)
{
	this->root = CopyTree(tree);
	//this->current = nullptr;
	this->size = treeCount(this->root);
}

// конструктор копирования
/*template <typename T>
AVLTree<T>::AVLTree(const AVLTree<T>& tree)
{
	this->root = CopyTree(tree.root);

	// присвоить текущему указателю значение корня и задать размер дерева
	this->current = this->root;
	this->size = tree.size;
}*/


// оператор копирования (присваивания)
/*template <class T>
AVLTree<T>& AVLTree<T>::operator= (const AVLTree<T>& rhs)
{
	// нельзя копировать дерево в само себя
	if (this == &rhs)
		return *this;

	// очистить текущее дерево
	ClearList();

	// скопировать новое дерево в текущий объект
	this->root = CopyTree(rhs.root);

	// присвоить текущему указателю значение корня и задать размер дерева
	this->current = this->root;
	this->size = rhs.size;

	// возвратить ссылку на текущий объект
	return *this;
}*/

// очистка дерева
template <typename T>
void AVLTree<T>::ClearList() {
	deleteTree(this->root);
	this->root = nullptr;
	//this->current = nullptr;
	this->size = 0;
}

//проверка, пустое ли дерево
template<class T>
bool AVLTree<T>::ListEmpty() const {
	return (this->root == nullptr);
}

// количество узлов в дереве
template<class T>
int AVLTree<T>::ListSize() const {
	return this->size;
}


// поиск узла
// возвращает уровень, на котором был найден узел
// либо -1, если узла с искомым значением нет
template<class T>
int AVLTree<T>::Find(const T& item) {
	return SearchNode(this->root, item);
}

// Возвращает указатель на корень
template <typename T>
AVLTreeNode<T>* AVLTree<T>::GetRoot()
{
	return this->root;
}

template <class T>
void AVLTree<T>::Insert(const T& item)
{
	this->root = InsertNode(this->root, item);
	size = treeCount(this->root);
}

template <class T>
void AVLTree<T>::Delete(const T& item)
{
	this->root = DeleteNode(this->root, item);
	size = treeCount(this->root);
}



/*
// выполнить поворот по часовой стрелке вокруг узла р.
// сделать lс новой точкой вращения
template <class T>
void AVLTree<T>::SingleRotateRight(AVLTreeNode<T>*& p)
{
	// левое, перевешивающее поддерево узла р
	AVLTreeNode<T>* lc;
	// назначить lс левым поддеревом
	lc = p->Left();
	// скорректировать показатель сбалансированности для
	// родительского узла и его левого сына
	p->balanceFactor = balanced;
	lc->balanceFactor = balanced;
	// правое поддерево узла lс в любом случае должно оставаться справа
	// от lс. выполнить это условие, сделав st левым поддеревом узла р
	p->SetLeft(lc->Right());
	// переместить р в правое поддерево узла lс.
	// сделать lс новой точкой вращения.
	lc->SetRight(p);
	p = lc;
}

// выполнить поворот против часовой стрелки вокруг узла р.
// сделать rс новой точкой вращения
template <class T>
void AVLTree<T>::SingleRotateLeft(AVLTreeNode<T>*& p)
{
	// правое, перевешивающее поддерево узла р
	AVLTreeNode<T>* rc;
	// назначить lс левым поддеревом
	rc = p->Right();
	// скорректировать показатель сбалансированности для
	// родительского узла и его левого сына
	p->balanceFactor = balanced;
	rc->balanceFactor = balanced;
	// левое поддерево узла rс в любом случае должно оставаться слева
	// от rс. выполнить это условие, сделав st правым поддеревом узла р
	p->SetRight(rc->Left());
	// переместить р в левое поддерево узла rс.
	// сделать rс новой точкой вращения.
	rc->SetLeft(p);
	p = rc;
}

// двойной поворот вправо вокруг узла р
template <class T>
void AVLTree<T>::DoubleRotateRight(AVLTreeNode<T>*& p)
{
	// два поддерева, подлежащих повороту
	AVLTreeNode<T>* lc, *np;
	// узел lc <= узел np < узел р
	lc = p->Left(); // левый сын узла р
	np = lc->Right(); // правый сын узла 1с
	// обновить показатели сбалансированности в узлах р, 1с и пр
	if (np->balanceFactor == rightheavy)
	{
		p->balanceFactor = balanced;
		lc->balanceFactor = rightheavy;
	}
	else
	{
		p->balanceFactor = rightheavy;
		lc->balanceFactor = balanced;
	}
	np->balanceFactor = balanced;
	// перед тем как заменить родительский узел р,
	// следует отсоединить его старых детей и присоединить новых
	lc->SetRight(np->Left());
	np->SetLeft(lc);
	p->SetLeft(np->Right());
	np->SetRight(p);
	p = np;
}

// двойной поворот вправо вокруг узла р
template <class T>
void AVLTree<T>::DoubleRotateLeft(AVLTreeNode<T>*& p)
{
	// два поддерева, подлежащих повороту
	AVLTreeNode<T>* rc, * np;
	// узел rc >= узел np > узел р
	rc = p->Right(); // правый сын узла р
	np = rc->Left(); // левыйвый сын узла rс
	// обновить показатели сбалансированности в узлах р, rс и np
	if (np->balanceFactor == leftheavy)
	{
		p->balanceFactor = balanced;
		rc->balanceFactor = leftheavy;
	}
	else
	{
		p->balanceFactor = leftheavy;
		rc->balanceFactor = balanced;
	}
	np->balanceFactor = balanced;
	// перед тем как заменить родительский узел р,
	// следует отсоединить его старых детей и присоединить новых
	rc->SetLeft(np->Right());
	np->SetRight(rc);
	p->SetRight(np->Left());
	np->SetLeft(p);
	p = np;
}

template <class T>
void AVLTree<T>::UpdateLeftTree(AVLTreeNode<T>*& p,
	int reviseBalanceFactor)
{
	AVLTreeNode<T>* lc;
	lc = p->Left();
	// перевешивает левое поддерево?
	if (lc->balanceFactor == leftheavy)
	{
		SingleRotateRight(p); // однократный поворот
		reviseBalanceFactor = 0;
	}
	// перевешивает правое поддерево?
	else if (lc->balanceFactor == rightheavy)
	{
		// выполнить двойной поворот
		DoubleRotateRight(p);
		// теперь корень уравновешен
		reviseBalanceFactor = 0;
	}
}

template <class T>
void AVLTree<T>::UpdateRightTree(AVLTreeNode<T>*& p,
	int reviseBalanceFactor)
{
	AVLTreeNode<T>* lc;
	lc = p->Right();
	// перевешивает правое поддерево?
	if (lc->balanceFactor == rightheavy)
	{
		SingleRotateLeft(p); // однократный поворот
		reviseBalanceFactor = 0;
	}
	// перевешивает левое поддерево?
	else if (lc->balanceFactor == leftheavy)
	{
		// выполнить двойной поворот
		DoubleRotateLeft(p);
		// теперь корень уравновешен
		reviseBalanceFactor = 0;
	}
}

// рекурсивный метод вставки
template <class T>
void AVLTree<T>::AVLInsert(AVLTreeNode<T>* tree,
	AVLTreeNode<T>* newNode, int& reviseBalanceFactor)
{
	// флажок "Показатель сбалансированности был изменен"
	int rebalanceCurrNode;

	// встретилось пустое поддерево, пора включать новый узел
	if (tree == nullptr)
	{
		// вставить новый узел
		tree = newNode;
		// объявить новый узел сбалансированным
		tree->balanceFactor = balanced;
		// сообщить об изменении показателя сбалансированности
		reviseBalanceFactor = 1;
	}
	// рекурсивно спускаться по левому поддереву,
	// если новый узел меньше текущего
	else if (newNode->Data() < tree->Data())
	{
		AVLInsert(tree->Left(), newNode, rebalanceCurrNode);
		// проверить, нужно ли корректировать balanceFactor
		if (rebalanceCurrNode)
		{
			// включение слева от узла, перевешивающего влево, будет нарушено
			// условие сбалансированности; выполнить поворот (случай 3)
			if (tree->GetBalanceFactor() == leftheavy)
				UpdateLeftTree(tree, reviseBalanceFactor);
			// вставка слева от сбалансированного узла.
			// узел станет перевешивать влево (случай 1)
			else if (tree->GetBalanceFactor() == balanced)
			{
				tree->balanceFactor = leftheavy;
				reviseBalanceFactor = 1;
			}
			// вставка слева от узла, перевешивающего вправо.
			// узел станет сбалансированным (случай 2)
			else
			{
				tree->balanceFactor = balanced;
				reviseBalanceFactor = 0;
			}
		}
		else
			// перебалансировка не требуется, не опрашивать предыдущие узлы
			reviseBalanceFactor = 0;
	}
	// иначе рекурсивно спускаться по правому поддереву
	else if (newNode->Data() > tree->Data())
	{
		AVLInsert(tree->Right(), newNode, rebalanceCurrNode);
		// проверить, нужно ли корректировать balanceFactor
		if (rebalanceCurrNode)
		{
			// вставка справа от узла, перевешивающего вправо, будет нарушено
			// условие сбалансированности; выполнить поворот (случай 3)
			if (tree->GetBalanceFactor() == rightheavy)
				UpdateRightTree(tree, reviseBalanceFactor);
			// вставка справа от сбалансированного узла.
			// узел станет перевешивать вправо (случай 1)
			else if (tree->GetBalanceFactor() == balanced)
			{
				tree->balanceFactor = rightheavy;
				reviseBalanceFactor = 1;
			}
			// вставка справа от узла, перевешивающего влево.
			// узел станет сбалансированным (случай 2)
			else
			{
				tree->balanceFactor = balanced;
				reviseBalanceFactor = 0;
			}
		}
		else
			// перебалансировка не требуется, не опрашивать предыдущие узлы
			reviseBalanceFactor = 0;
	}
}

template <class T>
void AVLTree<T>::Insert(const T& item)
{
	// объявить указатель AVL-дерева, используя метод
	// GetRoot.
	AVLTreeNode<T>* treeRoot = this->GetRoot(), 
		*newNode;

	// флажок, используемый функцией AVLInsert для перебалансировки узлов
	int reviseBalanceFactor = 0;

	// создать новый узел AVL-дерева с нулевыми полями указателей
	newNode = new AVLTreeNode<T>(item, nullptr, nullptr);

	// вызвать рекурсивную процедуру для фактической вставки элемента
	AVLInsert(treeRoot, newNode, reviseBalanceFactor);

	// присвоить новые значения элементам данных базового класса
	this->root = treeRoot;
	this->current = newNode;
	this->size++;
}*/

// вставка узла
/*template<class T>
void AVLTree<T>::Insert(const T& item) {
	this->root = InsertNode(this->root, item);
	size = treeCount(this->root);
}

// удаление узла
template<class T>
void AVLTree<T>::Delete(const T& item) {
	this->root = DeleteNode(this->root, item);
	size = treeCount(this->root);
}*/
