cmake_minimum_required(VERSION 3.27)
project(AudioPlayerProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(AudioPlayerProject main.cpp DoublyLL.h
        Audio.h
        Playlist.h
        PlaylistsManager.h
        Menu.h)

target_link_libraries(AudioPlayerProject winmm)