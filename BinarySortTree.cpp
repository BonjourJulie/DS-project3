#include "BinarySortTree.h"
#include <queue>

template <class ElemType>
BinarySortTree<ElemType>::BinarySortTree(const ElemType* arr, int n) : root(nullptr) {
    for (int i = 0; i < n; ++i) {
        Insert(arr[i]);
    }
}

template <class ElemType>
void BinarySortTree<ElemType>::Destroy(BinTreeNode<ElemType>*& p) {
    if (p) {
        Destroy(p->leftChild);
        Destroy(p->rightChild);
        delete p;
        p = nullptr;
    }
}

template <class ElemType>
void BinarySortTree<ElemType>::InOrderTraverse(BinTreeNode<ElemType>* p) const {
    if (p) {
        InOrderTraverse(p->leftChild);
        std::cout << p->data << " ";
        InOrderTraverse(p->rightChild);
    }
}

template <class ElemType>
BinTreeNode<ElemType>* BinarySortTree<ElemType>::Search(const ElemType& key) const {
    return Search(root, key);
}

template <class ElemType>
BinTreeNode<ElemType>* BinarySortTree<ElemType>::Search(BinTreeNode<ElemType>* p, const ElemType& key) const {
    if (p == nullptr || p->data == key) {
        return p;
    }
    return key < p->data ? Search(p->leftChild, key) : Search(p->rightChild, key);
}

template <class ElemType>
bool BinarySortTree<ElemType>::Insert(const ElemType& key) {
    return Insert(root, key);
}

template <class ElemType>
bool BinarySortTree<ElemType>::Insert(BinTreeNode<ElemType>*& p, const ElemType& key) {
    if (p == nullptr) {
        p = new BinTreeNode<ElemType>(key);
        return true;
    }
    if (key == p->data) {
        return false; // �Ѵ��ڣ�������
    }
    return key < p->data ? Insert(p->leftChild, key) : Insert(p->rightChild, key);
}

// ��һ��ɾ���㷨���̲ı�׼�㷨��
template <class ElemType>
void BinarySortTree<ElemType>::DeleteStandard(BinTreeNode<ElemType>*& p, const ElemType& key) {
    if (p == nullptr) return;

    if (key < p->data) {
        DeleteStandard(p->leftChild, key);
    }
    else if (key > p->data) {
        DeleteStandard(p->rightChild, key);
    }
    else {
        if (p->leftChild == nullptr && p->rightChild == nullptr) { // Ҷ�ӽڵ�
            delete p;
            p = nullptr;
        }
        else if (p->leftChild == nullptr) { // ֻ��������
            BinTreeNode<ElemType>* temp = p;
            p = p->rightChild;
            delete temp;
        }
        else if (p->rightChild == nullptr) { // ֻ��������
            BinTreeNode<ElemType>* temp = p;
            p = p->leftChild;
            delete temp;
        }
        else { // ��������������
            // �ҵ�ǰ���ڵ㣨�����������ģ�
            BinTreeNode<ElemType>* predecessor = p->leftChild;
            BinTreeNode<ElemType>* predecessorParent = p;

            while (predecessor->rightChild != nullptr) {
                predecessorParent = predecessor;
                predecessor = predecessor->rightChild;
            }

            p->data = predecessor->data;
            if (predecessorParent == p) {
                predecessorParent->leftChild = predecessor->leftChild;
            }
            else {
                predecessorParent->rightChild = predecessor->leftChild;
            }
            delete predecessor;
        }
    }
}

// �ڶ���ɾ���㷨���ƶ�����������̵���������
template <class ElemType>
void BinarySortTree<ElemType>::DeleteAlternative(BinTreeNode<ElemType>*& p, const ElemType& key) {
    if (p == nullptr) return;
    if (key < p->data) {
        DeleteAlternative(p->leftChild, key);
    }
    else if (key > p->data) {
        DeleteAlternative(p->rightChild, key);
    }
    else {
        if (p->leftChild == nullptr && p->rightChild == nullptr) { // Ҷ�ӽڵ�
            delete p;
            p = nullptr;
        }
        else if (p->leftChild == nullptr) { // ֻ��������
            BinTreeNode<ElemType>* temp = p;
            p = p->rightChild;
            delete temp;
        }
        else if (p->rightChild == nullptr) { // ֻ��������
            BinTreeNode<ElemType>* temp = p;
            p = p->leftChild;
            delete temp;
        }
        else { // ��������������
            // �ҵ���̽ڵ㣨����������С�ģ�
            BinTreeNode<ElemType>* successor = p->rightChild;
            BinTreeNode<ElemType>* successorParent = p;
            while (successor->leftChild != nullptr) {
                successorParent = successor;
                successor = successor->leftChild;
            }
            successor->leftChild = p->leftChild;  // ��ԭ�������ƶ�����̵�������
            if (successorParent != p) {    // ����������
                successorParent->leftChild = successor->rightChild;
                successor->rightChild = p->rightChild;
            }
            // �ú�̽ڵ��滻��ǰ�ڵ�
            BinTreeNode<ElemType>* temp = p;
            p = successor;
            delete temp;
        }
    }
}

template <class ElemType>
int BinarySortTree<ElemType>::Height(BinTreeNode<ElemType>* p) const {
    if (p == nullptr) return 0;
    return 1 + std::max(Height(p->leftChild), Height(p->rightChild));
}

template <class ElemType>
double BinarySortTree<ElemType>::AverageSearchLength() const {
    int total = 0, nodes = 0;
    CalculateASL(root, 1, total, nodes);
    return nodes == 0 ? 0 : static_cast<double>(total) / nodes;
}

template <class ElemType>
void BinarySortTree<ElemType>::CalculateASL(BinTreeNode<ElemType>* p, int level, int& total, int& nodes) const {
    if (p) {
        total += level;
        nodes++;
        CalculateASL(p->leftChild, level + 1, total, nodes);
        CalculateASL(p->rightChild, level + 1, total, nodes);
    }
}

// ��ʽʵ����ģ���ࣨ������Ҫ����������ͣ�
template class BinarySortTree<int>;
template class BinarySortTree<double>;

//=======================================���Ժ���===================================

#include "BinarySortTree.h"
#include <iostream>
#include <ctime>
#include <vector>
#include <chrono> // �߾��ȼ�ʱ

using namespace std;

// ��ӡ���Խ��
template <class ElemType>
void TestBinarySortTree(const vector<ElemType>& arr) {
    cout << "��ʼ�������ݼ���" << endl;
    BinarySortTree<ElemType> tree(arr.data(), arr.size());

    // �����������
    cout << "����������������: ";
    tree.InOrderTraverse();
    cout << endl;

    // ���Բ��Ҳ���
    ElemType key = arr[arr.size() / 2];
    auto start = chrono::high_resolution_clock::now();
    auto result = tree.Search(key);
    auto end = chrono::high_resolution_clock::now();
    double time_used = chrono::duration<double>(end - start).count();
    if (result != nullptr) {
        cout << "����Ԫ�� " << key << " �ɹ���ʱ��: " << time_used << " ��" << endl;
    }
    else {
        cout << "����Ԫ�� " << key << " ʧ�ܡ�" << endl;
    }

    // ����ɾ��������ʹ�ñ�׼ɾ���㷨
    start = chrono::high_resolution_clock::now();
    tree.DeleteStandard(key);
    end = chrono::high_resolution_clock::now();
    time_used = chrono::duration<double>(end - start).count();
    cout << "ɾ����������׼�㷨����ʱ: " << time_used << " ��" << endl;

    // ����ɾ��������ʹ�����ɾ���㷨
    start = chrono::high_resolution_clock::now();
    tree.DeleteAlternative(key);
    end = chrono::high_resolution_clock::now();
    time_used = chrono::duration<double>(end - start).count();
    cout << "ɾ������������㷨����ʱ: " << time_used << " ��" << endl;

    // ���ܲ��ԣ����ĸ߶Ⱥ�ƽ�����ҳ���
    cout << "���ĸ߶�: " << tree.Height() << endl;
    cout << "ƽ�����ҳ���: " << tree.AverageSearchLength() << endl;
    cout << endl;
}


vector<int> generateLargeTestData(int size) {
    vector<int> data;
    srand(time(0));
    for (int i = 0; i < size; ++i) {
        data.push_back(rand() % 100); // ���� 0 �� 99 ֮����������
    }
    return data;
}
vector<int> generateSequentialData(int size) {
    vector<int> data(size);
    for (int i = 0; i < size; ++i) {
        data[i] = i + 1; // ���� 1 �� size �ĵ�������
    }
    return data;
}
vector<int> generateReverseSequentialData(int size) {
    vector<int> data(size);
    for (int i = 0; i < size; ++i) {
        data[i] = size - i; // ���ɴ� size �� 1 �ĵݼ�����
    }
    return data;
}





int main() {
    // �������ݼ�����ͬ��С�ͷֲ���
    vector<int> testData1 = generateLargeTestData(100);
    vector<int> testData2 = generateSequentialData(100);
    vector<int> testData3 = generateReverseSequentialData(100);

    // ���Բ�ͬ���ݼ�
    TestBinarySortTree(testData1);
    TestBinarySortTree(testData2);
    TestBinarySortTree(testData3);

    return 0;
}
