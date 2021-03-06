#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError
{
};

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key &key, const Value &value, AVLNode<Key, Value> *parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    char getBalance() const;
    void setBalance(char balance);
    void updateBalance(char diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value> *getParent() const override;
    virtual AVLNode<Key, Value> *getLeft() const override;
    virtual AVLNode<Key, Value> *getRight() const override;

protected:
    char balance_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template <class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key &key, const Value &value, AVLNode<Key, Value> *parent) : Node<Key, Value>(key, value, parent), balance_(0)
{
}

/**
* A destructor which does nothing.
*/
template <class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{
}

/**
* A getter for the balance of a AVLNode.
*/
template <class Key, class Value>
char AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template <class Key, class Value>
void AVLNode<Key, Value>::setBalance(char balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template <class Key, class Value>
void AVLNode<Key, Value>::updateBalance(char diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template <class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value> *>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template <class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value> *>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template <class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value> *>(this->right_);
}

/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/

template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert(const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key &key);                              // TODO
protected:
    virtual void nodeSwap(AVLNode<Key, Value> *n1, AVLNode<Key, Value> *n2);

    // Add helper functions here
    void insertFix(AVLNode<Key, Value> *parent, AVLNode<Key, Value> *node);
    void removeFix(AVLNode<Key, Value> *node, int diff);

    void rotateLeft(AVLNode<Key, Value> *node);
    void rotateRight(AVLNode<Key, Value> *node);
    //void zigzig(AVLNode<Key, Value> *node, bool left);
    //void zigzag(AVLNode<Key, Value> *node, bool left);
};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template <class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &new_item)
{
    if (this->root_ == nullptr)
    {
        this->root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
    }
    else
    {
        Node<Key, Value> *node = this->internalFind(new_item.first);
        if (node != nullptr)
        {
            node->setValue(new_item.second);
        }
        else //node doesn't currently exist
        {
            node = this->root_; //Which we know exists
            bool done = false;
            while (!done)
            {
                if (new_item.first < node->getKey())
                {
                    if (node->getLeft() == nullptr)
                    {
                        done = true;
                        AVLNode<Key, Value> *castedNode = static_cast<AVLNode<Key, Value> *>(node);
                        AVLNode<Key, Value> *nodeToInsert = new AVLNode<Key, Value>(new_item.first, new_item.second, castedNode);
                        castedNode->setLeft(nodeToInsert);

                        if (abs(castedNode->getBalance()) == 1)
                        {
                            castedNode->setBalance(0);
                        }
                        else
                        {
                            castedNode->updateBalance(-1);
                            insertFix(castedNode, nodeToInsert);
                        }
                    }
                    else
                    {
                        node = node->getLeft();
                    }
                }
                else
                {
                    if (node->getRight() == nullptr)
                    {
                        done = true;
                        AVLNode<Key, Value> *castedNode = static_cast<AVLNode<Key, Value> *>(node);
                        AVLNode<Key, Value> *nodeToInsert = new AVLNode<Key, Value>(new_item.first, new_item.second, castedNode);
                        castedNode->setRight(nodeToInsert);
                        if (abs(castedNode->getBalance()) == 1)
                        {
                            castedNode->setBalance(0);
                        }
                        else
                        {
                            castedNode->updateBalance(1);
                            insertFix(castedNode, nodeToInsert);
                        }
                    }
                    else
                    {
                        node = node->getRight();
                    }
                }
            }
        }
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template <class Key, class Value>
void AVLTree<Key, Value>::remove(const Key &key)
{
    Node<Key, Value> *node = this->internalFind(key);
    AVLNode<Key, Value> *castedNode = static_cast<AVLNode<Key, Value> *>(node);
    if (node != nullptr)
    {
        int numChildren = 0;
        AVLNode<Key, Value> *right = castedNode->getRight();
        AVLNode<Key, Value> *left = castedNode->getLeft();
        AVLNode<Key, Value> *parent = castedNode->getParent();
        if (right != nullptr)
        {
            numChildren++;
        }
        if (left != nullptr)
        {
            numChildren++;
        }
        if (numChildren == 0)
        { //leaf node
            if (parent != nullptr)
            {
                if (parent->getRight() == node)
                {
                    parent->setRight(nullptr);
                }
                else
                {
                    parent->setLeft(nullptr);
                }
                //node->setParent(nullptr);
            }
            else
            {
                this->root_ = nullptr;
            }
        }
        else if (numChildren == 1)
        {
            Node<Key, Value> *childNode;
            if (left != nullptr)
            {
                childNode = left;
            }
            else
            {
                childNode = right;
            }
            if (parent != nullptr)
            {
                if (parent->getRight() == node)
                {
                    parent->setRight(childNode);
                }
                else
                {
                    parent->setLeft(childNode);
                }
                childNode->setParent(parent);
            }
            else
            {
                this->root_ = childNode;
                childNode->setParent(nullptr);
            }
        }
        else if (numChildren == 2)
        {
            nodeSwap(castedNode, static_cast<AVLNode<Key, Value> *>(this->predecessor(castedNode)));
            right = castedNode->getRight();
            left = castedNode->getLeft();
            parent = castedNode->getParent();
            Node<Key, Value> *childNode = nullptr;
            if (left != nullptr)
            {
                childNode = left;
            }
            else if (right != nullptr)
            {
                childNode = right;
            }
            if (childNode != nullptr)
            {
                if (parent->getRight() == node)
                {
                    parent->setRight(childNode);
                }
                else
                {
                    parent->setLeft(childNode);
                }
                childNode->setParent(parent);
            }

            else if (parent != nullptr)
            {
                if (parent->getRight() == node)
                {
                    parent->setRight(nullptr);
                }
                else
                {
                    parent->setLeft(nullptr);
                }
            }
        }
        if (node->getParent() != nullptr)
        {
            if (node->getParent()->getLeft() == node)
            {
                //removeFix(node, 1);
            }
            else
            {
                //removeFix(node, -1);
            }
        }
        delete node;
    }
}

template <class Key, class Value>
void AVLTree<Key, Value>::nodeSwap(AVLNode<Key, Value> *n1, AVLNode<Key, Value> *n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    char tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}

template <class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value> *parent, AVLNode<Key, Value> *node)
{
    if (parent == nullptr || parent->getParent() == nullptr)
    {
        return;
    }
    AVLNode<Key, Value> *gp = parent->getParent();
    if (gp->getRight() == parent)
    {
        gp->updateBalance(1);
    }
    else
    {
        gp->updateBalance(-1);
    }
    if (gp->getBalance() == 0)
    {
        return;
    }
    else if (std::abs(gp->getBalance()) == 1)
    {
        insertFix(gp, parent);
    }
    else
    {
        if (gp->getBalance() == -2)
        {
            //Zig zig
            if (parent->getBalance() == -1)
            {
                rotateRight(gp);
                gp->setBalance(0);
                parent->setBalance(0);
            }
            //zig zag
            else
            {
                rotateLeft(parent);
                rotateRight(gp);
                if (node->getBalance() == -1)
                {
                    parent->setBalance(0);
                    gp->setBalance(1);
                    node->setBalance(0);
                }
                else if (node->getBalance() == 0)
                {
                    parent->setBalance(0);
                    gp->setBalance(0);
                }
                else if (node->getBalance() == 1)
                {
                    parent->setBalance(-1);
                    gp->setBalance(0);
                    node->setBalance(0);
                }
            }
        }
        else
        {
            //Zig zig
            if (parent->getBalance() == 1)
            {
                rotateLeft(gp);
                gp->setBalance(0);
                parent->setBalance(0);
            }
            //zig zag
            else
            {
                rotateRight(parent);
                rotateLeft(gp);
                if (node->getBalance() == 1)
                {
                    parent->setBalance(0);
                    gp->setBalance(-1);
                    node->setBalance(0);
                }
                else if (node->getBalance() == 0)
                {
                    parent->setBalance(0);
                    gp->setBalance(0);
                }
                else if (node->getBalance() == -1)
                {
                    parent->setBalance(1);
                    gp->setBalance(0);
                    node->setBalance(0);
                }
            }
        }
    }
}

template <class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value> *n, int diff)
{
    AVLNode<Key, Value> *p = n->getParent();
    int ndiff = 0;
    if (p != nullptr)
    {
        if (n->getParent()->getLeft() == n)
        {
            ndiff = 1;
        }
        else
        {
            ndiff = -1;
        }
    }
    if (n->getBalance() + diff == -2)
    {
        AVLNode<Key, Value> *c = n->getLeft();
        if (c->getBalance() == -1)
        {
            rotateRight(n);
            c->setBalance(0);
            n->setBalance(0);
            removeFix(p, ndiff);
        }
        else if (c->getBalance() == 0)
        {
            rotateRight(n);
            n->setBalance(-1);
            c->setBalance(1);
        }
        else if (c->getBalance() == 1)
        {
            AVLNode<Key, Value> *g = c->getRight();
            rotateLeft(c);
            rotateRight(n);
            if (g->getBalance() == 1)
            {
                n->setBalance(0);
                c->setBalance(-1);
                g->setBalance(0);
            }
            else if (g->getBalance() == 0)
            {
                n->setBalance(0);
                c->setBalance(0);
                g->setBalance(0);
            }
            else
            {
                n->setBalance(1);
                c->setBalance(0);
                g->setBalance(0);
            }
            removeFix(p, ndiff);
        }
    }
    else if (n->getBalance() + diff = -1)
    {
        n->setBalance(-1);
    }
    else if (n->getBalance() + diff == 2)
    {
        AVLNode<Key, Value> *c = n->getRight();
        if (c->getBalance() == -1)
        {
            rotateLeft(n);
            c->setBalance(0);
            n->setBalance(0);
            removeFix(p, ndiff);
        }
        else if (c->getBalance() == 0)
        {
            rotateLeft(n);
            n->setBalance(1);
            c->setBalance(-1);
        }
        else if (c->getBalance() == 1)
        {
            AVLNode<Key, Value> *g = c->getLeft();
            rotateRight(c);
            rotateLeft(n);
            if (g->getBalance() == 1)
            {
                n->setBalance(0);
                c->setBalance(1);
                g->setBalance(0);
            }
            else if (g->getBalance() == 0)
            {
                n->setBalance(0);
                c->setBalance(0);
                g->setBalance(0);
            }
            else
            {
                n->setBalance(-1);
                c->setBalance(0);
                g->setBalance(0);
            }
            removeFix(p, ndiff);
        }
    }
    else if (n->getBalance() + diff == 1)
    {
        n->setBalance(1);
    }
    else if (n->getBalance() + diff == 0)
    {
        n->setBalance(0);
        removeFix(p, ndiff);
    }
}

template <class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value> *node)
{
    AVLNode<Key, Value> *gp = node->getParent();
    AVLNode<Key, Value> *leftChild = node->getLeft();
    if (node == this->root_)
    {
        this->root_ = leftChild;
    }
    node->setLeft(leftChild->getRight());
    if (node->getLeft() != nullptr)
    {
        node->getLeft()->setParent(node);
    }
    leftChild->setRight(node);
    leftChild->setParent(gp);
    node->setParent(leftChild);
    if (gp != nullptr)
    {
        if (gp->getLeft() == node)
        {
            gp->setLeft(leftChild);
        }
        else
        {
            gp->setRight(leftChild);
        }
    }
}

template <class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value> *node)
{
    AVLNode<Key, Value> *gp = node->getParent();
    AVLNode<Key, Value> *rightChild = node->getRight();
    if (node == this->root_)
    {
        this->root_ = rightChild;
    }
    node->setRight(rightChild->getLeft());
    if (node->getRight() != nullptr)
    {
        node->getRight()->setParent(node);
    }
    rightChild->setLeft(node);
    rightChild->setParent(gp);
    node->setParent(rightChild);
    if (gp != nullptr)
    {
        if (gp->getRight() == node)
        {
            gp->setRight(rightChild);
        }
        else
        {
            gp->setLeft(rightChild);
        }
    }
}

#endif
