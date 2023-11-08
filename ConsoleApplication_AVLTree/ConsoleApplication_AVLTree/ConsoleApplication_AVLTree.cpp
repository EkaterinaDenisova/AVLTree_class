// ConsoleApplication_AVLTree.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "AVLTreeNode.h"
#include "AVLTree.h"

using namespace std;

int main()
{

    setlocale(LC_ALL, "rus");
    std::cout << "Hello World!\n";

    // создаётся указатели на узлы дерева 
    AVLTreeNode<int>* leftleaf, * rightleaf, * root;


    //      10
    //        \
    //         5
    //        / \
    //       2   4
    //      /
    //     12

    //создаётся указатель на лист дерева (указатели на левый и правый узлы nullptr)
    leftleaf = new AVLTreeNode<int>(12);

    //создаётся узел только с левым потомком
    root = new AVLTreeNode<int>(2, leftleaf, nullptr);

    // указатель leftleaf переносится на только что созданный узел
    leftleaf = root;
    rightleaf = new AVLTreeNode<int>(4);

    //создаётся узел с левым и правым потомком
    root = new AVLTreeNode<int>(5, leftleaf, rightleaf);
    rightleaf = root;

    //создаётся узел только с правым потомком
    root = new AVLTreeNode<int>(10, nullptr, rightleaf);

    // вывод дерева в консоль
    cout << root->Data() << "\n  " << root->Right()->Data() << "\n " << root->Right()->Left()->Data()
        << " " << root->Right()->Right()->Data() << "\n" << root->Right()->Left()->Left()->Data() << "\n\n";


    AVLTree<int> avltree1;
    avltree1.Insert(5);

    cout << avltree1.GetRoot()->Data();

}

