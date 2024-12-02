#ifndef AUDIOPLAYERPROJECT_MENU_H
#define AUDIOPLAYERPROJECT_MENU_H
#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include <conio.h>
#include "Control.cpp"
#define byte rpcndr_byte
using namespace std;

class Menu{
    function<void()> displayHeader;
    int numberOfOptions;
    vector<string> optionsNames;
    vector<function<void()>> optionsFunctions;

    int selected = 1;

    void displayOptions(){
        cout << "Use arrows (up, down) to move, press S to select.\n";
        for (int i = 1; i <= numberOfOptions; ++i) {
            cout << (selected == i ? ORANGE + "-> " : "   ") << optionsNames[i - 1] << "\n" + RESET;
        }
    }

    void onPress(){
        int pressed = selected - 1;
        selected = -1; // to unselect while typing
        displayAll();
        cout << ORANGE;
        optionsFunctions[pressed]();
        selected = pressed + 1;
    }

    void displayAll(){
        clearScreen();
        displayHeader();
        displayOptions();
    }

public:
    Menu(function<void()> displayHeader, int numberOfOptions, vector<string> optionsNames, vector<function<void()>> optionsFunctions)
            : displayHeader(displayHeader), numberOfOptions(numberOfOptions), optionsNames(optionsNames), optionsFunctions(optionsFunctions) {}


    void displayMenu(){
        while(true){
            displayAll();

            int key = getch();
            if (key == sKey) { // Press option
                onPress();
                continue;
            }

            if (key == arrowInitial) {
                key = getch();

                if (key == arrowUp) { // Up arrow
                    if(selected > 1) selected--;
                } else if (key == arrowDown) {
                    if(selected < numberOfOptions) selected++;
                }

                continue;
            }

            if(key == escapeKey){
                return;
            }
        }
    }
};

#endif //AUDIOPLAYERPROJECT_MENU_H
