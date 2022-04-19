
#include "anime.h"
#pragma once
struct Node {

    int popularity; //key
    string title;
    vector<string> genres;
    int height = 0;

    anime animeObj;

    //see if node is red or black
    //black = false, means its red
    bool black = false;
    Node* left, * right, * parent;

    Node(int Inpopularity, anime animeObject) // constructor
    {
        this->popularity = Inpopularity;
        this->black = false;

        animeObj = animeObject;

        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }
};

