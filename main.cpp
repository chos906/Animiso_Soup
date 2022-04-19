#include <iomanip>
#include <iostream>
#include <vector>
#include "aniMisoSetup.h"
#include <fstream>
using namespace std;

int main() {

    //    //HEAP DATA
        // 1) make object
    aniMisoSetup aniMiso;

    cout << std::fixed << setprecision(2);

    // 2) loads data
    //automatically builds anime heap, based on popularity rank
    aniMiso.loadFile("animes.csv");

    // 3) opening message and first menu options
    aniMiso.welcomeMessage();

    char option = '0';
    //cin >> option;

    while (option != '4') {

        cin >> option;

        switch (option) {
        case '1':
            //print top 10
            aniMiso.optionOne();
            break;
        case '2':
            // prompts user for more input for specified genre
            aniMiso.optionTwo();
            break;
        case '3': //DOES NOT WORK
            aniMiso.optionThree();
            break;
        default:
            cout << "oop, that's not an option. try again!\n\n";
            break;
        }
        aniMiso.printMenu();
    }

    cout << "thank you! hope you enjoyed your bowl of AniMiso Soup!";


    return 0;
}

//TEST to see if input data works - it does :D
//    for (int i = 0; i < 7; i++){
//        cout << animes[i].title << " ";
//        cout << animes[i].popularity << " ";
//        print genre vector
//        for(int k = 0; k < animes[i].genres.size(); k++)
//        {
//            cout << animes[i].genres[k] << " ";
//        }
//        cout << "\n----------- \n";
//    }

//TEST to see if objects are inserted correctly - YES
//    cout << minHeap.getTopPopular().title << endl;
//    cout << minHeap.getTopPopular().popularity << endl;
//    for(int k = 0; k < minHeap.getTopPopular().genres.size(); k++)
//        {
//            cout << minHeap.getTopPopular().genres[k] << " ";
//        }

//    TEST to see if extract min works - YES
//    anime removed = minHeap.extractMin();
//    cout << "removing: " << removed.title << endl;
//    cout << removed.popularity << endl;
//    for(int i = 0; i < removed.genres.size(); i ++)
//    {
//        cout << removed.genres[i] << " ";
//    }