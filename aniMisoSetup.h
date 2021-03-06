#include <iomanip>
#include <iostream>
#include <vector>
#include "minHeap.h"
//#include "redBlackTree.h"
#include <fstream>
#pragma once
using namespace std;

//class solely to print out text based on user input
//and read in file
class aniMisoSetup
{
private:

    MinHeap minHeap;
    vector<anime> ogAnime; //vector to hold all the OG anime from dataset (unsorted)

public:

    //    vector<anime> ogAnime; //vector to hold all the OG anime from dataset (unsorted)

    void loadFile(string fileInput);
    void buildHeap(vector<anime> ogAnime);
    void welcomeMessage();
    void printMenu();

    //print statements based on option user chose
    void optionOne();
    void optionTwo();
    void optionThree();

    void treeTest();

};

void aniMisoSetup::loadFile(string fileInput) {

    //iterates through file ROWS
    //only using certain data in this project
    ifstream animeData(fileInput);
    string title;
    string popularity;
    string genresString; //using this will be used to create edges for graph
    string indivGenre;

    string ignore; //placeholder for skipped spaces when taking in input

    string firstLine;
    getline(animeData, firstLine); //ignore first line, gives variable names

    while (!animeData.eof()) //Not @ end of file
    {
        //defined variables
        getline(animeData, popularity, ',');
        //deliminator is [, since title can have commas... genres are seperated by []
        getline(animeData, title, '[');
        //no deliminator, since last one
        getline(animeData, genresString);

        //convert genre string into a vector:

        //deliminators that separate words in input vector
        int stringCount = 0;
        int openQuote = 0; //index of first quotation
        int closedQuote = 0; //index of last quotation
        int delimDistance = 0;
        vector<string> genreVector; //make new vector for each anime

        //repeat until size - 3 bc end of string is ']
        while (stringCount < genresString.size() - 3)
        {
            //each genre is between ' '

            //first genre read in
            if (stringCount == 0)
            {
                //find first quote
                openQuote = genresString.find('\'');
                //find next quote after ^
                closedQuote = genresString.find('\'', openQuote + 1);
            }
            else //all genres in between first and last one
            {
                //find first quote after latest closing quote
                openQuote = genresString.find('\'', closedQuote + 1);
                //find next quote after ^
                closedQuote = genresString.find('\'', openQuote + 1);
            }

            //distance between two quotes = length of genre string
            delimDistance = closedQuote - openQuote - 1;
            indivGenre = genresString.substr(openQuote + 1, delimDistance);
            genreVector.push_back(indivGenre);

            stringCount = closedQuote;
        }

        //delete last 2 char in title, which is ",""
        //since the deliminator was [
        title = title.substr(0, title.size() - 2);

        //anime obj
        anime anime(title, popularity, genreVector); //taking separate variables and now putting them together into the animeFile obj
        //make a vector of anime objects
        //then construct data structures with information stored (popularity, title, and rank)
        ogAnime.push_back(anime);

    }

    buildHeap(ogAnime);

    animeData.close();
}

void aniMisoSetup::buildHeap(vector<anime> ogAnime) {
    //insert all anime objects into heap
    for (int i = 0; i < ogAnime.size(); i++)
    {
        minHeap.insert(ogAnime[i]);
    }
}

void aniMisoSetup::welcomeMessage() {
    cout << "man... i really want some high qualty anime\n";
    cout << "oh my god - high quality anime!\n";
    cout << "\n";
    cout << "~ * ~ welcome to AniMiso Soup! ~ * ~\n\n";

    //prompt options to choose from
    cout << "choose an option to start your AniMiso journey: \n";
    cout << "   1 - print top 10 anime \n";
    cout << "   2 - print top 5 anime in certain genre \n";
    cout << "   3 - search anime by name and get other recommendations \n";
    cout << "   4 - i am done with my AniMiso journey :) \n\n";
}

void aniMisoSetup::optionOne() {
    //print top 10 anime
    cout << "\n~ * ~ TOP 10 ANIME ~ * ~ \n\n";
    minHeap.printTopTen();
}

void aniMisoSetup::optionTwo() {
    //print top 5 anime in certain genre

    cout << "what genre are you interested in?\n";
    cout << "1 - action     2 - comedy     3 - drama      4 - romance\n";
    int genre = 0;
    cin >> genre;
    string chosenGenre;

    bool genreSuccess = true;

    switch (genre) {
    case 1:
        chosenGenre = "ACTION";
        break;
    case 2:
        chosenGenre = "COMEDY";
        break;
    case 3:
        chosenGenre = "DRAMA";
        break;
    case 4:
        chosenGenre = "ROMANCE";
        break;
    default:
        genreSuccess = false;
        cout << "oop, that's not an option. restarting home page...\n\n";
    }

    if (genreSuccess)
    {
        vector<string> topFiveGenre = minHeap.getTopWithinGenre(genre);

        cout << "\n~ * ~ TOP 5 " << chosenGenre << " ANIME ~ * ~ \n\n";

        for (int i = 0; i < topFiveGenre.size(); i++)
        {
            cout << i + 1 << " - " << topFiveGenre[i] << "\n";
        }
    }

    cout << "\n";

}

void aniMisoSetup::optionThree() {
    cout << "what anime title are you looking for?\n\n";
    string title;
    cin >> title;
    minHeap.searchByName(title);
}

void aniMisoSetup::printMenu() {
    cout << "choose an option to continue your AniMiso journey: \n";
    cout << "   1 - print top 10 anime \n";
    cout << "   2 - print top 5 anime in certain genre \n";
    cout << "   3 - search anime by name and get other recommendations \n";
    cout << "   4 - i am done with my AniMiso journey :) \n\n";
}
//
//void aniMisoSetup::treeTest() {
//
//    redBlackTree tree;
//
//    for (int i = 0; i < 5; i++){
//        tree.insert(ogAnime[i].popularity, ogAnime[i]);
//    }
//
//    cout << "Inorder Traversal of Created Tree\n";
//    tree.inorder();
//}