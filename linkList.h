#pragma once
#include <iostream>

using namespace std;

template <typename N>
class linkNode
{
public:
    linkNode *previousNode = nullptr;
    N data;
    linkNode *nextNode = nullptr;
    linkNode(N inputData)
    {
        data = inputData;
    }
    linkNode(linkNode *preNode, N inputData)
    {
        previousNode = preNode;
        data = inputData;
    }

    void add(N inputData)
    {
        if (nextNode == nullptr)
        {
            linkNode *newNode = new linkNode(this, inputData);
            nextNode = newNode;
            return;
        }
        else
        {
            nextNode->add(inputData);
        }
    }
    bool remove(N deleteData)
    {
        if (nextNode->data == deleteData)
        {
            linkNode *tempNode = nextNode->nextNode;
            delete nextNode;
            nextNode = tempNode;
            return 1;
        }
        else
        {
            if (nextNode == nullptr)
            {
                return 0;
            }
            else
            {
                nextNode->remove(deleteData);
            }
        }
    }
    void destroyNode()
    {
        if (nextNode != nullptr)
        {
            nextNode->destroyNode();
        }
        if (nextNode == nullptr)
        {
            if (previousNode == nullptr)
            {
                return;
            }
            linkNode *parentNode = previousNode;
            delete parentNode->nextNode;
            parentNode->nextNode = nullptr;
            return;
        }
    }
    linkNode *indexNode(int pos, int target)
    {
        if (pos == target)
        {
            return this;
        }
        nextNode->indexNode(pos + 1, target);
    }
};

template <typename T>
class LinkList
{
    typedef linkNode<T> NODE;

public:
    void push(T pushData)
    {
        if (beginNode == nullptr)
        {
            NODE *newNode = new NODE(pushData);
            beginNode = newNode;
        }
        else
        {
            beginNode->add(pushData);
        }
        size++;
    }
    void pop(T popData)
    {
        if (beginNode == nullptr)
        {
            return;
        }
        else
        {
            if (beginNode->remove(popData))
            {
                size--;
            }
        }
    }
    NODE *operator[](size_t pos)
    {
        if (pos >= size)
        {
            return nullptr;
        }
        return beginNode->indexNode(0, pos);
    }
    ~LinkList()
    {
        if (beginNode != nullptr)
        {
            beginNode->destroyNode();
            delete beginNode;
            beginNode = nullptr;
        }
    }

private:
    NODE *beginNode = nullptr;
    size_t size = 0;
};