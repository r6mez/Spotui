#include <thread>
#include <chrono>
#include <algorithm>
using namespace std;

const int sKey = 115;
const int arrowInitial = 224;
const int arrowUp = 72;
const int arrowDown = 80;
const int arrowLeft = 75;
const int arrowRight = 77;
const int escapeKey = 27;
const string ORANGE = "\033[38;5;214m";    // Orange color
const string RESET = "\033[0m";

void SleepForSecond(){
    this_thread::sleep_for(chrono::milliseconds(1000));
}

void clearScreen() {
    cout << "\033[2J\033[H"; // Clear screen and move cursor to top-left
    cout.flush(); // Force the output to be flushed
    cout << RESET;
}

string formatButton(string buttonText, int width, bool isSelected, bool left = true) {
    string result = buttonText;
    if (isSelected) {
        result = ORANGE + buttonText + RESET;
    }

    if (buttonText.size() < width) {
        if(left) result += string(max(0, width - int(buttonText.size())), ' ');
        else result = string(max(0, width - int(buttonText.size())), ' ') + result;
    }
    return result;
}