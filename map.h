#include "anime.h"
#include "redBlackTree.h"
#include "Node.h"
#include <iostream>
#pragma once
using namespace std;

class map {
    redBlackTree tree;
    int size;
public:
    begin();
    end();
    int getSize();
    bool isEmpty();
    void insert(int key, anime _anime);
    void erase(int key);
    find();
};

int map::getSize()
{
    return size;
}
bool map::isEmpty()
{
    if (size == 0)
    {
        return true;
    }
    return false;
}
void map::insert(int key, anime _anime)
{
    Node node;
    node.popularity = key;
    node.title = _anime.title;
    node.genres = _anime.genres;
    tree.insert(tree.root, node);
}
void map::erase(int key)
{
    tree.remove(tree.root, key);
}
