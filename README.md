﻿# Spotui 🎵

Spotui is a Text-based User Interface (TUI) audio player designed to make managing and playing audio playlists an engaging and efficient experience directly from the terminal.

## 🎥 Project Showcase

Check out a demo of Spotui in action:
https://www.youtube.com/watch?v=R671-NRpTlc


## Features ✨

- **Playlist Management**:  
  - Create, delete, and manage multiple playlists.
  - Add or remove audio files from playlists with ease.

- **Audio Playback Controls**:  
  - Play, pause, resume, stop, or navigate between audio tracks.  
  - Shuffle playlist for a dynamic listening experience.

- **Intuitive Navigation**:  
  - Arrow keys for menu navigation.  
  - Press `S` to select options.  
  - Escape key to exit menus or stop playback.

- **TUI Design**:  
  - Clean, minimalist interface with clear instructions.  
  - Display audio information such as track name, type, and duration.

- **Persistent Storage**:  
  - Save playlists to a file to preserve data between sessions.  
  - Automatically load playlists on startup.

## Usage 🧑‍💻

1. **Main Menu**:  
   - Navigate through playlists using the arrow keys.
   - Select options to enter a playlist, create a new playlist, or delete an existing one.

2. **Inside a Playlist**:  
   - View all audio tracks with details such as name, type, and duration.
   - Add or delete audio tracks.

3. **Audio Playback**:  
   - Control playback with interactive buttons.  
   - Navigate between tracks or shuffle the playlist for random playback.

## Key Bindings ⌨️

| Key           | Action                           |
|---------------|----------------------------------|
| **Arrow Keys** | Navigate options or tracks.     |
| **S**         | Select the current option.       |
| **Escape**    | Exit current menu or stop audio. |

## Dependencies 📦

- **C++17 or later**
- **Windows Multimedia Library (`winmm`)**: Used for audio file operations.
- A terminal emulator capable of rendering basic ANSI color codes.

## Project Structure 📂

### UML
![](media/spotuiUML.png)

```
Spotui/
├── Menu.h                   # TUI menu management
├── PlaylistsManager.h       # Manages playlists
├── Playlist.h               # Playlist operations and UI
├── Audio.h                  # Audio playback and details
├── main.cpp                 # Entry point of the application
├── DoublyLL.h               # Doubly linked list for playlist tracks
└── Control.cpp              # Helper functions (e.g., screen clearing)
```

---

Thanks .. 
