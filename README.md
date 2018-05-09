# Character-Lookup-VLC-Plugin

VLC Plugin that lets you find out a character's name and background at the press of a button.

##Platforms

Currently only supports Linux (Debian/Ubuntu)

##Building and Installing VLC Plugin

0. Download VLC

1. Clone or Download repo

2. Get required libraries and tools:
```bash
sudo apt-get install build-essential pkg-config libvlccore-dev libvlc-dev
```

3. Build and install:
```bash
make
sudo make install
```
4. Enable plugin from Preferences/Video/Video_Filters. Plugin should be named "Character Lookup"

##Building Qt Gui

0. Download QtCreator

1. Open Project in QtCreator

2. Build within QtCreator