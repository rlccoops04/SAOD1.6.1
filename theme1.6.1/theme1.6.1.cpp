#include <iostream>
using namespace std;
struct Node
{
    int key;
    int count;
    Node* pLeft;
    Node* pRight;
};
void searchNode(Node*& pCurrent, int searchkey)
{
    bool Stop = false;
    while (pCurrent != nullptr && (not Stop))
    {
        if (searchkey < pCurrent->key)
        {
            pCurrent = pCurrent->pLeft;
        }
        else if (searchkey > pCurrent->key)
        {
            pCurrent = pCurrent->pRight;
        }
        else
        {
            Stop = true;
        }
    }
}
void addNodeRec(Node*& pCurrent, int newkey)
{
    if (pCurrent == nullptr)
    {
        pCurrent = new Node;
        pCurrent->key = newkey;
        pCurrent->pLeft = nullptr; pCurrent->pRight = nullptr;
        pCurrent->count = 1;
    }
    else
    {
        if (newkey < pCurrent->key)
        {
            addNodeRec(pCurrent->pLeft, newkey);
        }
        else if (newkey > pCurrent->key)
        {
            addNodeRec(pCurrent->pRight, newkey);
        }
        else
        {
            pCurrent->count += 1;
        }
    }
}
void addNodeNonRec(Node*& pRoot, int newkey)
{
    Node* pParent = new Node;
    Node* pCurrent = pRoot;
    if (pCurrent == nullptr)
    {
        pRoot = new Node;
        pRoot->key = newkey;
        pRoot->pLeft = nullptr; pRoot->pRight = nullptr;
        pRoot->count = 1;
    }
    else
    {
        while (pCurrent != nullptr)
        {
            pParent = pCurrent;
            if (newkey < pCurrent->key)
            {
                pCurrent = pCurrent->pLeft;
            }
            else if (newkey > pCurrent->key)
            {
                pCurrent = pCurrent->pRight;
            }
            else
            {
                pCurrent->count++;
                pCurrent = nullptr;
            }
        }
        if (newkey < pParent->key)
        {
            pCurrent = new Node;
            pCurrent->pLeft = nullptr;
            pCurrent->pRight = nullptr;
            pCurrent->key = newkey;
            pCurrent->count = 1;
            pParent->pLeft = pCurrent;
        }
        else if(newkey>pParent->key)
        {
            pCurrent = new Node;
            pCurrent->pLeft = nullptr;
            pCurrent->pRight = nullptr;
            pCurrent->key = newkey;
            pCurrent->count = 1;
            pParent->pRight = pCurrent;
        }
    }
}
void changer(Node*& pCurrent, Node*& pTemp)
{
    if (pCurrent->pRight != nullptr) { changer(pCurrent->pRight, pTemp); }
    else
    {
        pTemp->key = pCurrent->key;
        pTemp = pCurrent;
        pCurrent = pCurrent->pLeft;
    }
}
void deleteNode(Node*& pCurrent, int key)
{
    Node* pTemp = new Node();
    if (pCurrent == nullptr)
    {
        std::cout << "Вершина не найдена" << endl;
    }
    else if (key < pCurrent->key)
    {
        deleteNode(pCurrent->pLeft, key);
    }
    else if (key > pCurrent->key)
    {
        deleteNode(pCurrent->pRight, key);
    }
    else
    {
        pTemp = pCurrent;
        if (pTemp->pRight == nullptr)
        {
            pCurrent = pTemp->pLeft;
        }
        else if (pTemp->pLeft == nullptr)
        {
            pCurrent = pTemp->pRight;
        }
        else
        {
            changer(pCurrent->pLeft, pTemp);
        }
        delete pTemp;
        pTemp = nullptr;
    }
}
void displayBackSymmetric(Node* pCurrent, int lvl)
{
    if (pCurrent != nullptr)
    {
        lvl++;
        displayBackSymmetric(pCurrent->pRight, lvl);
        for (int i = 0; i < lvl - 1; i++)
        {
            std::cout << "     ";
        }
        std::cout << pCurrent->key << std::endl;
        displayBackSymmetric(pCurrent->pLeft, lvl);
    }
}
void display(Node* pCurrent)
{
    if (pCurrent != nullptr)
    {
        display(pCurrent->pLeft);
        cout << pCurrent->key << "(" << pCurrent->count << ")  ";
        display(pCurrent->pRight);
    }
}
void clearMemory(Node*& pCurrent)
{
    if (pCurrent != nullptr)
    {
        clearMemory(pCurrent->pLeft);
        clearMemory(pCurrent->pRight);
        delete pCurrent;
        pCurrent = nullptr;
    }
}
int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    Node* pRoot = nullptr;
    bool menu = true;
    int choicemenu, numNode, newkey, choicepush, searchkey;
    Node* pCurrent;
    while (menu)
    {
        cout << "1) Добавить случайные вершины.\n"
            "2) Добавить вершину.\n"
            "3) Найти вершину\n"
            "4) Удалить вершину\n"
            "5) Обратно-симметричный вывод\n"
            "6) Вывод в строку\n"
            "7) Выход\n\nВвод: ";
        cin >> choicemenu;
        switch (choicemenu)
        {
        case 1:
            cout << "Введите количество вершин: ";
            cin >> numNode;
            for (int i = 0; i < numNode; i++)
            {
                addNodeRec(pRoot, rand() % 101);
            }
            break;
        case 2:
            cout << "Введите новую вершину: ";
            cin >> newkey;
            cout << "Добавление рекурсивным(0) или нерекурсивным(1) методом: ";
            cin >> choicepush;
            if (choicepush == 0)
            {
                addNodeRec(pRoot, newkey);
            }
            else
            {
                addNodeNonRec(pRoot, newkey);
            }
            break;
        case 3:
            cout << "Введите вершину(инф. часть): ";
            cin >> searchkey;
            pCurrent = pRoot;
            searchNode(pCurrent, searchkey);
            cout << "Вершина: " << pCurrent->key << "(" << pCurrent->count << ")\n";
            break;
        case 4:
            cout << "Введите вершину для удаления: ";
            cin >> searchkey;
            deleteNode(pRoot, searchkey);
            break;
        case 5:
            displayBackSymmetric(pRoot, 0);
            break;
        case 6:
            display(pRoot);
            std::cout << std::endl;
            break;
        case 7:
            menu = false;
            break;
        default:
            cout << "Введите корректное значение.\n";
            break;
        }
        cout << endl;
    }
    clearMemory(pRoot);
}