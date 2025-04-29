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
    void Destroy(BinTreeNode<ElemType>*& p);                                              //�ݹ���������
    void InOrderTraverse(BinTreeNode<ElemType>* p) const;                                 //�ݹ��������
    BinTreeNode<ElemType>* Search(BinTreeNode<ElemType>* p, const ElemType& key) const;   //�ݹ����
    bool Insert(BinTreeNode<ElemType>*& p, const ElemType& key);                          //�ݹ����
    void DeleteStandard(BinTreeNode<ElemType>*& p, const ElemType& key);
    void DeleteAlternative(BinTreeNode<ElemType>*& p, const ElemType& key);
    int Height(BinTreeNode<ElemType>* p) const;
    void CalculateASL(BinTreeNode<ElemType>* p, int level, int& total, int& nodes) const;

public:
    BinarySortTree() : root(nullptr) {}          //���캯��
    BinarySortTree(const ElemType* arr, int n);  //
    ~BinarySortTree() { Destroy(root); }         //��������

    bool IsEmpty() const { return root == nullptr; }           //�ж����Ƿ�Ϊ��
    void InOrderTraverse() const { InOrderTraverse(root); }    //�������
    BinTreeNode<ElemType>* Search(const ElemType& key) const;  //���ҽڵ�
    bool Insert(const ElemType& key);                          //�����½ڵ�

    // ����ɾ���㷨
    void DeleteStandard(const ElemType& key) { DeleteStandard(root, key); }        //���ϵ�һ��
    void DeleteAlternative(const ElemType& key) { DeleteAlternative(root, key); }  //��һ��

    // ���ܷ�������
    int Height() const { return Height(root); }   //��ȡ���ĸ߶�
    double AverageSearchLength() const;           //����ƽ�����ҳ��ȣ�ASL��

};

#endif // BINARYSORTTREE_H