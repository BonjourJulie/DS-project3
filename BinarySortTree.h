#pragma once
#ifndef BINARYSORTTREE_H
#define BINARYSORTTREE_H

#include <iostream>
template <class ElemType>
struct BinTreeNode {
    ElemType data;
    BinTreeNode<ElemType>* leftChild;
    BinTreeNode<ElemType>* rightChild;

    BinTreeNode() : leftChild(nullptr), rightChild(nullptr) {}
    BinTreeNode(ElemType x, BinTreeNode<ElemType>* l = nullptr, BinTreeNode<ElemType>* r = nullptr)
        : data(x), leftChild(l), rightChild(r) {}
};

template <class ElemType>
class BinarySortTree {
private:
    BinTreeNode<ElemType>* root;
    void Destroy(BinTreeNode<ElemType>*& p);                                              //递归销毁子树
    void InOrderTraverse(BinTreeNode<ElemType>* p) const;                                 //递归中序遍历
    BinTreeNode<ElemType>* Search(BinTreeNode<ElemType>* p, const ElemType& key) const;   //递归查找
    bool Insert(BinTreeNode<ElemType>*& p, const ElemType& key);                          //递归插入
    void DeleteStandard(BinTreeNode<ElemType>*& p, const ElemType& key);
    void DeleteAlternative(BinTreeNode<ElemType>*& p, const ElemType& key);
    int Height(BinTreeNode<ElemType>* p) const;
    void CalculateASL(BinTreeNode<ElemType>* p, int level, int& total, int& nodes) const;

public:
    BinarySortTree() : root(nullptr) {}          //构造函数
    BinarySortTree(const ElemType* arr, int n);  //
    ~BinarySortTree() { Destroy(root); }         //析构函数

    bool IsEmpty() const { return root == nullptr; }           //判断树是否为空
    void InOrderTraverse() const { InOrderTraverse(root); }    //中序遍历
    BinTreeNode<ElemType>* Search(const ElemType& key) const;  //查找节点
    bool Insert(const ElemType& key);                          //插入新节点

    // 两种删除算法
    void DeleteStandard(const ElemType& key) { DeleteStandard(root, key); }        //书上第一种
    void DeleteAlternative(const ElemType& key) { DeleteAlternative(root, key); }  //另一种

    // 性能分析工具
    int Height() const { return Height(root); }   //获取树的高度
    double AverageSearchLength() const;           //计算平均查找长度（ASL）

};

#endif // BINARYSORTTREE_H