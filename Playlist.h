#ifndef AUDIOPLAYERPROJECT_PLAYLIST_H
#define AUDIOPLAYERPROJECT_PLAYLIST_H
#include <iostream>
#include <iomanip>
#include "DoublyLL.h"
#include "Audio.h"
using namespace std;

class Playlist{
public:
    string playlistName;
    Node<Audio> *current;
    DoublyLL<Audio> list;

private:
    void longLine(){
        cout << "------------------------------------------------------------\n";
    }

    void displayHeader(){
        longLine();
        cout << "  Playlist: " << playlistName << "\n";
        longLine();
        int smallWidth = 8, bigWidth = 20;
        cout << left  << "| " << setw(smallWidth) << "ID"
                              << setw(bigWidth) << "Name"
                              << setw(bigWidth) << "Type"
                              << setw(smallWidth) << "Length"
                              << " |\n";
        longLine();
    }

    void displaySounds(){
        if(list.getSize() == 0) cout << "Empty!\n";
        else list.traverse();

        longLine();
    }

    void smallLine(){
        cout << "+--------------------------+\n";
    }

    void displayPlayerUI(int &selected, int &isPlaying){
        string playText = isPlaying? " Pause" : " Play";

        int smallWidth = 8, midumWidth = smallWidth*2, fullWdith = smallWidth*3;
        // Display header and buttons
        smallLine();
        cout << "| " << setw(fullWdith) << " " << " |\n";
        cout << "| " << setw(midumWidth) << left << current->data.name
              << setw(smallWidth) << right << current->data.getFormattedLength() << " |\n";

        cout << "| " << setw(fullWdith) << " " << " |\n";

        // Display buttons with spacing
        cout << "| " << formatButton("<-", smallWidth, selected == 1)
             << formatButton(playText, smallWidth, selected == 2)
             << formatButton("->", smallWidth, selected == 3, false) << " |"<< "\n";

        cout << "| " << setw(fullWdith) << " " << " |\n";
        smallLine();
    }

public:
    Playlist() : playlistName(""), current(list.getHead()) {};

    Playlist(string newPlayListName) : playlistName(newPlayListName), current(list.getHead()) {};

    friend ostream& operator<<(ostream& os, const Playlist& playlist) {
        int smallWidth = 8, bigWidth = 20;
        os << left << setw(bigWidth) << playlist.playlistName << setw(smallWidth) << playlist.list.getSize();
        return os;
    }

    void displayUI(){
        displayHeader();
        displaySounds();
    }

    void addAudioFromObj(Audio newAudioObj){
        list.insert_at_end(newAudioObj);
    }

    void addAudio(){
        string audioName, audioPath, audioType;
        cout << "Enter audio name: ";
        getline(cin, audioName);
        cout << "Enter audio path: ";
        getline(cin, audioPath);
        cout << "Enter audio type: ";
        getline(cin, audioType);

        Audio newAudio(audioName, audioPath, audioType);

        list.insert_at_end(newAudio);

        cout << audioName + " Is Added to " + playlistName + " Succefully!\n";
        SleepForSecond();
    }

    void deleteAudio(){
        cout << "Enter ID of the audio to delete: ";
        int index; cin >> index; cin.ignore();

        list.delete_at(index);
    }

    void startPlaylist(){
        current = list.getHead();
        current->data.playAudio();

        int selected = 1;
        int isPlaying = 1;

        while(true){
            // clear
            clearScreen();

            displayPlayerUI(selected, isPlaying);

            int key = getch();
            if (key == sKey) { // Press option
                if(selected == 1){
                    isPlaying = true;
                    playPreviousAudio();
                } else if (selected == 2){
                    if(isPlaying){
                        pauseAudio();
                    } else {
                        resumeAudio();
                    }
                    isPlaying = !isPlaying;
                } else {
                    isPlaying = true;
                    playNextAudio();
                }
                continue;
            }

            if (key == arrowInitial) {
                key = getch();

                if (key == arrowLeft) { // Up arrow
                    if(selected > 1) selected--;
                } else if (key == arrowRight) {
                    if(selected < 3) selected++;
                }

                continue;
            }

            if(key == escapeKey){
                stopAudio();
                return;
            }
        }
    }

    void shufflePlaylist(){
        list.shuffle();
    }

    void playNextAudio(){
        if(current->next == nullptr){
            cout << "Reached the end!\n";
            SleepForSecond();
            return;
        }
        current = current->next;
        current->data.playAudio();
    }

    void playPreviousAudio(){
        if(current->prev == nullptr){
            cout << "This is the first song!\n";
            SleepForSecond();
            return;
        }

        current = current->prev;
        current->data.playAudio();
    }

    void pauseAudio(){
        current->data.pauseAudio();
    }

    void resumeAudio(){
        current->data.resumeAudio();
    }

    void stopAudio(){
        current->data.stopAudio();
    }


};
#endif //AUDIOPLAYERPROJECT_PLAYLIST_H
