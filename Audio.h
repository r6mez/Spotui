#ifndef AUDIOPLAYERPROJECT_AUDIO_H
#define AUDIOPLAYERPROJECT_AUDIO_H
#include <iostream>
#include <iomanip>
#include <windows.h>
using namespace std;


class Audio{
public:
    string name;
    string path;
    string type;
    int length; // Audio length in ms

    Audio() : name(""), path(""), type(""), length(0) {}

    Audio(string name, string path, string type) : name(name), path(path), type(type), length(0) {
        // Open the audio file and get its length and then close it
        string command = "open \"" + path + "\" type mpegvideo alias saturnAudio";
        mciSendString(command.c_str(), NULL, 0, NULL);
        char buffer[256];
        mciSendString("status saturnAudio length", buffer, sizeof(buffer), NULL);
        length = atoi(buffer);
        mciSendString("close saturnAudio", NULL, 0, NULL);
    }

    bool operator==(const Audio& other) const {
        return (this->name == other.name && this->path == other.path && this->type == other.type);
    }

    friend ostream& operator<<(ostream& os, const Audio& audio) {
        int smallWidth = 8, bigWidth = 20;
        os  << left << setw(bigWidth) << audio.name
                    << setw(bigWidth) << audio.type
                    << setw(smallWidth) << audio.getFormattedLength();
        return os;
    }

    string getFormattedLength() const {
        int minutes = length / 60000;
        int seconds = (length % 60000) / 1000;
        return (minutes< 10? "0" : "") + to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + to_string(seconds);
    }


    void playAudio() {
        mciSendString("close saturnAudio", NULL, 0, NULL);
        string command = "open \"" + path + "\" type mpegvideo alias saturnAudio";
        mciSendString(command.c_str(), NULL, 0, NULL);
        mciSendString("play saturnAudio repeat", NULL, 0, NULL);

    }

    void pauseAudio() {
        mciSendString("pause saturnAudio", NULL, 0, NULL);
    }

    void resumeAudio() {
        mciSendString("play saturnAudio", NULL, 0, NULL);
    }

    void stopAudio() {
        mciSendString("stop saturnAudio", NULL, 0, NULL);
        mciSendString("close saturnAudio", NULL, 0, NULL);
    }
};

#endif //AUDIOPLAYERPROJECT_AUDIO_H
