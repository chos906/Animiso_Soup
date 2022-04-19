#pragma once
#include <iostream>
#include "Node.h"
#include "anime.h"
#include "redBlackTree.h"
#pragma once

class redBlackTree {

public:
    Node* root;
    redBlackTree() // constructor
    {
        root = nullptr;
    }
    int findHeight(Node* root); // function to find the height

    void insert(int popularity, anime animeObj);

    void inorder();

private:

    Node* insertHelper(Node* root, Node* node);
    void insertionRepair(Node* root, Node* node);

    void inorderHelper(Node* root);

    Node* rotateLeft(Node* node) // left rotation
    {
        Node* newRoot = node->right;
        newRoot->height--;
        node->right = newRoot->left;
        node->height++;
        newRoot->left = node;
        newRoot->right->height--;
        return newRoot;
    }
    Node* rotateRight(Node* node) // right rotation
    {
        Node* newRoot = node->left;
        newRoot->height--;
        node->left = newRoot->right;
        node->height++;
        newRoot->right = node;
        newRoot->left->height--;
        return newRoot;
    }
    Node* rotateLeftRight(Node* node) // left right rotation
    {
        node->left = rotateLeft(node->left);
        node = rotateRight(node);
        return node;
    }
    Node* rotateRightLeft(Node* node) // right left rotation
    {
        node->right = rotateRight(node->right);
        node = rotateLeft(node);
        return node;
    }
};

int redBlackTree::findHeight(Node* root)
{
    int tempLeft = 0;
    int tempRight = 0;
    if (root == nullptr)
    {
        return 0;
    }
    tempLeft = findHeight(root->left);
    tempRight = findHeight(root->right);
    if (tempLeft >= tempRight)
    {
        return tempLeft + 1;
    }
    if (tempRight >= tempLeft)
    {
        return tempRight + 1;
    }
    return 0;
}

Node* redBlackTree::insertHelper(Node* root, Node* node)
{
    if (root == nullptr) // if empty tree, sets node to root
    {
        root = node;
        root->parent = nullptr;
        root->black = true; //root is always black
    }
    else if (node->popularity == root->popularity) // if ID is already in tree, just does not insert
    {
        return root;
    }
    else if (node->popularity < root->popularity) // if ID is less than root, recursively calls the left node
    {
        node->height++;
        root->left = insertHelper(root->left, node);
        root->left->parent = root;
    }
    else if (node->popularity > root->popularity) // if ID is less than root, recursively calls the right node
    {
        node->height++;
        root->right = insertHelper(root->right, node);
        root->right->parent = root;
    }

    return root;
}

void redBlackTree::insertionRepair(Node* root, Node* node)
{
    //red - 1 and black -0
    Node* parent_ = nullptr;
    Node* grand = nullptr;

    while ((node != root) && (node->black == false) && (node->parent->black == false))
    {
        parent_ = node->parent;
        grand = node->parent->parent;

        //if parent of node is LEFT child
        //of grandparent of node
        if (parent_ = grand->left)
        {
            Node* aunt = grand->right;
            //if uncle of node is also red
            //just have to RECOLOR
            if (aunt != nullptr && aunt->black == false)
            {
                grand->black = false;
                parent_->black = true;
                aunt->black = true;
                node = grand;
            }
            else
            {
                //if node is right child of its parent
                //LEFT ROTATE
                if (node == parent_->right)
                {
                    rotateLeft(root);
                    node = parent_;
                    parent_ = node->parent;

                }
                //node is LEFT child of parent
                //RIGHT ROTATE
                rotateRight(root);
                swap(parent_->black, grand->black);
                node = parent_;
            }
        }
        //if parent of node is RIGHT child
        //of grandparent of node
        else
        {
            Node* aunt = grand->left;

            //if uncle of node is also red
            //only recoloring required
            if ((aunt != nullptr) && (aunt->black == false))
            {
                grand->black = false;
                parent_->black = true;
                aunt->black = true;
                node = grand;
            }
            else
            {
                //if node is LEFT child of parent
                //ROTATE RIGHT
                if (node = parent_->left)
                {
                    rotateRight(root);
                    node = parent_;
                    parent_ = node->parent;
                }
                //if node is RIGHT child of parent
                //LEFT rotate
                rotateLeft(root);
                swap(parent_->black, grand->black);
                node = parent_;
            }

        }
    }
    root->black = true;

}

void redBlackTree::insert(int popularity, anime animeObj) {

    Node* anime = new Node(popularity, animeObj); //make new node

    root = insertHelper(root, anime); //insert node into red black tree

    insertionRepair(root, anime); //fix insertion based on red black rules

}

//TODO TEST
void redBlackTree::inorderHelper(Node* root) {
    if (root == NULL)
    {
        return;
    }

    inorderHelper(root->left);
    cout << root->popularity << " " << root->title << endl;
    inorderHelper(root->right);
}

void redBlackTree::inorder() {
    inorderHelper(root);
}