#ifndef AUDIOPLAYERPROJECT_PLAYLISTSMANAGER_H
#define AUDIOPLAYERPROJECT_PLAYLISTSMANAGER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include "DoublyLL.h"
#include "Audio.h"
#include "Playlist.h"

class PlaylistsManager{
    DoublyLL<Playlist> playlists;


    static void displayLine(){
        cout << "----------------------------------------\n";
    }

    void displayHeader(){
        displayLine();
        cout << "\t   Ramez's PlayLists\n";
        displayLine();
        int smallWidth = 8, bigWidth = 20;
        cout << left << "| " << setw(smallWidth) << "ID" << setw(bigWidth) << "Name" << setw(smallWidth) << "Items" << " |\n";
        displayLine();
    }

    void displayPlaylists(){
        playlists.traverse();
    }

public:

    void displayUI() {
        displayHeader();
        displayPlaylists();
        displayLine();
    }

    void createPlaylist(){
        cout << "Enter Playlist Name: ";

        string playlistName;
        getline(cin , playlistName);

        Playlist newPlaylist(playlistName);
        playlists.insert_at_end(newPlaylist);
    }

    void deletePlayList(){
        cout << "Enter ID of playlist to delete: ";
        int index; cin >> index; cin.ignore();

        playlists.delete_at(index);
    }

    void enterPlayList(){
        cout << "Enter ID of Playlist to Enter: ";
        int index; cin >> index; cin.ignore();

        if (index > playlists.getSize() || index < 0) {
            cout << "Invaild Index! Out of Range\n";
            SleepForSecond();
            return;
        }

        Playlist *choosen = &playlists.getElement(index);

        Menu playlistMenu(
                bind(&Playlist::displayUI, choosen),
                4,
                {"Start Playing", "Add Audio", "Delete Audio", "Shuffle Playlist"},
                {bind(&Playlist::startPlaylist, choosen),
                                bind(&Playlist::addAudio, choosen),
                                  bind(&Playlist::deleteAudio, choosen),
                                   bind(&Playlist::shufflePlaylist, choosen),}
                );

        playlistMenu.displayMenu();
    }

    const string saveFileName = "SoundPlayerDatabase.txt";

    void saveToFile() {
        ofstream outFile(saveFileName);
        if (!outFile) {
            cout << "Error opening file for writing.\n";
            return;
        }

        int playlistCount = playlists.getSize();
        outFile << playlistCount << "\n";

        Node<Playlist>* temp = playlists.getHead();
        while (temp != nullptr) {
            outFile << temp->data.playlistName << "," << temp->data.list.getSize() << "\n";

            Node<Audio>* audioNode = temp->data.list.getHead();
            while (audioNode != nullptr) {
                outFile << audioNode->data.name << ","
                        << audioNode->data.path << ","
                        << audioNode->data.type << "\n";
                audioNode = audioNode->next;
            }

            temp = temp->next;
        }

        outFile.close();
        cout << "Playlists saved successfully.\n";
        SleepForSecond();
    }

    void loadFromFile() {
        ifstream inFile(saveFileName);
        if (!inFile) {
            cout << "Error opening file for reading.\n";
            return;
        }

        int playlistCount;
        string line;

        if (!(inFile >> playlistCount)) {
            cout << "Error reading playlist count.\n";
            inFile.close();
            return;
        }
        // Clear the leftover newline
        inFile.ignore();

        for (int i = 0; i < playlistCount; ++i) {
            if (!getline(inFile, line)) {
                cout << "Error reading playlist details.\n";
                break;
            }

            stringstream ss(line);
            string playlistName;
            int audioCount;

            if (!getline(ss, playlistName, ',') || !(ss >> audioCount)) {
                cout << "Malformed playlist data.\n";
                continue;
            }

            Playlist newPlaylist(playlistName);

            for (int j = 0; j < audioCount; ++j) {
                if (!getline(inFile, line)) {
                    cout << "Error reading audio details.\n";
                    break;
                }

                stringstream audioStream(line);
                string audioName, audioPath, audioType;

                if (!getline(audioStream, audioName, ',') ||
                    !getline(audioStream, audioPath, ',') ||
                    !getline(audioStream, audioType)) {
                    cout << "Malformed audio data.\n";
                    continue;
                }

                Audio newAudio(audioName, audioPath, audioType);
                newPlaylist.addAudioFromObj(newAudio);
            }

            playlists.insert_at_end(newPlaylist);
        }

        inFile.close();
        cout << "Playlists loaded successfully.\n";
        SleepForSecond();
    }

};


#endif //AUDIOPLAYERPROJECT_PLAYLISTSMANAGER_H
