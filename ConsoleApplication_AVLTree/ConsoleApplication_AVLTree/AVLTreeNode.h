#pragma once
// author: �������� ���������
#include "TreeNode.h"

// ����� ���� AVL-������
template <typename T>
class AVLTreeNode : public TreeNode<T>  // ��������� ������ TreeNode
{
private:
	//int balanceFactor;

public:
	int balanceFactor;
	// �������������� ���� ������
	// ������������ �������� ������ AVLTree � ���������
	// �������� "�������������" �����
	// 
	// ����������� ��� ����������
	// ���������� ������� ����������� �� ���������
	AVLTreeNode() = default;

	// ����������� � �����������
	AVLTreeNode(const T& item, AVLTreeNode<T>* lptr = nullptr, AVLTreeNode<T>* rptr = nullptr, int balfact = 0);

	// ������ ������� � ����� ����������
	AVLTreeNode<T>* Left() const;
	AVLTreeNode<T>* Right() const;

	void SetRight(AVLTreeNode<T>* right1);
	void SetLeft(AVLTreeNode<T>* right1);


	// ����� ��� ������� � ������ ���� ������
	int GetBalanceFactor();
};

// ����������� �������������� ���� ������ � ����������
// �������� nullptr ������������� ������� ���������
template <typename T>
AVLTreeNode<T>::AVLTreeNode(const T& item, AVLTreeNode<T>* lptr, AVLTreeNode<T>* rptr, int balfact)
{
	this->data = item;
	this->left = lptr;
	this->right = rptr;
	this->balanceFactor = balfact;
}

// ������ Left � Right ���������� �������� ����� ������ � ������� ����������
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

// ����� ������� �������� ������� �������
template <typename T>
void AVLTreeNode<T>::SetRight(AVLTreeNode<T>* right1) {
	this->right = right1;
}

// ����� ������� �������� ������ �������
template <typename T>
void AVLTreeNode<T>::SetLeft(AVLTreeNode<T>* left1) {
	this->left = left1;
}

// ����� ��� ������� � ������ ���� ������
template <typename T>
int AVLTreeNode<T>::GetBalanceFactor() {
	return this->balanceFactor;
}


// �������� ����������� ��������� ������ ������
// ���������� ��������� �� ������ ������ ������
template <typename T>
AVLTreeNode<T>* CopyTree(AVLTreeNode<T>* t) {

	// ���������� newnode ��������� �� ����� ����, 
	// �������������� � ����������
	// � ������ ������, ��������� newlptr � newrptr �������� �������
	// ������ ���� � ���������� � �������� ���������� ��� �������� ����
	AVLTreeNode<T>* newlptr, * newrptr, * newnode;
	// ���������� ����������� ����������� ��� ���������� ������� ������
	if (t == nullptr)
		return nullptr;

	// CopyTree ������ ����� ������ � �������� ����������� ����� ������ t. � ������
	// ���� ����� ������ ������� CopyTree ��������� ������� ������ ����, ���� ��
	// ����, ��������� ��� �����, � ��������� ������ ������������ NULL. CopyTree
	// ������� ����� ���� � ������� GetTreeNode � ����������� � ���� ����� �������.
	if (t->Left() != nullptr)
		newlptr = CopyTree(t->Left());
	else
		newlptr = nullptr;
	if (t->Right() != nullptr)
		newrptr = CopyTree(t->Right());
	else
		newrptr = nullptr;

	// ��������� ����� ������ ����� �����, ������� ��������
	// ���� �������, � ����� �� ��������
	newnode = new AVLTreeNode<T>(t->Data(), newlptr, newrptr);

	// ������� ��������� �� ����� ��������� ������
	return newnode;

}