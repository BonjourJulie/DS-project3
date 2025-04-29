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
        return false; // 已存在，不插入
    }
    return key < p->data ? Insert(p->leftChild, key) : Insert(p->rightChild, key);
}

// 第一种删除算法（教材标准算法）
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
        if (p->leftChild == nullptr && p->rightChild == nullptr) { // 叶子节点
            delete p;
            p = nullptr;
        }
        else if (p->leftChild == nullptr) { // 只有右子树
            BinTreeNode<ElemType>* temp = p;
            p = p->rightChild;
            delete temp;
        }
        else if (p->rightChild == nullptr) { // 只有左子树
            BinTreeNode<ElemType>* temp = p;
            p = p->leftChild;
            delete temp;
        }
        else { // 左右子树都存在
            // 找到前驱节点（左子树中最大的）
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

// 第二种删除算法（移动左子树到后继的左子树）
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
        if (p->leftChild == nullptr && p->rightChild == nullptr) { // 叶子节点
            delete p;
            p = nullptr;
        }
        else if (p->leftChild == nullptr) { // 只有右子树
            BinTreeNode<ElemType>* temp = p;
            p = p->rightChild;
            delete temp;
        }
        else if (p->rightChild == nullptr) { // 只有左子树
            BinTreeNode<ElemType>* temp = p;
            p = p->leftChild;
            delete temp;
        }
        else { // 左右子树都存在
            // 找到后继节点（右子树中最小的）
            BinTreeNode<ElemType>* successor = p->rightChild;
            BinTreeNode<ElemType>* successorParent = p;
            while (successor->leftChild != nullptr) {
                successorParent = successor;
                successor = successor->leftChild;
            }
            successor->leftChild = p->leftChild;  // 将原左子树移动到后继的左子树
            if (successorParent != p) {    // 处理右子树
                successorParent->leftChild = successor->rightChild;
                successor->rightChild = p->rightChild;
            }
            // 用后继节点替换当前节点
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

// 显式实例化模板类（根据需要添加其他类型）
template class BinarySortTree<int>;
template class BinarySortTree<double>;

//=======================================测试函数===================================

#include "BinarySortTree.h"
#include <iostream>
#include <ctime>
#include <vector>
#include <chrono> // 高精度计时

using namespace std;

// 打印测试结果
template <class ElemType>
void TestBinarySortTree(const vector<ElemType>& arr) {
    cout << "开始测试数据集：" << endl;
    BinarySortTree<ElemType> tree(arr.data(), arr.size());

    // 测试中序遍历
    cout << "中序遍历树（插入后）: ";
    tree.InOrderTraverse();
    cout << endl;

    // 测试查找操作
    ElemType key = arr[arr.size() / 2];
    auto start = chrono::high_resolution_clock::now();
    auto result = tree.Search(key);
    auto end = chrono::high_resolution_clock::now();
    double time_used = chrono::duration<double>(end - start).count();
    if (result != nullptr) {
        cout << "查找元素 " << key << " 成功，时间: " << time_used << " 秒" << endl;
    }
    else {
        cout << "查找元素 " << key << " 失败。" << endl;
    }

    // 测试删除操作：使用标准删除算法
    start = chrono::high_resolution_clock::now();
    tree.DeleteStandard(key);
    end = chrono::high_resolution_clock::now();
    time_used = chrono::duration<double>(end - start).count();
    cout << "删除操作（标准算法）耗时: " << time_used << " 秒" << endl;

    // 测试删除操作：使用替代删除算法
    start = chrono::high_resolution_clock::now();
    tree.DeleteAlternative(key);
    end = chrono::high_resolution_clock::now();
    time_used = chrono::duration<double>(end - start).count();
    cout << "删除操作（替代算法）耗时: " << time_used << " 秒" << endl;

    // 性能测试：树的高度和平均查找长度
    cout << "树的高度: " << tree.Height() << endl;
    cout << "平均查找长度: " << tree.AverageSearchLength() << endl;
    cout << endl;
}


vector<int> generateLargeTestData(int size) {
    vector<int> data;
    srand(time(0));
    for (int i = 0; i < size; ++i) {
        data.push_back(rand() % 100); // 生成 0 到 99 之间的随机整数
    }
    return data;
}
vector<int> generateSequentialData(int size) {
    vector<int> data(size);
    for (int i = 0; i < size; ++i) {
        data[i] = i + 1; // 生成 1 到 size 的递增整数
    }
    return data;
}
vector<int> generateReverseSequentialData(int size) {
    vector<int> data(size);
    for (int i = 0; i < size; ++i) {
        data[i] = size - i; // 生成从 size 到 1 的递减整数
    }
    return data;
}





int main() {
    // 测试数据集（不同大小和分布）
    vector<int> testData1 = generateLargeTestData(100);
    vector<int> testData2 = generateSequentialData(100);
    vector<int> testData3 = generateReverseSequentialData(100);

    // 测试不同数据集
    TestBinarySortTree(testData1);
    TestBinarySortTree(testData2);
    TestBinarySortTree(testData3);

    return 0;
}
