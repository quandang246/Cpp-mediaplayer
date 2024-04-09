# Media Files Browser & Player CLI Application

This is a CLI (Command Line Interface) application written in C++ for Linux systems, designed to serve as a basic media files browser and player. The application allows users to navigate through directories, view media files, create playlists, view metadata of media files, edit metadata, and play music using SDL2/taglib library. 

## Requirements

- Linux Operating System (Currently, I'm using Ubuntu 20.04)
- Compiler C++20 (Maybe C++17 can also work)
- Taglib Library
- SDL2 Library
- CMake (Currently, I'm using CMake 3.16.3)

## Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/quandang246/Cpp-mediaplayer.git
    ```

2. Compile the taglib:

    ```bash
    cd path-to-taglib
    mkdir build
    cd build/
    cmake -S .. -B .
    make
    sudo make install 
    ```

2. Navigate to the project directory:

    ```bash
    cd path-to-Cpp-mediaplayer
    ```

3. Compile the source code:

    ```bash
    mkdir build
    cd build/
    cmake -S .. -B .
    make
    sudo make install 
    ```

4. Run the application (can run anywhere in your computer):

    ```bash
    media 
    ```

## Usage

### Running the Application

- The application can be run from any directory on your computer or from an external USB device (ensure the device is mounted).

### Note (using with usb)

- First, you need to mount your usb int usb/ folder with following command:

    ```bash
    sudo mount -t drvfs usb_disk_name: path_to_usb_folder
    sudo mount -t drvfs E: /home/quan246/projects/src/mock_prj/usb
    ```

- Last, you need to unmount your usb with following command:

    ```bash
    sudo umount path_to_usb_folder
    sudo umount /home/quan246/projects/src/mock_prj/usb
    ```

### Available Options

1. **View List of Media Files**:
    - [x] Displays a list of media files (audio and video) in the current folder and all sub-folders with pagination (25 files per page).

2. **Playlists**:
    - Allows users to manage playlists:
        - [x] View existing playlists
        - [x] View contents of a playlist
        - [x] Create, update, and delete playlists

3. **Metadata of a File**:
    - Retrieve and edit metadata of media files:
        - [x] View metadata such as track name, album, artist, duration, genre, publisher, publish year for audio files; name, size, duration, bitrate, codec for video files.
        - [x] Edit metadata: modify existing values or add new keys.

4. **Play Music**:
    - Utilizes SDL2 library to play music:
        - [x] Play functionality (in another thread)
        - [x] Pause/Resume functionality
        - [x] Next/Previous track
        - [x] Automatically moves to the next song when the current song finishes
        - [x] Displays current time and duration of the song

5. **Change Volume**:
    - [x] Adjust the volume of the device.

## Dependencies

- Taglib Library: This application uses Taglib library for read/edit metadata.
- SDL2 Library: This application uses SDL2 library for multimedia playback.

## Acknowledgments

- Special thanks to the SDL2 and Taglib community for providing a powerful library for multimedia applications.
- Thanks to [TagLib](https://taglib.org/) for the library to handle audio metadata.
- Thanks to [SDL2](https://www.libsdl.org/) for the library to handle play audio/video.
  
Please let me know if you need further assistance or have any questions!
