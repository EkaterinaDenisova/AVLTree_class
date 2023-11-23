#pragma once
// author: �������� ���������

#include "AVLTreeNode.h"


const int leftheavy = -1;
const int balanced = 0;
const int rightheavy = 1;

// ����� AVL-������
template <typename T>
class AVLTree
{
private:
	// ��������� �� ������ 
	AVLTreeNode<T>* root;
	//AVLTreeNode<T>* current;

	// ����� ��������� ������ 
	int size;

public:
	// ����������� �� ���������
	AVLTree();

	// ����������� � ����������
	AVLTree(AVLTreeNode<T>* tree);


	// ����������� �����������
	//AVLTree(const AVLTree<T>& tree);

	// �������� ����������� (������������)
	//AVLTree<T>& operator= (const AVLTree<T>& rhs);

	// ����������
	~AVLTree() { deleteTree(this->root); }


	// ����������� ������ ��������� �������

	// ���������� �������, �� ������� ��������� ������� ����
	// ���� -1, ���� ���� � ����� ��������� � ������ ���
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

	// ��������, ������ �� ������
	bool ListEmpty() const;

	// ���������� ����� � ������
	int ListSize() const;

	AVLTreeNode<T>* GetRoot();

};

// ����������� �� ���������
template <typename T>
AVLTree<T>::AVLTree()
{
	this->root = nullptr;
	//this->current = nullptr;
	this->size = 0;
}

// ����������� � �����������
template <typename T>
AVLTree<T>::AVLTree(AVLTreeNode<T>* tree)
{
	this->root = CopyTree(tree);
	//this->current = nullptr;
	this->size = treeCount(this->root);
}

// ����������� �����������
/*template <typename T>
AVLTree<T>::AVLTree(const AVLTree<T>& tree)
{
	this->root = CopyTree(tree.root);

	// ��������� �������� ��������� �������� ����� � ������ ������ ������
	this->current = this->root;
	this->size = tree.size;
}*/


// �������� ����������� (������������)
/*template <class T>
AVLTree<T>& AVLTree<T>::operator= (const AVLTree<T>& rhs)
{
	// ������ ���������� ������ � ���� ����
	if (this == &rhs)
		return *this;

	// �������� ������� ������
	ClearList();

	// ����������� ����� ������ � ������� ������
	this->root = CopyTree(rhs.root);

	// ��������� �������� ��������� �������� ����� � ������ ������ ������
	this->current = this->root;
	this->size = rhs.size;

	// ���������� ������ �� ������� ������
	return *this;
}*/

// ������� ������
template <typename T>
void AVLTree<T>::ClearList() {
	deleteTree(this->root);
	this->root = nullptr;
	//this->current = nullptr;
	this->size = 0;
}

//��������, ������ �� ������
template<class T>
bool AVLTree<T>::ListEmpty() const {
	return (this->root == nullptr);
}

// ���������� ����� � ������
template<class T>
int AVLTree<T>::ListSize() const {
	return this->size;
}


// ����� ����
// ���������� �������, �� ������� ��� ������ ����
// ���� -1, ���� ���� � ������� ��������� ���
template<class T>
int AVLTree<T>::Find(const T& item) {
	return SearchNode(this->root, item);
}

// ���������� ��������� �� ������
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
// ��������� ������� �� ������� ������� ������ ���� �.
// ������� l� ����� ������ ��������
template <class T>
void AVLTree<T>::SingleRotateRight(AVLTreeNode<T>*& p)
{
	// �����, �������������� ��������� ���� �
	AVLTreeNode<T>* lc;
	// ��������� l� ����� ����������
	lc = p->Left();
	// ��������������� ���������� ������������������ ���
	// ������������� ���� � ��� ������ ����
	p->balanceFactor = balanced;
	lc->balanceFactor = balanced;
	// ������ ��������� ���� l� � ����� ������ ������ ���������� ������
	// �� l�. ��������� ��� �������, ������ st ����� ���������� ���� �
	p->SetLeft(lc->Right());
	// ����������� � � ������ ��������� ���� l�.
	// ������� l� ����� ������ ��������.
	lc->SetRight(p);
	p = lc;
}

// ��������� ������� ������ ������� ������� ������ ���� �.
// ������� r� ����� ������ ��������
template <class T>
void AVLTree<T>::SingleRotateLeft(AVLTreeNode<T>*& p)
{
	// ������, �������������� ��������� ���� �
	AVLTreeNode<T>* rc;
	// ��������� l� ����� ����������
	rc = p->Right();
	// ��������������� ���������� ������������������ ���
	// ������������� ���� � ��� ������ ����
	p->balanceFactor = balanced;
	rc->balanceFactor = balanced;
	// ����� ��������� ���� r� � ����� ������ ������ ���������� �����
	// �� r�. ��������� ��� �������, ������ st ������ ���������� ���� �
	p->SetRight(rc->Left());
	// ����������� � � ����� ��������� ���� r�.
	// ������� r� ����� ������ ��������.
	rc->SetLeft(p);
	p = rc;
}

// ������� ������� ������ ������ ���� �
template <class T>
void AVLTree<T>::DoubleRotateRight(AVLTreeNode<T>*& p)
{
	// ��� ���������, ���������� ��������
	AVLTreeNode<T>* lc, *np;
	// ���� lc <= ���� np < ���� �
	lc = p->Left(); // ����� ��� ���� �
	np = lc->Right(); // ������ ��� ���� 1�
	// �������� ���������� ������������������ � ����� �, 1� � ��
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
	// ����� ��� ��� �������� ������������ ���� �,
	// ������� ����������� ��� ������ ����� � ������������ �����
	lc->SetRight(np->Left());
	np->SetLeft(lc);
	p->SetLeft(np->Right());
	np->SetRight(p);
	p = np;
}

// ������� ������� ������ ������ ���� �
template <class T>
void AVLTree<T>::DoubleRotateLeft(AVLTreeNode<T>*& p)
{
	// ��� ���������, ���������� ��������
	AVLTreeNode<T>* rc, * np;
	// ���� rc >= ���� np > ���� �
	rc = p->Right(); // ������ ��� ���� �
	np = rc->Left(); // �������� ��� ���� r�
	// �������� ���������� ������������������ � ����� �, r� � np
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
	// ����� ��� ��� �������� ������������ ���� �,
	// ������� ����������� ��� ������ ����� � ������������ �����
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
	// ������������ ����� ���������?
	if (lc->balanceFactor == leftheavy)
	{
		SingleRotateRight(p); // ����������� �������
		reviseBalanceFactor = 0;
	}
	// ������������ ������ ���������?
	else if (lc->balanceFactor == rightheavy)
	{
		// ��������� ������� �������
		DoubleRotateRight(p);
		// ������ ������ �����������
		reviseBalanceFactor = 0;
	}
}

template <class T>
void AVLTree<T>::UpdateRightTree(AVLTreeNode<T>*& p,
	int reviseBalanceFactor)
{
	AVLTreeNode<T>* lc;
	lc = p->Right();
	// ������������ ������ ���������?
	if (lc->balanceFactor == rightheavy)
	{
		SingleRotateLeft(p); // ����������� �������
		reviseBalanceFactor = 0;
	}
	// ������������ ����� ���������?
	else if (lc->balanceFactor == leftheavy)
	{
		// ��������� ������� �������
		DoubleRotateLeft(p);
		// ������ ������ �����������
		reviseBalanceFactor = 0;
	}
}

// ����������� ����� �������
template <class T>
void AVLTree<T>::AVLInsert(AVLTreeNode<T>* tree,
	AVLTreeNode<T>* newNode, int& reviseBalanceFactor)
{
	// ������ "���������� ������������������ ��� �������"
	int rebalanceCurrNode;

	// ����������� ������ ���������, ���� �������� ����� ����
	if (tree == nullptr)
	{
		// �������� ����� ����
		tree = newNode;
		// �������� ����� ���� ����������������
		tree->balanceFactor = balanced;
		// �������� �� ��������� ���������� ������������������
		reviseBalanceFactor = 1;
	}
	// ���������� ���������� �� ������ ���������,
	// ���� ����� ���� ������ ��������
	else if (newNode->Data() < tree->Data())
	{
		AVLInsert(tree->Left(), newNode, rebalanceCurrNode);
		// ���������, ����� �� �������������� balanceFactor
		if (rebalanceCurrNode)
		{
			// ��������� ����� �� ����, ��������������� �����, ����� ��������
			// ������� ������������������; ��������� ������� (������ 3)
			if (tree->GetBalanceFactor() == leftheavy)
				UpdateLeftTree(tree, reviseBalanceFactor);
			// ������� ����� �� ����������������� ����.
			// ���� ������ ������������ ����� (������ 1)
			else if (tree->GetBalanceFactor() == balanced)
			{
				tree->balanceFactor = leftheavy;
				reviseBalanceFactor = 1;
			}
			// ������� ����� �� ����, ��������������� ������.
			// ���� ������ ���������������� (������ 2)
			else
			{
				tree->balanceFactor = balanced;
				reviseBalanceFactor = 0;
			}
		}
		else
			// ���������������� �� ���������, �� ���������� ���������� ����
			reviseBalanceFactor = 0;
	}
	// ����� ���������� ���������� �� ������� ���������
	else if (newNode->Data() > tree->Data())
	{
		AVLInsert(tree->Right(), newNode, rebalanceCurrNode);
		// ���������, ����� �� �������������� balanceFactor
		if (rebalanceCurrNode)
		{
			// ������� ������ �� ����, ��������������� ������, ����� ��������
			// ������� ������������������; ��������� ������� (������ 3)
			if (tree->GetBalanceFactor() == rightheavy)
				UpdateRightTree(tree, reviseBalanceFactor);
			// ������� ������ �� ����������������� ����.
			// ���� ������ ������������ ������ (������ 1)
			else if (tree->GetBalanceFactor() == balanced)
			{
				tree->balanceFactor = rightheavy;
				reviseBalanceFactor = 1;
			}
			// ������� ������ �� ����, ��������������� �����.
			// ���� ������ ���������������� (������ 2)
			else
			{
				tree->balanceFactor = balanced;
				reviseBalanceFactor = 0;
			}
		}
		else
			// ���������������� �� ���������, �� ���������� ���������� ����
			reviseBalanceFactor = 0;
	}
}

template <class T>
void AVLTree<T>::Insert(const T& item)
{
	// �������� ��������� AVL-������, ��������� �����
	// GetRoot.
	AVLTreeNode<T>* treeRoot = this->GetRoot(), 
		*newNode;

	// ������, ������������ �������� AVLInsert ��� ���������������� �����
	int reviseBalanceFactor = 0;

	// ������� ����� ���� AVL-������ � �������� ������ ����������
	newNode = new AVLTreeNode<T>(item, nullptr, nullptr);

	// ������� ����������� ��������� ��� ����������� ������� ��������
	AVLInsert(treeRoot, newNode, reviseBalanceFactor);

	// ��������� ����� �������� ��������� ������ �������� ������
	this->root = treeRoot;
	this->current = newNode;
	this->size++;
}*/

// ������� ����
/*template<class T>
void AVLTree<T>::Insert(const T& item) {
	this->root = InsertNode(this->root, item);
	size = treeCount(this->root);
}

// �������� ����
template<class T>
void AVLTree<T>::Delete(const T& item) {
	this->root = DeleteNode(this->root, item);
	size = treeCount(this->root);
}*/
