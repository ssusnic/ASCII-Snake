# ASCII Snake for Windows Console

This repository contains the source code of my terminal based **Snake** game written in **C++** for the **Windows Command Line**.  

The game is primarily developed with **MinGW** development tools using the **GCC** compiler and is available in the **Snake_MinGW** folder.

But if you rather prefer Visual Studio than MinGW to compile your C++ projects, then lucky you!  
There is also a **Visual Studio** solution of the Snake game availaible in the **Snake_VS** folder.

Your task is to move the snake with the cursor keys, and eat as much food as possible before you die of insatiable greed. The snake earns points with each item eaten, but it also gets longer as a result of enormous gluttony. The game is over when the snake runs into itself, or hits the border walls.  

Watch the Video Tutorial:  

[![Watch Video!](https://github.com/ssusnic/ASCII-Snake/raw/main/thumb_snake_720x480.png)](https://www.youtube.com/watch?v=ivxeUwFvjow "Watch Video!")


## Terminator Framework

To make this game, I used my own game framework called **Terminator**, which provides a set of specific functions needed for developing terminal based games in Windows Console as follows:  

  - creating and destroying console window
  - tracking time to ensure refreshing at proper frames per second
  - drawing characters, text and rectangles
  - clearing and redrawing the screen
  - playing sounds

The framework is consisted of the following files:
  - ```Terminator.h``` - header file
  - ```Terminator.lib``` - static library
  - ```Terminator.dll``` - dynamic library

Since the binary files generated with different C++ compilers are in general not link compatible, there are special versions of the Terminator framework for using with MinGW and Visual Studio.


## Building the game with MinGW

1. install MinGW development tools (https://www.mingw-w64.org/) 
2. download the MinGW project from the **Snake_MinGW** folder 
3. build the game:  
    a) dynamically by running this command:
      ```shell
      g++ Snake.cpp Terminator.dll -o Snake.exe -DUNICODE -O3 -lwinmm
      ```
    b) statically by running this command:  
      ```shell
      g++ Snake.cpp Terminator.lib -o Snake.exe -DUNICODE -O3 -lwinmm -DSTATIC_LIB -static  
      ```
    c) by using the make.bat script and running the following commands:  
      ```make -d``` to build dynamically  
      ```make -s``` to build statically  


## Building the game with Visual Studio

1. install MS Visual Studio (https://visualstudio.microsoft.com/)  
2. download the Visual Studio solution from the **Snake_VS** folder  
3. open **Snake.sln** in MS Visual Studio
4. select the Solution Configuration (Debug/Release)
5. select the Solution Platform (x64/x86)
6. choose the Build Solution command to build the game


## License notice

Copyright (C) 2022 Ask For Game Task

All programs in this repository are protected by GNU General Public License version 3.  
If you use them, you must attribute me.

Each program in this repository is free software: 
you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or any later version.

Each program in this repository is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 

See the LICENSE file for more details on the GNU General Public License.
