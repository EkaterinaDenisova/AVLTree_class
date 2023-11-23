#pragma once
// author: �������� ���������
#include "TreeNode.h"

// ����� ���� AVL-������
template <typename T>
class AVLTreeNode : public TreeNode<T>  // ��������� ������ TreeNode
{
private:
	// �������������� ���� ������
	// ������������ �������� ������ AVLTree � ���������
	// �������� "�������������" �����
	int balanceFactor;

public:
	//int balanceFactor;
	
	// ����������� ��� ����������
	// ���������� ������� ����������� �� ���������
	AVLTreeNode() = default;

	// ����������� � �����������
	AVLTreeNode(const T& item, AVLTreeNode<T>* lptr = nullptr, AVLTreeNode<T>* rptr = nullptr, int balfact = 0);

	// ������ ������� � ����� ����������
	AVLTreeNode<T>* Left() const;
	AVLTreeNode<T>* Right() const;
	//T Data() const;

	void SetRight(AVLTreeNode<T>* right1);
	void SetLeft(AVLTreeNode<T>* right1);


	// ����� ��� ������� � balance factor
	int GetBalanceFactor();
	//��������� balance factor
	void SetBalanceFactor(int bfactor);
	// ���������� balance factor ��� ����
	//int ResetBalanceFactor(AVLTreeNode<T>* avlnode);

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
	//return dynamic_cast<AVLTreeNode<T>*>(this->right);
	return (AVLTreeNode<T>*)this->right;
}

template <typename T>
AVLTreeNode<T>* AVLTreeNode<T>::Left() const
{
	//return dynamic_cast<AVLTreeNode<T>*>(this->left);
	return (AVLTreeNode<T>*)this->left;
}

// ����� Data ���������� �������� ���� ������
/*template <typename T>
T AVLTreeNode<T>::Data() const
{
	return this->data;
}*/

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

// ����� ��� ������� � balance factor
template <typename T>
int AVLTreeNode<T>::GetBalanceFactor() {
	//this->balanceFactor = ResetBalanceFactor(this);
	//������� ������
	/*if (this == nullptr) {
		return 0;
	}*/
	//������������� balance factor
	this->balanceFactor = treeHeight(this->right) - treeHeight(this->left);
	return this->balanceFactor;
}

//��������� balance factor
template <typename T>
void AVLTreeNode<T>::SetBalanceFactor(int bfactor) {
	balanceFactor = bfactor;
}

// ���������� balance factor ��� ����
/*template <typename T>
int AVLTreeNode<T>::ResetBalanceFactor(AVLTreeNode<T>* avlnode) {
	//������� ������
	if (avlnode == nullptr) {
		return 0;
	}
	//������������� balance factor
	return treeHeight(avlnode->Right()) - treeHeight(avlnode->Left());
}*/

// ��������� �������� ����� � avl-������
// (������� �������� ����������� �� ������ ���������)
// ����� �������
template <typename T>
AVLTreeNode<T>* SingleRotateLeft(AVLTreeNode<T>* avlnode) {

	AVLTreeNode<T>* rightTree = avlnode->Right();
	AVLTreeNode<T>* rightTree_left = rightTree->Left();

	// ������ �������

	// avlnode ���������� ����� �������� ������ �������� ������� ������� (������� ������ ������� �������)
	rightTree->SetLeft(avlnode);
	
	// ���� � ������� ������� avlnode ���� ����� ������� (����� ���������)
	// �� ��� ���������� ������� ��������� avlnode
	avlnode->SetRight(rightTree_left);
	
	// ���������� ��������� �� ����� ������ (������� ������ ��� ������ �������� avlnode)
	return rightTree;
}

// ������ �������
template <typename T>
AVLTreeNode<T>* SingleRotateRight(AVLTreeNode<T>* avlnode) {

	AVLTreeNode<T>* leftTree = avlnode->Left();
	AVLTreeNode<T>* leftTree_right = leftTree->Right();

	// ������ �������

	// avlnode ���������� ������ �������� ������ �������� ������ ������� (������� �� ������� �������)
	leftTree->SetRight(avlnode);

	// ���� � ������ ������� avlnode ���� ������ ������� (������ ���������)
	// �� ��� ���������� ������ ��������� avlnode
	avlnode->SetLeft(leftTree_right);

	// ���������� ��������� �� ����� ������ (������� ������ ��� ����� �������� avlnode)
	return leftTree;
}

//������������ ������ (���������) � ������ root
//���������� ������ ����������������� ������ (���������)
template <typename T>
AVLTreeNode<T>* RebalanceTree(AVLTreeNode<T>* root) {
	// ������� ������
	if (root == nullptr) {
		return nullptr;
	}

	// ������������� balance factor ��� �����, ����������� ��� �������� � ���������� balfact
	//root->SetBalanceFactor(ResetBalanceFactor(root));
	int balfact = root->GetBalanceFactor();

	// ��������� ������� ������ � �����-���� �� ������, ������ ��������������� ��������
	// ���� ������ ����� ������� �����
	if (balfact <= -2) {
		// ���� ��� ���� ����� ��������� ����� ������ ����� � ���� ������ ���������
		// �� ��������� ������� ������� 
		if (root->Left()->GetBalanceFactor() > 0) {
			// �.�. ������� ����� ������� ����� ������� ������ ��������� (����� ��� �� ������������ ������)
			root->SetLeft(SingleRotateLeft(root->Left()));
		}
		// ������ ������� ��� ����� �������� ������ (���������)
		return SingleRotateRight(root);
	}

	// ���� �� ������ ����� ������� ������
	else if (balfact >= 2) {
		// ���� ��� ���� ������ ��������� ����� ������ ����� � ���� ����� ���������
		// �� ��������� ������� ������� 
		if (root->Right()->GetBalanceFactor() < 0) {
			// �.�. ������� ����� ������� ������ ������� ������� ��������� (����� ��� �� ������������ �����)
			root->SetRight(SingleRotateRight(root->Right()));
		}
		// ����� ������� ��� ����� �������� ������ (���������)
		return SingleRotateLeft(root);
	}
	// ���� ������������ �� �����
	return root;
}

// �������� ������� ���� � AVL-������
template <typename T>
AVLTreeNode<T>* InsertNode(AVLTreeNode<T>* root, const T value) {

	if (root == nullptr) {

		// ���� ������ ������, �� ������ ������ (������ ����)
		return new AVLTreeNode<T>(value);
	}

	// ��������� ������ ���� � �����, ���� � ������ ���������
	if (value > root->Data()) {
		// ���� ��������, ������� ����� ��������, ������ ��������
		root->SetRight(InsertNode(root->Right(), value));
	}
	else if (value < root->Data()) {
		// ���� ��������, ������� ����� ��������, ������ ��������
		root->SetLeft(InsertNode(root->Left(), value));
	}

	// �� ��������� � ������� ������� ��� �������� ��������� ������ ������
	// � AVL-������ ����������� ������������ �� balance factor

	//���������� ������ ����������������� ������
	return RebalanceTree(root);
}

// ��������� �������� ���� �� ������
// �������� �������� ���� �� ��������� ������ ������
template <typename T>
AVLTreeNode<T>* DeleteNode(AVLTreeNode<T>* root, const T value) {

	// ������� ������
	if (root == nullptr) {
		return root;
	}

	// ����������� ����� �������, ���� �� ����� ������ ����, ������� ����� �������
	if (root->Data() > value) {
		root->SetLeft(DeleteNode(root->Left(), value));
		return RebalanceTree(root);
	}
	else if (root->Data() < value) {
		root->SetRight(DeleteNode(root->Right(), value));
		return RebalanceTree(root);
	}
	else { // ����� ������ ���� �� ��������
		

		// ������ 1 � 2. ���� ���� ������ 1 ������� ��� ������� ���������� ���� (0 ��������)
		// ���� ��� ������ �������, �� ������ ����������� �� ����� ���������� ����
		if (root->Left() == nullptr) {
			AVLTreeNode<T>* temp = root->Right();
			delete root;
			return RebalanceTree(temp);
		}
		// ���� ��� ������� �������, �� ����� ����������� �� ����� ���������� ����
		else if (root->Right() == nullptr) {
			AVLTreeNode<T>* temp = root->Left();
			delete root;
			return RebalanceTree(temp);
		}

		// ������ 3. ���� ���� ��� �������
		else {

			// ����, ������� �������� ��������� ���������� �����������
			AVLTreeNode<T>* succParent = root;

			// ������� ��������� ���������� (����� ����� ���� � ������ ���������) � ��� ��������
			AVLTreeNode<T>* succ = root->Right();
			while (succ->Left() != nullptr) {
				succParent = succ;
				succ = succ->Left();
			}


			// ������ �������� � ������ �������� ���� ������ � ������ ��������
			// ������� ������� ���������� ����������� ������ ����� �������� ��������
			// ���������� �����������

			if (succParent != root)
				succParent->SetLeft(succ->Right());
			else
				// ���� ������ �� ������ ��������� �� ����
				succParent->SetRight(succ->Right());


			// ������ �� ���������� ����������� ����������� �� ����� ���������� ����
			root->SetData(succ->Data());

			// ������� ��������� ����������
			delete succ;
			return RebalanceTree(root);
		}
	}
}





// �������� ����������� ��������� ������ ������
// ���������� ��������� �� ������ ������ ������
/*template <typename T>
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

}*/