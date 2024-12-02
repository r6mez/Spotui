#include "Menu.h"
#include "PlaylistsManager.h"
using namespace std;

int main() {
    PlaylistsManager pm;

    pm.loadFromFile();

    Menu playlistsManagerMenu(
            bind(&PlaylistsManager::displayUI, &pm),
            3,
            {"Enter Playlist", "Create Playlist", "Delete Playlist",},
            {bind(&PlaylistsManager::enterPlayList, &pm),
                            bind(&PlaylistsManager::createPlaylist, &pm),
                             bind(&PlaylistsManager::deletePlayList, &pm)}
    );

    playlistsManagerMenu.displayMenu();

    pm.saveToFile();
    return 0;
}


